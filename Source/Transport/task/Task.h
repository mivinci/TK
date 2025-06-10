#pragma once
#include <cstdint>

#include "TX/Platform.h"
#include "Transport/Result.h"

namespace TP {
class Task {
 public:
  enum class Kind : int {
    Auto,
  };

  explicit Task(int32_t id) : id_(id) {}
  TX_NODISCARD int32_t Id() const { return id_; }

  TP_RESULT Start();
  TP_RESULT Stop();

 private:
  int32_t id_;
};
}  // namespace TP
