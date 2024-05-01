#include "Pch.h"
#include "ConfigUtilities.h"
#include "Camera.h"

static ViewMatrix CreateMatrix(Vector3 rot, Vector3 origin) {
	const float DEG_TO_RAD = static_cast<float>(3.14159265358979323846) / 180.f;
	const float radPitch = rot.x * DEG_TO_RAD;
	const float radYaw = rot.y * DEG_TO_RAD;
	const float radRoll = rot.z * DEG_TO_RAD;

	const float SP = sinf(radPitch);
	const float CP = cosf(radPitch);
	const float SY = sinf(radYaw);
	const float CY = cosf(radYaw);
	const float SR = sinf(radRoll);
	const float CR = cosf(radRoll);

	ViewMatrix matrix;
	matrix.matrix[0][0] = CP * CY;
	matrix.matrix[0][1] = CP * SY;
	matrix.matrix[0][2] = SP;
	matrix.matrix[0][3] = 0.f;

	matrix.matrix[1][0] = SR * SP * CY - CR * SY;
	matrix.matrix[1][1] = SR * SP * SY + CR * CY;
	matrix.matrix[1][2] = -SR * CP;
	matrix.matrix[1][3] = 0.f;

	matrix.matrix[2][0] = -(CR * SP * CY + SR * SY);
	matrix.matrix[2][1] = CY * SR - CR * SP * SY;
	matrix.matrix[2][2] = CR * CP;
	matrix.matrix[2][3] = 0.f;

	matrix.matrix[3][0] = origin.x;
	matrix.matrix[3][1] = origin.y;
	matrix.matrix[3][2] = origin.z;
	matrix.matrix[3][3] = 1.f;

	return matrix;
}

Vector2 Camera::WorldToScreen(MinimalViewInfo viewinfo, Vector3 world)
{
	Vector3 Screenlocation(0, 0, 0);
	Vector3 rot = Vector3(viewinfo.Rotation.Pitch, viewinfo.Rotation.Yaw, viewinfo.Rotation.Roll);
	Vector3 campos = Vector3(viewinfo.Location.X, viewinfo.Location.Y, viewinfo.Location.Z);
	const ViewMatrix tempMatrix = CreateMatrix(rot, Vector3(0, 0, 0));

	Vector3 vAxisX(tempMatrix.matrix[0][0], tempMatrix.matrix[0][1], tempMatrix.matrix[0][2]);
	Vector3 vAxisY(tempMatrix.matrix[1][0], tempMatrix.matrix[1][1], tempMatrix.matrix[1][2]);
	Vector3 vAxisZ(tempMatrix.matrix[2][0], tempMatrix.matrix[2][1], tempMatrix.matrix[2][2]);

	Vector3 vDelta = world - campos;
	Vector3 vTransformed = Vector3(Vector3::Dot(vDelta,vAxisY), Vector3::Dot(vDelta,vAxisZ), Vector3::Dot(vDelta,vAxisX));

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	const float FOV_DEG_TO_RAD = static_cast<float>(3.14159265358979323846) / 360.f;
	int centrex = Configs.Overlay.OverrideResolution ? Configs.Overlay.Width /2 : GetSystemMetrics(SM_CXSCREEN) / 2;
	int centrey = Configs.Overlay.OverrideResolution ? Configs.Overlay.Height / 2 : GetSystemMetrics(SM_CYSCREEN) / 2;
	Screenlocation.x = centrex + vTransformed.x * (centrex / tanf(
		viewinfo.FOV * FOV_DEG_TO_RAD)) / vTransformed.z;
	Screenlocation.y = centrey - vTransformed.y * (centrex / tanf(
		viewinfo.FOV * FOV_DEG_TO_RAD)) / vTransformed.z;

	return Vector2(Screenlocation.x, Screenlocation.y);
}