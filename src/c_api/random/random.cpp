#ifdef LTCORE_COMPONENT_C_API
#include <LTCore/c_api/random/random.h>
#include <LTCore/random/random.hpp>


using namespace LTCore;


class CRandom : public Random::Random {
public:
	CRandom(LTCore_CustomRandomFuncs funcs) {
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
	LTCore_CustomRandomFuncs m_funcs;
};


LTCore_HRandom LTCore_CustomRandom(LTCore_CustomRandomFuncs funcs) {
	return {{ new CRandom(funcs) }};
}

void LTCore_CustomRandom_free(LTCore_HRandom handle) {
	delete (Random::Random *)handle.handle.ptr;
}


LTCore_u8 LTCore_Random_next_u8(LTCore_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_u8();
}

LTCore_u16 LTCore_Random_next_u16(LTCore_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_u16();
}

LTCore_u32 LTCore_Random_next_u32(LTCore_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_u32();
}

LTCore_u64 LTCore_Random_next_u64(LTCore_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_u64();
}


LTCore_i8 LTCore_Random_next_i8(LTCore_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_i8();
}

LTCore_i16 LTCore_Random_next_i16(LTCore_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_i16();
}

LTCore_i32 LTCore_Random_next_i32(LTCore_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_i32();
}

LTCore_i64 LTCore_Random_next_i64(LTCore_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_i64();
}


LTCore_f32 LTCore_Random_next_f32(LTCore_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_f32();
}

LTCore_f64 LTCore_Random_next_f64(LTCore_HRandom handle) {
	return ((Random::Random *)handle.handle.ptr)->next_f64();
}


void LTCore_Random_nextBytes(LTCore_HRandom handle, void *data, size_t size) {
	((Random::Random *)handle.handle.ptr)->nextBytes(data, size);
}

#endif
