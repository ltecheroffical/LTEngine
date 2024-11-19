#include <acutest.h>

#include <LTEngine/tick_system.hpp>
#include <LTEngine/timer.hpp>


void test_tick_system() {
	LTEngine::TickSystem tickSystem;
	tickSystem.setTickDelay(0.1f);

	tickSystem.registerTick("test_tick1", 2);
	tickSystem.registerTick("test_tick2", 4);

	bool tick1 = false;
	bool tick2 = false;

	tickSystem.setTickCallback("test_tick1", [&tick1](u64 tick) { tick1 = true; });
	tickSystem.setTickCallback("test_tick2", [&tick2](u64 tick) { tick2 = true; });

	tickSystem.step(0.1f);
	TEST_CHECK(!tick1 && !tick2);

	tickSystem.step(0.1f);
	TEST_CHECK(tick1);

	tickSystem.step(0.1f);
	tickSystem.step(0.1f);
	TEST_CHECK(tick1 && tick2);
}

void test_timer() {
	LTEngine::Timer timer;

	const f32 time = 2.f;

	bool callbackCalled = false;

	timer.setCallback([&callbackCalled]() { callbackCalled = true; });
	timer.start(time);

	timer.step(time / 2.f);
	TEST_CHECK(!callbackCalled);
	timer.step(time / 2.f);
	TEST_CHECK(callbackCalled);
}


TEST_LIST = {{"test_tick_system", test_tick_system},
             {"test_timer", test_timer},

             {NULL, NULL}};
