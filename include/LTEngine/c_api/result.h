#ifndef _LTENGINE_RESULT_H_
#define _LTENGINE_RESULT_H_

#include <stdbool.h>

#include <LTEngine/common/compiler_utils.h>


typedef enum {
	LTENGINE_RESULT_SUCCESS = 0,

	LTENGINE_RESULT_ERROR,
	LTENGINE_RESULT_ERROR_MALFORMED_ARGUMENT,
	LTENGINE_RESULT_ERROR_MEMORY,
	LTENGINE_RESULT_ERROR_INVALID_ARGUMENT,
	LTENGINE_RESULT_ERROR_NOT_IMPLEMENTED,

	// Anything that can't be recovered
	LTENGINE_RESULT_FATAL,
	// Use example: Resizing a batch of objects and one fails to be resized
	LTENGINE_RESULT_FATAL_MEMORY,
} LTEngine_result_type_t;


// This object can be allocated on the stack due to it being entirely written in C
typedef struct {
	LTEngine_result_type_t _type;
	const char *_message;

	bool _value_present;
	void *_value;
} LTEngine_result_t;


#ifdef __cplusplus
extern "C" {
#endif

LTEngine_result_t LTENGINE_API LTEngine_result_create(LTEngine_result_type_t type, const char *message);
LTEngine_result_t LTENGINE_API LTEngine_result_create_with_value(LTEngine_result_type_t type, void *value);

LTEngine_result_type_t LTENGINE_API LTEngine_result_get_type(LTEngine_result_t *result);
const char *LTENGINE_API LTEngine_result_get_message(LTEngine_result_t *result);

void *LTENGINE_API LTEngine_result_get_value(LTEngine_result_t *result);


#ifdef __cplusplus
}
#endif

#endif
