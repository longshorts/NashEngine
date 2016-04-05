////////////////////////////////////////////////////////////////////////////////
// Filename: Scene.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Scene.h"


Scene::Scene()
{
	m_UserInterface = 0;
	m_Camera = 0;
	m_Light = 0;
	m_Position = 0;
	m_SkyDome = 0;
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
	D3DManager* Direct3D = D3DManager::getInstance();


	// Create the user interface object.
	m_UserInterface = new UserInterface;
	if (!m_UserInterface)
	{
		return false;
	}

	// Initialize the user interface object.
	result = m_UserInterface->Initialize(Direct3D, screenHeight, screenWidth);
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

	// Create the light object.
	m_Light = new Light;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(-0.5f, -1.0f, -0.5f);

	// Create the position object.
	m_Position = new Position;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation.
	m_Position->SetPosition(128.0f, 10.0f, -10.0f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);

	// Create the sky dome object.
	m_SkyDome = new SkyDome;
	if (!m_SkyDome)
	{
		return false;
	}

	// Initialize the sky dome object.
	result = m_SkyDome->Initialize(Direct3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain object.
	m_Terrain = new Terrain;
	if (!m_Terrain)
	{
		return false;
	}

	// Initialize the terrain object.
	result = m_Terrain->Initialize(Direct3D->GetDevice(), "../Assets/setup.txt");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	// Set the UI to display by default.
	m_displayUI = true;

	// Set wire frame rendering initially to enabled.
	m_wireFrame = true;

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

	// Release the sky dome object.
	if (m_SkyDome)
	{
		m_SkyDome->Shutdown();
		delete m_SkyDome;
		m_SkyDome = 0;
	}

	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
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

	// Determine if the terrain should be rendered in wireframe or not.
	if (Input->IsButtonDown(DIK_F2))
	{
		m_wireFrame = !m_wireFrame;
	}

	return;
}


bool Scene::Render(ShaderManager* ShaderManager)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrix, orthoMatrix;
	bool result;
	XMFLOAT3 cameraPosition;


	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	D3DManager::getInstance()->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	D3DManager::getInstance()->GetProjectionMatrix(projectionMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	D3DManager::getInstance()->GetOrthoMatrix(orthoMatrix);

	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();

	// Clear the buffers to begin the scene.
	D3DManager::getInstance()->BeginScene(0.0f, 0.0f, 0.1f, 1.0f);

	// Turn off back face culling and turn off the Z buffer.
	D3DManager::getInstance()->TurnOffCulling();
	D3DManager::getInstance()->TurnZBufferOff();

	// Translate the sky dome to be centered around the camera position.
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Render the sky dome using the sky dome shader.
	m_SkyDome->Render(D3DManager::getInstance()->GetDeviceContext());
	result = ShaderManager->RenderSkyDomeShader(D3DManager::getInstance()->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());
	if (!result)
	{
		return false;
	}

	// Reset the world matrix.
	D3DManager::getInstance()->GetWorldMatrix(worldMatrix);

	// Turn the Z buffer back and back face culling on.
	D3DManager::getInstance()->TurnZBufferOn();
	D3DManager::getInstance()->TurnOnCulling();

	// Turn on wire frame rendering of the terrain if needed.
	if (m_wireFrame)
	{
		D3DManager::getInstance()->EnableWireframe();
	}

	// Render the terrain grid using the terrain shader.
	m_Terrain->Render(D3DManager::getInstance()->GetDeviceContext());
	result = ShaderManager->RenderTerrainShader(D3DManager::getInstance()->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, TextureManager::getInstance()->GetTexture(1), TextureManager::getInstance()->GetTexture(1),
		m_Light->GetDirection(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	// Turn off wire frame rendering of the terrain if it was on.
	if (m_wireFrame)
	{
		D3DManager::getInstance()->DisableWireframe();
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