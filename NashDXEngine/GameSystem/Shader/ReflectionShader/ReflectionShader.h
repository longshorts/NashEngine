////////////////////////////////////////////////////////////////////////////////
// Filename: ReflectionShader.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _ReflectionShader_H_
#define _ReflectionShader_H_


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
// Class name: ReflectionShader
////////////////////////////////////////////////////////////////////////////////
class ReflectionShader
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct ClipPlaneBufferType
	{
		XMFLOAT4 clipPlane;
	};

	struct LightBufferType
	{
		XMFLOAT4 lightDiffuseColor;
		XMFLOAT3 lightDirection;
		float colorTextureBrightness;
	};

public:
	ReflectionShader();
	ReflectionShader(const ReflectionShader&);
	~ReflectionShader();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX,
		XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		XMFLOAT4, XMFLOAT3, float, XMFLOAT4);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, XMFLOAT4,
		XMFLOAT3, float, XMFLOAT4);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_clipPlaneBuffer;
	ID3D11Buffer* m_lightBuffer;
};

#endif