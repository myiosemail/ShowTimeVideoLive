
#ifndef BOOST_MPL_MAP_MAP0_HPP_INCLUDED
#define BOOST_MPL_MAP_MAP0_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: map0.hpp 49267 2008-10-11 06:19:02Z agurtovoy $
// $Date: 2008-10-10 23:19:02 -0700 (Fri, 10 Oct 2008) $
// $Revision: 49267 $

#include <boost/mpl/map/aux_/contains_impl.hpp>
#include <boost/mpl/map/aux_/at_impl.hpp>
//#include <boost/mpl/map/aux_/O1_size.hpp>
#include <boost/mpl/map/aux_/insert_impl.hpp>
#include <boost/mpl/map/aux_/erase_impl.hpp>
#include <boost/mpl/map/aux_/erase_key_impl.hpp>
#include <boost/mpl/map/aux_/has_key_impl.hpp>
#include <boost/mpl/map/aux_/key_type_impl.hpp>
#include <boost/mpl/map/aux_/value_type_impl.hpp>
#include <boost/mpl/map/aux_/clear_impl.hpp>
#include <boost/mpl/map/aux_/size_impl.hpp>
#include <boost/mpl/map/aux_/empty_impl.hpp>
#include <boost/mpl/map/aux_/begin_end_impl.hpp>
#include <boost/mpl/map/aux_/iterator.hpp>
#include <boost/mpl/map/aux_/item.hpp>
#include <boost/mpl/map/aux_/map0.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

#endif // BOOST_MPL_MAP_MAP0_HPP_INCLUDED
, X, T) \
    BOOST_MPL_AUX_MAP0_OVERLOAD(R, f, X, T); \
    using Base::BOOST_PP_CAT(BOOST_MPL_AUX_OVERLOAD_,f) \
/**/

#endif


template< typename Dummy = na > struct map0
{
    typedef map0            type;
    typedef aux::map_tag    tag;
    typedef void_           key_;
    typedef long_<1>        order;
    typedef long_<0>        size;

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
    BOOST_MPL_AUX_MAP0_OVERLOAD( aux::type_wrapper<void_>, VALUE_BY_KEY, map0<>, void const volatile* );
    BOOST_MPL_AUX_MAP0_OVERLOAD( aux::type_wrapper<void_>, ITEM_BY_ORDER, map0<>, long_<1>* );
    BOOST_MPL_AUX_MAP0_OVERLOAD( aux::no_tag, ORDER_BY_KEY, map0<>, void const volatile* );
#else
    BOOST_MPL_AUX_MAP0_OVERLOAD( aux::no_tag, ORDER_BY_KEY, map0<>, void const volatile* );
    BOOST_MPL_AUX_MAP0_OVERLOAD( aux::no_tag, IS_MASKED, map0<>, void const volatile* );
#endif
};

}}

#endif // BOOST_MPL_MAP_AUX_MAP0_HPP_INCLUDED
