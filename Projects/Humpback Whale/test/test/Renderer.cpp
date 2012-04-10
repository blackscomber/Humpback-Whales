#include "Renderer.h"

void Renderer::StaticConstructor()
{
	memset( &m_PresentParams, 0, sizeof( m_PresentParams ) );

	m_WindowWidth = 0;
	m_WindowHeight = 0;

	m_PreviewMesh = NULL;
}

void Renderer::StaticDestructor()
{
	SAFE_RELEASE( m_PreviewMesh );
	SAFE_RELEASE( theDevice );
}

void Renderer::CreateDevice(HWND Wnd, int Width, int Height)
{
	m_WindowWidth = Width;
	m_WindowHeight = Height;

	IDirect3D9* Direct3D = Direct3DCreate9( D3D_SDK_VERSION );

	DWORD BehaviorFlag = 0;
	BehaviorFlag |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	BehaviorFlag |= D3DCREATE_MULTITHREADED;

	D3DPRESENT_PARAMETERS Params = {0, };
	Params.Windowed = TRUE;
	Params.BackBufferCount = 1;
	Params.BackBufferWidth = 0;
	Params.BackBufferHeight = 0;
	Params.BackBufferFormat = D3DFMT_UNKNOWN;
	Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	Params.MultiSampleType = D3DMULTISAMPLE_NONE;
	Params.MultiSampleQuality = 0;
	Params.hDeviceWindow = Wnd;
	Params.EnableAutoDepthStencil = TRUE;
	Params.AutoDepthStencilFormat = D3DFMT_D24S8;
	Params.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	Params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	m_PresentParams = Params;

	HR( Direct3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Wnd, BehaviorFlag, &Params, &theDevice ) );

	SAFE_RELEASE( Direct3D );

#if 1
	HR( D3DXCreateSphere( theDevice, 3.f, 100, 100, &m_PreviewMesh, NULL ) );
#else
	ID3DXMesh* Mesh = NULL;
	HR( D3DXLoadMeshFromXA( "rez\\models\\sphere.x", D3DXMESH_MANAGED, theDevice, NULL, NULL, NULL, NULL, &Mesh ) );
	DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX3 | D3DFVF_TEXCOORDSIZE2(0) | D3DFVF_TEXCOORDSIZE3(1) | D3DFVF_TEXCOORDSIZE3(2);
	HR( Mesh->CloneMeshFVF( D3DXMESH_MANAGED, FVF, theDevice, &m_PreviewMesh ) );
	SAFE_RELEASE( Mesh );
#endif

	D3DXMATRIX worldMat, viewmat, projectionMat;
	D3DXMatrixIdentity( &worldMat );
	D3DXMatrixLookAtLH( &viewmat, &D3DXVECTOR3(0.f, 0.f, -12.0f), &D3DXVECTOR3(0.f, 0.f, 0.f), &D3DXVECTOR3(0.f, 1.f, 0.f) );
	D3DXMatrixPerspectiveFovLH( &projectionMat, D3DX_PI / 4, m_WindowWidth / (float)m_WindowHeight, 1.f, 100.f );
	theDevice->SetTransform( D3DTS_WORLD, &worldMat );
	theDevice->SetTransform( D3DTS_VIEW, &viewmat );
	theDevice->SetTransform( D3DTS_PROJECTION, &projectionMat );

#if 1
	D3DMATERIAL9 material;
	memset( &material, 0, sizeof(material) );
	material.Diffuse.r = 1.f;
	theDevice->SetMaterial( &material );

	theDevice->LightEnable( 0, true );
	theDevice->SetRenderState( D3DRS_LIGHTING, 1 );
	D3DLIGHT9 light;
	memset(&light, 0, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient.r = 0.1f; light.Ambient.g = 0.1f; light.Ambient.b = 0.1f; light.Ambient.a = 1.f;
	light.Diffuse.r = 1.f; light.Diffuse.g = 1.f; light.Diffuse.b = 1.f; light.Diffuse.a = 1.f;
	light.Direction = D3DXVECTOR3( 1.f, -0.5f, 1.f );
	theDevice->SetLight( 0, &light );
#endif

#if 0
	theEffectAgent.CreateEffect();
#endif
}

void Renderer::DestroyDevice()
{
	SAFE_RELEASE( theDevice );
}

void Renderer::DoRender()
{
	HR(theDevice->Clear( 0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.f, 0 ));
	HR(theDevice->BeginScene());

	if(m_PreviewMesh)
		m_PreviewMesh->DrawSubset( 0 );

	HR(theDevice->EndScene());
	HR(theDevice->Present( 0, 0, 0, 0 ));
}