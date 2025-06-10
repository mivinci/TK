#include <map>

#include "TX/Ref.h"
#include "gtest/gtest.h"

namespace TX {

struct RefTest : testing::Test {
  void SetUp() override { X_deleted = 0; }
  static int X_deleted;
};

int RefTest::X_deleted = 0;

struct X final : RefCounted<X> {
  ~X() override { RefTest::X_deleted++; }
};

TEST_F(RefTest, Ref) {
  {
    Ref a(*new X);
    EXPECT_EQ(a->refCount(), 1);
    Ref<X> b = a;
    EXPECT_EQ(a->refCount(), 2);
    EXPECT_EQ(b->refCount(), 2);
    Ref c(*new X);
    EXPECT_EQ(c->refCount(), 1);
    b = c;
    EXPECT_EQ(a->refCount(), 1);
    EXPECT_EQ(b->refCount(), 2);
    EXPECT_EQ(c->refCount(), 2);
  }
  EXPECT_EQ(X_deleted, 2);
}

TEST_F(RefTest, RefPtr) {
  {
    RefPtr a(new X);
    EXPECT_EQ(a->refCount(), 1);
    a = nullptr;
    EXPECT_EQ(a, nullptr);
    EXPECT_EQ(X_deleted, 1);
    RefPtr b(new X);
    a = b;
    EXPECT_EQ(a->refCount(), 2);
    EXPECT_EQ(b->refCount(), 2);
    RefPtr<X> c;
    EXPECT_EQ(c, nullptr);
  }
  EXPECT_EQ(X_deleted, 2);
}

TEST_F(RefTest, RefContainer) {
  std::map<int, Ref<X>> m;
  Ref a = adoptRef(*new X);
  m.emplace(0, a);
  EXPECT_EQ(a->refCount(), 2);
  EXPECT_EQ(m.at(0), a);
  // EXPECT_EQ(m[0], a);
  // m[0] will do a `Ref<X> a` causing a compile error since there's no
  // constructor with empty arguments for Ref. weired.

  std::set<Ref<X>> s;
  s.emplace(a);
  EXPECT_EQ(a->refCount(), 3);
  EXPECT_EQ(s.find(a).operator*(), a);

  std::vector<Ref<X>> v;
  v.emplace_back(a);
  EXPECT_EQ(a->refCount(), 4);
  EXPECT_EQ(v.at(0), a);
  EXPECT_EQ(v[0], a);
}
}  // namespace TX
