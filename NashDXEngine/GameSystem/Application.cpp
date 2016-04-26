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
	m_ParticleSystem = 0;*/

	enableParticleSystem = false;
	enableAdditiveBlending = true;
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
	XMFLOAT4X4 baseViewMatrix;

	// Initialize the Direct3D singleton.
	new D3DManager();
	if (!D3DManager::getInstance())
		return false;

	result = D3DManager::getInstance()->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	//Create shaderManager
	m_ShaderManager = new ShaderManager;
	if (!m_ShaderManager)
		return false;

	//Initialize shaderManager
	result = m_ShaderManager->Initialize(D3DManager::getInstance()->GetDevice(), hwnd);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize ShaderManager.", L"Error", MB_OK);
		return false;
	}

	//Create texture manager
	new TextureManager();
	if (!TextureManager::getInstance())
		return false;

	//Initialize texture manager object
	result = TextureManager::getInstance()->Initialize(10);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the texture manager object.", L"Error", MB_OK);
		return false;
	}

	/*result = TextureManager::getInstance()->LoadTexture(
		D3DManager::getInstance()->GetDevice(), D3DManager::getInstance()->GetDeviceContext(), "../Assets/textures/dirt01d.tga", 1);
	if (!result) {
		return false;
	}

	result = TextureManager::getInstance()->LoadTexture(
		D3DManager::getInstance()->GetDevice(), D3DManager::getInstance()->GetDeviceContext(), "../Assets/textures/dirt01n.tga", 1);
	if (!result)
	{
		return false;
	}*/

	// Load textures into the texture manager.
	result = TextureManager::getInstance()->LoadTexture(
		D3DManager::getInstance()->GetDevice(), D3DManager::getInstance()->GetDeviceContext(), "../Assets/textures/rock01d.tga", 0);
	if (!result)
	{
		return false;
	}

	result = TextureManager::getInstance()->LoadTexture(
		D3DManager::getInstance()->GetDevice(), D3DManager::getInstance()->GetDeviceContext(), "../Assets/textures/rock01n.tga", 1);
	if (!result)
	{
		return false;
	}

	result = TextureManager::getInstance()->LoadTexture(
		D3DManager::getInstance()->GetDevice(), D3DManager::getInstance()->GetDeviceContext(), "../Assets/textures/dirt01n.tga", 2);
	if (!result)
	{
		return false;
	}

	result = TextureManager::getInstance()->LoadTexture(
		D3DManager::getInstance()->GetDevice(), D3DManager::getInstance()->GetDeviceContext(), "../Assets/textures/waternormal.dds", 3);

	//Initialize the Timer singleton
	new TimerManager();
	if (!TimerManager::getInstance())
		return false;

	result = TimerManager::getInstance()->Initialize();
	if (!result) {
		MessageBox(hwnd, L"Could not initialize TimerManager.", L"Error", MB_OK);
		return false;
	}

	//Initialize the FPS singleton
	new FPSManager();
	if (!FPSManager::getInstance())
		return false;

	//Learn and test dynamic casting??
	//result = dynamic_cast<FPSManager*>(FPSManager::getInstance())->Initialize();
	result = FPSManager::getInstance()->Initialize();
	if (!result) {
		MessageBox(hwnd, L"Could not initialize FPSManager.", L"Error", MB_OK);
		return false;
	}

	//Initialize scene object
	m_Scene = new Scene;
	if (!m_Scene)
		return false;

	result = m_Scene->Initialize(hwnd, screenWidth, screenHeight, SCREEN_DEPTH);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize Scene.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void Application::Shutdown()
{
	//Release TextureManager instance
	if (TextureManager::getInstance()) {
		TextureManager::getInstance()->Shutdown();
		delete TextureManager::getInstance();
	}

	//Release ShaderManager
	if (m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	//Release FPSManager instance
	if (FPSManager::getInstance()) {
		FPSManager::getInstance()->Shutdown();
		delete FPSManager::getInstance();;
	}

	//Release TimerManager instance
	if (TimerManager::getInstance()) {
		delete TimerManager::getInstance();;
	}

	// Release the D3D object.
	if (D3DManager::getInstance()) {
		D3DManager::getInstance()->Shutdown();
		delete D3DManager::getInstance();
	}
		



	return;
}


bool Application::Frame(int fps, int cpu, float frameTime)
{
	bool result, keyDown;
	static float rotate = 0.0f;
	int mouseX, mouseY;
	float rotationY, rotationX;
	float positionX, positionY, positionZ;

	FPSManager::getInstance()->Frame();
	TimerManager::getInstance()->Frame();

	//Do Scene processing
	result = m_Scene->Frame(m_ShaderManager, TimerManager::getInstance()->GetTime(), FPSManager::getInstance()->GetFps());
	if (!result) {
		return false;
	}

	return true;
}