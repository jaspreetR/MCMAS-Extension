#ifndef MCMAS_STRINGVISITOR_HPP
#define MCMAS_STRINGVISITOR_HPP
#include <string>
#include "Visitor.hpp"


namespace mcmas {

  class StringVisitor : public ConstVisitor {
    public:
      std::string result;

      void visit(const IntLiteral& expr) {
        result = std::to_string(expr.value);
      }

      void visit(const BoolLiteral& expr) {
        result = expr.value ? "true" : "false";
      }

      void visit(const Identifier& expr) {
        if (expr.owner.size() == 0) {
          result = expr.id;
        } else {
          result = expr.owner + "." + expr.id;
        }
      }

      void visit(const UnaryExpression& expr) {
        expr.child->accept(*this);
        auto child_result = std::move(result);

        result = "(" + expr.op->getToken() + child_result + ")";
      } 

      void visit(const BinaryExpression& expr) {
        expr.left->accept(*this);
        auto left_result = std::move(result);

        expr.right->accept(*this);
        auto right_result = std::move(result);

        result = "(" + left_result + " " + expr.op->getToken() + " " + right_result + ")";
      }
  };

}

#endif