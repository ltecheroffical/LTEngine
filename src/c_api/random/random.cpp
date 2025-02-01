#include <LTEngine/c_api/random/random.h>
#include <LTEngine/random/random.hpp>


using namespace LTEngine;


class CRandom : public Random::Random {
public:
	CRandom(LTEngine_RandomFuncs funcs) {
		m_ctx = funcs.init();
		m_funcs = funcs;
	}

	~CRandom() override {
		m_funcs.free(m_ctx);
	}


	u8 next_u8() override {
		return m_funcs.next_u8(m_ctx);
	}

	u16 next_u16() override {
		return m_funcs.next_u16(m_ctx);
	}

	u32 next_u32() override {
		return m_funcs.next_u32(m_ctx);
	}

	u64 next_u64() override {
		return m_funcs.next_u64(m_ctx);
	}


	i8 next_i8() override {
		return m_funcs.next_i8(m_ctx);
	}

	i16 next_i16() override {
		return m_funcs.next_i16(m_ctx);
	}

	i32 next_i32() override {
		return m_funcs.next_i32(m_ctx);
	}

	i64 next_i64() override {
		return m_funcs.next_i64(m_ctx);
	}


	f32 next_f32() override {
		return m_funcs.next_f32(m_ctx);
	}

	f64 next_f64() override {
		return m_funcs.next_f64(m_ctx);
	}


	void nextBytes(void *data, size_t size) override {
		m_funcs.nextBytes(m_ctx, data, size);
	}

private:
	void *m_ctx;
	LTEngine_RandomFuncs m_funcs;
};


LTEngine_HRandom LTEngine_Random_init(LTEngine_RandomFuncs funcs) {
	return new CRandom(funcs);
}

void LTEngine_Random_free(LTEngine_HRandom handle) {
	delete (Random::Random *)handle;
}


LTEngine_u8 LTEngine_Random_next_u8(LTEngine_HRandom handle) {
	return ((Random::Random *)handle)->next_u8();
}

LTEngine_u16 LTEngine_Random_next_u16(LTEngine_HRandom handle) {
	return ((Random::Random *)handle)->next_u16();
}

LTEngine_u32 LTEngine_Random_next_u32(LTEngine_HRandom handle) {
	return ((Random::Random *)handle)->next_u32();
}

LTEngine_u64 LTEngine_Random_next_u64(LTEngine_HRandom handle) {
	return ((Random::Random *)handle)->next_u64();
}


LTEngine_i8 LTEngine_Random_next_i8(LTEngine_HRandom handle) {
	return ((Random::Random *)handle)->next_i8();
}

LTEngine_i16 LTEngine_Random_next_i16(LTEngine_HRandom handle) {
	return ((Random::Random *)handle)->next_i16();
}

LTEngine_i32 LTEngine_Random_next_i32(LTEngine_HRandom handle) {
	return ((Random::Random *)handle)->next_i32();
}

LTEngine_i64 LTEngine_Random_next_i64(LTEngine_HRandom handle) {
	return ((Random::Random *)handle)->next_i64();
}


LTEngine_f32 LTEngine_Random_next_f32(LTEngine_HRandom handle) {
	return ((Random::Random *)handle)->next_f32();
}

LTEngine_f64 LTEngine_Random_next_f64(LTEngine_HRandom handle) {
	return ((Random::Random *)handle)->next_f64();
}


void LTEngine_Random_nextBytes(LTEngine_HRandom handle, void *data, size_t size) {
	((Random::Random *)handle)->nextBytes(data, size);
}
