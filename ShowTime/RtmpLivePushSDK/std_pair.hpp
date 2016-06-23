/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INCLUDE_STD_PAIR)
#define FUSION_INCLUDE_STD_PAIR

#include <boost/fusion/adapted/std_pair.hpp>

#endif
IR_HPP
#define BOOST_FUSION_ADAPTED_STD_PAIR_HPP

#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <utility>

BOOST_FUSION_ADAPT_TPL_STRUCT(
    (T1)(T2),(std::pair)(T1)(T2),(T1, first)(T2, second))

#endif
