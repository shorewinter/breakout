static int intersect(v2 pos1, v2 half1, v2 pos2, v2 half2) {
	return pos1.y + half1.y > pos2.y - half2.x &&
		pos1.y - half1.y < pos2.y + half2.x &&
		pos1.x + half1.x > pos2.x - half2.x &&
		pos1.x - half1.x < pos2.x - half2.x;
}