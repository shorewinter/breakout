struct {
	int isDown;
	int changed;
} typedef Button;

enum {
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_UP,
	BUTTON_DOWN,

	BUTTON_COUNT,
};

struct {
	v2i mouse;
	Button buttons[BUTTON_COUNT];
} typedef Input;

#define pressed(b) (input->buttons[b].isDown && input->buttons[b].changed)
#define released(b) (!input->buttons[b].isDown && input->buttons[b].changed)
#define isDown(b) (input->buttons[b].isDown)