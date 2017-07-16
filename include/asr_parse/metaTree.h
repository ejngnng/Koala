/*
 * metaTree.h
 *
 * */

#ifndef _VOICE_META_TREE_H_
#define _VOICE_META_TREE_H_

#include "metaNode.h"

typedef struct _MetaTree
{
    MetaNode* root;
} MetaTree;


int voice_meta_tree_init(MetaTree* tree);
MetaNode* voice_meta_tree_root(MetaTree* tree);
int voice_meta_tree_destory(MetaTree* tree);



#endif /* _VOICE_META_TREE_H_ */

