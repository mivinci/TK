#pragma once
namespace TP {
enum class Status : int {
  Ok,
};

class Error {};

#define TP_RESULT Status
#define TP_ERR(e) Status::e
#define TP_OK Status::Ok
}
