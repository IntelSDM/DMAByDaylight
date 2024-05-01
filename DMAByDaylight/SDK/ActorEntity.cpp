#include "Pch.h"
#include "ActorEntity.h"

ActorEntity::ActorEntity(uint64_t address)
{
	Class = address;

	PlayerState = TargetProcess.Read<uint64_t>(Class + PlayerState);
	if (!PlayerState)
		return;

	PlayerRole = TargetProcess.Read<EPlayerRole>(PlayerState + GameRole);
	printf("PlayerRole: %d\n", PlayerRole);
	if (PlayerRole != EPlayerRole::EPlayerRole__VE_Camper && PlayerRole != EPlayerRole::EPlayerRole__VE_Slasher)
		return;
	AcknowledgedPawn = TargetProcess.Read<uint64_t>(Class + AcknowledgedPawn);
	RootComponent = TargetProcess.Read<uint64_t>(Class + RootComponent);
	Vector3 location = TargetProcess.Read<Vector3>(RootComponent + RelativeLocation);
	printf("Actor: %p,Location: %f %f %f\n", Class,location.x, location.y, location.z);
}