#ifndef TK_VERSION_H_
#define TK_VERSION_H_

extern "C" {
struct TK_Version {
  int major;
  int minor;
  int patch;
  int build_no;
  const char extra[64];
};

typedef struct TK_Version TK_Version;

void TK_GetVersion(TK_Version *);
}
#endif  // TK_VERSION_H_
