#ifndef TK_EXPORT_H_
#define TK_EXPORT_H_

#undef TK_API
#if defined(TK_STATIC)
#define TK_API
#elif defined(_WIN32) || defined(__CYGWIN__)
#if defined(BUILD_TK)
#define TK_API __declspec(dllexport)
#else
#define TK_API __declspec(dllimport)
#endif // defined(BUILD_TK)
#elif defined(__GNUC__) || defined(__clang__)
#define TK_API __attribute__((visibility("default")))
#endif // defined(TK_STATIC)

#endif // TK_API_EXPORT_H_
