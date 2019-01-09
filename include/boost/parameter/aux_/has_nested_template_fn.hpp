// Copyright Cromwell D. Enage 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_HAS_NESTED_TEMPLATE_FN_HPP
#define BOOST_PARAMETER_AUX_HAS_NESTED_TEMPLATE_FN_HPP

#include <boost/parameter/aux_/yesno.hpp>
#include <boost/parameter/config.hpp>
#include <boost/tti/detail/dnullptr.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <template <typename P0, typename P1> class F>
    struct has_nested_template_fn_substitute_1
    {
    };

    template <typename T>
    class has_nested_template_fn_impl
    {
        template <typename U>
        static BOOST_CONSTEXPR ::boost::parameter::aux::no_tag _check(...);

        template <typename U>
        static BOOST_CONSTEXPR ::boost::parameter::aux::yes_tag
            _check(
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                ::boost::mp11::mp_identity<U> const volatile*
#else
                ::boost::mpl::identity<U> const volatile*
#endif
              , ::boost::parameter::aux::has_nested_template_fn_substitute_1<
                    U::template fn
                >* = BOOST_TTI_DETAIL_NULLPTR
            );

     public:
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_bool<
#else
        typedef ::boost::mpl::bool_<
#endif
            sizeof(
                ::boost::parameter::aux::has_nested_template_fn_impl<T>
                ::template _check<T>(
                    static_cast<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                        ::boost::mp11::mp_identity<T> const volatile*
#else
                        ::boost::mpl::identity<T> const volatile*
#endif
                    >(BOOST_TTI_DETAIL_NULLPTR)
                )
            ) == sizeof(::boost::parameter::aux::yes_tag)
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        >;
#else
        > type;
#endif
    };
}}} // namespace boost::parameter::aux

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>
#else
#include <boost/type_traits/remove_const.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using has_nested_template_fn = typename ::boost::parameter::aux
    ::has_nested_template_fn_impl<typename ::std::remove_const<T>::type>
    ::type;
#else
    struct has_nested_template_fn
      : ::boost::parameter::aux::has_nested_template_fn_impl<
            typename ::boost::remove_const<T>::type
        >::type
    {
    };
#endif
}}} // namespace boost::parameter::aux

#endif  // include guard

