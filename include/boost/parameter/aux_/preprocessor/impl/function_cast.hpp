// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_CAST_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_CAST_HPP

#include <boost/parameter/config.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))

#define BOOST_PARAMETER_FUNCTION_CAST_T(value_t, predicate, args) value_t

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#include <boost/mpl/bool.hpp>

#define BOOST_PARAMETER_FUNCTION_CAST_B(value_t, predicate, args) \
    ::boost::mpl::true_

#include <boost/move/utility_core.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T, typename B>
    inline T&& forward(T&& t)
    {
        return ::boost::forward<T>(t);
    }
}}} // namespace boost::parameter::aux

#else

#define BOOST_PARAMETER_FUNCTION_CAST_B(value, predicate, args) value

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING

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

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
namespace boost { namespace parameter { namespace aux {

    template <typename T, typename B>
    inline ::boost::parameter::aux::use_default_tag
        forward(::boost::parameter::aux::use_default_tag)
    {
        return ::boost::parameter::aux::use_default_tag();
    }
}}} // namespace boost::parameter::aux
#endif

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#include <boost/move/utility_core.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename Args>
    struct cast<void*,Args>
    {
#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
        template <typename T, typename B>
        struct apply
        {
            typedef typename ::boost::mpl
            ::if_<B,T,::boost::mpl::true_>::type type;
        };
#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
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
#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
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

#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#else
#include <type_traits>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename Target, typename Source, typename Args>
    struct is_target_same_as_source
      : ::boost::mpl::if_<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
            ::boost::is_same<
                typename ::boost::remove_const<
                    typename ::boost::remove_reference<
#else
            ::std::is_same<
                typename ::std::remove_const<
                    typename ::std::remove_reference<
#endif
                        typename ::boost::mpl::apply2<
                            ::boost::parameter::aux
                            ::as_placeholder_expr<Target>
                          , Source
                          , Args
                        >::type
                    >::type
                >::type
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
              , typename ::boost::remove_const<Source>::type
#else
              , typename ::std::remove_const<Source>::type
#endif
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

#if !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
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
#endif // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
}}} // namespace boost::parameter::aux

#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
#include <boost/type_traits/add_const.hpp>
#if !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#include <boost/type_traits/add_lvalue_reference.hpp>
#endif
#endif

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS) || ( \
        BOOST_WORKAROUND(BOOST_MSVC, >= 1700) && \
        BOOST_WORKAROUND(BOOST_MSVC, < 1800) \
    )
#include <boost/type_traits/is_const.hpp>
#endif
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
#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
        typedef typename boost::mpl::eval_if<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS) || ( \
        BOOST_WORKAROUND(BOOST_MSVC, >= 1700) && \
        BOOST_WORKAROUND(BOOST_MSVC, < 1800) \
    )
            // MSVC 11.0 on AppVeyor reports error C2039:
            // '_Is_const': is not a member of 'std::_Ptr_traits<_Ty>'
            ::boost::is_const<Source>
#else
            ::std::is_const<Source>
#endif
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
          , ::boost::add_const<Target>
          , ::boost::remove_const<Target>
#else
          , ::std::add_const<Target>
          , ::std::remove_const<Target>
#endif
#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
        typedef typename ::boost::add_lvalue_reference<
            typename ::boost::add_const<Target>::type
#else
        typedef typename ::std::add_lvalue_reference<
            typename ::std::add_const<Target>::type
#endif
#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
        >::type type;

     private:
#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
        inline static typename _self::type
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
            _copy(typename ::boost::remove_const<Target>::type value)
#else
            _copy(typename ::std::remove_const<Target>::type value)
#endif
        {
            return value;
        }
#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
        template <typename U>
        inline static typename _self::type _mod_const(U const& u)
        {
            return u;
        }

        inline static Target _copy(Target value)
        {
            return value;
        }
#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING

     public:
#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
        inline static typename _self::type evaluate(Source&& source)
        {
            return _self::_copy(source);
        }
#else
        inline static typename _self::type evaluate(Source& source)
        {
            return _self::_mod_const(_self::_copy(source));
        }
#endif
    };

    template <typename Target, typename Source, typename Args>
#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
    struct cast_impl
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
      : ::boost::remove_reference<
#else
      : ::std::remove_reference<
#endif
#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
    struct cast_impl<Target,Source,Args,::boost::mpl::false_>
      : ::boost::parameter::aux::cast_convert<
            Source,
#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
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

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#include <boost/mpl/identity.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename Target, typename Args>
    struct cast<void(Target),Args>
    {
#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
        template <typename T, typename B>
#else
        template <typename T>
#endif
        struct apply
        {
            typedef typename ::boost::mpl::eval_if<
#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
                B
              , ::boost::mpl::eval_if<
#endif
                    ::boost::parameter::aux
                    ::is_target_same_as_source<Target,T,Args>
#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
                  , ::boost::mpl::identity<T>
#elif defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
                  , ::boost::add_lvalue_reference<T>
#else
                  , ::std::add_lvalue_reference<T>
#endif
                  , ::boost::parameter::aux::cast_impl<
                        Target
                      , T
                      , Args
#if !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
                      , ::boost::mpl::false_
#endif
                    >
#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
                >
              , ::boost::parameter::aux
                ::is_target_same_as_source<Target,T,Args>
#endif
            >::type type;
        };

#if !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
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
#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/apply_wrap.hpp>
#include <boost/parameter/value_type.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

// Expands to the target type of the argument as indicated by the predicate.
#define BOOST_PARAMETER_FUNCTION_CAST_T(tag, predicate, args)                \
    typename ::boost::mpl::apply_wrap2<                                      \
        ::boost::parameter::aux::cast<void predicate, args>                  \
      , typename ::boost::parameter::value_type<                             \
            args                                                             \
          , tag                                                              \
          , ::boost::parameter::aux::use_default_tag                         \
        >::type                                                              \
      , ::boost::mpl::true_                                                  \
    >::type
/**/

// Expands to boost::mpl::true_ if and only if the argument's source and
// target types are the same.
#define BOOST_PARAMETER_FUNCTION_CAST_B(tag, predicate, args)                \
    typename ::boost::mpl::apply_wrap2<                                      \
        ::boost::parameter::aux::cast<void predicate, args>                  \
      , typename ::boost::parameter::value_type<                             \
            args                                                             \
          , tag                                                              \
          , ::boost::parameter::aux::use_default_tag                         \
        >::type                                                              \
      , ::boost::mpl::false_                                                 \
    >::type
/**/

#include <boost/core/enable_if.hpp>

namespace boost { namespace parameter { namespace aux {

    // If the source and target types are not the same,
    // then perform an implicit conversion.
    template <typename Target, typename B, typename Source>
    inline typename ::boost::lazy_disable_if<
        B
      , ::boost::parameter::aux::cast_convert<Source,Target>
    >::type
        forward(Source&& source)
    {
        return ::boost::parameter::aux::cast_convert<Source,Target>
        ::evaluate(::boost::forward<Source>(source));
    }

    // If the source and target types are the same,
    // then simply forward the argument.
    // However, treat rvalue references to scalars as const lvalue references.
    template <typename T, typename B>
    inline typename ::boost::enable_if<B,T const&>::type forward(T const& t)
    {
        return t;
    }

    template <typename T, typename B>
    inline typename ::boost::enable_if<
        typename ::boost::mpl::eval_if<
            B
          , ::boost::mpl::if_<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS) || ( \
        BOOST_WORKAROUND(BOOST_MSVC, >= 1700) && \
        BOOST_WORKAROUND(BOOST_MSVC, < 1800) \
    )
                // MSVC 11.0 on AppVeyor reports error C2039:
                // '_Is_const': is not a member of 'std::_Ptr_traits<_Ty>'
                ::boost::is_const<T>
#else
                ::std::is_const<T>
#endif
              , ::boost::mpl::false_
              , ::boost::mpl::true_
            >
          , ::boost::mpl::false_
        >::type
      , T&
    >::type
        forward(T& t)
    {
        return t;
    }
}}} // namespace boost::parameter::aux

#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
#include <boost/type_traits/is_scalar.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T, typename B>
    inline typename ::boost::enable_if<
        typename ::boost::mpl::eval_if<
            B
          , ::boost::mpl::if_<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
                ::boost::is_scalar<T>
#else
                ::std::is_scalar<T>
#endif
              , ::boost::mpl::false_
              , ::boost::mpl::true_
            >
          , ::boost::mpl::false_
        >::type
      , T const&&
    >::type
        forward(T const&& t)
    {
        return static_cast<T const&&>(t);
    }

    template <typename T, typename B>
    inline typename ::boost::enable_if<
        typename ::boost::mpl::eval_if<
            B
          , ::boost::mpl::if_<
#if defined(BOOST_PARAMETER_USES_BOOST_VICE_CXX11_TYPE_TRAITS)
                ::boost::is_scalar<T>
#else
                ::std::is_scalar<T>
#endif
              , ::boost::mpl::false_
              , ::boost::mpl::true_
            >
          , ::boost::mpl::false_
        >::type
      , T&&
    >::type
        forward(T&& t)
    {
        return ::boost::forward<T>(t);
    }
}}} // namespace boost::parameter::aux

#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

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

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif  // Borland workarounds needed.
#endif  // include guard
