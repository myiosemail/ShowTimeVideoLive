/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion
{
    
    template <typename T0>
    struct vector1;
    template <typename T0 , typename T1>
    struct vector2;
    template <typename T0 , typename T1 , typename T2>
    struct vector3;
    template <typename T0 , typename T1 , typename T2 , typename T3>
    struct vector4;
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    struct vector5;
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    struct vector6;
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    struct vector7;
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    struct vector8;
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    struct vector9;
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    struct vector10;
}}
ED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    // expand vector1 to vector10
    #define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/vector10_fwd.hpp>
    #define BOOST_PP_ITERATION_LIMITS (1, 10)
    #include BOOST_PP_ITERATE()
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

#else

    template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename T)>
    struct BOOST_PP_CAT(vector, BOOST_PP_ITERATION());

#endif
