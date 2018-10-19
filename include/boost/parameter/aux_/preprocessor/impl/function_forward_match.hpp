// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_FORWARD_MATCH_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_FORWARD_MATCH_HPP

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if !defined(BOOST_NO_SFINAE) && \
    !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x592))

#define BOOST_PARAMETER_FUNCTION_FORWARD_MATCH(name, params, n, prefix)      \
    typename ::boost::parameter::aux::match<                                 \
        params, BOOST_PP_ENUM_PARAMS(n, prefix)                              \
    >::type = params()
/**/

#define BOOST_PARAMETER_FUNCTION_FORWARD_MATCH_Z(z, name, params, n, prefix) \
    typename ::boost::parameter::aux::match<                                 \
        params, BOOST_PP_ENUM_PARAMS_Z(z, n, prefix)                         \
    >::type = params()
/**/

#else   // SFINAE/Borland workarounds needed.

#define BOOST_PARAMETER_FUNCTION_FORWARD_MATCH(name, params, n, prefix)      \
    params = params()
/**/

#define BOOST_PARAMETER_FUNCTION_FORWARD_MATCH_Z(z, name, params, n, prefix) \
    params = params()
/**/

#endif


#if !defined(BOOST_NO_SFINAE) && \
    !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x592))

#include <boost/parameter/aux_/pp_impl/match.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

// Expands to an extra argument that is well-formed
// iff all Args... satisfy the requirements set by params.
#define BOOST_PARAMETER_FUNCTION_FWD_MATCH_Z(z, name, parameters, n) \
    , typename ::boost::parameter::aux::match< \
          parameters, BOOST_PP_ENUM_PARAMS(n, ParameterArgumentType) \
      >::type = parameters()
/**/

#else

#define BOOST_PARAMETER_FUNCTION_FWD_MATCH_Z(z, name, parameters, n)
/**/

#endif
#endif  // include guard

