#pragma once
#ifndef _GEGUICLASS_H_
#define _GEGUICLASS_H_

#include "GEManageClass.h"

#include <vector>

namespace GE
{
	enum GUIControlType
	{
		GUI_BUTTON = 1,
	};

	struct GUIControl
	{
		//type
		int m_type;
		//id
		int m_id;
		//position
		int m_xPos, m_yPos;
		int m_width, m_height;

		//control picture
		ID3D11ShaderResourceView *m_upTex, *m_downTex, *m_overTex;
	};

	struct GUIScene
	{
		//id
		int m_id;
		//background texture
		ID3D11ShaderResourceView *m_BGTex;

		//controls
		std::vector<GUIControl> m_control;
	};

	class GUIClass : public GEClass
	{
	private:
		//scenes
		std::vector<GUIScene> m_scene;
	};
}

#endif