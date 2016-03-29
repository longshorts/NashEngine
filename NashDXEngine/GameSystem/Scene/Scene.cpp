////////////////////////////////////////////////////////////////////////////////
// Filename: Scene.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Scene.h"


Scene::Scene()
{
	m_UserInterface = 0;
	m_Camera = 0;
	m_Position = 0;
	m_Terrain = 0;
}


Scene::Scene(const Scene& other)
{
}


Scene::~Scene()
{
}


bool Scene::Initialize(HWND hwnd, int screenWidth, int screenHeight, float screenDepth)
{
	bool result;


	// Create the user interface object.
	m_UserInterface = new UserInterface;
	if (!m_UserInterface)
	{
		return false;
	}

	// Initialize the user interface object.
	result = m_UserInterface->Initialize(D3DManager::getInstance(), screenHeight, screenWidth);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the user interface object.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new Camera;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera and build the matrices needed for rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();
	m_Camera->RenderBaseViewMatrix();

	// Create the position object.
	m_Position = new Position;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation.
	m_Position->SetPosition(128.0f, 5.0f, -10.0f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);

	// Create the terrain object.
	m_Terrain = new Terrain;
	if (!m_Terrain)
	{
		return false;
	}

	// Initialize the terrain object.
	result = m_Terrain->Initialize(D3DManager::getInstance()->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	// Set the UI to display by default.
	m_displayUI = true;

	return true;
}


void Scene::Shutdown()
{
	// Release the terrain object.
	if (m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}

	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the user interface object.
	if (m_UserInterface)
	{
		m_UserInterface->Shutdown();
		delete m_UserInterface;
		m_UserInterface = 0;
	}

	return;
}


bool Scene::Frame(ShaderManager* ShaderManager, float frameTime, int fps)
{
	bool result;
	float posX, posY, posZ, rotX, rotY, rotZ;

	// Do the frame input processing.
	HandleMovementInput(InputManager::getInstance(), frameTime);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Do the frame processing for the user interface.
	result = m_UserInterface->Frame(D3DManager::getInstance()->GetDeviceContext(), fps, posX, posY, posZ, rotX, rotY, rotZ);
	if (!result)
	{
		return false;
	}

	// Render the graphics.
	result = Render(ShaderManager);
	if (!result)
	{
		return false;
	}

	return true;
}


void Scene::HandleMovementInput(InputManager* Input, float frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;


	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = Input->IsButtonDown(DIK_LEFT);
	m_Position->TurnLeft(keyDown);

	keyDown = Input->IsButtonDown(DIK_RIGHT);
	m_Position->TurnRight(keyDown);

	keyDown = Input->IsButtonDown(DIK_UP);
	m_Position->MoveForward(keyDown);

	keyDown = Input->IsButtonDown(DIK_DOWN);
	m_Position->MoveBackward(keyDown);

	keyDown = Input->IsButtonDown(DIK_A);
	m_Position->MoveUpward(keyDown);

	keyDown = Input->IsButtonDown(DIK_Z);
	m_Position->MoveDownward(keyDown);

	keyDown = Input->IsButtonDown(DIK_PGUP);
	m_Position->LookUpward(keyDown);

	keyDown = Input->IsButtonDown(DIK_PGDN);
	m_Position->LookDownward(keyDown);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	// Determine if the user interface should be displayed or not.
	if (Input->IsButtonDown(DIK_F1))
	{
		m_displayUI = !m_displayUI;
	}

	return;
}


bool Scene::Render(ShaderManager* ShaderManager)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrix, orthoMatrix;
	bool result;


	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	worldMatrix = XMLoadFloat4x4(&D3DManager::getInstance()->GetWorldMatrix());
	m_Camera->GetViewMatrix(viewMatrix);
	projectionMatrix = XMLoadFloat4x4(&D3DManager::getInstance()->GetProjectionMatrix());
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	orthoMatrix = XMLoadFloat4x4(&D3DManager::getInstance()->GetOrthoMatrix());

	// Clear the buffers to begin the scene.
	D3DManager::getInstance()->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Render the terrain grid using the color shader.
	m_Terrain->Render(D3DManager::getInstance()->GetDeviceContext());
	result = ShaderManager->RenderColorShader(D3DManager::getInstance()->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix);
	if (!result)
	{
		return false;
	}

	// Render the user interface.
	if (m_displayUI)
	{
		result = m_UserInterface->Render(D3DManager::getInstance(), ShaderManager, worldMatrix, baseViewMatrix, orthoMatrix);
		if (!result)
		{
			return false;
		}
	}

	// Present the rendered scene to the screen.
	D3DManager::getInstance()->EndScene();

	return true;
}