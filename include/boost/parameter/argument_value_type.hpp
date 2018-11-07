// Copyright Andrey Semashev 2016.
// Copyright Cromwell D. Enage 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_ARGUMENT_VALUE_TYPE_HPP
#define BOOST_PARAMETER_ARGUMENT_VALUE_TYPE_HPP

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename TaggedArg, typename Keyword>
    struct argument_value_type
      : ::boost::mpl::if_<
            ::boost::is_same<typename TaggedArg::key_type,Keyword>
          , typename TaggedArg::value_type
          , void
        >
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/is_tagged_argument.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace parameter {

    template <typename T, typename Keyword>
    struct argument_value_type
      : ::boost::mpl::eval_if<
            ::boost::parameter::aux_::is_tagged_argument<T>
          , ::boost::parameter::aux::argument_value_type<T,Keyword>
          , ::boost::mpl::identity<void>
        >
    {
        typedef void type;
    };
}} // namespace boost::parameter

#endif  // include guard

