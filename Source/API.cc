#include "API.h"

extern "C" {
TK_API TK_RESULT TKInit() { return TK_OK; }
TK_API TK_RESULT TKCreateTask(TKTaskKind kind, TKTaskContext *context) {
  return TK_OK;
}
TK_API TK_RESULT TKStopTask(int32_t task_id) { return TK_OK; }
TK_API TK_RESULT TKPauseTask(int32_t task_id) { return TK_OK; }
TK_API TK_RESULT TKResumeTask(int32_t task_id) { return TK_OK; }
TK_API TK_RESULT TKGetProxyURL(int32_t task_id, char *buf, size_t *len) {
  return TK_OK;
}
TK_API TK_RESULT TKClearCache() { return TK_OK; }
TK_API TK_RESULT TKUpdateCachePath(const char *, size_t) { return TK_OK; }
}
