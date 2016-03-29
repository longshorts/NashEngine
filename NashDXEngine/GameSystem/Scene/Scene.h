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
#include "../TimerManager/TimerManager.h"
#include "../UI/UserInterface.h"
#include "../Camera/Camera.h"
#include "Position/Position.h"
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
	Terrain* m_Terrain;
	bool m_displayUI;
};

#endif