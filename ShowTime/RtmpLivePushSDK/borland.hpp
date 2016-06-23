/*
 *
 * Copyright (c) 1998-2002
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */
 
 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         boost/regex/config/borland.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: regex borland-specific config setup.
  */


#if defined(__BORLANDC__)
#  if (__BORLANDC__ == 0x550) || (__BORLANDC__ == 0x551)
      // problems with std::basic_string and dll RTL:
#     if defined(_RTLDLL) && defined(_RWSTD_COMPILE_INSTANTIATE)
#        ifdef BOOST_REGEX_BUILD_DLL
#           error _RWSTD_COMPILE_INSTANTIATE must not be defined when building regex++ as a DLL
#        else
#           pragma message("Defining _RWSTD_COMPILE_INSTANTIATE when linking to the DLL version of the RTL may produce memory corruption problems in std::basic_string, as a result of separate versions of basic_string's static data in the RTL and you're exe/dll: be warned!!")
#        endif
#     endif
#     ifndef _RTLDLL
         // this is harmless for a staic link:
#        define _RWSTD_COMPILE_INSTANTIATE
#     endif
      // external templates cause problems for some reason:
#     define BOOST_REGEX_NO_EXTERNAL_TEMPLATES
#  endif
#  if (__BORLANDC__ <= 0x540) && !defined(BOOST_REGEX_NO_LIB) && !defined(_NO_VCL)
      // C++ Builder 4 and earlier, we can't tell whether we should be using
      // the VCL runtime or not, do a static link instead:
#     define BOOST_REGEX_STATIC_LINK
#  endif
   //
   // VCL support:
   // if we're building a console app then there can't be any VCL (can there?)
#  if !defined(__CONSOLE__) && !defined(_NO_VCL)
#     define BOOST_REGEX_USE_VCL
#  endif
   //
   // if this isn't Win32 then don't automatically select link
   // libraries:
   //
#  ifndef _Windows
#     ifndef BOOST_REGEX_NO_LIB
#        define BOOST_REGEX_NO_LIB
#     endif
#     ifndef BOOST_REGEX_STATIC_LINK
#        define BOOST_REGEX_STATIC_LINK
#     endif
#  endif

#if __BORLANDC__ < 0x600
//
// string workarounds:
//
#include <cstring>
#undef strcmp
#undef strcpy
#endif

#endif


roken <cstring> so that Boost.test works:
#     include <cstring>
#     undef strcmp
#  endif
   // fix broken errno declaration:
#  include <errno.h>
#  ifndef errno
#     define errno errno
#  endif

#endif

//
// new bug in 5.61:
#if (__BORLANDC__ >= 0x561) && (__BORLANDC__ <= 0x580)
   // this seems to be needed by the command line compiler, but not the IDE:
#  define BOOST_NO_MEMBER_FUNCTION_SPECIALIZATIONS
#endif

// Borland C++ Builder 2006 Update 2 and below:
#if (__BORLANDC__ <= 0x582)
#  define BOOST_NO_SFINAE
#  define BOOST_BCB_PARTIAL_SPECIALIZATION_BUG
#  define BOOST_NO_TEMPLATE_TEMPLATES

#  define BOOST_NO_PRIVATE_IN_AGGREGATE

#  ifdef _WIN32
#     define BOOST_NO_SWPRINTF
#  elif defined(linux) || defined(__linux__) || defined(__linux)
      // we should really be able to do without this
      // but the wcs* functions aren't imported into std::
#     define BOOST_NO_STDC_NAMESPACE
      // _CPPUNWIND doesn't get automatically set for some reason:
#     pragma defineonoption BOOST_CPPUNWIND -x
#  endif
#endif

#if (__BORLANDC__ <= 0x613)  // Beman has asked Alisdair for more info
   // we shouldn't really need this - but too many things choke
   // without it, this needs more investigation:
#  define BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#  define BOOST_NO_IS_ABSTRACT
#  define BOOST_NO_FUNCTION_TYPE_SPECIALIZATIONS
#  define BOOST_NO_USING_TEMPLATE
#  define BOOST_SP_NO_SP_CONVERTIBLE

// Temporary workaround
#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif

// Borland C++ Builder 2008 and below:
#  define BOOST_NO_INTEGRAL_INT64_T
#  define BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#  define BOOST_NO_DEPENDENT_NESTED_DERIVATIONS
#  define BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#  define BOOST_NO_TWO_PHASE_NAME_LOOKUP
#  define BOOST_NO_USING_DECLARATION_OVERLOADS_FROM_TYPENAME_BASE
#  define BOOST_NO_NESTED_FRIENDSHIP
#  define BOOST_NO_TYPENAME_WITH_CTOR
#if (__BORLANDC__ < 0x600)
#  define BOOST_ILLEGAL_CV_REFERENCES
#endif

//
//  Positive Feature detection
//
// Borland C++ Builder 2008 and below:
#if (__BORLANDC__ >= 0x599)
#  pragma defineonoption BOOST_CODEGEAR_0X_SUPPORT -Ax
#endif
//
// C++0x Macros:
//
#if !defined( BOOST_CODEGEAR_0X_SUPPORT ) || (__BORLANDC__ < 0x610)
#  define BOOST_NO_CXX11_CHAR16_T
#  define BOOST_NO_CXX11_CHAR32_T
#  define BOOST_NO_CXX11_DECLTYPE
#  define BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#  define BOOST_NO_CXX11_EXTERN_TEMPLATE
#  define BOOST_NO_CXX11_RVALUE_REFERENCES 
#  define BOOST_NO_CXX11_SCOPED_ENUMS
#  define BOOST_NO_CXX11_STATIC_ASSERT
#else
#  define BOOST_HAS_ALIGNOF
#  define BOOST_HAS_CHAR16_T
#  define BOOST_HAS_CHAR32_T
#  define BOOST_HAS_DECLTYPE
#  define BOOST_HAS_EXPLICIT_CONVERSION_OPS
#  define BOOST_HAS_REF_QUALIFIER
#  define BOOST_HAS_RVALUE_REFS
#  define BOOST_HAS_STATIC_ASSERT
#endif

#define BOOST_NO_CXX11_AUTO_DECLARATIONS
#define BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#define BOOST_NO_CXX11_CONSTEXPR
#define BOOST_NO_CXX11_DECLTYPE_N3276
#define BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#define BOOST_NO_CXX11_DELETED_FUNCTIONS
#define BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#define BOOST_NO_CXX11_LAMBDAS
#define BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#define BOOST_NO_CXX11_NULLPTR
#define BOOST_NO_CXX11_RANGE_BASED_FOR
#define BOOST_NO_CXX11_RAW_LITERALS
#define BOOST_NO_CXX11_RVALUE_REFERENCES
#define BOOST_NO_CXX11_SCOPED_ENUMS
#define BOOST_NO_SFINAE_EXPR
#define BOOST_NO_CXX11_TEMPLATE_ALIASES
#define BOOST_NO_CXX11_UNICODE_LITERALS    // UTF-8 still not supported
#define BOOST_NO_CXX11_VARIADIC_TEMPLATES
#define BOOST_NO_CXX11_NOEXCEPT
#define BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX

#if __BORLANDC__ >= 0x590
#  define BOOST_HAS_TR1_HASH

#  define BOOST_HAS_MACRO_USE_FACET
#endif

//
// Post 0x561 we have long long and stdint.h:
#if __BORLANDC__ >= 0x561
#  ifndef __NO_LONG_LONG
#     define BOOST_HAS_LONG_LONG
#  else
#     define BOOST_NO_LONG_LONG
#  endif
   // On non-Win32 platforms let the platform config figure this out:
#  ifdef _WIN32
#      define BOOST_HAS_STDINT_H
#  endif
#endif

// Borland C++Builder 6 defaults to using STLPort.  If _USE_OLD_RW_STL is
// defined, then we have 0x560 or greater with the Rogue Wave implementation
// which presumably has the std::DBL_MAX bug.
#if defined( BOOST_BCB_WITH_ROGUE_WAVE )
// <climits> is partly broken, some macros define symbols that are really in
// namespace std, so you end up having to use illegal constructs like
// std::DBL_MAX, as a fix we'll just include float.h and have done with:
#include <float.h>
#endif
//
// __int64:
//
#if (__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__)
#  define BOOST_HAS_MS_INT64
#endif
//
// check for exception handling support:
//
#if !defined(_CPPUNWIND) && !defined(BOOST_CPPUNWIND) && !defined(__EXCEPTIONS) && !defined(BOOST_NO_EXCEPTIONS)
#  define BOOST_NO_EXCEPTIONS
#endif
//
// all versions have a <dirent.h>:
//
#ifndef __STRICT_ANSI__
#  define BOOST_HAS_DIRENT_H
#endif
//
// all versions support __declspec:
//
#if defined(__STRICT_ANSI__)
// config/platform/win32.hpp will define BOOST_SYMBOL_EXPORT, etc., unless already defined  
#  define BOOST_SYMBOL_EXPORT
#endif
//
// ABI fixing headers:
//
#if __BORLANDC__ != 0x600 // not implemented for version 6 compiler yet
#ifndef BOOST_ABI_PREFIX
#  define BOOST_ABI_PREFIX "boost/config/abi/borland_prefix.hpp"
#endif
#ifndef BOOST_ABI_SUFFIX
#  define BOOST_ABI_SUFFIX "boost/config/abi/borland_suffix.hpp"
#endif
#endif
//
// Disable Win32 support in ANSI mode:
//
#if __BORLANDC__ < 0x600
#  pragma defineonoption BOOST_DISABLE_WIN32 -A
#elif defined(__STRICT_ANSI__)
#  define BOOST_DISABLE_WIN32
#endif
//
// MSVC compatibility mode does some nasty things:
// TODO: look up if this doesn't apply to the whole 12xx range
//
#if defined(_MSC_VER) && (_MSC_VER <= 1200)
#  define BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#  define BOOST_NO_VOID_RETURNS
#endif

// Borland did not implement value-initialization completely, as I reported
// in 2007, Borland Report 51854, "Value-initialization: POD struct should be
// zero-initialized", http://qc.embarcadero.com/wc/qcmain.aspx?d=51854
// See also: http://www.boost.org/libs/utility/value_init.htm#compiler_issues
// (Niels Dekker, LKEB, April 2010)
#define BOOST_NO_COMPLETE_VALUE_INITIALIZATION

#define BOOST_COMPILER "Borland C++ version " BOOST_STRINGIZE(__BORLANDC__)




