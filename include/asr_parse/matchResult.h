
/***
 *
 *  matchResult.h
 *
 ***/

#ifndef _CMATCH_RESULT_H_
#define _CMATCH_RESULT_H_

#include "platform.h"

typedef struct _Token Token;
typedef struct _MetaNode MetaNode;

typedef enum {
    MATCH_RESULT_ERROR      = -2,
    MATCH_RESULT_A_BETTER_B = -1,
    MATCH_RESULT_A_EQUAL_B  = 0,
    MATCH_RESULT_B_BETTER_A = 1,
} MATCH_RESULT_E;

typedef struct _MatchResult {
    int offset;
    Token* token;
    MetaNode* node;
} MatchResult;


int voice_match_result_init(MatchResult* result);

int voice_match_result_set_token(MatchResult* result, int offset, Token* token);
int voice_match_result_set_mete_node(MatchResult* result, MetaNode* node);

int voice_match_result_get_offset(MatchResult* result);
Token* voice_match_result_get_token(MatchResult* result);
MetaNode* voice_match_result_get_mete_node(MatchResult* result);

int voice_match_result_status(MatchResult* result);
int voice_match_result_compare(MatchResult* resultA, MatchResult* resultB);
int voice_match_result_copy(MatchResult* dst, MatchResult* src);

#endif /* _CMATCH_RESULT_H_ */


