// main.cpp
#include "MultiMethod.h"
#include <iostream>
#include <memory>

class Number {
public:
  virtual ~Number()
    {}
};

class Integer : public Number {
  int val;
public:
  Integer(int v) : val {v}
    {}
  int Value() const
    { return val; }
};

class Real : public Number {
  double val;
public:
  Real(double v) : val {v}
    {}
  double Value() const
    { return val; }
};

int main() {
  // Мультиметод печати одного числа.
  MultiMethod<bool(Number)> print1;
  print1.Add<Real>(
    [](Real& r)
      { return (std::cout << r.Value() << std::endl, true); });
  print1.Add<Integer>(
    [](Integer& i)
      { return (std::cout << i.Value() << std::endl, true); });
  // Мультиметод печати пары чисел.
  MultiMethod<bool(Number, Number)> print2;
  print2.Add<Real, Real>(
    [&print2](Real& r1, Real& r2)
      { return (std::cout << r1.Value() << " " << r2.Value() << std::endl, true); });
  print2.Add<Real, Integer>(
    [&print2](Real& r1, Integer& i2)
      { return (std::cout << r1.Value() << " " << i2.Value() << std::endl, true); });
  print2.Add<Integer, Real>(
    [&print2](Integer& i1, Real& r2)
      { return (std::cout << i1.Value() << " " << r2.Value() << std::endl, true); });
  print2.Add<Integer, Integer>(
    [&print2](Integer& i1, Integer& i2)
      { return (std::cout << i1.Value() << " " << i2.Value() << std::endl, true); });
  // Мультиметод сложения двух чисел.
  MultiMethod<std::unique_ptr<Number>(Number, Number)> add;
  add.Add<Real, Real>(
    [](Real& r1, Real& r2)
      { return std::unique_ptr<Number> {new Real {r1.Value() + r2.Value()}}; });
  add.Add<Integer, Integer>(
    [](Integer& i1, Integer& i2)
      { return std::unique_ptr<Number> {new Integer {i1.Value() + i2.Value()}}; });
  add.Add<Real, Integer>(
    [&add](Real& r1, Integer& i2)
      { return add(i2, r1); });
  add.Add<Integer, Real>(
    [&add](Integer& i1, Real& r2) {
      std::unique_ptr<Real> r1 {new Real(i1.Value())};
      return add(*r1, r2);
    }
  );
  // Вызов мультиметодов.
  std::unique_ptr<Number> n1 {new Real {12.3}};
  std::unique_ptr<Number> n2 {new Integer {4}};
  print1(*n1);
  print1(*n2);
  print2(*n1, *n1);
  print2(*n1, *n2);
  print2(*n2, *n1);
  print2(*n2, *n2);
  print1(*add(*n1, *n1));
  print1(*add(*n1, *n2));
  print1(*add(*n2, *n1));
  print1(*add(*n2, *n2));
  return 0;
}
