/*
 * sentence.h
 *
 * */

#ifndef _VOICE_SENTENCE_H_
#define _VOICE_SENTENCE_H_

#include "platform.h"

typedef struct _Sentence {
    char data[VOICE_SENTENCE_DATA_MAX_SIZE];
    unsigned int length;
    unsigned int pos;
} Sentence;

int voice_sentence_init(Sentence* sentence);
int voice_sentence_set_data(Sentence* sentence, const char* data);
const char* voice_sentence_get_data(Sentence* sentence);
int voice_sentence_set_offset(Sentence* sentence, unsigned int offset);


#endif /* _VOICE_SENTENCE_H_ */

