#pragma once
#include "TX/RunLoop.h"
#include "TX/Time.h"

namespace TransportCore {
class Scheduler : public TX::RunLoop::Timer, public TX::RefCounted<Scheduler> {
 public:
  explicit Scheduler(const TX::Duration period,
                      TX::Ref<TX::RunLoop> &run_loop)
      : Timer(0, period, UINT64_MAX), tick_(0), run_loop_(run_loop) {}

  virtual void OnSchedule();
  void Start();
  void Stop();

  void OnTimeout(TX::RunLoop &, TX::RefPtr<TX::RunLoop::Scope> &) override {
    OnSchedule();
  }

 private:
  uint64_t tick_;
  TX::Ref<TX::RunLoop> run_loop_;
};
}  // namespace TransportCore
