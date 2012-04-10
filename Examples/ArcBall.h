#pragma once

#include "GraphicsProxyUtility.h"

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
	const D3DXMATRIX* GetRotationMatrix();

private:
	D3DXVECTOR3 m_Start;
	D3DXVECTOR3 m_Current;
	D3DXQUATERNION m_OldRotation;
	D3DXQUATERNION m_CurRotation;
	D3DXMATRIX m_RotationMatrix;

	int m_WindowWidth;
	int m_WindowHeight;
};

__declspec(selectany) ArcBall theModelArcBall;
__declspec(selectany) ArcBall theLightArcBall;