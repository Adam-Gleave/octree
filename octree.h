#include <stdexcept>

template <typename T> class Octree {
public:
	//Initialiser to be called when creating a top-level tree
	Octree(int dimension, int minSize) { 
		//All octrees must have dimensions of powers of 2
		//Bitwise operation determines powers of 2
		if (dimension & (dimension - 1) != 0 || dimension <= 0) {
			throw new std::exception("Must initialise with a positive power of 2.");
		}
		if (minSize != 1 || minSize & (minSize - 1) != 0 || minSize <= 0 || minSize > dimension) {
			throw new std::exception("Minimum node size must be a positive power of two <= octree dimension.");
		}
		else {
			_minSize = minSize;
			_currentDepth = 1;
			_maxDimension = dimension;

			//Point each child to null for easy comparisons
			for each (Octree *child in _children) {
				child = nullptr;
			}
		}
	}
	
	//Recursively delete all children that are not nullptr
	~Octree() {
		for each (Octree *child in _children) {
			if (child) {
				delete child;
			}
		}
	};

	//Recursively insert a new node, or a new node state, identifying the octant of each child
	//until a leaf node (currentDepth == maxDepth) is reached
	void setState(int x, int y, int z, T state) {
		//Determine if a node coordinate is valid
		if (x >= _maxDimension || y >= _maxDimension || z >= _maxDimension) {
			throw new std::out_of_range("Node does not fit in tree.");
		}

		//If a new node needs to be inserted to reach the intended location, do so
		if (this->getDimension() > _minSize) {		
			//Octant 0
			if (x  < this->getDimension() / 2 && y  < this->getDimension() / 2 
				&& z < this->getDimension() / 2) {
				if (!_children[0]) {
					_children[0] = new Octree<T>(this);
				}

				_children[0]->setState(x, y, z, state);
			}
			//Octant 1
			else if (x >= this->getDimension() / 2 && y < this->getDimension() / 2
				&& z < this->getDimension() / 2) {
				if (!_children[1]) {
					_children[1] = new Octree<T>(this);
				}

				//Coordinates to pass into next recursion level (coords in next octree)
				//Retrieved by taking off half of the current dimension from the current coords
				x -= this->getDimension() / 2;
				_children[1]->setState(x, y, z, state);
			}
			//Octant 2
			else if (x >= this->getDimension() / 2 && y < this->getDimension() / 2
				&& z >= this->getDimension() / 2) {
				if (!_children[2]) {
					_children[2] = new Octree<T>(this);
				}

				x -= this->getDimension() / 2;
				z -= this->getDimension() / 2;
				_children[2]->setState(x, y, z, state);
			}
			//Octant 3
			else if (x < this->getDimension() / 2 && y < this->getDimension() / 2
				&& z >= this->getDimension() / 2) {
				if (!_children[3]) {
					_children[3] = new Octree<T>(this);
				}

				z -= this->getDimension() / 2;
				_children[3]->setState(x, y, z, state);
			}
			//Octant 4
			if (x < this->getDimension() / 2 && y >= this->getDimension() / 2
				&& z < this->getDimension() / 2) {
				if (!_children[4]) {
					_children[4] = new Octree<T>(this);
				}

				y -= this->getDimension() / 2;
				_children[4]->setState(x, y, z, state);
			}
			//Octant 5
			else if (x >= this->getDimension() / 2 && y >= this->getDimension() / 2
				&& z < this->getDimension() / 2) {
				if (!_children[5]) {
					_children[5] = new Octree<T>(this);
				}

				x -= this->getDimension() / 2;
				y -= this->getDimension() / 2;
				_children[5]->setState(x, y, z, state);
			}
			//Octant 6
			else if (x >= this->getDimension() / 2 && y >= this->getDimension() / 2
				&& z >= this->getDimension() / 2) {
				if (!_children[6]) {
					_children[6] = new Octree<T>(this);
				}

				x -= this->getDimension() / 2;
				y -= this->getDimension() / 2;
				z -= this->getDimension() / 2;
				_children[6]->setState(x, y, z, state);
			}
			//Octant 7
			else if (x < this->getDimension() / 2 && y >= this->getDimension() / 2
				&& z >= this->getDimension() / 2) {
				if (!_children[7]) {
					_children[7] = new Octree<T>(this);
				}

				y -= this->getDimension() / 2;
				z -= this->getDimension() / 2;
				_children[7]->setState(x, y, z, state);
			}
		}
		//Once the leaf node has been reached or made, set its state
		else {
			_state = state;
		}

		tryRefactor();
	}

	//Retrieve the state of a particular octree node
	//Causes an exception if the node does not exist, since we cannot know the type of the state member
	const T getState(int x, int y, int z) {
		//Determine if a node coordinate is valid
		if (x >= _maxDimension || y >= _maxDimension || z >= _maxDimension) {
			throw new std::out_of_range("Node does not fit in tree.");
		}

		//Return state of current node if specified node does not exist
		//Since a full octree is deleted and replaced with a node of the correct state
		if (this->getDimension() > _minSize) {
			//Octant 0
			if (x < this->getDimension() / 2 && y < this->getDimension() / 2
				&& z < this->getDimension() / 2) {
				if (!_children[0]) {
					return _state;
				}

				return _children[0]->getState(x, y, z);
			}
			//Octant 1
			else if (x >= this->getDimension() / 2 && y < this->getDimension() / 2
				&& z < this->getDimension() / 2) {
				if (!_children[1]) {
					return _state;
				}

				x -= this->getDimension() / 2;
				return _children[1]->getState(x, y, z);
			}
			//Octant 2
			else if (x >= this->getDimension() / 2 && y < this->getDimension() / 2
				&& z >= this->getDimension() / 2) {
				if (!_children[2]) {
					return _state;
				}

				x -= this->getDimension() / 2;
				z -= this->getDimension() / 2;
				return _children[2]->getState(x, y, z);
			}
			//Octant 3
			else if (x < this->getDimension() / 2 && y < this->getDimension() / 2
				&& z >= this->getDimension() / 2) {
				if (!_children[3]) {
					return _state;
				}

				z -= this->getDimension() / 2;
				return _children[3]->getState(x, y, z);
			}
			//Octant 4
			if (x < this->getDimension() / 2 && y >= this->getDimension() / 2
				&& z < this->getDimension() / 2) {
				if (!_children[4]) {
					return _state;
				}

				y -= this->getDimension() / 2;
				return _children[4]->getState(x, y, z);
			}
			//Octant 5
			else if (x >= this->getDimension() / 2 && y >= this->getDimension() / 2
				&& z < this->getDimension() / 2) {
				if (!_children[5]) {
					return _state;
				}

				x -= this->getDimension() / 2;
				y -= this->getDimension() / 2;
				return _children[5]->getState(x, y, z);
			}
			//Octant 6
			else if (x >= this->getDimension() / 2 && y >= this->getDimension() / 2
				&& z >= this->getDimension() / 2) {
				if (!_children[6]) {
					return _state;
				}

				x -= this->getDimension() / 2;
				y -= this->getDimension() / 2;
				z -= this->getDimension() / 2;
				return _children[6]->getState(x, y, z);
			}
			//Octant 7
			else if (x < this->getDimension() / 2 && y >= this->getDimension() / 2
				&& z >= this->getDimension() / 2) {
				if (!_children[7]) {
					return _state;
				}

				y -= this->getDimension() / 2;
				z -= this->getDimension() / 2;
				return _children[7]->getState(x, y, z);
			}
		}
		//Reached a leaf node
		else {
			return _state;
		}
	}

	const uint8_t getDepth() { return _currentDepth; };
	
	const uint8_t getDimension() {
		if (_currentDepth == 1) {
			return _maxDimension;
		}

		return _maxDimension / pow(2, _currentDepth - 1);
	};

	const uint8_t getMaxDimension() { return _maxDimension; };
	const uint8_t getMinSize() { return _minSize; };
	Octree *getParent() { return _parent };
	Octree *getChild(int index) { return _children[index]; };

	//Value held by octree node (can take any primitive type)
	//Public, so that it can be accessed by parent nodes
	T _state = 0;

private:
	//Alternative constructor for creating child nodes
	//Only to be called by an Octree object
	Octree(Octree *parent) {
		_minSize = parent->getMinSize();
		_currentDepth = parent->getDepth() + 1;
		_maxDimension = parent->getMaxDimension();
		_parent = parent;

		for each (Octree *child in _children) {
			child = nullptr;
		}
	}

	//After returning from each stage of recursion, check if all child states are identical
	//Allows for dynamic memory deallocation
	void tryRefactor() {
		if (_children[0]) {
			T state = _children[0]->_state;
			bool canOptimise = true;
			bool isFull = true;

			for each (Octree *child in _children) {
				if (!child) {
					isFull = false;

				}
				else {
					if (child->_state != state) {
						canOptimise = false;
					}
				}

				if (!isFull || !canOptimise) {
					break;
				}
			}

			//If they are, change the state of the current node to that state, and point children to null
			//This dynamically frees memory where it can be optimised
			if (canOptimise && isFull) {
				_state = state;

				for (int i = 0; i < 8; ++i) {
					_children[i] = nullptr;
				}
			}
		}
	}

	uint8_t _minSize;					//Discrete minimum size (in units) of a leaf node
	uint8_t _currentDepth;				//Depth of current node
	uint8_t _maxDimension;				//Max dimension of the octree		
	Octree *_children[8];				//Array of child octrees (nonexistent children are nullptr)				
	Octree *_parent = nullptr;			//Parent octree of current octree
};