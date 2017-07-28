#pragma once


#include "ntlplproperty.h"


class CNtlPLSoundProp :	public CNtlPLProperty
{
public:
	CNtlPLSoundProp(void);
	virtual ~CNtlPLSoundProp(void);

public:
	RwBool Load(CNtlXMLDoc *pDoc, IXMLDOMNode *pNode);
	RwBool Save(CNtlXMLDoc *pDoc, IXMLDOMNode *pNode);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CNtlPLSoundFieldProp : public CNtlPLProperty
{
public:
	CNtlPLSoundFieldProp(void);
	virtual ~CNtlPLSoundFieldProp(void);

	RwBool Load(CNtlXMLDoc *pDoc, IXMLDOMNode *pNode);
	RwBool Save(CNtlXMLDoc *pDoc, IXMLDOMNode *pNode);

public:
	typedef std::map<RwInt32, std::string>	MAP_SOUND;
	typedef MAP_SOUND::iterator				MAP_SOUND_IT;

	MAP_SOUND								m_mapSound;
};
