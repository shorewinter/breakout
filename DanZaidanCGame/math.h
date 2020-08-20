static int clamp(int min, int val, int max) {
	if(val < min) return min;
	if(val > max) return max;
	return val;
}

struct {
	union {
		struct {
			float x;
			float y;
		};
		float e[2];
	};
} typedef v2;

struct {
	union {
		struct {
			int x;
			int y;
		};
		int e[2];
	};
} typedef v2i;