#ifndef MCMAS_ABSTRACTAGENT_HPP
#define MCMAS_ABSTRACTAGENT_HPP
#include "SwarmAgent.hpp"
#include "AgentState.hpp"

namespace mcmas {
  class AbstractAgent : public SwarmAgent {
    public:
      const AgentState state;
      //const SwarmAgent& concrete_agent;
      std::map<std::string, std::vector<std::string>> action_register;

      AbstractAgent(const AgentState& state, const SwarmAgent& concrete_agent, Expression::Ptr&& transition, int id);

      static std::string generate_abstract_agent_name(const std::string& concrete_name, int i);
      
 };

}

#endif