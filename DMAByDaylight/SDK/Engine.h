#pragma once
#include "ActorEntity.h"
// ScriptStruct CoreUObject.Vector
struct UEVector {
	double X; // 0x0(0x8)
	double Y; // 0x8(0x8)
	double Z; // 0x10(0x8)
};
// ScriptStruct CoreUObject.Rotator
struct UERotator {
	double Pitch; // 0x0(0x8)
	double Yaw; // 0x8(0x8)
	double Roll; // 0x10(0x8)
};
struct MinimalViewInfo
{
	struct UEVector Location; // 0x0(0x18)
	struct UERotator Rotation; // 0x18(0x18)
	float FOV; // 0x30(0x4)
};
struct CameraCacheEntry
{
	float Timestamp; // 0x00(0x04)
	char pad_4[0xc]; // 0x04(0x0c)
	MinimalViewInfo POV; // 0x10(0x5e0)
};
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
	uint64_t GWorld = 0xEBF5530; 
	uint64_t LocalPlayers = 0x40; // GameInstance -> LocalPlayers
	uint64_t PlayerController = 0x38; // Player -> PlayerController
	uint64_t AcknowledgedPawn = 0x2f8;	
	uint64_t CameraManager = 0x360; // PlayerController -> PlayerCameraManager
	uint64_t CameraCachePrivate = 0x0; // PlayerCameraManager -> CameraCachePrivate
	uint64_t CameraCachePrivateOffset = 0x22D0; // PlayerCameraManager -> CameraCachePrivate
	CameraCacheEntry CameraEntry; // ScriptStruct Engine.CameraCacheEntry
	std::string GameName;
	MinimalViewInfo CameraViewInfo; // ScriptStruct Engine.MinimalViewInfo
	std::vector<std::shared_ptr<ActorEntity>> Actors;
public:
	Engine(std::string name);
	void Cache();
	std::vector<std::shared_ptr<ActorEntity>> GetActors();
	CameraCacheEntry GetCameraCache();
	void RefreshViewMatrix(VMMDLL_SCATTER_HANDLE handle);
};