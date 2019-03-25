#ifndef MCMAS_OPERATORS_HPP
#define MCMAS_OPERATORS_HPP
#include <string>

namespace mcmas {

  template <typename Op>
  using ResultType = typename Op::ResultType;

namespace operators {

/*
namespace detail {
  struct BOOLEAN {};
  struct LOGIC {};
  struct ARITHMETIC {};
} // namespace detail
*/

  struct AND {
    using ResultType = bool;
    inline static const std::string token = "and";

    static ResultType apply(bool left, bool right) {
      return left && right;
    }
  };

  struct OR {
    using ResultType = bool;
    inline static const std::string token = "or";

    static ResultType apply(bool left, bool right) {
      return left || right;
    }
  };

  struct NOT {
    using ResultType = bool;
    inline static const std::string token = "!";

    static ResultType apply(bool arg) {
      return !arg;
    }
  };

  struct LEQ {
    using ResultType = bool;
    inline static const std::string token = "<=";

    static ResultType apply(int left, int right) {
      return left <= right;
    }
  };

  struct LT {
    using ResultType = bool;
    inline static const std::string token = "<";

    static ResultType apply(int left, int right) {
      return left < right;
    }
  };

  struct GEQ {
    using ResultType = bool;
    inline static const std::string token = ">=";

    static ResultType apply(int left, int right) {
      return left >= right;
    }
  };

  struct GT {
    using ResultType = bool;
    inline static const std::string token = ">";

    static ResultType apply(int left, int right) {
      return left > right;
    }
  };

  struct EQ {
    using ResultType = bool;
    inline static const std::string token = "=";

    static ResultType apply(int left, int right) {
      return left == right;
    }
  };

  struct NEQ {
    using ResultType = bool;
    inline static const std::string token = "!=";

    static ResultType apply(int left, int right) {
      return left != right;
    }
  };

  struct ADD {
    using ResultType = int;
    inline static const std::string token = "+";

    static ResultType apply(int left, int right) {
      return left + right;
    }
  };

  struct SUB {
    using ResultType = int;
    inline static const std::string token = "-";

    static ResultType apply(int left, int right) {
      return left - right;
    }
  };

  struct MUL {
    using ResultType = int;
    inline static const std::string token = "*";

    static ResultType apply(int left, int right) {
      return left * right;
    }
  };

  struct DIV {
    using ResultType = int;
    inline static const std::string token = "/";

    static ResultType apply(int left, int right) {
      return left / right;
    }
  };

  struct BITAND {
    using ResultType = int;
    inline static const std::string token = "&";

    static ResultType apply(int left, int right) {
      return left & right;
    }
  };

  struct BITOR {
    using ResultType = int;
    inline static const std::string token = "|";

    static ResultType apply(int left, int right) {
      return left | right;
    }
  };

  struct BITXOR {
    using ResultType = int;
    inline static const std::string token = "^";

    static ResultType apply(int left, int right) {
      return left ^ right;
    }
  };

  struct BITNOT {
    using ResultType = int;
    inline static const std::string token = "~";

    static ResultType apply(int child) {
      return ~child;
    }
  };

} // namespace operators
} // namespace mcmas

#endif