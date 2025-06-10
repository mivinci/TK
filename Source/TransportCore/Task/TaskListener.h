#pragma once
namespace TransportCore {

struct TaskEvent {
  int32_t task_id;
};

class TaskListener {
 public:
  virtual ~TaskListener() = default;
  virtual void onEvent(TaskEvent event) = 0;
};
}  // namespace TransportCore
