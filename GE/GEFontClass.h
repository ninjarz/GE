#ifndef _GEFONTCLASS_H_
#define _GEFONTCLASS_H_

#include <d3d11.h>
#include <d3dx11async.h>
#include "GEmath.h"
#include "GEManageClass.h"

//-----------------------------------------------------------------------
namespace GE
{
	struct FontData
	{
		float left, right;
		int size;
	};

	struct FontVertex
	{
		FLOAT3 pos;
		FLOAT2 tex;
	};

	struct FontBuffer
	{
		FLOAT4 fontColor;
	};

	class FontClass : public GEClass
	{
	public:
		inline FontClass()
		{
		}

		inline FontClass(const FontClass&)
		{
		}

		inline ~FontClass()
		{
		}

		bool Initialize();
		void Shutdown();

		bool SetFontParameters(const FLOAT4& _fontColor);

		bool Print(FLOAT _posX, FLOAT _posY, const FLOAT4& _color, const char* _info);
		bool Printv(FLOAT _posX, FLOAT _posY, const FLOAT4& _color, const char* _info, ...);

	private:
		bool LoadFontData();

	private:
		FontData *m_fontData;

		ID3D11Buffer *m_fontBuffer;

		ID3D11ShaderResourceView *m_fontTex;

		ID3D11VertexShader *m_fontVS;
		ID3D11PixelShader  *m_fontPS;

		ID3D11InputLayout *m_fontIL;
	};

	extern FontClass *g_fontClass;

	bool GEPrint(FLOAT _posX, FLOAT _posY, const FLOAT4& _color, const char* _info);
}


#endif