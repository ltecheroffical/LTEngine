#ifndef _LTCORE_FLOATTYPES_H_
#define _LTCORE_FLOATTYPES_H_


typedef float LTCore_float32;
typedef double LTCore_float64;
typedef long double LTCore_float128;

typedef LTCore_float32 LTCore_f32;
typedef LTCore_float64 LTCore_f64;
typedef LTCore_float128 LTCore_f128;


#ifdef __cplusplus

namespace LTCore {
	typedef LTCore_float32 float32;
	typedef LTCore_float64 float64;
	typedef LTCore_float128 float128;

	typedef LTCore_f32 f32;
	typedef LTCore_f64 f64;
	typedef LTCore_f128 f128;
} // namespace LTCore
#endif


#ifdef LTCORE_GLOBAL_BASIC_TYPES

typedef LTCore_float32 float32;
typedef LTCore_float64 float64;
typedef LTCore_float128 float128;

typedef LTCore_f32 f32;
typedef LTCore_f64 f64;
typedef LTCore_f128 f128;

#endif
#endif
