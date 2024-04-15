#ifndef CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"

namespace s21 {

class Controller {
 public:
  Controller() = default;
  ~Controller() = default;

  int call_model(std::string& str, double x, double& result);

 private:
  Model m;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_
