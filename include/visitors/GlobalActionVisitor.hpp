#ifndef MCMAS_GLOBALACTIONVISITOR_HPP
#define MCMAS_GLOBALACTIONVISITOR_HPP
#include <iostream>
#include <memory>
#include <map>
#include <string>
#include "expressions/Expression.hpp"
#include "Visitor.hpp"
#include "AbstractAgent.hpp"
#include "SwarmAgent.hpp"
#include "utils/Misc.hpp"

namespace mcmas {

  class GlobalActionVisitor : public ConstVisitor {
    public:
      std::map<std::string, Expression::Ptr> agent_actions;
      Expression::Ptr result;

      GlobalActionVisitor() = default;

      void add_owner_action(const std::string& action, const std::string& owner_id) {
        add_owner_action(action, owner_id, action);
      }

      // for compound actions from abstract agents
      void add_owner_action(const std::string& action, const std::string& owner_id, const std::string& action_id) {
        auto agent_action_expr = Expression::Eq(Expression::Id(owner_id, "Action"), Expression::Id(action_id));
        // TODO: use iterator to avoid repeat searches
        if (agent_actions.find(action) == agent_actions.end()) {
          agent_actions[action] = std::move(agent_action_expr);
        } else {
          agent_actions[action] = Expression::Or(std::move(agent_actions[action]), std::move(agent_action_expr));
        }
      }

      void add_actions_from_sa(const SwarmAgent& agent) {
        for (const auto& action : agent.actions) {
          add_owner_action(action, agent.name);
        }
      }

      void add_actions_from_aa(const AbstractAgent& agent) {
        for (const auto& [action, compound_actions] : agent.action_register) {
          for (const auto& compound_action : compound_actions) {
            add_owner_action(action, agent.name, compound_action);
          }
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
          if (left_id && left_id->is_global_action()) {
            auto* action_id = static_cast<Identifier*>(expr.right.get());
            auto& action = action_id->id;
            result = agent_actions.at(action)->clone();
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