# MCMAS-Extension

To build the project, a C++17 compliant compiler is needed. Simply call "make" from the command line.

To run the transpiler, run the built executable with options of the following format:

1. ./abstract_generator -abstract "input SISPL file" "output ISPL file path"
2. ./abstract_generator -abstract_with_meta "input SISPL file" "output ISPL file path"
3. ./abstract_generator -concrete "number of addition concrete agents" "input SISPL file" "output ISPL file path"

Format 1 creates an ISPL file containing the abstract model WITHOUT transition metadata corresponding to the given SISPL model

Format 2 creates an ISPL file containing the abstract model WITH transition metadata corresponding to the given SISPL model

Format 3 creates an ISPL file containing the concrete model with the given additional number of agents corresponding to the given SISPL model e.g ./abstract_generator -concrete 10 model.sispl concrete_model.ispl. 

This additional number of agents is calculated by the modified version of MCMAS found at https://github.com/jaspreetR/MCMAS-SS

Example SISPL files are in the "examples" folder. These models are similar to the models found in my report.

Typical usage of this transpiler would be as follows:

./abstract_generator -abstract_with_metadata swarm.sispl abstract.ispl


./mcmas -et 2 abstract.ispl 

(NOTE: the value of 2 which is the temporal depth of the formula is given by this transpiler (i.e the previous command) as console output)

./abstract_generator -concrete 5 swarm.sispl concrete.ispl

(NOTE: the value of 5 which is the emergence threshold is given by the modified version of MCMAS (i.e the previous command) as console output)

./mcmas concrete.ispl

This final command returns the result of the formula when applied to the given model and tells us if it is an emergent behaviour.