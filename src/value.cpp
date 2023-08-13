
#include "value.h"
#include <iostream>
#include <set>
#include <sstream>

Value::Value(double data, std::vector<Value *> children,
             const std::string &op) {
  static int counter = 1;
  std::stringstream ss;
  ss << "Value" << counter++;
  tag_ = ss.str();
  data_ = data;
  children_ = children;
  op_ = op;
  grad_ = 0;
  backward_ = &Value::add_backward;
  // backward_ = [](Value& v) { std::cout << "No function " << v.get() <<
  // std::endl; };
}

std::string Value::get() const {
  std::stringstream ss;
  ss << "Value(tag: " << tag_ << " data: " << data_ << ", grad: " << grad_
     << ")";
  return ss.str();
}

void Value::add_backward() {
  children()[0]->grad() += grad();
  children()[1]->grad() += grad();
}

Value operator+(Value &a, Value &b) {
  Value c(a.data_ + b.data_, {&a, &b}, "+");
  c.backward_ = &Value::add_backward;
  return c;
}

// Value operator*(Value& a, Value& b) {
//   Value c(a.data_ * b.data_, {&a, &b}, "*");
//   c.backward_ = [&]() {
//     std::cout << c.tag_ << " increased " << a.tag_ << " by " << c.grad_ *
//     b.data_ << " and " << b.tag_ << " by " << c.grad_ * a.data_ << std::endl;
//     a.grad_ += c.grad_ * b.data_;
//     b.grad_ += c.grad_ * a.data_;
//   };
//   return c;
// }

bool operator==(const Value &a, const Value &b) {
  return a.data_ == b.data_ && a.grad_ == b.grad_ && a.op_ == b.op_ &&
         a.children_ == b.children_ && a.tag_ == b.tag_;
}

bool operator!=(const Value &a, const Value &b) { return !(a == b); }

bool operator<(const Value &a, const Value &b) { return a.data_ < b.data_; }

void Value::backward() {
  std::set<Value> visited;
  std::vector<Value *> topo;
  std::function<void(Value &)> build_topo = [&](Value &v) {
    if (visited.find(v) != visited.end()) {
      return;
    }
    visited.insert(v);
    for (auto &child : v.children_) {
      build_topo(*child);
    }
    topo.push_back(&v);
  };
  build_topo(*this);
  grad_ = 1;
  for (auto it = topo.rbegin(); it != topo.rend(); ++it) {
    std::cout << (*it)->get() << std::endl;
    auto a = **it;
    (a.*(a.backward_))();
  }
}
