#include "ArcBall.h"

void ArcBall::StaticConstructor()
{
	m_WindowWidth = 0;
	m_WindowHeight = 0;

	m_Start = m_Current = D3DXVECTOR3(0.f, 0.f, 0.f);

	D3DXQuaternionIdentity(&m_OldRotation);
	D3DXQuaternionIdentity(&m_CurRotation);
	D3DXMatrixIdentity(&m_RotationMatrix);
}

void ArcBall::StaticDestructor()
{
	
}

void ArcBall::SetWindowSize(int width, int height)
{
	m_WindowWidth = width;
	m_WindowHeight = height;
}

void ArcBall::DragStart(int x, int y)
{
	m_Start = ScreenToVector(x, y);
	m_OldRotation = m_CurRotation;
}

void ArcBall::Drag(int x, int y)
{
	m_Current = ScreenToVector(x, y);
	m_CurRotation = m_OldRotation * QuatFromBallPoints(m_Start, m_Current);
}

D3DXVECTOR3 ArcBall::ScreenToVector(float xIn, float yIn)
{
	float x = -( xIn - m_WindowWidth * 0.5f ) / ( m_WindowWidth * 0.5f );
	float y = ( yIn - m_WindowHeight * 0.5f ) / ( m_WindowHeight * 0.5f );

	float z = 0.0f;
	float mag = x * x + y * y;

	if( mag > 1.0f )
	{
		float scale = 1.0f / sqrtf( mag );
		x *= scale;
		y *= scale;
	}
	else
		z = sqrtf( 1.0f - mag );

	return D3DXVECTOR3( x, y, z );
}

D3DXQUATERNION ArcBall::QuatFromBallPoints(const D3DXVECTOR3& from, const D3DXVECTOR3& to)
{
	float dot = D3DXVec3Dot( &from, &to );

	D3DXVECTOR3 cross;
	D3DXVec3Cross( &cross, &from, &to );

	return D3DXQUATERNION( cross.x, cross.y, cross.z, dot );
}

const D3DXMATRIX* ArcBall::GetRotationMatrix()
{
	return D3DXMatrixRotationQuaternion(&m_RotationMatrix, &m_CurRotation);
}