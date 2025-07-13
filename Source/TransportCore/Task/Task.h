#pragma once
#include "TX/RunLoop.h"
#include "TransportCore/API/TransportCore.h"
#include "TransportCore/Task/Scheduler.h"

namespace TransportCore {
// We can actually implement Start/Stop/Pause/Resume/ReadData etc. directly in
// class `Task` but we don't for two reasons.
// 1. A task is more like a container holding meta information about a specific
// work while a scheduler sounds more like how the work is done. Semantics
// always matters.
// 2. We can do some argument checks in `Task`s methods before calling into
// schedulers. Otherwise every scheduler will have to do those checks which is
// so bloated and unnecessary.
class Task {
 public:
  explicit Task(const TX::Ref<TX::RunLoop> &run_loop, const int32_t id,
                const TransportCoreTaskContext &context)
      : id_(id), run_loop_(run_loop), scheduler_(createScheduler(context)) {}

  TK_RESULT Start() {
    if (!scheduler_) return TK_ERR;
    return scheduler_->Start();
  }

  TK_RESULT Stop() {
    if (!scheduler_) return TK_ERR;
    return scheduler_->Stop();
  }

  TK_RESULT Pause() {
    if (!scheduler_) return TK_ERR;
    return scheduler_->Pause();
  }

  TK_RESULT Resume() {
    if (!scheduler_) return TK_ERR;
    return scheduler_->Resume();
  }

  int64_t ReadData(int32_t clip_no, size_t offset, size_t size, char *buf) {
    if (!scheduler_) return TK_ERR;
    return scheduler_->ReadData(clip_no, offset, size, buf);
  }

  std::string GetProxyURL() {
    if (!scheduler_) return "";
    return scheduler_->GetProxyURL();
  }

  TX_NODISCARD TX::RefPtr<Scheduler> createScheduler(
      const TransportCoreTaskContext &context) const {
    Scheduler *scheduler = nullptr;
    switch (context.kind) {
      case kTransportCoreTaskKindUnSpec:
        scheduler = new Scheduler(run_loop_, id_, context);
        break;
      case kTransportCoreTaskKindPlain:
        scheduler = nullptr;  // TODO
        break;
      default:
        break;
    }
    return TX::adoptRef(scheduler);
  }

 private:
  friend class TaskManager;
  int32_t id_;
  TX::Ref<TX::RunLoop> run_loop_;
  TX::RefPtr<Scheduler> scheduler_;
};
}  // namespace TransportCore
