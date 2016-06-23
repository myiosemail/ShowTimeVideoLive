// Boost.Function library

//  Copyright Douglas Gregor 2002-2003. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#define BOOST_FUNCTION_NUM_ARGS 1
#include <boost/function/detail/maybe_include.hpp>
#undef BOOST_FUNCTION_NUM_ARGS
t/mpl/apply.hpp>

namespace boost { namespace detail {

// A utility for creating unary function objects that play nicely with
// boost::result_of and that handle the forwarding problem.
//
// mpl::apply<F, A0>::type is expected to be a stateless function
// object that accepts an argument of type A0&.  It is also expected
// to have a nested ::result_type identical to its return type.
template<typename F>
struct function1
{
    template<typename Signature>
    struct result
    {};

    template<typename This, typename A0>
    struct result<This(A0)>
    {
        // How adding const to arguments handles rvalues.
        //
        // if A0 is     arg0 is       represents actual argument
        // --------     -------       --------------------------
        // T const &    T const       const T lvalue
        // T &          T             non-const T lvalue
        // T const      T const       const T rvalue
        // T            T const       non-const T rvalue
        typedef typename remove_reference<
            typename add_const< A0 >::type
        >::type arg0;

        typedef typename mpl::apply1<F, arg0>::type impl;
        typedef typename impl::result_type type;
    };

    // Handles mutable lvalues
    template<typename A0>
    typename result<function1(A0 &)>::type
    operator ()(A0 &a0) const
    {
        typedef typename result<function1(A0 &)>::impl impl;
        typedef typename result<function1(A0 &)>::type type;
        typedef A0 &arg0;
        BOOST_CONCEPT_ASSERT((UnaryFunction<impl, type, arg0>));
        //boost::function_requires<UnaryFunctionConcept<impl, type, arg0> >();
        return impl()(a0);
    }

    // Handles const lvalues and all rvalues
    template<typename A0>
    typename result<function1(A0 const &)>::type
    operator ()(A0 const &a0) const
    {
        typedef typename result<function1(A0 const &)>::impl impl;
        typedef typename result<function1(A0 const &)>::type type;
        typedef A0 const &arg0;
        BOOST_CONCEPT_ASSERT((UnaryFunction<impl, type, arg0>));
        //boost::function_requires<UnaryFunctionConcept<impl, type, arg0> >();
        return impl()(a0);
    }
};

}} // namespace boost::detail

#endif // BOOST_DETAIL_FUNCTION1_DWA200655_HPP
