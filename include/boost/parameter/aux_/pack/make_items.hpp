// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_MAKE_ITEMS_HPP
#define BOOST_PARAMETER_AUX_PACK_MAKE_ITEMS_HPP

#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/pack/item.hpp>
#include <boost/parameter/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
#include <boost/type_traits/is_same.hpp>
#else
#include <type_traits>
#endif

namespace boost { namespace parameter { namespace aux {

    // Creates a item typelist.
    template <typename Spec, typename Arg, typename Tail>
    struct make_items
      : ::boost::mpl::eval_if<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
            ::boost::is_same<Arg,::boost::parameter::void_>
#else
            ::std::is_same<Arg,::boost::parameter::void_>
#endif
          , ::boost::mpl::identity< ::boost::parameter::void_>
          , ::boost::parameter::aux::make_item<Spec,Arg,Tail>
        >
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard

