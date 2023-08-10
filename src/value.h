
#pragma once

#include <vector>
#include <string>
#include <functional>

enum class Op {
    add, mul, div, neg, sin, cos, exp, log, pow, none
};

class Value {
public:
  Value(double data, std::vector<Value&> children, Op op=Op::none);
  // Value(const Value& other);

  void backward();

  // std::vector<Value>& children() { return children_; }

  // double data() const { return data_; }

  void set_tag(std::string tag) { tag_ = tag; }

  std::string get() const;

  Value operator+(Value& other);
  Value operator*(Value& other);
  Value& operator=(Value other);
  // friend Value operator*(Value& a, Value& b);
  // friend Value operator*(double a, Value& b);
  // friend Value operator*(Value& a, double b);
  // friend Value operator-(Value& a); // Negation
  // friend Value operator-(Value& a, Value& b); // Subtraction
  friend bool operator==(const Value& a, const Value& b);
  friend bool operator!=(const Value& a, const Value& b);
  friend bool operator<(const Value& a, const Value& b);

private:
  double data_;
  std::vector<Value&> children_;
  Op op_;
  double grad_;
  std::function<void()> backward_;
  std::string tag_;

};
