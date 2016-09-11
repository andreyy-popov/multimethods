// MultiMethod.h
#ifndef _MULTI_METHOD_H_
#define _MULTI_METHOD_H_

#include "TypeInfo.h"
#include <functional>
#include <tuple>
#include <map>

template <typename>
class MultiMethod;

template <typename Res, typename... ArgsBase>
class MultiMethod<Res(ArgsBase...)> {
  // Параметры регистрации функций обратного вызова.
  template <class T>
  using ArgId = TypeInfo;
  using CallbackId = std::tuple<ArgId<ArgsBase>...>;
  using Callback = std::function<Res(ArgsBase&...)>;
  using Callbacks = std::map<CallbackId, Callback>;
  Callbacks callbacks;
public:
  // Добавление функции.
  template <typename... Args, typename Fn>
  void Add(Fn fn) {
    callbacks[CallbackId(TypeInfo(typeid(Args))...)] = [fn](ArgsBase&... args) -> Res {
      return fn(dynamic_cast<Args&>(args)...);
    };
  }
  // Вызов функции.
  template <typename... Args>
  Res operator()(Args&... args) {
    auto it = callbacks.find(CallbackId(TypeInfo(typeid(args))...));
    if (it != callbacks.end()) {
      return it->second(args...);
    }
    return Callback()(args...);
  }
};

#endif // _MULTI_METHOD_H_
