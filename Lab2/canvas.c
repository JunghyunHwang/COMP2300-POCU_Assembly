#include <assert.h>

#include "canvas.h"
#include "palette.h"

#define PALETTE_SIZE (32)
#define WIDTH (32)
#define HEIGHT (32)
#define TRUE (1)
#define FALSE (0)

static unsigned char* s_canvas;
static unsigned char s_xpos = 0;
static unsigned char s_ypos = 0;

static const unsigned char* s_palette;
static unsigned char penColor;

void set_canvas(unsigned char* canvas32x32)
{
	s_canvas = canvas32x32;
	s_palette = get_palette(0);
	penColor = s_palette[0];
}

void execute(unsigned char instruction)
{
	unsigned char arg = instruction & 0x11111;
	unsigned char op = (instruction >> 5) & 0x111;

	switch (op) {
	case 0x000:
		clear(arg);
		break;
	case 0x001:
		s_palette = get_palette(arg);
		break;
	case 0x010:
		s_xpos = arg;
		break;
	case 0x011:
		s_ypos = arg;
		break;
	case 0x100:
		s_canvas[s_ypos + HEIGHT * s_xpos] = s_palette[arg];
		break;
	case 0x101:
		penColor = s_palette[arg];
		break;
	case 0x110:
		// setxy
		break;
	case 0x111:
		if (arg & 0x10000 > 0) {
			s_canvas[s_ypos + HEIGHT * s_xpos] = penColor;
		}

		move_direction(arg & 0x1111);
		break;
	default:
		assert(FALSE);
		break;
	}
}

void clear(unsigned char color)
{
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			s_canvas[HEIGHT * i + j] = color;
		}
	}
}

void move_direction(unsigned char direction)
{
	switch (direction) {
	case 0x0000:
		break;
	case 0x0001:
		if (s_ypos > 0) {
			--s_ypos;
		}

		break;
	case 0x0010:
		if (s_ypos < HEIGHT - 1) {
			++s_ypos;
		}

		break;
	case 0x0100:
		if (s_xpos < WIDTH - 1) {
			++s_xpos;
		}

		break;
	case 0x1000:
		if (s_xpos > 0) {
			--s_xpos;
		}

		break;
	case 0x0101:
		// ++x
		// --y
		if (s_xpos < WIDTH - 1) {
			++s_xpos;
		}

		if (s_ypos > 0) {
			--s_ypos;
		}

		break;
	case 0x0110:
		// ++x
		// ++y
		if (s_xpos < WIDTH - 1) {
			++s_xpos;
		}

		if (s_ypos < HEIGHT - 1) {
			++s_ypos;
		}
		break;
	case 0x1001:
		// --x
		// --y
		if (s_xpos > 0) {
			--s_xpos;
		}

		if (s_ypos > 0) {
			--s_ypos;
		}

		break;
	case 0x1010:
		// --x
		// ++y
		if (s_xpos > 0) {
			--s_xpos;
		}

		if (s_ypos < HEIGHT - 1) {
			++s_ypos;
		}
		break;
	}
}