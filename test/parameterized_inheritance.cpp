// Copyright Cromwell D. Enage 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/parameter/config.hpp>

#if (BOOST_PARAMETER_MAX_ARITY < 3)
#error Define BOOST_PARAMETER_MAX_ARITY as 3 or greater.
#endif

#include <boost/parameter/name.hpp>

namespace test {

    BOOST_PARAMETER_NAME(a0)
    BOOST_PARAMETER_NAME(a1)
    BOOST_PARAMETER_NAME(a2)

    template <typename T>
    class base0
    {
        T _a0;

     public:
        template <typename ArgPack>
        explicit base0(ArgPack const& args) : _a0(args[test::_a0])
        {
        }

        T const& get_a0() const
        {
            return this->_a0;
        }

     protected:
        template <typename ArgPack>
        void initialize_impl(ArgPack const& args)
        {
            this->_a0 = args[test::_a0];
        }
    };

    template <typename B, typename T>
    class base1 : public B
    {
        T _a1;

     public:
        template <typename ArgPack>
        explicit base1(ArgPack const& args) : B(args), _a1(args[test::_a1])
        {
        }

        T const& get_a1() const
        {
            return this->_a1;
        }

     protected:
        template <typename ArgPack>
        void initialize_impl(ArgPack const& args)
        {
            B::initialize_impl(args);
            this->_a1 = args[test::_a1];
        }
    };

    template <typename B, typename T>
    class base2 : public B
    {
        T _a2;

     public:
        template <typename ArgPack>
        explicit base2(ArgPack const& args) : B(args), _a2(args[test::_a2])
        {
        }

        T const& get_a2() const
        {
            return this->_a2;
        }

     protected:
        template <typename ArgPack>
        void initialize_impl(ArgPack const& args)
        {
            B::initialize_impl(args);
            this->_a2 = args[test::_a2];
        }
    };
}

#include <boost/parameter/preprocessor.hpp>

namespace test {

    template <typename B>
    struct derived : public B
    {
        BOOST_PARAMETER_NO_SPEC_CONSTRUCTOR(derived, (B))

        BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION((void), initialize)
        {
            this->initialize_impl(args);
        }

        BOOST_PARAMETER_NO_SPEC_FUNCTION_CALL_OPERATOR((void))
        {
            this->initialize_impl(args);
        }
    };
} // namespace test

#include <boost/core/lightweight_test.hpp>

int main()
{
    char const* p = "foo";
    char const* q = "bar";
    test::derived<
        test::base2<test::base1<test::base0<char const*>, char>, int>
    > t0(test::_a2 = 4, test::_a1 = ' ', test::_a0 = p);
    test::derived<
        test::base1<test::base2<test::base0<char const*>, int>, char>
    > t1(test::_a0 = p, test::_a1 = ' ', test::_a2 = 4);
    BOOST_TEST_EQ(t0.get_a0(), t1.get_a0());
    BOOST_TEST_EQ(t0.get_a1(), t1.get_a1());
    BOOST_TEST_EQ(t0.get_a2(), t1.get_a2());
    t0.initialize(test::_a0 = q, test::_a1 = '!', test::_a2 = 8);
    t1.initialize(test::_a2 = 8, test::_a1 = '!', test::_a0 = q);
    BOOST_TEST_EQ(t0.get_a0(), t1.get_a0());
    BOOST_TEST_EQ(t0.get_a1(), t1.get_a1());
    BOOST_TEST_EQ(t0.get_a2(), t1.get_a2());
    t0(test::_a2 = 8, test::_a1 = '!', test::_a0 = q);
    t1(test::_a0 = q, test::_a1 = '!', test::_a2 = 8);
    BOOST_TEST_EQ(t0.get_a0(), t1.get_a0());
    BOOST_TEST_EQ(t0.get_a1(), t1.get_a1());
    BOOST_TEST_EQ(t0.get_a2(), t1.get_a2());
    return boost::report_errors();
}

