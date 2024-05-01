#include "Pch.h"
#include "Drawing.h"
#include "Globals.h"
#include "Camera.h"
#include "ActorEntity.h"
#include "Engine.h"
#include "PlayerEsp.h"
#include "ConfigUtilities.h"

std::shared_ptr<CheatFunction> UpdatePlayers = std::make_shared<CheatFunction>(10, [] {
	if (!EngineInstance)
		return;
	EngineInstance->UpdatePlayers();
	});

void DrawPlayerEsp()
{
	if (!EngineInstance)
		return;
	for (auto entity : EngineInstance->GetActors())
	{
		if (entity->GetPosition() == Vector3(0, 0, 0))
			continue;
		PlayerConfig config = Configs.Survivor;
		if (entity->GetPlayerRole() == EPlayerRole::EPlayerRole__VE_Slasher)
			config = Configs.Killer;

		Vector2 screenpos = Camera::WorldToScreen(EngineInstance->GetCameraCache().POV, entity->GetPosition());
		if (screenpos == Vector2::Zero())
			continue;
		Vector3 campos = Vector3(EngineInstance->GetCameraCache().POV.Location.X, EngineInstance->GetCameraCache().POV.Location.Y, EngineInstance->GetCameraCache().POV.Location.Z);
		float distance = (Vector3::Distance(campos, entity->GetPosition()) / 39.62f) - 6;
		if (distance < 0)
			continue;
		std::wstring wdistance = config.Distance ? L"[" + std::to_wstring((int)distance) + L"m]" : L"";
		std::wstring name = config.Name ? entity->GetName() : L"";
		if (distance > config.MaxDistance)
			continue;
		DrawText(screenpos.x, screenpos.y, name + wdistance, "Verdana", config.FontSize, config.TextColour, CentreCentre);
	}
	
}