////////////////////////////////////////////////////////////////////////////////
// Filename: UserInterface.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _UserInterface_H_
#define _UserInterface_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "Text/Text.h"
#include "../Direct3DManager/D3DManager.h"
#include "../Shader/ShaderManager.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: UserInterface
////////////////////////////////////////////////////////////////////////////////
class UserInterface
{
public:
	UserInterface();
	UserInterface(const UserInterface&);
	~UserInterface();

	bool Initialize(D3DManager*, int, int);
	void Shutdown();

	bool Frame(ID3D11DeviceContext*, int, float, float, float, float, float, float);
	bool Render(D3DManager*, ShaderManager*, XMMATRIX, XMMATRIX, XMMATRIX);

private:
	bool UpdateFpsString(ID3D11DeviceContext*, int);
	bool UpdatePositionStrings(ID3D11DeviceContext*, float, float, float, float, float, float);

private:
	Font* m_Font1;
	Text *m_FpsString, *m_VideoStrings, *m_PositionStrings;
	int m_previousFps;
	int m_previousPosition[6];
};

#endif