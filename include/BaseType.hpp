#ifndef MCMAS_BASETYPE_HPP
#define MCMAS_BASETYPE_HPP
#include <variant>
#include <set>

namespace mcmas {

  struct BOOL {
  };

  struct ENUM {
    std::set<std::string> ids; 
  };

  struct RANGED_INT {
    int min;
    int max;
  };

  using BaseType = std::variant<BOOL, ENUM, RANGED_INT>;
}

#endif