#include <gtest/gtest.h>
#include <ghStackAllocator.h>

class MemoryTest : public ::testing::Test {
protected:
    StackAllocator *allocator;

    virtual void SetUp() {
        allocator = new StackAllocator(32);
        allocator->v_initialize();
    }

    virtual void TearDown() {
        allocator->v_destroy();
    }
};


class Dummy {
public:
    int x;
    float y;

    Dummy() : x(0), y(0.0f) {}
    Dummy(int xp, float yp) : x(xp), y(yp) {}
};


TEST_F(MemoryTest, allocationArea) {
        EXPECT_EQ(allocator->m_pLastAddr, allocator->m_pFirstAddr + (32 * sizeof(char)));
}

TEST_F(MemoryTest, allocationShouldBeContiguous) {
    void *ptr1 = allocator->alloc(16);
    void *ptr2 = allocator->alloc(16);

    ASSERT_TRUE(ptr1 != nullptr);
    ASSERT_TRUE(ptr2 != nullptr);
    EXPECT_GT(ptr2, ptr1);
    EXPECT_EQ(ptr2, ptr1 + (16 * sizeof(char)));
}


TEST_F(MemoryTest, noMoreRoomInAllocatorShouldReturnNull) {
    void *ptr1 = allocator->alloc(32);

    ASSERT_TRUE(ptr1 != nullptr);
    void *mustBeNull = allocator->alloc(1);
    EXPECT_TRUE(mustBeNull == nullptr);
}

TEST_F(MemoryTest, clearAllocator) {
    void *ptr1 = allocator->alloc(32);

    ASSERT_TRUE(ptr1 != nullptr);
    void *mustBeNull = allocator->alloc(32);
    EXPECT_TRUE(mustBeNull == nullptr);
    allocator->clear();
    void  *mustNotBeNull = allocator->alloc(32);
    EXPECT_TRUE(mustNotBeNull != nullptr);
}

TEST_F(MemoryTest, allocatedObjectShouldBeInitialized) {
    Dummy *ptr1 = allocator->alloc<Dummy>();

    ASSERT_TRUE(ptr1 != nullptr);
    EXPECT_EQ(ptr1->x, 0);
    EXPECT_EQ(ptr1->y, 0.0f);
    ptr1->x = 123;
    ptr1->y = 1.23f;
    EXPECT_EQ(ptr1->x, 123);
    EXPECT_EQ(ptr1->y, 1.23f);
}