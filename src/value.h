
#pragma once

#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

class Value {
public:
  Value(double data, std::vector<Value *> children = {},
        const std::string &op = "");
  // Value(const Value& other);

  void backward();

  // std::vector<Value>& children() { return children_; }

  // double data() const { return data_; }

  void set_tag(std::string tag) { tag_ = tag; }

  std::string get() const;

  std::vector<Value*> children() { return children_; }

  double& grad() { return grad_; }

  double& data() { return data_; }

  std::vector<std::string> printTreeHelper() const;
  // void printTree() const;

  void add_backward();

  friend Value operator+(Value &a, Value &b);
  friend Value operator+(Value &a, Value &&b) {
    throw std::invalid_argument("rvalue operators not supported yet");
  }
  friend Value operator+(Value &&a, Value &b) {
    throw std::invalid_argument("rvalue operators not supported yet");
  }
  friend Value operator+(Value &&a, Value &&b) {
    throw std::invalid_argument("rvalue operators not supported yet");
  }

  // friend Value operator*(Value &a, Value &b);
  // friend Value operator*(Value &a, Value &&b) {
  //   throw std::invalid_argument("rvalue operators not supported yet");
  // }
  // friend Value operator*(Value &&a, Value &b) {
  //   throw std::invalid_argument("rvalue operators not supported yet");
  // }
  // friend Value operator*(Value &&a, Value &&b) {
  //   throw std::invalid_argument("rvalue operators not supported yet");
  // }
  // friend Value operator*(double a, Value& b);
  // friend Value operator*(Value& a, double b);
  // friend Value operator-(Value& a); // Negation
  // friend Value operator-(Value& a, Value& b); // Subtraction
  friend bool operator==(const Value &a, const Value &b);
  friend bool operator!=(const Value &a, const Value &b);
  friend bool operator<(const Value &a, const Value &b);

private:
  double data_;
  std::vector<Value *> children_;
  std::string op_;
  double grad_;
  // std::function<void(Value& v)> backward_;
  void (Value::*backward_)();
  std::string tag_;
};
