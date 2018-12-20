// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_SATISFIES_HPP
#define BOOST_PARAMETER_AUX_PACK_SATISFIES_HPP

#include <boost/mpl/bool.hpp>
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if defined(__MINGW_32__) || ( \
        BOOST_WORKAROUND(BOOST_GCC, >= 40900) && \
        BOOST_WORKAROUND(BOOST_GCC, < 70000) \
    ) || !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#include <boost/parameter/aux_/arg_list.hpp>
#include <boost/parameter/aux_/augment_predicate.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/type_traits/is_same.hpp>
#else
#include <boost/parameter/aux_/yesno.hpp>
#include <boost/tti/detail/dnullptr.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

#if defined(__MINGW_32__) || ( \
        BOOST_WORKAROUND(BOOST_GCC, >= 40900) && \
        BOOST_WORKAROUND(BOOST_GCC, < 70000) \
    ) || !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
    template <typename ArgList, typename ParameterRequirements, typename Bound>
    struct satisfies_impl
      : ::boost::mpl::apply_wrap2<
            ::boost::parameter::aux::augment_predicate<
                typename ParameterRequirements::predicate
              , typename ArgList::reference
              , typename ArgList::key_type
            >
          , Bound
          , ArgList
        >
    {
    };
#endif

    // Returns mpl::true_ iff the given ParameterRequirements are satisfied by
    // ArgList.
    template <typename ArgList, typename ParameterRequirements>
    struct satisfies
    {
#if defined(__MINGW_32__) || ( \
        BOOST_WORKAROUND(BOOST_GCC, >= 40900) && \
        BOOST_WORKAROUND(BOOST_GCC, < 70000) \
    ) || !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
        // The compilers & modes detected above report ambiguous overloads,
        // so we use this instead.
        typedef typename ::boost::mpl::apply_wrap3<
            typename ArgList::binding
          , typename ParameterRequirements::keyword
          , ::boost::parameter::void_
          , ::boost::mpl::false_
        >::type bound;

        typedef typename ::boost::mpl::eval_if<
            ::boost::is_same<bound,::boost::parameter::void_>
          , typename ParameterRequirements::has_default
          , ::boost::mpl::eval_if<
                ::boost::is_same<
                    ArgList
                  , ::boost::parameter::aux::empty_arg_list
                >
              , ::boost::mpl::false_
              , ::boost::parameter::aux::satisfies_impl<
                    ArgList
                  , ParameterRequirements
                  , bound
                >
            >
        >::type type;
#else   // Use sizeof() trick.
        BOOST_STATIC_CONSTANT(
            bool, value = (
                sizeof(
                    ::boost::parameter::aux::to_yesno(
                        ArgList::satisfies(
                            static_cast<ParameterRequirements*>(
                                BOOST_TTI_DETAIL_NULLPTR
                            )
                          , static_cast<ArgList*>(BOOST_TTI_DETAIL_NULLPTR)
                        )
                    )
                ) == sizeof(::boost::parameter::aux::yes_tag)
            )
        );

        typedef ::boost::mpl::bool_<satisfies::value> type;
#endif  // Workarounds needed.
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/pack/as_parameter_requirements.hpp>

namespace boost { namespace parameter { namespace aux {
    // Returns mpl::true_ if the requirements of the given ParameterSpec
    // are satisfied by ArgList.
    template <typename ArgList, typename ParameterSpec>
    struct satisfies_requirements_of
      : ::boost::parameter::aux::satisfies<
            ArgList
          , typename ::boost::parameter::aux
            ::as_parameter_requirements<ParameterSpec>::type
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard

