#ifndef _LTCORE_C_API_RESULT_H_
#define _LTCORE_C_API_RESULT_H_
#ifdef LTCORE_COMPONENT_C_API

#include <LTCore/common/compiler_utils.h>


typedef enum {
	LTCore_SUCCESS = 0,
	LTCore_FAILURE,

	LTCore_Error_MALLOC,
	LTCore_Error_OS,

	LTCore_Error_INVLAID_DATA,
	LTCore_Error_CORRUPT_DATA,
	LTCore_Error_INVALID_ARG,
	LTCore_Error_UNIMPLMENTED,
	LTCore_Error_CONFLICT,
	LTCore_Error_ALREADY_EXISTS,
	LTCore_Error_IMPOSSIBLE,
	LTCore_Error_NOT_FOUND
} LTCore_Error;


typedef struct LTCORE_API {
	LTCore_Error _type;
	bool _is_result_valid;
	void *_result;
} LTCore_Result;


#ifdef __cplusplus
extern "C" {
#endif


LTCore_Result LTCORE_API LTCore_Result_init(LTCore_Error type);
LTCore_Result LTCORE_API LTCore_Result_init_result(LTCore_Error type, void *const result);

bool LTCORE_API LTCore_Result_get(LTCore_Result *const result, void **out, LTCore_Error *type);

#ifdef __cplusplus
}
#endif
#endif
#endif
