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
	static InputManager* getInstance()
	{
		return instance;
	}

	InputManager();
	InputManager(const InputManager&);
	~InputManager();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

	bool IsButtonDown(unsigned int);
	bool IsButtonPressed(unsigned int);

	void GetMouseLocation(int&, int&);
	int GetMouseDeltaX();
	int GetMouseDeltaY();

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

private:
	static InputManager* instance;


	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	unsigned char m_keyboardState[256];
	unsigned char m_prevKeyboardState[256];
	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
	float mouseSensitivity = 0.2f;
};


#endif

//SINGLETON TEMPLATE
/*static InputManager* Instance()
{
	return instance;
}

private:
	static InputManager* instance;


	InputManager* InputManager::instance;

	InputManager::InputManger()
	{
		if (instance)
		{
			delete this;
		}
		else instance = this;
	}

	InputManager::~InputManager()
	{
		Terminate();
		instance = 0;
	}

instance.ProcessInput() // Reference
instance->ProcessInput() // Pointer
*/