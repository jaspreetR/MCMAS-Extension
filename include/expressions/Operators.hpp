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

    static bool apply(bool left, bool right) {
      return left && right;
    }
  };

  struct OR {
    using ResultType = bool;
    inline static const std::string token = "or";

    static bool apply(bool left, bool right) {
      return left || right;
    }
  };

  struct NOT {
    using ResultType = bool;
    inline static const std::string token = "!";

    static bool apply(bool arg) {
      return !arg;
    }
  };

  struct LEQ {
    using ResultType = bool;
    inline static const std::string token = "<=";

    static bool apply(int left, int right) {
      return left <= right;
    }
  };

  struct LT {
    using ResultType = bool;
    inline static const std::string token = "<";

    static bool apply(int left, int right) {
      return left < right;
    }
  };

  struct GEQ {
    using ResultType = bool;
    inline static const std::string token = ">=";

    static bool apply(int left, int right) {
      return left >= right;
    }
  };

  struct GT {
    using ResultType = bool;
    inline static const std::string token = ">";

    static bool apply(int left, int right) {
      return left > right;
    }
  };

  struct EQ {
    using ResultType = bool;
    inline static const std::string token = "=";

    static bool apply(int left, int right) {
      return left == right;
    }
  };

  struct NEQ {
    using ResultType = bool;
    inline static const std::string token = "!=";

    static bool apply(int left, int right) {
      return left != right;
    }
  };
} // namespace operators
} // namespace mcmas

#endif