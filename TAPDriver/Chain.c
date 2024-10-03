////////////////////////////////////////////////////////////////////////////////
//
// Global including files.
//
// Including the files for the system.
//
// These including files are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

#include "Global.h"

////////////////////////////////////////////////////////////////////////////////
//
// Internal definitions.
//
// These definitions are generally used internally.
//
////////////////////////////////////////////////////////////////////////////////

#define NO_CAPACITY_LIMITED									0xFFFFFFFF

////////////////////////////////////////////////////////////////////////////////
//
// Initialize chain.
//
////////////////////////////////////////////////////////////////////////////////

void InitializeChain(SimpleChain* pChain)
{
#ifdef _DEBUG
	assert(pChain != NULL);
#endif

	//Clear chain.
	memset(pChain,0,sizeof(SimpleChain));

	//Set capacity.
	//Unlimited.
	pChain->nCapacity = NO_CAPACITY_LIMITED;
	//Set count.
	pChain->nCount = 0;

	//Set chain root.
	//Set next.
	pChain->nodeRoot.lpNext = &pChain->nodeRoot;
	//Set previous.
	pChain->nodeRoot.lpPrevious = &pChain->nodeRoot;
	//Set root.
	pChain->nodeRoot.lpObject = &pChain->nodeRoot;
}

////////////////////////////////////////////////////////////////////////////////
//
// Uninitialize chain.
//
////////////////////////////////////////////////////////////////////////////////

void UninitializeChain(SimpleChain* pChain)
{
	ChainNode* lpCurrent;

#ifdef _DEBUG
	assert(pChain != NULL);
#endif

	//Set current.
	lpCurrent = &pChain->nodeRoot;
	//Browse chain.
	while(lpCurrent->lpNext != &pChain->nodeRoot)
	{
		//Get next.
		lpCurrent = lpCurrent->lpNext;

#ifdef _DEBUG
		assert(lpCurrent != NULL);
#endif

		//Keep next.
		pChain->nodeRoot.lpNext = lpCurrent->lpNext;
		//Keep previous.
		lpCurrent->lpNext->lpPrevious = &pChain->nodeRoot;

		//Delete current.
		free(lpCurrent);

		//Set current.
		lpCurrent = &pChain->nodeRoot;

		//Sub count.
		pChain->nCount --;
	}

#ifdef _DEBUG
	assert(pChain->nCount == 0);
#endif

	//Set chain root.
	//Set next.
	pChain->nodeRoot.lpNext = &pChain->nodeRoot;
	//Set previous.
	pChain->nodeRoot.lpPrevious = &pChain->nodeRoot;
	//Set root.
	pChain->nodeRoot.lpObject = &pChain->nodeRoot;
}

////////////////////////////////////////////////////////////////////////////////
//
// Remove chain objects.
//
////////////////////////////////////////////////////////////////////////////////

void RemoveChainObjects(SimpleChain* pChain)
{
	ChainNode* lpCurrent;

#ifdef _DEBUG
	assert(pChain != NULL);
#endif

	//Set current.
	lpCurrent = &pChain->nodeRoot;
	//Browse chain.
	while(lpCurrent->lpNext != &pChain->nodeRoot)
	{
		//Get next.
		lpCurrent = lpCurrent->lpNext;

#ifdef _DEBUG
		assert(lpCurrent != NULL);
#endif

		//Keep next.
		pChain->nodeRoot.lpNext = lpCurrent->lpNext;
		//Keep previous.
		lpCurrent->lpNext->lpPrevious = &pChain->nodeRoot;

		//Delete current.
		free(lpCurrent);

		//Set current.
		lpCurrent = &pChain->nodeRoot;

		//Sub count.
		pChain->nCount --;
	}

#ifdef _DEBUG
	assert(pChain->nCount == 0);
#endif

	//Set chain root.
	//Set next.
	pChain->nodeRoot.lpNext = &pChain->nodeRoot;
	//Set previous.
	pChain->nodeRoot.lpPrevious = &pChain->nodeRoot;
	//Set root.
	pChain->nodeRoot.lpObject = &pChain->nodeRoot;
}

////////////////////////////////////////////////////////////////////////////////
//
// Delete chain objects.
//
////////////////////////////////////////////////////////////////////////////////

void DeleteChainObjects(SimpleChain* pChain)
{
	ChainNode* lpCurrent;

#ifdef _DEBUG
	assert(pChain != NULL);
#endif

	//Set current.
	lpCurrent = &pChain->nodeRoot;
	//Browse chain.
	while(lpCurrent->lpNext != &pChain->nodeRoot)
	{
		//Get next.
		lpCurrent = lpCurrent->lpNext;

#ifdef _DEBUG
		assert(lpCurrent != NULL);
#endif

		//Keep next.
		pChain->nodeRoot.lpNext = lpCurrent->lpNext;
		//Keep previous.
		lpCurrent->lpNext->lpPrevious = &pChain->nodeRoot;

		//Delete object.
		if(lpCurrent->lpObject != NULL)
		{
			//Free object.
			free(lpCurrent->lpObject);
			//Set NULL.
			lpCurrent->lpObject = NULL;
		}

		//Delete current.
		free(lpCurrent);

		//Set current.
		lpCurrent = &pChain->nodeRoot;

		//Sub count.
		pChain->nCount --;
	}

#ifdef _DEBUG
	assert(pChain->nCount == 0);
#endif

	//Set chain root.
	//Set next.
	pChain->nodeRoot.lpNext = &pChain->nodeRoot;
	//Set previous.
	pChain->nodeRoot.lpPrevious = &pChain->nodeRoot;
	//Set root.
	pChain->nodeRoot.lpObject = &pChain->nodeRoot;
}

////////////////////////////////////////////////////////////////////////////////
//
// Is chain full.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL IsChainFull(SimpleChain* pChain)
{
#ifdef _DEBUG
	assert(pChain != NULL);
#endif

	//Check capacity.
	if(pChain->nCapacity != NO_CAPACITY_LIMITED)
	{
		//Check count.
		if(pChain->nCount >= pChain->nCapacity)
		{
			//Return true.
			return _TRUE;
		}
	}
	//Return false.
	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Is chain empty.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL IsChainEmpty(SimpleChain* pChain)
{
#ifdef _DEBUG
	assert(pChain != NULL);
#endif

	//Check count.
	if(pChain->nCount <= 0)
	{
		//Return true.
		return _TRUE;
	}
	//Return false.
	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Find chain node.
//
////////////////////////////////////////////////////////////////////////////////

ChainNode* FindChainNode(SimpleChain* pChain,_OBJECT lpObject)
{
	ChainNode* lpCurrent;

#ifdef _DEBUG
	assert(pChain != NULL);
#endif

	//Set current.
	lpCurrent = &pChain->nodeRoot;
	while(lpCurrent->lpNext != &pChain->nodeRoot)
	{
		//Get next.
		lpCurrent = lpCurrent->lpNext;

#ifdef _DEBUG
		assert(lpCurrent != NULL);
#endif

		//Check object.
		if(lpCurrent->lpObject == lpObject)
		{
			//Return node.
			return lpCurrent;
		}
	}
	//Return null.
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Insert chain object.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL InsertChainObject(SimpleChain* pChain,_OBJECT lpObject)
{
	ChainNode* lpCurrent = NULL;

#ifdef _DEBUG
	assert(pChain != NULL && lpObject != NULL);
#endif

	//Create a chain.
	lpCurrent = (ChainNode *)malloc(sizeof(ChainNode));
	//Check result.
	if(lpCurrent != NULL)
	{
		//Set object.
		lpCurrent->lpObject = lpObject;
		//Set previous.
		lpCurrent->lpPrevious = pChain->nodeRoot.lpPrevious;
		//Set next.
		lpCurrent->lpNext = &pChain->nodeRoot;

		//Set root.
		pChain->nodeRoot.lpPrevious->lpNext = lpCurrent;
		pChain->nodeRoot.lpPrevious = lpCurrent;

		//Add count.
		pChain->nCount ++;
		//Return true.
		return _TRUE;
	}

#ifdef _DEBUG
	PrintLine(stderr,"Chain::InsertChainObject : fail to create chain node !");
#endif
	//Return false.
	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Remove chain object.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL RemoveChainObject(SimpleChain* pChain,_OBJECT object)
{
	ChainNode* lpCurrent = NULL;

#ifdef _DEBUG
	assert(pChain != NULL && object != NULL);
#endif

	//Find object.
	lpCurrent = FindChainNode(pChain,object);
	//Check result
	if(lpCurrent != NULL)
	{
		//Check current node.
		if(pChain->nodeRoot.lpObject == lpCurrent)
		{
			//Set current node.
			pChain->nodeRoot.lpObject = &pChain->nodeRoot;
		}

		//Connect previous and next.
		lpCurrent->lpPrevious->lpNext = lpCurrent->lpNext;
		lpCurrent->lpNext->lpPrevious = lpCurrent->lpPrevious;
		//Set NULL pointer.
		lpCurrent->lpNext = NULL;
		lpCurrent->lpPrevious = NULL;
		lpCurrent->lpObject = NULL;
		//Delete current.
		free(lpCurrent);

		//Sub count.
		pChain->nCount --;
		//Return true.
		return _TRUE;
	}
	//Return false.
	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Remove chain head.
//
////////////////////////////////////////////////////////////////////////////////

_OBJECT RemoveChainHead(SimpleChain* pChain)
{
	_OBJECT lpObject = NULL;

#ifdef _DEBUG
	assert(pChain != NULL);
#endif

	//Check next.
	if(pChain->nodeRoot.lpNext != &pChain->nodeRoot)
	{
		//Get object.
		lpObject = pChain->nodeRoot.lpNext->lpObject;

#ifdef _DEBUG
		assert(lpObject != NULL);
#endif

		//Remove head.
		if(!RemoveChainObject(pChain,lpObject))
		{
#ifdef _DEBUG
			PrintLine(stderr,"Chain::RemoveChainHead : fail to remove chain object !");
#endif
		}
	}
	//Return object.
	return lpObject;
}

////////////////////////////////////////////////////////////////////////////////
//
// Remove chain tail.
//
////////////////////////////////////////////////////////////////////////////////

_OBJECT RemoveChainTail(SimpleChain* pChain)
{
	_OBJECT lpObject = NULL;

#ifdef _DEBUG
	assert(pChain != NULL);
#endif

	//Check previous.
	if(pChain->nodeRoot.lpPrevious != &pChain->nodeRoot)
	{
		//Get object.
		lpObject = pChain->nodeRoot.lpPrevious->lpObject;

#ifdef _DEBUG
		assert(lpObject != NULL);
#endif

		//Remove head.
		if(!RemoveChainObject(pChain,lpObject))
		{
#ifdef _DEBUG
			PrintLine(stderr,"Chain::RemoveChainTail : fail to remove chain object !");
#endif
		}
	}
	//Return object.
	return lpObject;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get next chain object.
//
////////////////////////////////////////////////////////////////////////////////

_OBJECT GetNextChainObject(SimpleChain* pChain)
{
	ChainNode* lpCurrent;

#ifdef _DEBUG
	assert(pChain != NULL);
#endif

	//Check count.
	if(pChain->nCount > 0)
	{
		//Get current.
		lpCurrent = (ChainNode *)pChain->nodeRoot.lpObject;

#ifdef _DEBUG
		assert(lpCurrent != NULL);
#endif

		//Check next.
		if(lpCurrent->lpNext == &pChain->nodeRoot)
		{
			//Set current as root.
			lpCurrent = &pChain->nodeRoot;
		}

		//Get next.
		lpCurrent = lpCurrent->lpNext;

#ifdef _DEBUG
		assert(lpCurrent != NULL);
#endif

		//Set current.
		pChain->nodeRoot.lpObject = lpCurrent;
		//Return object.
		return lpCurrent->lpObject;
	}
	//Return null.
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Get previous chain object.
//
////////////////////////////////////////////////////////////////////////////////

_OBJECT GetPreviousChainObject(SimpleChain* pChain)
{
	ChainNode* lpCurrent;

#ifdef _DEBUG
	assert(pChain != NULL);
#endif

	//Check count.
	if(pChain->nCount > 0)
	{
		//Get current.
		lpCurrent = (ChainNode *)pChain->nodeRoot.lpObject;

#ifdef _DEBUG
		assert(lpCurrent != NULL);
#endif

		//Check previous.
		if(lpCurrent->lpPrevious == &pChain->nodeRoot)
		{
			//Set current as root.
			lpCurrent = &pChain->nodeRoot;
		}

		//Get previous.
		lpCurrent = lpCurrent->lpPrevious;

#ifdef _DEBUG
		assert(lpCurrent != NULL);
#endif

		//Set current.
		pChain->nodeRoot.lpObject = lpCurrent;
		//Return object.
		return lpCurrent->lpObject;
	}
	//Return null.
	return NULL;
}
