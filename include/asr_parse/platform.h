/*
 * platform.h
 *
 * */

#ifndef _VOICE_PLATFORM_H_
#define _VOICE_PLATFORM_H_

#include <stdio.h>
#include <string.h>

/* the max size of token list in meta node */
#define VOICE_META_NODE_TOKEN_MAX_SIZE 64

/* the max size of value in token */
#define VOICE_TOKEN_VALUE_MAX_SIZE 64

/* the max length of token in Action */
#define VOICE_ACTION_TOKEN_MAX_LEN 4

/* the max length of token in Action */
#define VOICE_ENGINE_RESULT_MAX_LEN 8

/* the max size of data in Sentence */
#define VOICE_SENTENCE_DATA_MAX_SIZE 2048

/* the max size of meta node counts in meta tree */
#define VOICE_META_TREE_NODE_MAX_CNTS 128


typedef enum {
    FALSE = 0,
    TRUE = 1,
} BOOL;

typedef enum {
    STATUS_FAILED = -1,
    STATUS_SUCCESS = 0,
} STATUS_E;

/*
  * For debug information
  */
#if 1
#define voice_log_error(fmt...)   printf("[ERROR] %s(%d): ", __FUNCTION__, __LINE__);printf(fmt)
#define voice_log_warning(fmt...) printf("[WARNING] %s(%d): ", __FUNCTION__, __LINE__);printf(fmt)
#define voice_log_info(fmt...)    printf("[INFO] %s(%d): ", __FUNCTION__, __LINE__);printf(fmt)
#define voice_log_debug(fmt...)   printf("[DEBUG] %s(%d): ", __FUNCTION__, __LINE__);printf(fmt)
#else
#define voice_log_error(fmt...)
#define voice_log_warning(fmt...)
#define voice_log_info(fmt...)
#define voice_log_debug(fmt...)
#endif

#endif /* _VOICE_PLATFORM_H_ */

