#pragma once
#include "ActorEntity.h"


struct FMinimalViewInfo
{
	Vector3 Location; // 0x00(0x0c)
	Vector3 Rotation; // 0x0c(0x0c)
	float FOV; // 0x18(0x04)
};
struct FCameraCacheEntry
{
	float Timestamp; // 0x00(0x04)
	char pad_4[0xc]; // 0x04(0x0c)
	FMinimalViewInfo POV; // 0x10(0x5e0)
};
// For these offsets just 7 dumper the game and open Engine_Classes
class Engine
{

private:
	uint64_t OwningActorOffset = 0xA0;
	uint64_t MaxPacketOffset = 0xA8;
	uint64_t OwningActor;
	uint64_t MaxPacket;
	uint64_t OwningGameInstance = 0x1c8;
	uint64_t PersistentLevel = 0x38;
	uint64_t GName = 0xE98FD00;
	uint64_t GWorld = 0xEBF5530;
	uint64_t LocalPlayers = 0x40;
	uint64_t PlayerController = 0x38;
	uint64_t AcknowledgedPawn = 0x2f8;	
	uint64_t CameraManager = 0x360;
	uint64_t CameraCachePrivate = 0x22D0;
	FCameraCacheEntry CameraCacheEntry;
	std::string GameName;

	std::string GetNameById(uint32_t actorid);

	std::vector<std::shared_ptr<ActorEntity>> Actors;
public:
	Engine(std::string name);
	void Cache();
	std::vector<std::shared_ptr<ActorEntity>> GetActors();
};