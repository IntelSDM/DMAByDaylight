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
	CameraEntry = TargetProcess.Read<CameraCacheEntry>(CameraManager + CameraCachePrivateOffset);
	printf("CameraCacheEntry: %p\n", CameraEntry);

}


void Engine::Cache()
{

	OwningActor = TargetProcess.Read<uint64_t>(PersistentLevel + OwningActorOffset);
	MaxPacket = TargetProcess.Read<uint32_t>(PersistentLevel + MaxPacketOffset);

	printf("Actor Array: %p\n", OwningActor);
	printf("Actor Array Size: %d\n", MaxPacket);
	std::vector<uint64_t> entitylist;
	entitylist.resize(MaxPacket);
	std::unique_ptr<uint64_t[]> object_raw_ptr = std::make_unique<uint64_t[]>(MaxPacket);
	TargetProcess.Read(OwningActor, object_raw_ptr.get(), MaxPacket * sizeof(uint64_t));
	for (size_t i = 0; i < MaxPacket; i++)
	{
		entitylist[i] = object_raw_ptr[i];
	}

	for (uint64_t address : entitylist)
	{
		uintptr_t actor = address;
		if (!actor)
			continue;
			std::shared_ptr<ActorEntity> entity = std::make_shared<ActorEntity>(actor);
			if (entity->GetPlayerRole() != EPlayerRole::EPlayerRole__VE_Slasher && entity->GetPlayerRole() != EPlayerRole::EPlayerRole__VE_Camper)
				continue;
			Actors.push_back(entity);
		
		
	}

}

void Engine::RefreshViewMatrix(VMMDLL_SCATTER_HANDLE handle)
{
	TargetProcess.AddScatterReadRequest(handle, CameraManager + CameraCachePrivateOffset,reinterpret_cast<void*>(&CameraEntry),sizeof(CameraCacheEntry));
}

CameraCacheEntry Engine::GetCameraCache()
{
	return CameraEntry;
}