#pragma once

#include "TX/RunLoop.h"

namespace TransportCore {
class HTTPClient final : public TX::RunLoop::Timer {
 public:
  explicit HTTPClient();
  ~HTTPClient() override;

  void Start();
  void Stop();

  int32_t CreateRequest();
  int32_t StartRequest(int32_t);
  int32_t StopRequest(int32_t);

  
 protected:
  void OnTimeout(TX::RunLoop &, TX::RefPtr<TX::RunLoop::Scope> &) override;

 private:
  friend TX::RunLoop;
  void *handle_;
  TX::Ref<TX::RunLoop> run_loop_;
};
}  // namespace TransportCore
