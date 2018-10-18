// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_CAST_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_CAST_HPP

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))

#define BOOST_PARAMETER_FUNCTION_CAST_T(value_t, predicate, args) value_t
#define BOOST_PARAMETER_FUNCTION_CAST_B(value, predicate, args) value

#else   // !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))

namespace boost { namespace parameter { namespace aux {

    // Handles possible implicit casts.  Used by preprocessor.hpp
    // to normalize user input.
    //
    // cast<void*>::execute() is identity
    // cast<void*(X)>::execute() is identity
    // cast<void(X)>::execute() casts to X
    //
    // preprocessor.hpp uses this like this:
    //
    //     #define X(value, predicate)
    //         cast<void predicate>::execute(value)
    //
    //     X(something, *)
    //     X(something, *(predicate))
    //     X(something, (int))
    template <typename VoidExpr, typename Args>
    struct cast;
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Args>
    struct cast<void*,Args>
    {
        template <typename T>
        struct apply
        {
            typedef T& type;
        };

        inline static ::boost::parameter::aux::use_default_tag
            execute(::boost::parameter::aux::use_default_tag)
        {
            return ::boost::parameter::aux::use_default_tag();
        }

        template <typename U>
        inline static U& execute(U& value)
        {
            return value;
        }
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/void.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Predicate, typename Args>
#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
    struct cast< ::boost::parameter::aux::voidstar(Predicate),Args>
#else
    struct cast<void*(Predicate),Args>
#endif
      : ::boost::parameter::aux::cast<void*,Args>
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/placeholders.hpp>

namespace boost { namespace parameter { namespace aux {

    // This is a hack used in cast<> to turn the user supplied type,
    // which may or may not be a placeholder expression, into one,
    // so that it will be properly evaluated by mpl::apply.
    template <typename T, typename Dummy = ::boost::mpl::_1>
    struct as_placeholder_expr
    {
        typedef T type;
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/apply.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Target, typename Source, typename Args>
    struct is_target_same_as_source
      : ::boost::mpl::if_<
            ::boost::is_same<
                typename ::boost::remove_const<
                    typename ::boost::remove_reference<
                        typename ::boost::mpl::apply2<
                            ::boost::parameter::aux
                            ::as_placeholder_expr<Target>
                          , Source
                          , Args
                        >::type
                    >::type
                >::type
              , typename ::boost::remove_const<Source>::type
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

    template <
        typename Target
      , typename Source
      , typename Args
      , typename Enable = ::boost::parameter::aux
        ::is_target_same_as_source<Target,Source,Args>
    >
    struct cast_impl
    {
        typedef Source& type;

        inline static Source& evaluate(Source& value)
        {
            return value;
        }
    };
}}} // namespace boost::parameter::aux

#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // Covers the case where is_convertible<Source,Target> but not
    // is_same<Source,Target>.  Use cases are covered
    // by test/normalize_argument_types.cpp
    template <typename Source, typename Target>
    class cast_convert
    {
        typedef ::boost::parameter::aux::cast_convert<Source,Target> _self;

     public:
        typedef typename ::boost::add_lvalue_reference<
            typename ::boost::add_const<Target>::type
        >::type type;

        inline static typename _self::type evaluate(Source& source)
        {
            return _self::_mod_const(_self::_copy(source));
        }
    };

    template <typename Target, typename Source, typename Args>
    struct cast_impl<Target,Source,Args,::boost::mpl::false_>
      : ::boost::parameter::aux::cast_convert<
            Source,
            typename ::boost::mpl::apply2<
                ::boost::parameter::aux::as_placeholder_expr<Target>
              , Source
              , Args
            >::type
        >
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/eval_if.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Target, typename Args>
    struct cast<void(Target),Args>
    {
        template <typename T>
        struct apply
        {
            typedef typename ::boost::mpl::eval_if<
                    ::boost::parameter::aux
                    ::is_target_same_as_source<Target,T,Args>
                  , ::boost::add_lvalue_reference<T>
                  , ::boost::parameter::aux::cast_impl<
                        Target
                      , T
                      , Args
                      , ::boost::mpl::false_
                    >
            >::type type;
        };

        inline static ::boost::parameter::aux::use_default_tag
            execute(::boost::parameter::aux::use_default_tag)
        {
            return ::boost::parameter::aux::use_default_tag();
        }

        template <typename U>
        inline static typename ::boost::parameter::aux
        ::cast_impl<Target,U const,Args>::type
            execute(U const& value)
        {
            return ::boost::parameter::aux
            ::cast_impl<Target,U const,Args>::evaluate(value);
        }

        template <typename U>
        inline static typename ::boost::parameter::aux
        ::cast_impl<Target,U,Args>::type
            execute(U& value)
        {
            return ::boost::parameter::aux
            ::cast_impl<Target,U,Args>::evaluate(value);
        }
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/apply_wrap.hpp>
#include <boost/parameter/value_type.hpp>

// Expands to the reference-qualified target type of the argument
// as indicated by the predicate.
#define BOOST_PARAMETER_FUNCTION_CAST_T(tag, predicate, args)                \
    typename ::boost::mpl::apply_wrap1<                                      \
        ::boost::parameter::aux::cast<void predicate, args>                  \
      , typename ::boost::parameter::value_type<                             \
            args                                                             \
          , tag                                                              \
          , ::boost::parameter::aux::use_default_tag                         \
        >::type                                                              \
    >::type
/**/

// Expands to the converted or passed-through value
// as indicated by the predicate.
#define BOOST_PARAMETER_FUNCTION_CAST_B(value, predicate, args)              \
    ::boost::parameter::aux::cast<void predicate, args>::execute(value)
/**/

#endif  // Borland workarounds needed.
#endif  // include guard

