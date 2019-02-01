// Copyright Cromwell D. Enage 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_ENABLE_IF_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_ENABLE_IF_HPP

#define BOOST_PARAMETER_AUX_PP_ENABLE_IF_EAT_(x) x
#define BOOST_PARAMETER_AUX_PP_ENABLE_IF_EAT_enable_if(x)
#define BOOST_PARAMETER_AUX_PP_ENABLE_IF_EAT_enable_if_c(x)
#define BOOST_PARAMETER_AUX_PP_ENABLE_IF_EAT_lazy_enable_if(x)
#define BOOST_PARAMETER_AUX_PP_ENABLE_IF_EAT_lazy_enable_if_c(x)
#define BOOST_PARAMETER_AUX_PP_ENABLE_IF_EAT_disable_if(x)
#define BOOST_PARAMETER_AUX_PP_ENABLE_IF_EAT_disable_if_c(x)
#define BOOST_PARAMETER_AUX_PP_ENABLE_IF_EAT_lazy_disable_if(x)
#define BOOST_PARAMETER_AUX_PP_ENABLE_IF_EAT_lazy_disable_if_c(x)

#define BOOST_PARAMETER_AUX_PP_GET_ENABLE_IF_enable_if(x) enable_if
#define BOOST_PARAMETER_AUX_PP_GET_ENABLE_IF_enable_if_c(x) enable_if_c
#define BOOST_PARAMETER_AUX_PP_GET_ENABLE_IF_lazy_enable_if(x) lazy_enable_if
#define BOOST_PARAMETER_AUX_PP_GET_ENABLE_IF_lazy_enable_if_c(x) \
    lazy_enable_if_c
#define BOOST_PARAMETER_AUX_PP_GET_ENABLE_IF_disable_if(x) disable_if
#define BOOST_PARAMETER_AUX_PP_GET_ENABLE_IF_disable_if_c(x) disable_if_c
#define BOOST_PARAMETER_AUX_PP_GET_ENABLE_IF_lazy_disable_if(x) lazy_disable_if
#define BOOST_PARAMETER_AUX_PP_GET_ENABLE_IF_lazy_disable_if_c(x) \
    lazy_disable_if_c

#define BOOST_PARAMETER_AUX_PP_STRIP_ENABLE_IF_enable_if(x) x
#define BOOST_PARAMETER_AUX_PP_STRIP_ENABLE_IF_enable_if_c(x) x
#define BOOST_PARAMETER_AUX_PP_STRIP_ENABLE_IF_lazy_enable_if(x) x
#define BOOST_PARAMETER_AUX_PP_STRIP_ENABLE_IF_lazy_enable_if_c(x) x
#define BOOST_PARAMETER_AUX_PP_STRIP_ENABLE_IF_disable_if(x) x
#define BOOST_PARAMETER_AUX_PP_STRIP_ENABLE_IF_disable_if_c(x) x
#define BOOST_PARAMETER_AUX_PP_STRIP_ENABLE_IF_lazy_disable_if(x) x
#define BOOST_PARAMETER_AUX_PP_STRIP_ENABLE_IF_lazy_disable_if_c(x) x

#include <boost/preprocessor/cat.hpp>

// Expands to the filter of x.
//
//   enable_if(k) => enable_if
//   enable_if_c(k) => enable_if_c
//   lazy_enable_if(k) => lazy_enable_if
//   lazy_enable_if_c(k) => lazy_enable_if_c
//   disable_if(k) => disable_if
//   disable_if_c(k) => disable_if_c
//   lazy_disable_if(k) => lazy_disable_if
//   lazy_disable_if_c(k) => lazy_disable_if_c
#define BOOST_PARAMETER_AUX_PP_GET_ENABLE_IF_FILTER(x) \
    BOOST_PP_CAT(BOOST_PARAMETER_AUX_PP_GET_ENABLE_IF_, x)
/**/

#define BOOST_PARAMETER_AUX_PP_GET_ENABLE_IF_CLAUSE(x) \
    BOOST_PP_CAT(BOOST_PARAMETER_AUX_PP_STRIP_ENABLE_IF_, x)
/**/

#include <boost/preprocessor/facilities/is_empty.hpp>

// Expands to 1 if x is either "enable_if(k)", "enable_if_c(k)",
// "lazy_enable_if(k)", "lazy_enable_if_c(k)", "disable_if(k)",
// "disable_if_c(k)", "lazy_disable_if(k)", or "lazy_disable_if_c(k)";
// expands to 0 otherwise.
#define BOOST_PARAMETER_AUX_PP_IS_ENABLE_IF_FILTER(x) \
    BOOST_PP_IS_EMPTY(BOOST_PP_CAT(BOOST_PARAMETER_AUX_PP_ENABLE_IF_EAT_, x))
/**/

#include <boost/preprocessor/control/iif.hpp>

// Expands to the unfiltered version of x.
//
//   enable_if(k) => k
//   enable_if_c(k) => k
//   lazy_enable_if(k) => k
//   lazy_enable_if_c(k) => k
//   disable_if(k) => k
//   disable_if_c(k) => k
//   lazy_disable_if(k) => k
//   lazy_disable_if_c(k) => k
#define BOOST_PARAMETER_AUX_PP_ENABLE_IF_CLAUSE(x) \
    BOOST_PP_IIF( \
        BOOST_PARAMETER_AUX_PP_IS_ENABLE_IF_FILTER(x) \
      , BOOST_PARAMETER_AUX_PP_GET_ENABLE_IF_CLAUSE(x) \
      , x \
    )
/**/

#endif  // include guard

