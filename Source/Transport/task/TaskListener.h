#pragma once

#include <cstdint>

namespace TP {

struct TaskEvent {
  int32_t task_id;
};

class TaskListener {
 public:
  virtual ~TaskListener() = default;
  virtual void onTaskEvent(TaskEvent event) = 0;
};
}  // namespace TP
