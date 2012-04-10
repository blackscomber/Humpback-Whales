#include "mesh.h"
#include "sat_utility.h"

#include <sstream>

extern IDirect3DDevice9 *g_pDevice;

#define PATH_TO_MESHES "resources/meshes/"

Mesh::Mesh()
	: m_pMesh(NULL)
{
}

Mesh::Mesh(const string & fName)
	: m_pMesh(NULL)
{
	LoadMeshFromX(fName);
}

Mesh::~Mesh()
{
	Release();
}

HRESULT Mesh::LoadMeshFromX(const string & fName)
{
	// Release old resources (if any)
	Release();

	// Set m_white material
	m_white.Ambient = m_white.Specular = m_white.Diffuse  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_white.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_white.Power = 1.f;

	//Load new mesh
	ID3DXBuffer * adjacencyBfr = NULL;
	ID3DXBuffer * materialBfr = NULL;
	DWORD noMaterials = NULL;

	try
	{
		HR(D3DXLoadMeshFromXA((LPCSTR)fName.c_str(), D3DXMESH_MANAGED, g_pDevice, &adjacencyBfr, &materialBfr, NULL, &noMaterials, &m_pMesh))	
	}
	catch (HRESULT e)
	{
		g_debug << "Failed to load mesh from X -- " << fName << "\n";
		return E_FAIL;
	}

	D3DXMATERIAL *mtrls = (D3DXMATERIAL*)materialBfr->GetBufferPointer();

	for(int i=0;i<(int)noMaterials;i++)
	{
		m_materials.push_back(mtrls[i].MatD3D);

		//Load textures for each material
		if(mtrls[i].pTextureFilename != NULL)
		{	
			std::ostringstream oss;
			oss << PATH_TO_MESHES << mtrls[i].pTextureFilename;
			std::string textureFileName = oss.str();
			IDirect3DTexture9 * newTexture = NULL;
			D3DXCreateTextureFromFileA(g_pDevice, (LPCSTR)textureFileName.c_str(), &newTexture);			
			m_textures.push_back(newTexture);
		}
		else m_textures.push_back(NULL);
	}

	m_pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
							(DWORD*)adjacencyBfr->GetBufferPointer(), NULL, NULL, NULL);

	adjacencyBfr->Release();
	materialBfr->Release();

	return S_OK;
}

void Mesh::Render()
{
	int numMaterials = (int)m_materials.size();

	for(int i=0;i<numMaterials;i++)
	{	
		//Set material
		if(m_textures[i] != NULL)
			g_pDevice->SetMaterial(&m_white);
		else g_pDevice->SetMaterial(&m_materials[i]);

		//Set Texture
		g_pDevice->SetTexture(0, m_textures[i]);

		//Render mesh
		m_pMesh->DrawSubset(i);
	}	
}

void Mesh::Release()
{
	//Clear old mesh...
	if(m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//Clear textures and materials
	int numTextures = (int)m_textures.size();

	for(int i=0;i<numTextures;i++)
		if(m_textures[i] != NULL)
			m_textures[i]->Release();

	m_textures.clear();
	m_materials.clear();	
}