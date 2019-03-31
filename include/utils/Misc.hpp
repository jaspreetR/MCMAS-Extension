#ifndef MCMAS_MISC_HPP
#define MCMAS_MISC_HPP
#include <string>

namespace mcmas {

  inline std::string generate_local_action(const std::string& action, int i, int j) {
    // could cache results in static var
    return action + "_" + std::to_string(i) + "_" + std::to_string(j);
  }

}

#endif