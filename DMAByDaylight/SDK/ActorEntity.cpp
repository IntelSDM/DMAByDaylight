#include "Pch.h"
#include "ActorEntity.h"
#include "Camera.h"
#include "Globals.h"
ActorEntity::ActorEntity(uint64_t address)
{
	Class = address;

	PlayerState = TargetProcess.Read<uint64_t>(Class + PlayerState);
	if (!PlayerState)
		return;

	PlayerRole = TargetProcess.Read<EPlayerRole>(PlayerState + GameRole);

	if (PlayerRole != EPlayerRole::EPlayerRole__VE_Camper && PlayerRole != EPlayerRole::EPlayerRole__VE_Slasher)
		return;
	printf("PlayerRole: %d\n", PlayerRole);
	if(PlayerRole == EPlayerRole::EPlayerRole__VE_Camper)
	{
		Name = "Survivor";
	}
	else
	{
		Name = "Killer";
	}

	AcknowledgedPawn = TargetProcess.Read<uint64_t>(Class + AcknowledgedPawn);
	if(AcknowledgedPawn) // players aren't pawns
		return;
	RootComponent = TargetProcess.Read<uint64_t>(Class + RootComponent);
	if (!RootComponent)
		return;
	UEVector location = TargetProcess.Read<UEVector>(RootComponent + RelativeLocation);
	Vector3 pos = Vector3(location.X, location.Y, location.Z);

	printf("Actor: %p,Location: %f %f %f\n", Class,location.X, location.Y, location.Z);
	Vector3 screen = Camera::WorldToScreen(EngineInstance->GetCameraCache().POV, pos);
	printf("Screen: %f %f %f\n", screen.x, screen.y, screen.z);
}

EPlayerRole ActorEntity::GetPlayerRole()
{
	return PlayerRole;
}

uint64_t ActorEntity::GetClass()
{
	return Class;
}

std::string ActorEntity::GetName()
{
	return Name;
}