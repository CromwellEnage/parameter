// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/parameter/name.hpp>

BOOST_PARAMETER_NAME(x)

#include <boost/parameter/parameters.hpp>
#include <boost/parameter/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/if.hpp>

#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
#include <boost/type_traits/is_convertible.hpp>
#else
#include <type_traits>
#endif

int main()
{
    boost::parameter::parameters<
        boost::parameter::optional<
            boost::parameter::deduced<tag::x>
          , boost::mpl::if_<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
                boost::is_convertible<boost::mpl::_,int>
#else
                std::is_convertible<boost::mpl::_,int>
#endif
              , boost::mpl::true_
              , boost::mpl::false_
            >
        >
    >()("foo");

    return 0;
}

