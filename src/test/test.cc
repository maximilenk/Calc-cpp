#include <gtest/gtest.h>

#include "../controller/controller.h"

namespace s21 {

TEST(Calc, Simple) {
  std::string a = "2 + 2";
  s21::Controller c;
  double b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(b, 4);

  a = "2 - 2";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(b, 0);

  a = "2 / 2";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(b, 1);

  a = "2 * 2";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(b, 4);

  a = "2 mod 2";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(b, 0);

  a = "3 mod 2";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(b, 1);

  a = "sin(1.57)";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  ASSERT_NEAR(b, 0.999999, 0.000001);

  a = "cos(0)";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(b, 1);

  a = "tan(0.785)";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  ASSERT_NEAR(b, 0.999204, 0.000001);

  a = "asin(1)";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  ASSERT_NEAR(b, 1.570796, 0.000001);

  a = "acos(0.56)";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  ASSERT_NEAR(b, 0.97641, 0.000001);

  a = "atan(0.56)";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  ASSERT_NEAR(b, atan(0.56), 0.000001);

  a = "ln(234)";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  ASSERT_NEAR(b, log(234), 0.000001);

  a = "log(234)";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  ASSERT_NEAR(b, log10(234), 0.000001);

  a = "sqrt(3.23)";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  ASSERT_NEAR(b, sqrt(3.23), 0.000001);

  a = "-5.2";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(b, -5.2);

  a = "+4";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(b, 4);

  a = "3^(6-4)";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(b, 9);
}

TEST(Calc, Dots) {
  std::string a = "3.12";
  s21::Controller c;
  double b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(b, 3.12);

  a = ".12";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));
  EXPECT_EQ(b, 0);

  a = "12.";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));
  EXPECT_EQ(b, 0);

  a = "3.21.2";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));
  EXPECT_EQ(b, 0);
}

TEST(Calc, Brackets) {
  std::string a = "(4)";
  s21::Controller c;
  double b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(b, 4);

  a = "(4";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));
  EXPECT_EQ(b, 0);

  a = "4)";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));
  EXPECT_EQ(b, 0);

  a = "(4))";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));
  EXPECT_EQ(b, 0);

  a = ")4(";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));
  EXPECT_EQ(b, 0);

  a = ")4";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));
  EXPECT_EQ(b, 0);

  a = "(4";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));
  EXPECT_EQ(b, 0);

  a = "()";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));
  EXPECT_EQ(b, 0);
}

TEST(Calc, InfAndNan) {
  std::string a = "asin(2)";
  s21::Controller c;
  double b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(std::isnan(b), 1);

  a = "acos(2)";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(std::isnan(b), 1);

  a = "sqrt(-2)";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(std::isnan(b), 1);

  a = "1/0";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(std::isinf(b), 1);

  a = "1/(5-5)";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(std::isinf(b), 1);

  a = "log(-1)";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(std::isnan(b), 1);

  a = "ln(-1)";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(std::isnan(b), 1);

  a = "4 mod 0";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(std::isnan(b), 1);

  a = "4 mod (-1)";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  EXPECT_EQ(b, fmod(4, -1));

  a = "4 mod 2.2";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  ASSERT_NEAR(b, 1.8, 0.1);
}

TEST(Calc, Hard) {
  std::string a = "(2+2*3)/25 - (sin(1.54 + (22 - (11/2))))";
  s21::Controller c;
  double b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  ASSERT_NEAR(b, 1.043980, 0.000001);

  a = "log(sqrt((4-5)+2))";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  ASSERT_NEAR(b, 0, 0.000001);

  a = "+2 * asin(-0.56)/acos(0.123)+ ln(16.0/4.0)/log( 1.0/2.0)";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  ASSERT_NEAR(
      b, +2 * asin(-0.56) / acos(0.123) + log(16.0 / 4.0) / log10(1.0 / 2.0),
      0.000001);

  a = "+2*atan(-0.56)/sqrt(144.144)+3*(10.0 mod 3.0)";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  ASSERT_NEAR(b, +2 * atan(-0.56) / sqrt(144.144) + 3 * fmod(10.0, 3.0),
              0.000001);

  a = "-(-87.543*sin(0.999+tan(55.5)-2.234))-50.66*(acos(0.234)/atan(0.55))";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 0, b));
  ASSERT_NEAR(b,
              -(-87.543 * sin(0.999 + tan(55.5) - 2.234)) -
                  50.66 * (acos(0.234) / atan(0.55)),
              0.000001);

  a = "-(-x*sin(0.999+tan(55.5)-2.234))-50.66*(acos(0.234)/atan(0.55))";
  b = 0;
  EXPECT_EQ(0, c.call_model(a, 87.543, b));
  ASSERT_NEAR(b,
              -(-87.543 * sin(0.999 + tan(55.5) - 2.234)) -
                  50.66 * (acos(0.234) / atan(0.55)),
              0.000001);
}

TEST(Calc, IncorrectInput) {
  std::string a = "2+";
  s21::Controller c;
  double b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));

  a = "log3";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));

  a = "sin(5_0)";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));

  a = "tgs(4)";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));

  a = "a";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));

  a = "4 / - 2";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));

  a = "/ 2";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));

  a = "--2";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));

  a = "sin4";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));

  a = "()";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));

  a = "(2.x)";
  b = 0;
  EXPECT_EQ(1, c.call_model(a, 0, b));
}

}  // namespace s21