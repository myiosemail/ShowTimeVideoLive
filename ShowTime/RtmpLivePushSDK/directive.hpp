//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(SPIRIT_REPOSITORY_QI_DIRECTIVE_APR_28_2009_1258PM)
#define SPIRIT_REPOSITORY_QI_DIRECTIVE_APR_28_2009_1258PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/repository/home/qi/directive/distinct.hpp>
#include <boost/spirit/repository/home/qi/directive/confix.hpp>
#include <boost/spirit/repository/home/qi/directive/kwd.hpp>
#include <boost/spirit/repository/home/qi/directive/seek.hpp>

#endif

#include <boost/spirit/home/karma/directive/left_alignment.hpp>
#include <boost/spirit/home/karma/directive/right_alignment.hpp>
#include <boost/spirit/home/karma/directive/center_alignment.hpp>

///////////////////////////////////////////////////////////////////////////////
//  directives related to truncating length
//  maxwidth[...], columns[]
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/karma/directive/maxwidth.hpp>
#include <boost/spirit/home/karma/directive/columns.hpp>

///////////////////////////////////////////////////////////////////////////////
//  directives related to character case
//  lower[...] and upper[...]
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/karma/directive/upper_lower_case.hpp>

///////////////////////////////////////////////////////////////////////////////
//  directives related to delimiting generators 
//  delimit[...] and verbatim[...]
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/karma/directive/verbatim.hpp>
#include <boost/spirit/home/karma/directive/delimit.hpp>
#include <boost/spirit/home/karma/directive/no_delimit.hpp>

///////////////////////////////////////////////////////////////////////////////
//  repeat directives
//  repeat[...]
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/karma/directive/repeat.hpp>

///////////////////////////////////////////////////////////////////////////////
//  omit, skip, and duplicate directives
//  omit[...], skip[...], duplicate[...]
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/karma/directive/omit.hpp>
#include <boost/spirit/home/karma/directive/duplicate.hpp>

///////////////////////////////////////////////////////////////////////////////
//  buffer directive
//  buffer[...]
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/karma/directive/buffer.hpp>

///////////////////////////////////////////////////////////////////////////////
//  strict and relaxed directives
//  strict[...], relaxed[...]
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/karma/directive/strict_relaxed.hpp>

///////////////////////////////////////////////////////////////////////////////
//  as_string and as_wstring directives
//  as_string[...], as_wstring[...]
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/karma/directive/as.hpp>

#endif
