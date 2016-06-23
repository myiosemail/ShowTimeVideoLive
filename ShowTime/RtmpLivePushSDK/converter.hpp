/* Copyright 2003-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_CONVERTER_HPP
#define BOOST_MULTI_INDEX_DETAIL_CONVERTER_HPP

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* converter offers means to access indices of a given multi_index_container
 * and for convertibilty between index iterators, so providing a
 * localized access point for get() and project() functions.
 */

template<typename MultiIndexContainer,typename Index>
struct converter
{
  static const Index& index(const MultiIndexContainer& x){return x;}
  static Index&       index(MultiIndexContainer& x){return x;}

  static typename Index::const_iterator const_iterator(
    const MultiIndexContainer& x,typename MultiIndexContainer::node_type* node)
  {
    return x.Index::make_iterator(node);
  }

  static typename Index::iterator iterator(
    MultiIndexContainer& x,typename MultiIndexContainer::node_type* node)
  {
    return x.Index::make_iterator(node);
  }
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif
                               UserRangeChecker
                                                 >::type
{
  typedef Traits traits ;

  typedef typename Traits::argument_type argument_type ;
  typedef typename Traits::result_type   result_type   ;

  result_type operator() ( argument_type s ) const { return this->convert(s) ; }
} ;



template<class S,
         class OverflowHandler  = def_overflow_handler,
         class Float2IntRounder = Trunc<S>  ,
         class UserRangeChecker = UseInternalRangeChecker
        >
struct make_converter_from
{
  template<class T,
           class Traits       = conversion_traits<T,S>,
           class RawConverter = raw_converter<Traits>
          > 
  struct to
  {
    typedef converter<T,S,Traits,OverflowHandler,Float2IntRounder,RawConverter,UserRangeChecker> type ;
  } ;

} ;

} } // namespace boost::numeric

#endif


