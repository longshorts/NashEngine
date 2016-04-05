////////////////////////////////////////////////////////////////////////////////
// Filename: Scene.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _Scene_H_
#define _Scene_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "../Direct3DManager/D3DManager.h"
#include "../InputManager/InputManager.h"
#include "../Shader/ShaderManager.h"
#include "../Texture/TextureManager.h"
#include "../TimerManager/TimerManager.h"
#include "../UI/UserInterface.h"
#include "../Camera/Camera.h"
#include "Light/Light.h"
#include "Position/Position.h"
#include "Model/SkyDome.h"
#include "Terrain/Terrain.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: Scene
////////////////////////////////////////////////////////////////////////////////
class Scene
{
public:
	Scene();
	Scene(const Scene&);
	~Scene();

	bool Initialize(HWND, int, int, float);
	void Shutdown();
	bool Frame(ShaderManager*, float, int);

private:
	void HandleMovementInput(InputManager*, float);
	bool Render(ShaderManager*);

private:
	UserInterface* m_UserInterface;
	Camera* m_Camera;
	Position* m_Position;
	SkyDome* m_SkyDome;
	Light* m_Light;
	Terrain* m_Terrain;
	bool m_displayUI, m_wireFrame;
};

#endif