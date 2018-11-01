// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef ARG_LIST_050329_HPP
#define ARG_LIST_050329_HPP

namespace boost { namespace parameter { namespace aux {

    //
    // Structures used to build the tuple of actual arguments.  The tuple is a
    // nested cons-style list of arg_list specializations terminated by an
    // empty_arg_list.
    //
    // Each specialization of arg_list is derived from its successor in the
    // list type.  This feature is used along with using declarations to build
    // member function overload sets that can match against keywords.
    //

    // MPL sequence support
    struct arg_list_tag;

    template <typename T>
    struct get_reference
    {
        typedef typename T::reference type;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux {

    struct value_type_is_void
    {
    };

    struct value_type_is_not_void
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/yesno.hpp>
#include <boost/parameter/aux_/result_of0.hpp>
#include <boost/parameter/aux_/default.hpp>
#include <utility>

namespace boost { namespace parameter { namespace aux {

    // Terminates arg_list<> and represents an empty list.  Since this is just
    // the terminating case, you might want to look at arg_list first to get a
    // feel for what's really happening here.
    struct empty_arg_list
    {
        struct tagged_arg
        {
            typedef ::boost::parameter::void_ value_type;
        };

        // Variadic constructor also serves as default constructor.
        template <typename ...Args>
        inline empty_arg_list(Args&&...)
        {
        }

        // A metafunction class that, given a keyword and a default type,
        // returns the appropriate result type for a keyword lookup given
        // that default.
        struct binding
        {
            template <typename KW, typename Default, typename Reference>
            struct apply
            {
                typedef Default type;
            };
        };

        // Terminator for has_key, indicating that the keyword is unique.
        template <typename KW>
        static ::boost::parameter::aux::no_tag has_key(KW*);

        // If either of these operators are called, it means there is no
        // argument in the list that matches the supplied keyword.  Just
        // return the default value.
        template <typename K, typename Default>
        inline Default&
            operator[](::boost::parameter::aux::default_<K,Default> x) const
        {
            return x.value;
        }

        template <typename K, typename Default>
        inline Default&&
            operator[](::boost::parameter::aux::default_r_<K,Default> x) const
        {
            return ::std::forward<Default>(x.value);
        }

        // If this operator is called, it means there is no argument in the
        // list that matches the supplied keyword.  Just evaluate and return
        // the default value.
        template <typename K, typename F>
        inline typename ::boost::parameter::aux::result_of0<F>::type
            operator[](BOOST_PARAMETER_lazy_default_fallback<K,F> x) const
        {
            return x.compute_default();
        }

        // No argument corresponding to ParameterRequirements::key_type
        // was found if we match this overload, so unless that parameter
        // has a default, we indicate that the actual arguments don't
        // match the function's requirements.
        template <typename ParameterRequirements, typename ArgPack>
        static typename ParameterRequirements::has_default
            satisfies(ParameterRequirements*, ArgPack*);

        // MPL sequence support
        typedef ::boost::parameter::aux::empty_arg_list type; // convenience
        // For dispatching to sequence intrinsics
        typedef ::boost::parameter::aux::arg_list_tag tag;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/yesno.hpp>
#include <boost/parameter/aux_/is_maybe.hpp>
#include <boost/parameter/aux_/tagged_argument_fwd.hpp>
#include <boost/parameter/aux_/parameter_requirements.hpp>
#include <boost/parameter/aux_/augment_predicate.hpp>
#include <boost/parameter/keyword_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/tti/detail/dnullptr.hpp>

namespace boost { namespace parameter { namespace aux {

    // A tuple of tagged arguments, terminated with empty_arg_list.  Every
    // TaggedArg is an instance of tagged_argument<> or
    // tagged_argument_rref<>.
    template <
        typename TaggedArg
      , typename Next = ::boost::parameter::aux::empty_arg_list
    >
    struct arg_list : Next
    {
        typedef TaggedArg tagged_arg;
        typedef ::boost::parameter::aux::arg_list<TaggedArg,Next> self;
        typedef typename TaggedArg::key_type key_type;

        typedef typename ::boost::parameter::aux
        ::is_maybe<typename TaggedArg::value_type>::type holds_maybe;

        typedef typename ::boost::mpl::eval_if<
            holds_maybe
          , ::boost::parameter::aux
            ::get_reference<typename TaggedArg::value_type>
          , ::boost::parameter::aux::get_reference<TaggedArg>
        >::type reference;

        typedef typename ::boost::mpl::if_<
            holds_maybe
          , reference
          , typename TaggedArg::value_type
        >::type value_type;

        TaggedArg arg;      // Stores the argument

        // Create a new list by prepending arg to a copy of tail.  Used when
        // incrementally building this structure with the comma operator.
        inline arg_list(TaggedArg const& head, Next const& tail)
          : Next(tail), arg(head)
        {
        }

        // Store the arguments in successive nodes of this list.
        // Use tag dispatching to determine whether to forward all arguments
        // to the Next constructor, or store the first argument and forward
        // the rest. -- Cromwell D. Enage
        template <typename A0>
        inline arg_list(
            ::boost::parameter::aux::value_type_is_not_void
          , A0&& a0
        ) : Next(
                typename ::boost::mpl::if_<
                    ::boost::is_same<
                        typename Next::tagged_arg::value_type
                      , ::boost::parameter::void_
                    >
                  , ::boost::parameter::aux::value_type_is_void
                  , ::boost::parameter::aux::value_type_is_not_void
                >::type()
            )
          , arg(::std::forward<A0>(a0))
        {
        }

        template <typename ...Args>
        inline arg_list(
            ::boost::parameter::aux::value_type_is_void
          , Args&&... args
        ) : Next(
                typename ::boost::mpl::if_<
                    ::boost::is_same<
                        typename Next::tagged_arg::value_type
                      , ::boost::parameter::void_
                    >
                  , ::boost::parameter::aux::value_type_is_void
                  , ::boost::parameter::aux::value_type_is_not_void
                >::type()
              , ::std::forward<Args>(args)...
            )
          , arg(::boost::parameter::aux::void_reference())
        {
        }

        template <typename A0, typename A1, typename ...Args>
        inline arg_list(
            ::boost::parameter::aux::value_type_is_not_void
          , A0&& a0
          , A1&& a1
          , Args&&... args
        ) : Next(
                typename ::boost::mpl::if_<
                    ::boost::is_same<
                        typename Next::tagged_arg::value_type
                      , ::boost::parameter::void_
                    >
                  , ::boost::parameter::aux::value_type_is_void
                  , ::boost::parameter::aux::value_type_is_not_void
                >::type()
              , ::std::forward<A1>(a1)
              , ::std::forward<Args>(args)...
            )
          , arg(::std::forward<A0>(a0))
        {
        }

        // A metafunction class that, given a keyword and a default type,
        // returns the appropriate result type for a keyword lookup given
        // that default.
        struct binding
        {
            typedef typename Next::binding next_binding;

            template <typename KW, typename Default, typename Reference>
            struct apply
            {
                typedef typename ::boost::mpl::eval_if<
                    ::boost::is_same<KW,key_type>
                  , ::boost::mpl::if_<Reference,reference,value_type>
                  , ::boost::mpl::apply_wrap3<
                        next_binding
                      , KW
                      , Default
                      , Reference
                    >
                >::type type;
            };
        };

        // Overload for key_type, so the assert below will fire
        // if the same keyword is used again.
        static ::boost::parameter::aux::yes_tag has_key(key_type*);
        using Next::has_key;

        BOOST_MPL_ASSERT_MSG(
            sizeof(
                Next::has_key(
                    static_cast<key_type*>(BOOST_TTI_DETAIL_NULLPTR)
                )
            ) == sizeof(::boost::parameter::aux::no_tag)
          , duplicate_keyword
          , (key_type)
        );

        //
        // Begin implementation of indexing operators
        // for looking up specific arguments by name.
        //

        // Helpers that handle the case when TaggedArg is empty<T>.
        template <typename D>
        inline reference get_default(D const&, ::boost::mpl::false_) const
        {
            return this->arg.get_value();
        }

        template <typename D>
        inline reference get_default(D const& d, ::boost::mpl::true_) const
        {
            return (
                this->arg.get_value()
              ? this->arg.get_value().get()
              : this->arg.get_value().construct(d.value)
            );
        }

        inline reference
            operator[](::boost::parameter::keyword<key_type> const&) const
        {
            BOOST_MPL_ASSERT_NOT((holds_maybe));
            return this->arg.get_value();
        }

        template <typename Default>
        inline reference
            operator[](
                ::boost::parameter::aux::default_<key_type,Default> const& d
            ) const
        {
            return this->get_default(d, holds_maybe());
        }

        template <typename Default>
        inline reference
            operator[](
                ::boost::parameter::aux::default_r_<key_type,Default> const& d
            ) const
        {
            return this->get_default(d, holds_maybe());
        }

        template <typename Default>
        inline reference
            operator[](
                BOOST_PARAMETER_lazy_default_fallback<key_type,Default> const&
            ) const
        {
            BOOST_MPL_ASSERT_NOT((holds_maybe));
            return this->arg.get_value();
        }

        // Builds an overload set including operator[]s defined
        // in base classes.
        using Next::operator[];

        //
        // End of indexing support
        //

        // For parameter_requirements matching this node's key_type, return
        // a bool constant wrapper indicating whether the requirements are
        // satisfied by TaggedArg.  Used only for compile-time computation
        // and never really called, so a declaration is enough.
        template <typename HasDefault, typename Predicate, typename ArgPack>
        static typename ::boost::mpl::apply_wrap2<
            ::boost::parameter::aux
            ::augment_predicate<Predicate,reference,key_type>
          , value_type
          , ArgPack
        >::type
            satisfies(
                ::boost::parameter::aux::parameter_requirements<
                    key_type
                  , Predicate
                  , HasDefault
                >*
              , ArgPack*
            );

        // Builds an overload set including satisfies functions defined
        // in base classes.
        using Next::satisfies;

        // Comma operator to compose argument list without using parameters<>.
        // Useful for argument lists with undetermined length.
        template <typename KW, typename T2>
        inline ::boost::parameter::aux::arg_list<
            ::boost::parameter::aux::tagged_argument<KW,T2>
          , self
        >
            operator,(
                ::boost::parameter::aux::tagged_argument<KW,T2> const& x
            ) const
        {
            return ::boost::parameter::aux::arg_list<
                ::boost::parameter::aux::tagged_argument<KW,T2>
              , self
            >(x, *this);
        }

        template <typename KW, typename T2>
        inline ::boost::parameter::aux::arg_list<
            ::boost::parameter::aux::tagged_argument_rref<KW,T2>
          , self
        >
            operator,(
                ::boost::parameter::aux::tagged_argument_rref<KW,T2> const& x
            ) const
        {
            return ::boost::parameter::aux::arg_list<
                ::boost::parameter::aux::tagged_argument_rref<KW,T2>
              , self
            >(x, *this);
        }

        // MPL sequence support
        typedef self type;        // Convenience for users
        typedef Next tail_type;   // For the benefit of iterators
        // For dispatching to sequence intrinsics
        typedef ::boost::parameter::aux::arg_list_tag tag;
    };
}}} // namespace boost::parameter::aux

#else
#include <boost/parameter/aux_/cpp03/arg_list.hpp>
#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING

#include <boost/mpl/iterator_tags.hpp>

namespace boost { namespace parameter { namespace aux {

    // MPL sequence support
    template <typename ArgumentPack>
    struct arg_list_iterator
    {
        typedef ::boost::mpl::forward_iterator_tag category;

        // The incremented iterator
        typedef ::boost::parameter::aux
        ::arg_list_iterator<typename ArgumentPack::tail_type> next;

        // dereferencing yields the key type
        typedef typename ArgumentPack::key_type type;
    };

    template <>
    struct arg_list_iterator< ::boost::parameter::aux::empty_arg_list>
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/begin.hpp>

// MPL sequence support
namespace boost { namespace mpl {

    template <>
    struct begin_impl< ::boost::parameter::aux::arg_list_tag>
    {
        template <typename S>
        struct apply
        {
            typedef ::boost::parameter::aux::arg_list_iterator<S> type;
        };
    };
}} // namespace boost::mpl

#include <boost/mpl/end.hpp>

namespace boost { namespace mpl {

    template <>
    struct end_impl< ::boost::parameter::aux::arg_list_tag>
    {
        template <typename>
        struct apply
        {
            typedef ::boost::parameter::aux::arg_list_iterator<
                ::boost::parameter::aux::empty_arg_list
            > type;
        };
    };
}} // namespace boost::mpl

#endif  // include guard

