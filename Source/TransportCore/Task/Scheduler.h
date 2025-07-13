#pragma once

#include "TX/RunLoop.h"
#include "TransportCore/API/TransportCore.h"

namespace TransportCore {

class Scheduler : public TX::RunLoop::Timer,
                  public TX::AtomicRefCounted<Scheduler> {
 public:
  explicit Scheduler(const TX::Ref<TX::RunLoop> &run_loop, int32_t task_id,
                     TransportCoreTaskContext context)
      : Timer(0, TX::Duration::Second(1), kTimerRepeatAlways, "Scheduler"),
        run_loop_(run_loop),
        context_(context),
        task_id_(task_id) {}

  virtual TK_RESULT Start();
  virtual TK_RESULT Stop();
  virtual TK_RESULT Pause();
  virtual TK_RESULT Resume();
  virtual TK_RESULT Schedule();
  virtual int64_t ReadData(int32_t, size_t, size_t, char *);
  virtual std::string GetProxyURL();

  void OnTimeout(TX::RunLoop &, TX::RefPtr<TX::RunLoop::Scope> &) override {
    // Run the internal schedule callback.
    Schedule();
    // See if we need to run the task's custom schedule callback.
    if (context_.schedule) {
      context_.schedule(GetTick(), context_.context);
    }
  }

 private:
  TX::Ref<TX::RunLoop> run_loop_;
  TransportCoreTaskContext context_;
  int32_t task_id_;
};

}  // namespace TransportCore
