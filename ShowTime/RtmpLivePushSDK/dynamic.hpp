/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2004 Daniel Wallin

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef PHOENIX_SCOPE_DYNAMIC_HPP
#define PHOENIX_SCOPE_DYNAMIC_HPP

#include <boost/spirit/home/phoenix/core/limits.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/spirit/home/phoenix/core/actor.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/inc.hpp>

#include <boost/noncopyable.hpp>
#include <boost/assert.hpp>

#define PHOENIX_DYNAMIC_MEMBER(z, n, data)                                      \
    typedef actor<dynamic_member<n, self_type> >                                \
        BOOST_PP_CAT(member, BOOST_PP_INC(n));

namespace boost { namespace phoenix
{
    template <typename DynamicScope>
    struct dynamic_frame : noncopyable
    {
        typedef typename DynamicScope::tuple_type tuple_type;

        dynamic_frame(DynamicScope const& scope)
            : tuple()
            , save(scope.frame)
            , scope(scope)
        {
            scope.frame = this;
        }

        template <typename Tuple>
        dynamic_frame(DynamicScope const& scope, Tuple const& init)
            : tuple(init)
            , save(scope.frame)
            , scope(scope)
        {
            scope.frame = this;
        }

        ~dynamic_frame()
        {
            scope.frame = save;
        }

        tuple_type& data() { return tuple; }
        tuple_type const& data() const { return tuple; }

    private:

        tuple_type tuple;
        dynamic_frame* save;
        DynamicScope const& scope;
    };

    template <int N, typename DynamicScope>
    struct dynamic_member
    {
        typedef mpl::false_ no_nullary;
        typedef typename DynamicScope::tuple_type tuple_type;

        dynamic_member(DynamicScope const& scope)
            : scope(scope) {}

        template <typename Env>
        struct result
        {
            typedef typename
                fusion::result_of::at_c<tuple_type, N>::type
            type;
        };

        template <typename Env>
        typename result<Env>::type
        eval(Env const& /*env*/) const
        {
            BOOST_ASSERT(scope.frame != 0);
            return fusion::at_c<N>(scope.frame->data());
        }

    private:

        DynamicScope const& scope;
    };

    template <BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PHOENIX_DYNAMIC_LIMIT, typename T, void_)>
    struct dynamic : noncopyable
    {
        typedef fusion::vector<BOOST_PP_ENUM_PARAMS(PHOENIX_DYNAMIC_LIMIT, T)> tuple_type;
        typedef dynamic<BOOST_PP_ENUM_PARAMS(PHOENIX_DYNAMIC_LIMIT, T)> self_type;
        typedef dynamic_frame<self_type> dynamic_frame_type;

        dynamic()
            : frame(0) {}

        BOOST_PP_REPEAT(PHOENIX_DYNAMIC_LIMIT, PHOENIX_DYNAMIC_MEMBER, _)

    private:

        template <int N, typename DynamicScope>
        friend struct dynamic_member;

        template <typename DynamicScope>
        friend struct dynamic_frame;

        mutable dynamic_frame_type* frame;
    };
}}

#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable:4355)
#endif

/*
    PHOENIX_DYNAMIC macro(name, type-name sequence)
    Example:

    PHOENIX_DYNAMIC(
        my_dynamic,
            (int, num)
            (std::string, message)
            (double, real)
    );

    which expands to:

    struct my_dynamic : ::boost::phoenix::dynamic<int, std::string, double>
    {
        my_dynamic() : num(*this), message(*this), real(*this) {}

        member1 num;
        member2 message;
        member3 real;
    };

    PHOENIX_DYNAMIC takes the input (containing a binary sequence)
    and converts that sequence to a unary sequence of
    binary tuples and passes it on to PHOENIX_DYNAMIC_I.

    Thanks to Paul Mensonides for the PP macro help
*/

#define PHOENIX_DYNAMIC(name, bseq)                                             \
    PHOENIX_DYNAMIC_I(name, BOOST_PP_CAT(PHOENIX_DYNAMIC_X bseq, 0))            \

#define PHOENIX_DYNAMIC_X(x, y) ((x, y)) PHOENIX_DYNAMIC_Y
#define PHOENIX_DYNAMIC_Y(x, y) ((x, y)) PHOENIX_DYNAMIC_X
#define PHOENIX_DYNAMIC_X0
#define PHOENIX_DYNAMIC_Y0

// PHOENIX_DYNAMIC_I generates the overarching structure and uses
// SEQ_FOR_EACH_I to generate the "linear" substructures.

#define PHOENIX_DYNAMIC_I(name, seq)                                            \
    struct name :                                                               \
        ::boost::phoenix::dynamic<                                              \
            BOOST_PP_SEQ_FOR_EACH_I(PHOENIX_DYNAMIC_A, ~, seq)> {               \
        name() : BOOST_PP_SEQ_FOR_EACH_I(PHOENIX_DYNAMIC_B, ~, seq) {}          \
        BOOST_PP_SEQ_FOR_EACH_I(PHOENIX_DYNAMIC_C, ~, seq)                      \
    }                                                                           \

#define PHOENIX_DYNAMIC_A(r, _, i, xy)                                          \
    BOOST_PP_COMMA_IF(i) BOOST_PP_TUPLE_ELEM(2, 0, xy)                          \

#define PHOENIX_DYNAMIC_B(r, _, i, xy)                                          \
    BOOST_PP_COMMA_IF(i) BOOST_PP_TUPLE_ELEM(2, 1, xy)(*this)                   \

#define PHOENIX_DYNAMIC_C(r, _, i, xy)                                          \
    BOOST_PP_CAT(member, BOOST_PP_INC(i)) BOOST_PP_TUPLE_ELEM(2, 1, xy);        \

#undef PHOENIX_DYNAMIC_MEMBER

#if defined(BOOST_MSVC)
# pragma warning(pop)
#endif

#endif
ek(xpression_peeker<Char> &peeker) const
    {
        peeker.accept(*static_cast<Matcher const *>(this));
    }
};

//////////////////////////////////////////////////////////////////////////
// make_simple_repeat
template<typename BidiIter, typename Xpr>
inline void
make_simple_repeat(quant_spec const &spec, sequence<BidiIter> &seq, Xpr const &xpr)
{
    if(spec.greedy_)
    {
        simple_repeat_matcher<Xpr, mpl::true_> quant(xpr, spec.min_, spec.max_, seq.width().value());
        seq = make_dynamic<BidiIter>(quant);
    }
    else
    {
        simple_repeat_matcher<Xpr, mpl::false_> quant(xpr, spec.min_, spec.max_, seq.width().value());
        seq = make_dynamic<BidiIter>(quant);
    }
}

//////////////////////////////////////////////////////////////////////////
// make_simple_repeat
template<typename BidiIter>
inline void
make_simple_repeat(quant_spec const &spec, sequence<BidiIter> &seq)
{
    seq += make_dynamic<BidiIter>(true_matcher());
    make_simple_repeat(spec, seq, seq.xpr());
}

//////////////////////////////////////////////////////////////////////////
// make_optional
template<typename BidiIter>
inline void
make_optional(quant_spec const &spec, sequence<BidiIter> &seq)
{
    typedef shared_matchable<BidiIter> xpr_type;
    seq += make_dynamic<BidiIter>(alternate_end_matcher());
    if(spec.greedy_)
    {
        optional_matcher<xpr_type, mpl::true_> opt(seq.xpr());
        seq = make_dynamic<BidiIter>(opt);
    }
    else
    {
        optional_matcher<xpr_type, mpl::false_> opt(seq.xpr());
        seq = make_dynamic<BidiIter>(opt);
    }
}

//////////////////////////////////////////////////////////////////////////
// make_optional
template<typename BidiIter>
inline void
make_optional(quant_spec const &spec, sequence<BidiIter> &seq, int mark_nbr)
{
    typedef shared_matchable<BidiIter> xpr_type;
    seq += make_dynamic<BidiIter>(alternate_end_matcher());
    if(spec.greedy_)
    {
        optional_mark_matcher<xpr_type, mpl::true_> opt(seq.xpr(), mark_nbr);
        seq = make_dynamic<BidiIter>(opt);
    }
    else
    {
        optional_mark_matcher<xpr_type, mpl::false_> opt(seq.xpr(), mark_nbr);
        seq = make_dynamic<BidiIter>(opt);
    }
}

//////////////////////////////////////////////////////////////////////////
// make_repeat
template<typename BidiIter>
inline void
make_repeat(quant_spec const &spec, sequence<BidiIter> &seq)
{
    // only bother creating a repeater if max is greater than one
    if(1 < spec.max_)
    {
        // create a hidden mark so this expression can be quantified
        int mark_nbr = -static_cast<int>(++*spec.hidden_mark_count_);
        seq = make_dynamic<BidiIter>(mark_begin_matcher(mark_nbr)) + seq
            + make_dynamic<BidiIter>(mark_end_matcher(mark_nbr));
        make_repeat(spec, seq, mark_nbr);
        return;
    }

    // if min is 0, the repeat must be made optional
    if(0 == spec.min_)
    {
        make_optional(spec, seq);
    }
}

//////////////////////////////////////////////////////////////////////////
// make_repeat
template<typename BidiIter>
inline void
make_repeat(quant_spec const &spec, sequence<BidiIter> &seq, int mark_nbr)
{
    BOOST_ASSERT(spec.max_); // we should never get here if max is 0

    // only bother creating a repeater if max is greater than one
    if(1 < spec.max_)
    {
        // TODO: statically bind the repeat matchers to the mark matchers for better perf
        unsigned int min = spec.min_ ? spec.min_ : 1U;
        repeat_begin_matcher repeat_begin(mark_nbr);
        if(spec.greedy_)
        {
            repeat_end_matcher<mpl::true_> repeat_end(mark_nbr, min, spec.max_);
            seq = make_dynamic<BidiIter>(repeat_begin) + seq
                + make_dynamic<BidiIter>(repeat_end);
        }
        else
        {
            repeat_end_matcher<mpl::false_> repeat_end(mark_nbr, min, spec.max_);
            seq = make_dynamic<BidiIter>(repeat_begin) + seq
                + make_dynamic<BidiIter>(repeat_end);
        }
    }

    // if min is 0, the repeat must be made optional
    if(0 == spec.min_)
    {
        make_optional(spec, seq, mark_nbr);
    }
}

}}} // namespace boost::xpressive::detail

#endif
