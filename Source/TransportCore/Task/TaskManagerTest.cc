#include "TransportCore/Global/Global.h"
#include "TransportCore/Task/TaskManager.h"
#include "gtest/gtest.h"

namespace TransportCore {
class TaskManagerTest : public ::testing::Test {
 public:
  static void SetUpTestSuite() {}
  static void TearDownTestSuite() {}
  void SetUp() override { num_scheduled = 0; }
  void TearDown() override {}

  static int num_scheduled;
};

int TaskManagerTest::num_scheduled = 0;

void MockTaskScheduleCallback(uint64_t tick, void *context) {
  TaskManagerTest::num_scheduled++;
}

TEST_F(TaskManagerTest, GenTaskId) {
  constexpr int32_t base = kTaskIdBase;
  TaskManager mgr;
  for (int i = 0; i < base; i++) {
    TransportCoreTaskContext context{};
    context.kind = kTransportCoreTaskKindUnSpec;
    const int32_t id = mgr.CreateTask(context);
    ASSERT_EQ((id / base) - 1,
              static_cast<int32_t>(kTransportCoreTaskKindUnSpec));
    ASSERT_EQ(id % base, i);
  }
}

TEST_F(TaskManagerTest, Start) {
  TaskManager mgr;
  mgr.Start();
  sleep(3);
  mgr.Stop();
  ASSERT_EQ(mgr.GetTick(), 3);
}

TEST_F(TaskManagerTest, TaskLifeCycle) {
  TaskManager mgr;
  TransportCoreTaskContext context{};
  context.keyid = "abc";
  context.kind = kTransportCoreTaskKindUnSpec;
  context.schedule = MockTaskScheduleCallback;
  const int32_t task_id = mgr.CreateTask(context);
  ASSERT_TRUE(task_id > 0);
  mgr.StartTask(task_id);
  sleep(1);
  mgr.StopTask(task_id);
  ASSERT_EQ(num_scheduled, 1);
}

}  // namespace TransportCore
