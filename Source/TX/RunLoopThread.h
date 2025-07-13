#pragma once
#include "TX/Own.h"
#include "TX/Ref.h"
#include "TX/RunLoop.h"
#include "TX/Thread.h"

namespace TX {
class RunLoopThread {
 public:
  static Own<RunLoopThread> Spawn(const String &name = "RunLoop") {
    auto thread = RunLoop::SpawnThread(name);
    // If we do not detach here, ~RunLoopThread will block on join,
    // before it stops the underlying run loop.
    thread->Detach();
    const auto run_loop = RunLoop::FromThread(thread->GetId());
    return Own(new RunLoopThread(std::move(thread), run_loop));
  }

  ~RunLoopThread() { run_loop_->Stop(); }
  Ref<RunLoop> GetRunLoop() { return run_loop_; }

 private:
  explicit RunLoopThread(Own<Thread> thread, const Ref<RunLoop> &run_loop)
      : thread_(std::move(thread)), run_loop_(run_loop) {}

 private:
  Own<Thread> thread_{};
  Ref<RunLoop> run_loop_;
};
}  // namespace TX
