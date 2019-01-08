// Copyright Cromwell D. Enage 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_HAS_NESTED_TEMPLATE_FN_HPP
#define BOOST_PARAMETER_AUX_HAS_NESTED_TEMPLATE_FN_HPP

#include <boost/mpl/has_xxx.hpp>

namespace boost { namespace parameter { namespace aux {

    BOOST_MPL_HAS_XXX_TEMPLATE_NAMED_DEF(has_nested_tpl_fn_impl, fn, false)
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>
#else
#include <boost/type_traits/remove_const.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using has_nested_template_fn = ::boost::mp11::mp_if<
        typename ::boost::parameter::aux
        ::has_nested_tpl_fn_impl<typename ::std::remove_const<T>::type>::type
      , ::boost::mp11::mp_true
      , ::boost::mp11::mp_false
    >;
#else
    struct has_nested_template_fn
      : ::boost::parameter::aux::has_nested_tpl_fn_impl<
            typename ::std::remove_const<T>::type
            typename ::boost::remove_const<T>::type
        >::type
    {
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}}} // namespace boost::parameter::aux

#endif  // include guard

