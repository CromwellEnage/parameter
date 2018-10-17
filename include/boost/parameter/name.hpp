// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_NAME_060806_HPP
#define BOOST_PARAMETER_NAME_060806_HPP

#include <boost/parameter/aux_/name.hpp>
#include <boost/preprocessor/stringize.hpp>

#define BOOST_PARAMETER_NAME_TAG(tag_namespace, tag, q)                      \
    namespace tag_namespace                                                  \
    {                                                                        \
        struct tag                                                           \
        {                                                                    \
            static char const* keyword_name()                                \
            {                                                                \
                return BOOST_PP_STRINGIZE(tag);                              \
            }                                                                \
            typedef BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(tag) _;             \
            typedef BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(tag) _1;            \
            typedef ::boost::parameter::q qualifier;                         \
        };                                                                   \
    }
/**/

#include <boost/parameter/keyword.hpp>

#define BOOST_PARAMETER_NAME_KEYWORD(tag_namespace, tag, name)               \
    namespace                                                                \
    {                                                                        \
        ::boost::parameter::keyword<tag_namespace::tag> const& name          \
            = ::boost::parameter::keyword<tag_namespace::tag>::instance;     \
    }
/**/

#define BOOST_PARAMETER_BASIC_NAME(tag_namespace, tag, qualifier, name)      \
    BOOST_PARAMETER_NAME_TAG(tag_namespace, tag, qualifier)                  \
    BOOST_PARAMETER_NAME_KEYWORD(tag_namespace, tag, name)
/**/

#define BOOST_PARAMETER_COMPLEX_NAME_TUPLE1(object, namespace)               \
    (object, namespace), ~
/**/

#include <boost/preprocessor/tuple/elem.hpp>

#define BOOST_PARAMETER_COMPLEX_NAME_TUPLE(name)                             \
    BOOST_PP_TUPLE_ELEM(2, 0, (BOOST_PARAMETER_COMPLEX_NAME_TUPLE1 name))
/**/

#define BOOST_PARAMETER_COMPLEX_NAME_OBJECT(name)                            \
    BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PARAMETER_COMPLEX_NAME_TUPLE(name))
/**/

#define BOOST_PARAMETER_COMPLEX_NAME_NAMESPACE(name)                         \
    BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PARAMETER_COMPLEX_NAME_TUPLE(name))
/**/

#include <boost/preprocessor/tuple/eat.hpp>

#define BOOST_PARAMETER_COMPLEX_NAME(name)                                   \
    BOOST_PARAMETER_BASIC_NAME(                                              \
        BOOST_PARAMETER_COMPLEX_NAME_NAMESPACE(name)                         \
      , BOOST_PARAMETER_UNQUALIFIED_NAME(BOOST_PP_TUPLE_EAT(2) name)         \
      , BOOST_PARAMETER_GET_NAME_QUALIFIER(BOOST_PP_TUPLE_EAT(2) name)       \
      , BOOST_PARAMETER_COMPLEX_NAME_OBJECT(name)                            \
    )
/**/

#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_SIMPLE_NAME(name)                                    \
    BOOST_PARAMETER_BASIC_NAME(                                              \
        tag                                                                  \
      , BOOST_PARAMETER_UNQUALIFIED_NAME(name)                               \
      , BOOST_PARAMETER_GET_NAME_QUALIFIER(name)                             \
      , BOOST_PP_CAT(_, BOOST_PARAMETER_UNQUALIFIED_NAME(name))              \
    )
/**/

#include <boost/parameter/aux_/preprocessor/is_binary.hpp>
#include <boost/preprocessor/control/iif.hpp>

#define BOOST_PARAMETER_NAME(name)                                           \
    BOOST_PP_IIF(                                                            \
        BOOST_PARAMETER_IS_BINARY(name)                                      \
      , BOOST_PARAMETER_COMPLEX_NAME                                         \
      , BOOST_PARAMETER_SIMPLE_NAME                                          \
    )(name)
/**/

#include <boost/parameter/aux_/template_keyword.hpp>

#define BOOST_PARAMETER_TEMPLATE_KEYWORD(name)                               \
    namespace tag                                                            \
    {                                                                        \
        struct name;                                                         \
    }                                                                        \
    template <typename T>                                                    \
    struct name : ::boost::parameter::template_keyword<tag::name,T>          \
    {                                                                        \
    };
/**/

#endif  // include guard

