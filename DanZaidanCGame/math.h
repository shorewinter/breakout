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


static int clamp(int min, int val, int max) {
	if(val < min) return min;
	if(val > max) return max;
	return val;
}


static v2 V2(float x, float y) {
	v2 result;
	result.x = x;
	result.y = y;
	return result;
}

static v2 v2Add(v2 a, v2 b) {
	return (v2){a.x + b.x, a.y + b.y};
}

static v2 v2Mul(v2 a, float b) {
	return (v2){ a.x * b, a.y * b};
}