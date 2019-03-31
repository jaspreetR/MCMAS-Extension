#ifndef MCMAS_BASETYPE_HPP
#define MCMAS_BASETYPE_HPP
#include <variant>
#include <set>
#include <string>
#include "utils/Overload.hpp"

namespace mcmas {

  struct BOOL {
  };

  struct ENUM {
    std::set<std::string> ids; 
  };

  struct RANGED_INT {
    int min;
    int max;

    RANGED_INT() = default;
    RANGED_INT(int min, int max) : min(min), max(max) {}
  };

  using BaseType = std::variant<BOOL, ENUM, RANGED_INT>;

  std::string to_string(const BaseType& type);
}

#endif