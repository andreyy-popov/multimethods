// TypeInfo.h
#ifndef _TYPE_INFO_H_
#define _TYPE_INFO_H_

#include <typeinfo>

class TypeInfo {
  const std::type_info& ti;
public:
  // Конструктор.
  TypeInfo(const std::type_info& ti) : ti(ti)
    {}
  // Друзья класса.
  friend bool operator<(const TypeInfo& t1, const TypeInfo& t2);
};

// Операция сравнения.
bool operator<(const TypeInfo& t1, const TypeInfo& t2);

#endif // _TYPE_INFO_H_
