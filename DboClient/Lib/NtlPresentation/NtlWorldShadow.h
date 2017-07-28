////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma once


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define dLIGHT_ELEVATION    (45.0f)
#define dLIGHT_AZIMUTH      (60.0f)


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ntlworldcommon.h"
#include "NtlWorldShadowManager.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class CNtlWorldShadow
{
public:
	CNtlWorldShadow(void);
	~CNtlWorldShadow(void);

public:
	RwMatrix	m_matLight;
	RwMatrix	m_matTex;
	RwTexture*	m_pTexShadow;
	RwReal		m_CamViewWindowX;
	RwRGBA		m_rgbaShadow;

public:
	RwBool	Create(RwInt32 _NtlWorldDir);
	RwBool	Delete();
	void	Update();

#ifdef dNTL_WORLD_TOOL_MODE

public:
	sNTL_WORLD_SHADOW_PARAM m_NtlWorldShadowParam;
	sNTL_WORLD_SHADOW_PARAM* m_pNtlWorldShadowParam4Doodads;

public:
	void SaveSwapFile(RwInt32 _SectorIdx);
	void LoadSwapFile(RwInt32 _SectorIdx);
	void UpdateSParam(sNTL_WORLD_SHADOW_PARAM& _NtlWorldShadowParam);
	void UpdateSParam4Doodads(sNTL_WORLD_SHADOW_PARAM& _NtlWorldShadowParam);

#endif
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
