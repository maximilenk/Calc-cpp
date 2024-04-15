#include "controller.h"

int s21::Controller::call_model(std::string& str, double x, double& result) {
  return m.calculate(str, x, result);
}
