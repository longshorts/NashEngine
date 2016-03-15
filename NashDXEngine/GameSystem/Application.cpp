////////////////////////////////////////////////////////////////////////////////
// Filename: Application.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Application.h"


Application::Application()
{
	
	/*m_D3D = 0;
	m_Camera = 0;
	m_BoxModel = 0;
	m_TreeModel = 0;
	m_FireplaceModel = 0;
	m_FireModel = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_Text = 0;
	m_Position = 0;
	m_FireShader = 0;
	m_ParticleShader = 0;
	m_ParticleSystem = 0;

	enableParticleSystem = false;
	enableAdditiveBlending = false;*/

	m_InputManager = 0;
}


Application::Application(const Application& other)
{
}


Application::~Application()
{
}


bool Application::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	/*D3DXMATRIX baseViewMatrix;

	// Create the Direct3D object.
	m_D3D = new D3DManager;
	if (!m_D3D)
	{
		return false;
	}*/

	// Initialize the Direct3D object.
	/*result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}*/

	// Create the camera object.
	/*m_Camera = new Camera;
	if (!m_Camera)
	{
		return false;
	}*/

	// Create the position object.
	/*m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}
	m_Position->SetPosition(0.0f, 0.0f, -10.0f);*/

	// Set the initial position of the camera.
	/*m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);*/

	// Create the particle shader object.
	/*m_ParticleShader = new ParticleShaderClass;
	if (!m_ParticleShader)
	{
		return false;
	}*/

	// Initialize the particle shader object.
	/*result = m_ParticleShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the particle shader object.", L"Error", MB_OK);
		return false;
	}*/

	// Create the particle system object.
	/*m_ParticleSystem = new ParticleSystemClass;
	if (!m_ParticleSystem)
	{
		return false;
	}*/

	// Initialize the particle system object.
	/*result = m_ParticleSystem->Initialize(m_D3D->GetDevice(), L"../DX11Engine/data/star.dds");
	if (!result)
	{
		return false;
	}*/

	// Create the model objects.
	/*m_BoxModel = new ModelClass;
	if (!m_BoxModel)
	{
		return false;
	}

	m_TreeModel = new ModelClass;
	if (!m_TreeModel)
	{
		return false;
	}

	m_FireplaceModel = new ModelClass;
	if (!m_TreeModel)
	{
		return false;
	}

	m_FireModel = new ModelClass;
	if (!m_FireModel)
	{
		return false;
	}

	// Initialize the model objects.
	result = m_BoxModel->Initialize(m_D3D->GetDevice(), "../DX11Engine/data/cube.txt", L"../DX11Engine/data/grasstexturelrg.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the box model object.", L"Error", MB_OK);
		return false;
	}

	result = m_TreeModel->Initialize(m_D3D->GetDevice(), "../DX11Engine/data/lowpolytree.txt", L"../DX11Engine/data/grasstexturelrg.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the tree model object.", L"Error", MB_OK);
		return false;
	}

	result = m_FireplaceModel->Initialize(m_D3D->GetDevice(), "../DX11Engine/data/fireplace.txt", L"../DX11Engine/data/fireplacetexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fireplace model object.", L"Error", MB_OK);
		return false;
	}
	result = m_FireModel->Initialize(m_D3D->GetDevice(), "../DX11Engine/data/square.txt", L"../DX11Engine/data/firecolor.dds",
		L"../DX11Engine/data/firenoise.dds", L"../DX11Engine/data/firealpha.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fire model object.", L"Error", MB_OK);
		return false;
	}

	// Create the fire shader object.
	m_FireShader = new FireShaderClass;
	if (!m_FireShader)
	{
		return false;
	}

	// Initialize the fire shader object.
	result = m_FireShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fire shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.5f, -0.4f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}*/

	return true;
}


void Application::Shutdown()
{
	// Release the text object.
	/*if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the fire shader object.
	if (m_FireShader)
	{
		m_FireShader->Shutdown();
		delete m_FireShader;
		m_FireShader = 0;
	}

	// Release the model objects.
	if (m_BoxModel)
	{
		m_BoxModel->Shutdown();
		delete m_BoxModel;
		m_BoxModel = 0;
	}

	if (m_TreeModel)
	{
		m_TreeModel->Shutdown();
		delete m_TreeModel;
		m_TreeModel = 0;
	}

	if (m_FireplaceModel)
	{
		m_FireplaceModel->Shutdown();
		delete m_FireplaceModel;
		m_FireplaceModel = 0;
	}

	if (m_FireModel)
	{
		m_FireModel->Shutdown();
		delete m_FireModel;
		m_FireModel = 0;
	}

	// Release the particle system object.
	if (m_ParticleSystem)
	{
		m_ParticleSystem->Shutdown();
		delete m_ParticleSystem;
		m_ParticleSystem = 0;
	}

	// Release the particle shader object.
	if (m_ParticleShader)
	{
		m_ParticleShader->Shutdown();
		delete m_ParticleShader;
		m_ParticleShader = 0;
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

	// Release the D3D object.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}*/

	return;
}


bool Application::Frame(int fps, int cpu, float frameTime)
{
	bool result, keyDown;
	static float rotate = 0.0f;
	int mouseX, mouseY;
	float rotationY, rotationX;
	float positionX, positionY, positionZ;

	//keyDown = m_InputManager->IsButtonDown(DIK_ESCAPE);

	// Set the frames per second.
	/*result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Get the location of the mouse from the input object,
	input->GetMouseLocation(mouseX, mouseY);

	// Set the location of the mouse.
	result = m_Text->SetMousePosition(mouseX, mouseY, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Run the frame processing for the particle system.
	if (enableParticleSystem) m_ParticleSystem->Frame(frameTime, m_D3D->GetDeviceContext());

	// Check if an arrow key has been pressed, if so rotate the camera accordingly.
	keyDown = input->IsLeftArrowPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = input->IsRightArrowPressed();
	m_Position->TurnRight(keyDown);

	keyDown = input->IsUpArrowPressed();
	m_Position->TurnUp(keyDown);

	keyDown = input->IsDownArrowPressed();
	m_Position->TurnDown(keyDown);

	//Check if a WSAD key has been pressed, if so move camera accordingly.
	keyDown = input->IsWKeyPressed();
	m_Position->MoveForward(keyDown);

	keyDown = input->IsSKeyPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = input->IsAKeyPressed();
	m_Position->MoveLeft(keyDown);

	keyDown = input->IsDKeyPressed();
	m_Position->MoveRight(keyDown);

	//Other input functions
	//enableParticleSystem = input->IsPKeyPressed();
	if (input->IsPKeyPressed()) {
		enableParticleSystem = true;
	}
	else if (input->IsOKeyPressed()) {
		enableParticleSystem = false;
	}
	//enableParticleSystem = !input->IsOKeyPressed();

	if (input->IsLKeyPressed()) {
		enableAdditiveBlending = true;
	}
	else if (input->IsKKeyPressed()) {
		enableAdditiveBlending = false;
	}

	// Get the current view point rotation.
	m_Position->GetRotationY(rotationY);
	m_Position->GetRotationX(rotationX);
	m_Position->GetPosition(positionX, positionY, positionZ);

	// Set the rotation of the camera.
	m_Camera->SetRotation(rotationX, rotationY, 0.0f);
	m_Camera->SetPosition(positionX, positionY, positionZ);*/

	return true;
}


bool Application::Render(float frameTime)
{
	/*D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, modRotate;
	bool result;
	D3DXVECTOR3 scrollSpeeds, scales;
	D3DXVECTOR2 distortion1, distortion2, distortion3;
	float distortionScale, distortionBias;
	static float totalFrameTime = 0.0f;

	//BEGIN:FIRESETUP//////////////////////

	// Increment the frame time counter.
	totalFrameTime += 0.2f / frameTime;
	if (totalFrameTime > 1000.0f)
	{
		totalFrameTime = 0.0f;
	}

	// Set the three scrolling speeds for the three different noise textures.
	scrollSpeeds = D3DXVECTOR3(1.3f, 2.1f, 2.3f);

	// Set the three scales which will be used to create the three different noise octave textures.
	scales = D3DXVECTOR3(1.0f, 2.0f, 3.0f);

	// Set the three different x and y distortion factors for the three different noise textures.
	distortion1 = D3DXVECTOR2(0.1f, 0.2f);
	distortion2 = D3DXVECTOR2(0.1f, 0.3f);
	distortion3 = D3DXVECTOR2(0.1f, 0.1f);

	// The the scale and bias of the texture coordinate sampling perturbation.
	distortionScale = 0.8f;
	distortionBias = 0.5f;
	//END:FIRESETUP////////////////////////

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.1f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);


	if (enableAdditiveBlending) {
		m_D3D->EnableAdditiveBlending();
	}
	else {
		m_D3D->DisableAdditiveBlending();
	}
	// Turn on alpha blending for the fire transparency.
	//m_D3D->TurnOnAlphaBlending();



	// Turn off alpha blending.
	//m_D3D->TurnOffAlphaBlending();

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	//D3DXMatrixRotationY(&worldMatrix, rotation);
	//D3DXMatrixRotationYawPitchRoll(&modRotate, rotation, 0, 0);

	D3DXVECTOR3 boxPos = D3DXVECTOR3(0.0f, -1.7f, 0.0f);
	D3DXVECTOR3 boxScale = D3DXVECTOR3(10.0f, 0.1f, 10.0f);

	D3DXMATRIX pos, rot, sca;

	D3DXMatrixScaling(&sca, boxScale.x, boxScale.y, boxScale.z);
	D3DXMatrixTranslation(&pos, boxPos.x, boxPos.y, boxPos.z);

	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &sca);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &pos);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_BoxModel->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_BoxModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_BoxModel->GetTexture1(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}

	//RENDER TREES/////////////////////////////////

	D3DXVECTOR3 treePos1 = D3DXVECTOR3(1.0f, 0.0f, 2.5f);
	D3DXVECTOR3 treePos2 = D3DXVECTOR3(-2.0f, 0.0f, 3.0f);
	D3DXVECTOR3 treePos3 = D3DXVECTOR3(-0.5f, 0.0f, 4.0f);
	D3DXVECTOR3 treePos4 = D3DXVECTOR3(-5.5f, 0.0f, 4.0f);
	D3DXVECTOR3 treePos5 = D3DXVECTOR3(4.5f, 0.0f, 5.0f);

	//Reset world matrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixTranslation(&worldMatrix, treePos1.x, treePos1.y, treePos1.z);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_TreeModel->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_TreeModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_TreeModel->GetTexture1(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}

	//Reset world matrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixTranslation(&worldMatrix, treePos2.x, treePos2.y, treePos2.z);

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_TreeModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_TreeModel->GetTexture1(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}

	//Reset world matrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixTranslation(&worldMatrix, treePos3.x, treePos3.y, treePos3.z);

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_TreeModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_TreeModel->GetTexture1(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}

	//Reset world matrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixTranslation(&worldMatrix, treePos4.x, treePos4.y, treePos4.z);

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_TreeModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_TreeModel->GetTexture1(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}

	//Reset world matrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixTranslation(&worldMatrix, treePos5.x, treePos5.y, treePos5.z);

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_TreeModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_TreeModel->GetTexture1(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}

	//RENDER FIRE////////////////////////////////////////

	//Reset world matrix
	m_D3D->GetWorldMatrix(worldMatrix);

	D3DXVECTOR3 fireplacePos = D3DXVECTOR3(0.0f, -1.725f, 0.0f);
	D3DXVECTOR3 fireplaceScale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);

	D3DXMatrixScaling(&sca, fireplaceScale.x, fireplaceScale.y, fireplaceScale.z);
	D3DXMatrixTranslation(&pos, fireplacePos.x, fireplacePos.y, fireplacePos.z);

	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &sca);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &pos);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_FireplaceModel->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_FireplaceModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_FireplaceModel->GetTexture1(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	//Reset world matrix
	m_D3D->GetWorldMatrix(worldMatrix);

	float roty = 0;
	m_Position->GetRotationY(roty);
	D3DXVECTOR3 firePos = D3DXVECTOR3(0.0f, -0.8f, 0.0f);

	D3DXMatrixRotationY(&rot, D3DXToRadian(roty));
	D3DXMatrixTranslation(&pos, firePos.x, firePos.y, firePos.z);

	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &rot);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &pos);

	// Turn on the alpha blending
	m_D3D->TurnOnAlphaBlending();
	//m_D3D->DisableAdditiveBlending();

	// Put the fire model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_FireModel->Render(m_D3D->GetDeviceContext());

	// Render the square model using the fire shader.
	result = m_FireShader->Render(m_D3D->GetDeviceContext(), m_FireModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_FireModel->GetTexture1(), m_FireModel->GetTexture2(), m_FireModel->GetTexture3(), totalFrameTime, scrollSpeeds,
		scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
	if (!result)
	{
		return false;
	}

	if (enableParticleSystem) {
		m_D3D->GetWorldMatrix(worldMatrix);

		D3DXVECTOR3 fireParticlePos = D3DXVECTOR3(0.0f, -0.8f, 0.0f);
		D3DXMatrixTranslation(&worldMatrix, firePos.x, firePos.y, firePos.z);

		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &rot);


		// Put the particle system vertex and index buffers on the graphics pipeline to prepare them for drawing.
		m_ParticleSystem->Render(m_D3D->GetDeviceContext());

		// Render the model using the texture shader.
		result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_ParticleSystem->GetTexture());
		if (!result)
		{
			return false;
		}
	}

	//Reset world matrix
	m_D3D->GetWorldMatrix(worldMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Turn off alpha blending
	m_D3D->TurnOffAlphaBlending();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();*/

	return true;
}