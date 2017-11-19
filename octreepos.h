#ifndef OCTREEPOS_H
#define OCTREEPOS_H

// Data structure for indicating position within the octree
struct OctreePos
{
	int x;
	int y;
	int z;

	OctreePos(const OctreePos& pos2) : x(pos2.x), y(pos2.y), z(pos2.z) {}
	OctreePos(const int in_x, const int in_y, const int in_z) : x(in_x), y(in_y), z(in_z) {}
	OctreePos(const int pt[3]) : x(pt[0]), y(pt[1]), z(pt[2]) {}
	
	// Mathematical operators
	OctreePos operator+(const OctreePos& pos2) 
	{ 
		return OctreePos(x + pos2.x, y + pos2.y, z + pos2.z); 
	}
	OctreePos operator-(const OctreePos& pos2) 
	{ 
		return OctreePos(x - pos2.x, y - pos2.y, z - pos2.z); 
	}
	OctreePos operator*(const OctreePos& pos2) 
	{ 
		return OctreePos(x * pos2.x, y * pos2.y, z * pos2.y); 
	}	
	OctreePos operator/(const OctreePos& pos2) 
	{ 
		return OctreePos(x / pos2.x, y / pos2.y, z / pos2.z); 
	}
	
	// Comparison operators
	bool operator<(const OctreePos& pos2) 
	{ 
		return x < pos2.x && y < pos2.y && z < pos2.z; 
	}	
	bool operator>(const OctreePos& pos2) 
	{ 
		return x > pos2.x && y > pos2.y && z > pos2.z; 
	}	
	bool operator<=(const OctreePos& pos2) 
	{ 
		return x <= pos2.x && y <= pos2.y && z <= pos2.z; 
	}	
	bool operator>=(const OctreePos& pos2) 
	{ 
		return x >= pos2.x && y >= pos2.y && z >= pos2.z; 
	}	
	bool operator==(const OctreePos& pos2) 
	{ 
		return x == pos2.x && y == pos2.y && z == pos2.z; 
	}	
	bool operator!=(const OctreePos& pos2) 
	{ 
		return x != pos2.z || y != pos2.y || z != pos2.z; 
	}
};

#endif //OCTREEPOS_H