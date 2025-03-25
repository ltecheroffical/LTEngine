#ifdef LTENGINE_COMPONENT_C_API
#include <LTEngine/c_api/common/result.h>


LTEngine_Result LTEngine_Result_init(LTEngine_Error type) {
	return (LTEngine_Result){._type = type, ._is_result_valid = false};
}

LTEngine_Result LTEngine_Result_init_result(LTEngine_Error type, void *const result) {
	return (LTEngine_Result){._type = type, ._is_result_valid = true, ._result = result};
}


bool LTEngine_Result_get(LTEngine_Result *const result, void **out, LTEngine_Error *type) {
	if (!result->_is_result_valid) {
		*type = result->_type;
		return false;
	}

	*type = result->_type;
	*out = result->_result;
	return true;
}

#endif