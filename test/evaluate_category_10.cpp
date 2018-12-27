// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/parameter/config.hpp>

#if (BOOST_PARAMETER_MAX_ARITY < 10)
#error Define BOOST_PARAMETER_MAX_ARITY as 10 or greater.
#endif

#include <boost/parameter/name.hpp>

namespace test {

    BOOST_PARAMETER_NAME((_lrc0, keywords) in(lrc0))
    BOOST_PARAMETER_NAME((_lr0, keywords) in_out(lr0))
    BOOST_PARAMETER_NAME((_rrc0, keywords) in(rrc0))
#if !defined(__MINGW32__) && defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
    BOOST_PARAMETER_NAME((_rr0, keywords) consume(rr0))
#else
    BOOST_PARAMETER_NAME((_rr0, keywords) rr0)
#endif
    BOOST_PARAMETER_NAME((_lrc1, keywords) in(lrc1))
    BOOST_PARAMETER_NAME((_lr1, keywords) out(lr1))
    BOOST_PARAMETER_NAME((_rrc1, keywords) in(rrc1))
    BOOST_PARAMETER_NAME((_lrc2, keywords) in(lrc2))
    BOOST_PARAMETER_NAME((_lr2, keywords) out(lr2))
    BOOST_PARAMETER_NAME((_rr2, keywords) rr2)
} // namespace test

#include <boost/parameter/parameters.hpp>

#if ( \
        !defined(__MINGW32__) && ( \
            defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING) || \
            (10 < BOOST_PARAMETER_EXPONENTIAL_OVERLOAD_THRESHOLD_ARITY) \
        ) \
    ) || ( \
        !defined(__APPLE_CC__) && !( \
            defined(linux) && BOOST_WORKAROUND(BOOST_GCC, == 40800) \
        ) \
    )
#include <boost/parameter/required.hpp>
#include <boost/parameter/optional.hpp>
#endif

namespace test {

    struct g_parameters
      : boost::parameter::parameters<
#if ( \
        !defined(__MINGW32__) && ( \
            defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING) || \
            (10 < BOOST_PARAMETER_EXPONENTIAL_OVERLOAD_THRESHOLD_ARITY) \
        ) \
    ) || ( \
        !defined(__APPLE_CC__) && !( \
            defined(linux) && BOOST_WORKAROUND(BOOST_GCC, == 40800) \
        ) \
    )
            boost::parameter::required<test::keywords::lrc0>
          , boost::parameter::required<test::keywords::lr0>
          , boost::parameter::required<test::keywords::rrc0>
          , boost::parameter::required<test::keywords::rr0>
          , boost::parameter::required<test::keywords::lrc1>
          , boost::parameter::required<test::keywords::lr1>
          , boost::parameter::required<test::keywords::rrc1>
          , boost::parameter::optional<test::keywords::lrc2>
          , boost::parameter::optional<test::keywords::lr2>
          , boost::parameter::optional<test::keywords::rr2>
#endif
        >
    {
    };
} // namespace test

#include <boost/core/lightweight_test.hpp>
#include "evaluate_category.hpp"

namespace test {

    struct C
    {
        template <typename Args>
        static void evaluate(Args const& args)
        {
            BOOST_TEST_EQ(
                test::passed_by_lvalue_reference_to_const
              , test::U::evaluate_category<0>(args[test::_lrc0])
            );
            BOOST_TEST_EQ(
                test::passed_by_lvalue_reference
              , test::U::evaluate_category<0>(args[test::_lr0])
            );
            BOOST_TEST_EQ(
                test::passed_by_lvalue_reference_to_const
              , test::U::evaluate_category<1>(args[test::_lrc1])
            );
            BOOST_TEST_EQ(
                test::passed_by_lvalue_reference
              , test::U::evaluate_category<1>(args[test::_lr1])
            );
            BOOST_TEST_EQ(
                test::passed_by_lvalue_reference_to_const
              , test::U::evaluate_category<2>(
                    args[test::_lrc2 | test::lvalue_const_bitset<2>()]
                )
            );
            BOOST_TEST_EQ(
                test::passed_by_lvalue_reference
              , test::U::evaluate_category<2>(
                    args[test::_lr2 || test::lvalue_bitset_function<2>()]
                )
            );
#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
            BOOST_TEST_EQ(
                test::passed_by_rvalue_reference_to_const
              , test::U::evaluate_category<0>(args[test::_rrc0])
            );
            BOOST_TEST_EQ(
                test::passed_by_rvalue_reference
              , test::U::evaluate_category<0>(args[test::_rr0])
            );
            BOOST_TEST_EQ(
                test::passed_by_rvalue_reference_to_const
              , test::U::evaluate_category<1>(args[test::_rrc1])
            );
            BOOST_TEST_EQ(
                test::passed_by_rvalue_reference
              , test::U::evaluate_category<2>(
                    args[test::_rr2 || test::rvalue_bitset_function<2>()]
                )
            );
#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
            BOOST_TEST_EQ(
                test::passed_by_lvalue_reference_to_const
              , test::U::evaluate_category<0>(args[test::_rrc0])
            );
            BOOST_TEST_EQ(
                test::passed_by_lvalue_reference_to_const
              , test::U::evaluate_category<0>(args[test::_rr0])
            );
            BOOST_TEST_EQ(
                test::passed_by_lvalue_reference_to_const
              , test::U::evaluate_category<1>(args[test::_rrc1])
            );
            BOOST_TEST_EQ(
                test::passed_by_lvalue_reference_to_const
              , test::U::evaluate_category<2>(
                    args[test::_rr2 || test::rvalue_bitset_function<2>()]
                )
            );
#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
        }
    };
} // namespace test

#if defined(__MINGW32__) || ( \
        !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING) && \
        !(10 < BOOST_PARAMETER_EXPONENTIAL_OVERLOAD_THRESHOLD_ARITY) \
    )
#include <boost/parameter/aux_/as_lvalue.hpp>
#include <boost/core/ref.hpp>
#endif

int main()
{
#if !defined(__MINGW32__) && ( \
        defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING) || \
        (10 < BOOST_PARAMETER_EXPONENTIAL_OVERLOAD_THRESHOLD_ARITY) \
    )
    test::C::evaluate(
        test::g_parameters()(
            test::lvalue_const_bitset<0>()
          , test::lvalue_bitset<0>()
          , test::rvalue_const_bitset<0>()
          , test::rvalue_bitset<0>()
          , test::lvalue_const_bitset<1>()
          , test::lvalue_bitset<1>()
          , test::rvalue_const_bitset<1>()
        )
    );
    test::C::evaluate(
        test::g_parameters()(
            test::lvalue_const_bitset<0>()
          , test::lvalue_bitset<0>()
          , test::rvalue_const_bitset<0>()
          , test::rvalue_bitset<0>()
          , test::lvalue_const_bitset<1>()
          , test::lvalue_bitset<1>()
          , test::rvalue_const_bitset<1>()
          , test::lvalue_const_bitset<2>()
          , test::lvalue_bitset<2>()
          , test::rvalue_bitset<2>()
        )
    );
#elif !defined(__APPLE_CC__) && !( \
        defined(linux) && BOOST_WORKAROUND(BOOST_GCC, == 40800) \
    )
    test::C::evaluate(
        test::g_parameters()(
            test::lvalue_const_bitset<0>()
          , boost::ref(test::lvalue_bitset<0>())
          , test::rvalue_const_bitset<0>()
          , boost::parameter::aux::as_lvalue(test::rvalue_bitset<0>())
          , test::lvalue_const_bitset<1>()
          , boost::ref(test::lvalue_bitset<1>())
          , test::rvalue_const_bitset<1>()
        )
    );
    test::C::evaluate(
        test::g_parameters()(
            test::lvalue_const_bitset<0>()
          , boost::ref(test::lvalue_bitset<0>())
          , test::rvalue_const_bitset<0>()
          , boost::parameter::aux::as_lvalue(test::rvalue_bitset<0>())
          , test::lvalue_const_bitset<1>()
          , boost::ref(test::lvalue_bitset<1>())
          , test::rvalue_const_bitset<1>()
          , test::lvalue_const_bitset<2>()
          , boost::ref(test::lvalue_bitset<2>())
          , boost::parameter::aux::as_lvalue(test::rvalue_bitset<2>())
        )
    );
#else   // All parameters must be named.
    test::C::evaluate(
        test::g_parameters()(
            test::_lrc0 = test::lvalue_const_bitset<0>()
          , test::_lr0 = boost::ref(test::lvalue_bitset<0>())
          , test::_rrc0 = test::rvalue_const_bitset<0>()
          , test::_rr0 = boost::parameter::aux::as_lvalue(
                test::rvalue_bitset<0>()
            )
          , test::_lrc1 = test::lvalue_const_bitset<1>()
          , test::_lr1 = boost::ref(test::lvalue_bitset<1>())
          , test::_rrc1 = test::rvalue_const_bitset<1>()
        )
    );
    test::C::evaluate(
        test::g_parameters()(
            test::_lrc0 = test::lvalue_const_bitset<0>()
          , test::_lr0 = boost::ref(test::lvalue_bitset<0>())
          , test::_rrc0 = test::rvalue_const_bitset<0>()
          , test::_rr0 = boost::parameter::aux::as_lvalue(
                test::rvalue_bitset<0>()
            )
          , test::_lrc1 = test::lvalue_const_bitset<1>()
          , test::_lr1 = boost::ref(test::lvalue_bitset<1>())
          , test::_rrc1 = test::rvalue_const_bitset<1>()
          , test::_lrc2 = test::lvalue_const_bitset<2>()
          , test::_lr2 = boost::ref(test::lvalue_bitset<2>())
          , test::_rr2 = boost::parameter::aux::as_lvalue(
                test::rvalue_bitset<2>()
            )
        )
    );
#endif
    return boost::report_errors();
}

