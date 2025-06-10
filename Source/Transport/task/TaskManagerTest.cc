#include "Transport/task/TaskManager.h"
#include "gtest/gtest.h"

namespace TP {
class TaskManagerTest : public testing::Test {};

TEST_F(TaskManagerTest, genTaskId) {
  constexpr int factor = 10, span = 1;
  const TaskManager mgr(factor, span);
  for (int i = 0; i < factor; i++) {
    const int32_t id = mgr.CreateTask(Task::Kind::Auto);
    EXPECT_EQ(id / factor, static_cast<int32_t>(Task::Kind::Auto));
    EXPECT_EQ(id % factor, i);
  }
  EXPECT_EQ(mgr.CreateTask(), -1);
}

}  // namespace TP
