//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: Ptrs.h
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef Ptrs_h
#define Ptrs_h

#include <Common.h>
#include <CCore.h>
extern CCore * g_pCore;

#define PTR_CHAT g_pCore->GetChat()

#endif // Ptrs_h