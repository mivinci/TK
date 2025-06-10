#ifndef TK_ERROR_H_
#define TK_ERROR_H_

extern "C" {
enum TK_Errno {
  TK_Errno_Ok = 0,
  TK_Errno_Unknown,
  TK_Errno_NullPointer,
  TK_Errno_InvalidArgument,
  TK_Errno_OutOfMemory,
  TK_Errno_Timeout,
  TK_Errno_NotFound,
  TK_Errno_AlreadyExists,
  TK_Errno_PermissionDenied,
  TK_Errno_OperationFailed,
};

typedef enum TK_Errno TK_Errno;
}

#endif  // TK_ERROR_H_
