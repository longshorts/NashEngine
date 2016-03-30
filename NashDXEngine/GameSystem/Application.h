////////////////////////////////////////////////////////////////////////////////
// Filename: Application.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _APPLICATION_H_
#define _APPLICATION_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
/*#include "D3DManager.h"
#include "Camera.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "Text.h"
#include "CameraPosition.h"
#include "InputManager.h"
#include "fireshaderclass.h"
#include "particleshaderclass.h"
#include "particlesystemclass.h"*/

#include "Camera\Camera.h"
#include "InputManager\InputManager.h"
#include "Direct3DManager\D3DManager.h"
#include "FPSManager\FPSManager.h"
#include "TimerManager\TimerManager.h"
#include "UI\Text\Text.h"
#include "UI\UserInterface.h"
#include "Shader\ShaderManager.h"
#include "Texture\TextureManager.h"
#include "Scene\Scene.h"

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
	/*D3DManager* m_D3D;
	Camera* m_Camera;
	ModelClass* m_BoxModel;
	ModelClass* m_TreeModel;
	ModelClass* m_FireplaceModel;
	ModelClass* m_FireModel;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	Text* m_Text;
	CameraPosition* m_Position;
	FireShaderClass* m_FireShader;
	ParticleShaderClass* m_ParticleShader;
	ParticleSystemClass* m_ParticleSystem;*/
	Camera* m_Camera;
	Text* m_Text;
	UserInterface* m_UI;
	ShaderManager* m_ShaderManager;
	Scene* m_Scene;


	bool enableParticleSystem;
	bool enableAdditiveBlending;
};

#endif