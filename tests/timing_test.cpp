#define LTENGINE_GLOBAL_BASIC_TYPES

#include <catch2/catch_test_macros.hpp>

#include <LTEngine/tick_system.hpp>
#include <LTEngine/timer.hpp>


TEST_CASE("The tick system should correctly call the callbacks", "[tick_system]") {
	LTEngine::TickSystem tickSystem;
	tickSystem.setTickDelay(0.1f);

	tickSystem.registerTick("test_tick1", 2);
	tickSystem.registerTick("test_tick2", 4);

	bool tick1 = false;
	bool tick2 = false;

	*tickSystem.getTickEvent("test_tick1") += [&tick1](u64 tick) {
		tick1 = true;
	};
	*tickSystem.getTickEvent("test_tick2") += [&tick2](u64 tick) {
		tick2 = true;
	};

	tickSystem.step(0.1f);
	REQUIRE_FALSE(tick1);
	REQUIRE_FALSE(tick2);

	tickSystem.step(0.1f);
	REQUIRE(tick1);
	REQUIRE_FALSE(tick2);

	tickSystem.step(0.1f);
	tickSystem.step(0.1f);
	REQUIRE(tick1);
	REQUIRE(tick2);
}

TEST_CASE("The timer should correctly call the callback", "[timer]") {
	LTEngine::Timer timer;

	const f32 time = 2.f;

	bool callbackCalled = false;

	timer.onEnd += [&callbackCalled]() {
		callbackCalled = true;
	};
	timer.start(time);

	timer.step(time / 2.f);
	REQUIRE(!callbackCalled);
	timer.step(time / 2.f);
	REQUIRE(callbackCalled);
}
