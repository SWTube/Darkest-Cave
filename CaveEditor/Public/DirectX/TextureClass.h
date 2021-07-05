#pragma once

class TextureClass
{
public:
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();

	bool Initialize(ID3D11Device*, WCHAR*);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

protected:
	XMFLOAT2 mStartUV = XMFLOAT2(0.0f, 0.0f);
	XMFLOAT2 mEndUV = XMFLOAT2(0.0f, 0.0f);

private:
	ID3D11ShaderResourceView* m_texture = nullptr;

public:
	XMFLOAT2 GetStartUV() const{
		return mStartUV;
	}
	XMFLOAT2 GetEndUV() const {
		return mEndUV;
	}
};