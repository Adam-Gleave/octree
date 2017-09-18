#include <list>
using namespace std;

template <typename T> class Octree {
public:
	//Initialiser to be called when creating a top-level tree
	Octree(int dimension) { 
		//All octrees must have dimensions of powers of 2
		if (dimension & (dimension - 1) != 0 || dimension <= 0) {
			throw new exception("Must initialise with a positive power of 2.");
			return 0;
		}
		else {
			_maxDimension = dimension;
			_currentDimension = dimension;

			//Point each child to null for easy comparisons
			for each (Octree *child in children) {
				child = nullptr;
			}
		}
	}
	
	//Recursively delete all children that are not nullptr
	~Octree() {
		for each (Octree *child in children) {
			if (child) {
				delete child;
			}
		}
	};

	//Recursively insert a new node by identifying the octant of each child
	//until a leaf node (currentDepth == maxDepth) is reached
	void insertNode(int x, int y, int z, T state) {
		//Determine if a node coordinate is valid
		if (x >= _maxDimension || y >= _maxDimension || z >= _maxDimension) {
			throw new exception("Node does not fit in tree.");
			return 0;
		}
		//If a new node needs to be inserted to reach the intended location, do so
		else if (_currentDepth != _maxDepth) {
			//Octant 0
			if (x < _currentDimension / 2 && y < _currentDimension / 2 
				&& z < _currentDimension / 2) {
				if (!_children[0]) {
					_children[0] = Octree<T>(this);
				}

				_children[0]->insertNode(x, y, z, state);
			}
			//Octant 1
			else if (x >= _currentDimension / 2 && y < _currentDimension / 2
				&& z < _currentDimension / 2) {
				if (!_children[1]) {
					_children[1] = Octree<T>(this);
				}

				_children[1]->insertNode(x, y, z, state);
			}
			//Octant 2
			else if (x >= _currentDimension / 2 && y < _currentDimension / 2
				&& z >= _currentDimension / 2) {
				if (!_children[2]) {
					_children[2] = Octree<T>(this);
				}

				_children[2]->insertNode(x, y, z, state);
			}
			//Octant 3
			else if (x < _currentDimension / 2 && y < _currentDimension / 2
				&& z >= _currentDimension / 2) {
				if (!children[3]) {
					_children[3] = Octree<T>(this);
				}

				_children[3]->insertNode(x, y, z, state);
			}
			//Octant 4
			if (x < _currentDimension / 2 && y >= _currentDimension / 2
				&& z < _currentDimension / 2) {
				if (!_children[4]) {
					_children[4] = Octree<T>(this);
				}

				_children[4]->insertNode(x, y, z, state);
			}
			//Octant 5
			else if (x >= _currentDimension / 2 && y >= _currentDimension / 2
				&& z < _currentDimension / 2) {
				if (!_children[5]) {
					_children[5] = Octree<T>(this);
				}

				_children[5]->insertNode(x, y, z, state);
			}
			//Octant 6
			else if (x >= _currentDimension / 2 && y >= _currentDimension / 2
				&& z >= _currentDimension / 2) {
				if (!_children[6]) {
					_children[6] = Octree<T>(this);
				}

				_children[6]->insertNode(x, y, z, state);
			}
			//Octant 7
			else if (x < _currentDimension / 2 && y >= _currentDimension / 2
				&& z >= _currentDimension / 2) {
				if (!children[7]) {
					_children[7] = Octree<T>(this);
				}

				_children[7]->insertNode(x, y, z, state);
			}
		}
		//Once the leaf node has been reached or made, set its state
		else {
			_state = state;
			return;
		}
	}

	uint8_t getDimension() { return _currentDimension; };
	Octree *getParent() { return _parent };

	//Value held by octree node (can take any primitive type)
	T _state = 0;

private:
	//Alternative constructor for creating child nodes
	//Only to be called by an Octree object
	Octree(Octree *parent) {
		_currentDimension = parent->getDimension() / 2;
		_parent = parent;

		for each (Octree *child in children) {
			child = nullptr;
		}
	}

	uint8_t _maxDimension;				//Max dimension of the octree		
	uint8_t _currentDimension;			//Dimension of current node
	const uint8_t MIN_SIZE = 1;			//Discrete minimum size (in units) of a leaf node
	Octree *children[8];				//Array of child octrees (nonexistent children are nullptr)				
	Octree *parent = nullptr;			//Parent octree of current octree
};