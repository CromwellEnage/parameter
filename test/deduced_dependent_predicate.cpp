// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/parameter/config.hpp>
#include <boost/parameter/parameters.hpp>
#include <boost/parameter/name.hpp>
#include <boost/parameter/binding.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/if.hpp>
#include "deduced.hpp"

#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_convertible.hpp>
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#include <boost/type_traits/remove_reference.hpp>
#else
#include <boost/type_traits/add_lvalue_reference.hpp>
#endif  // Borland workarounds needed.
#else
#include <type_traits>
#endif  // BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS

namespace test {

    BOOST_PARAMETER_NAME(x)
    BOOST_PARAMETER_NAME(y)
    BOOST_PARAMETER_NAME(z)
} // namespace test

#include <boost/core/lightweight_test.hpp>

int main()
{
    test::check<
        boost::parameter::parameters<
            test::tag::x
          , boost::parameter::optional<
                boost::parameter::deduced<test::tag::y>
              , boost::mpl::if_<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
                    boost::is_same<
#else
                    std::is_same<
#endif
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
                        boost::mpl::_1
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
                      , boost::remove_reference<
#else
                      , std::remove_reference<
#endif
                            boost::parameter::binding<
                                boost::mpl::_2
                              , test::tag::x
                            >
                        >
#else   // !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
                        boost::add_lvalue_reference<boost::mpl::_1>
#else
                        std::add_lvalue_reference<boost::mpl::_1>
#endif
                      , boost::parameter::binding<boost::mpl::_2,test::tag::x>
#endif  // Borland workarounds needed.
                    >
                  , boost::mpl::true_
                  , boost::mpl::false_
                >
            >
        >
    >((test::_x = 0, test::_y = 1), 0, 1);

    test::check<
        boost::parameter::parameters<
            test::tag::x
          , boost::parameter::optional<
                boost::parameter::deduced<test::tag::y>
              , boost::mpl::if_<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
                    boost::is_same<
#else
                    std::is_same<
#endif
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
                        boost::mpl::_1
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
                      , boost::remove_reference<
#else
                      , std::remove_reference<
#endif
                            boost::parameter::binding<
                                boost::mpl::_2
                              , test::tag::x
                            >
                        >
#else   // !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
                        boost::add_lvalue_reference<boost::mpl::_1>
#else
                        std::add_lvalue_reference<boost::mpl::_1>
#endif
                      , boost::parameter::binding<boost::mpl::_2,test::tag::x>
#endif  // Borland workarounds needed.
                    >
                  , boost::mpl::true_
                  , boost::mpl::false_
                >
            >
        >
    >((test::_x = 0U, test::_y = 1U), 0U, 1U);

    test::check<
        boost::parameter::parameters<
            test::tag::x
          , boost::parameter::optional<
                boost::parameter::deduced<test::tag::y>
              , boost::mpl::if_<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
                    boost::is_convertible<boost::mpl::_1,test::tag::x::_>
#else
                    std::is_convertible<boost::mpl::_1,test::tag::x::_>
#endif
                  , boost::mpl::true_
                  , boost::mpl::false_
                >
            >
        >
    >((test::_x = 0U, test::_y = 1U), 0U, 1U);

    test::check<
        boost::parameter::parameters<
            test::tag::x
          , boost::parameter::optional<
                boost::parameter::deduced<test::tag::y>
              , boost::mpl::if_<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
                    boost::is_convertible<boost::mpl::_1,test::tag::x::_1>
#else
                    std::is_convertible<boost::mpl::_1,test::tag::x::_1>
#endif
                  , boost::mpl::true_
                  , boost::mpl::false_
                >
            >
        >
    >((test::_x = 0U, test::_y = 1U), 0U, 1U);

    return boost::report_errors();
}

