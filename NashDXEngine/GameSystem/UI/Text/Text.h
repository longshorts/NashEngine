////////////////////////////////////////////////////////////////////////////////
// Filename: Text.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _Text_H_
#define _Text_H_


//////////////
// INCLUDES //
//////////////
#include "../Font/Font.h"
#include "../../Shader/ShaderManager.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: Text
////////////////////////////////////////////////////////////////////////////////
class Text
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

public:
	Text();
	Text(const Text&);
	~Text();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, int, int, int, bool, Font*, char*, int, int, float, float, float);
	void Shutdown();
	void Render(ID3D11DeviceContext*, ShaderManager*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*);

	bool UpdateSentence(ID3D11DeviceContext*, Font*, char*, int, int, float, float, float);

private:
	bool InitializeSentence(ID3D11Device*, ID3D11DeviceContext*, Font*, char*, int, int, float, float, float);
	void RenderSentence(ID3D11DeviceContext*, ShaderManager*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*);

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer, *m_vertexBuffer2, *m_indexBuffer2;
	int m_screenWidth, m_screenHeight, m_maxLength, m_vertexCount, m_indexCount;
	bool m_shadow;
	XMFLOAT4 m_pixelColor;
};

#endif