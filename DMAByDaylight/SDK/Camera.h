#pragma once
#include "Engine.h"

class Camera
{
public:
	static Vector2 WorldToScreen(MinimalViewInfo viewinfo, Vector3 world);
};