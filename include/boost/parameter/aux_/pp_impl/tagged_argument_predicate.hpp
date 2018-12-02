// Copyright Cromwell D. Enage 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PP_IMPL_TAGGED_ARGUMENT_PREDICATE_HPP
#define BOOST_PARAMETER_AUX_PP_IMPL_TAGGED_ARGUMENT_PREDICATE_HPP

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux {

    template <typename TaggedArg0, typename ...TaggedArgs>
    struct tagged_argument_predicate;
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/is_tagged_argument.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename TaggedArg0>
    struct tagged_argument_predicate<TaggedArg0>
      : ::boost::parameter::aux::is_tagged_argument<TaggedArg0>
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename TaggedArg0, typename ...TaggedArgs>
    struct tagged_argument_predicate
      : ::boost::mpl::if_<
            ::boost::parameter::aux::is_tagged_argument<TaggedArg0>
          , ::boost::parameter::aux::tagged_argument_predicate<TaggedArgs...>
          , ::boost::mpl::false_
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#define BOOST_PARAMETER_AUX_PP_IMPL_TAGGED_ARGUMENT_PRED_END_Z(z, n, f) ,f>
/**/

#include <boost/parameter/aux_/is_tagged_argument.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_AUX_PP_IMPL_TAGGED_ARGUMENT_PRED_BEG_Z(z, n, prefix) \
    ::boost::mpl::eval_if<                                                   \
        ::boost::parameter::aux::is_tagged_argument<BOOST_PP_CAT(prefix, n)>,
/**/

#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#define BOOST_PARAMETER_AUX_PP_IMPL_TAGGED_ARGUMENT_PRED_Z(z, n, prefix)     \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename prefix)>                 \
    struct tagged_argument_predicate<BOOST_PP_ENUM_PARAMS_Z(z, n, prefix)>   \
      : BOOST_PP_CAT(BOOST_PP_REPEAT_, z)(                                   \
            n                                                                \
          , BOOST_PARAMETER_AUX_PP_IMPL_TAGGED_ARGUMENT_PRED_BEG_Z           \
          , prefix                                                           \
        )                                                                    \
        ::boost::mpl::true_                                                  \
        BOOST_PP_CAT(BOOST_PP_REPEAT_, z)(                                   \
            n                                                                \
          , BOOST_PARAMETER_AUX_PP_IMPL_TAGGED_ARGUMENT_PRED_END_Z           \
          , ::boost::mpl::false_                                             \
        )::type                                                              \
    {                                                                        \
    };
/**/

#include <boost/parameter/aux_/void.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

namespace boost { namespace parameter { namespace aux {

    template <
        BOOST_PP_ENUM_BINARY_PARAMS(
            BOOST_PARAMETER_MAX_ARITY
          , typename TaggedArg
          , = ::boost::parameter::void_ BOOST_PP_INTERCEPT
        )
    >
    struct tagged_argument_predicate;
}}} // namespace boost::parameter::aux

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace boost { namespace parameter { namespace aux {

    BOOST_PP_REPEAT_FROM_TO(
        1
      , BOOST_PP_INC(BOOST_PARAMETER_MAX_ARITY)
      , BOOST_PARAMETER_AUX_PP_IMPL_TAGGED_ARGUMENT_PRED_Z
      , TaggedArg
    )
}}} // namespace boost::parameter::aux

#undef BOOST_PARAMETER_AUX_PP_IMPL_TAGGED_ARGUMENT_PRED_Z
#undef BOOST_PARAMETER_AUX_PP_IMPL_TAGGED_ARGUMENT_PRED_BEG_Z
#undef BOOST_PARAMETER_AUX_PP_IMPL_TAGGED_ARGUMENT_PRED_END_Z

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif  // include guard

