v2 playerPos;
static void simulateGame(Input *input, float dt) {
	float speed = 100;
	clearScreen(0x191919);
	if(isDown(BUTTON_LEFT)) playerPos.x -= speed * dt;
	if(isDown(BUTTON_RIGHT)) playerPos.x += speed * dt;
	if(isDown(BUTTON_UP)) playerPos.y += speed * dt;
	if(isDown(BUTTON_DOWN)) playerPos.y -= speed * dt;
	drawRect(playerPos, (v2){1, 1}, 0xefefef);
}