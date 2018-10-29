// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_CONFIG_050403_HPP
#define BOOST_PARAMETER_CONFIG_050403_HPP

#include <boost/move/detail/workaround.hpp>
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/deque/deque_fwd.hpp>

// Require correct SFINAE support, needed explicitly by tagged_argument &
// keyword & cast; correct function template ordering, needed by the code
// generation macros; either a variadic implementation of
// boost::fusion::list/deque or a user-defined variadic MPL Sequence model,
// needed by parameters; and the ability to handle multiple parameter packs,
// needed by parameters.  Older versions of GCC either don't have the latter
// ability or cannot disambiguate between keyword's overloaded
// operators.  Newer versions of MSVC fail on the evaluate_category and
// preprocessor_eval_category test programs when parameters uses
// boost::fusion::list.
// -- Cromwell D. Enage
#if !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING) && \
    !defined(BOOST_NO_SFINAE) && \
    !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) && \
    !BOOST_WORKAROUND(BOOST_GCC, < 40900) && ( \
        defined(BOOST_PARAMETER_VARIADIC_MPL_SEQUENCE) || ( \
            defined(BOOST_FUSION_HAS_VARIADIC_LIST) && ( \
                !defined(BOOST_MSVC) || (BOOST_MSVC < 1800) \
            ) \
        ) || defined(BOOST_FUSION_HAS_VARIADIC_DEQUE) \
    ) && defined(BOOST_MOVE_PERFECT_FORWARDING)
#define BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif

#if !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#error Your compiler does not support perfect forwarding.
#endif

// Deprecated. -- Cromwell D. Enage
#if !defined(BOOST_PARAMETER_MAX_ARITY)
#define BOOST_PARAMETER_MAX_ARITY 8
#endif
#endif  // include guard

