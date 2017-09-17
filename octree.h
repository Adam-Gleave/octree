#include <list>
#include "octreenode.h"
using namespace std;

class Octree {
public:
	Octree(int dimension) { 
		if (dimension & (dimension - 1) != 0 || dimension <= 0) {
			throw new exception("Must initialise with a positive power of 2.");
		}
		else {
			MAX_DEPTH = log2(dimension);
			
			for each (int i in _dimensions) {
				_dimensions[i] = dimension;
			}

			for each (OctreeNode *child in children) {
				child = nullptr;
			}
		}
	}
	
	~Octree() {
		for each (OctreeNode *child in children) {
			delete child;
		}
	};

	OctreeNode *children[8];

private:
	int _dimensions[3]; 	//x, y and z co-ordinates of bounding box (units)
	int MAX_DEPTH;
	const int MIN_SIZE = 1; //Discrete minimum size (in units) of a leaf node
};