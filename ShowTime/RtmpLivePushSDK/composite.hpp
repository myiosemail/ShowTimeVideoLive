/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#ifndef PHOENIX_CORE_DETAIL_COMPOSITE_HPP
#define PHOENIX_CORE_DETAIL_COMPOSITE_HPP

#include <boost/preprocessor/iterate.hpp>

#define BOOST_PP_ITERATION_PARAMS_1                                             \
    (3, (3, PHOENIX_COMPOSITE_LIMIT,                                            \
    "boost/spirit/home/phoenix/core/detail/composite.hpp"))
#include BOOST_PP_ITERATE()

#endif

///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#else // defined(BOOST_PP_IS_ITERATING)

#define N BOOST_PP_ITERATION()

    template <BOOST_PP_ENUM_PARAMS(N, typename U)>
    composite(BOOST_PP_ENUM_BINARY_PARAMS(N, U, & _))
        : base_type(BOOST_PP_ENUM_PARAMS(N, _)) {}

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


ruct composite : EvalTuple
    {
        typedef EvalTuple base_type;
        typedef composite<EvalPolicy, EvalTuple> self_type;
        typedef EvalPolicy eval_policy_type;
        
        typedef typename
            mpl::fold<
                EvalTuple
              , mpl::false_
              , detail::compute_no_nullary
            >::type
        no_nullary;

        template <typename Env>
        struct result
        {
            typedef
                typename detail::composite_eval<
                    fusion::result_of::size<base_type>::value>::
                template result<self_type, Env>::type
            type;
        };

        composite()
            : base_type() {}

        composite(base_type const& base)
            : base_type(base) {}

        template <typename U0>
        composite(U0& _0)
            : base_type(_0) {}

        template <typename U0, typename U1>
        composite(U0& _0, U1& _1)
            : base_type(_0, _1) {}

        template <typename Env>
        typename result<Env>::type
        eval(Env const& env) const
        {
            typedef typename result<Env>::type return_type;
            return detail::
                composite_eval<fusion::result_of::size<base_type>::value>::template
                    call<return_type>(*this, env);
        }

        //  Bring in the rest of the constructors
        #include <boost/spirit/home/phoenix/core/detail/composite.hpp>
    };

    //  Bring in the detail::composite_eval<0..N> definitions
    #include <boost/spirit/home/phoenix/core/detail/composite_eval.hpp>
}}

#endif
