
#pragma once

#include <vector>
#include <string>
#include <functional>

class Value {
public:
  Value(double data, std::vector<Value> children={}, const std::string& op="");
  // Value(const Value& other);

  void backward();

  // std::vector<Value>& children() { return children_; }

  // double data() const { return data_; }

  void set_tag(std::string tag) { tag_ = tag; }

  std::string get() const;

  std::vector<std::string> printTreeHelper() const;
  // void printTree() const;

  friend Value operator+(Value& a, Value& b);
  friend Value operator+(Value& a, Value&& b) { return a + b; }
  friend Value operator+(Value&& a, Value& b) { return a + b; }
  friend Value operator+(Value&& a, Value&& b) { return a + b; }

  friend Value operator*(Value& a, Value& b);
  friend Value operator*(Value& a, Value&& b) { return a * b; }
  friend Value operator*(Value&& a, Value& b) { return a * b; }
  friend Value operator*(Value&& a, Value&& b) { return a * b; }
  // friend Value operator*(double a, Value& b);
  // friend Value operator*(Value& a, double b);
  // friend Value operator-(Value& a); // Negation
  // friend Value operator-(Value& a, Value& b); // Subtraction
  friend bool operator==(const Value& a, const Value& b);
  friend bool operator!=(const Value& a, const Value& b);
  friend bool operator<(const Value& a, const Value& b);

private:
  double data_;
  std::vector<Value> children_;
  std::string op_;
  double grad_;
  std::function<void()> backward_;
  std::string tag_;
};
