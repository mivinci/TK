#ifndef TRANSPORT_CORE_API_BASE_H_
#define TRANSPORT_CORE_API_BASE_H_
#ifndef __cplusplus
#include <stdbool.h>
#endif
#include <stddef.h>  // NOLINT(*-deprecated-headers)
#include <stdint.h>  // NOLINT(*-deprecated-headers)

#undef TK_API
#if defined(TK_STATIC)
#define TK_API
#elif defined(_WIN32) || defined(__CYGWIN__)
#if defined(BUILD_TK)
#define TK_API __declspec(dllexport)
#else
#define TK_API __declspec(dllimport)
#endif  // defined(BUILD_TK)
#elif defined(__GNUC__) || defined(__clang__)
#define TK_API __attribute__((visibility("default")))
#endif  // defined(TK_STATIC)

#define TK_RESULT int
#define TK_OK 0
#define TK_ERR(e)
#endif  // TRANSPORT_CORE_API_BASE_H_
