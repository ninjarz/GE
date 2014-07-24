#pragma once
#ifndef _GEMAZECLASS_H_
#define _GEMAZECLASS_H_

#include <iostream>
#include <ctime>

#include "GEMath.h"

//-----------------------------------------------------------------------
namespace GE
{
	enum PosType
	{
		POS_UNINIT = -1,
		POS_WALL = 0,
		POS_FRAME,
		POS_ENTER,
		POS_EXIT,
		POS_WAY,
		POS_OLDWAY,
		POS_PATH,
	};

	class MazeClass
	{
	public:
		inline MazeClass(int _width, int _height) : m_width(_width), m_height(_height)
		{
			m_maze = new PosType* [m_width];
			for(int i = 0; i < m_height; ++i)
			{
				m_maze[i] = new PosType [m_height];
			}

			Initialize();
		}

		inline ~MazeClass()
		{
			if(m_maze)
			{
				for(int i = 0; i < m_height; ++i)
				{
					delete[] m_maze[i];
				}
				delete[] m_maze;
				m_maze = NULL;
			}
		}

		bool Initialize();
		void Shutdown();

		inline int GetWidth() const { return m_width; }
		inline int GetHeight() const { return m_height; }
		inline PosType** GetMaze() const { return m_maze; }

	private:
		void CreateMaze(const INT2 &_int2);

	private:
		PosType **m_maze;
		int m_width;
		int m_height;
	};
}


#endif