#pragma once

#include "TransportCore/CDN/HTTPLink.h"

namespace TransportCore {
class HTTPRequest final : public HTTPLink::Observer {
public:
  struct Event {

  };

  class Observer {
  public:
    virtual ~Observer() = default;
    virtual void OnHTTPEvent(Event) = 0;
  };

 protected:
  void OnDomainResolve(int32_t) override;
  void OnHeaderRecv(int32_t, HTTPHeader) override;
  void OnDataRecv(int32_t, char*, size_t) override;
  void OnError(int32_t, int32_t) override;
};
}  // namespace TransportCore
