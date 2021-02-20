#include <vector>
#include <iostream>
#include <chrono>
#include "ecsmanager.hpp"

struct DemoComponent1 : public ecs::Component
{
    int val;
    double an_val;
};

struct DemoComponent2 : public ecs::Component
{
    int val;
    std::string an_val;
};

struct DemoComponent3 : public ecs::Component
{
    int val;
    bool an_val;
};

struct DemoComponent4 : public ecs::Component
{
    int val;
    short an_val = 13;
};

int main()
{
    using namespace ecs;
    using namespace std;
    using namespace std::chrono;

    auto start = high_resolution_clock::now();

    size_t ar_size = 10000;
    std::vector<Entity> entities(ar_size);

    for (auto& en: entities) {
        en.addComponent<DemoComponent1>();
        en.addComponent<DemoComponent2>();
        en.addComponent<DemoComponent3>();
        en.addComponent<DemoComponent4>();
    }

    short a;
    for (auto& en: entities) {
        for (size_t i = 0; i < 1000; ++i) {
            a = en.getComponent<DemoComponent4>()->an_val;
            ++a;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << duration.count() << endl;

    return 0;
}
