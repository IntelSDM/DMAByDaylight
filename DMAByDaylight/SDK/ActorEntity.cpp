#include "Pch.h"
#include "ActorEntity.h"

ActorEntity::ActorEntity(uint64_t address, std::string fname,ActorType type)
{
	Class = address;
	Type = type;
	FName = fname;
}