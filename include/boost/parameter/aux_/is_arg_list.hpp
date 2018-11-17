// Copyright Cromwell D. Enage 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_IS_ARG_LIST_HPP
#define BOOST_PARAMETER_AUX_IS_ARG_LIST_HPP

#include <boost/mpl/has_xxx.hpp>

namespace boost { namespace parameter { namespace aux {

    BOOST_MPL_HAS_XXX_TRAIT_DEF(binding)
    BOOST_MPL_HAS_XXX_TRAIT_DEF(tagged_arg)
    BOOST_MPL_HAS_XXX_TRAIT_DEF(tail_type)
}}} // namespace boost::parameter::aux

#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_arg_list
      : ::boost::mpl::eval_if<
            typename ::boost::mpl::eval_if<
                ::boost::parameter::aux::has_binding<T>
              , ::boost::parameter::aux::has_tagged_arg<T>
              , ::boost::mpl::false_
            >
          , ::boost::parameter::aux::has_tail_type<T>
          , ::boost::mpl::false_
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard

