v2 playerPos;
v2 playerVel;
v2 playerSizeHalf;
v2 ballPos;
v2 ballVel;
v2 ballSizeHalf;
v2 arenaSizeHalf;
static int init = 0;

static void simulateGame(Input *input, float dt) {
	if(!init) {
		init = 1;
		ballVel.y = -20;
		ballPos.y = 40;
		ballSizeHalf = (v2){1, 1};
		playerPos.y = -40;
		playerSizeHalf = (v2){20, 1};
		arenaSizeHalf = (v2){80, 45};
	}
	
	//float speed = 100;
	//if(isDown(BUTTON_LEFT)) playerPos.x -= speed * dt;
	//if(isDown(BUTTON_RIGHT)) playerPos.x += speed * dt;
	//if(isDown(BUTTON_UP)) playerPos.y += speed * dt;
	//if(isDown(BUTTON_DOWN)) playerPos.y -= speed * dt;

	float playerNewX = pixelsToWorld(input->mouse).x;
	playerVel.x = (playerNewX - playerPos.x) / dt;
	playerPos.x = playerNewX;
	ballPos = v2Add(ballPos, v2Mul(ballVel, dt));
	if(ballVel.y < 0 && intersect(playerPos, playerSizeHalf, ballPos, ballSizeHalf)) {
		ballVel.y *= -1;
		ballVel.x += playerVel.x;
	} else if(ballPos.x + ballSizeHalf.x > arenaSizeHalf.x) {
		ballPos.x = arenaSizeHalf.x - ballSizeHalf.x;
		ballVel.x *= -1;
	} else if(ballPos.x - ballSizeHalf.x < -arenaSizeHalf.x) {
		ballPos.x = -arenaSizeHalf.x + ballSizeHalf.x;
		ballVel.x *= -1;
	}

	clearScreen(0x191919);
	drawRect((v2){0, 0}, arenaSizeHalf, 0x444444);
	drawRect(ballPos, ballSizeHalf, 0xaaffaa);
	drawRect(playerPos, playerSizeHalf, 0xefefef);
}