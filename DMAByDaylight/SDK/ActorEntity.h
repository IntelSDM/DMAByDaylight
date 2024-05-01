#pragma once
enum class EPlayerRole: uint8_t
{
	EPlayerRole__VE_None = 0,
	EPlayerRole__VE_Slasher = 1,
	EPlayerRole__VE_Camper = 2,
	EPlayerRole__VE_Observer = 3,
	EPlayerRole__Max = 4,
	EPlayerRole__EPlayerRole_MAX = 5
};
class ActorEntity
{
private:
	uint64_t Class = 0;
	std::string FName;
	EPlayerRole PlayerRole;
	uint64_t PlayerState = 0x2C0;
	uint64_t AcknowledgedPawn = 0x2f8;
	uint64_t RootComponent = 0x1A8;
	uint64_t RelativeLocation = 0x140;
	uint64_t GameRole = 0x3fa; // DBDPlayerState -> GameRole
	

public:
	ActorEntity(uint64_t address);
	uint64_t GetClass();

};