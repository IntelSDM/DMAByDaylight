#pragma once
#include "ActorEntity.h"
// For these offsets just 7 dumper the game and open Engine_Classes
class Engine
{

private:
	uint64_t OwningActor = 0xA0;
	uint64_t MaxPacket = 0xA8;
	uint64_t OwningGameInstance = 0x190;
	uint64_t PersistentLevel = 0x38;
	uint64_t GName = 0xE98FD00;
	uint64_t GWorld = 0xEBF55A0;
	std::string GameName;

	std::string GetNameById(uint32_t actorid);

	std::vector<std::shared_ptr<ActorEntity>> Actors;
public:
	Engine(std::string name);
	void Cache();
	std::vector<std::shared_ptr<ActorEntity>> GetActors();
};