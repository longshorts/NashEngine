////////////////////////////////////////////////////////////////////////////////
// Filename: Application.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _APPLICATION_H_
#define _APPLICATION_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
/*#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "textclass.h"
#include "positionclass.h"
#include "InputManager.h"
#include "fireshaderclass.h"
#include "particleshaderclass.h"
#include "particlesystemclass.h"*/

#include "InputManager\InputManager.h"

#include <Windows.h>


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: Application
////////////////////////////////////////////////////////////////////////////////
class Application
{
public:
	Application();
	Application(const Application&);
	~Application();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int, int, float);
	bool Render(float);

private:
	/*D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_BoxModel;
	ModelClass* m_TreeModel;
	ModelClass* m_FireplaceModel;
	ModelClass* m_FireModel;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	TextClass* m_Text;
	PositionClass* m_Position;
	FireShaderClass* m_FireShader;
	ParticleShaderClass* m_ParticleShader;
	ParticleSystemClass* m_ParticleSystem;*/
	InputManager* m_InputManager;

	bool enableParticleSystem;
	bool enableAdditiveBlending;
};

#endif