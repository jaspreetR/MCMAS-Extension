#include <string>
#include <iostream>
#include <fstream>

#include "parser/parser.hpp"
#include "visitors/FormulaTDVisitor.hpp"

void print_error_message() {
  std::cout << "Args should be the following:" << std::endl;
  std::cout << "  -abstract <input SISPL file path> <output ISPL file path>" << std::endl;
  std::cout << "  -abstract_with_meta <input SISPL file path> <output ISPL file path>" << std::endl;
  std::cout << "  -concrete <num of additional concrete agents> <input SISPL file path> <output ISPL file path>" << std::endl;
}

int main(int argc, char* argv[]) {
  std::optional<mcmas::SwarmSystem> ss;
  std::string output_ispl_file;

  if (argc == 4) {
    if (std::string(argv[1]) == "-abstract") {
      ss = mcmas::parser::do_parse(std::string(argv[2]), -1, false);
    } else if (std::string(argv[1]) == "-abstract_with_meta") {
      ss = mcmas::parser::do_parse(std::string(argv[2]), -1, true);
    } else {
      print_error_message();
      return -1;
    }
    output_ispl_file = std::string(argv[3]);
  } else if (argc == 5) {
    if (std::string(argv[1]) == "-concrete") {
      ss = mcmas::parser::do_parse(std::string(argv[3]), atoi(argv[2]), false);
    } else {
      print_error_message();
      return -1;
    }
    output_ispl_file = std::string(argv[4]);
  } else {
    print_error_message();
    return -1;
  }
    
  std::ofstream fs; 
  fs.open(output_ispl_file);
  ss->print(fs);
  fs.close();

  mcmas::FormulaTDVisitor temporal_depth_visitor;
  ss->formulas[0].formula->accept(temporal_depth_visitor);
  std::cout << "Temporal depth of the formula is " << temporal_depth_visitor.result << std::endl;
  return 0;
}