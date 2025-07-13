#include "TransportCore/API/TransportCore.h"

#include "TX/RunLoopThread.h"
#include "TransportCore/Log/Log.h"
#include "TransportCore/Task/TaskManager.h"

struct Guard {
  TransportCore::TaskManager *task_manager = nullptr;
  bool initialized = false;
};

static TX::Mutex<Guard> gGuard;

void TransportCoreInit() {
  auto guard = gGuard.Lock();
  if (guard->initialized) TK_FATAL("TransportCore already initialized");
  guard->task_manager = new TransportCore::TaskManager;
  guard->task_manager->Start();
  guard->initialized = true;
}

void TransportCoreDestroy() {
  auto guard = gGuard.Lock();
  if (!guard->initialized) TK_FATAL("TransportCore not initialized");
  guard->task_manager->Stop();
  guard->initialized = false;
  delete guard->task_manager;
}

int32_t TransportCoreCreateTask(TransportCoreTaskContext context) {
  auto guard = gGuard.Lock();
  if (!guard->initialized) TK_FATAL("TransportCore not initialized");
  return guard->task_manager->CreateTask(context);
}

TK_RESULT TransportCoreStartTask(const int32_t task_id) {
  auto guard = gGuard.Lock();
  if (!guard->initialized) TK_FATAL("TransportCore not initialized");
  return guard->task_manager->StartTask(task_id);
}

TK_RESULT TransportCoreStopTask(const int32_t task_id) {
  auto guard = gGuard.Lock();
  if (!guard->initialized) TK_FATAL("TransportCore not initialized");
  return guard->task_manager->StopTask(task_id);
}

TK_RESULT TransportCorePauseTask(const int32_t task_id) {
  auto guard = gGuard.Lock();
  if (!guard->initialized) TK_FATAL("TransportCore not initialized");
  return guard->task_manager->PauseTask(task_id);
}

TK_RESULT TransportCoreResumeTask(const int32_t task_id) {
  auto guard = gGuard.Lock();
  if (!guard->initialized) TK_FATAL("TransportCore not initialized");
  return guard->task_manager->ResumeTask(task_id);
}

int64_t TransportCoreReadData(int32_t task_id, int32_t clip_no, size_t offset,
                              size_t size, char *buf) {
  auto guard = gGuard.Lock();
  if (!guard->initialized) TK_FATAL("TransportCore not initialized");
  return guard->task_manager->ReadData(task_id, clip_no, offset, size, buf);
}

TK_RESULT TransportCoreGetProxyURL(const int32_t task_id, char *buf,
                                   const size_t buf_size) {
  auto guard = gGuard.Lock();
  if (!guard->initialized) TK_FATAL("TransportCore not initialized");
  const std::string proxy_url = guard->task_manager->GetProxyURL(task_id);
  const size_t size = std::min(buf_size, proxy_url.size());
  std::memcpy(buf, proxy_url.data(), size);
  buf[size - 1] = '\0';
  return TK_OK;
}
