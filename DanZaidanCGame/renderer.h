static void clearScreen(uint32_t color) {
	uint32_t *pixel = renderBuffer.pixels;
	for(int y = 0; y < renderBuffer.height; ++y) {
		for(int x = 0; x < renderBuffer.width; ++x){
			*pixel++ = color;
		}
	}	
}

static void rectangle(int x1, int y1, int x2, int y2, uint32_t color) {
	x1 = clamp(0, x1, renderBuffer.width);
	x2 = clamp(0, x2, renderBuffer.width);
	y1 = clamp(0, y1, renderBuffer.height);
	y2 = clamp(0, y2, renderBuffer.height);
	
	for(int y = y1; y < y2; y++) {
		uint32_t *pixel = renderBuffer.pixels + x1 + renderBuffer.width * y;
		for(int x = x1; x < x2; x++){
			*pixel++ = color;
		}
	}	
}

static void drawRect(v2 p, v2 half_size, uint32_t color) {
	float scale = 0.01f;
	// aspect ratio idependent
	float aspectRatio = (float) renderBuffer.height;
	if ((float)renderBuffer.width / (float)renderBuffer.height < 1.77f) {
		aspectRatio = (float)(renderBuffer.width / 1.77f);
	}
	half_size.x *= (float)aspectRatio * scale;
	half_size.y *= (float)aspectRatio * scale;
	p.x *= aspectRatio * scale;
	p.y *= aspectRatio * scale;

	// change 0, 0 to center
	p.x += (float) renderBuffer.width * 0.5f;
	p.y += (float) renderBuffer.height * 0.5f;

	int x1 = (int)(p.x - half_size.x);
	int y1 = (int)(p.y - half_size.y);
	int x2 = (int)(p.x + half_size.x);
	int y2 = (int)(p.y + half_size.y);

	rectangle(x1, y1, x2, y2, color);
}