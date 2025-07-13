#ifdef LTENGINE_COMPONENT_C_API
#include <LTEngine/c_api/random/random.h>
#include <LTEngine/random/random.hpp>


using namespace LTEngine;


class CRandom : public Random::Random {
public:
	CRandom(LTEngine_CustomRandomFuncs funcs) {
		_ctx = funcs.init();
		_funcs = funcs;
	}

	~CRandom() override {
		_funcs.free(_ctx);
	}


	u8 next_u8() override {
		return _funcs.next_u8(_ctx);
	}

	u16 next_u16() override {
		return _funcs.next_u16(_ctx);
	}

	u32 next_u32() override {
		return _funcs.next_u32(_ctx);
	}

	u64 next_u64() override {
		return _funcs.next_u64(_ctx);
	}


	i8 next_i8() override {
		return _funcs.next_i8(_ctx);
	}

	i16 next_i16() override {
		return _funcs.next_i16(_ctx);
	}

	i32 next_i32() override {
		return _funcs.next_i32(_ctx);
	}

	i64 next_i64() override {
		return _funcs.next_i64(_ctx);
	}


	f32 next_f32() override {
		return _funcs.next_f32(_ctx);
	}

	f64 next_f64() override {
		return _funcs.next_f64(_ctx);
	}


	void next_bytes(void *data, size_t size) {
		_funcs.next_bytes(_ctx, data, size);
	}

private:
	void *_ctx;
	LTEngine_CustomRandomFuncs _funcs;
};


LTEngine_HRandom lt_engine_custom_random(LTEngine_CustomRandomFuncs funcs) {
	return {{ new CRandom(funcs) }};
}

void lt_engine_custom_random_free(LTEngine_HRandom handle) {
	delete (Random::Random *)handle.handle.ptr;
}


LTEngine_u8 lt_engine_random_next_u8(LTEngine_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_u8();
}

LTEngine_u16 lt_engine_random_next_u16(LTEngine_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_u16();
}

LTEngine_u32 lt_engine_random_next_u32(LTEngine_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_u32();
}

LTEngine_u64 lt_engine_random_next_u64(LTEngine_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_u64();
}


LTEngine_i8 lt_engine_random_next_i8(LTEngine_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_i8();
}

LTEngine_i16 lt_engine_random_next_i16(LTEngine_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_i16();
}

LTEngine_i32 lt_engine_random_next_i32(LTEngine_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_i32();
}

LTEngine_i64 lt_engine_random_next_i64(LTEngine_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_i64();
}


LTEngine_f32 lt_engine_random_next_f32(LTEngine_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_f32();
}

LTEngine_f64 lt_engine_random_next_f64(LTEngine_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_f64();
}


void lt_engine_random_next_bytes(LTEngine_HRandom handle, void *data, size_t size) {
	((Random::Random *)handle.handle.ptr)->next_bytes(data, size);
}

#endif
