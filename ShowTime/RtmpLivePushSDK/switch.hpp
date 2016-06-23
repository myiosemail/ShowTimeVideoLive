/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef PHOENIX_STATEMENT_SWITCH_HPP
#define PHOENIX_STATEMENT_SWITCH_HPP

#include <boost/spirit/home/phoenix/core/composite.hpp>
#include <boost/spirit/home/phoenix/core/compose.hpp>
#include <boost/spirit/home/phoenix/core/nothing.hpp>
#include <boost/spirit/home/phoenix/statement/detail/switch_eval.hpp>
#include <boost/spirit/home/phoenix/statement/detail/switch.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace phoenix
{
    template <typename Derived, typename Actor>
    struct switch_case_base 
    {
        typedef Derived derived_t;
        typedef Actor actor_t;
        typedef typename Actor::no_nullary no_nullary;

        template <typename Env>
        struct result
        {
            typedef typename Actor::eval_type::template result<Env>::type type;
        };

        switch_case_base(Actor const& actor)
            : actor(actor) {}

        template <typename Env>
        typename result<Env>::type
        eval(Env const& env) const
        {
            return actor.eval(env);
        }

        Actor actor;
    };

    template <typename Actor, typename K, K Value>
    struct switch_case : switch_case_base<switch_case<Actor, K, Value>, Actor>
    {
        typedef switch_case_base<switch_case<Actor, K, Value>, Actor> base_t;
        static K const value = Value;
        static bool const is_default = false;

        switch_case(Actor const& actor)
            : base_t(actor) {}
    };

    template <typename Actor>
    struct default_case : switch_case_base<default_case<Actor>, Actor>
    {
        typedef switch_case_base<default_case<Actor>, Actor> base_t;
        static bool const is_default = true;

        default_case(Actor const& actor)
            : base_t(actor) {}
    };

    template <typename Cond>
    struct switch_gen
    {
        switch_gen(Cond const& cond)
            : cond(cond) {}

        template <typename Cases>
        typename lazy_enable_if<
            fusion::traits::is_sequence<Cases>
          , detail::switch_composite_actor<Cond, Cases>
        >::type
        operator[](Cases const& cases) const
        {
            typedef typename
                detail::switch_composite<Cond, Cases>
            switch_composite;
            return switch_composite::eval(cond, cases);
        }

        template <typename D, typename A>
        actor<typename detail::
            switch_composite<Cond, fusion::vector<actor<D> > >::type>
        operator[](switch_case_base<D, A> const& case_) const
        {
            typedef typename
                detail::switch_composite<Cond, fusion::vector<actor<D> > >
            switch_composite;
            return switch_composite::eval(cond,
                fusion::vector<actor<D> >(static_cast<D const&>(case_)));
        }

        Cond cond;
    };

    template <typename Cond>
    inline switch_gen<typename as_actor<Cond>::type>
    switch_(Cond const& cond)
    {
        return switch_gen<typename as_actor<Cond>::type>(
            as_actor<Cond>::convert(cond));
    }

    template <int N, typename A0>
    switch_case<typename as_actor<A0>::type, int, N>
    case_(A0 const& _0)
    {
        return switch_case<typename as_actor<A0>::type, int, N>
            (as_actor<A0>::convert(_0));
    }

    template <typename A0>
    default_case<typename as_actor<A0>::type>
    default_(A0 const& _0)
    {
        return default_case<typename as_actor<A0>::type>
            (as_actor<A0>::convert(_0));
    }

    template <typename D0, typename A0, typename D1, typename A1>
    inline typename detail::compose_case_a<D0, D1>::type
    operator,(
        switch_case_base<D0, A0> const& _0
      , switch_case_base<D1, A1> const& _1
    )
    {
        return detail::compose_case_a<D0, D1>::eval(
            static_cast<D0 const&>(_0)
          , static_cast<D1 const&>(_1)
        );
    }

    template <typename Seq, typename D, typename A>
    inline typename
        lazy_enable_if<
            fusion::traits::is_sequence<Seq>
          , detail::compose_case_b<Seq, D>
        >::type
    operator,(Seq const& seq, switch_case_base<D, A> const& case_)
    {
        return detail::compose_case_b<Seq, D>::eval(
            seq, static_cast<D const&>(case_));
    }

    // Implementation of routines in detail/switch.hpp that depend on
    // the completeness of default_case.
    namespace detail {
        template <typename Cases>
        typename ensure_default<Cases>::type
        ensure_default<Cases>::eval(Cases const& cases, mpl::false_)
        {
            actor<default_case<actor<null_actor> > > default_
              = default_case<actor<null_actor> >(nothing);
            return fusion::push_front(cases, default_);
        }
    }
}}

#endif
pedef unary<ParserT, parser<self_t> >     base_t;

    typedef typename base_t::subject_t          self_subject_t;

    BOOST_STATIC_CONSTANT(int, value = N);
    BOOST_STATIC_CONSTANT(bool, is_default = IsDefault);
    BOOST_STATIC_CONSTANT(bool, is_simple = true);
    BOOST_STATIC_CONSTANT(bool, is_epsilon = (
        is_default && boost::is_same<self_subject_t, epsilon_parser>::value
    ));

    case_parser(parser<ParserT> const &p)
    :   base_t(p.derived())
    {}

    template <typename ScannerT>
    struct result
    {
        typedef typename match_result<ScannerT, nil_t>::type type;
    };

    template <typename ScannerT, typename CondT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scan, CondT const &cond) const
    {
        typedef impl::default_case<self_t> default_t;

        if (!scan.at_end()) {
            typedef impl::default_delegate_parse<
                value, is_default, default_t::value> default_parse_t;

            typename ScannerT::iterator_t const save(scan.first);
            return default_parse_t::parse(cond(scan), *this,
                *this, scan, save);
        }

        return default_t::is_epsilon ? scan.empty_match() : scan.no_match();
    }

    template <int N1, typename ParserT1, bool IsDefault1>
    impl::compound_case_parser<
        self_t, case_parser<N1, ParserT1, IsDefault1>, IsDefault1
    >
    operator, (case_parser<N1, ParserT1, IsDefault1> const &p) const
    {
        //  If the following compile time assertion fires, you've probably used
        //  more than one default_p case inside the switch_p parser construct.
        BOOST_STATIC_ASSERT(!is_default || !IsDefault1);

        typedef case_parser<N1, ParserT1, IsDefault1> right_t;
        return impl::compound_case_parser<self_t, right_t, IsDefault1>(*this, p);
    }
};

///////////////////////////////////////////////////////////////////////////////
struct switch_parser_gen {

//  This generates a switch parser, which is driven by the condition value
//  returned by the lazy parameter expression 'cond'. This may be a parser,
//  which result is used or a phoenix actor, which will be dereferenced to
//  obtain the switch condition value.
    template <typename CondT>
    switch_cond_parser<CondT>
    operator()(CondT const &cond) const
    {
        return switch_cond_parser<CondT>(cond);
    }

//  This generates a switch parser, which is driven by the next character/token
//  found in the input stream.
    template <typename CaseT>
    switch_parser<CaseT>
    operator[](parser<CaseT> const &p) const
    {
        return switch_parser<CaseT>(p.derived());
    }
};

switch_parser_gen const switch_p = switch_parser_gen();

///////////////////////////////////////////////////////////////////////////////
template <int N, typename ParserT>
inline case_parser<N, ParserT, false>
case_p(parser<ParserT> const &p)
{
    return case_parser<N, ParserT, false>(p);
}

///////////////////////////////////////////////////////////////////////////////
struct default_parser_gen
:   public case_parser<BOOST_SPIRIT_DEFAULTCASE_MAGIC, epsilon_parser, true>
{
    default_parser_gen()
    :   case_parser<BOOST_SPIRIT_DEFAULTCASE_MAGIC, epsilon_parser, true>
            (epsilon_p)
    {}

    template <typename ParserT>
    case_parser<BOOST_SPIRIT_DEFAULTCASE_MAGIC, ParserT, true>
    operator()(parser<ParserT> const &p) const
    {
        return case_parser<BOOST_SPIRIT_DEFAULTCASE_MAGIC, ParserT, true>(p);
    }
};

default_parser_gen const default_p = default_parser_gen();

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}  // namespace BOOST_SPIRIT_CLASSIC_NS

#endif // BOOST_SPIRIT_SWITCH_HPP
