#ifndef MCMAS_OPERATOR_HPP
#define MCMAS_OPERATOR_HPP
#include <variant>
#include <string>
#include <type_traits>

namespace mcmas {

  using EvalType = std::variant<int, bool>;

  class UnaryOperator {
    public:
      using Ptr = std::unique_ptr<UnaryOperator>;
      virtual EvalType apply(EvalType arg) = 0;
      virtual std::string getToken() = 0;

      virtual Ptr clone() = 0;
  };

  class BinaryOperator {
    public:
      using Ptr = std::unique_ptr<BinaryOperator>;
      virtual EvalType apply(EvalType left, EvalType right) = 0;
      virtual std::string getToken() = 0;

      virtual Ptr clone() = 0;
  };

  class AndOperator : public BinaryOperator{
    public:
      EvalType apply(EvalType left, EvalType right) {
        return {std::get<bool>(left) && std::get<bool>(right)};
      }

      std::string getToken() {
        return "and";
      } 

      Ptr clone() {
        return Ptr(new std::remove_reference_t<decltype(*this)>());
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

      Ptr clone() {
        return Ptr(new std::remove_reference_t<decltype(*this)>());
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

      Ptr clone() {
        return Ptr(new std::remove_reference_t<decltype(*this)>());
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

      Ptr clone() {
        return Ptr(new std::remove_reference_t<decltype(*this)>());
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

      Ptr clone() {
        return Ptr(new std::remove_reference_t<decltype(*this)>());
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

      Ptr clone() {
        return Ptr(new std::remove_reference_t<decltype(*this)>());
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

      Ptr clone() {
        return Ptr(new std::remove_reference_t<decltype(*this)>());
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

      Ptr clone() {
        return Ptr(new std::remove_reference_t<decltype(*this)>());
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

      Ptr clone() {
        return Ptr(new std::remove_reference_t<decltype(*this)>());
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

      Ptr clone() {
        return Ptr(new std::remove_reference_t<decltype(*this)>());
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

      Ptr clone() {
        return Ptr(new std::remove_reference_t<decltype(*this)>());
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

      Ptr clone() {
        return Ptr(new std::remove_reference_t<decltype(*this)>());
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

      Ptr clone() {
        return Ptr(new std::remove_reference_t<decltype(*this)>());
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

      Ptr clone() {
        return Ptr(new std::remove_reference_t<decltype(*this)>());
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

      Ptr clone() {
        return Ptr(new std::remove_reference_t<decltype(*this)>());
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

      Ptr clone() {
        return Ptr(new std::remove_reference_t<decltype(*this)>());
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

      Ptr clone() {
        return Ptr(new std::remove_reference_t<decltype(*this)>());
      }
  };
}

#endif