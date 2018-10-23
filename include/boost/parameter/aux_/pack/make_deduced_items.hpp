// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_MAKE_DEDUCED_ITEMS_HPP
#define BOOST_PARAMETER_AUX_PACK_MAKE_DEDUCED_ITEMS_HPP

#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/pack/deduced_item.hpp>
#include <boost/parameter/deduced.hpp>
#include <boost/parameter/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
#include <boost/type_traits/is_same.hpp>
#else
#include <type_traits>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename Spec, typename Tail>
    struct make_deduced_items
      : ::boost::mpl::eval_if<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
            ::boost::is_same<Spec,::boost::parameter::void_>
#else
            ::std::is_same<Spec,::boost::parameter::void_>
#endif
          , ::boost::mpl::identity< ::boost::parameter::void_>
          , ::boost::mpl::eval_if<
                ::boost::parameter::aux::is_deduced<Spec>
              , ::boost::parameter::aux::make_deduced_item<Spec,Tail>
              , Tail
            >
        >
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard

