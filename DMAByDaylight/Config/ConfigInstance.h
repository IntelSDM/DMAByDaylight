#pragma once
#include "Pch.h"
#include "PlayerConfig.h"
#include "Overlay.h"
class ConfigInstances
{
public:
	PlayerConfig Player = PlayerConfig(LIT("Player"));
	OverlayConfig Overlay = OverlayConfig(LIT("Overlay"));
	json ToJson()
	{
		json jsoned;
		jsoned.merge_patch(Player.ToJson());
		jsoned.merge_patch(Overlay.ToJson());
	}

	void FromJson(json jsoned)
	{
		Player.FromJson(jsoned);
		Overlay.FromJson(jsoned);
	}
};
inline ConfigInstances ConfigInstance;