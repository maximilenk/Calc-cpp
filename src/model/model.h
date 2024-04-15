#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_H_

#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include <utility>

namespace s21 {

class Model {
 public:
  Model() = default;
  ~Model() = default;

  int calculate(std::string &str, double x, double &result);

 private:
  int parcer(std::string &str);
  int find_priority(char oper);
  int compatibility(int i, int j);
  int compatibility_num(char ch);
  int comp_check(std::string &str);
  void unary_oper(char &it, char &prev);
  int polish(std::string &str);
  void do_math(std::stack<double> &numbers, char ch);
  double pol_math(std::string &str, double x);
  void func_check(std::string::iterator &it, std::string &tmp, int &result);
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_H_
