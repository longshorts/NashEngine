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
	m_Frustum = 0;
	m_SkyDome = 0;
	m_Terrain = 0;
	m_RefractionTexture = 0;
	m_ReflectionTexture = 0;
	m_Water = 0;
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

	//sandColor = XMFLOAT4((float)(235 / 255), (float)(185 / 255), (float)(136 / 255), 1);
	sandColor = XMFLOAT4(235.0f / 255.0f, 185.0f / 255.0f, 136.0f / 255.0f, 1);
	grassColor = XMFLOAT4(58.0f / 255.0f, 124.0f / 255.0f, 37.0f / 255.0f, 1);

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
	m_Position->SetPosition(283.0f, 55.0f, 474.0f);
	m_Position->SetRotation(9.0f, 86.0f, 0.0f);

	// Create the frustum object.
	m_Frustum = new Frustum;
	if (!m_Frustum)
	{
		return false;
	}

	// Initialize the frustum object.
	m_Frustum->Initialize(screenDepth);

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

	// Create the refraction render to texture object.
	m_RefractionTexture = new RenderTexture;
	if (!m_RefractionTexture)
	{
		return false;
	}

	// Initialize the refraction render to texture object.
	result = m_RefractionTexture->Initialize(Direct3D->GetDevice(), screenWidth, screenHeight, screenDepth, 0.1f);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the refraction render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the reflection render to texture object.
	m_ReflectionTexture = new RenderTexture;
	if (!m_ReflectionTexture)
	{
		return false;
	}

	// Initialize the reflection render to texture object.
	result = m_ReflectionTexture->Initialize(Direct3D->GetDevice(), screenWidth, screenHeight, screenDepth, 0.1f);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the reflection render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the water object.
	m_Water = new Water;
	if (!m_Water)
	{
		return false;
	}

	// Initialize the water object.
	result = m_Water->Initialize(Direct3D->GetDevice(), L"../Engine/data/waternormal.dds", 14.75f, (float)(m_Terrain->GetTerrainWidth()/2));
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the water object.", L"Error", MB_OK);
		return false;
	}

	// Set the UI to display by default.
	m_displayUI = true;

	// Set wire frame rendering initially to enabled.
	m_wireFrame = false;

	// Set the rendering of cell lines initially to enabled.
	m_cellLines = false;

	// Set the user locked to the terrain height for movement.
	m_heightLocked = true;

	return true;
}


void Scene::Shutdown()
{
	// Release the water object.
	if (m_Water)
	{
		m_Water->Shutdown();
		delete m_Water;
		m_Water = 0;
	}

	// Release the reflection render to texture object.
	if (m_ReflectionTexture)
	{
		m_ReflectionTexture->Shutdown();
		delete m_ReflectionTexture;
		m_ReflectionTexture = 0;
	}

	// Release the refraction render to texture object.
	if (m_RefractionTexture)
	{
		m_RefractionTexture->Shutdown();
		delete m_RefractionTexture;
		m_RefractionTexture = 0;
	}

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

	// Release the frustum object.
	if (m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = 0;
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
	bool result, foundHeight;
	float posX, posY, posZ, rotX, rotY, rotZ, height;


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

	// Do the terrain frame processing.
	m_Terrain->Frame();

	// If the height is locked to the terrain then position the camera on top of it.
	if (m_heightLocked)
	{
		// Get the height of the triangle that is directly underneath the given camera position.
		foundHeight = m_Terrain->GetHeightAtPosition(posX, posZ, height);
		if (foundHeight)
		{
			// If there was a triangle under the camera then position the camera just above it by one meter.
			m_Position->SetPosition(posX, height + 1.0f, posZ);
			m_Camera->SetPosition(posX, height + 1.0f, posZ);
		}
	}

	// Do the water frame processing.
	m_Water->Frame();

	// Render the refraction of the scene to a texture.
	RenderRefractionToTexture();

	// Render the reflection of the scene to a texture.
	RenderReflectionToTexture();

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

	//Check mouse input
	m_Position->MouseTurn(Input->GetMouseDeltaX());
	m_Position->MousePitch(Input->GetMouseDeltaY());

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	// Determine if the user interface should be displayed or not.
	if (Input->IsButtonPressed(DIK_F1))
	{
		m_displayUI = !m_displayUI;
	}

	// Determine if the terrain should be rendered in wireframe or not.
	if (Input->IsButtonPressed(DIK_F2))
	{
		m_wireFrame = !m_wireFrame;
	}

	// Determine if the cell terrain frame should be rendered or not
	if (Input->IsButtonPressed(DIK_F3))
	{
		m_cellLines = !m_cellLines;
	}

	// Determine if we should be locked to the terrain height when we move around or not.
	if (Input->IsButtonPressed(DIK_F4))
	{
		m_heightLocked = !m_heightLocked;
	}

	return;
}

void Scene::RenderRefractionToTexture()
{
	/*XMFLOAT4 clipPlane;
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;


	// Setup a clipping plane based on the height of the water to clip everything above it to create a refraction.
	clipPlane = XMFLOAT4(0.0f, -1.0f, 0.0f, m_Water->GetWaterHeight() + 0.1f);

	// Set the render target to be the refraction render to texture.
	m_RefractionTexture->SetRenderTarget(D3DManager::getInstance()->GetDeviceContext());

	// Clear the refraction render to texture.
	m_RefractionTexture->ClearRenderTarget(D3DManager::getInstance()->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the matrices from the camera and d3d objects.
	D3DManager::getInstance()->GetWTurnOnAlporldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	D3DManager::getInstance()->GetProjectionMatrix(projectionMatrix);

	// Render the terrain using the reflection shader and the refraction clip plane to produce the refraction effect.
	m_Terrain->Render(D3DManager::getInstance()->GetDeviceContext());
	m_ReflectionShader->Render(D3DManager::getInstance()->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Terrain->GetColorTexture(), m_Terrain->GetNormalTexture(), m_Light->GetDiffuseColor(), m_Light->GetDirection(), 2.0f,
		clipPlane);

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	D3DManager::getInstance()->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	D3DManager::getInstance()->ResetViewport();

	return;*/
}

void Scene::RenderReflectionToTexture()
{
	/*D3DXVECTOR4 clipPlane;
	D3DXMATRIX reflectionViewMatrix, worldMatrix, projectionMatrix;
	D3DXVECTOR3 cameraPosition;


	// Setup a clipping plane based on the height of the water to clip everything below it.
	clipPlane = D3DXVECTOR4(0.0f, 1.0f, 0.0f, -m_Water->GetWaterHeight());

	// Set the render target to be the reflection render to texture.
	m_ReflectionTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	// Clear the reflection render to texture.
	m_ReflectionTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Use the camera to render the reflection and create a reflection view matrix.
	m_Camera->RenderReflection(m_Water->GetWaterHeight());

	// Get the camera reflection view matrix instead of the normal view matrix.
	m_Camera->GetReflectionViewMatrix(reflectionViewMatrix);

	// Get the world and projection matrices from the d3d object.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();

	// Invert the Y coordinate of the camera around the water plane height for the reflected camera position.
	cameraPosition.y = -cameraPosition.y + (m_Water->GetWaterHeight() * 2.0f);

	// Translate the sky dome and sky plane to be centered around the reflected camera position.
	D3DXMatrixTranslation(&worldMatrix, cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Turn off back face culling and the Z buffer.
	m_Direct3D->TurnOffCulling();
	m_Direct3D->TurnZBufferOff();

	// Render the sky dome using the reflection view matrix.
	m_SkyDome->Render(m_Direct3D->GetDeviceContext());
	m_SkyDomeShader->Render(m_Direct3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());

	// Enable back face culling.
	m_Direct3D->TurnOnCulling();

	// Enable additive blending so the clouds blend with the sky dome color.
	m_Direct3D->EnableSecondBlendState();

	// Render the sky plane using the sky plane shader.
	m_SkyPlane->Render(m_Direct3D->GetDeviceContext());
	m_SkyPlaneShader->Render(m_Direct3D->GetDeviceContext(), m_SkyPlane->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_SkyPlane->GetCloudTexture(), m_SkyPlane->GetPerturbTexture(), m_SkyPlane->GetTranslation(), m_SkyPlane->GetScale(),
		m_SkyPlane->GetBrightness());

	// Turn off blending and enable the Z buffer again.
	m_Direct3D->TurnOffAlphaBlending();
	m_Direct3D->TurnZBufferOn();

	// Reset the world matrix.
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// Render the terrain using the reflection view matrix and reflection clip plane.
	m_Terrain->Render(m_Direct3D->GetDeviceContext());
	m_ReflectionShader->Render(m_Direct3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_Terrain->GetColorTexture(), m_Terrain->GetNormalTexture(), m_Light->GetDiffuseColor(), m_Light->GetDirection(), 2.0f,
		clipPlane);

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_Direct3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_Direct3D->ResetViewport();
	*/
	return;
}

bool Scene::Render(ShaderManager* ShaderManager)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrix, orthoMatrix, reflectionViewMatrix;
	bool result;
	XMFLOAT3 cameraPosition;
	int i;


	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Generate the reflection matrix based on the camera's position and the height of the water.
	m_Camera->RenderReflection(m_Water->GetWaterHeight());

	// Get the world, view, and projection matrices from the camera and d3d objects.
	D3DManager::getInstance()->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	D3DManager::getInstance()->GetProjectionMatrix(projectionMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	D3DManager::getInstance()->GetOrthoMatrix(orthoMatrix);
	m_Camera->GetReflectionViewMatrix(reflectionViewMatrix);

	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();

	// Construct the frustum.
	m_Frustum->ConstructFrustum(projectionMatrix, viewMatrix);

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

	// Render the terrain cells (and cell lines if needed).
	for (i = 0; i<m_Terrain->GetCellCount(); i++)
	{
		// Render each terrain cell if it is visible only.
		result = m_Terrain->RenderCell(D3DManager::getInstance()->GetDeviceContext(), i, m_Frustum);
		if (result)
		{
			// Render the cell buffers using the terrain shader.
			result = ShaderManager->RenderTerrainShader(D3DManager::getInstance()->GetDeviceContext(), m_Terrain->GetCellIndexCount(i), worldMatrix, viewMatrix,
				projectionMatrix, TextureManager::getInstance()->GetTexture(0), TextureManager::getInstance()->GetTexture(1),
				TextureManager::getInstance()->GetTexture(2), m_Light->GetDirection(), m_Light->GetDiffuseColor(), sandColor, grassColor);
			if (!result)
			{
				return false;
			}

			// If needed then render the bounding box around this terrain cell using the color shader. 
			if (m_cellLines)
			{
				m_Terrain->RenderCellLines(D3DManager::getInstance()->GetDeviceContext(), i);
				ShaderManager->RenderColorShader(D3DManager::getInstance()->GetDeviceContext(), m_Terrain->GetCellLinesIndexCount(i), worldMatrix,
					viewMatrix, projectionMatrix);
				if (!result)
				{
					return false;
				}
			}
		}
	}
	D3DManager::getInstance()->EnableAlphaBlending();

	// Translate to the location of the water and render it.
	worldMatrix = XMMatrixTranslation((float)(m_Terrain->GetTerrainWidth()/2), m_Water->GetWaterHeight()+XMScalarSin(TimerManager::getInstance()->GetTotalTime()*0.001f), (float)(m_Terrain->GetTerrainHeight() / 2));
	m_Water->Render(D3DManager::getInstance()->GetDeviceContext());
	result = ShaderManager->RenderWaterShader(D3DManager::getInstance()->GetDeviceContext(), m_Water->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, reflectionViewMatrix,
		m_RefractionTexture->GetShaderResourceView(), m_ReflectionTexture->GetShaderResourceView(), m_Water->GetTexture(),
		m_Camera->GetPosition(), m_Water->GetNormalMapTiling(), m_Water->GetWaterTranslation(), m_Water->GetReflectRefractScale(),
		m_Water->GetRefractionTint(), m_Light->GetDirection(), m_Water->GetSpecularShininess());
	if (!result)
	{
		return false;
	}

	D3DManager::getInstance()->DisableAlphaBlending();

	// Turn off wire frame rendering of the terrain if it was on.
	if (m_wireFrame)
	{
		D3DManager::getInstance()->DisableWireframe();
	}

	// Reset the world matrix.
	D3DManager::getInstance()->GetWorldMatrix(worldMatrix);

	// Update the render counts in the UI.
	result = m_UserInterface->UpdateRenderCounts(D3DManager::getInstance()->GetDeviceContext(), m_Terrain->GetRenderCount(), m_Terrain->GetCellsDrawn(),
		m_Terrain->GetCellsCulled());
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