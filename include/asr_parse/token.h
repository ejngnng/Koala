/***
 *
 *  token.h
 *
 ***/

#ifndef _CTOKEN_H_
#define _CTOKEN_H_

#include "platform.h"
#include "matchResult.h"
#include "sentence.h"

typedef enum {
    TOKEN_TYPE_ERROR = -1,
    TOKEN_TYPE_NONE = 0,
    TOKEN_TYPE_ROOM = 1,
    TOKEN_TYPE_OBJECT = 2,
    TOKEN_TYPE_OPERA = 3,
} TOKEN_TYPE_E;

typedef struct _Token {
    char value[VOICE_TOKEN_VALUE_MAX_SIZE];
    TOKEN_TYPE_E type;
    unsigned int length;
} Token;

int voice_token_init(Token* token);
int voice_token_match(Token* token, Sentence* sentence, MatchResult* result);

const char* voice_token_get_value(Token* token);
TOKEN_TYPE_E voice_token_get_type(Token* token);
unsigned int voice_token_get_length(Token* token);

int voice_token_set(Token* token, const char* value, TOKEN_TYPE_E type);
int voice_token_copy(Token* dst, Token* src);


#endif /* _CTOKEN_H_ */

