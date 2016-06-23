/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#ifndef PHOENIX_CORE_DETAIL_BASIC_ENVIRONMENT_HPP
#define PHOENIX_CORE_DETAIL_BASIC_ENVIRONMENT_HPP

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define BOOST_PP_ITERATION_PARAMS_1                                             \
    (3, (3, PHOENIX_ARG_LIMIT,                                                  \
    "boost/spirit/home/phoenix/core/detail/basic_environment.hpp"))
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
    basic_environment(BOOST_PP_ENUM_BINARY_PARAMS(N, U, & _))
        : args_(BOOST_PP_ENUM_PARAMS(N, _)) {}

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


       // tie_type: a fusion::tuple of references
        typedef typename
            fusion::result_of::as_vector<
                typename mpl::transform<
                    args_type, boost::add_reference<mpl::_1> 
                >::type
            >::type
        tie_type;

        basic_environment()
            : args_() {}

        template <typename U0>
        explicit basic_environment(U0& _0)
            : args_(_0) {}

        template <typename U0, typename U1>
        basic_environment(U0& _0, U1& _1)
            : args_(_0, _1) {}

        //  Bring in the rest of the constructors
        #include <boost/spirit/home/phoenix/core/detail/basic_environment.hpp>

        tie_type const& 
        args() const
        {
            return args_;
        }

        tie_type& 
        args()
        {
            return args_;
        }

    private:

        tie_type args_;
    };
}}

#endif

