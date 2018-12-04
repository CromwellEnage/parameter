// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_PREPROCESSOR_060206_HPP
#define BOOST_PARAMETER_PREPROCESSOR_060206_HPP

#include <boost/parameter/aux_/preprocessor/impl/forwarding_overloads.hpp>

// Exapnds to a variadic function header that is enabled if and only if all
// its arguments are tagged arguments.  All arguments are accessible via args
// and keywords only.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION(result, name)                       \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_HEAD(result, name)                      \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_HEAD(name);                        \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_OVERLOAD(name, name, 0, 0)              \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_HEAD(name)
/**/

#include <boost/preprocessor/control/expr_if.hpp>

// Helper macro for BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION,
// BOOST_PARAMETER_NO_SPEC_CONST_MEMBER_FUNCTION,
// BOOST_PARAMETER_NO_SPEC_FUNCTION_CALL_OPERATOR, and
// and BOOST_PARAMETER_NO_SPEC_CONST_FUNCTION_CALL_OPERATOR.
#define BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION_AUX(result, name, impl, c)   \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_HEAD(result, impl)                      \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_OVERLOAD(name, impl, 1, c)              \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_HEAD(impl)                         \
    BOOST_PP_EXPR_IF(c, const)
/**/

// Exapnds to a variadic member function header that is enabled if and only if
// all its arguments are tagged arguments.  All arguments are accessible via
// args and keywords only.
#define BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION(result, name)                \
    BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION_AUX(result, name, name, 0)
/**/

// Exapnds to a const-qualified variadic member function header that is
// enabled if and only if all its arguments are tagged arguments.  All
// arguments are accessible via args and keywords only.
#define BOOST_PARAMETER_NO_SPEC_CONST_MEMBER_FUNCTION(result, name)          \
    BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION_AUX(result, name, name, 1)
/**/

// Exapnds to a variadic function call operator header that is enabled if and
// only if all its arguments are tagged arguments.  All arguments are
// accessible via args and keywords only.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_CALL_OPERATOR(result)               \
    BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION_AUX(                             \
        result, operator(), operator, 0                                      \
    )
/**/

// Exapnds to a const-qualified variadic function call operator header that is
// enabled if and only if all its arguments are tagged arguments.  All
// arguments are accessible via args and keywords only.
#define BOOST_PARAMETER_NO_SPEC_CONST_FUNCTION_CALL_OPERATOR(result)         \
    BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION_AUX(                             \
        result, operator(), operator, 1                                      \
    )
/**/

#include <boost/parameter/aux_/preprocessor/impl/specification.hpp>
#include <boost/preprocessor/cat.hpp>

// Helper macro for BOOST_PARAMETER_CONSTRUCTOR.
#define BOOST_PARAMETER_CONSTRUCTOR_AUX(class_, base, tag_namespace, args)   \
    BOOST_PARAMETER_SPECIFICATION(tag_namespace, ctor, args)                 \
        BOOST_PP_CAT(constructor_parameters, __LINE__);                      \
    BOOST_PARAMETER_CONSTRUCTOR_OVERLOADS(class_, base, args)
/**/

#include <boost/parameter/aux_/preprocessor/impl/function_name.hpp>

// Defines the implementation function header.
#define BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name)                             \
    template <typename Args>                                                 \
    typename BOOST_PARAMETER_FUNCTION_RESULT_NAME(name)<                     \
        Args                                                                 \
    >::type BOOST_PARAMETER_FUNCTION_IMPL_NAME(name)(Args const& args)
/**/

#include <boost/parameter/aux_/preprocessor/impl/parenthesized_type.hpp>

// Expands to the result metafunction and the parameters specialization.
#define BOOST_PARAMETER_FUNCTION_HEAD(result, name, tag_namespace, args)     \
    template <typename Args>                                                 \
    struct BOOST_PARAMETER_FUNCTION_RESULT_NAME(name)                        \
    {                                                                        \
        typedef typename BOOST_PARAMETER_PARENTHESIZED_TYPE(result) type;    \
    };                                                                       \
    BOOST_PARAMETER_SPECIFICATION(tag_namespace, name, args)                 \
        BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(name);
/**/

// Helper macro for BOOST_PARAMETER_BASIC_FUNCTION.
#define BOOST_PARAMETER_BASIC_FUNCTION_AUX(result, name, tag_ns, args)       \
    BOOST_PARAMETER_FUNCTION_HEAD(result, name, tag_ns, args)                \
    BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name);                                \
    BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS(name, name, args, 0, 0)       \
    BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name)
/**/

// Helper macro for BOOST_PARAMETER_BASIC_MEMBER_FUNCTION,
// BOOST_PARAMETER_BASIC_CONST_MEMBER_FUNCTION,
// BOOST_PARAMETER_BASIC_FUNCTION_CALL_OPERATOR, and
// BOOST_PARAMETER_BASIC_CONST_FUNCTION_CALL_OPERATOR.
#define BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(r, n, i, tag_ns, args, c)  \
    BOOST_PARAMETER_FUNCTION_HEAD(r, i, tag_ns, args)                        \
    BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS(n, i, args, 1, c)             \
    BOOST_PARAMETER_FUNCTION_IMPL_HEAD(i) BOOST_PP_EXPR_IF(c, const)
/**/

#include <boost/parameter/aux_/preprocessor/impl/flatten.hpp>

// Expands to a Boost.Parameter-enabled constructor header.  All arguments are
// accessible via args and keywords only.
#define BOOST_PARAMETER_CONSTRUCTOR(class_, base, tag_namespace, args)       \
    BOOST_PARAMETER_CONSTRUCTOR_AUX(                                         \
        class_, base, tag_namespace                                          \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled function header.  All arguments are
// accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_FUNCTION(result, name, tag_namespace, args)    \
    BOOST_PARAMETER_BASIC_FUNCTION_AUX(                                      \
        result, name, tag_namespace                                          \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled member function header.  All arguments
// are accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_MEMBER_FUNCTION(result, name, tag_ns, args)    \
    BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(                               \
        result, name, name, tag_ns                                           \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args), 0                     \
    )
/**/

// Expands to a Boost.Parameter-enabled const-qualified member function
// header.  All arguments are accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_CONST_MEMBER_FUNCTION(r, name, tag_ns, args)   \
    BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(                               \
        r, name, name, tag_ns                                                \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args), 1                     \
    )
/**/

// Expands to a Boost.Parameter-enabled function call operator header.  All
// arguments are accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_FUNCTION_CALL_OPERATOR(result, tag_ns, args)   \
    BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(                               \
        result, operator(), operator, tag_ns                                 \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args), 0                     \
    )
/**/

// Expands to a Boost.Parameter-enabled const-qualified function call
// operator header.  All arguments are accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_CONST_FUNCTION_CALL_OPERATOR(r, tag_ns, args)  \
    BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(                               \
        r, operator(), operator, tag_ns                                      \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args), 1                     \
    )
/**/

#include <boost/parameter/aux_/preprocessor/impl/function_dispatch_layer.hpp>

// Helper macro for BOOST_PARAMETER_FUNCTION.
#define BOOST_PARAMETER_FUNCTION_AUX(result, name, tag_ns, args)             \
    BOOST_PARAMETER_FUNCTION_HEAD(result, name, tag_ns, args)                \
    BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name);                                \
    BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS(name, name, args, 0, 0)       \
    BOOST_PARAMETER_FUNCTION_DISPATCH_LAYER(                                 \
        1, (name, BOOST_PARAMETER_FUNCTION_SPLIT_ARGS(args), 0, 0, tag_ns)   \
    )
/**/

// Expands to a Boost.Parameter-enabled function header.  All arguments are
// accessible via args and keywords, as well as by name.
#define BOOST_PARAMETER_FUNCTION(result, name, tag_namespace, args)          \
    BOOST_PARAMETER_FUNCTION_AUX(                                            \
        result, name, tag_namespace                                          \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

// Helper macro for BOOST_PARAMETER_MEMBER_FUNCTION
// BOOST_PARAMETER_CONST_MEMBER_FUNCTION,
// BOOST_PARAMETER_FUNCTION_CALL_OPERATOR, and
// BOOST_PARAMETER_CONST_FUNCTION_CALL_OPERATOR.
#define BOOST_PARAMETER_MEMBER_FUNCTION_AUX(r, name, impl, tag_ns, c, args)  \
    BOOST_PARAMETER_FUNCTION_HEAD(r, impl, tag_ns, args)                     \
    BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS(name, impl, args, 1, c)       \
    BOOST_PARAMETER_FUNCTION_DISPATCH_LAYER(                                 \
        0, (                                                                 \
            impl                                                             \
          , BOOST_PARAMETER_FUNCTION_SPLIT_ARGS(args)                        \
          , BOOST_PP_IF(                                                     \
                BOOST_PARAMETER_MEMBER_FUNCTION_IS_STATIC(impl)              \
              , 0                                                            \
              , 1                                                            \
            )                                                                \
          , c                                                                \
          , tag_ns                                                           \
        )                                                                    \
    )
/**/

// Expands to a Boost.Parameter-enabled member function header.  All
// arguments are accessible via args and keywords, as well as by name.
#define BOOST_PARAMETER_MEMBER_FUNCTION(result, name, tag_ns, args)          \
    BOOST_PARAMETER_MEMBER_FUNCTION_AUX(                                     \
        result, name, name, tag_ns, 0                                        \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled const-qualified member function
// header.  All arguments are accessible via args and keywords, as well as
// by name.
#define BOOST_PARAMETER_CONST_MEMBER_FUNCTION(result, name, tag_ns, args)    \
    BOOST_PARAMETER_MEMBER_FUNCTION_AUX(                                     \
        result, name, name, tag_ns, 1                                        \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled function call operator header.  All
// arguments are accessible via args and keywords, as well as by name.
#define BOOST_PARAMETER_FUNCTION_CALL_OPERATOR(result, tag_ns, args)         \
    BOOST_PARAMETER_MEMBER_FUNCTION_AUX(                                     \
        result, operator(), operator, tag_ns, 0                              \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled const-qualified function call operator
// header.  All arguments are accessible via args and keywords, as well as
// by name.
#define BOOST_PARAMETER_CONST_FUNCTION_CALL_OPERATOR(result, tag_ns, args)   \
    BOOST_PARAMETER_MEMBER_FUNCTION_AUX(                                     \
        result, operator(), operator, tag_ns, 1                              \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

#endif  // include guard

