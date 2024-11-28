#ifndef _LTENGINE_FLOATTYPES_H_
#define _LTENGINE_FLOATTYPES_H_


typedef float LTEngine_float32;
typedef double LTEngine_float64;
typedef long double LTEngine_float128;

typedef LTEngine_float32 LTEngine_f32;
typedef LTEngine_float64 LTEngine_f64;
typedef LTEngine_float128 LTEngine_f128;


#ifdef __cplusplus

namespace LTEngine {
	typedef LTEngine_float32 float32;
	typedef LTEngine_float64 float64;
	typedef LTEngine_float128 float128;

	typedef LTEngine_f32 f32;
	typedef LTEngine_f64 f64;
	typedef LTEngine_f128 f128;
} // namespace LTEngine
#endif


#ifdef LTENGINE_GLOBAL_BASIC_TYPES

typedef LTEngine_float32 float32;
typedef LTEngine_float64 float64;
typedef LTEngine_float128 float128;

typedef LTEngine_f32 f32;
typedef LTEngine_f64 f64;
typedef LTEngine_f128 f128;

#endif
#endif
