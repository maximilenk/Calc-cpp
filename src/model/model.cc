#include "model.h"

namespace s21 {

int Model::calculate(std::string &str, double x, double &result) {
  int is_ok = 0;
  result = 0;
  if (str.size() > 255 || !str.size()) is_ok = 1;
  if (!is_ok) is_ok = parcer(str);
  if (!is_ok) is_ok = comp_check(str);
  if (!is_ok) is_ok = polish(str);
  if (!is_ok) result = pol_math(str, x);
  return is_ok;
}

int Model::parcer(std::string &str) {
  std::string tmp;
  std::string::iterator it = str.begin();
  int result = 0;
  int check = 0;
  while (it != str.end() && !result) {
    if ((*it >= '0' && *it <= '9') || *it == 'x' || *it == '-' || *it == '+' ||
        *it == '*' || *it == '/' || *it == '^' || *it == '(' || *it == ')' ||
        *it == '.') {
      tmp.push_back(*it);
      if (*it == '(') check++;
      if (*it == ')') check--;
    } else if (*it == 'e' || *it == 'E') {
      tmp.push_back('*');
      tmp.push_back('1');
      tmp.push_back('0');
      tmp.push_back('^');
      tmp.push_back('(');
      ++it;
      while (compatibility_num(*it) == 0 || *it == '+' || *it == '-') {
        tmp.push_back(*it);
        ++it;
      }
      tmp.push_back(')');
      --it;
    } else
      func_check(it, tmp, result);
    ++it;
  }
  if (check != 0) result = 1;
  str = tmp;
  return result;
}

void Model::func_check(std::string::iterator &it, std::string &tmp,
                       int &result) {
  if (*it == 's') {
    if (*(it + 1) == 'i' && *(it + 2) == 'n') {
      tmp.push_back('s');
      it += 2;
    } else if (*(it + 1) == 'q' && *(it + 2) == 'r' && *(it + 3) == 't') {
      tmp.push_back('q');
      it += 3;
    } else
      result = 1;
  } else if (*it == 'c') {
    if (*(it + 1) == 'o' && *(it + 2) == 's') {
      tmp.push_back('c');
      it += 2;
    } else
      result = 1;
  } else if (*it == 't') {
    if (*(it + 1) == 'a' && *(it + 2) == 'n') {
      tmp.push_back('t');
      it += 2;
    } else
      result = 1;
  } else if (*it == 'a') {
    if (*(it + 1) == 'c' && *(it + 2) == 'o' && *(it + 3) == 's') {
      tmp.push_back('o');
      it += 3;
    } else if (*(it + 1) == 's' && *(it + 2) == 'i' && *(it + 3) == 'n') {
      tmp.push_back('i');
      it += 3;
    } else if (*(it + 1) == 't' && *(it + 2) == 'a' && *(it + 3) == 'n') {
      tmp.push_back('a');
      it += 3;
    } else
      result = 1;
  } else if (*it == 'l') {
    if (*(it + 1) == 'n') {
      tmp.push_back('n');
      ++it;
    } else if (*(it + 1) == 'o' && *(it + 2) == 'g') {
      tmp.push_back('g');
      it += 2;
    } else
      result = 1;
  } else if (*it == 'm') {
    if (*(it + 1) == 'o' && *(it + 2) == 'd') {
      tmp.push_back('m');
      it += 2;
    } else
      result = 1;
  } else if (*it != ' ')
    result = 1;
}

void Model::unary_oper(char &it, char &prev) {
  if (compatibility_num(prev) == 1 || compatibility_num(prev) == 9) {
    if (it == '+')
      it = 'p';
    else
      it = '~';
  }
}

int Model::comp_check(std::string &str) {
  int result = 0;
  char prev = 7;
  auto it = str.begin();
  int flag = 0;
  while (it != str.end() && !result) {
    if (*it == '+' || *it == '-') {
      unary_oper(*it, prev);
    }
    if (*it == '.') {
      if (flag == 1) result = 1;
      flag = 1;
    }
    if (*it != '.' && flag == 1 &&
        (compatibility_num(*it) != 0 && compatibility_num(*it) != 8))
      flag = 0;
    if (compatibility(compatibility_num(prev), compatibility_num(*it)))
      result = 1;
    prev = *it;
    ++it;
  }
  if (compatibility(compatibility_num(prev), compatibility_num(7))) result = 1;
  return result;
}

int Model::compatibility_num(char ch) {
  int res = -1;
  if (ch >= '0' && ch <= '9') res = 0;
  if (ch == '(') res = 1;
  if (ch == ')') res = 2;
  if (ch == 'n' || ch == 'g' || ch == 'q' || ch == 'c' || ch == 's' ||
      ch == 't' || ch == 'a' || ch == 'i' || ch == 'o')
    res = 3;
  if (ch == 'm') res = 4;
  if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') res = 5;
  if (ch == '~' || ch == 'p') res = 6;
  if (ch == '.') res = 7;
  if (ch == 'x') res = 8;
  if (ch == 7) res = 9;
  return res;
}

int Model::compatibility(int i, int j) {
  int comp[10][10] = {
      {0, 1, 0, 1, 0, 0, 1, 0, 1, 0}, {0, 0, 1, 0, 1, 1, 0, 1, 0, 1},
      {1, 1, 0, 1, 0, 0, 1, 1, 1, 0}, {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
      {0, 0, 1, 1, 1, 1, 1, 1, 0, 1}, {0, 0, 1, 0, 1, 1, 1, 1, 0, 1},
      {0, 0, 1, 0, 1, 1, 1, 1, 0, 1}, {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 0, 1, 0, 0, 1, 1, 1, 0}, {0, 0, 1, 0, 1, 1, 0, 1, 0, 0}};
  return comp[i][j];
}

int Model::polish(std::string &str) {
  int result = 0;
  std::string tmp;
  std::stack<std::pair<char, int>> operations;
  auto it = str.begin();
  int flag = 0;
  while (it != str.end()) {
    if (*it == 'x') {
      tmp.push_back('x');
      ++it;
      tmp.push_back(' ');
    } else if ((*it >= '0' && *it <= '9')) {
      while ((*it >= '0' && *it <= '9') || *it == '.') {
        tmp.push_back(*it);
        ++it;
      }
      tmp.push_back(' ');
    } else {
      if (flag == 0) {
        flag++;
        operations.push(std::make_pair(*it, find_priority(*it)));
      } else {
        if (*it == '(')
          operations.push(std::make_pair(*it, find_priority(*it)));
        else if (*it == 'p')
          flag++;
        else if (*it == ')') {
          while (operations.top().first != '(') {
            tmp.push_back(operations.top().first);
            operations.pop();
            if (!operations.size()) {
              result = 1;
              break;
            }
          }
          operations.pop();  //это надо проверить
        } else {
          if (operations.size()) {
            while (find_priority(*it) <= operations.top().second) {
              tmp.push_back(operations.top().first);
              operations.pop();
              if (!operations.size()) break;
            }
          }
          operations.push(std::make_pair(*it, find_priority(*it)));
        }
      }
      ++it;
    }
  }
  while (operations.size()) {
    tmp.push_back(operations.top().first);
    operations.pop();
  }
  str = tmp;
  return result;
}

int Model::find_priority(char oper) {
  int priority = 127;
  if (oper == 'c' || oper == 's' || oper == 't' || oper == 'a' || oper == 'i' ||
      oper == 'o' || oper == 'q' || oper == 'n' || oper == 'g')
    priority = 3;
  if (oper == '*' || oper == '/' || oper == 'm') priority = 2;
  if (oper == '+' || oper == '-' || oper == '~') priority = 1;
  if (oper == ')' || oper == '(') priority = 0;
  if (oper == 'p') priority = 6;
  if (oper == '^') priority = 4;
  return priority;
}

double Model::pol_math(std::string &str, double x_value) {
  std::stack<double> numbers;
  std::string buff;
  auto it = str.begin();
  while (it != str.end()) {
    if ((*it >= '0' && *it <= '9') || *it == 'x') {
      while (*it != ' ') {
        buff.push_back(*it);
        ++it;
      }
      if (buff[0] == 'x')
        numbers.push(x_value);
      else
        numbers.push(std::stod(buff));
      buff.clear();
    } else if (compatibility_num(*it) != -1)
      do_math(numbers, *it);
    ++it;
  }
  return numbers.top();
}

void Model::do_math(std::stack<double> &numbers, char ch) {
  double temp;
  if (ch == 'n') numbers.top() = log(numbers.top());
  if (ch == 'g') numbers.top() = log10(numbers.top());
  if (ch == 'q') numbers.top() = sqrt(numbers.top());
  if (ch == 'c') numbers.top() = cos(numbers.top());
  if (ch == 's') numbers.top() = sin(numbers.top());
  if (ch == 't') numbers.top() = tan(numbers.top());
  if (ch == 'a') numbers.top() = atan(numbers.top());
  if (ch == 'i') numbers.top() = asin(numbers.top());
  if (ch == 'o') numbers.top() = acos(numbers.top());
  if (ch == '~') numbers.top() = -(numbers.top());
  if (ch == '+') {
    temp = numbers.top();
    numbers.pop();
    numbers.top() += temp;
  }
  if (ch == '-') {
    temp = numbers.top();
    numbers.pop();
    numbers.top() -= temp;
  }
  if (ch == '/') {
    temp = numbers.top();
    numbers.pop();
    numbers.top() /= temp;
  }
  if (ch == '*') {
    temp = numbers.top();
    numbers.pop();
    numbers.top() *= temp;
  }
  if (ch == '^') {
    temp = numbers.top();
    numbers.pop();
    numbers.top() = pow(numbers.top(), temp);
  }
  if (ch == 'm') {
    temp = numbers.top();
    numbers.pop();
    numbers.top() = fmod(numbers.top(), temp);
  }
}

}  // namespace s21
