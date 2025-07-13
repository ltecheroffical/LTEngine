#ifndef _LTENGINE_CONDITIONS_H_
#define _LTENGINE_CONDITIONS_H_

#include <math.h>
#include <float.h>

#include <LTEngine/common/types/floattypes.h>

#define LTENGINE_RETURN_VALUE_CONDITION(cond, value) if (cond) return value; (void)0
#define LTENGINE_RETURN_CONDITION(cond) if (cond) return; (void)0

#define LTENGINE_RETURN_VALUE_NULL(test, value) if (test == NULL) return value; (void)0
#define LTENGINE_RETURN_NULL(test) if (test == NULL) return; (void)0

#define LTENGINE_F32_EPSILON 0.000001
static inline int LTEngine_f32_eq(LTEngine_f32 a, LTEngine_f32 b) {
    float diff = fabsf(a - b);
    float max_val = fmaxf(fabsf(a), fabsf(b));
    if (max_val < FLT_MIN) max_val = FLT_MIN;
    return diff <= LTENGINE_F32_EPSILON * max_val;
}

#endif // _LTENGINE_CONDITIONS_H_
