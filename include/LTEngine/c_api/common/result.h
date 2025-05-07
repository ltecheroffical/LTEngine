#ifndef _LTENGINE_C_API_RESULT_H_
#define _LTENGINE_C_API_RESULT_H_
#ifdef LTENGINE_COMPONENT_C_API

#include <LTEngine/common/compiler_utils.h>


typedef enum {
	LTEngine_SUCCESS = 0,
	LTEngine_FAILURE,

	LTEngine_Error_MALLOC,
	LTEngine_Error_OS,

	LTEngine_Error_INVLAID_DATA,
	LTEngine_Error_CORRUPT_DATA,
	LTEngine_Error_INVALID_ARG,
	LTEngine_Error_UNIMPLMENTED,
	LTEngine_Error_CONFLICT,
	LTEngine_Error_ALREADY_EXISTS,
	LTEngine_Error_IMPOSSIBLE,
	LTEngine_Error_NOT_FOUND
} LTEngine_Error;


typedef struct LTENGINE_API {
	LTEngine_Error _type;
	bool _is_result_valid;
	void *_result;
} LTEngine_Result;


#ifdef __cplusplus
extern "C" {
#endif


LTEngine_Result LTENGINE_API LTEngine_Result_init(LTEngine_Error type);
LTEngine_Result LTENGINE_API LTEngine_Result_init_result(LTEngine_Error type, void *const result);

bool LTENGINE_API LTEngine_Result_get(LTEngine_Result *const result, void **out, LTEngine_Error *type);

#ifdef __cplusplus
}
#endif
#endif
#endif
