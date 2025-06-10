#include "TransportCore/Task/TaskManager.h"
#include "gtest/gtest.h"

namespace TransportCore {
class TaskManagerTest : public testing::Test {};

class MockTaskListener final : public TaskListener {
  void onEvent(TaskEvent event) override {}
};

TEST_F(TaskManagerTest, GenTaskId) {
  constexpr int factor = 10, span = 1;
  const MockTaskListener listener;
  const TaskManager mgr(factor, span);
  for (int i = 0; i < factor; i++) {
    const int32_t id = mgr.CreateTask(Task::Kind::Auto, &listener);
    EXPECT_EQ(id / factor, static_cast<int32_t>(Task::Kind::Auto));
    EXPECT_EQ(id % factor, i);
  }
}

}  // namespace TransportCore
