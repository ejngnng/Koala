/*
 * syntax.h
 *
 * */

#ifndef _VOICE_SYNTAX_H_
#define _VOICE_SYNTAX_H_

#include "sentence.h"
#include "action.h"
#include "metaTree.h"
#include "engine.h"

typedef struct _Syntax {
    MetaTree tree;
    Engine engine;
} Syntax;

int voice_syntax_init(Syntax* syntax);
int voice_syntax_reset(Syntax* syntax);
int voice_syntax_destroy(Syntax* syntax);
int voice_syntax_parse_sentece(Syntax* syntax, Sentence* sentence, Action* action);


#endif /* _VOICE_SYNTAX_H_ */

