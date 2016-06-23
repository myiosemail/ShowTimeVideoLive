///////////////////////////////////////////////////////////////////////////////
/// \file sub_match.hpp
/// Contains the definition of the class template sub_match\<\>
/// and associated helper functions
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_SUB_MATCH_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_SUB_MATCH_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <iosfwd>
#include <string>
#include <utility>
#include <iterator>
#include <algorithm>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>

//{{AFX_DOC_COMMENT
///////////////////////////////////////////////////////////////////////////////
// This is a hack to get Doxygen to show the inheritance relation between
// sub_match<T> and std::pair<T,T>.
#ifdef BOOST_XPRESSIVE_DOXYGEN_INVOKED
/// INTERNAL ONLY
namespace std
{
    /// INTERNAL ONLY
    template<typename, typename> struct pair {};
}
#endif
//}}AFX_DOC_COMMENT

namespace boost { namespace xpressive
{

///////////////////////////////////////////////////////////////////////////////
// sub_match
//
/// \brief Class template sub_match denotes the sequence of characters matched by a particular marked sub-expression.
///
/// When the marked sub-expression denoted by an object of type sub_match\<\> participated in a
/// regular expression match then member matched evaluates to true, and members first and second
/// denote the range of characters [first,second) which formed that match. Otherwise matched is false,
/// and members first and second contained undefined values.
///
/// If an object of type sub_match\<\> represents sub-expression 0 - that is to say the whole match -
/// then member matched is always true, unless a partial match was obtained as a result of the flag
/// match_partial being passed to a regular expression algorithm, in which case member matched is
/// false, and members first and second represent the character range that formed the partial match.
template<typename BidiIter>
struct sub_match
  : std::pair<BidiIter, BidiIter>
{
private:
    /// INTERNAL ONLY
    ///
    struct dummy { int i_; };
    typedef int dummy::*bool_type;

public:
    typedef typename iterator_value<BidiIter>::type value_type;
    typedef typename iterator_difference<BidiIter>::type difference_type;
    typedef typename detail::string_type<value_type>::type string_type;
    typedef BidiIter iterator;

    sub_match()
      : std::pair<BidiIter, BidiIter>()
      , matched(false)
    {
    }

    sub_match(BidiIter first, BidiIter second, bool matched_ = false)
      : std::pair<BidiIter, BidiIter>(first, second)
      , matched(matched_)
    {
    }

    string_type str() const
    {
        return this->matched ? string_type(this->first, this->second) : string_type();
    }

    operator string_type() const
    {
        return this->matched ? string_type(this->first, this->second) : string_type();
    }

    difference_type length() const
    {
        return this->matched ? std::distance(this->first, this->second) : 0;
    }

    operator bool_type() const
    {
        return this->matched ? &dummy::i_ : 0;
    }

    bool operator !() const
    {
        return !this->matched;
    }

    /// \brief Performs a lexicographic string comparison
    /// \param str the string against which to compare
    /// \return the results of (*this).str().compare(str)
    int compare(string_type const &str) const
    {
        return this->str().compare(str);
    }

    /// \overload
    ///
    int compare(sub_match const &sub) const
    {
        return this->str().compare(sub.str());
    }

    /// \overload
    ///
    int compare(value_type const *ptr) const
    {
        return this->str().compare(ptr);
    }

    /// \brief true if this sub-match participated in the full match.
    bool matched;
};

///////////////////////////////////////////////////////////////////////////////
/// \brief insertion operator for sending sub-matches to ostreams
/// \param sout output stream.
/// \param sub sub_match object to be written to the stream.
/// \return sout \<\< sub.str()
template<typename BidiIter, typename Char, typename Traits>
inline std::basic_ostream<Char, Traits> &operator <<
(
    std::basic_ostream<Char, Traits> &sout
  , sub_match<BidiIter> const &sub
)
{
    typedef typename iterator_value<BidiIter>::type char_type;
    BOOST_MPL_ASSERT_MSG(
        (boost::is_same<Char, char_type>::value)
      , CHARACTER_TYPES_OF_STREAM_AND_SUB_MATCH_MUST_MATCH
      , (Char, char_type)
    );
    if(sub.matched)
    {
        std::ostream_iterator<char_type, Char, Traits> iout(sout);
        std::copy(sub.first, sub.second, iout);
    }
    return sout;
}


// BUGBUG make these more efficient

template<typename BidiIter>
bool operator == (sub_match<BidiIter> const &lhs, sub_match<BidiIter> const &rhs)
{
    return lhs.compare(rhs) == 0;
}

template<typename BidiIter>
bool operator != (sub_match<BidiIter> const &lhs, sub_match<BidiIter> const &rhs)
{
    return lhs.compare(rhs) != 0;
}

template<typename BidiIter>
bool operator < (sub_match<BidiIter> const &lhs, sub_match<BidiIter> const &rhs)
{
    return lhs.compare(rhs) < 0;
}

template<typename BidiIter>
bool operator <= (sub_match<BidiIter> const &lhs, sub_match<BidiIter> const &rhs)
{
    return lhs.compare(rhs) <= 0;
}

template<typename BidiIter>
bool operator >= (sub_match<BidiIter> const &lhs, sub_match<BidiIter> const &rhs)
{
    return lhs.compare(rhs) >= 0;
}

template<typename BidiIter>
bool operator > (sub_match<BidiIter> const &lhs, sub_match<BidiIter> const &rhs)
{
    return lhs.compare(rhs) > 0;
}

template<typename BidiIter>
bool operator == (typename iterator_value<BidiIter>::type const *lhs, sub_match<BidiIter> const &rhs)
{
    return lhs == rhs.str();
}

template<typename BidiIter>
bool operator != (typename iterator_value<BidiIter>::type const *lhs, sub_match<BidiIter> const &rhs)
{
    return lhs != rhs.str();
}

template<typename BidiIter>
bool operator < (typename iterator_value<BidiIter>::type const *lhs, sub_match<BidiIter> const &rhs)
{
    return lhs < rhs.str();
}

template<typename BidiIter>
bool operator > (typename iterator_value<BidiIter>::type const *lhs, sub_match<BidiIter> const &rhs)
{
    return lhs> rhs.str();
}

template<typename BidiIter>
bool operator >= (typename iterator_value<BidiIter>::type const *lhs, sub_match<BidiIter> const &rhs)
{
    return lhs >= rhs.str();
}

template<typename BidiIter>
bool operator <= (typename iterator_value<BidiIter>::type const *lhs, sub_match<BidiIter> const &rhs)
{
    return lhs <= rhs.str();
}

template<typename BidiIter>
bool operator == (sub_match<BidiIter> const &lhs, typename iterator_value<BidiIter>::type const *rhs)
{
    return lhs.str() == rhs;
}

template<typename BidiIter>
bool operator != (sub_match<BidiIter> const &lhs, typename iterator_value<BidiIter>::type const *rhs)
{
    return lhs.str() != rhs;
}

template<typename BidiIter>
bool operator < (sub_match<BidiIter> const &lhs, typename iterator_value<BidiIter>::type const *rhs)
{
    return lhs.str() < rhs;
}

template<typename BidiIter>
bool operator > (sub_match<BidiIter> const &lhs, typename iterator_value<BidiIter>::type const *rhs)
{
    return lhs.str() > rhs;
}

template<typename BidiIter>
bool operator >= (sub_match<BidiIter> const &lhs, typename iterator_value<BidiIter>::type const *rhs)
{
    return lhs.str() >= rhs;
}

template<typename BidiIter>
bool operator <= (sub_match<BidiIter> const &lhs, typename iterator_value<BidiIter>::type const *rhs)
{
    return lhs.str() <= rhs;
}

template<typename BidiIter>
bool operator == (typename iterator_value<BidiIter>::type const &lhs, sub_match<BidiIter> const &rhs)
{
    return lhs == rhs.str();
}

template<typename BidiIter>
bool operator != (typename iterator_value<BidiIter>::type const &lhs, sub_match<BidiIter> const &rhs)
{
    return lhs != rhs.str();
}

template<typename BidiIter>
bool operator < (typename iterator_value<BidiIter>::type const &lhs, sub_match<BidiIter> const &rhs)
{
    return lhs < rhs.str();
}

template<typename BidiIter>
bool operator > (typename iterator_value<BidiIter>::type const &lhs, sub_match<BidiIter> const &rhs)
{
    return lhs> rhs.str();
}

template<typename BidiIter>
bool operator >= (typename iterator_value<BidiIter>::type const &lhs, sub_match<BidiIter> const &rhs)
{
    return lhs >= rhs.str();
}

template<typename BidiIter>
bool operator <= (typename iterator_value<BidiIter>::type const &lhs, sub_match<BidiIter> const &rhs)
{
    return lhs <= rhs.str();
}

template<typename BidiIter>
bool operator == (sub_match<BidiIter> const &lhs, typename iterator_value<BidiIter>::type const &rhs)
{
    return lhs.str() == rhs;
}

template<typename BidiIter>
bool operator != (sub_match<BidiIter> const &lhs, typename iterator_value<BidiIter>::type const &rhs)
{
    return lhs.str() != rhs;
}

template<typename BidiIter>
bool operator < (sub_match<BidiIter> const &lhs, typename iterator_value<BidiIter>::type const &rhs)
{
    return lhs.str() < rhs;
}

template<typename BidiIter>
bool operator > (sub_match<BidiIter> const &lhs, typename iterator_value<BidiIter>::type const &rhs)
{
    return lhs.str() > rhs;
}

template<typename BidiIter>
bool operator >= (sub_match<BidiIter> const &lhs, typename iterator_value<BidiIter>::type const &rhs)
{
    return lhs.str() >= rhs;
}

template<typename BidiIter>
bool operator <= (sub_match<BidiIter> const &lhs, typename iterator_value<BidiIter>::type const &rhs)
{
    return lhs.str() <= rhs;
}

// Operator+ convenience function
template<typename BidiIter>
typename sub_match<BidiIter>::string_type
operator + (sub_match<BidiIter> const &lhs, sub_match<BidiIter> const &rhs)
{
    return lhs.str() + rhs.str();
}

template<typename BidiIter>
typename sub_match<BidiIter>::string_type
operator + (sub_match<BidiIter> const &lhs, typename iterator_value<BidiIter>::type const &rhs)
{
    return lhs.str() + rhs;
}

template<typename BidiIter>
typename sub_match<BidiIter>::string_type
operator + (typename iterator_value<BidiIter>::type const &lhs, sub_match<BidiIter> const &rhs)
{
    return lhs + rhs.str();
}

template<typename BidiIter>
typename sub_match<BidiIter>::string_type
operator + (sub_match<BidiIter> const &lhs, typename iterator_value<BidiIter>::type const *rhs)
{
    return lhs.str() + rhs;
}

template<typename BidiIter>
typename sub_match<BidiIter>::string_type
operator + (typename iterator_value<BidiIter>::type const *lhs, sub_match<BidiIter> const &rhs)
{
    return lhs + rhs.str();
}

template<typename BidiIter>
typename sub_match<BidiIter>::string_type
operator + (sub_match<BidiIter> const &lhs, typename sub_match<BidiIter>::string_type const &rhs)
{
    return lhs.str() + rhs;
}

template<typename BidiIter>
typename sub_match<BidiIter>::string_type
operator + (typename sub_match<BidiIter>::string_type const &lhs, sub_match<BidiIter> const &rhs)
{
    return lhs + rhs.str();
}

}} // namespace boost::xpressive

#endif
= (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) != 0; }
template <class RandomAccessIterator>
inline bool operator < (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) > 0; }
template <class RandomAccessIterator>
inline bool operator > (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) < 0; }
template <class RandomAccessIterator>
inline bool operator <= (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) >= 0; }
template <class RandomAccessIterator>
inline bool operator >= (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) <= 0; }

// comparison to const charT& part 1:
template <class RandomAccessIterator>
inline bool operator == (const sub_match<RandomAccessIterator>& m,
                  typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) == 0; }
template <class RandomAccessIterator>
inline bool operator != (const sub_match<RandomAccessIterator>& m,
                  typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) != 0; }
template <class RandomAccessIterator>
inline bool operator > (const sub_match<RandomAccessIterator>& m,
                  typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) > 0; }
template <class RandomAccessIterator>
inline bool operator < (const sub_match<RandomAccessIterator>& m,
                  typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) < 0; }
template <class RandomAccessIterator>
inline bool operator >= (const sub_match<RandomAccessIterator>& m,
                  typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) >= 0; }
template <class RandomAccessIterator>
inline bool operator <= (const sub_match<RandomAccessIterator>& m,
                  typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) <= 0; }
// comparison to const charT* part 2:
template <class RandomAccessIterator>
inline bool operator == (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) == 0; }
template <class RandomAccessIterator>
inline bool operator != (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) != 0; }
template <class RandomAccessIterator>
inline bool operator < (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) > 0; }
template <class RandomAccessIterator>
inline bool operator > (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) < 0; }
template <class RandomAccessIterator>
inline bool operator <= (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) >= 0; }
template <class RandomAccessIterator>
inline bool operator >= (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) <= 0; }

// addition operators:
template <class RandomAccessIterator, class traits, class Allocator>
inline std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator> 
operator + (const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                  const sub_match<RandomAccessIterator>& m)
{
   std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator> result;
   result.reserve(s.size() + m.length() + 1);
   return result.append(s).append(m.first, m.second);
}
template <class RandomAccessIterator, class traits, class Allocator>
inline std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator> 
operator + (const sub_match<RandomAccessIterator>& m,
            const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{
   std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator> result;
   result.reserve(s.size() + m.length() + 1);
   return result.append(m.first, m.second).append(s);
}
#if !(defined(__GNUC__) && defined(BOOST_NO_STD_LOCALE))
template <class RandomAccessIterator>
inline std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type> 
operator + (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{
   std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type> result;
   result.reserve(std::char_traits<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type>::length(s) + m.length() + 1);
   return result.append(s).append(m.first, m.second);
}
template <class RandomAccessIterator>
inline std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type> 
operator + (const sub_match<RandomAccessIterator>& m,
            typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const * s)
{
   std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type> result;
   result.reserve(std::char_traits<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type>::length(s) + m.length() + 1);
   return result.append(m.first, m.second).append(s);
}
#else
// worwaround versions:
template <class RandomAccessIterator>
inline std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type> 
operator + (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{
   return s + m.str();
}
template <class RandomAccessIterator>
inline std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type> 
operator + (const sub_match<RandomAccessIterator>& m,
            typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const * s)
{
   return m.str() + s;
}
#endif
template <class RandomAccessIterator>
inline std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type> 
operator + (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{
   std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type> result;
   result.reserve(m.length() + 2);
   return result.append(1, s).append(m.first, m.second);
}
template <class RandomAccessIterator>
inline std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type> 
operator + (const sub_match<RandomAccessIterator>& m,
            typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{
   std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type> result;
   result.reserve(m.length() + 2);
   return result.append(m.first, m.second).append(1, s);
}
template <class RandomAccessIterator>
inline std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type> 
operator + (const sub_match<RandomAccessIterator>& m1,
            const sub_match<RandomAccessIterator>& m2)
{
   std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type> result;
   result.reserve(m1.length() + m2.length() + 1);
   return result.append(m1.first, m1.second).append(m2.first, m2.second);
}
#ifndef BOOST_NO_STD_LOCALE
template <class charT, class traits, class RandomAccessIterator>
std::basic_ostream<charT, traits>&
   operator << (std::basic_ostream<charT, traits>& os,
                const sub_match<RandomAccessIterator>& s)
{
   return (os << s.str());
}
#else
template <class RandomAccessIterator>
std::ostream& operator << (std::ostream& os,
                           const sub_match<RandomAccessIterator>& s)
{
   return (os << s.str());
}
#endif

#ifdef BOOST_OLD_REGEX_H
namespace re_detail{
template <class BidiIterator, class charT>
int do_toi(BidiIterator i, BidiIterator j, char c, int radix)
{
   std::string s(i, j);
   char* p;
   int result = std::strtol(s.c_str(), &p, radix);
   if(*p)raise_regex_exception("Bad sub-expression");
   return result;
}

//
// helper:
template <class I, class charT>
int do_toi(I& i, I j, charT c)
{
   int result = 0;
   while((i != j) && (isdigit(*i)))
   {
      result = result*10 + (*i - '0');
      ++i;
   }
   return result;
}
}


template <class BidiIterator>
sub_match<BidiIterator>::operator int()const
{
   BidiIterator i = first;
   BidiIterator j = second;
   if(i == j)raise_regex_exception("Bad sub-expression");
   int neg = 1;
   if((i != j) && (*i == '-'))
   {
      neg = -1;
      ++i;
   }
   neg *= re_detail::do_toi(i, j, *i);
   if(i != j)raise_regex_exception("Bad sub-expression");
   return neg;
}
template <class BidiIterator>
sub_match<BidiIterator>::operator unsigned int()const
{
   BidiIterator i = first;
   BidiIterator j = second;
   if(i == j)
      raise_regex_exception("Bad sub-expression");
   return re_detail::do_toi(i, j, *first);
}
#endif

} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4103)
#endif
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif

