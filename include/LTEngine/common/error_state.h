#pragma once

#include <LTCommon/types/inttypes.h>
#include <LTCommon/types/booltypes.h>


#define DEFINE_LTERROR_STATE_GET_ERROR_BODY(error_state) \
    return error_state##->_error;

#define DEFINE_LTERROR_STATE_GET_ERROR_MSG_BODY(error_state) \
    return error_state##->_message;

#define LTERROR_STATE_RUN_IF_FATAL(error_state, code) \
    if (##error_state##->_fatal) { \
        ##body## \
    }


typedef struct {
    enum lterror_type_e : u8 {
        LTERROR_TYPE_NONE = 0,

        LTERROR_TYPE_ALLOCATION,

        LTERROR_TYPE_OPEN,

        LTERROR_TYPE_CUSTOM
    } _error;
    bool _fatal;

    char *_message;
} lterror_state_t;

typedef enum lterror_type_e lterror_type_e;


lterror_state_t lterror_state_new();

void lterror_state_set_error(lterror_state_t *error_state, lterror_type_e error);
void lterror_state_set_error_message(lterror_state_t *error_state, char *message);
void lterror_clear_error(lterror_state_t *error_state);

lterror_type_e lterror_state_get_error(const lterror_state_t *error_state);
char *lterror_state_get_error_message(const lterror_state_t *error_state);
bool lterror_state_is_fatal(const lterror_state_t *error_state);
