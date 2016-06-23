/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef PHOENIX_BIND_BIND_MEMBER_FUNCTION_HPP
#define PHOENIX_BIND_BIND_MEMBER_FUNCTION_HPP

#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/core/compose.hpp>
#include <boost/spirit/home/phoenix/core/detail/function_eval.hpp>
#include <boost/spirit/home/phoenix/bind/detail/member_function_ptr.hpp>

namespace boost { namespace phoenix
{
    template <typename RT, typename ClassT, typename ClassA>
    inline actor<
        typename as_composite<
            detail::function_eval<1>
          , detail::member_function_ptr<0, RT, RT(ClassT::*)()>
          , ClassA
        >::type>
    bind(RT(ClassT::*f)(), ClassA const& obj)
    {
        typedef detail::member_function_ptr<0, RT, RT(ClassT::*)()> fp_type;
        return compose<detail::function_eval<1> >(fp_type(f), obj);
    }

    template <typename RT, typename ClassT, typename ClassA>
    inline actor<
        typename as_composite<
            detail::function_eval<1>
          , detail::member_function_ptr<0, RT, RT(ClassT::*)() const>
          , ClassA
        >::type>
    bind(RT(ClassT::*f)() const, ClassA const& obj)
    {
        typedef detail::member_function_ptr<0, RT, RT(ClassT::*)() const> fp_type;
        return compose<detail::function_eval<1> >(fp_type(f), obj);
    }

    template <typename RT, typename ClassT>
    inline actor<
        typename as_composite<
            detail::function_eval<1>
          , detail::member_function_ptr<0, RT, RT(ClassT::*)()>
          , actor<reference<ClassT> >
        >::type>
    bind(RT(ClassT::*f)(), ClassT& obj)
    {
        typedef detail::member_function_ptr<0, RT, RT(ClassT::*)()> fp_type;
        return compose<detail::function_eval<1> >(
            fp_type(f)
          , actor<reference<ClassT> >(reference<ClassT>(obj)));
    }

    template <typename RT, typename ClassT>
    inline actor<
        typename as_composite<
            detail::function_eval<1>
          , detail::member_function_ptr<0, RT, RT(ClassT::*)() const>
          , actor<reference<ClassT> >
        >::type>
    bind(RT(ClassT::*f)() const, ClassT& obj)
    {
        typedef detail::member_function_ptr<0, RT, RT(ClassT::*)() const> fp_type;
        return compose<detail::function_eval<1> >(
            fp_type(f)
          , actor<reference<ClassT> >(reference<ClassT>(obj)));
    }

    //  Bring in the rest of the function binders
    #include <boost/spirit/home/phoenix/bind/detail/bind_member_function.hpp>
}}

#endif
n compose<detail::function_eval<BOOST_PP_INC(N)> >(
            fp_type(f), obj, BOOST_PP_ENUM_PARAMS(N, _));
    }

    template <typename RT
      , typename ClassT
      , BOOST_PP_ENUM_PARAMS(N, typename T)
      , BOOST_PP_ENUM_PARAMS(N, typename A)>
    inline actor<
        typename as_composite<
            detail::function_eval<BOOST_PP_INC(N)>
          , detail::member_function_ptr<N,
                RT, RT(ClassT::*)(BOOST_PP_ENUM_PARAMS(N, T))>
          , actor<reference<ClassT> >
          , BOOST_PP_ENUM_PARAMS(N, A)
        >::type>
    bind(
        RT(ClassT::*f)(BOOST_PP_ENUM_PARAMS(N, T))
      , ClassT& obj
      , BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& _))
    {
        typedef detail::member_function_ptr<
            N, RT, RT(ClassT::*)(BOOST_PP_ENUM_PARAMS(N, T))> fp_type;
        return compose<detail::function_eval<BOOST_PP_INC(N)> >(
            fp_type(f)
          , actor<reference<ClassT> >(reference<ClassT>(obj))
          , BOOST_PP_ENUM_PARAMS(N, _));
    }

    template <typename RT
      , typename ClassT
      , BOOST_PP_ENUM_PARAMS(N, typename T)
      , BOOST_PP_ENUM_PARAMS(N, typename A)>
    inline actor<
        typename as_composite<
            detail::function_eval<BOOST_PP_INC(N)>
          , detail::member_function_ptr<N,
                RT, RT(ClassT::*)(BOOST_PP_ENUM_PARAMS(N, T)) const>
          , actor<reference<ClassT> >
          , BOOST_PP_ENUM_PARAMS(N, A)
        >::type>
    bind(
        RT(ClassT::*f)(BOOST_PP_ENUM_PARAMS(N, T)) const
      , ClassT& obj
      , BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& _))
    {
        typedef detail::member_function_ptr<
            N, RT, RT(ClassT::*)(BOOST_PP_ENUM_PARAMS(N, T)) const> fp_type;
        return compose<detail::function_eval<BOOST_PP_INC(N)> >(
            fp_type(f)
          , actor<reference<ClassT> >(reference<ClassT>(obj))
          , BOOST_PP_ENUM_PARAMS(N, _));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


