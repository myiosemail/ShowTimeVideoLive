//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TR1_ARRAY_HPP_INCLUDED
#  define BOOST_TR1_ARRAY_HPP_INCLUDED
#  include <boost/tr1/detail/config.hpp>

#ifdef BOOST_HAS_TR1_ARRAY

#  if defined(BOOST_HAS_INCLUDE_NEXT) && !defined(BOOST_TR1_DISABLE_INCLUDE_NEXT)
#     include_next BOOST_TR1_HEADER(array)
#  else
#     include <boost/tr1/detail/config_all.hpp>
#     include BOOST_TR1_STD_HEADER(BOOST_TR1_PATH(array))
#  endif

#else

#include <boost/array.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/detail/workaround.hpp>

namespace std{ namespace tr1{

using ::boost::array;

#if !BOOST_WORKAROUND(__BORLANDC__, < 0x0582)
// [6.1.3.2] Tuple creation functions
using ::boost::swap;
#endif

#if !defined(BOOST_TR1_USE_OLD_TUPLE)
}} namespace boost{ namespace fusion{
#endif

// [6.2.2.5] Tuple interface to class template array
template <class T> struct tuple_size; // forward declaration
template <int I, class T> struct tuple_element; // forward declaration
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T, size_t N>
struct tuple_size< ::boost::array<T, N> >
   : public ::boost::integral_constant< ::std::size_t, N>{};


template <int I, class T, size_t N>
struct tuple_element<I, ::boost::array<T, N> >
{
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x570))
   BOOST_STATIC_ASSERT(I < (int)N);
   BOOST_STATIC_ASSERT(I >= 0);
#endif
   typedef T type;
};
#endif
template <int I, class T, size_t N>
T& get( ::boost::array<T, N>& a)
{
   BOOST_STATIC_ASSERT(I < N);
   BOOST_STATIC_ASSERT(I >= 0);
   return a[I];
}

template <int I, class T, size_t N>
const T& get(const array<T, N>& a)
{
   BOOST_STATIC_ASSERT(I < N);
   BOOST_STATIC_ASSERT(I >= 0);
   return a[I];
}

#if !defined(BOOST_TR1_USE_OLD_TUPLE)
}} namespace std{ namespace tr1{

   using ::boost::fusion::tuple_size;
   using ::boost::fusion::tuple_element;
   using ::boost::fusion::get;

#endif


} } // namespaces

#endif

#endif
mpl::true_ )
    {
      boost::serialization::split_member(ar, *this, version);
    }

    // default implementation
    template<class Archive>
    void save(Archive &ar, const unsigned int version) const
    {
      ar.save_array(*this,version);
    }

    // default implementation
    template<class Archive>
    void load(Archive &ar, const unsigned int version)
    {
      ar.load_array(*this,version);
    }
    
    // default implementation
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
      typedef BOOST_DEDUCED_TYPENAME 
          boost::serialization::use_array_optimization<Archive>::template apply<
                    BOOST_DEDUCED_TYPENAME remove_const< T >::type 
                >::type use_optimized;
      serialize_optimized(ar,version,use_optimized());
    }
    
    value_type* address() const
    {
      return m_t;
    }

    std::size_t count() const
    {
      return m_element_count;
    }
    
private:
    value_type* m_t;
    std::size_t m_element_count;
};

template<class T>
inline
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
const
#endif
array< T > make_array( T* t, std::size_t s){
    return array< T >(t, s);
}

template <class Archive, class T, std::size_t N>
void serialize(Archive& ar, boost::array<T,N>& a, const unsigned int /* version */)
{
  ar & boost::serialization::make_nvp("elems",a.elems);
}

} } // end namespace boost::serialization

#ifdef __BORLANDC__
// ignore optimizations for Borland
#define BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(Archive)      
#else
#define BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(Archive)           \
namespace boost { namespace serialization {                           \
template <> struct use_array_optimization<Archive> {                  \
  template <class ValueType>                                          \
  struct apply : boost::mpl::apply1<Archive::use_array_optimization   \
      , BOOST_DEDUCED_TYPENAME boost::remove_const<ValueType>::type   \
    >::type {};                                                       \
}; }}
#endif // __BORLANDC__

#endif //BOOST_SERIALIZATION_ARRAY_HPP
