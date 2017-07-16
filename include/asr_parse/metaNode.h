/*
 * metaNode.h
 *
 * */

#ifndef _VOICE_META_NODE_H_
#define _VOICE_META_NODE_H_

#include "sentence.h"
#include "token.h"
#include "matchResult.h"


typedef struct _MetaNode
{
    struct _MetaNode* parent;
    struct _MetaNode* child;
    struct _MetaNode* brother;

    Token list[VOICE_META_NODE_TOKEN_MAX_SIZE];
    unsigned int counts;
} MetaNode;

int voice_meta_node_init(MetaNode* node);
int voice_meta_node_match_child(MetaNode* node, Sentence* sentence, MatchResult* result);

BOOL voice_meta_node_has_child(MetaNode* node);
int voice_meta_node_add_child(MetaNode* node, MetaNode* child);
int voice_meta_node_add_brother(MetaNode* node, MetaNode* brother);
int voice_meta_node_add_token(MetaNode* node, Token* token);


#endif /* _VOICE_META_NODE_H_ */
