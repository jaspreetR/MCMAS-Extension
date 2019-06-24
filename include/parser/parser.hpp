#ifndef MCMAS_PARSER_HPP
#define MCMAS_PARSE_HPP
#include "parser/pegtl.hpp"
#include "expressions/Expression.hpp"

namespace mcmas {
namespace parser {

  using namespace tao;

  template< typename Key >
  struct key : pegtl::seq< Key, pegtl::not_at< pegtl::identifier_other > > {};

  struct true_str : TAO_PEGTL_STRING("true") {};
  struct false_str : TAO_PEGTL_STRING("false") {};
  struct agent_str : TAO_PEGTL_STRING("Agent") {};
  struct actions_str : TAO_PEGTL_STRING("Actions") {};
  struct protocol_str : TAO_PEGTL_STRING("Protocol") {};
  struct evolution_str : TAO_PEGTL_STRING("Evolution") {};
  struct evaluation_str : TAO_PEGTL_STRING("Evaluation") {};
  struct initstate_str : TAO_PEGTL_STRING("InitState") {};
  struct formulae_str : TAO_PEGTL_STRING("Formulae") {};
  struct end_str : TAO_PEGTL_STRING("end") {};
  struct vars_str : TAO_PEGTL_STRING("Vars") {};
  struct boolean_str : TAO_PEGTL_STRING("boolean") {};
  struct or_str : TAO_PEGTL_STRING("or") {};
  struct and_str : TAO_PEGTL_STRING("and") {};
  struct if_str : TAO_PEGTL_STRING("if") {};

  struct str_keyword : pegtl::sor< true_str, false_str, agent_str, actions_str, protocol_str, 
                                   evolution_str, evaluation_str, initstate_str, formulae_str, 
                                   end_str, vars_str, boolean_str, and_str, or_str, if_str > {};

  struct true_literal : key< true_str > {};
  struct false_literal : key< false_str > {};
  struct agent_literal : key< agent_str > {};
  struct actions_literal : key< actions_str > {};
  struct protocol_literal : key< protocol_str > {};
  struct evolution_literal : key< evolution_str > {};
  struct evaluation_literal : key< evaluation_str > {};
  struct initstate_literal : key< initstate_str > {};
  struct formulae_literal : key< formulae_str > {};
  struct end_literal : key< end_str > {};
  struct vars_literal : key< vars_str > {};
  struct boolean_literal : key< boolean_str > {};
  struct or_literal : key< or_str > {};
  struct and_literal : key< and_str > {};
  struct if_literal : key< if_str > {};

  struct single_id : pegtl::seq< pegtl::not_at< key< str_keyword > >, pegtl::identifier > {};
  struct qual_id : pegtl::seq< single_id, pegtl::if_must< pegtl::one< '.' >, single_id > > {};
  struct id : pegtl::sor< qual_id, single_id > {};

  struct number : pegtl::seq< pegtl::opt< pegtl::one< '-' > >, pegtl::plus< pegtl::digit > > {};

  struct var_value : pegtl::sor< true_literal, false_literal, id, number > {};

  struct open_bracket : pegtl::seq< pegtl::one< '(' >, pegtl::star< pegtl::space > > {};
  struct close_bracket : pegtl::seq< pegtl::star< pegtl::space >, pegtl::one< ')' > > {};
  struct open_curly : pegtl::seq< pegtl::one< '{' >, pegtl::star< pegtl::space > > {};
  struct close_curly : pegtl::seq< pegtl::star< pegtl::space >, pegtl::one< '}' > > {};

  ////////////////////////////
  // Expression Rules
  ////////////////////////////

  struct and_op : and_literal {};
  struct or_op : or_literal {};
  struct not_op : TAO_PEGTL_STRING("!") {};

  struct lt_op : TAO_PEGTL_STRING("<") {};
  struct leq_op : TAO_PEGTL_STRING("<=") {};
  struct gt_op : TAO_PEGTL_STRING(">") {};
  struct geq_op : TAO_PEGTL_STRING(">=") {};
  struct eq_op : TAO_PEGTL_STRING("=") {};
  struct neq_op : TAO_PEGTL_STRING("!=") {};

  struct bitor_op : TAO_PEGTL_STRING("|") {};
  struct bitxor_op : TAO_PEGTL_STRING("^") {};
  struct bitand_op : TAO_PEGTL_STRING("&") {};
  struct bitnot_op : TAO_PEGTL_STRING("~") {};

  struct add_op : TAO_PEGTL_STRING("+") {};
  struct sub_op : TAO_PEGTL_STRING("-") {};
  struct mul_op : TAO_PEGTL_STRING("*") {};
  struct div_op : TAO_PEGTL_STRING("/") {};

  template <typename Rule>
  using pad_ws = pegtl::pad< Rule, pegtl::space >;

  template <typename Rule>
  using bracketed = pegtl::if_must< open_bracket, Rule, close_bracket >;

  ////////////////////////////
  // Expression Rules
  ////////////////////////////

  struct bool_expr;
  struct bool_term;
  struct bool_factor;
  struct bool_element;
  struct logic_expr;
  struct bit_expr;
  struct bit_term;
  struct bit_factor;
  struct bit_element;
  struct arith_expr;
  struct arith_term;
  struct arith_element;

  struct or_expr : pegtl::seq< bool_term, pad_ws< or_op >, bool_expr > {};
  struct bool_expr : pegtl::sor< or_expr, bool_term> {};
  
  struct and_expr : pegtl::seq< bool_factor, pad_ws< and_op >, bool_term > {};
  struct bool_term : pegtl::sor< and_expr, bool_factor > {};

  struct not_expr : pegtl::seq< pad_ws< not_op >, bool_element > {};
  struct bool_factor : pegtl::sor< not_expr, bool_element > {};

  struct bool_element : pegtl::sor< bracketed< bool_expr >, logic_expr > {};

  struct lt_expr : pegtl::seq< bit_expr, pad_ws< lt_op >, bit_expr > {};
  struct leq_expr : pegtl::seq< bit_expr, pad_ws< leq_op >, bit_expr > {};
  struct gt_expr : pegtl::seq< bit_expr, pad_ws< gt_op >, bit_expr > {};
  struct geq_expr : pegtl::seq< bit_expr, pad_ws< geq_op >, bit_expr > {};
  struct eq_expr : pegtl::seq< bit_expr, pad_ws< eq_op >, bit_expr > {};
  struct neq_expr : pegtl::seq< bit_expr, pad_ws< neq_op >, bit_expr > {};
  struct logic_expr : pegtl::sor< lt_expr, leq_expr, gt_expr, geq_expr, eq_expr, neq_expr > {};
   
  struct bitor_expr : pegtl::seq< bit_term, pad_ws< bitor_op >, bit_expr > {};
  struct bitxor_expr : pegtl::seq< bit_term, pad_ws< bitxor_op >, bit_expr > {};
  struct bit_expr : pegtl::sor< bitor_expr, bitxor_expr, bit_term> {};

  struct bitand_expr : pegtl::seq< bit_factor, pad_ws< bitand_op >, bit_term > {};
  struct bit_term : pegtl::sor< bitand_expr, bit_factor> {};

  struct bitnot_expr : pegtl::seq< pad_ws< bitnot_op >, bit_element > {};
  struct bit_factor : pegtl::sor< bitnot_expr, bit_element> {};

  struct bit_element : pegtl::sor< bracketed< bit_expr >, arith_expr > {};

  struct add_expr : pegtl::seq< arith_term, pad_ws< add_op >, arith_expr > {};
  struct sub_expr : pegtl::seq< arith_term, pad_ws< sub_op >, arith_expr > {};
  struct arith_expr : pegtl::sor< add_expr, sub_expr, arith_term > {};

  struct mul_expr : pegtl::seq< arith_element, pad_ws< mul_op >, arith_term > {};
  struct div_expr : pegtl::seq< arith_element, pad_ws< div_op >, arith_term > {};
  struct arith_term : pegtl::sor< mul_expr, div_expr, arith_element > {};

  struct arith_element : pegtl::sor< bracketed< arith_expr >, var_value > {};

  //////////////////////////////////

  struct bool_var_def : pegtl::seq< single_id, pad_ws< pegtl::one< ':' > >, boolean_literal > {};
  struct int_var_def : pegtl::seq< single_id, pad_ws< pegtl::one< ':' > >, pegtl::if_must< number, pad_ws< pegtl::two< '.' > >, number > > {};
  struct one_var_def : pegtl::seq< pegtl::sor< bool_var_def, int_var_def >, pad_ws< pegtl::one< ';' > > > {};
  struct vars_def : pegtl::if_must< vars_literal, pad_ws< pegtl::opt< pegtl::one< ':' > > >, pegtl::star< one_var_def >, pad_ws< end_literal >, vars_literal > {}; 

  struct initstate_def : pegtl::if_must< initstate_literal, pad_ws< pegtl::opt< pegtl::one< ':' > > >, bool_expr, pad_ws< pegtl::one< ';' > >, pad_ws< end_literal >, initstate_literal > {};

  struct action_def : pegtl::if_must< actions_literal, pad_ws< eq_op >, open_curly, pegtl::list_must< single_id, pegtl::one< ',' >, pegtl::space >, pad_ws< close_curly >, pegtl::one< ';' > > {}; 

  struct protocol_line : pegtl::if_must< bool_expr, pad_ws< pegtl::one< ':' > >, open_curly, pegtl::list_must< single_id, pegtl::one< ',' >, pegtl::space >, pad_ws< close_curly >, pegtl::one< ';' > > {};
  struct protocol_def : pegtl::if_must< protocol_literal, pad_ws< pegtl::opt< pegtl::one< ':' > > >, pegtl::star< pad_ws< protocol_line > >, pad_ws< end_literal >, protocol_literal > {}; 

  struct evolution_line : pegtl::seq< bool_expr, pad_ws< if_literal >, bool_expr, pad_ws< pegtl::one< ';' > > > {};
  struct evolution_def : pegtl::if_must< evolution_literal, pad_ws< pegtl::opt< pegtl::one< ':' > > >, pegtl::star< pad_ws< evolution_line > >, pad_ws< end_literal >, evolution_literal > {};

  struct agent_contents : pegtl::seq< pegtl::opt< pad_ws< vars_def > >, pad_ws< initstate_def >, pad_ws< action_def >, pad_ws< protocol_def >, pad_ws< evolution_def > > {};
  struct agent_def : pegtl::if_must< agent_literal, pad_ws< single_id >, agent_contents, pad_ws< end_literal >, agent_literal > {}; 
  
  struct environment_str : TAO_PEGTL_STRING("Environment") {};
  struct environment_def : pegtl::if_must< agent_literal, pad_ws< environment_str >, agent_contents, pad_ws< end_literal >, agent_literal > {}; 

  struct evaluation_line : pegtl::seq< single_id, pad_ws< if_literal >, bool_expr, pad_ws< pegtl::one< ';' > > > {};
  struct evaluation_def : pegtl::if_must< evaluation_literal, pegtl::plus< pad_ws< evaluation_line > >, pad_ws< end_literal >, evaluation_literal > {};

  struct grammar : pegtl::must< bool_expr, pegtl::eof > {};

  template <typename Rule>
  struct test : pegtl::must<Rule, pegtl::eof> {};
  
  template< typename Rule >
  using selector = pegtl::parse_tree::selector<
    Rule,
    pegtl::parse_tree::store_content::on<
      number,
      single_id
    >,
    pegtl::parse_tree::remove_content::on<
      true_literal,
      false_literal,
      id,
      and_expr,
      or_expr,
      not_expr,
      lt_expr,
      leq_expr,
      gt_expr,
      geq_expr,
      eq_expr,
      neq_expr,
      bitor_expr,
      bitxor_expr,
      bitand_expr,
      bitnot_expr,
      add_expr,
      sub_expr,
      mul_expr,
      div_expr,
      vars_def,
      int_var_def,
      bool_var_def,
      initstate_def,
      action_def,
      protocol_line,
      protocol_def,
      evolution_line,
      evolution_def,
      agent_def,
      environment_def,
      evaluation_def
    >
  >;

  struct SwarmSystemGenerator {
    void generate_swarm_system(const std::unique_ptr<pegtl::parse_tree::node>& n) {
      
    }

    Expression::Ptr gen_expr(const std::unique_ptr<pegtl::parse_tree::node>& n) {
      auto& children = n->children;

      if (n->is<true_literal>()) { return Expression::Bool(true); }
      else if (n->is<false_literal>()) { return Expression::Bool(false); }
      else if (n->is<id>() && children.size() == 1) { return Expression::Id(children[0]->string()); }
      else if (n->is<id>() && children.size() == 2) { return Expression::Id(children[0]->string(), children[1]->string()); }
      else if (n->is<number>()) { return Expression::Int(std::stoi(n->string())); }
      else if (n->is<and_expr>()) { return Expression::And(gen_expr(children[0]), gen_expr(children[1])); }
      else if (n->is<or_expr>()) { return Expression::Or(gen_expr(children[0]), gen_expr(children[1])); }
      else if (n->is<not_expr>()) { return Expression::Not(gen_expr(children[0])); }
      else if (n->is<lt_expr>()) { return Expression::Lt(gen_expr(children[0]), gen_expr(children[1])); }
      else if (n->is<leq_expr>()) { return Expression::Leq(gen_expr(children[0]), gen_expr(children[1])); }
      else if (n->is<gt_expr>()) { return Expression::Gt(gen_expr(children[0]), gen_expr(children[1])); }
      else if (n->is<geq_expr>()) { return Expression::Geq(gen_expr(children[0]), gen_expr(children[1])); }
      else if (n->is<eq_expr>()) { return Expression::Eq(gen_expr(children[0]), gen_expr(children[1])); }
      else if (n->is<neq_expr>()) { return Expression::Neq(gen_expr(children[0]), gen_expr(children[1])); }
      else if (n->is<bitor_expr>()) { return Expression::BitOr(gen_expr(children[0]), gen_expr(children[1])); }
      else if (n->is<bitxor_expr>()) { return Expression::BitXor(gen_expr(children[0]), gen_expr(children[1])); }
      else if (n->is<bitand_expr>()) { return Expression::BitAnd(gen_expr(children[0]), gen_expr(children[1])); }
      else if (n->is<bitnot_expr>()) { return Expression::BitNot(gen_expr(children[0])); }
      else if (n->is<add_expr>()) { return Expression::Add(gen_expr(children[0]), gen_expr(children[1])); }
      else if (n->is<sub_expr>()) { return Expression::Sub(gen_expr(children[0]), gen_expr(children[1])); }
      else if (n->is<mul_expr>()) { return Expression::Mul(gen_expr(children[0]), gen_expr(children[1])); }
      else if (n->is<div_expr>()) { return Expression::Div(gen_expr(children[0]), gen_expr(children[1])); }
      else { 
        std::cout << "invalid expr: " << n->string() << std::endl;
        return Expression::Ptr();
      }
    }
  };

  void do_parse() {
    std::string input = "(a = b or c = d) and e = f";
    std::string var_test = "Vars : hello : 3..9; true_blue : boolean; end Vars";
    std::string action_test = "Actions =  { hello, gg, kk }  ;";
    std::string protocol_test = "Protocol : a = b : { g, a, b }; c = d : {h, k, l}; end Protocol";
    std::string initstate_test = "InitState : a = b ; end InitState";
    std::string evolution_test = "Evolution : a = b if c = d ;end Evolution";
    std::string agent_test = "Agent Environment " + var_test + " " + initstate_test + " " + action_test + " " + protocol_test + " " + evolution_test + " end Agent";
    std::string evaluation_test = "Evaluation stopped if a = c; end Evaluation";
    pegtl::string_input in(evaluation_test, "");
    try {
        const auto root = pegtl::parse_tree::parse< test<evaluation_def>, selector >( in );
        if (root == nullptr) {
          std::cout << "parsing error in file" << std::endl;
          return;
        }
        //SwarmSystemGenerator ssg;
        //auto expr = ssg.gen_expr(root->children[0]);
        //std::cout << expr->to_string() << std::endl;
        pegtl::parse_tree::print_dot( std::cout, *root );
        return;
    }
    catch( const pegtl::parse_error& e ) {
        const auto p = e.positions.front();
        std::cerr << e.what() << std::endl
                  << in.line_at( p ) << std::endl
                  << std::string( p.byte_in_line, ' ' ) << '^' << std::endl;
    }
    catch( const std::exception& e ) {
        std::cerr << e.what() << std::endl;
    }
  }
} // namespace parser
} // namespace mcmas


#endif