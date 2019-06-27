#include <string>
#include <iostream>
#include <fstream>

#include "parser/parser.hpp"
#include "visitors/FormulaTDVisitor.hpp"

int main(int argc, char* argv[]) {

  if (argc == 5) {

    auto ss = mcmas::parser::do_parse(std::string(argv[1]), atoi(argv[3]), (bool)atoi(argv[4]));

    if (ss) {
      auto file_name = std::string(argv[2]);
      std::ofstream fs; 
      fs.open(file_name);
      ss->print(fs);
      fs.close();

      mcmas::FormulaTDVisitor temporal_depth_visitor;
      ss->formulas[0].formula->accept(temporal_depth_visitor);
      std::cout << "Temporal depth of the formula is " << temporal_depth_visitor.result << std::endl;
    }

  } else {
    std::cout << "Invalid args" << std::endl;
    std::cout << "Arg 1 - string - input SISPL file path" << std::endl;
    std::cout << "Arg 2 - string - output ISPL file path" << std::endl;
    std::cout << "Arg 3 - int    - emergence threshold calculated by MCMAS to generate concrete model or -1 to generate abstract model" << std::endl;
    std::cout << "Arg 4 - bool   - 0 to generate model with metadata or 1 to generate without" << std::endl;
  }
  
}