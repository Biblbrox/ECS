#include <gtest/gtest.h>
#include "../ecs.hpp"

using namespace ecs;

struct DummyComponent : Component
{

};

struct DataComponent : Component
{
    std::string name;
    size_t number;
};

// Demonstrate some basic assertions.
TEST(EntityTest, TestAddComponent) {
    Entity en(1);
    en.addComponent<DummyComponent>();

    // Test component created
    auto dummy_comp = en.getComponent<DummyComponent>();
    EXPECT_NE(dummy_comp, nullptr);

    // Test change value of component
    en.addComponent<DataComponent>();
    auto data_comp = en.getComponent<DataComponent>();
    data_comp->name = "TestName";
    data_comp->number = 42;

    // They must be equal
    EXPECT_EQ(data_comp->name, en.getComponent<DataComponent>()->name);
    EXPECT_EQ(data_comp->number, en.getComponent<DataComponent>()->number);
}