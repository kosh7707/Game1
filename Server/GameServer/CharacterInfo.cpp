#include "pch.h"
#include "CharacterInfo.h"

CharacterInfo::CharacterInfo(Protocol::CharacterInfo* characterInfo)
{
	this->characterId	= characterInfo->characterid();
	this->playerType	= (PlayerType)characterInfo->playertype();
	this->name			= characterInfo->name();
	this->level			= characterInfo->level();
	this->hp			= characterInfo->hp();
	this->exp			= characterInfo->exp();
	this->attack		= characterInfo->attack();
	this->mapId			= characterInfo->mapid();
}
