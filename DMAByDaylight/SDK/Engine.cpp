#include "Pch.h"
#include "Engine.h"
#include "ActorEntity.h"

Engine::Engine(std::string name)
{
	GameName = name;
	GWorld = TargetProcess.Read<uint64_t>(TargetProcess.GetBaseAddress(GameName) + GWorld);
	printf("GWorld: %p\n", GWorld);
	PersistentLevel = TargetProcess.Read<uint64_t>(GWorld + PersistentLevel);
	printf("PersistentLevel: %p\n", PersistentLevel);
	OwningGameInstance = TargetProcess.Read<uint64_t>(GWorld + OwningGameInstance);
	printf("OwningGameInstance: %p\n", OwningGameInstance);
	LocalPlayers = TargetProcess.Read<uint64_t>(OwningGameInstance + LocalPlayers);
	printf("LocalPlayers: %p\n", LocalPlayers);
	LocalPlayers = TargetProcess.Read<uint64_t>(LocalPlayers);
	printf("LocalPlayers: %p\n", LocalPlayers);
	PlayerController = TargetProcess.Read<uint64_t>(LocalPlayers + PlayerController);
	printf("PlayerController: %p\n", PlayerController);
	AcknowledgedPawn = TargetProcess.Read<uint64_t>(PlayerController + AcknowledgedPawn);
	printf("AcknowledgedPawn: %p\n", AcknowledgedPawn);
	CameraManager = TargetProcess.Read<uint64_t>(PlayerController + CameraManager);
	printf("CameraManager: %p\n", CameraManager);
	CameraCacheEntry = TargetProcess.Read<FCameraCacheEntry>(CameraManager + CameraCachePrivate);
	printf("CameraCacheEntry: %p\n", CameraCacheEntry);

	uint64_t gamestate = TargetProcess.Read<uint64_t>(GWorld + 0x130);
	printf("GameState: %p\n", gamestate);
	uint64_t playerarray = TargetProcess.Read<uint64_t>(gamestate + 0x248);
	printf("PlayerArray: %p\n", playerarray);
	uint32_t playerarraysize = TargetProcess.Read<uint64_t>(gamestate + 0x248 + 0x8);
	printf("PlayerArraySize: %d\n", playerarraysize);

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
	OwningActor = TargetProcess.Read<uint64_t>(PersistentLevel + OwningActorOffset);
	MaxPacket = TargetProcess.Read<uint32_t>(PersistentLevel + MaxPacketOffset);

	printf("Actor Array: %p\n", OwningActor);
	printf("Actor Array Size: %d\n", MaxPacket);

	for (int i = 0; i < MaxPacket; i++)
	{
		uintptr_t actor = TargetProcess.Read<uintptr_t>(OwningActor + i * 0x8);
		if (!actor)
			continue;
			std::shared_ptr<ActorEntity> entity = std::make_shared<ActorEntity>(actor);
		//	Actors.push_back(entity);
		
		
	}

}