////////////////////////////////////////////////////////////////////////////////
// Filename: Frustum.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _Frustum_H_
#define _Frustum_H_


//////////////
// INCLUDES //
//////////////
#include <directxmath.h>
using namespace DirectX;


////////////////////////////////////////////////////////////////////////////////
// Class name: Frustum
////////////////////////////////////////////////////////////////////////////////
class Frustum
{
public:
	Frustum();
	Frustum(const Frustum&);
	~Frustum();

	void Initialize(float);

	void ConstructFrustum(XMMATRIX, XMMATRIX);

	bool CheckPoint(float, float, float);
	bool CheckCube(float, float, float, float);
	bool CheckSphere(float, float, float, float);
	bool CheckRectangle(float, float, float, float, float, float);
	bool CheckRectangle2(float, float, float, float, float, float);

private:
	float m_screenDepth;
	float m_planes[6][4];
};

#endif