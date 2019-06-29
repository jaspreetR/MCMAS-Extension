#ifndef MCMAS_PARSER_HPP
#define MCMAS_PARSE_HPP
#include <optional>
#include "parser/pegtl.hpp"
#include "SwarmSystem.hpp"

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
  struct ag_str : TAO_PEGTL_STRING("AG") {};
  struct eg_str : TAO_PEGTL_STRING("EG") {};
  struct af_str : TAO_PEGTL_STRING("AF") {};
  struct ef_str : TAO_PEGTL_STRING("EF") {};
  struct ax_str : TAO_PEGTL_STRING("AX") {};
  struct ex_str : TAO_PEGTL_STRING("EX") {};
  struct a_str : TAO_PEGTL_STRING("A") {};
  struct e_str : TAO_PEGTL_STRING("E") {};
  struct u_str : TAO_PEGTL_STRING("U") {};
  struct k_str : TAO_PEGTL_STRING("K") {};

  struct str_keyword : pegtl::sor< true_str, false_str, agent_str, actions_str, protocol_str, 
                                   evolution_str, evaluation_str, initstate_str, formulae_str, 
                                   end_str, vars_str, boolean_str, and_str, or_str, if_str,
                                   ag_str, eg_str, af_str, ef_str, ax_str, ex_str, a_str, e_str,
                                   u_str, k_str > {};

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
  struct ag_literal : key< ag_str > {};
  struct eg_literal : key< eg_str > {};
  struct af_literal : key< af_str > {};
  struct ef_literal : key< ef_str > {};
  struct ax_literal : key< ax_str > {};
  struct ex_literal : key< ex_str > {};
  struct a_literal : key< a_str > {};
  struct e_literal : key< e_str > {};
  struct u_literal : key< u_str > {};
  struct k_literal : key< k_str > {};

  struct single_id : pegtl::seq< pegtl::not_at< key< str_keyword > >, pegtl::identifier > {};
  struct qual_id : pegtl::seq< single_id, pegtl::if_must< pegtl::one< '.' >, single_id > > {};
  struct id : pegtl::sor< qual_id, single_id > {};

  struct number : pegtl::seq< pegtl::opt< pegtl::one< '-' > >, pegtl::plus< pegtl::digit > > {};

  struct var_value : pegtl::sor< true_literal, false_literal, id, number > {};

  struct open_bracket : pegtl::seq< pegtl::one< '(' >, pegtl::star< pegtl::space > > {};
  struct close_bracket : pegtl::seq< pegtl::star< pegtl::space >, pegtl::one< ')' > > {};
  struct open_curly : pegtl::seq< pegtl::one< '{' >, pegtl::star< pegtl::space > > {};
  struct close_curly : pegtl::seq< pegtl::star< pegtl::space >, pegtl::one< '}' > > {};

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

  struct arrow_op : TAO_PEGTL_STRING("->") {};

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

  ////////////////////////////
  // Formula Rules
  ////////////////////////////
  
  struct formula;
  struct formula_1;
  struct formula_2;
  struct formula_3;
  struct formula_4;
  struct formula_5;
  struct arrow_formula;
  struct or_formula;
  struct and_formula;
  struct not_formula;
  struct ax_formula;
  struct ex_formula;
  struct af_formula;
  struct ef_formula;
  struct ag_formula;
  struct eg_formula;
  struct au_formula;
  struct eu_formula;
  struct k_formula;

  struct arrow_formula : pegtl::seq< formula_1, pad_ws< arrow_op >, formula > {};
  struct formula : pegtl::sor< arrow_formula, formula_1 > {};

  struct or_formula : pegtl::seq< formula_2, pad_ws< or_op >, formula_1 > {};
  struct formula_1 : pegtl::sor< or_formula, formula_2 > {};

  struct and_formula : pegtl::seq< formula_3, pad_ws< and_op >, formula_2 > {};
  struct formula_2 : pegtl::sor< and_formula, formula_3 > {};

  struct not_formula : pegtl::seq< pad_ws< not_op >, formula_3 > {};
  struct formula_3 : pegtl::sor< not_formula, formula_4 > {};

  struct ax_formula : pegtl::seq< pad_ws< ax_literal >, formula_3 > {};
  struct ex_formula : pegtl::seq< pad_ws< ex_literal >, formula_3 > {};
  struct af_formula : pegtl::seq< pad_ws< af_literal >, formula_3 > {};
  struct ef_formula : pegtl::seq< pad_ws< ef_literal >, formula_3 > {};
  struct ag_formula : pegtl::seq< pad_ws< ag_literal >, formula_3 > {};
  struct eg_formula : pegtl::seq< pad_ws< eg_literal >, formula_3 > {};
  struct au_formula : pegtl::seq< pad_ws< a_literal >, bracketed< pegtl::seq< formula, pad_ws< u_literal >, formula > > > {};
  struct eu_formula : pegtl::seq< pad_ws< e_literal >, bracketed< pegtl::seq< formula_4, pad_ws< u_literal >, formula > > > {};
  struct k_formula : pegtl::seq< pad_ws< k_literal >, bracketed< pegtl::seq< single_id, pad_ws< pegtl::one< ',' > >, formula > > > {};
  struct atom_formula : pegtl::seq< single_id, pad_ws< bracketed< single_id > > > {};
  struct formula_4 : pegtl::sor< ax_formula, ex_formula, af_formula, ef_formula, ag_formula, eg_formula, 
                                 au_formula, eu_formula, k_formula, atom_formula, bracketed< formula > > {};

  ////////////////////////////

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

  struct agent_contents : pegtl::seq< pegtl::opt< pad_ws< vars_def > >, pad_ws< initstate_def >, pad_ws< action_def >, pad_ws< protocol_def >, pegtl::opt< pad_ws< evolution_def > > > {};
  struct agent_def : pegtl::if_must< agent_literal, pad_ws< single_id >, agent_contents, pad_ws< end_literal >, agent_literal > {}; 
  
  struct environment_str : TAO_PEGTL_STRING("Environment") {};
  struct environment_def : pegtl::if_must< agent_literal, pad_ws< environment_str >, agent_contents, pad_ws< end_literal >, agent_literal > {}; 

  struct evaluation_line : pegtl::seq< single_id, pad_ws< if_literal >, bool_expr, pad_ws< pegtl::one< ';' > > > {};
  struct evaluation_def : pegtl::if_must< evaluation_literal, pegtl::plus< pad_ws< evaluation_line > >, pad_ws< end_literal >, evaluation_literal > {};

  struct formulae_placeholders : bracketed< pegtl::list_must< single_id, pegtl::one< ',' >, pegtl::space > > {};
  struct formulae_line : pegtl::seq< pad_ws < formulae_placeholders >, formula, pad_ws< pegtl::one< ';' > > > {};
  struct formulae_def : pegtl::if_must< formulae_literal, pegtl::plus< pad_ws< formulae_line > >, pad_ws< end_literal >, formulae_literal > {};

  struct grammar : pegtl::must< pad_ws< environment_def >, 
                                pad_ws< agent_def >,
                                pad_ws< evaluation_def >,
                                pad_ws< formulae_def>,
                                pegtl::eof > {};

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
      arrow_formula,
      or_formula,
      and_formula,
      not_formula,
      ax_formula,
      ex_formula,
      af_formula,
      ef_formula,
      ag_formula,
      eg_formula,
      au_formula,
      eu_formula,
      k_formula,
      atom_formula,
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
      evaluation_line,
      evaluation_def,
      formulae_def,
      formulae_line,
      formulae_placeholders
    >
  >;

  struct SwarmSystemGenerator {
    using NodePtr = std::unique_ptr<pegtl::parse_tree::node>;

    const NodePtr root;

    SwarmSystemGenerator(NodePtr&& root) : root(std::move(root)) {

    }

    SwarmSystem generate_swarm_system(int num_concrete, bool has_meta) {
      assert(num_concrete >= -1);
      auto& children = root->children;
      SwarmAgent env = gen_env(children[0]);
      SwarmAgent agent = gen_agent(children[1]);
      Evaluation evaluation = gen_eval(children[2]);
      IndexedFormula formula = gen_indexed_formula(children[3]);
      int m = formula.placeholders.size();
      std::vector<IndexedFormula> formulas;
      formulas.emplace_back(std::move(formula));

      if (num_concrete == -1) {
        return SwarmSystem(env, agent, m, evaluation, std::move(formulas), true, has_meta);
      } else {
        return SwarmSystem(env, agent, num_concrete + m, evaluation, std::move(formulas), false, false);
      }
    }

    Evaluation gen_eval(const NodePtr& n) {
      Evaluation evaluation;
      for (auto& eval_line : n->children) {
        auto& children = eval_line->children;
        evaluation.lines.emplace_back(EvaluationLine(children[0]->string(), gen_expr(children[1])));
      }

      return evaluation;
    }

    IndexedFormula gen_indexed_formula(const NodePtr& n) {
      auto& first_formula = n->children[0];
      auto& placeholders = first_formula->children[0];
      std::vector<std::string> placeholder_strs;
      for (auto& placeholder : placeholders->children) {
        placeholder_strs.emplace_back(placeholder->string()); 
      }

      if (n->children.size() != 1) {
        std::cout << "Only a single formula can be defined" << std::endl;
      }

      return IndexedFormula(placeholder_strs, gen_formula(first_formula->children[1]));
    }

    SwarmAgent gen_env(const NodePtr& n) {
      auto& children = n->children;
      SwarmAgent env;
      env.name = "Environment";

      gen_var(children[0], env);
      gen_initstate(children[1], env);
      gen_actions(children[2], env);
      gen_protocol(children[3], env);

      if (children.size() > 4) {
        gen_evolution(children[4], env);
      }

      return env;
    }

    SwarmAgent gen_agent(const NodePtr& n) {
      auto& children = n->children;
      SwarmAgent agent;
      agent.name = children[0]->string();
      gen_var(children[1], agent);
      gen_initstate(children[2], agent);
      gen_actions(children[3], agent);
      gen_protocol(children[4], agent);

      if (children.size() > 5) {
        gen_evolution(children[5], agent);
      }

      return agent;
    }

    void gen_var(const NodePtr& n, SwarmAgent& agent) {
      for (auto& var_def : n->children) {
        auto& children = var_def->children;

        if (var_def->is<int_var_def>()) {
          auto var_name = children[0]->string();
          auto min_range = std::stoi(children[1]->string());
          auto max_range = std::stoi(children[2]->string());
          agent.add_variable(var_name, RANGED_INT(min_range, max_range));
        } else if (var_def->is<bool_var_def>()) {
          auto var_name = children[0]->string();
          agent.add_variable(var_name, BOOL()); 
        } else {
          std::cout << "invalid var def" << std::endl;
        }
      }
    }

    void gen_initstate(const NodePtr& n, SwarmAgent& agent) {
      agent.add_init_condition(gen_expr(n->children[0]));
    }

    void gen_actions(const NodePtr& n, SwarmAgent& agent) {
      std::vector<std::string> actions;
      for (auto& action : n->children) {
        actions.emplace_back(action->string());
      }
      agent.add_actions(std::move(actions));
    }

    void gen_protocol(const NodePtr& n, SwarmAgent& agent) {
      for (auto& protocol_line : n->children) {
        auto& children = protocol_line->children;
        auto condition = gen_expr(children[0]);
        std::vector<std::string> actions;

        for (size_t i = 1; i < children.size(); ++i) {
          actions.emplace_back(children[i]->string());
        }

        agent.add_protocol_line(std::move(condition), std::move(actions));
      }
    }

    void gen_evolution(const NodePtr& n, SwarmAgent& agent) {
      for (auto& evolution_line : n->children) {
        auto& children = evolution_line->children;
        auto transition = gen_expr(children[0]);
        auto condition = gen_expr(children[1]);
        agent.add_evolution_line(std::move(transition), std::move(condition));
      }
    }

    Expression::Ptr gen_expr(const NodePtr& n) {
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

    Formula::Ptr gen_formula(const NodePtr& n) {
      auto& children = n->children;

      if (n->is<atom_formula>()) { return Formula::Atom(children[1]->string(), children[0]->string()); }
      else if (n->is<arrow_formula>()) { return Formula::Arrow(gen_formula(children[0]), gen_formula(children[1])); }
      else if (n->is<or_formula>()) { return Formula::Or(gen_formula(children[0]), gen_formula(children[1])); }
      else if (n->is<and_formula>()) { return Formula::And(gen_formula(children[0]), gen_formula(children[1])); }
      else if (n->is<not_formula>()) { return Formula::Not(gen_formula(children[0])); }
      else if (n->is<af_formula>()) { return Formula::AF(gen_formula(children[0])); }
      else if (n->is<ef_formula>()) { return Formula::EF(gen_formula(children[0])); }
      else if (n->is<ag_formula>()) { return Formula::AG(gen_formula(children[0])); }
      else if (n->is<eg_formula>()) { return Formula::EG(gen_formula(children[0])); }
      else if (n->is<ax_formula>()) { return Formula::AX(gen_formula(children[0])); }
      else if (n->is<ex_formula>()) { return Formula::EX(gen_formula(children[0])); }
      else if (n->is<k_formula>()) { return Formula::K(children[0]->string(), gen_formula(children[1])); }
      else if (n->is<au_formula>()) { return Formula::AU(gen_formula(children[0]), gen_formula(children[1])); }
      else if (n->is<eu_formula>()) { return Formula::EU(gen_formula(children[0]), gen_formula(children[1])); }
      else {
        std::cout << "invalid formula: " << n->string() << std::endl;
        return Formula::Ptr();
      }
    }

  };

  std::optional<SwarmSystem> do_parse(const std::string& file_name, int num_concrete, bool has_meta) {
    pegtl::file_input in(file_name);
    try {
        std::cout << "Parsing SISPL..." << std::endl;
        auto root = pegtl::parse_tree::parse< test<grammar>, selector >( in );

        if (root == nullptr) {
          std::cout << "parsing error in file" << std::endl;
          return std::nullopt;
        }

        std::cout << "Generating Model..." << std::endl;
        SwarmSystemGenerator ssg{std::move(root)};
        //pegtl::parse_tree::print_dot( std::cout, *ssg.root );
        return ssg.generate_swarm_system(num_concrete, has_meta);
    }
    catch( const pegtl::parse_error& e ) {
        const auto p = e.positions.front();
        std::cerr << e.what() << std::endl
                  << in.line_at( p ) << std::endl
                  << std::string( p.byte_in_line, ' ' ) << '^' << std::endl;
    }
    catch( const std::exception& e ) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return std::nullopt;
  }
} // namespace parser
} // namespace mcmas


#endif