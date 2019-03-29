#include "SwarmAgent.hpp"
#include "Overload.hpp"

namespace mcmas {

  void SwarmAgent::add_variable(const std::string& var_name, BaseType var_type) {
    vars[var_name] = var_type;
  }

  void SwarmAgent::add_actions(const std::vector<std::string>& actions) {
    this->actions = actions;
  }

  void SwarmAgent::add_protocol_line(Expression::Ptr&& condition, const std::vector<std::string>& actions) {
    ProtocolLine protocol_line(std::move(condition), actions);
    protocol.lines.emplace_back(std::move(protocol_line));
  }

  void SwarmAgent::add_evolution_line(Expression::Ptr&& result, Expression::Ptr&& condition) {
    EvolutionLine evolution_line(std::move(result), std::move(condition));
    evolution.lines.emplace_back(std::move(evolution_line));
  }

  std::string SwarmAgent::to_string() const {
    std::string vars = "Vars : ";

    for (auto& [id, type] : vars) {
      std::string type_string = std::visit(Overload {
        [](BOOL){ 
          return "boolean";
        },
        [](ENUM e){ 
          std::string enum_ids;
          for (const auto& id : e.ids) {
            enum_ids += " " + id + ",";
          };
          enum_ids.pop_back();
          return enum_ids;
        },
        [](RANGED_INT i){
          return i.min + ".." + i.max;
        }
      }, type);
      vars += id + " : " + type_string + '\n';
    };

    vars += " end Vars " + '\n';

  }

}