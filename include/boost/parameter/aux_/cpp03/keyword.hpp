// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_CPP03_KEYWORD_HPP
#define BOOST_PARAMETER_AUX_CPP03_KEYWORD_HPP

#if !defined(BOOST_NO_SFINAE)
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_const.hpp>
#endif  // BOOST_NO_SFINAE

namespace boost { namespace parameter {

    // Instances of unique specializations of keyword<...> serve to
    // associate arguments with parameter names.  For example:
    //
    //     struct rate_;             // parameter names
    //     struct skew_;
    //
    //     namespace
    //     {
    //         keyword<rate_> rate;  // keywords
    //         keyword<skew_> skew;
    //     }
    //
    //     ...
    //
    //     f(rate = 1, skew = 2.4);
    template <typename Tag>
    struct keyword
    {
        template <typename T>
#if defined(BOOST_NO_SFINAE)
        inline typename ::boost::parameter::aux::tag<Tag,T const&>::type
#else
        inline typename ::boost::lazy_enable_if<
            typename ::boost::mpl::eval_if<
                ::boost::is_scalar<T>
              , ::boost::mpl::true_
              , ::boost::mpl::eval_if<
                    ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::in_reference
                    >
                  , ::boost::mpl::true_
                  , ::boost::mpl::if_<
                        ::boost::is_same<
                            typename Tag::qualifier
                          , ::boost::parameter::forward_reference
                        >
                      , ::boost::mpl::true_
                      , ::boost::mpl::false_
                    >
                >
            >::type
          , ::boost::parameter::aux::tag<Tag,T const&>
        >::type BOOST_CONSTEXPR
#endif  // BOOST_NO_SFINAE
            operator=(T const& x) const
        {
            typedef typename ::boost::parameter::aux
            ::tag<Tag,T const&>::type result;
            return result(x);
        }

        template <typename Default>
#if defined(BOOST_NO_SFINAE)
        inline ::boost::parameter::aux::default_<Tag,Default const>
#else
        inline typename ::boost::enable_if<
            typename ::boost::mpl::eval_if<
                ::boost::is_scalar<Default>
              , ::boost::mpl::true_
              , ::boost::mpl::eval_if<
                    ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::in_reference
                    >
                  , ::boost::mpl::true_
                  , ::boost::mpl::if_<
                        ::boost::is_same<
                            typename Tag::qualifier
                          , ::boost::parameter::forward_reference
                        >
                      , ::boost::mpl::true_
                      , ::boost::mpl::false_
                    >
                >
            >::type
          , ::boost::parameter::aux::default_<Tag,Default const>
        >::type
#endif  // BOOST_NO_SFINAE
            operator|(Default const& d) const
        {
            return ::boost::parameter::aux::default_<Tag,Default const>(d);
        }

        template <typename T>
#if defined(BOOST_NO_SFINAE)
        inline typename ::boost::parameter::aux::tag<Tag,T&>::type
#else
        inline typename ::boost::lazy_enable_if<
            typename ::boost::mpl::eval_if<
                typename ::boost::mpl::if_<
                    ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::out_reference
                    >
                  , ::boost::mpl::true_
                  , ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::forward_reference
                    >
                >::type
              , ::boost::mpl::if_<
                    ::boost::is_const<T>
                  , ::boost::mpl::false_
                  , ::boost::mpl::true_
                >
              , ::boost::mpl::false_
            >::type
          , ::boost::parameter::aux::tag<Tag,T&>
        >::type BOOST_CONSTEXPR
#endif  // BOOST_NO_SFINAE
            operator=(T& x) const
        {
            typedef typename ::boost::parameter::aux
            ::tag<Tag,T&>::type result;
            return result(x);
        }

        template <typename Default>
#if defined(BOOST_NO_SFINAE)
        inline ::boost::parameter::aux::default_<Tag,Default>
#else
        inline typename ::boost::enable_if<
            typename ::boost::mpl::eval_if<
                typename ::boost::mpl::if_<
                    ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::out_reference
                    >
                  , ::boost::mpl::true_
                  , ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::forward_reference
                    >
                >::type
              , ::boost::mpl::if_<
                    ::boost::is_const<Default>
                  , ::boost::mpl::false_
                  , ::boost::mpl::true_
                >
              , ::boost::mpl::false_
            >::type
          , ::boost::parameter::aux::default_<Tag,Default>
        >::type
#endif  // BOOST_NO_SFINAE
            operator|(Default& d) const
        {
            return ::boost::parameter::aux::default_<Tag,Default>(d);
        }

        template <typename Default>
        inline ::boost::parameter::aux::lazy_default<Tag,Default const>
            operator||(Default const& d) const
        {
            return ::boost::parameter::aux
            ::lazy_default<Tag,Default const>(d);
        }

        template <typename Default>
        inline ::boost::parameter::aux::lazy_default<Tag,Default>
            operator||(Default& d) const
        {
            return ::boost::parameter::aux::lazy_default<Tag,Default>(d);
        }

     public: // Insurance against ODR violations
        // Users will need to define their keywords in header files.  To
        // prevent ODR violations, it's important that the keyword used in
        // every instantiation of a function template is the same object.
        // We provide a reference to a common instance of each keyword
        // object and prevent construction by users.
        static ::boost::parameter::keyword<Tag> const instance;

        // This interface is deprecated.
        static ::boost::parameter::keyword<Tag>& get()
        {
            return const_cast< ::boost::parameter::keyword<Tag>&>(instance);
        }
    };

    template <typename Tag>
    ::boost::parameter::keyword<Tag> const ::boost::parameter
    ::keyword<Tag>::instance = ::boost::parameter::keyword<Tag>();
}} // namespace boost::parameter

#endif  // include guard

