#ifndef MCMAS_SUBSTVISITOR_HPP
#define MCMAS_SUBSTVISITOR_HPP
#include <iostream>
#include <memory>
#include "expressions/Expression.hpp"
#include "AgentState.hpp"
#include "Visitor.hpp"
#include "utils/Misc.hpp"
#include "utils/Overload.hpp"

namespace mcmas {

  class SubstVisitor : public ConstVisitor {
    public:
      const AgentState* state;
      Expression::Ptr result;

      SubstVisitor(const AgentState* state) : state(state) 
      {}

      void visit(const IntLiteral& expr) {
        result = expr.clone();
      }

      void visit(const BoolLiteral& expr) {
        result = expr.clone();
      }

      void visit(const Identifier& expr) {
        result = expr.clone();
      }

      void visit(const UnaryExpression& expr) {
        Expression::Ptr child_result;

        auto* child_id = dynamic_cast<Identifier*>(expr.child.get());
        if (child_id && child_id->is_current_agent()) {
          auto var_value = state->get_value(child_id->id);
          child_result = value_to_expr(var_value);
        } else {
          expr.child->accept(*this);
          child_result = std::move(result);
        }

        result = Expression::Ptr(new UnaryExpression(std::move(child_result), expr.op->clone()));
      }

      void visit(const BinaryExpression& expr) {
        Expression::Ptr left_result;
        Expression::Ptr right_result;

        auto* left_id = dynamic_cast<Identifier*>(expr.left.get());
        if (left_id && left_id->is_current_agent() && !left_id->is_action()) {
          auto var_value = state->get_value(left_id->id);
          left_result = value_to_expr(var_value);
        } else {
          expr.left->accept(*this);
          left_result = std::move(result);
        }

        auto* right_id = dynamic_cast<Identifier*>(expr.right.get());
        if (right_id && right_id->is_current_agent() && !left_id->is_action()) {
          auto var_value = state->get_value(right_id->id);
          right_result = value_to_expr(var_value);
        } else {
          expr.right->accept(*this);
          right_result = std::move(result);
        }

        result = Expression::Ptr(new BinaryExpression(std::move(left_result), std::move(right_result), expr.op->clone()));
      }

      // these ids are hardcoded in Environment because mcmas does not accept const expressions
      Expression::Ptr value_to_expr(std::variant<int, bool> value) {
        return std::visit(Overload {
          [](int value) { return Expression::Id("Environment", "env_val_" + std::to_string(value)); },
          [](bool value) { return value ? Expression::Id("Environment", "env_val_true") : 
                                          Expression::Id("Environment", "env_val_false");}
        }, value);
      }
  };

}

#endif