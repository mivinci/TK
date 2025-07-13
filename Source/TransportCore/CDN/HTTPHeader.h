#pragma once
#include <string>

#include "TX/Platform.h"

namespace TransportCore {

class HTTPHeader {
public:
  enum class Key {
    kContentType,
    kContentLength,
  };

  explicit HTTPHeader() : content_length_(0) {}
  TX_NODISCARD std::string Get(Key key) const;
  void Set(Key key, std::string value);

 private:
  std::string content_type_;
  size_t content_length_;
};

} // TransportCore

