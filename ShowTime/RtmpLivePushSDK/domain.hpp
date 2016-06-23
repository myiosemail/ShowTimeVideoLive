//  Copyright (c) 2001-2011 Joel de Guzman
//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_DOMAIN_MAR_13_2007_0140PM)
#define BOOST_SPIRIT_LEX_DOMAIN_MAR_13_2007_0140PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/meta_compiler.hpp>
#include <boost/spirit/home/support/info.hpp>

namespace boost { namespace spirit { namespace lex
{
    // lex's domain
    struct domain {};

    // bring in some of spirit parts into spirit::lex
    using spirit::unused;
    using spirit::unused_type;
    using spirit::compile;
    using spirit::info;

}}}

#endif
main {};

    // bring in some of spirit parts into spirit::karma
    using spirit::unused;
    using spirit::unused_type;
    using spirit::compile;
    using spirit::info;

    // You can bring these in with the using directive
    // without worrying about bringing in too much.
    namespace labels
    {
        BOOST_PP_REPEAT(SPIRIT_ARGUMENTS_LIMIT, SPIRIT_USING_ARGUMENT, _)
        BOOST_PP_REPEAT(SPIRIT_ATTRIBUTES_LIMIT, SPIRIT_USING_ATTRIBUTE, _)

        using spirit::_pass_type;
        using spirit::_val_type;
        using spirit::_a_type;
        using spirit::_b_type;
        using spirit::_c_type;
        using spirit::_d_type;
        using spirit::_e_type;
        using spirit::_f_type;
        using spirit::_g_type;
        using spirit::_h_type;
        using spirit::_i_type;
        using spirit::_j_type;

#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

        using spirit::_pass;
        using spirit::_val;
        using spirit::_a;
        using spirit::_b;
        using spirit::_c;
        using spirit::_d;
        using spirit::_e;
        using spirit::_f;
        using spirit::_g;
        using spirit::_h;
        using spirit::_i;
        using spirit::_j;

#endif
    }

}}}

#endif
