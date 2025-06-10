#pragma once

#include "TX/Log.h"

namespace TP {
#define TP_DEBUG(...) TX_DEBUG_SCOPE("TP", __VA_ARGS__)
#define TP_INFO(...) TX_DEBUG_SCOPE("TP", __VA_ARGS__)
#define TP_WARN(...) TX_DEBUG_SCOPE("TP", __VA_ARGS__)
#define TP_ERROR(...) TX_DEBUG_SCOPE("TP", __VA_ARGS__)
#define TP_FATAL(...) TX_DEBUG_SCOPE("TP", __VA_ARGS__)
} // namespace TP
