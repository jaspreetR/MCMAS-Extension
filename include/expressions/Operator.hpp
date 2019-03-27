#ifndef MCMAS_OPERATOR_HPP
#define MCMAS_OPERATOR_HPP
#include <variant>
#include <string>

namespace mcmas {

  using EvalType = std::variant<int, bool>;

  class UnaryOperator {
    public:
      using Ptr = std::unique_ptr<UnaryOperator>;
      virtual EvalType apply(EvalType arg) = 0;
      virtual std::string getToken() = 0;
  };

  class BinaryOperator {
    public:
      using Ptr = std::unique_ptr<BinaryOperator>;
      virtual EvalType apply(EvalType left, EvalType right) = 0;
      virtual std::string getToken() = 0;
  };

  class AndOperator : public BinaryOperator{
    public:
      EvalType apply(EvalType left, EvalType right) {
        return {std::get<bool>(left) && std::get<bool>(right)};
      }

      std::string getToken() {
        return "and";
      } 
  };

  class OrOperator : public BinaryOperator {
    public:
      EvalType apply(EvalType left, EvalType right) {
        return {std::get<bool>(left) || std::get<bool>(right)};
      }

      std::string getToken() {
        return "or";
      } 
  };

  class NotOperator : public UnaryOperator {
    public:
      EvalType apply(EvalType child) {
        return {!std::get<bool>(child)};
      }

      std::string getToken() {
        return "!";
      } 
  };

  class LtOperator : public BinaryOperator {
    public:
      EvalType apply(EvalType left, EvalType right) {
        return {std::get<int>(left) < std::get<int>(right)};
      }

      std::string getToken() {
        return "<";
      } 
  };

  class LeqOperator : public BinaryOperator {
    public:
      EvalType apply(EvalType left, EvalType right) {
        return {std::get<int>(left) <= std::get<int>(right)};
      }

      std::string getToken() {
        return "<=";
      } 
  };

  class GtOperator : public BinaryOperator {
    public:
      EvalType apply(EvalType left, EvalType right) {
        return {std::get<int>(left) > std::get<int>(right)};
      }

      std::string getToken() {
        return ">";
      } 
  };

  class GeqOperator : public BinaryOperator {
    public:
      EvalType apply(EvalType left, EvalType right) {
        return {std::get<int>(left) >= std::get<int>(right)};
      }

      std::string getToken() {
        return ">=";
      } 
  };

  class EqOperator : public BinaryOperator {
    public:
      EvalType apply(EvalType left, EvalType right) {
        return {std::get<int>(left) == std::get<int>(right)};
      }

      std::string getToken() {
        return "=";
      } 
  };

  class NeqOperator : public BinaryOperator {
    public:
      EvalType apply(EvalType left, EvalType right) {
        return {std::get<int>(left) != std::get<int>(right)};
      }

      std::string getToken() {
        return "!=";
      } 
  };

  class AddOperator : public BinaryOperator {
    public:
      EvalType apply(EvalType left, EvalType right) {
        return {std::get<int>(left) + std::get<int>(right)};
      }

      std::string getToken() {
        return "+";
      } 
  };
  
  class SubOperator : public BinaryOperator {
    public:
      EvalType apply(EvalType left, EvalType right) {
        return {std::get<int>(left) - std::get<int>(right)};
      }

      std::string getToken() {
        return "-";
      } 
  };
  
  class MulOperator : public BinaryOperator {
    public:
      EvalType apply(EvalType left, EvalType right) {
        return {std::get<int>(left) * std::get<int>(right)};
      }

      std::string getToken() {
        return "*";
      } 
  };
  
  class DivOperator : public BinaryOperator {
    public:
      EvalType apply(EvalType left, EvalType right) {
        return {std::get<int>(left) / std::get<int>(right)};
      }

      std::string getToken() {
        return "/";
      } 
  };
  
  class BitAndOperator : public BinaryOperator {
    public:
      EvalType apply(EvalType left, EvalType right) {
        return {std::get<int>(left) & std::get<int>(right)};
      }

      std::string getToken() {
        return "&";
      } 
  };
  
  class BitOrOperator : public BinaryOperator {
    public:
      EvalType apply(EvalType left, EvalType right) {
        return {std::get<int>(left) | std::get<int>(right)};
      }

      std::string getToken() {
        return "|";
      } 
  };
  
  class BitXorOperator : public BinaryOperator {
    public:
      EvalType apply(EvalType left, EvalType right) {
        return {std::get<int>(left) ^ std::get<int>(right)};
      }

      std::string getToken() {
        return "^";
      } 
  };

  class BitNotOperator : public UnaryOperator {
    public:
      EvalType apply(EvalType child) {
        return {~std::get<int>(child)};
      }

      std::string getToken() {
        return "~";
      } 
  };
}

#endif