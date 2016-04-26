////////////////////////////////////////////////////////////////////////////////
// Filename: ShaderManager.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _ShaderManager_H_
#define _ShaderManager_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "../Direct3DManager/D3DManager.h"
#include "ColorShader/ColorShader.h"
#include "TextureShader/TextureShader.h"
#include "LightShader/LightShader.h"
#include "FontShader/FontShader.h"
#include "SkyDomeShader/SkyDomeShader.h"
#include "TerrainShader/TerrainShader.h"
#include "WaterShader/WaterShader.h"
#include "ReflectionShader/ReflectionShader.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: ShaderManager
////////////////////////////////////////////////////////////////////////////////
class ShaderManager
{
public:
	ShaderManager();
	ShaderManager(const ShaderManager&);
	~ShaderManager();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();

	bool RenderColorShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX);
	bool RenderTextureShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*);
	bool RenderLightShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4);
	bool RenderFontShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT4);
	bool RenderSkyDomeShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, XMFLOAT4, XMFLOAT4);
	bool RenderTerrainShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4, XMFLOAT4, XMFLOAT4);
	bool RenderWaterShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT2, float, float, XMFLOAT4, XMFLOAT3, float);
	bool RenderReflectionShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX,
		XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		XMFLOAT4, XMFLOAT3, float, XMFLOAT4);

private:
	ColorShader* m_ColorShader;
	TextureShader* m_TextureShader;
	LightShader* m_LightShader;
	FontShader* m_FontShader;
	SkyDomeShader* m_SkyDomeShader;
	TerrainShader* m_TerrainShader;
	WaterShader* m_WaterShader;
	ReflectionShader* m_ReflectionShader;
};

#endif