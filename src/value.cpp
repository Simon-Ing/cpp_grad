
#include "value.h"
#include <sstream>
#include <set>
#include <iostream>

Value::Value(double data, std::vector<Value> children, const std::string& op){
  static int counter = 0;
  std::stringstream ss;
  ss << "Value" << counter++;
  tag_ = ss.str();
  data_ = data;
  children_ = children;
  op_ = op;
  grad_ = 0;
  backward_ = []() {};
}

std::string Value::get() const {
  std::stringstream ss;
  ss << "Value(tag: " << tag_ << " data: " << data_ << ", grad: " << grad_ << ")";
  return ss.str();
}

Value operator+(Value& a, Value& b) {
  Value c(a.data_ + b.data_, {a, b}, "+");
  c.backward_ = [&]() {
    std::cout << c.tag_ << " increased " << a.tag_ << " and " << b.tag_ << " by " << c.grad_ << std::endl;
    a.grad_ += c.grad_;
    b.grad_ += c.grad_;
  };
  return c;
}

Value operator*(Value& a, Value& b) {
  Value c(a.data_ * b.data_, {a, b}, "*");
  c.backward_ = [&]() {
    std::cout << c.tag_ << " increased " << a.tag_ << " by " << c.grad_ * b.data_ << " and " << b.tag_ << " by " << c.grad_ * a.data_ << std::endl;
    a.grad_ += c.grad_ * b.data_;
    b.grad_ += c.grad_ * a.data_;
  };
  return c;
}

bool operator==(const Value& a, const Value& b) {
  return a.data_ == b.data_ && a.grad_ == b.grad_ && a.op_ == b.op_ && a.children_ == b.children_ && a.tag_ == b.tag_;
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
    it->backward_();
  }
}

/*
data
op
child child
op    op
grandchild grandchild grandchild grandchild
*/



// void Value::printTree() const {
//   std::vector<Value> visited;
//   std::vector<std::pair<Value, int>> topo_map;
//   std::function<void(const Value&, int)> build_topo = [&](const Value& v, int depth) {
//     if (std::find(visited.begin(), visited.end(), v) != visited.end()) {
//       // std::cout << "already visited " << v.tag_ << std::endl;
//       return;
//     }
//     visited.push_back(v);
//     // std::cout << v.tag_ << std::endl;
//     for (auto& child : v.children_) {
//       build_topo(child, depth + 1);
//     }
//     topo_map.push_back({v, depth});
//   };
//   build_topo(*this, 0);
//   std::sort(topo_map.begin(), topo_map.end(), [](const auto& a, const auto& b) {
//     return a.second < b.second;
//   });
//   for (auto& pair : topo_map) {
//     std::cout << pair.second << " " << pair.first.get() << std::endl;
//   }
// }

/*
Value4
Value3 Value2
Value0 Value1
*/
