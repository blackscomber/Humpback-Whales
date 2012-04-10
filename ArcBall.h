#pragma once

#include <d3d9.h>
#include <d3dx9math.h>

class __declspec(novtable) ArcBall
{
public:
	void StaticConstructor();
	void StaticDestructor();
	void SetWindowSize(int width, int height);
	void DragStart(int x, int y);
	void Drag(int x, int y);
	D3DXVECTOR3 ScreenToVector(float x, float y);
	D3DXQUATERNION QuatFromBallPoints(const D3DXVECTOR3& from, const D3DXVECTOR3& to);
	D3DXMATRIX* GetRotationMatrix();

private:
	D3DXVECTOR3 m_Start;
	D3DXVECTOR3 m_Current;
	D3DXQUATERNION m_OldRotation;
	D3DXQUATERNION m_CurRotation;
	D3DXMATRIX m_RotationMatrix;

	int m_WindowWidth;
	int m_WindowHeight;
};

__declspec(selectany) ArcBall g_ModelArcBall;
__declspec(selectany) ArcBall g_LightArcBall;