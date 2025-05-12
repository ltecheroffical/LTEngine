#ifdef LTCORE_COMPONENT_C_API
#include <LTCore/c_api/common/result.h>


LTCore_Result LTCore_Result_init(LTCore_Error type) {
	return (LTCore_Result){._type = type, ._is_result_valid = false};
}

LTCore_Result LTCore_Result_init_result(LTCore_Error type, void *const result) {
	return (LTCore_Result){._type = type, ._is_result_valid = true, ._result = result};
}


bool LTCore_Result_get(LTCore_Result *const result, void **out, LTCore_Error *type) {
	if (!result->_is_result_valid) {
		*type = result->_type;
		return false;
	}

	*type = result->_type;
	*out = result->_result;
	return true;
}

#endif