#ifndef MCMAS_EXPRESSION_HPP
#define MCMAS_EXPRESSION_HPP
#include <variant>
#include <string>
#include <vector>
#include "utils/DeepPtr.hpp"
#include "Operator.hpp"

namespace mcmas {
  
  class Expression;
  class UnaryExpression;
  class BinaryExpression;
  class BoolLiteral;
  class Visitor;
  class ConstVisitor;

  class Expression {
    public:
      using Ptr = std::unique_ptr<Expression>;
      virtual void accept(Visitor& visitor) = 0;
      virtual void accept(ConstVisitor& visitor) const = 0;

      virtual Ptr clone() const = 0;

      std::string to_string() const;

      static Ptr And(Ptr&& left, Ptr&& right);
      static Ptr And(std::vector<Ptr>&& args);
      static Ptr Or(Ptr&& left, Ptr&& right);
      static Ptr Or(std::vector<Ptr>&& args);
      static Ptr Not(Ptr&& child);

      static Ptr Lt(Ptr&& left, Ptr&& right);
      static Ptr Leq(Ptr&& left, Ptr&& right);
      static Ptr Gt(Ptr&& left, Ptr&& right);
      static Ptr Geq(Ptr&& left, Ptr&& right);
      static Ptr Eq(Ptr&& left, Ptr&& right);
      static Ptr Neq(Ptr&& left, Ptr&& right);

      static Ptr Add(Ptr&& left, Ptr&& right);
      static Ptr Sub(Ptr&& left, Ptr&& right);
      static Ptr Div(Ptr&& left, Ptr&& right);
      static Ptr Mul(Ptr&& left, Ptr&& right);
      static Ptr BitAnd(Ptr&& left, Ptr&& right);
      static Ptr BitOr(Ptr&& left, Ptr&& right);
      static Ptr BitXor(Ptr&& left, Ptr&& right);
      static Ptr BitNot(Ptr&& child);

      static Ptr Bool(bool value);
      static Ptr Int(int value);

      static Ptr Id(const std::string& owner, const std::string& id);
      static Ptr Id(const std::string& id);
      
  };

  class BinaryExpression : public Expression {
    public:
      friend class Expression;
      BinaryExpression(Expression::Ptr&& left, Expression::Ptr&& right, BinaryOperator::Ptr&& op)
      : left(std::move(left)),
        right(std::move(right)),
        op(std::move(op))
      {}

      Expression::Ptr left;
      Expression::Ptr right;
      BinaryOperator::Ptr op;

      void accept(Visitor& visitor);
      void accept(ConstVisitor& visitor) const;

      Expression::Ptr clone() const;
  };

  class UnaryExpression : public Expression {
    public:
      friend class Expression;
      UnaryExpression(Expression::Ptr&& child, UnaryOperator::Ptr&& op)
      : child(std::move(child)),
        op(std::move(op))
      {}

      Expression::Ptr child;
      UnaryOperator::Ptr op;

      void accept(Visitor& visitor);
      void accept(ConstVisitor& visitor) const;

      Expression::Ptr clone() const;
  };

  class BoolLiteral : public Expression {
    public:
      friend class Expression;
      BoolLiteral(bool value) : value(value) {}

      bool value;

      void accept(Visitor& visitor);
      void accept(ConstVisitor& visitor) const;

      Expression::Ptr clone() const;
  };

  class IntLiteral : public Expression {
    public:
      friend class Expression;
      IntLiteral(int value) : value(value) {}

      int value;

      void accept(Visitor& visitor);
      void accept(ConstVisitor& visitor) const;

      Expression::Ptr clone() const;
  };

  class Identifier : public Expression {
    public:
      friend class Expression;
      Identifier(const std::string& owner, const std::string& id) : owner(owner), id(id) {}
      Identifier(const std::string& id) : id(id) {}

      std::string owner;
      std::string id;

      bool is_current_agent() const;
      bool is_environment_action() const;
      bool is_local_action() const;
      bool is_global_action() const;
      bool is_owner_action() const;
      bool is_action() const;

      void accept(Visitor& visitor);
      void accept(ConstVisitor& visitor) const;

      Expression::Ptr clone() const;
  };
}

#endif