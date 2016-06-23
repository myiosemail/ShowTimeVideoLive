///////////////////////////////////////////////////////////////////////////////
/// \file deep_copy.hpp
/// Replace all nodes stored by reference by nodes stored by value.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DEEP_COPY_HPP_EAN_11_21_2006
#define BOOST_PROTO_DEEP_COPY_HPP_EAN_11_21_2006

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/args.hpp>
#include <boost/proto/expr.hpp>

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename Expr, long Arity = Expr::proto_arity_c>
        struct deep_copy_impl;

        template<typename Expr>
        struct deep_copy_impl<Expr, 0>
        {
            typedef
                typename base_expr<
                    typename Expr::proto_domain
                  , tag::terminal
                  , term<typename term_traits<typename Expr::proto_child0>::value_type>
                >::type
            expr_type;

            typedef typename Expr::proto_generator proto_generator;
            typedef typename proto_generator::template result<proto_generator(expr_type)>::type result_type;

            template<typename Expr2, typename S, typename D>
            result_type operator()(Expr2 const &e, S const &, D const &) const
            {
                return proto_generator()(expr_type::make(e.proto_base().child0));
            }
        };
    }

    namespace result_of
    {
        /// \brief A metafunction for calculating the return type
        /// of \c proto::deep_copy().
        ///
        /// A metafunction for calculating the return type
        /// of \c proto::deep_copy(). The type parameter \c Expr
        /// should be the type of a Proto expression tree.
        /// It should not be a reference type, nor should it
        /// be cv-qualified.
        template<typename Expr>
        struct deep_copy
        {
            typedef
                typename detail::deep_copy_impl<
                    BOOST_PROTO_UNCVREF(Expr)
                >::result_type
            type;
        };
    }

    namespace functional
    {
        /// \brief A PolymorphicFunctionObject type for deep-copying
        /// Proto expression trees.
        ///
        /// A PolymorphicFunctionObject type for deep-copying
        /// Proto expression trees. When a tree is deep-copied,
        /// all internal nodes and most terminals held by reference
        /// are instead held by value.
        ///
        /// \attention Terminals of reference-to-function type are
        /// left unchanged. Terminals of reference-to-array type are
        /// stored by value, which can cause a large amount of data
        /// to be passed by value and stored on the stack.
        struct deep_copy
        {
            BOOST_PROTO_CALLABLE()

            template<typename Sig>
            struct result;

            template<typename This, typename Expr>
            struct result<This(Expr)>
            {
                typedef
                    typename detail::deep_copy_impl<
                        BOOST_PROTO_UNCVREF(Expr)
                    >::result_type
                type;
            };

            /// \brief Deep-copies a Proto expression tree, turning all
            /// nodes and terminals held by reference into ones held by
            /// value.
            template<typename Expr>
            typename result_of::deep_copy<Expr>::type
            operator()(Expr const &e) const
            {
                return proto::detail::deep_copy_impl<Expr>()(e, 0, 0);
            }
        };
    }

    /// \brief A function for deep-copying
    /// Proto expression trees.
    ///
    /// A function for deep-copying
    /// Proto expression trees. When a tree is deep-copied,
    /// all internal nodes and most terminals held by reference
    /// are instead held by value.
    ///
    /// \attention Terminals of reference-to-function type are
    /// left unchanged.
    ///
    /// \sa proto::functional::deep_copy.
    template<typename Expr>
    typename proto::result_of::deep_copy<Expr>::type
    deep_copy(Expr const &e)
    {
        return proto::detail::deep_copy_impl<Expr>()(e, 0, 0);
    }

    /// \brief A PrimitiveTransform for deep-copying
    /// Proto expression trees.
    ///
    /// A PrimitiveTransform for deep-copying
    /// Proto expression trees. When a tree is deep-copied,
    /// all internal nodes and most terminals held by reference
    /// are instead held by value.
    ///
    /// \attention Terminals of reference-to-function type are
    /// left unchanged.
    ///
    /// \sa proto::functional::deep_copy.
    struct _deep_copy
      : proto::transform<_deep_copy>
    {
        template<typename E, typename S, typename D>
        struct impl
          : detail::deep_copy_impl<BOOST_PROTO_UNCVREF(E)>
        {};
    };

    namespace detail
    {
        // include the definition of deep_copy_impl
        #include <boost/proto/detail/deep_copy.hpp>
    }

}}

#endif // BOOST_PROTO_COMPILER_DEEP_COPY_HPP_EAN_11_21_2006

_copy_impl< typename remove_reference< typename Expr::proto_child1 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child2 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child3 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child4 >::type::proto_derived_expr >::result_type
                >
            >::type
        expr_type;
        typedef typename Expr::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type result_type;
        template<typename Expr2, typename S, typename D>
        result_type operator()(Expr2 const &e, S const &, D const &) const
        {
            expr_type const that = {
                proto::deep_copy(e.proto_base().child0) , proto::deep_copy(e.proto_base().child1) , proto::deep_copy(e.proto_base().child2) , proto::deep_copy(e.proto_base().child3) , proto::deep_copy(e.proto_base().child4)
            };
            return proto_generator()(that);
        }
    };
    template<typename Expr>
    struct deep_copy_impl<Expr, 6>
    {
        typedef
            typename base_expr<
                typename Expr::proto_domain
              , typename Expr::proto_tag
              , list6<
                    typename deep_copy_impl< typename remove_reference< typename Expr::proto_child0 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child1 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child2 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child3 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child4 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child5 >::type::proto_derived_expr >::result_type
                >
            >::type
        expr_type;
        typedef typename Expr::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type result_type;
        template<typename Expr2, typename S, typename D>
        result_type operator()(Expr2 const &e, S const &, D const &) const
        {
            expr_type const that = {
                proto::deep_copy(e.proto_base().child0) , proto::deep_copy(e.proto_base().child1) , proto::deep_copy(e.proto_base().child2) , proto::deep_copy(e.proto_base().child3) , proto::deep_copy(e.proto_base().child4) , proto::deep_copy(e.proto_base().child5)
            };
            return proto_generator()(that);
        }
    };
    template<typename Expr>
    struct deep_copy_impl<Expr, 7>
    {
        typedef
            typename base_expr<
                typename Expr::proto_domain
              , typename Expr::proto_tag
              , list7<
                    typename deep_copy_impl< typename remove_reference< typename Expr::proto_child0 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child1 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child2 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child3 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child4 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child5 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child6 >::type::proto_derived_expr >::result_type
                >
            >::type
        expr_type;
        typedef typename Expr::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type result_type;
        template<typename Expr2, typename S, typename D>
        result_type operator()(Expr2 const &e, S const &, D const &) const
        {
            expr_type const that = {
                proto::deep_copy(e.proto_base().child0) , proto::deep_copy(e.proto_base().child1) , proto::deep_copy(e.proto_base().child2) , proto::deep_copy(e.proto_base().child3) , proto::deep_copy(e.proto_base().child4) , proto::deep_copy(e.proto_base().child5) , proto::deep_copy(e.proto_base().child6)
            };
            return proto_generator()(that);
        }
    };
    template<typename Expr>
    struct deep_copy_impl<Expr, 8>
    {
        typedef
            typename base_expr<
                typename Expr::proto_domain
              , typename Expr::proto_tag
              , list8<
                    typename deep_copy_impl< typename remove_reference< typename Expr::proto_child0 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child1 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child2 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child3 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child4 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child5 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child6 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child7 >::type::proto_derived_expr >::result_type
                >
            >::type
        expr_type;
        typedef typename Expr::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type result_type;
        template<typename Expr2, typename S, typename D>
        result_type operator()(Expr2 const &e, S const &, D const &) const
        {
            expr_type const that = {
                proto::deep_copy(e.proto_base().child0) , proto::deep_copy(e.proto_base().child1) , proto::deep_copy(e.proto_base().child2) , proto::deep_copy(e.proto_base().child3) , proto::deep_copy(e.proto_base().child4) , proto::deep_copy(e.proto_base().child5) , proto::deep_copy(e.proto_base().child6) , proto::deep_copy(e.proto_base().child7)
            };
            return proto_generator()(that);
        }
    };
    template<typename Expr>
    struct deep_copy_impl<Expr, 9>
    {
        typedef
            typename base_expr<
                typename Expr::proto_domain
              , typename Expr::proto_tag
              , list9<
                    typename deep_copy_impl< typename remove_reference< typename Expr::proto_child0 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child1 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child2 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child3 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child4 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child5 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child6 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child7 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child8 >::type::proto_derived_expr >::result_type
                >
            >::type
        expr_type;
        typedef typename Expr::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type result_type;
        template<typename Expr2, typename S, typename D>
        result_type operator()(Expr2 const &e, S const &, D const &) const
        {
            expr_type const that = {
                proto::deep_copy(e.proto_base().child0) , proto::deep_copy(e.proto_base().child1) , proto::deep_copy(e.proto_base().child2) , proto::deep_copy(e.proto_base().child3) , proto::deep_copy(e.proto_base().child4) , proto::deep_copy(e.proto_base().child5) , proto::deep_copy(e.proto_base().child6) , proto::deep_copy(e.proto_base().child7) , proto::deep_copy(e.proto_base().child8)
            };
            return proto_generator()(that);
        }
    };
    template<typename Expr>
    struct deep_copy_impl<Expr, 10>
    {
        typedef
            typename base_expr<
                typename Expr::proto_domain
              , typename Expr::proto_tag
              , list10<
                    typename deep_copy_impl< typename remove_reference< typename Expr::proto_child0 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child1 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child2 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child3 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child4 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child5 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child6 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child7 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child8 >::type::proto_derived_expr >::result_type , typename deep_copy_impl< typename remove_reference< typename Expr::proto_child9 >::type::proto_derived_expr >::result_type
                >
            >::type
        expr_type;
        typedef typename Expr::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type result_type;
        template<typename Expr2, typename S, typename D>
        result_type operator()(Expr2 const &e, S const &, D const &) const
        {
            expr_type const that = {
                proto::deep_copy(e.proto_base().child0) , proto::deep_copy(e.proto_base().child1) , proto::deep_copy(e.proto_base().child2) , proto::deep_copy(e.proto_base().child3) , proto::deep_copy(e.proto_base().child4) , proto::deep_copy(e.proto_base().child5) , proto::deep_copy(e.proto_base().child6) , proto::deep_copy(e.proto_base().child7) , proto::deep_copy(e.proto_base().child8) , proto::deep_copy(e.proto_base().child9)
            };
            return proto_generator()(that);
        }
    };
