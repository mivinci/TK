#include "TransportCore/Task/Scheduler.h"

#include "TransportCore/Global/Option.h"
#include "TransportCore/Log/Log.h"

namespace TransportCore {
TK_RESULT Scheduler::Start() {
  TK_INFO("task: %d(%s), start", task_id_, context_.keyid);
  run_loop_->AddTimer(this);
  return TK_OK;
}

TK_RESULT Scheduler::Stop() {
  TK_INFO("task: %d(%s), stop", task_id_, context_.keyid);
  run_loop_->RemoveTimer(this);
  return TK_OK;
}

TK_RESULT Scheduler::Pause() {
  TK_INFO("task: %d(%s), pause", task_id_, context_.keyid);
  run_loop_->RemoveTimer(this);
  return TK_OK;
}

TK_RESULT Scheduler::Resume() {
  TK_INFO("task: %d(%s), resume", task_id_, context_.keyid);
  run_loop_->AddTimer(this);
  return TK_OK;
}

TK_RESULT Scheduler::Schedule() { return TK_OK; }

int64_t Scheduler::ReadData(int32_t, size_t, size_t, char *) { return TK_OK; }

std::string Scheduler::GetProxyURL() { return ""; }

}  // namespace TransportCore
