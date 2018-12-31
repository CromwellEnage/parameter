// Copyright David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/parameter/aux_/unwrap_cv_reference.hpp>
#include <boost/parameter/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/aux_/test.hpp>
#include <boost/type_traits/is_same.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>
#endif

MPL_TEST_CASE()
{
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    static_assert(
        std::is_same<
            boost::parameter::aux::unwrap_cv_reference<int>::type
          , int
        >::value
      , "unwrap_cv_reference<int>::type should be int"
    );
    static_assert(
        std::is_same<
            boost::parameter::aux::unwrap_cv_reference<int const>::type
          , int const
        >::value
      , "unwrap_cv_reference<int const>::type should be int const"
    );
    static_assert(
        std::is_same<
            boost::parameter::aux::unwrap_cv_reference<int volatile>::type
          , int volatile
        >::value
      , "unwrap_cv_reference<int volatile>::type should be int volatile"
    );
    static_assert(
        std::is_same<
            boost::parameter::aux::unwrap_cv_reference<
                int const volatile
            >::type
          , int const volatile
        >::value
      , "unwrap_cv_reference<int cv>::type should be int cv"
    );
#endif  // BOOST_PARAMETER_CAN_USE_MP11

    BOOST_MPL_ASSERT((
        boost::mpl::if_<
            boost::is_same<
                boost::parameter::aux::unwrap_cv_reference<int>::type
              , int
            >
          , boost::mpl::true_
          , boost::mpl::false_
        >::type
    ));
    BOOST_MPL_ASSERT((
        boost::mpl::if_<
            boost::is_same<
                boost::parameter::aux::unwrap_cv_reference<int const>::type
              , int const
            >
          , boost::mpl::true_
          , boost::mpl::false_
        >::type
    ));
    BOOST_MPL_ASSERT((
        boost::mpl::if_<
            boost::is_same<
                boost::parameter::aux::unwrap_cv_reference<int volatile>::type
              , int volatile
            >
          , boost::mpl::true_
          , boost::mpl::false_
        >::type
    ));
    BOOST_MPL_ASSERT((
        boost::mpl::if_<
            boost::is_same<
                boost::parameter::aux::unwrap_cv_reference<
                    int const volatile
                >::type
              , int const volatile
            >
          , boost::mpl::true_
          , boost::mpl::false_
        >::type
    ));
}

namespace test {

    struct foo
    {
    };
} // namespace test

MPL_TEST_CASE()
{
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    static_assert(
        std::is_same<
            boost::parameter::aux::unwrap_cv_reference<test::foo>::type
          , test::foo
        >::value
      , "unwrap_cv_reference<foo>::type should be foo"
    );
    static_assert(
        std::is_same<
            boost::parameter::aux::unwrap_cv_reference<test::foo const>::type
          , test::foo const
        >::value
      , "unwrap_cv_reference<foo const>::type should be foo const"
    );
    static_assert(
        std::is_same<
            boost::parameter::aux::unwrap_cv_reference<
                test::foo volatile
            >::type
          , test::foo volatile
        >::value
      , "unwrap_cv_reference<foo volatile>::type should be foo volatile"
    );
    static_assert(
        std::is_same<
            boost::parameter::aux::unwrap_cv_reference<
                test::foo const volatile
            >::type
          , test::foo const volatile
        >::value
      , "unwrap_cv_reference<foo cv>::type should be foo cv"
    );
#endif  // BOOST_PARAMETER_CAN_USE_MP11

    BOOST_MPL_ASSERT((
        boost::mpl::if_<
            boost::is_same<
                boost::parameter::aux::unwrap_cv_reference<test::foo>::type
              , test::foo
            >
          , boost::mpl::true_
          , boost::mpl::false_
        >::type
    ));
    BOOST_MPL_ASSERT((
        boost::mpl::if_<
            boost::is_same<
                boost::parameter::aux::unwrap_cv_reference<
                    test::foo const
                >::type
              , test::foo const
            >
          , boost::mpl::true_
          , boost::mpl::false_
        >::type
    ));
    BOOST_MPL_ASSERT((
        boost::mpl::if_<
            boost::is_same<
                boost::parameter::aux::unwrap_cv_reference<
                    test::foo volatile
                >::type
              , test::foo volatile
            >
          , boost::mpl::true_
          , boost::mpl::false_
        >::type
    ));
    BOOST_MPL_ASSERT((
        boost::mpl::if_<
            boost::is_same<
                boost::parameter::aux::unwrap_cv_reference<
                    test::foo const volatile
                >::type
              , test::foo const volatile
            >
          , boost::mpl::true_
          , boost::mpl::false_
        >::type
    ));
}

#include <boost/ref.hpp>

MPL_TEST_CASE()
{
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    static_assert(
        std::is_same<
            boost::parameter::aux::unwrap_cv_reference<
                boost::reference_wrapper<test::foo>
            >::type
          , test::foo
        >::value
      , "unwrap_cv_reference<rw<foo> >::type should be foo"
    );
    static_assert(
        std::is_same<
            boost::parameter::aux::unwrap_cv_reference<
                boost::reference_wrapper<test::foo> const
            >::type
          , test::foo
        >::value
      , "unwrap_cv_reference<rw<foo> const>::type should be foo"
    );
    static_assert(
        std::is_same<
            boost::parameter::aux::unwrap_cv_reference<
                boost::reference_wrapper<test::foo> volatile
            >::type
          , test::foo
        >::value
      , "unwrap_cv_reference<rw<foo> volatile>::type should be foo"
    );
    static_assert(
        std::is_same<
            boost::parameter::aux::unwrap_cv_reference<
                boost::reference_wrapper<test::foo> const volatile
            >::type
          , test::foo
        >::value
      , "unwrap_cv_reference<rw<foo> cv>::type should be foo"
    );
#endif  // BOOST_PARAMETER_CAN_USE_MP11

    BOOST_MPL_ASSERT((
        boost::mpl::if_<
            boost::is_same<
                boost::parameter::aux::unwrap_cv_reference<
                    boost::reference_wrapper<test::foo>
                >::type
              , test::foo
            >
          , boost::mpl::true_
          , boost::mpl::false_
        >::type
    ));
    BOOST_MPL_ASSERT((
        boost::mpl::if_<
            boost::is_same<
                boost::parameter::aux::unwrap_cv_reference<
                    boost::reference_wrapper<test::foo> const
                >::type
              , test::foo
            >
          , boost::mpl::true_
          , boost::mpl::false_
        >::type
    ));
    BOOST_MPL_ASSERT((
        boost::mpl::if_<
            boost::is_same<
                boost::parameter::aux::unwrap_cv_reference<
                    boost::reference_wrapper<test::foo> volatile
                >::type
              , test::foo
            >
          , boost::mpl::true_
          , boost::mpl::false_
        >::type
    ));
    BOOST_MPL_ASSERT((
        boost::mpl::if_<
            boost::is_same<
                boost::parameter::aux::unwrap_cv_reference<
                    boost::reference_wrapper<test::foo> const volatile
                >::type
              , test::foo
            >
          , boost::mpl::true_
          , boost::mpl::false_
        >::type
    ));
}

#if !defined(BOOST_NO_CXX11_HDR_FUNCTIONAL)

#include <functional>

MPL_TEST_CASE()
{
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    static_assert(
        std::is_same<
            boost::parameter::aux::unwrap_cv_reference<
                std::reference_wrapper<test::foo>
            >::type
          , test::foo
        >::value
      , "unwrap_cv_reference<rw<foo> >::type should be foo"
    );
    static_assert(
        std::is_same<
            boost::parameter::aux::unwrap_cv_reference<
                std::reference_wrapper<test::foo> const
            >::type
          , test::foo
        >::value
      , "unwrap_cv_reference<rw<foo> const>::type should be foo"
    );
    static_assert(
        std::is_same<
            boost::parameter::aux::unwrap_cv_reference<
                std::reference_wrapper<test::foo> volatile
            >::type
          , test::foo
        >::value
      , "unwrap_cv_reference<rw<foo> volatile>::type should be foo"
    );
    static_assert(
        std::is_same<
            boost::parameter::aux::unwrap_cv_reference<
                std::reference_wrapper<test::foo> const volatile
            >::type
          , test::foo
        >::value
      , "unwrap_cv_reference<rw<foo> cv>::type should be foo"
    );
#endif  // BOOST_PARAMETER_CAN_USE_MP11

    BOOST_MPL_ASSERT((
        boost::mpl::if_<
            boost::is_same<
                boost::parameter::aux::unwrap_cv_reference<
                    std::reference_wrapper<test::foo>
                >::type
              , test::foo
            >
          , boost::mpl::true_
          , boost::mpl::false_
        >::type
    ));
    BOOST_MPL_ASSERT((
        boost::mpl::if_<
            boost::is_same<
                boost::parameter::aux::unwrap_cv_reference<
                    std::reference_wrapper<test::foo> const
                >::type
              , test::foo
            >
          , boost::mpl::true_
          , boost::mpl::false_
        >::type
    ));
    BOOST_MPL_ASSERT((
        boost::mpl::if_<
            boost::is_same<
                boost::parameter::aux::unwrap_cv_reference<
                    std::reference_wrapper<test::foo> volatile
                >::type
              , test::foo
            >
          , boost::mpl::true_
          , boost::mpl::false_
        >::type
    ));
    BOOST_MPL_ASSERT((
        boost::mpl::if_<
            boost::is_same<
                boost::parameter::aux::unwrap_cv_reference<
                    std::reference_wrapper<test::foo> const volatile
                >::type
              , test::foo
            >
          , boost::mpl::true_
          , boost::mpl::false_
        >::type
    ));
}

#endif  // BOOST_NO_CXX11_HDR_FUNCTIONAL

