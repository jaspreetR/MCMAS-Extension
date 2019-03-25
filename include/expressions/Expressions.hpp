#ifndef MCMAS_EXPRESSIONS_HPP  
#define MCMAS_EXPRESSIONS_HPP  
#include <string>
#include <variant>
#include "utils/DeepPtr.hpp"
#include "Operators.hpp"

namespace mcmas {

  class BoolExpr;
  class LogicExpr;
  class ArithmeticExpr;


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
  };

  class Bool {
    public:
      bool value;

      Bool() = default;
      explicit Bool(bool value) : value(value){}
  };

  class Int {
    public:
      int value;

      Int() = default;
      explicit Int(int value) : value(value){}
  };

  class Identifier {
    public:
      std::string value;

      Identifier() = default;
      explicit Identifier(const std::string& value) : value(value){}
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
  };

  class LogicExpr {
    private:
      using LEQ = BinaryExpr<ArithmeticExpr, operators::LEQ>;
      using LT = BinaryExpr<ArithmeticExpr, operators::LT>;
      using GEQ = BinaryExpr<ArithmeticExpr, operators::GEQ>;
      using GT = BinaryExpr<ArithmeticExpr, operators::GT>;
      using EQ = BinaryExpr<ArithmeticExpr, operators::EQ>;
      using NEQ = BinaryExpr<ArithmeticExpr, operators::NEQ>;

      LogicExpr(LEQ&& expr) : expr(std::forward<LEQ>(expr)){}
      LogicExpr(LT&& expr) : expr(std::forward<LT>(expr)){}
      LogicExpr(GEQ&& expr) : expr(std::forward<GEQ>(expr)){}
      LogicExpr(GT&& expr) : expr(std::forward<GT>(expr)){}
      LogicExpr(EQ&& expr) : expr(std::forward<EQ>(expr)){}
      LogicExpr(NEQ&& expr) : expr(std::forward<NEQ>(expr)){}
      
    public:
      static LogicExpr Leq(ArithmeticExpr&& left, ArithmeticExpr&& right) {
        return LogicExpr(LEQ(std::forward<ArithmeticExpr>(left), std::forward<ArithmeticExpr>(right)));
      }

      static LogicExpr Lt(ArithmeticExpr&& left, ArithmeticExpr&& right) {
        return LogicExpr(LT(std::forward<ArithmeticExpr>(left), std::forward<ArithmeticExpr>(right)));
      }

      static LogicExpr Geq(ArithmeticExpr&& left, ArithmeticExpr&& right) {
        return LogicExpr(GEQ(std::forward<ArithmeticExpr>(left), std::forward<ArithmeticExpr>(right)));
      }

      static LogicExpr Gt(ArithmeticExpr&& left, ArithmeticExpr&& right) {
        return LogicExpr(GT(std::forward<ArithmeticExpr>(left), std::forward<ArithmeticExpr>(right)));
      }

      static LogicExpr Eq(ArithmeticExpr&& left, ArithmeticExpr&& right) {
        return LogicExpr(EQ(std::forward<ArithmeticExpr>(left), std::forward<ArithmeticExpr>(right)));
      }

      static LogicExpr Neq(ArithmeticExpr&& left, ArithmeticExpr&& right) {
        return LogicExpr(NEQ(std::forward<ArithmeticExpr>(left), std::forward<ArithmeticExpr>(right)));
      }
  
      std::variant<LEQ, LT, GEQ, GT, EQ, NEQ> expr;

      template <typename Visitor>
      auto accept(Visitor&& visitor) {
        auto func = [&](auto&& expr) { return visitor.visit(expr); };
        return std::visit(func, expr);
      }
  };

  class ArithmeticExpr {
    private:
      using ADD = BinaryExpr<ArithmeticExpr, operators::ADD>;
      using SUB = BinaryExpr<ArithmeticExpr, operators::SUB>;
      using MUL = BinaryExpr<ArithmeticExpr, operators::MUL>;
      using DIV = BinaryExpr<ArithmeticExpr, operators::DIV>;
      using BITAND= BinaryExpr<ArithmeticExpr, operators::BITAND>;
      using BITOR = BinaryExpr<ArithmeticExpr, operators::BITOR>;
      using BITXOR = BinaryExpr<ArithmeticExpr, operators::BITXOR>;
      using BITNOT = UnaryExpr<ArithmeticExpr, operators::BITNOT>;

      ArithmeticExpr(ADD&& expr) : expr(std::forward<ADD>(expr)){}
      ArithmeticExpr(SUB&& expr) : expr(std::forward<SUB>(expr)){}
      ArithmeticExpr(MUL&& expr) : expr(std::forward<MUL>(expr)){}
      ArithmeticExpr(DIV&& expr) : expr(std::forward<DIV>(expr)){}
      ArithmeticExpr(BITAND&& expr) : expr(std::forward<BITAND>(expr)){}
      ArithmeticExpr(BITOR&& expr) : expr(std::forward<BITOR>(expr)){}
      ArithmeticExpr(BITXOR&& expr) : expr(std::forward<BITXOR>(expr)){}
      ArithmeticExpr(BITNOT&& expr) : expr(std::forward<BITNOT>(expr)){}
      
    public:
      // allow implicit cast from mcmas::Int
      ArithmeticExpr(Int&& expr) : expr(std::forward<Int>(expr)){}

      static ArithmeticExpr Add(ArithmeticExpr&& left, ArithmeticExpr&& right) {
        return ArithmeticExpr(ADD(std::forward<ArithmeticExpr>(left), std::forward<ArithmeticExpr>(right)));
      }

      static ArithmeticExpr Sub(ArithmeticExpr&& left, ArithmeticExpr&& right) {
        return ArithmeticExpr(SUB(std::forward<ArithmeticExpr>(left), std::forward<ArithmeticExpr>(right)));
      }

      static ArithmeticExpr Mul(ArithmeticExpr&& left, ArithmeticExpr&& right) {
        return ArithmeticExpr(MUL(std::forward<ArithmeticExpr>(left), std::forward<ArithmeticExpr>(right)));
      }

      static ArithmeticExpr Div(ArithmeticExpr&& left, ArithmeticExpr&& right) {
        return ArithmeticExpr(DIV(std::forward<ArithmeticExpr>(left), std::forward<ArithmeticExpr>(right)));
      }

      static ArithmeticExpr BitAnd(ArithmeticExpr&& left, ArithmeticExpr&& right) {
        return ArithmeticExpr(BITAND(std::forward<ArithmeticExpr>(left), std::forward<ArithmeticExpr>(right)));
      }

      static ArithmeticExpr BitOr(ArithmeticExpr&& left, ArithmeticExpr&& right) {
        return ArithmeticExpr(BITOR(std::forward<ArithmeticExpr>(left), std::forward<ArithmeticExpr>(right)));
      }

      static ArithmeticExpr BitXor(ArithmeticExpr&& left, ArithmeticExpr&& right) {
        return ArithmeticExpr(BITXOR(std::forward<ArithmeticExpr>(left), std::forward<ArithmeticExpr>(right)));
      }

      static ArithmeticExpr BitNot(ArithmeticExpr&& child) {
        return ArithmeticExpr(BitNot(std::forward<ArithmeticExpr>(child)));
      }
  
      std::variant<ADD, SUB, MUL, DIV, BITAND, BITOR, BITXOR, BITNOT, Int> expr;

      template <typename Visitor>
      auto accept(Visitor&& visitor) {
        auto func = [&](auto&& expr) { return visitor.visit(expr); };
        return std::visit(func, expr);
      }
  };

}

#endif