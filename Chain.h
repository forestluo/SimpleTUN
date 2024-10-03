#ifndef _SIMPLE_CHAIN_H
#define _SIMPLE_CHAIN_H

////////////////////////////////////////////////////////////////////////////////
//
// General including files
//
// Including the files for the system.
//
// These including files are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

typedef struct tagChainNode
{
	//Next
	struct tagChainNode* lpNext;
	//Previous
	struct tagChainNode* lpPrevious;

	//Data
	_OBJECT lpObject;

}

ChainNode;

typedef struct tagSimpleChain
{
	//Capacity
	_UINT32 nCapacity;
	//Count
	_UINT32 nCount;

	//Root Node
	ChainNode nodeRoot;

}

SimpleChain;

////////////////////////////////////////////////////////////////////////////////
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

extern void InitializeChain(SimpleChain* pChain);
extern void UninitializeChain(SimpleChain* pChain);

extern void RemoveChainObjects(SimpleChain* pChain);
extern void DeleteChainObjects(SimpleChain* pChain);

extern _BOOL IsChainFull(SimpleChain* pChain);
extern _BOOL IsChainEmpty(SimpleChain* pChain);

extern ChainNode* FindChainNode(SimpleChain* pChain,_OBJECT lpObject);

extern _BOOL InsertChainObject(SimpleChain* pChain,_OBJECT lpObject);
extern _BOOL RemoveChainObject(SimpleChain* pChain,_OBJECT lpObject);

extern _OBJECT RemoveChainHead(SimpleChain* pChain);
extern _OBJECT RemoveChainTail(SimpleChain* pChain);

extern _OBJECT GetNextChainObject(SimpleChain* pChain);
extern _OBJECT GetPreviousChainObject(SimpleChain* pChain);

////////////////////////////////////////////////////////////////////////////////

#endif //End of the header file.
