#include "SwarmSystem.hpp"

namespace mcmas {

  SwarmSystem::SwarmSystem(const SwarmAgent& environment, 
                           const SwarmAgent& agent, 
                           int num_agents, 
                           const Evaluation& evaluation) {
    
    this->environment = environment.clone();
    
    concrete_agents.reserve(num_agents);
    for 

    // add new visitor for changing owner in ids - needed for init states
    // generate new concrete_agents and change ids - need to change name and init states
    // generate abstract agents
    // apply global action transform to all agents
    // generate init states condition
    // generate new atoms for each concrete agent - maybe check if atom contains agent name
    // given formulae with given placeholders, substitute with agent1, agent2 etc
  }

}