// Copyright Eric Niebler 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_NESTED_KEYWORD_HPP
#define BOOST_PARAMETER_NESTED_KEYWORD_HPP

#include <boost/parameter/aux_/name.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#define BOOST_PARAMETER_NESTED_KEYWORD_AUX(tag_namespace, q, name, alias)    \
    namespace tag_namespace                                                  \
    {                                                                        \
        template <int Dummy = 0>                                             \
        struct BOOST_PP_CAT(name, _)                                         \
        {                                                                    \
            static char const* keyword_name()                                \
            {                                                                \
                return BOOST_PP_STRINGIZE(tag);                              \
            }                                                                \
            typedef BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(                    \
                BOOST_PP_CAT(name, _)<Dummy>                                 \
            ) _;                                                             \
            typedef BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(                    \
                BOOST_PP_CAT(name, _)<Dummy>                                 \
            ) _1;                                                            \
            typedef ::boost::parameter::q qualifier;                         \
        };                                                                   \
        namespace                                                            \
        {                                                                    \
            template <int Dummy>                                             \
            ::boost::parameter::keyword<                                     \
                BOOST_PP_CAT(name, _)<Dummy>                                 \
            > const& BOOST_PP_CAT(name, _)<Dummy>::alias                     \
                = ::boost::parameter::keyword<                               \
                    BOOST_PP_CAT(name, _)<Dummy>                             \
                >::instance;                                                 \
        }                                                                    \
        typedef BOOST_PP_CAT(name, _)<> name;                                \
    }                                                                        \
    namespace                                                                \
    {                                                                        \
        ::boost::parameter::keyword<tag_namespace::name> const& name         \
            = ::boost::parameter::keyword<tag_namespace::name>::instance;    \
    }
/**/

#define BOOST_PARAMETER_NESTED_KEYWORD(tag_namespace, name, alias)           \
    BOOST_PARAMETER_NESTED_KEYWORD_AUX(                                      \
        tag_namespace                                                        \
      , BOOST_PARAMETER_GET_NAME_QUALIFIER(name)                             \
      , BOOST_PARAMETER_UNQUALIFIED_NAME(name)                               \
      , alias                                                                \
    )
/**/

#endif // BOOST_PARAMETER_NESTED_KEYWORD_HPP

