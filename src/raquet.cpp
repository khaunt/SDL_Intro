#include "./raquet.h"
#include "./constants.h"


raquet::raquet(const int player_num)
	:width(2), height(30)
{
	if (player_num == 1) {
		x = WINDOW_WIDTH - 30;
		y = WINDOW_HEIGHT / 2.0;
	} else {
		x = 30;
		y = WINDOW_HEIGHT / 2.0;
	}
}
