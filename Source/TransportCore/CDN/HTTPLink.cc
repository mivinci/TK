#include "TransportCore/CDN/HTTPLink.h"

#include <curl/curl.h>

namespace TransportCore {
HTTPLink::HTTPLink(const int32_t link_id, Observer *observer)
    : link_id_(link_id), observer_(observer), handle_(curl_easy_init()) {}
}  // namespace TransportCore