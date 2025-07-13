#include "TransportCore/CDN/HTTPClient.h"

#include <curl/curl.h>

#include "TX/Assert.h"
#include "TransportCore/Global/Global.h"

namespace TransportCore {
HTTPClient::HTTPClient()
    : TX::RunLoop::Timer(0, TX::Duration::Second(1), kTimerRepeatAlways,
                         "HTTPClientTimer"),
      handle_(curl_multi_init()),
      run_loop_(GetMainRunLoop()) {
  TX_ASSERT(handle_, "curl_multi_init returned NULL");
}

HTTPClient::~HTTPClient() { curl_multi_cleanup(handle_); }

void HTTPClient::Start() { run_loop_->AddTimer(this); }

void HTTPClient::Stop() { run_loop_->RemoveTimer(this); }

void HTTPClient::OnTimeout(TX::RunLoop&, TX::RefPtr<TX::RunLoop::Scope>&) {

}

}  // namespace TransportCore
