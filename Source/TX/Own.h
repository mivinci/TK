#pragma once
#include "TX/Memory.h"
#include "TX/Platform.h"

namespace TX {
template <class T>
class Own {
 public:
  Own() : t_(nullptr) {}
  Own(T *t) : t_(t) {}
  Own(Own &&other) noexcept {
    t_ = other.t_;
    other.t_ = nullptr;
  }
  Own &operator=(T *t) {
    t_ = t;
    return *this;
  }
  Own &operator=(Own &&other) noexcept {
    t_ = other.t_;
    other.t_ = nullptr;
    return *this;
  }
  ~Own() {
    delete t_;
    t_ = nullptr;
  }

  TX_DISALLOW_COPY(Own)

  T *Take() {
    T *t = t_;
    t_ = nullptr;
    return t;
  }

  T *Leak() { return t_; }

  void Reset(T *t = nullptr) {
    if (t_ != t) {
      delete t_;
      t_ = t;
    }
  }
  
  TX_NODISCARD explicit operator bool() const { return !!t_; }

  T &operator*() { return *t_; }
  T *operator->() { return t_; }

 private:
  T *t_;
};

// Opposite to Own, UnOwn does not delete t_ when it is destructed.
template <class T>
class UnOwn {
 public:
  explicit UnOwn(T *t) : t_(t) {}
  ~UnOwn() = default;
  TX_DISALLOW_COPY(UnOwn)
  UnOwn(UnOwn &&other) noexcept {
    t_ = other.t_;
    other.t_ = nullptr;
  }
  UnOwn &operator=(UnOwn &&other) noexcept {
    t_ = other.t_;
    other.t_ = nullptr;
    return *this;
  }
  T *Take() {
    T *t = t_;
    t_ = nullptr;
    return t;
  }
  T &operator*() { return *t_; }
  T *operator->() { return t_; }

 private:
  T *t_;
};
}  // namespace TX
