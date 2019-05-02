#ifndef MCMAS_VISITOR_HPP
#define MCMAS_VISITOR_HPP
#include "expressions/Expression.hpp"

namespace mcmas {

  class Visitor {
    public:
      virtual void visit(UnaryExpression& expr);
      virtual void visit(BinaryExpression& expr);
      virtual void visit(BoolLiteral& expr);
      virtual void visit(IntLiteral& expr);
      virtual void visit(Identifier& expr);
  };

  class ConstVisitor {
    public:
      virtual void visit(const UnaryExpression& expr);
      virtual void visit(const BinaryExpression& expr);
      virtual void visit(const BoolLiteral& expr);
      virtual void visit(const IntLiteral& expr);
      virtual void visit(const Identifier& expr);
  };
}

#endif