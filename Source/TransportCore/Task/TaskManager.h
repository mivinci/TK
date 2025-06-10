#pragma once
#include "TX/Assert.h"
#include "TX/Platform.h"
#include "TransportCore/Task/Task.h"
#include "TransportCore/Task/TaskListener.h"

namespace TransportCore {
#define TASK_ID_FACTOR 100000
#define TASK_ID_SPAN 1

class TaskManager {
 public:
  explicit TaskManager(const int32_t factor = TASK_ID_FACTOR,
                       const int8_t span = TASK_ID_SPAN)
      : factor_(factor), span_(span) {
    TX_ASSERT(TX::IsPowerOfTen(factor),
              "Task ID generator factor must be the power of 10");
  }

  TX_NODISCARD int32_t CreateTask(Task::Kind kind,
                                  const TaskListener *listener) const;
  void StartTask(int32_t task_id);
  void StopTask(int32_t task_id);
  void PauseTask(int32_t task_id);
  void ResumeTask(int32_t task_id);
  TX_NODISCARD TX::String GetProxyURL(int32_t task_id) const;

 private:
  TX_NODISCARD int32_t GenTaskId(Task::Kind kind) const noexcept;

 private:
  int32_t factor_;
  int32_t span_;
};
}  // namespace TransportCore
