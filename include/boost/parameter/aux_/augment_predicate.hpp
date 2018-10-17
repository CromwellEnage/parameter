// Copyright Cromwell D. Enage 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUGMENT_PREDICATE_HPP
#define BOOST_PARAMETER_AUGMENT_PREDICATE_HPP

namespace boost { namespace parameter { namespace aux {

    struct lambda_tag;
}}} // namespace boost::parameter::aux

#include <boost/parameter/keyword_fwd.hpp>
#include <boost/parameter/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>

#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
#include <boost/type_traits/is_lvalue_reference.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_same.hpp>
#else
#include <type_traits>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename V, typename R, typename Tag>
    struct augment_predicate_check_consume_ref
      : ::boost::mpl::eval_if<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
            ::boost::is_scalar<V>
#else
            ::std::is_scalar<V>
#endif
          , ::boost::mpl::true_
          , ::boost::mpl::eval_if<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
                ::boost::is_same<
#else
                ::std::is_same<
#endif
                    typename Tag::qualifier
                  , ::boost::parameter::consume_reference
                >
              , ::boost::mpl::if_<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
                    ::boost::is_lvalue_reference<R>
#else
                    ::std::is_lvalue_reference<R>
#endif
                  , ::boost::mpl::false_
                  , ::boost::mpl::true_
                >
              , boost::mpl::true_
            >
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/config/workaround.hpp>

#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS) || ( \
        BOOST_WORKAROUND(BOOST_MSVC, >= 1700) && \
        BOOST_WORKAROUND(BOOST_MSVC, < 1800) \
    )
#include <boost/type_traits/is_const.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename V, typename R, typename Tag>
    struct augment_predicate_check_out_ref
      : ::boost::mpl::eval_if<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
            ::boost::is_same<
#else
            ::std::is_same<
#endif
                typename Tag::qualifier
              , ::boost::parameter::out_reference
            >
          , ::boost::mpl::eval_if<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
                ::boost::is_lvalue_reference<R>
#else
                ::std::is_lvalue_reference<R>
#endif
              , ::boost::mpl::if_<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS) || ( \
        BOOST_WORKAROUND(BOOST_MSVC, >= 1700) && \
        BOOST_WORKAROUND(BOOST_MSVC, < 1800) \
    )
                    // MSVC 11.0 on AppVeyor reports error C2039:
                    // '_Is_const': is not a member of 'std::_Ptr_traits<_Ty>'
                    ::boost::is_const<V>
#else
                    ::std::is_const<V>
#endif
                  , ::boost::mpl::false_
                  , ::boost::mpl::true_
                >
              , ::boost::mpl::false_
            >
          , ::boost::mpl::true_
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/lambda.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Predicate, typename R, typename Tag>
    struct augment_predicate
    {
        typedef typename ::boost::mpl::lambda<
            Predicate
          , ::boost::parameter::aux::lambda_tag
        >::type actual_predicate;

        template <typename T, typename Args>
        struct apply
        {
            typedef typename ::boost::mpl::eval_if<
                typename ::boost::mpl::if_<
                    ::boost::parameter::aux
                    ::augment_predicate_check_consume_ref<T,R,Tag>
                  , ::boost::parameter::aux
                    ::augment_predicate_check_out_ref<T,R,Tag>
                  , ::boost::mpl::false_
                >::type
              , ::boost::mpl::apply_wrap2<actual_predicate,T,Args>
              , ::boost::mpl::false_
            >::type type;
        };
    };
}}} // namespace boost::parameter::aux

#endif  // include guard
