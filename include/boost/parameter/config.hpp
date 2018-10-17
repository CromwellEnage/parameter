// Copyright Daniel Wallin, David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_CONFIG_050403_HPP
#define BOOST_PARAMETER_CONFIG_050403_HPP

#include <boost/move/detail/workaround.hpp>
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/deque/deque_fwd.hpp>

// Allow projects to #define BOOST_PARAMETER_DISABLE_PERFECT_FORWARDING to
// turn off perfect forwarding as necessary.  Otherwise, also require correct
// SFINAE support, needed explicitly by tagged_argument & keyword & cast;
// correct function template ordering, needed by the code generation macros;
// either a variadic implementation of boost::fusion::list/deque or a
// user-defined variadic MPL Sequence model, needed by parameters; and the
// ability to handle multiple parameter packs, needed by parameters.  Older
// versions of GCC either don't have the latter ability or cannot
// disambiguate between keyword's overloaded operators.  Newer versions of
// MSVC fail on the evaluate_category and preprocessor_eval_category test
// programs when parameters uses boost::fusion::list.
// -- Cromwell D. Enage
#if !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING) && \
    !defined(BOOST_PARAMETER_DISABLE_PERFECT_FORWARDING) && \
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
#if !defined(BOOST_PARAMETER_ALL_CONST_THRESHOLD_ARITY)
#define BOOST_PARAMETER_ALL_CONST_THRESHOLD_ARITY 11
#endif
#endif

// Only in the absence of perfect forwarding should client code be limited
// by BOOST_PARAMETER_MAX_ARITY.  However, BOOST_PARAMETER_MAX_ARITY will
// remain defined for code that still needs it. -- Cromwell D. Enage
//#if !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#if !defined(BOOST_PARAMETER_MAX_ARITY)
#define BOOST_PARAMETER_MAX_ARITY 8
#endif
//#endif

#if !defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS) && ( \
        defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS) || ( \
            !defined(BOOST_MSVC) && ( \
                ( \
                    defined(BOOST_CLANG) && (1 == BOOST_CLANG) && \
                    !defined(__APPLE_CC__) \
                ) || ( \
                    BOOST_WORKAROUND(BOOST_GCC, < 40900) \
                ) || ( \
                    BOOST_WORKAROUND(BOOST_GCC, >= 40900) && \
                    !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING) \
                ) \
            ) \
        ) \
    )
// Most other compilers fulfulling the condition above have ICEd on certain
// tests due to using C++11 type traits instead of the Boost versions.
// -- Cromwell D. Enage
#define BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS
#endif
#endif  // include guard

