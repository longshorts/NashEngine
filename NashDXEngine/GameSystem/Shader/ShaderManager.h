////////////////////////////////////////////////////////////////////////////////
// Filename: ShaderManager.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _ShaderManager_H_
#define _ShaderManager_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "../Direct3DManager/D3DManager.h"
#include "ColorShader\ColorShader.h"
#include "FontShader\FontShader.h"


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
	bool RenderFontShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT4);

private:
	ColorShader* m_ColorShader;
	FontShader* m_FontShader;
};

#endif