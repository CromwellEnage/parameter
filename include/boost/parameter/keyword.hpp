// Copyright Daniel Wallin, David Abrahams 2005. Use, modification and
// distribution is subject to the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef KEYWORD_050328_HPP
#define KEYWORD_050328_HPP

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if !defined(BOOST_NO_SFINAE) && BOOST_WORKAROUND(BOOST_MSVC, >= 1700) && \
    BOOST_WORKAROUND(BOOST_MSVC, < 1800)
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/function.hpp>
#endif  // MSVC-11.0

#include <boost/parameter/aux_/unwrap_cv_reference.hpp>
#include <boost/parameter/aux_/tag.hpp>
#include <boost/parameter/aux_/default.hpp>

namespace boost { namespace parameter {

// Instances of unique specializations of keyword<...> serve to
// associate arguments with parameter names.  For example:
//
//    struct rate_;           // parameter names
//    struct skew_;
//    namespace
//    {
//      keyword<rate_> rate;  // keywords
//      keyword<skew_> skew;
//    }
//
//    ...
//
//    f(rate = 1, skew = 2.4);
//
template <typename Tag>
struct keyword
{
#if !defined(BOOST_NO_SFINAE) && BOOST_WORKAROUND(BOOST_MSVC, >= 1700) && \
    BOOST_WORKAROUND(BOOST_MSVC, < 1800)
    template <typename T>
    typename ::boost::lazy_enable_if<
        ::boost::is_function<
            typename ::boost::remove_const<
                typename ::boost::remove_pointer<
                    typename ::boost::remove_reference<T>::type
                >::type
            >::type
        >
      , ::boost::parameter::aux::tag<Tag,T>
    >::type const
    operator=(T x) const
    {
        typedef typename ::boost::parameter::aux::tag<Tag,T>::type result;
        return result(
            ::boost::function<
                typename ::boost::remove_const<
                    typename ::boost::remove_pointer<
                        typename ::boost::remove_reference<T>::type
                    >::type
                >::type
            >(x)
        );
    }
#endif  // MSVC-11.0

    template <typename T>
#if !defined(BOOST_NO_SFINAE) && BOOST_WORKAROUND(BOOST_MSVC, >= 1700) && \
    BOOST_WORKAROUND(BOOST_MSVC, < 1800)
    typename ::boost::lazy_enable_if<
        typename ::boost::mpl::eval_if<
            ::boost::is_function<
                typename ::boost::remove_const<
                    typename ::boost::remove_pointer<T>::type
                >::type
            >
          , ::boost::mpl::false_
          , ::boost::mpl::if_<
                ::boost::is_const<T>
              , ::boost::mpl::false_
              , ::boost::mpl::true_
            >
        >::type
      , ::boost::parameter::aux::tag<Tag,T>
    >::type const
#else
    typename ::boost::parameter::aux::tag<Tag,T>::type const
#endif  // MSVC-11.0
    operator=(T& x) const
    {
        typedef typename ::boost::parameter::aux::tag<Tag,T>::type result;
        return result(x);
    }

    template <typename Default>
    aux::default_<Tag, Default>
    operator|(Default& default_) const
    {
        return aux::default_<Tag, Default>(default_);
    }

    template <typename Default>
    aux::lazy_default<Tag, Default>
    operator||(Default& default_) const
    {
        return aux::lazy_default<Tag, Default>(default_);
    }

    template <typename T>
#if !defined(BOOST_NO_SFINAE) && BOOST_WORKAROUND(BOOST_MSVC, >= 1700) && \
    BOOST_WORKAROUND(BOOST_MSVC, < 1800)
    typename ::boost::lazy_enable_if<
        typename ::boost::mpl::eval_if<
            ::boost::is_function<
                typename ::boost::remove_const<
                    typename ::boost::remove_pointer<T>::type
                >::type
            >
          , ::boost::mpl::false_
          , ::boost::mpl::true_
        >::type
      , ::boost::parameter::aux::tag<Tag,T const>
    >::type const
#else
    typename ::boost::parameter::aux::tag<Tag,T const>::type const
#endif  // MSVC-11.0
    operator=(T const& x) const
    {
        typedef typename ::boost::parameter::aux
        ::tag<Tag,T const>::type result;
        return result(x);
    }

    template <typename Default>
    aux::default_<Tag, const Default>
    operator|(Default const& default_) const
    {
        return aux::default_<Tag, Default const>(default_);
    }

    template <typename Default>
    aux::lazy_default<Tag, Default>
    operator||(Default const& default_) const
    {
        return aux::lazy_default<Tag, Default>(default_);
    }

 public: // Insurance against ODR violations
    // People will need to define these keywords in header files.  To
    // prevent ODR violations, it's important that the keyword used in
    // every instantiation of a function template is the same object.
    // We provide a reference to a common instance of each keyword
    // object and prevent construction by users.
    static keyword<Tag> const instance;

    // This interface is deprecated
    static keyword<Tag>& get()
    {
        return const_cast<keyword<Tag>&>(instance);
    }
};

template <typename Tag>
keyword<Tag> const keyword<Tag>::instance = {};

// Reduces boilerplate required to declare and initialize keywords
// without violating ODR.  Declares a keyword tag type with the given
// name in namespace tag_namespace, and declares and initializes a
// reference in an anonymous namespace to a singleton instance of that
// type.

#define BOOST_PARAMETER_KEYWORD(tag_namespace,name)                 \
    namespace tag_namespace                                         \
    {                                                               \
      struct name                                                   \
      {                                                             \
          static char const* keyword_name()                         \
          {                                                         \
              return #name;                                         \
          }                                                         \
      };                                                            \
    }                                                               \
    namespace                                                       \
    {                                                               \
       ::boost::parameter::keyword<tag_namespace::name> const& name \
       = ::boost::parameter::keyword<tag_namespace::name>::instance;\
    }

}} // namespace boost::parameter

#endif // KEYWORD_050328_HPP

