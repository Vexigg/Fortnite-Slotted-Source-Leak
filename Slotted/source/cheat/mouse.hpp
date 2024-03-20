#pragma once
#include "../util.hpp"

inline const byte XOR_KEY = 0xACACACADDEDFFFA;

inline void EncryptFunctionBytes(BYTE* bytes, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        bytes[i] ^= XOR_KEY;
    }
}

inline void DecryptFunctionBytes(BYTE* bytes, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        bytes[i] ^= XOR_KEY;
    }
}

enum InjectedInputMouseOptions
{
    Absolute = 32768,
    HWheel = 4096,
    LeftDown = 2,
    LeftUp = 4,
    MiddleDown = 32,
    MiddleUp = 64,
    Move = 1,
    MoveNoCoalesce = 8192,
    None = 0,
    RightDown = 8,
    RightUp = 16,
    VirtualDesk = 16384,
    Wheel = 2048,
    XDown = 128,
    XUp = 256
};
typedef struct _InjectedInputMouseInfo {
    int DeltaX;
    int DeltaY;
    unsigned int MouseData;
    InjectedInputMouseOptions MouseOptions;
    unsigned int TimeOffsetInMilliseconds;
    void* ExtraInfo;
} InjectedInputMouseInfo;

typedef bool (WINAPI* InjectMouseInput_t)(InjectedInputMouseInfo* inputs, int count);
inline InjectMouseInput_t InjectMouseInput;


//extra protectin by encrypting the code that calls the sys call function and copying it to a new location in memory and it encrypts and decrypts its bytes when allocating new memory
namespace MouseController
{
	static BYTE NtUserInjectMouseInput_Bytes[30];

	
	static BOOLEAN WINAPI Init()
	{
		// windows 8.1 / windows 10
		LPVOID NtUserInjectMouseInput_Addr = GetProcAddress(GetModuleHandle("win32u"), "NtUserInjectMouseInput");
		if (!NtUserInjectMouseInput_Addr)
		{
			NtUserInjectMouseInput_Addr = GetProcAddress(GetModuleHandle("user32"), "NtUserInjectMouseInput");
			if (!NtUserInjectMouseInput_Addr)
			{
				// Windows 7 or lower detected
				NtUserInjectMouseInput_Addr = GetProcAddress(GetModuleHandle("user32"), "InjectMouseInput");
				if (!NtUserInjectMouseInput_Addr)
					return FALSE;
			}
		}
		memcpy(NtUserInjectMouseInput_Bytes, NtUserInjectMouseInput_Addr, 30);
		EncryptFunctionBytes(NtUserInjectMouseInput_Bytes, 30);
		return TRUE;
	}

	/* This function spoofs the function. It prevents BattlEye from scanning it! */
	static BOOLEAN WINAPI NtInjectMouse(InjectedInputMouseInfo* input, int count)
	{
		LPVOID NtUserInjectMouseInput_Spoof = VirtualAlloc(0, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE); // allocate space for syscall
		if (!NtUserInjectMouseInput_Spoof)
			return FALSE;

		DecryptFunctionBytes(NtUserInjectMouseInput_Bytes, 30);
		memcpy(NtUserInjectMouseInput_Spoof, NtUserInjectMouseInput_Bytes, 30); // copy syscall
		EncryptFunctionBytes(NtUserInjectMouseInput_Bytes, 30);

		
		NTSTATUS Result = reinterpret_cast<NTSTATUS(NTAPI*)(InjectedInputMouseInfo*, int)>(NtUserInjectMouseInput_Spoof)(input, count); // calling spoofed function
		ZeroMemory(NtUserInjectMouseInput_Spoof, 0x1000); // clean address
		VirtualFree(NtUserInjectMouseInput_Spoof, 0, MEM_RELEASE); // free it
		return (Result > 0); // return the status
	}

	/* This function moves the mouse using the syscall */
	static BOOLEAN WINAPI NtInjectMouse(int X, int Y)
	{
		InjectedInputMouseInfo info = { 0 };
		info.DeltaX = X;
		info.DeltaY = Y;
		return NtInjectMouse(&info, 1);
	}
}

inline void move_mouse(vector2 Head2D) {



	float x = Head2D.x; float y = Head2D.y;
	float AimSpeed = smoothing;

	vector2 ScreenCenter = { (double)screen_width / 2 , (double)screen_height / 2 };
	vector2 Target;

	if (x != 0)
	{
		if (x > ScreenCenter.x)
		{
			Target.x = -(ScreenCenter.x - x);
			Target.x /= AimSpeed;
			if (Target.x + ScreenCenter.x > ScreenCenter.x * 2) Target.x = 0;
		}

		if (x < ScreenCenter.x)
		{
			Target.x = x - ScreenCenter.x;
			Target.x /= AimSpeed;
			if (Target.x + ScreenCenter.x < 0) Target.x = 0;
		}
	}
	if (y != 0)
	{
		if (y > ScreenCenter.y)
		{
			Target.y = -(ScreenCenter.y - y);
			Target.y /= AimSpeed;
			if (Target.y + ScreenCenter.y > ScreenCenter.y * 2) Target.y = 0;
		}

		if (y < ScreenCenter.y)
		{
			Target.y = y - ScreenCenter.y;
			Target.y /= AimSpeed;
			if (Target.y + ScreenCenter.y < 0) Target.y = 0;
		}
	}
	if ((int)Target.x != 0 or (int)Target.y != 0)
		MouseController::NtInjectMouse((int)Target.x, (int)Target.y);
}