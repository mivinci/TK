#include "TransportCore/Task/Scheduler.h"

#include "TransportCore/Log/Log.h"

void TransportCore::Scheduler::Start() { run_loop_->AddTimer(this); }
void TransportCore::Scheduler::Stop() { run_loop_->RemoveTimer(this); }
void TransportCore::Scheduler::OnSchedule() {
  tick_++;
  TC_INFO("");
}
