////////////////////////////////////////////////////////////////////////////////
// Filename: Water.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _Water_H_
#define _Water_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>

#include <DirectXMath.h>
using namespace DirectX;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "../../../Texture/Texture.h"
#include "../../../Texture/TextureManager.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: Water
////////////////////////////////////////////////////////////////////////////////
class Water
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	Water();
	Water(const Water&);
	~Water();

	bool Initialize(ID3D11Device*, WCHAR*, float, float);
	void Shutdown();
	void Frame();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

	float GetWaterHeight();
	XMFLOAT2 GetNormalMapTiling();
	float GetWaterTranslation();
	float GetReflectRefractScale();
	XMFLOAT4 GetRefractionTint();
	float GetSpecularShininess();

private:
	bool InitializeBuffers(ID3D11Device*, float);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	float m_waterHeight;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	//Texture* m_Texture;
	XMFLOAT2 m_normalMapTiling;
	float m_waterTranslation;
	float m_reflectRefractScale;
	XMFLOAT4 m_refractionTint;
	float m_specularShininess;
};

#endif