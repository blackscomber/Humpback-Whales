//////////////////////////////////////////////////////////////
// Mesh														//
// Written by: Claire Lee, 2012								//
// Description : Mesh class is to load and render meshes    //
//////////////////////////////////////////////////////////////

#pragma once

#include <d3dx9.h>
#include <vector>

using namespace std;

class Mesh
{
	public:
		Mesh();
		Mesh(const string & fName);
		virtual ~Mesh();
		HRESULT LoadMeshFromX(const string & fName);
		void Render();
		void Release();

	private:

		ID3DXMesh *m_pMesh;
		vector<IDirect3DTexture9*> m_textures;
		vector<D3DMATERIAL9> m_materials;
		D3DMATERIAL9 m_white;
};
