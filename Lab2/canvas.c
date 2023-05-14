#include <assert.h>

#include "canvas.h"
#include "palette.h"

#define PALETTE_SIZE (32)
#define WIDTH (32)
#define HEIGHT (32)
#define TRUE (1)
#define FALSE (0)
#define NULL (0)

static unsigned char* s_canvas;
static unsigned char s_xpos = 0;
static unsigned char s_ypos = 0;

static const unsigned char* s_palette;
static unsigned char s_pen_color;

void clear_members()
{
    s_xpos = 0;
    s_ypos = 0;
}

unsigned char get_x()
{
    return s_xpos;
}

unsigned char get_y()
{
    return s_ypos;
}

void set_canvas(unsigned char* canvas32x32)
{
    s_canvas = canvas32x32;
    s_palette = get_palette(0);
    s_pen_color = s_palette[0];
}

void execute(unsigned char instruction)
{
    unsigned char arg = instruction & 0b11111;
    unsigned char op = (instruction >> 5) & 0b111;

    switch (op) {
    case 0b000:
        clear(s_palette[arg]);
        break;
    case 0b001:
        s_palette = get_palette(arg);
        break;
    case 0b010:
        s_xpos = arg;
        break;
    case 0b011:
        s_ypos = arg;
        break;
    case 0b100:
        s_canvas[s_ypos * HEIGHT + s_xpos] = s_palette[arg];
        break;
    case 0b101:
        s_pen_color = s_palette[arg];
        break;
    case 0b110: {
        unsigned char corner = arg & 0b11;
        unsigned char quad = (arg >> 2) & 0b11;

        switch (quad) {
        case 0b00:
            switch (corner) {
            case 0b00:
                s_xpos = 16;
                s_ypos = 0;
                break;
            case 0b01:
                s_xpos = 16;
                s_ypos = 15;
                break;
            case 0b10:
                s_xpos = 31;
                s_ypos = 0;
                break;
            case 0b11:
                s_xpos = 31;
                s_ypos = 15;
                break;
            default:
                assert(FALSE);
                break;
            }
            break;
        case 0b01:
            switch (corner) {
            case 0b00:
                s_xpos = 0;
                s_ypos = 0;
                break;
            case 0b01:
                s_xpos = 0;
                s_ypos = 15;
                break;
            case 0b10:
                s_xpos = 15;
                s_ypos = 0;
                break;
            case 0b11:
                s_xpos = 15;
                s_ypos = 15;
                break;
            default:
                assert(FALSE);
                break;
            }
            break;
        case 0b10:
            switch (corner) {
            case 0b00:
                s_xpos = 0;
                s_ypos = 16;
                break;
            case 0b01:
                s_xpos = 0;
                s_ypos = 31;
                break;
            case 0b10:
                s_xpos = 15;
                s_ypos = 16;
                break;
            case 0b11:
                s_xpos = 15;
                s_ypos = 31;
                break;
            default:
                assert(FALSE);
                break;
            }
            break;
        case 0b11:
            switch (corner) {
            case 0b00:
                s_xpos = 16;
                s_ypos = 16;
                break;
            case 0b01:
                s_xpos = 16;
                s_ypos = 31;
                break;
            case 0b10:
                s_xpos = 31;
                s_ypos = 16;
                break;
            case 0b11:
                s_xpos = 31;
                s_ypos = 31;
                break;
            default:
                assert(FALSE);
                break;
            }
            break;
        default:
            assert(FALSE);
            break;
        }
        }
        break;
    case 0b111:
        if ((arg & 0b10000) > 0) {
            s_canvas[s_ypos * HEIGHT + s_xpos] = s_pen_color;
        }

        move_direction(arg & 0b1111);

        if ((arg & 0b10000) > 0) {
            s_canvas[s_ypos * HEIGHT + s_xpos] = s_pen_color;
        }
        break;
    default:
        assert(FALSE);
        break;
    }
}

void clear(unsigned char color)
{
    int i = 0;
    int j = 0;
    
    for (; i < HEIGHT; ++i) {
        j = 0;
        for (; j < WIDTH; ++j) {
            s_canvas[HEIGHT * i + j] = color;
        }
    }
}

void move_direction(unsigned char direction)
{
    switch (direction) {
    case 0b0000:
        break;
    case 0b0001:
        if (s_ypos > 0) {
            --s_ypos;
        } else {
            s_ypos = 0b11111;
        }
        break;
    case 0b0010:
        if (s_ypos < HEIGHT - 1) {
            ++s_ypos;
        } else {
            s_ypos = 0;
        }
        break;
    case 0b0100:
        if (s_xpos < WIDTH - 1) {
            ++s_xpos;
        } else {
            s_xpos = 0;
        }
        break;
    case 0b1000:
        if (s_xpos > 0) {
            --s_xpos;
        } else {
            s_xpos = 0b11111;
        }
        break;
    case 0b0101:
        if (s_xpos < WIDTH - 1) {
            ++s_xpos;
        } else {
            s_xpos = 0;
        }

        if (s_ypos > 0) {
            --s_ypos;
        } else {
            s_ypos = 0b11111;
        }
        break;
    case 0b0110:
        if (s_xpos < WIDTH - 1) {
            ++s_xpos;
        } else {
            s_xpos = 0;
        }

        if (s_ypos < HEIGHT - 1) {
            ++s_ypos;
        } else {
            s_ypos = 0;
        }
        break;
    case 0b1001:
        if (s_xpos > 0) {
            --s_xpos;
        } else {
            s_xpos = 0b11111;
        }

        if (s_ypos > 0) {
            --s_ypos;
        } else {
            s_ypos = 0b11111;
        }
        break;
    case 0b1010:
        if (s_xpos > 0) {
            --s_xpos;
        } else {
            s_xpos = 0b11111;
        }

        if (s_ypos < HEIGHT - 1) {
            ++s_ypos;
        } else {
            s_ypos = 0;
        }
        break;
    default:
        assert(FALSE);
        break;
    }
}
