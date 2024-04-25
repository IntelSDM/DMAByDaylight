#pragma once
enum ActorType
{
	Survivor,
	Killer

};
class ActorEntity
{
public:
	ActorEntity(uint64_t address, std::string fname, ActorType actortype);
	uint64_t GetClass();
	std::string GetFName();
	ActorType Type;
private:
	uint64_t Class = 0;
	std::string FName;

};