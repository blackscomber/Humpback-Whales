#include "D3DRenderer.h"

DWORD FrameCnt;
float TimeElapsed;
float FPS;

void CalcFPS(float timeDelta)
{
	FrameCnt++;
	TimeElapsed += timeDelta;

	if(TimeElapsed >= 1.0f)
	{
		FPS =  (float)FrameCnt / TimeElapsed;
		TimeElapsed = 0.f;
		FrameCnt = 0;
	}
}

void D3DRenderer::StaticConstructor()
{
	m_fAngle = 0.0f;
	WINDOW_WIDTH  = 0;
	WINDOW_HEIGHT = 0;

	p_mD3DFont = NULL;

	//LOGFONT logfont;
	//ZeroMemory(&logfont, sizeof(LOGFONT));
	//logfont.lfHeight = 25;
	//logfont.lfWidth  = 12;
	//logfont.lfWeight = 500; // scope : 0(thin) - 1000(bold)
	//logfont.lfItalic = false;
	//logfont.lfUnderline = false;
	//logfont.lfStrikeOut = false;
	//logfont.lfCharSet   = DEFAULT_CHARSET;
	//strcpy(logfont.lfFaceName, L"Times New Roman");

	//D3DXCreateFontIndirect(g_Device, &logfont, &p_mD3DFont);
}

void D3DRenderer::StaticDestructor()
{
	if(g_debug.good())
	{
		g_debug.close();
	}
}

HRESULT D3DRenderer::CreateDevice( HWND hWnd, int Width, int Height )
{
	//Create IDirect3D9 Interface
	IDirect3D9* d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	if(d3d9 == NULL)
	{
		g_debug << "Direct3DCreate9() - FAILED \n";
		return E_FAIL;
	}

	// Check that the Device supports what we need from it
	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	//Check vertex & pixelshader versions
	if(caps.VertexShaderVersion < D3DVS_VERSION(2, 0) || caps.PixelShaderVersion < D3DPS_VERSION(2, 0))
	{
		g_debug << "Warning - Your graphic card does not support vertex and pixelshaders version 2.0 \n";
		return E_FAIL;
	}

	//Set D3DPRESENT_PARAMETERS
	m_present.BackBufferWidth            = WINDOW_WIDTH  = (UINT)Width;
	m_present.BackBufferHeight           = WINDOW_HEIGHT = (UINT)Height;
	m_present.BackBufferFormat           = D3DFMT_A8R8G8B8;
	m_present.BackBufferCount            = 2;
	m_present.MultiSampleType            = D3DMULTISAMPLE_NONE;
	m_present.MultiSampleQuality         = 0;
	m_present.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	m_present.hDeviceWindow              = hWnd;
	m_present.Windowed                   = true; //windowed;
	m_present.EnableAutoDepthStencil     = true; 
	m_present.AutoDepthStencilFormat     = D3DFMT_D24S8;
	m_present.Flags                      = 0;
	m_present.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_present.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

	//Hardware Vertex Processing
	int vp = 0;
	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	try
	{
		//Create the IDirect3DDevice9
		HR(d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, vp, &m_present, &g_pDevice));
	}
	catch (HRESULT e)
	{
		g_debug << "Failed to create IDirect3DDevice9 \n";
		return E_FAIL;
	}

	//Release IDirect3D9 interface
	SAFE_RELEASE( d3d9 );

	//Load Application Specific resources here...
	D3DXCreateFont(g_pDevice, 20, 0, FW_BOLD, 1, false,  
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, L"Arial", &g_pFont);

	//Create Sprite
	D3DXCreateSprite(g_pDevice, &g_pSprite);

	//Load Effect
	try
	{
		ID3DXBuffer *pErrorMsgs = NULL;
		HR(D3DXCreateEffectFromFile(g_pDevice, L"Resources/FX/lighting.fx", NULL, NULL, D3DXSHADER_DEBUG, NULL, &g_pEffect, &pErrorMsgs))
	}
	catch (HRESULT e)
	{
		g_debug << "Failed to create effect from file -- Resources/fx/light.fx \n";
		return E_FAIL;
	}

	//Load Soldier Mesh
	const string & filename = "resources/meshes/soldier.x";
	m_mesh.LoadMeshFromX((LPCSTR)filename.c_str());
	m_bDeviceLost = false;

	//////////////////////////////////////////////////////////////////////////
	//Create Transformation Matrices
	D3DXMATRIX view, proj, world;
	D3DXMatrixIdentity(&world);
	m_vecCameraLocation = D3DXVECTOR3(0.f, 1.f, -5.0f);	
	D3DXMatrixLookAtLH( &view, &m_vecCameraLocation, &D3DXVECTOR3(0.f, 1.f, 0.f), &D3DXVECTOR3(0.f, 1.f, 0.f) );
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI / 4.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

	//Set transformation matrices
	g_pDevice->SetTransform(D3DTS_WORLD, &world);
	g_pDevice->SetTransform(D3DTS_VIEW, &view);
	g_pDevice->SetTransform(D3DTS_PROJECTION, &proj);
	g_pEffect->SetMatrix("matVP", &(view * proj));

	return S_OK;
}

void D3DRenderer::DestroyDevice()
{
	SAFE_RELEASE( g_pDevice );
}

void D3DRenderer::DeviceLost()
{
	//Device lost happens at ALT + TAB and similar events
	try
	{
		g_pFont->OnLostDevice();
		g_pSprite->OnLostDevice();
		g_pEffect->OnLostDevice();
		m_bDeviceLost = true;
	}
	catch(...)
	{
		g_debug << "Error occured in D3DRenderer::DeviceLost() \n";
	}
}

void D3DRenderer::DeviceGained()
{
	try
	{
		g_pDevice->Reset(&m_present);
		g_pFont->OnResetDevice();
		g_pSprite->OnResetDevice();	
		g_pEffect->OnResetDevice();
		m_bDeviceLost = false;
	}
	catch(...)
	{
		g_debug << "Error occured in D3DRenderer::DeviceGained() \n";
	}
}

void D3DRenderer::Update(float deltaTime)
{
	/*CalcFPS(deltaTime);

	std::string strFps;
	strFps.
	p_mD3DFont->DrawTextA()
	FPS*/
	try
	{
		//Check for lost device
		HRESULT coop = g_pDevice->TestCooperativeLevel();

		if(coop != D3D_OK)
		{
			if(coop == D3DERR_DEVICELOST)
			{
				if(m_bDeviceLost == false)
					DeviceLost();		
			}
			else if(coop == D3DERR_DEVICENOTRESET)
			{
				if(m_bDeviceLost == true)
					DeviceGained();
			}

			Sleep(100);
			return;
		}

		//Camera Rotation
		m_fAngle += deltaTime;

		//Keyboard input
		/*if(KeyDown(VK_ESCAPE))
		{
			Quit();
		}*/

		//Switching between window mode and full screen
		//if(KeyDown(VK_RETURN) && KeyDown(18))		//ALT + RETURN
		//{
		//	//Switch between windowed mode and fullscreen mode
		//	m_present.Windowed = !m_present.Windowed;

		//	DeviceLost();
		//	DeviceGained();

		//	if(m_present.Windowed)
		//	{
		//		RECT rc = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
		//		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
		//		SetWindowPos(m_hMainWindow, HWND_NOTOPMOST, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW);
		//		UpdateWindow(m_hMainWindow);
		//	}
		//}
	}
	catch(...)
	{
		g_debug << "Error in D3DRenderer::Update() \n";
	}
}

void D3DRenderer::Render()
{
	if(!m_bDeviceLost)
	{
		try
		{
			D3DXMATRIX identity, shadow;
			D3DXMatrixIdentity(&identity);

			//Set ground plane + light position
			D3DXPLANE ground(0.0f, 1.0f, 0.0f, 0.0f);
			D3DXVECTOR4 lightPos(-20.0f, 75.0f, -120.0f, 0.0f);

			//Create the shadow matrix
			D3DXMatrixShadow(&shadow, &lightPos, &ground);			

			// Clear the viewport
			g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);

			// Begin the scene 
			if(SUCCEEDED(g_pDevice->BeginScene()))
			{	
				//Render Soldier
				{					
#if 0
					D3DXVECTOR3 CameraLocation = D3DXVECTOR3(0.f, 0.f, -10.0f);
					D3DXVec3TransformCoord( &CameraLocation, &CameraLocation, g_ModelArcBall.GetRotationMatrix() );
					D3DXMatrixLookAtLH( &view, &CameraLocation, &D3DXVECTOR3(0.f, 0.f, 0.f), &D3DXVECTOR3(0.f, 1.f, 0.f) );
					g_pEffect->SetMatrix("matW", &world);
					g_pEffect->SetMatrix("matVP", &(view*proj));
#endif

					g_pEffect->SetVector("lightPos", &lightPos);
					D3DXHANDLE hTech = g_pEffect->GetTechniqueByName("Lighting");
					g_pEffect->SetTechnique(hTech);
					g_pEffect->Begin(NULL, NULL);
					g_pEffect->BeginPass(0);

					m_mesh.Render();			

					g_pEffect->EndPass();
					g_pEffect->End();
				}

				//Render Shadow
				{
					g_pEffect->SetMatrix("matW", &shadow);
					D3DXHANDLE hTech = g_pEffect->GetTechniqueByName("Shadow");
					g_pEffect->SetTechnique(hTech);
					g_pEffect->Begin(NULL, NULL);
					g_pEffect->BeginPass(0);

					m_mesh.Render();

					g_pEffect->EndPass();
					g_pEffect->End();
				}

				// End the scene.
				g_pDevice->EndScene();
				g_pDevice->Present(0, 0, 0, 0);
			}
		}
		catch(...)
		{
			g_debug << "Error in D3DRenderer::Render() \n";
		}
	}
}

void D3DRenderer::Cleanup()
{
	//Release all resources here...
	if(g_pSprite != NULL)	g_pSprite->Release();
	if(g_pFont != NULL)		g_pFont->Release();
	if(g_pDevice != NULL)	g_pDevice->Release();
	if(g_pEffect != NULL)	g_pEffect->Release();

	g_debug << "D3DRenderer Terminated \n";
}

//void D3DRenderer::Quit()
//{
//	DestroyWindow(m_hMainWindow);
//	PostQuitMessage(0);
//}