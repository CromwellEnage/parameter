// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_DEDUCED_HPP
#define BOOST_PARAMETER_DEDUCED_HPP

#include <boost/parameter/aux_/use_default.hpp>

namespace boost { namespace parameter {

    // This metafunction can be used to describe the treatment of particular
    // named parameters for the purposes of overload elimination with SFINAE,
    // by placing specializations in the parameters<...> list.
    //
    // If a keyword k is specified with deduced<...>, that keyword
    // will be automatically deduced from the argument list.
    template <typename Tag>
    struct deduced
    {
        typedef Tag key_type;
    };
}}

#include <boost/mpl/bool.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_deduced_aux : ::boost::mpl::false_
    {
    };

    template <typename Tag>
    struct is_deduced_aux< ::boost::parameter::deduced<Tag> >
      : ::boost::mpl::true_
    {
    };

    template <typename T>
    struct is_deduced0
      : ::boost::parameter::aux::is_deduced_aux<typename T::key_type>::type
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/required.hpp>
#include <boost/parameter/optional.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace parameter { namespace aux {

    //
    // tag_type, has_default, and predicate --
    //
    // These metafunctions accept a ParameterSpec and extract the
    // keyword tag, whether or not a default is supplied for the
    // parameter, and the predicate that the corresponding actual
    // argument type is required match.
    //
    // a ParameterSpec is a specialization of either keyword<...>,
    // required<...>, optional<...>
    //

    template <typename T>
    struct has_default
      : ::boost::mpl::if_<
            ::boost::parameter::aux::is_required<T>
          , ::boost::mpl::false_
          , ::boost::mpl::true_
        >::type
    {
    };

    template <typename T>
    struct is_deduced
      : ::boost::mpl::if_<
            typename ::boost::mpl::if_<
                ::boost::parameter::aux::is_optional<T>
              , ::boost::mpl::true_
              , ::boost::parameter::aux::is_required<T>
            >::type
          , ::boost::parameter::aux::is_deduced0<T>
          , ::boost::mpl::false_
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_deduced_aux_mp11 : ::boost::mp11::mp_false
    {
    };

    template <typename Tag>
    struct is_deduced_aux_mp11< ::boost::parameter::deduced<Tag> >
      : ::boost::mp11::mp_true
    {
    };

    template <typename T>
    using is_deduced1 = typename ::boost::parameter::aux
    ::is_deduced_aux_mp11<typename T::key_type>::type;

    template <typename T>
    using is_deduced_mp11 = ::boost::mp11::mp_if<
        ::boost::mp11::mp_if<
            ::boost::parameter::aux::is_optional_mp11<T>
          , ::boost::mp11::mp_true
          , ::boost::parameter::aux::is_required_mp11<T>
        >
      , ::boost::parameter::aux::is_deduced1<T>
      , ::boost::mp11::mp_false
    >;
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard

