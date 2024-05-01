#pragma once
#include "Engine.h"

class Camera
{
public:
	static Vector3 WorldToScreen(MinimalViewInfo viewinfo, Vector3 world);
};