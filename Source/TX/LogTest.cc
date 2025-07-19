#include "TX/Log.h"
#include "gtest/gtest.h"

namespace TX {
class MockReporter final : public Logger::Reporter {
 public:
  MockReporter() : n(0) {}
  void Report(const Logger::Log &) override { n++; }
  int n;
};

TEST(LogTest, Simple) {
  TX_DEBUG("The ultimate answer to the universe is %d", 42);
  EXPECT_ANY_THROW(TX_THROW("This is an exception."));
}

TEST(LogTest, Reporter) {
  const auto r = new MockReporter;
  Logger::SetReportCallback(r);
  Logger::SetLevel(Logger::Level::Error);
  TX_DEBUG("debug");
  TX_INFO("info");
  TX_WARN("warn");
  TX_ERROR("error");
  EXPECT_EQ(r->n, 1);
}
}  // namespace TX
