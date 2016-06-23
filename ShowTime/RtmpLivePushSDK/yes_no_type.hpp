
//  (C) Copyright John Maddock and Steve Cleary 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.
//
//  macros and helpers for working with integral-constant-expressions.

#ifndef BOOST_TT_DETAIL_YES_NO_TYPE_HPP_INCLUDED
#define BOOST_TT_DETAIL_YES_NO_TYPE_HPP_INCLUDED

namespace boost {
namespace type_traits {

typedef char yes_type;
struct no_type
{
   char padding[8];
};

} // namespace type_traits
} // namespace boost

#endif // BOOST_TT_DETAIL_YES_NO_TYPE_HPP_INCLUDED
escriptor 
        {
            typedef char (& type)[I];
        }; 

        typedef size_descriptor<1>::type yes_type;
        typedef size_descriptor<2>::type no_type;

    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_YES_NO_TYPE_DETAIL_HPP
