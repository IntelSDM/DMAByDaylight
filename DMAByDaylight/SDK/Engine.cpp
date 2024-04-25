#include "Pch.h"
#include "Engine.h"
#include "ActorEntity.h"

Engine::Engine(std::string name)
{
	GameName = name;
	GWorld = TargetProcess.Read<uint64_t>(TargetProcess.GetBaseAddress(GameName) + GWorld);
	PersistentLevel = TargetProcess.Read<uint64_t>(GWorld + PersistentLevel);

}
std::string Engine::GetNameById(uint32_t actorid)
{
	char buffer[128];
	int tablelocation = (unsigned int)(actorid >> 0x10);
	uint16_t rowlocation = (unsigned __int16)actorid;
	uint64_t gnametable = TargetProcess.GetBaseAddress(GameName) + GName;

	uint64_t tableaddress = TargetProcess.Read<uint64_t>(gnametable + 0x10 + tablelocation * 0x8) + (unsigned __int32)(4 * rowlocation);
	uint64_t length = (unsigned __int64)(TargetProcess.Read<uint16_t>(tableaddress + 4)) >> 1;

	if (length < 128)
	{
		TargetProcess.Read((tableaddress + 6), &buffer, length);
		std::string name = std::string(buffer, length);
		return name;
	}
	return "";
}

void Engine::Cache()
{
	OwningActor = TargetProcess.Read<uint64_t>(PersistentLevel + OwningActor);
	MaxPacket = TargetProcess.Read<uint32_t>(PersistentLevel + MaxPacket);

	printf("Actor Array: %p\n", OwningActor);
	printf("Actor Array Size: %d\n", MaxPacket);

	for (int i = 0; i < MaxPacket; i++)
	{
		uintptr_t actor = TargetProcess.Read<uintptr_t>(OwningActor + i * 0x8);
		if (!actor)
			continue;
		uint32_t objectId = TargetProcess.Read<int>(actor + 0x18);
		std::string name = GetNameById(objectId);
		
		if (name.find("BP_CamperMale") != std::string::npos)
		{
			printf("Actor: %p, ID: %d, Name: %s\n", actor, objectId, name.c_str());
			std::shared_ptr<ActorEntity> entity = std::make_shared<ActorEntity>(actor, name,Survivor);
			Actors.push_back(entity);
			continue;
		}
		if (name.find("BP_CamperFemale") != std::string::npos)
		{
			printf("Actor: %p, ID: %d, Name: %s\n", actor, objectId, name.c_str());
			std::shared_ptr<ActorEntity> entity = std::make_shared<ActorEntity>(actor, name, Survivor);
			Actors.push_back(entity);
			continue;
		}
		if (name.find("BP_Slasher") != std::string::npos)
		{
			printf("Actor: %p, ID: %d, Name: %s\n", actor, objectId, name.c_str());
			std::shared_ptr<ActorEntity> entity = std::make_shared<ActorEntity>(actor, name, Killer);
			Actors.push_back(entity);
			continue;
		}

		
	}

}