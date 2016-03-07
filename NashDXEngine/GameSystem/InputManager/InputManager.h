////////////////////////////////////////////////////////////////////////////////
// Filename: InputManager.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_


///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define DIRECTINPUT_VERSION 0x0800


/////////////
// LINKING //
/////////////
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


//////////////
// INCLUDES //
//////////////
#include <dinput.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: InputManager
////////////////////////////////////////////////////////////////////////////////
class InputManager
{
public:
	InputManager();
	InputManager(const InputManager&);
	~InputManager();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

	bool IsButtonDown(unsigned int);

	
	void GetMouseLocation(int&, int&);
	bool IsEscapePressed();
	/*bool IsLeftArrowPressed();
	bool IsRightArrowPressed();
	bool IsUpArrowPressed();
	bool IsDownArrowPressed();
	bool IsWKeyPressed();
	bool IsSKeyPressed();
	bool IsAKeyPressed();
	bool IsDKeyPressed();
	bool IsPKeyPressed();
	bool IsOKeyPressed();
	bool IsLKeyPressed();
	bool IsKKeyPressed();*/

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

private:
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	unsigned char m_keyboardState[256];
	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
};

#endif