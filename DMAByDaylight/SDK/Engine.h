#pragma once
#include "ActorEntity.h"
#include "EngineStructs.h"

// For these offsets just 7 dumper the game and open Engine_Classes
class Engine
{

private:
	uint64_t OwningActorOffset = 0xA0; // NetConnection -> OwningActor
	uint64_t MaxPacketOffset = 0xA8; // NetConnection -> MaxPacket
	uint64_t OwningActor;
	uint64_t MaxPacket;
	uint64_t OwningGameInstance = 0x1c8; // World -> OwningGameInstance
	uint64_t PersistentLevel = 0x38; // World  -> PersistentLevel
	uint64_t GWorld = 0xF34CE80;
	uint64_t LocalPlayers = 0x40; // GameInstance -> LocalPlayers
	uint64_t PlayerController = 0x38; // Player -> PlayerController
	uint64_t AcknowledgedPawn = 0x2f8;	
	uint64_t CameraManager = 0x360; // PlayerController -> PlayerCameraManager
	uint64_t CameraCachePrivate = 0x0; // PlayerCameraManager -> CameraCachePrivate
	uint64_t CameraCachePrivateOffset = 0x22D0; // PlayerCameraManager -> CameraCachePrivate
	CameraCacheEntry CameraEntry; // ScriptStruct Engine.CameraCacheEntry
	MinimalViewInfo CameraViewInfo; // ScriptStruct Engine.MinimalViewInfo
	std::vector<std::shared_ptr<ActorEntity>> Actors;
public:
	Engine();
	void Cache();
	void UpdatePlayers();
	std::vector<std::shared_ptr<ActorEntity>> GetActors();
	CameraCacheEntry GetCameraCache();
	void RefreshViewMatrix(VMMDLL_SCATTER_HANDLE handle);
	uint32_t GetActorSize();

};