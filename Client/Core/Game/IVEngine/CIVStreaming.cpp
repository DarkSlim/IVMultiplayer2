//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CIVStreaming.cpp
// Project: Client.Core
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVStreaming.h"
#include "../COffsets.h"
#include <SharedUtility.h>
#include <CLogFile.h>

#include <CCore.h>
extern CCore * g_pCore;

unsigned int CIVStreaming::GetResourceTypeIndex(eResourceType resourceType)
{
	switch(resourceType)
	{
		case RESOURCE_TYPE_WDR: return *(unsigned int *)COffsets::VAR_ResourceTypeWdrIndex;
		case RESOURCE_TYPE_WAD: return *(unsigned int *)COffsets::VAR_ResourceTypeWadIndex;
		case RESOURCE_TYPE_SCO: return *(unsigned int *)COffsets::VAR_ResourceTypeScoIndex;
		case RESOURCE_TYPE_WTD: return *(unsigned int *)COffsets::VAR_ResourceTypeWtdIndex;
		case RESOURCE_TYPE_CUT: return *(unsigned int *)COffsets::VAR_ResourceTypeCutIndex;
		case RESOURCE_TYPE_WDD: return *(unsigned int *)COffsets::VAR_ResourceTypeWddIndex;
		case RESOURCE_TYPE_WNV: return *(unsigned int *)COffsets::VAR_ResourceTypeWnvIndex;
		case RESOURCE_TYPE_RRR: return *(unsigned int *)COffsets::VAR_ResourceTypeRrrIndex;
		case RESOURCE_TYPE_WBD: return *(unsigned int *)COffsets::VAR_ResourceTypeWbdIndex;
		case RESOURCE_TYPE_IPL: return *(unsigned int *)COffsets::VAR_ResourceTypeIplIndex;
		case RESOURCE_TYPE_WBN: return *(unsigned int *)COffsets::VAR_ResourceTypeWbnIndex;
		case RESOURCE_TYPE_WBS: return *(unsigned int *)COffsets::VAR_ResourceTypeWbsIndex;
	}

	// Invalid resource type
	return 0;
}

void CIVStreaming::RequestResource(eResourceType resourceType, int iResourceIndex, DWORD dwFlags)
{
	unsigned int uiResourceTypeIndex = GetResourceTypeIndex(resourceType);

	_asm	push dwFlags;
	_asm	push uiResourceTypeIndex;
	_asm	push iResourceIndex;
	_asm	call COffsets::FUNC_RequestResource;
	_asm	add esp, 0Ch;
}

void CIVStreaming::LoadAllResources(bool bUnknown)
{
	_asm	push bUnknown;
	_asm	call COffsets::FUNC_LoadAllResources;
	_asm	add esp, 4;
}

bool CIVStreaming::HasResourceLoaded(eResourceType resourceType, int iResourceIndex)
{
	unsigned int uiResourceTypeIndex = GetResourceTypeIndex(resourceType);
	bool bLoaded = false;

	_asm	push uiResourceTypeIndex;
	_asm	push iResourceIndex;
	_asm	call COffsets::FUNC_HasResourceLoaded;
	_asm	add esp, 8;
	_asm	mov bLoaded, al;

	return bLoaded;
}

void CIVStreaming::ReleaseResource(eResourceType resourceType, int iResourceIndex)
{
	unsigned int uiResourceTypeIndex = GetResourceTypeIndex(resourceType);

	_asm	push uiResourceTypeIndex;
	_asm	push iResourceIndex;
	_asm	call COffsets::FUNC_ReleaseResource;
	_asm	add esp, 8;
}

int CIVStreaming::GetModelIndexFromHash(DWORD dwModelHash)
{
	int iModelIndex = -1;
	int * pModelIndex = &iModelIndex;

	_asm	push pModelIndex;
	_asm	push dwModelHash;
	_asm	call COffsets::FUNC_GetModelIndexFromHash;
	_asm	add esp, 8;

	return iModelIndex;
}

void CIVStreaming::LoadWorldAtPosition(CVector3 vecPosition)
{
	BYTE * pByteUnknown = &(*(BYTE *)COffsets::FUNC_IV_LOADWORLDATPOS_BYTE);
	CVector3 * pVecPosition = &vecPosition;

	_asm	push pVecPosition;
	_asm	mov ecx, pByteUnknown;
	_asm	call COffsets::FUNC_LoadWorldAtPosition;
	_asm	add esp, 4;
}

int CIVStreaming::GetAnimIndexFromName(const char * szName)
{
	return GetAnimIndexFromHash(SharedUtility::IVHash(szName));
}

int CIVStreaming::GetAnimIndexFromHash(unsigned int uiHash)
{
	int iAnimIndex = -1;

	_asm	push uiHash;
	_asm	call COffsets::FUNC_CAnimStore__GetIndexFromHash;
	_asm	mov iAnimIndex, eax;
	_asm	add esp, 4;

	return iAnimIndex;
}