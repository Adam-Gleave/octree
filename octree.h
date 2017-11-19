#ifndef OCTREE_H
#define OCTREE_H

#include <assert.h>
#include <octreepos.h>

template <class T>
class Octree
{
protected:
	// Node data structure
	struct OctreeNode
	{
		// Create a new node with null children
		OctreeNode()
		{
			for (int i = 0; i < 8; i++)
			{
				_children[i] = 0;
			}
		}
		// If children exist, recursively delete all children
		virtual ~OctreeNode()
		{
			// All or no children exist - only the first needs to be checked
			if (children[0])
			{
				delete[] _children;
			}
		}
		
		// Insert data into node
		void insert(T data)
		{
			*_data = data;
		}
		void insert(T* data)
		{
			_data = data;
		}

		T* _data = nullptr;				// Data stored in node
		OctreeNode* _children[8];		// Array of child nodes
	};

	OctreeNode* _rootNode;		// Root node of octree, contains all other nodes
	OctreePos _min;				// Minimum position of any node in octree
	OctreePos _max;				// Maximum position of any node in octree
	OctreePos _minSize;			// Minimum dimension of any node in octree

public:
	// Initialise octree with a dimension and the smallest cell dimension
	Octree(const int dim, const int cellDim = 1) : _min(0, 0, 0), 
		_max(dim, dim, dim), _minSize(cellDim, cellDim, cellDim) {}
	// Recursively delete all nodes in octree
	virtual ~Octree() 
	{ 
		delete _rootNode; 
	}
	
	// Retrieve the octree node at specified position
	OctreeNode* at(const OctreePos searchPos)
	{
		
	}
	// Helpful function overloading
	OctreeNode* at(const int x, const int y, const int z)
	{
		OctreePos searchPos = OctreePos(x, y, z);
	}
	OctreeNode* at(const int pos[3])
	{
		OctreePos searchPos = OctreePos(pos);
	}
	
	// Check for leaf node (the extremity of the octree)
	bool isLeafNode(OctreeNode* node)
	{
		return node->_children[0] == 0;
	}
	
	void clear()
	{
		delete _rootNode;
		_rootNode = 0;
	}
};

#endif //OCTREE_H