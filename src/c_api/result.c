#include <time.h>

#include <LTEngine/c_api/result.h>


LTEngine_result_t LTEngine_result_create(LTEngine_result_type_t type, const char *message) {
	return (LTEngine_result_t){._type = type, ._message = message, ._value_present = false};
}

LTEngine_result_t LTEngine_result_create_with_value(LTEngine_result_type_t type, void *value) {
	return (LTEngine_result_t){._type = type, ._message = NULL, ._value = value, ._value_present = true};
}


LTEngine_result_type_t LTEngine_result_get_type(LTEngine_result_t *result) {
	return result->_type;
}

const char *LTEngine_result_get_message(LTEngine_result_t *result) {
	return result->_message;
}


void *LTEngine_result_get_value(LTEngine_result_t *result) {
	if (!result->_value_present) { return NULL; }
	return result->_value;
}
