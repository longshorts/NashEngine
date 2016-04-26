////////////////////////////////////////////////////////////////////////////////
// Filename: WaterShader.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _WaterShader_H_
#define _WaterShader_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;

#include <DirectXMath.h>
using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: WaterShader
////////////////////////////////////////////////////////////////////////////////
class WaterShader
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
		XMMATRIX reflection;
	};

	struct CamNormBufferType
	{
		XMFLOAT3 cameraPosition;
		float padding1;
		XMFLOAT2 normalMapTiling;
		XMFLOAT2 padding2;
	};

	struct WaterBufferType
	{
		XMFLOAT4 refractionTint;
		XMFLOAT3 lightDirection;
		float waterTranslation;
		float reflectRefractScale;
		float specularShininess;
		XMFLOAT2 padding;
	};

public:
	WaterShader();
	WaterShader(const WaterShader&);
	~WaterShader();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT2, float, float, XMFLOAT4, XMFLOAT3, float);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT2, float, float, XMFLOAT4, XMFLOAT3, float);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_camNormBuffer;
	ID3D11Buffer* m_waterBuffer;
};

#endif