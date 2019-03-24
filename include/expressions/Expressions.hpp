#ifndef MCMAS_EXPRESSIONS_HPP  
#define MCMAS_EXPRESSIONS_HPP  
#include <string>
#include <variant>
#include "utils/DeepPtr.hpp"
#include "Operators.hpp"

namespace mcmas {
  template <typename Child, typename Op>
  class BinaryExpr {
    public:
      DeepPtr<Child> left;
      DeepPtr<Child> right;

      BinaryExpr() = default;

      template <typename Left, typename Right>
      BinaryExpr(Left&& left, Right&& right) {
        set_left(std::forward<Left>(left));
        set_right(std::forward<Right>(right));
      }

      template <typename... Args>
      void set_left(Args&&... child_args) {
        left.reset(new Child(std::forward<Args>(child_args)...));
      }

      template <typename... Args>
      void set_right(Args&&... child_args) {
        right.reset(new Child(std::forward<Args>(child_args)...));
      }

      template <typename Visitor>
      auto accept(Visitor&& visitor) {
        return visitor.visit(*this);
      }

      std::string to_string() {
        return "(" + left->to_string() + ") " + Op::token + " (" + right->to_string() + ")";
      };   

      auto evaluate() {
        auto left_result = left->evaluate();
        auto right_result = right->evaluate();
        return Op::apply(left_result, right_result); 
      }
  };

  template <typename Child, typename Op>
  class UnaryExpr {
    public:
      DeepPtr<Child> child;

      UnaryExpr() = default;

      template <typename Arg>
      UnaryExpr(Arg&& arg) {
        set_child(std::forward<Arg>(arg));
      }

      template <typename... Args>
      void set_child(Args&&... child_args) {
        child.reset(new Child(std::forward<Args>(child_args)...));
      }

      template <typename Visitor>
      auto accept(Visitor&& visitor) {
        return visitor.visit(*this);
      }

      std::string to_string() {
        return Op::token + " (" + child->to_string() + ")";
      }

      auto evaluate() {
        auto child_result = child->evaluate();
        return Op::apply(child_result);
      }
  };

  class Bool {
    public:
      bool value;

      Bool() = default;
      explicit Bool(bool value) : value(value){}

      std::string to_string() {
        return value ? "true" : "false";
      }

      bool evaluate() {
        return value;
      }
  };

  class Int {
    public:
      int value;

      Int() = default;
      explicit Int(int value) : value(value){}

      std::string to_string() {
        return std::to_string(value);
      }

      int evaluate() {
        return value;
      }
  };

  class Identifier {
    public:
      std::string value;

      Identifier() = default;
      explicit Identifier(const std::string& value) : value(value){}

      std::string to_string() {
        return value;
      }

      // TODO
      int evaluate() {
        return 0;
      }
  };

  class BoolExpr {
    private:
      using AND = BinaryExpr<BoolExpr, operators::AND>;
      using OR = BinaryExpr<BoolExpr, operators::OR>;
      using NOT = UnaryExpr<BoolExpr, operators::NOT>;

      BoolExpr(AND&& expr) : expr(std::forward<AND>(expr)){}
      BoolExpr(OR&& expr) : expr(std::forward<OR>(expr)){}
      BoolExpr(NOT&& expr) : expr(std::forward<NOT>(expr)){}
      
    public:
      // allow implicit casting from mcmas::Bool to mcmas::BoolExpr
      BoolExpr(Bool&& expr) : expr(std::forward<Bool>(expr)){}

      static BoolExpr And(BoolExpr&& left, BoolExpr&& right) {
        return BoolExpr(AND(std::forward<BoolExpr>(left), std::forward<BoolExpr>(right)));
      }

      static BoolExpr Or(BoolExpr&& left, BoolExpr&& right) {
        return BoolExpr(OR(std::forward<BoolExpr>(left), std::forward<BoolExpr>(right)));
      }

      static BoolExpr Not(BoolExpr&& child) {
        return BoolExpr(NOT(std::forward<BoolExpr>(child)));
      }
  
      std::variant<AND, OR, NOT, Bool> expr;

      template <typename Visitor>
      auto accept(Visitor&& visitor) {
        auto func = [&](auto&& expr) { return visitor.visit(expr); };
        return std::visit(func, expr);
      }

      std::string to_string() {
        auto to_string_visitor = [](auto&& expr){ return expr.to_string(); };
        return std::visit(to_string_visitor, expr);
      }

      bool evaluate() {
        auto evaluate_visitor = [](auto&& expr){ return expr.evaluate(); };
        return std::visit(evaluate_visitor, expr);
      }
  };

  class LogicExpr {
    private:
      using LEQ = BinaryExpr<LogicExpr, operators::LEQ>;
      using LT = BinaryExpr<LogicExpr, operators::LT>;
      using GEQ = BinaryExpr<LogicExpr, operators::GEQ>;
      using GT = BinaryExpr<LogicExpr, operators::GT>;
      using EQ = BinaryExpr<LogicExpr, operators::EQ>;
      using NEQ = BinaryExpr<LogicExpr, operators::NEQ>;

      LogicExpr(LEQ&& expr) : expr(std::forward<LEQ>(expr)){}
      LogicExpr(LT&& expr) : expr(std::forward<LT>(expr)){}
      LogicExpr(GEQ&& expr) : expr(std::forward<GEQ>(expr)){}
      LogicExpr(GT&& expr) : expr(std::forward<GT>(expr)){}
      LogicExpr(EQ&& expr) : expr(std::forward<EQ>(expr)){}
      LogicExpr(NEQ&& expr) : expr(std::forward<NEQ>(expr)){}
      
    public:
      static LogicExpr Leq(LogicExpr&& left, LogicExpr&& right) {
        return LogicExpr(LEQ(std::forward<LogicExpr>(left), std::forward<LogicExpr>(left)));
      }

      static LogicExpr Lt(LogicExpr&& left, LogicExpr&& right) {
        return LogicExpr(LT(std::forward<LogicExpr>(left), std::forward<LogicExpr>(left)));
      }

      static LogicExpr Geq(LogicExpr&& left, LogicExpr&& right) {
        return LogicExpr(GEQ(std::forward<LogicExpr>(left), std::forward<LogicExpr>(left)));
      }

      static LogicExpr Gt(LogicExpr&& left, LogicExpr&& right) {
        return LogicExpr(GT(std::forward<LogicExpr>(left), std::forward<LogicExpr>(left)));
      }

      static LogicExpr Eq(LogicExpr&& left, LogicExpr&& right) {
        return LogicExpr(EQ(std::forward<LogicExpr>(left), std::forward<LogicExpr>(left)));
      }

      static LogicExpr Neq(LogicExpr&& left, LogicExpr&& right) {
        return LogicExpr(NEQ(std::forward<LogicExpr>(left), std::forward<LogicExpr>(left)));
      }
  
      std::variant<LEQ, LT, GEQ, GT, EQ, NEQ> expr;

      template <typename Visitor>
      auto accept(Visitor&& visitor) {
        return std::visit([&](auto&& expr){ return visitor.visit(expr); }, expr);
      }

      std::string to_string() {
        auto to_string_visitor = [](auto&& expr){ return expr.to_string(); };
        return std::visit(to_string_visitor, expr);
      }

      bool evaluate() {
        auto evaluate_visitor = [](auto&& expr){ return expr.evaluate(); };
        return std::visit(evaluate_visitor, expr);
      }
  };


}

#endif