#include "TransportCore/Global/Global.h"

#include "TX/RunLoopThread.h"

namespace TransportCore {
static TX::Own<TX::RunLoopThread> gMainRunLoopThread;

TX::Ref<TX::RunLoop> GetMainRunLoop() {
  if (TX_UNLIKELY(!gMainRunLoopThread)) {
    gMainRunLoopThread = TX::RunLoopThread::Spawn("TransportCoreMainRunLoop");
  }
  return gMainRunLoopThread->GetRunLoop();
}

TX::Ref<TX::RunLoop> GetWorkerRunLoop() {
  
}
}  // namespace TransportCore
