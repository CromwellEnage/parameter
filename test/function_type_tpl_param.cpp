// Copyright Frank Mori Hess 2009.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/parameter/template_keyword.hpp>
#include <boost/parameter/parameters.hpp>
#include <boost/parameter/required.hpp>
#include <boost/parameter/value_type.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace test {
    namespace keywords {

        BOOST_PARAMETER_TEMPLATE_KEYWORD(function_type)
    } // namespace keywords

    template <typename K, typename A>
    struct X
      : boost::parameter::value_type<
            typename boost::parameter::parameters<
                boost::parameter::required<K>
            >::BOOST_NESTED_TEMPLATE bind<A>::type
          , K
        >
    {
    };

    template <typename T>
    struct Y
      : boost::mpl::if_<
            boost::is_same<
                T
              , typename X<
                    test::keywords::tag::function_type
                  , test::keywords::function_type<T>
                >::type
            >
          , boost::mpl::true_
          , boost::mpl::false_
        >::type
    {
    };

    struct Z
    {
        int operator()() const
        {
            return 0;
        }
    };
} // namespace test

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>

namespace test {

    template <typename T>
    using Y_mp11 = std::is_same<
        T
      , typename X<
            test::keywords::tag::function_type
          , test::keywords::function_type<T>
        >::type
    >;
} // namespace test

#endif  // BOOST_PARAMETER_CAN_USE_MP11

#include <boost/mpl/assert.hpp>
#include <boost/mpl/aux_/test.hpp>

MPL_TEST_CASE()
{
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    static_assert(test::Y_mp11<void()>::value, "void()");
    static_assert(test::Y_mp11<test::Z>::value, "test::Z");
    static_assert(test::Y_mp11<double(double)>::value, "double(double)");
#endif

    BOOST_MPL_ASSERT((test::Y<void()>));
    BOOST_MPL_ASSERT((test::Y<test::Z>));
    BOOST_MPL_ASSERT((test::Y<double(double)>));
}

