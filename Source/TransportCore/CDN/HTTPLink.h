#pragma once

#include "TransportCore/CDN/HTTPHeader.h"

namespace TransportCore {

class HTTPLink {
 public:
  class Observer {
   public:
    virtual ~Observer() = default;
    virtual void OnDomainResolve(int32_t) = 0;
    virtual void OnHeaderRecv(int32_t, HTTPHeader) = 0;
    virtual void OnDataRecv(int32_t, char *, size_t) = 0;
    virtual void OnError(int32_t, int32_t) = 0;
  };

  explicit HTTPLink(int32_t link_id, Observer *observer);

 private:
  int32_t link_id_;
  Observer *observer_;
  void *handle_;
};

}  // namespace TransportCore
