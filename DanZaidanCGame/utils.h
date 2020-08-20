#pragma once

static int running = 1;

struct {
	int width;
	int height;
	uint32_t *pixels;
	BITMAPINFO bitmapInfo;
} typedef RENDERBUFFER;

static RENDERBUFFER renderBuffer;