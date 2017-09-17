class OctreeNode {
public:
	OctreeNode() {
		for each (OctreeNode *child in children) {
			child = nullptr;
		}
	};
	~OctreeNode() {
		for (int i = 0; i < 8; i++) {
			if (children[i]) {
				delete children[i];
			}
		}
	};

	OctreeNode *children[8];
};
