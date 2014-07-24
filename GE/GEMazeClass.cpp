#include "GEMazeClass.h"

namespace GE
{
	//-----------------------------------------------------------------------
	bool MazeClass::Initialize()
	{
		for(int x = 0; x < m_width; ++x)
		{
			m_maze[x][0] = m_maze[x][m_height - 1] = POS_FRAME;
		}
		for(int y = 0; y < m_height; ++y)
		{
			m_maze[0][y] = m_maze[m_width - 1][y] = POS_FRAME;
		}
		for(int x = 1; x < m_width-1; ++x)
		{
			for(int y = 1; y < m_height-1; ++y)
			{
				m_maze[x][y] = POS_WALL;
			}
		}

		srand((unsigned int)time(NULL));
		INT2 pos(rand()%(m_width>>1)+(m_width>>2), rand()%(m_height>>1)+(m_height>>2));
		m_maze[pos.x][pos.y] = POS_WAY;
		CreateMaze(pos);

		INT2 enter(0, 1);
		INT2 exit(m_width - 1, m_height - 2);
		m_maze[enter.x][enter.y] = POS_ENTER;
		m_maze[exit.x][exit.y] = POS_EXIT;
		INT2 tmp = enter;
		int i = 1;
		for(; i < m_width - 1; ++i)
		{
			INT2 right = tmp;
			right.x += 1;
			if(m_maze[right.x][right.y] == POS_WALL)
			{
				m_maze[right.x][right.y] = POS_WAY;
				INT2 down = right;
				down.y += 1;
				if(m_maze[down.x][down.y] == POS_WALL)
				{
					tmp = right;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
		tmp = exit;
		for(; i < m_width - 1; ++i)
		{
			INT2 left = tmp;
			left.x -= 1;
			if(m_maze[left.x][left.y] == POS_WALL)
			{
				m_maze[left.x][left.y] = POS_WAY;
				INT2 up = left;
				up.x -= 1;
				if(m_maze[up.x][up.y] == POS_WALL)
				{
					tmp = left;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}

		return true;
	}

	//-----------------------------------------------------------------------
	void MazeClass::Shutdown()
	{
	}

	//-----------------------------------------------------------------------
	void MazeClass::CreateMaze(const INT2 &_int2)
	{
		int dir[4] = {-1};
		for(int i = 0; i < 4; ++i)
		{
			dir[i] = rand()%4;
			for(int j = 0; j < i; ++j)
			{
				if (dir[j] == dir[i])
				{
					--i;
					break;
				}
			}
		}

		for(int i = 0; i < 4; ++i)
		{
			INT2 pos = _int2;
			switch(dir[i])
			{
			case 0:
				pos.x -= 1;
				if(m_maze[pos.x][pos.y] != POS_WALL)
					break;
				if((m_maze[pos.x - 1][pos.y] == POS_WALL || m_maze[pos.x - 1][pos.y] == POS_FRAME) &&
					(m_maze[pos.x][pos.y + 1] == POS_WALL || m_maze[pos.x][pos.y + 1] == POS_FRAME) &&
					(m_maze[pos.x][pos.y - 1] == POS_WALL || m_maze[pos.x][pos.y - 1] == POS_FRAME))
				{
					m_maze[pos.x][pos.y] = POS_WAY;
					CreateMaze(pos);
				}
				break;
			case 1:
				pos.x += 1;
				if(m_maze[pos.x][pos.y] != POS_WALL)
					break;
				if((m_maze[pos.x + 1][pos.y] == POS_WALL || m_maze[pos.x + 1][pos.y] == POS_FRAME) &&
					(m_maze[pos.x][pos.y + 1] == POS_WALL || m_maze[pos.x][pos.y + 1] == POS_FRAME) &&
					(m_maze[pos.x][pos.y - 1] == POS_WALL || m_maze[pos.x][pos.y - 1] == POS_FRAME))
				{
					m_maze[pos.x][pos.y] = POS_WAY;
					CreateMaze(pos);
				}
				break;
			case 2:
				pos.y += 1;
				if(m_maze[pos.x][pos.y] != POS_WALL)
					break;
				if((m_maze[pos.x + 1][pos.y] == POS_WALL || m_maze[pos.x + 1][pos.y] == POS_FRAME) &&
					(m_maze[pos.x - 1][pos.y] == POS_WALL || m_maze[pos.x - 1][pos.y] == POS_FRAME) &&
					(m_maze[pos.x][pos.y + 1] == POS_WALL || m_maze[pos.x][pos.y + 1] == POS_FRAME))
				{
					m_maze[pos.x][pos.y] = POS_WAY;
					CreateMaze(pos);
				}
				break;
			case 3:
				pos.y -= 1;
				if(m_maze[pos.x][pos.y] != POS_WALL)
					break;
				if((m_maze[pos.x + 1][pos.y] == POS_WALL || m_maze[pos.x + 1][pos.y] == POS_FRAME) &&
					(m_maze[pos.x - 1][pos.y] == POS_WALL || m_maze[pos.x - 1][pos.y] == POS_FRAME) &&
					(m_maze[pos.x][pos.y - 1] == POS_WALL || m_maze[pos.x][pos.y - 1] == POS_FRAME))
				{
					m_maze[pos.x][pos.y] = POS_WAY;
					CreateMaze(pos);
				}
				break;
			default:
				break;
			}
		}
	}
}