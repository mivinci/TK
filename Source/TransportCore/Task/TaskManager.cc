#include "TransportCore/Task/TaskManager.h"

#include <atomic>

#include "TransportCore/Task/TaskListener.h"

namespace TransportCore {

int32_t TaskManager::GenTaskId(const Task::Kind kind) const noexcept {
  static std::atomic genTaskId = 0;
  const int32_t offset = factor_ * static_cast<int32_t>(kind);
  const int32_t base = genTaskId.fetch_add(span_, std::memory_order_relaxed);
  return (base >= factor_) ? -1 : base + offset;
}

int32_t TaskManager::CreateTask(const Task::Kind kind,
                                const TaskListener *listener) const {
  const int32_t task_id = GenTaskId(kind);
  return task_id;
}

void TaskManager::StartTask(const int32_t task_id) {}

void TaskManager::StopTask(int32_t task_id) {}

void TaskManager::PauseTask(int32_t task_id) {}

void TaskManager::ResumeTask(int32_t task_id) {}

TX::String TaskManager::GetProxyURL(int32_t task_id) const { return ""; }
}  // namespace TransportCore
