#include "Pch.h"
#include "Drawing.h"
#include "Globals.h"
#include "Camera.h"
#include "ActorEntity.h"
#include "Engine.h"
#include "PlayerEsp.h"

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
			Vector2 screenpos = Camera::WorldToScreen(EngineInstance->GetCameraCache().POV, entity->GetPosition());
			Vector3 campos = Vector3(EngineInstance->GetCameraCache().POV.Location.X, EngineInstance->GetCameraCache().POV.Location.Y, EngineInstance->GetCameraCache().POV.Location.Z);
			float distance = (Vector3::Distance(campos, entity->GetPosition()) / 39.62f) - 6;
			if (distance < 0)
				continue;
			std::wstring wdistance = L"[" + std::to_wstring((int)distance) + L"m]";
			DrawText(screenpos.x, screenpos.y, entity->GetName() + wdistance, "Verdana", 12, Colour(255, 0, 0, 255), CentreCentre);
		}
	
}