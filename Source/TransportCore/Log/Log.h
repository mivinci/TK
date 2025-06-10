#pragma once
#include "TX/Log.h"
namespace TransportCore {
static const char *scope = "TransportCore";
#define TC_INFO(...) TX_INFO_SCOPE(scope, __VA_ARGS__)
}

