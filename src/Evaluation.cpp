#include "Evaluation.hpp"

namespace mcmas {

  std::string Evaluation::to_string() const {
    std::string result = "Evaluation\n";

    for (const auto& line : lines) {
      result += line.to_string() + ";\n";
    }

    result += "end Evaluation\n";

    return result;
  }

  Evaluation Evaluation::clone() const {
    Evaluation result;
    result.lines.reserve(lines.size());

    for (const auto& line : lines) {
      result.lines.emplace_back(line.clone());
    }

    return result;
  }

}
