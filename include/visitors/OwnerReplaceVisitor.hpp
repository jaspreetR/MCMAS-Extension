#ifndef MCMAS_OWNERREPLACEVISITOR_HPP
#define MCMAS_OWNERREPLACEVISITOR_HPP
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

  class OwnerReplaceVisitor : public Visitor {
    public:
      const std::string& new_owner;
      const std::string old_owner = "";
      bool replace_actions = true;
      bool replace_vars = false;

      OwnerReplaceVisitor(const std::string& new_owner, const std::string& old_owner)
      : new_owner(new_owner),
        old_owner(old_owner),
        replace_actions(false),
        replace_vars(true)
      {
      }

      OwnerReplaceVisitor(const std::string& new_owner)
      : new_owner(new_owner)
      {
      }

      void visit(BinaryExpression& expr) {
        // check if current expr is a local action assignment
        if (dynamic_cast<EqOperator*>(expr.op.get())) {
          auto* left_id = dynamic_cast<Identifier*>(expr.left.get());
          /*
          if (replace_actions && left_id && left_id->owner == old_owner && left_id->id == "Action") {
            left_id->owner = new_owner;
            return;
          }
          */
          if (left_id && left_id->owner == old_owner && not (left_id->is_global_action() || left_id->is_local_action())) {
            left_id->owner = new_owner;
            return;
          }
        }

        expr.left->accept(*this);
        expr.right->accept(*this);
      }
  };

}

#endif