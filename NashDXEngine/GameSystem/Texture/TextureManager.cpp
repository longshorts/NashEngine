////////////////////////////////////////////////////////////////////////////////
// Filename: TextureManager.cpp
////////////////////////////////////////////////////////////////////////////////
#include "TextureManager.h"

TextureManager* TextureManager::instance;

TextureManager::TextureManager()
{
	if (instance) {
		delete this;
	}
	else instance = this;

	m_TextureArray = 0;
}


TextureManager::TextureManager(const TextureManager& other)
{
}


TextureManager::~TextureManager()
{
}


bool TextureManager::Initialize(int count)
{
	m_textureCount = count;

	// Create the color texture object.
	m_TextureArray = new Texture[m_textureCount];
	if (!m_TextureArray)
	{
		return false;
	}

	return true;
}


void TextureManager::Shutdown()
{
	int i;


	// Release the texture objects.
	if (m_TextureArray)
	{
		for (i = 0; i<m_textureCount; i++)
		{
			m_TextureArray[i].Shutdown();
		}
		delete[] m_TextureArray;
		m_TextureArray = 0;
	}

	return;
}


bool TextureManager::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename, int location)
{
	bool result;


	// Initialize the color texture object.
	result = m_TextureArray[location].Initialize(device, deviceContext, filename);
	if (!result)
	{
		return false;
	}

	return true;
}


ID3D11ShaderResourceView* TextureManager::GetTexture(int id)
{
	return m_TextureArray[id].GetTexture();
}