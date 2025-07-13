#include <gtest/gtest.h>

#include "TransportCore/CDN/HTTPLink.h"

class HTTPLinkTest : public ::testing::Test {};

namespace TransportCore {
TEST_F(HTTPLinkTest, Simple) { 
  HTTPLink link(0);
}
}  // namespace TransportCore
