
#include "value.h"
#include <sstream>
#include <set>
#include <iostream>

Value::Value(double data, std::vector<Value&> children, Op op){
  static int counter = 0;
  std::stringstream ss;
  ss << "Value" << counter++;
  tag_ = ss.str();
  data_ = data;
  children_ = children;
  op_ = op;
  grad_ = 0;
  backward_ = []() {};
  std::cout << "created value " << tag_ << std::endl;
}

std::string Value::get() const {
  std::stringstream ss;
  ss << "Value(data: " << data_ << ", grad: " << grad_ << ")";
  return ss.str();
}

Value Value::operator+(Value& other) {
  std::cout << "adding " << tag_ << " and " << other.tag_ << std::endl;
  Value result(data_ + other.data_, {*this, other}, Op::add);
  result.backward_ = [&]() {
    std::cout << result.tag_ << " increases grad of " << tag_ << " and " << other.tag_ << " by " << result.grad_ << std::endl;
    grad_ += result.grad_;
    other.grad_ += result.grad_;
  };
  std::cout << "created value by adding " << tag_ << " and " << other.tag_ << std::endl;
  return result;
}

Value Value::operator*(Value& other) {
  std::cout << "multiplying " << tag_ << " and " << other.tag_ << std::endl;
  Value result(data_ * other.data_, {*this, other}, Op::mul);
  result.backward_ = [&]() {
    std::cout << result.tag_ << " increases grad of " << tag_ << " by " << other.data_ * result.grad_ << std::endl;
    std::cout << " and " << other.tag_ << " by " << data_ * result.grad_ << std::endl;
    grad_ += other.data_ * result.grad_;
    other.grad_ += data_ * result.grad_;
  };
  std::cout << "created value by multiplying " << tag_ << " and " << other.tag_ << std::endl;
  return result;
}



Value& Value::operator=(Value other) {
  data_ = other.data_;
  children_ = other.children_;
  op_ = other.op_;
  grad_ = other.grad_;
  backward_ = other.backward_;
  tag_ = other.tag_;
  std::cout << "assigned value " << other.tag_ << " to " << tag_ << std::endl;
  return *this;
}

// Value operator*(double a, Value& b) {
//   Value c(a * b.data_, {b}, Op::mul);
//   c.backward_ = [&]() {
//     b.grad_ += a * c.grad_;
//   };
//   return c;
// }

// Value operator*(Value& a, double b) {
//   Value c(a.data_ * b, {a}, Op::mul);
//   c.backward_ = [&]() {
//     a.grad_ += b * c.grad_;
//   };
//   return c;
// }

// Value operator-(Value& a) {
//   return -1 * a;
// }

// Value operator-(Value& a, Value& b) {
//   Value c = -b;
//   return a + c;
// }

bool operator==(const Value& a, const Value& b) {
  return a.data_ == b.data_ && a.grad_ == b.grad_ && a.op_ == b.op_ && a.children_ == b.children_;
}

bool operator!=(const Value& a, const Value& b) {
  return !(a == b);
}

bool operator<(const Value& a, const Value& b) {
  return a.data_ < b.data_;
}

void Value::backward() {
  std::set<Value> visited;
  std::vector<Value> topo;
  std::function<void(Value&)> build_topo = [&](Value& v) {
    if (visited.find(v) != visited.end()) {
      return;
    }
    visited.insert(v);
    for (auto& child : v.children_) {
      build_topo(child);
    }
    topo.push_back(v);
  };
  build_topo(*this);
  grad_ = 1;
  for (auto it = topo.rbegin(); it != topo.rend(); ++it) {
    std::cout << it->tag_ << " has children: ";
    for (auto& child : it->children_) {
      std::cout << child.tag_ << " ";
    }
    std::cout << std::endl;
    it->backward_();
  }
}
