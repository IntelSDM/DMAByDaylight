#pragma once
// ScriptStruct CoreUObject.Vector
struct UEVector {
	double X; // 0x0(0x8)
	double Y; // 0x8(0x8)
	double Z; // 0x10(0x8)
};
// ScriptStruct CoreUObject.Rotator
struct UERotator {
	double Pitch; // 0x0(0x8)
	double Yaw; // 0x8(0x8)
	double Roll; // 0x10(0x8)
};
struct MinimalViewInfo
{
	struct UEVector Location; // 0x0(0x18)
	struct UERotator Rotation; // 0x18(0x18)
	float FOV; // 0x30(0x4)
};
struct CameraCacheEntry
{
	float Timestamp; // 0x00(0x04)
	char pad_4[0xc]; // 0x04(0x0c)
	MinimalViewInfo POV; // 0x10(0x5e0)
};