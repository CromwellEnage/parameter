// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FORWARDING_OVERLOADS_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FORWARDING_OVERLOADS_HPP

#include <boost/preprocessor/cat.hpp>

// Expands to a definition of a constructor or forwarding function argument
// passed by const reference.  Used by BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_0
// and BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_0.
#define BOOST_PARAMETER_FUNCTION_ARG_TYPE_Z(z, n, type_prefix)               \
    BOOST_PP_CAT(type_prefix, n) const&
/**/

#include <boost/parameter/aux_/pp_impl/argument_pack.hpp>
#include <boost/parameter/aux_/preprocessor/impl/function_name.hpp>
#include <boost/parameter/aux_/preprocessor/impl/function_forward_match.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// Expands to a forwarding function, whose job is to consolidate its arguments
// into a pack for the front-end implementation function to take in.  Used by
// BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_Z when the number of arguments
// the forwarding function will take in is greater than or equal to
// BOOST_PARAMETER_ALL_CONST_THRESHOLD_ARITY, in which case all the arguments
// will be passed by const reference.
#define BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_0(z, n, data)              \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename ParameterArgumentType)>  \
    BOOST_PARAMETER_MEMBER_FUNCTION_STATIC(BOOST_PP_TUPLE_ELEM(3, 1, data))  \
    inline typename                                                          \
    BOOST_PARAMETER_FUNCTION_RESULT_NAME(BOOST_PP_TUPLE_ELEM(3, 1, data))<   \
        typename ::boost::parameter::aux::argument_pack<                     \
            BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(                     \
                BOOST_PP_TUPLE_ELEM(3, 1, data)                              \
            )                                                                \
          , BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_PARAMETER_FUNCTION_ARG_TYPE_Z                          \
              , ParameterArgumentType                                        \
            )                                                                \
        >::type                                                              \
    >::type                                                                  \
    BOOST_PARAMETER_MEMBER_FUNCTION_NAME(BOOST_PP_TUPLE_ELEM(3, 0, data))(   \
        BOOST_PP_ENUM_BINARY_PARAMS_Z(                                       \
            z, n, ParameterArgumentType, const& a                            \
        )                                                                    \
      , BOOST_PARAMETER_FUNCTION_FORWARD_MATCH_Z(                            \
            z                                                                \
          , BOOST_PP_TUPLE_ELEM(3, 1, data)                                  \
          , BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(                     \
                BOOST_PP_TUPLE_ELEM(3, 1, data)                              \
            )                                                                \
          , n                                                                \
          , ParameterArgumentType                                            \
        )                                                                    \
    ) BOOST_PP_EXPR_IF(BOOST_PP_TUPLE_ELEM(3, 2, data), const)               \
    {                                                                        \
        return BOOST_PARAMETER_FUNCTION_IMPL_NAME(                           \
            BOOST_PP_TUPLE_ELEM(3, 1, data)                                  \
        )(                                                                   \
            BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(                     \
                BOOST_PP_TUPLE_ELEM(3, 1, data)                              \
            )()(BOOST_PP_ENUM_PARAMS_Z(z, n, a))                             \
        );                                                                   \
    }
/**/

#include <boost/parameter/aux_/parenthesized_type.hpp>
#include <boost/preprocessor/comparison/equal.hpp>

// Expands to a constructor whose job is to consolidate its arguments into a
// pack for the delegate to take in.  Used by
// BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_Z when the number of arguments
// the forwarding function will take in is greater than or equal to
// BOOST_PARAMETER_ALL_CONST_THRESHOLD_ARITY, in which case all the arguments
// will be passed by const reference.
#define BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_0(z, n, data)                   \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename ParameterArgumentType)>  \
    BOOST_PP_EXPR_IF(BOOST_PP_EQUAL(n, 1), explicit)                         \
    inline BOOST_PP_TUPLE_ELEM(2, 0, data)(                                  \
        BOOST_PP_ENUM_BINARY_PARAMS_Z(                                       \
            z, n, ParameterArgumentType, const& a                            \
        )                                                                    \
      , BOOST_PARAMETER_FUNCTION_FORWARD_MATCH_Z(                            \
            z                                                                \
          , BOOST_PP_TUPLE_ELEM(2, 0, data)                                  \
          , BOOST_PP_CAT(constructor_parameters, __LINE__)                   \
          , n                                                                \
          , ParameterArgumentType                                            \
        )                                                                    \
    ) : BOOST_PARAMETER_PARENTHESIZED_TYPE(BOOST_PP_TUPLE_ELEM(2, 1, data))( \
            BOOST_PP_CAT(constructor_parameters, __LINE__)()(                \
                BOOST_PP_ENUM_PARAMS_Z(z, n, a)                              \
            )                                                                \
        )                                                                    \
    {                                                                        \
    }
/**/

#include <boost/preprocessor/seq/seq.hpp>

// Expands to a 0-arity forwarding function, whose job is to pass an empty
// pack to the front-end implementation function.
#define BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_0_ARITY(z, n, seq)         \
    inline BOOST_PARAMETER_MEMBER_FUNCTION_STATIC(                           \
        BOOST_PP_TUPLE_ELEM(                                                 \
            3, 1, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))                  \
        )                                                                    \
    )                                                                        \
    BOOST_PARAMETER_FUNCTION_RESULT_NAME(                                    \
        BOOST_PP_TUPLE_ELEM(                                                 \
            3, 1, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))                  \
        )                                                                    \
    )<                                                                       \
        ::boost::parameter::aux::argument_pack<                              \
            BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(                     \
                BOOST_PP_TUPLE_ELEM(                                         \
                    3, 1, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))          \
                )                                                            \
            )                                                                \
        >::type                                                              \
    >::type                                                                  \
    BOOST_PARAMETER_MEMBER_FUNCTION_NAME(                                    \
        BOOST_PP_TUPLE_ELEM(                                                 \
            3, 0, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))                  \
        )                                                                    \
    )() BOOST_PP_EXPR_IF(                                                    \
        BOOST_PP_TUPLE_ELEM(                                                 \
            3, 2, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))                  \
        )                                                                    \
      , const                                                                \
    )                                                                        \
    {                                                                        \
        return BOOST_PARAMETER_FUNCTION_IMPL_NAME(                           \
            BOOST_PP_TUPLE_ELEM(                                             \
                3, 1, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))              \
            )                                                                \
        )(                                                                   \
            BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(                     \
                BOOST_PP_TUPLE_ELEM(                                         \
                    3, 1, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))          \
                )                                                            \
            )()()                                                            \
        );                                                                   \
    }
/**/

// Expands to the default constructor, whose job is to pass an empty back to
// the delegate constructor of the base class.
#define BOOST_PARAMETER_DEFAULT_CONSTRUCTOR(z, n, seq)                       \
    inline                                                                   \
    BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq)))()   \
      : BOOST_PARAMETER_PARENTHESIZED_TYPE(                                  \
            BOOST_PP_TUPLE_ELEM(                                             \
                2, 1, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))              \
            )                                                                \
        )(BOOST_PP_CAT(constructor_parameters, __LINE__)()())                \
    {                                                                        \
    }
/**/

#include <boost/parameter/aux_/preprocessor/binary_seq_to_args.hpp>

// Expands to a forwarding function, whose job is to consolidate its arguments
// into a pack for the front-end implementation function to take in.  Each
// element in BOOST_PP_SEQ_TAIL(seq) determines the const-ness of the
// corresponding argument.
#define BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_R(r, seq)                  \
    template <                                                               \
        BOOST_PP_ENUM_PARAMS(                                                \
            BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL(seq))                        \
          , typename ParameterArgumentType                                   \
        )                                                                    \
    >                                                                        \
    inline BOOST_PARAMETER_MEMBER_FUNCTION_STATIC(                           \
        BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_SEQ_HEAD(seq))                    \
    )                                                                        \
    typename BOOST_PARAMETER_FUNCTION_RESULT_NAME(                           \
        BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_SEQ_HEAD(seq))                    \
    )<                                                                       \
        typename ::boost::parameter::aux::argument_pack<                     \
            BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(                     \
                BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_SEQ_HEAD(seq))            \
            )                                                                \
          , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARGS(                       \
                BOOST_PP_SEQ_TAIL(seq), (ParameterArgumentType)              \
            )                                                                \
        >::type                                                              \
    >::type                                                                  \
    BOOST_PARAMETER_MEMBER_FUNCTION_NAME(                                    \
        BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_SEQ_HEAD(seq))                    \
    )(                                                                       \
        BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARGS(                           \
            BOOST_PP_SEQ_TAIL(seq), (ParameterArgumentType)(a)               \
        )                                                                    \
      , BOOST_PARAMETER_FUNCTION_FORWARD_MATCH(                              \
            BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_SEQ_HEAD(seq))                \
          , BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(                     \
                BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_SEQ_HEAD(seq))            \
            )                                                                \
          , BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL(seq))                        \
          , ParameterArgumentType                                            \
        )                                                                    \
    ) BOOST_PP_EXPR_IF(                                                      \
        BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_HEAD(seq)), const             \
    )                                                                        \
    {                                                                        \
        return BOOST_PARAMETER_FUNCTION_IMPL_NAME(                           \
            BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_SEQ_HEAD(seq))                \
        )(                                                                   \
            BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(                     \
                BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_SEQ_HEAD(seq))            \
            )()(                                                             \
                BOOST_PP_ENUM_PARAMS(                                        \
                    BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL(seq)), a             \
                )                                                            \
            )                                                                \
        );                                                                   \
    }
/**/

// Expands to a constructor whose job is to consolidate its arguments into a
// pack for the delegate constructor of the base class to take in.  Each
// element in BOOST_PP_SEQ_TAIL(seq) determines the const-ness of the
// corresponding argument.
#define BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_R(r, seq)                       \
    template <                                                               \
        BOOST_PP_ENUM_PARAMS(                                                \
            BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL(seq))                        \
          , typename ParameterArgumentType                                   \
        )                                                                    \
    >                                                                        \
    inline BOOST_PP_EXPR_IF(                                                 \
        BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL(seq)), 1)         \
      , explicit                                                             \
    )                                                                        \
    BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_SEQ_HEAD(seq))(                       \
        BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARGS(                           \
            BOOST_PP_SEQ_TAIL(seq), (ParameterArgumentType)(a)               \
        )                                                                    \
      , BOOST_PARAMETER_FUNCTION_FORWARD_MATCH(                              \
            BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_SEQ_HEAD(seq))                \
          , BOOST_PP_CAT(constructor_parameters, __LINE__)                   \
          , BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL(seq))                        \
          , ParameterArgumentType                                            \
        )                                                                    \
    ) : BOOST_PARAMETER_PARENTHESIZED_TYPE(                                  \
            BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_SEQ_HEAD(seq))                \
        )(                                                                   \
            BOOST_PP_CAT(constructor_parameters, __LINE__)()(                \
                BOOST_PP_ENUM_PARAMS(                                        \
                    BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL(seq)), a             \
                )                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
    }
/**/

#include <boost/parameter/aux_/preprocessor/binary_seq_for_each.hpp>
#include <boost/preprocessor/control/if.hpp>

// Expands to all forwarding functions that take in n arguments.  Used by
// BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_Z when n is less than
// BOOST_PARAMETER_ALL_CONST_THRESHOLD_ARITY.
#define BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_1(z, n, data)              \
    BOOST_PP_IF(                                                             \
        n                                                                    \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_Z                         \
      , BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_0_ARITY                    \
    )(z, n, (BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_R)(data))
/**/

// Expands to all constructors that take in n arguments.  Used by
// BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_Z when n is less than
// BOOST_PARAMETER_ALL_CONST_THRESHOLD_ARITY.
#define BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_1(z, n, data)                   \
    BOOST_PP_IF(                                                             \
        n                                                                    \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_Z                         \
      , BOOST_PARAMETER_DEFAULT_CONSTRUCTOR                                  \
    )(z, n, (BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_R)(data))
/**/

#include <boost/preprocessor/comparison/less.hpp>

// Enables BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS_AUX to use either
// BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_0 or
// BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_1 within BOOST_PP_REPEAT_FROM_TO.
#define BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_Z(z, n, data)              \
    BOOST_PP_CAT(                                                            \
        BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_                           \
      , BOOST_PP_LESS(n, BOOST_PARAMETER_ALL_CONST_THRESHOLD_ARITY)          \
    )(z, n, data)
/**/

// Enables BOOST_PARAMETER_CONSTRUCTOR_OVERLOADS_AUX to use either
// BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_0 or
// BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_1 within BOOST_PP_REPEAT_FROM_TO.
#define BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_Z(z, n, data)                   \
    BOOST_PP_CAT(                                                            \
        BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_                                \
      , BOOST_PP_LESS(n, BOOST_PARAMETER_ALL_CONST_THRESHOLD_ARITY)          \
    )(z, n, data)
/**/

#include <boost/preprocessor/repetition/repeat_from_to.hpp>

// Helper macro for BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS.
#define BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS_AUX(name, impl, range, c) \
    BOOST_PP_REPEAT_FROM_TO(                                                 \
        BOOST_PP_TUPLE_ELEM(2, 0, range)                                     \
      , BOOST_PP_TUPLE_ELEM(2, 1, range)                                     \
      , BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOAD_Z                          \
      , (name, impl, c)                                                      \
    )
/**/

#include <boost/parameter/aux_/preprocessor/impl/arity_range.hpp>

// Expands to the layer of forwarding functions for the function with the
// specified name, whose arguments determine the range of arities.
#define BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS(name, impl, args, const_) \
    BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS_AUX(                          \
        name, impl, BOOST_PARAMETER_ARITY_RANGE(args), const_                \
    )
/**/

// Helper macro for BOOST_PARAMETER_CONSTRUCTOR_OVERLOADS.
#define BOOST_PARAMETER_CONSTRUCTOR_OVERLOADS_AUX(class_, base, range)       \
    BOOST_PP_REPEAT_FROM_TO(                                                 \
        BOOST_PP_TUPLE_ELEM(2, 0, range)                                     \
      , BOOST_PP_TUPLE_ELEM(2, 1, range)                                     \
      , BOOST_PARAMETER_CONSTRUCTOR_OVERLOAD_Z                               \
      , (class_, base)                                                       \
    )
/**/

// Expands to the layer of forwarding functions for the constructor in the
// specified class, whose arguments determine the range of arities.
#define BOOST_PARAMETER_CONSTRUCTOR_OVERLOADS(class_, base, args)            \
    BOOST_PARAMETER_CONSTRUCTOR_OVERLOADS_AUX(                               \
        class_, base, BOOST_PARAMETER_ARITY_RANGE(args)                      \
    )
/**/

#endif  // include guard

