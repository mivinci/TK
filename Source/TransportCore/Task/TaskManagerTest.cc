#include "TransportCore/Task/TaskManager.h"
#include "gtest/gtest.h"

namespace TransportCore {
class TaskManagerTest : public testing::Test {};

TEST_F(TaskManagerTest, GenTaskId) {
  constexpr int32_t base = kTaskIdBase;
  TaskManager manager;
  for (int i = 0; i < base; i++) {
    Task::Context context;
    context.kind = Task::Kind::kTransportCoreTaskKindPlain;
    const int32_t id = manager.CreateTask(context);
    ASSERT_EQ(id / base,
              static_cast<int32_t>(Task::Kind::kTransportCoreTaskKindPlain));
    ASSERT_EQ(id % base, i);
  }
}

TEST_F(TaskManagerTest, Start) {
  TaskManager manager;
  manager.Start();
}

}  // namespace TransportCore
