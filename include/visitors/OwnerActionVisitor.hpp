#ifndef MCMAS_OWNERACTIONVISITOR_HPP
#define MCMAS_OWNERACTIONVISITOR_HPP
#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <cassert>
#include "expressions/Expression.hpp"
#include "Visitor.hpp"
#include "SwarmAgent.hpp"
#include "utils/Misc.hpp"

namespace mcmas {

  class OwnerActionVisitor : public ConstVisitor {
    public:
      std::map<std::string, Expression::Ptr> action_register;
      Expression::Ptr result;

      OwnerActionVisitor(const std::map<std::string, std::vector<std::string>>& agent_actions)
      {
        for (const auto& [action_id, actions] : agent_actions) {
          assert(actions.size() > 0);
          Expression::Ptr action_expr = Expression::Eq(Expression::Id("Action"), Expression::Id(actions[0]));
          for (size_t i = 1; i < actions.size(); ++i) {
            action_expr = Expression::Or(std::move(action_expr), 
                                         Expression::Eq(Expression::Id("Action"), Expression::Id(actions[i])));
          }

          action_register[action_id] = std::move(action_expr);
        }
      }

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
        expr.child->accept(*this);
        result = Expression::Ptr(new UnaryExpression(std::move(result), expr.op->clone()));
      }

      void visit(const BinaryExpression& expr) {
        // check if current expr is a local action assignment
        if (dynamic_cast<EqOperator*>(expr.op.get())) {
          auto* left_id = dynamic_cast<Identifier*>(expr.left.get());
          if (left_id && left_id->is_owner_action()) {
            auto* action_id = static_cast<Identifier*>(expr.right.get());
            auto& action = action_id->id;
            result = action_register.at(action)->clone();
            return;
          }
        }

        expr.left->accept(*this);
        auto left_result = std::move(result);

        expr.right->accept(*this);
        auto right_result = std::move(result);

        result = Expression::Ptr(new BinaryExpression(std::move(left_result), std::move(right_result), expr.op->clone()));
      }
  };

}

#endif