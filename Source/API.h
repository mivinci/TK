#ifndef TK_API_H
#define TK_API_H
#include <cstdint>

#include "Export.h"
#define TK_RESULT int
#define TK_OK 0

extern "C" {
enum TKTaskKind {};
struct TKTaskEvent {
  int32_t task_id;
};

struct TKTaskContext {
  void *info;
  void (*onEvent)(TKTaskEvent, void *);
};

TK_API TK_RESULT TKInit();
TK_API TK_RESULT TKDestroy();
TK_API int32_t TKCreateTask(TKTaskKind, TKTaskContext *);
TK_API TK_RESULT TKStopTask(int32_t);
TK_API TK_RESULT TKPauseTask(int32_t);
TK_API TK_RESULT TKResumeTask(int32_t);
TK_API TK_RESULT TKGetProxyURL(int32_t, char *, size_t *);
TK_API TK_RESULT TKClearCache();
TK_API TK_RESULT TKUpdateCachePath(const char *, size_t);
}
#endif  // TK_API_H
