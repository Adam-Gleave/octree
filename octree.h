#ifndef OCTREE_H
#define OCTREE_H

#include <assert.h>

template <class T>
class Octree
{
protected:
	struct Pos
	{
		int x;
		int y;
		int z;
	
		Pos(const Pos& pos2) : x(pos2.x), y(pos2.y), z(pos2.z) {}
		Pos(const int in_x, const int in_y, const int in_z) : x(in_x), y(in_y), z(in_z) {}
		Pos(const int pt[3]) : x(pt[0]), y(pt[1]), z(pt[2]) {}
		Pos operator+(const Pos& pos2) { return Pos(x + pos2.x, y + pos2.y, z + pos2.z); }
		Pos operator-(const Pos& pos2) { return Pos(x - pos2.x, y - pos2.y, z - pos2.z); }
		Pos operator*(const Pos& pos2) { return Pos(x * pos2.x, y * pos2.y, z * pos2.y); }
		Pos operator/(const Pos& pos2) { return Pos(x / pos2.x, y / pos2.y, z / pos2.z); }
		bool operator<(const Pos& pos2) { return x < pos2.x && y < pos2.y && z < pos2.z; }
		bool operator>(const Pos& pos2) { return x > pos2.x && y > pos2.y && z > pos2.z; }
		bool operator<=(const Pos& pos2) { return x <= pos2.x && y <= pos2.y && z <= pos2.z; }
		bool operator>=(const Pos& pos2) { return x >= pos2.x && y >= pos2.y && z >= pos2.z; }
		bool operator==(const Pos& pos2) { return x == pos2.x && y == pos2.y && z == pos2.z; }
		bool operator!=(const Pos& pos2) { return x != pos2.z || y != pos2.y || z != pos2.z; }
	};

	struct OctreeNode
	{
		OctreeNode()
		{
			for (int i = 0; i < 8; i++)
			{
				_children[i] = 0;
			}
		}

		virtual ~OctreeNode()
		{
			for (int i = 0; i < 8; i++)
			{
				if (children[i])
				{
					delete _children[i];
				}
			}
		}

		T _data;
		OctreeNode* _children[8];
	};

	OctreeNode* _rootNode;
	Pos _min;
	Pos _max;
	Pos _minSize;

public:
	Octree(int dim, int cellDim = 1) : _min(0, 0, 0), _max(dim, dim, dim), _minSize(cellDim, cellDim, cellDim) {}
	virtual ~Octree() { delete _rootNode; }

	const T at(int x, int y, int z)
	{
		Pos inPos(x, y, z);
		assert(inPos >= min && inPos < max);
		Pos nodeMin(_min);
		Pos nodeMax(_max);
		Pos nodeSize = _max - _min;

		if (!_rootNode)
		{
			return 0;
		}

		while (nodeSize >= _minSize)
		{
			//TODO
		}
	}
};

#endif //OCTREE_H