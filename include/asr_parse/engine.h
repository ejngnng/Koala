/*
 * engine.h
 *
 * */

#ifndef _VOICE_ENGINE_H_
#define _VOICE_ENGINE_H_

#include "matchResult.h"

typedef struct _Engine {
    MatchResult steps[VOICE_ENGINE_RESULT_MAX_LEN];
    unsigned int counts;
    MetaNode* current;

    BOOL completed;
} Engine;

int voice_engine_init(Engine* engine);
int voice_engine_reset(Engine* engine);
int voice_engine_execute(Engine* engine, MetaTree* tree, Sentence* sentence, MatchResult* result);
int voice_engine_completed(Engine* engine);
int voice_engine_build_action(Engine* engine, Action* action);

#endif /* _VOICE_ENGINE_H_ */
