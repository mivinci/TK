#pragma once
#include <cstdint>

#include "TX/Platform.h"

namespace TransportCore {
class Task {
 public:
  enum class Kind { Auto };
  explicit Task(const int32_t id) : id_(id) {}
  TX_NODISCARD int32_t Id() const { return id_; }

  void Start();
  void Stop();

 private:
  int32_t id_;
};
}  // namespace TP
