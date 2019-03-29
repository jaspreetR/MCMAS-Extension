#ifndef MCMAS_PROTOCOL_HPP
#define MCMAS_PROTOCOL_HPP
#include <vector>
#include <string>
#include <optional>
#include "ProtocolLine.hpp"

namespace mcmas {
  class Protocol {
    public:
      std::vector<ProtocolLine> lines;
      std::vector<std::string> other_actions;
  };
}

#endif