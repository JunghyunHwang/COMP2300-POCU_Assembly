#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "canvas.h"
#include "palette.h"

#define MAX_SIZE (32)

#define GET_INSTRUCTION(opcode, operand) (((opcode) << 5) | (operand))

static void homecoder_test()
{   
    clear_members();
    
    // 내부 변수를 초기화 시키는 함수를 만들어 테스트 해주시면 됩니다.

    unsigned char canvas[MAX_SIZE * MAX_SIZE];

    set_canvas(canvas);

    // SetPaletteClear test

    unsigned char palette_index;
    unsigned char color_index;

    for (palette_index = 0; palette_index < MAX_SIZE; ++palette_index) {

        const unsigned char* palette = get_palette(palette_index);

        execute(GET_INSTRUCTION(0b001, palette_index));

        for (color_index = 0; color_index < MAX_SIZE; ++color_index) {
            unsigned char color = palette[color_index];

            execute(GET_INSTRUCTION(0b000, color_index));
            int i = 0;
            int j = 0;
            for (; i < MAX_SIZE; ++i) {
                j = 0;
                for (; j < MAX_SIZE; ++j) {
                    assert(canvas[j * MAX_SIZE + i] == color);
                }
            }
        }
    }

    // DrawColor test
    clear_members();

    set_canvas(canvas);

    unsigned char x = 0;
    unsigned char y = 0;

    for (palette_index = 0; palette_index < MAX_SIZE; ++palette_index) {

        const unsigned char* palette = get_palette(palette_index);

        execute(GET_INSTRUCTION(0b001, palette_index));

        for (color_index = 0; color_index < MAX_SIZE; ++color_index) {
            unsigned char color = palette[color_index];

            execute(GET_INSTRUCTION(0b100, color_index));

            assert(canvas[MAX_SIZE * y + x] == color);
        }
    }

    // SetX, setY test

    clear_members();

    set_canvas(canvas);

    // 좌표값을 구하는 함수를 작성하시고 테스트 해주시면 됩니다.
    for (x = 0; x < MAX_SIZE; ++x) {
        execute(GET_INSTRUCTION(0b010, x));

        assert(get_x() == x);
    }

    for (y = 0; y < MAX_SIZE; ++y) {
        execute(GET_INSTRUCTION(0b011, y));

        assert(get_y() == y);
    }

    // SetXy test

    clear_members();

    set_canvas(canvas);

    // 1Quad - leftTop

    x = 16;
    y = 0;

    execute(GET_INSTRUCTION(0b110, 0b00000));
    assert(get_x() == x && get_y() == y);

    // 1Quad - leftDown

    x = 16;
    y = 15;

    execute(GET_INSTRUCTION(0b110, 0b00001));
    assert(get_x() == x && get_y() == y);

    // 1Quad - rightUp

    x = 31;
    y = 0;

    execute(GET_INSTRUCTION(0b110, 0b00010));
    assert(get_x() == x && get_y() == y);

    // 1Quad - rightDown

    x = 31;
    y = 15;

    execute(GET_INSTRUCTION(0b110, 0b00011));
    assert(get_x() == x && get_y() == y);

    // 1Quad - leftTop

    x = 16;
    y = 0;

    execute(GET_INSTRUCTION(0b110, 0b10000));
    assert(get_x() == x && get_y() == y);

    // 1Quad - leftDown

    x = 16;
    y = 15;

    execute(GET_INSTRUCTION(0b110, 0b10001));
    assert(get_x() == x && get_y() == y);

    // 1Quad - rightUp

    x = 31;
    y = 0;

    execute(GET_INSTRUCTION(0b110, 0b10010));
    assert(get_x() == x && get_y() == y);

    // 1Quad - rightDown

    x = 31;
    y = 15;

    execute(GET_INSTRUCTION(0b110, 0b10011));
    assert(get_x() == x && get_y() == y);

    // 2Quad - leftTop

    x = 0;
    y = 0;

    execute(GET_INSTRUCTION(0b110, 0b00100));
    assert(get_x() == x && get_y() == y);

    // 2Quad - leftDown

    x = 0;
    y = 15;

    execute(GET_INSTRUCTION(0b110, 0b00101));
    assert(get_x() == x && get_y() == y);

    // 2Quad - rightUp

    x = 15;
    y = 0;

    execute(GET_INSTRUCTION(0b110, 0b00110));
    assert(get_x() == x && get_y() == y);

    // 2Quad - rightDown

    x = 15;
    y = 15;

    execute(GET_INSTRUCTION(0b110, 0b00111));
    assert(get_x() == x && get_y() == y);

    // 2Quad - leftTop

    x = 0;
    y = 0;

    execute(GET_INSTRUCTION(0b110, 0b10100));
    assert(get_x() == x && get_y() == y);

    // 2Quad - leftDown

    x = 0;
    y = 15;

    execute(GET_INSTRUCTION(0b110, 0b10101));
    assert(get_x() == x && get_y() == y);

    // 2Quad - rightUp

    x = 15;
    y = 0;

    execute(GET_INSTRUCTION(0b110, 0b10110));
    assert(get_x() == x && get_y() == y);

    // 2Quad - rightDown

    x = 15;
    y = 15;

    execute(GET_INSTRUCTION(0b110, 0b10111));
    assert(get_x() == x && get_y() == y);

    // 3Quad - leftTop

    x = 0;
    y = 16;

    execute(GET_INSTRUCTION(0b110, 0b01000));
    assert(get_x() == x && get_y() == y);

    // 3Quad - leftDown

    x = 0;
    y = 31;

    execute(GET_INSTRUCTION(0b110, 0b01001));
    assert(get_x() == x && get_y() == y);

    // 3Quad - rightUp

    x = 15;
    y = 16;

    execute(GET_INSTRUCTION(0b110, 0b01010));
    assert(get_x() == x && get_y() == y);

    // 3Quad - rightDown

    x = 15;
    y = 31;

    execute(GET_INSTRUCTION(0b110, 0b01011));
    assert(get_x() == x && get_y() == y);

    // 3Quad - leftTop

    x = 0;
    y = 16;

    execute(GET_INSTRUCTION(0b110, 0b11000));
    assert(get_x() == x && get_y() == y);

    // 3Quad - leftDown

    x = 0;
    y = 31;

    execute(GET_INSTRUCTION(0b110, 0b11001));
    assert(get_x() == x && get_y() == y);

    // 3Quad - rightUp

    x = 15;
    y = 16;

    execute(GET_INSTRUCTION(0b110, 0b11010));
    assert(get_x() == x && get_y() == y);

    // 3Quad - rightDown

    x = 15;
    y = 31;

    execute(GET_INSTRUCTION(0b110, 0b11011));
    assert(get_x() == x && get_y() == y);

    // 4Quad - leftTop

    x = 16;
    y = 16;

    execute(GET_INSTRUCTION(0b110, 0b01100));
    assert(get_x() == x && get_y() == y);

    // 4Quad - leftDown

    x = 16;
    y = 31;

    execute(GET_INSTRUCTION(0b110, 0b01101));
    assert(get_x() == x && get_y() == y);

    // 4Quad - rightUp

    x = 31;
    y = 16;

    execute(GET_INSTRUCTION(0b110, 0b01110));
    assert(get_x() == x && get_y() == y);

    // 4Quad - rightDown

    x = 31;
    y = 31;

    execute(GET_INSTRUCTION(0b110, 0b01111));
    assert(get_x() == x && get_y() == y);

    // 4Quad - leftTop

    x = 16;
    y = 16;

    execute(GET_INSTRUCTION(0b110, 0b11100));
    assert(get_x() == x && get_y() == y);

    // 4Quad - leftDown

    x = 16;
    y = 31;

    execute(GET_INSTRUCTION(0b110, 0b11101));
    assert(get_x() == x && get_y() == y);

    // 4Quad - rightUp

    x = 31;
    y = 16;

    execute(GET_INSTRUCTION(0b110, 0b11110));
    assert(get_x() == x && get_y() == y);

    // 4Quad - rightDown

    x = 31;
    y = 31;

    execute(GET_INSTRUCTION(0b110, 0b11111));
    assert(get_x() == x && get_y() == y);

    // move test, pendown off

    clear_members();

    set_canvas(canvas);

    palette_index = 0;
    color_index = 0;

    const unsigned char* palette = get_palette(palette_index);
    unsigned char color = palette[color_index];

    execute(GET_INSTRUCTION(0b000, color_index));

    // not moving
    for (x = 0; x < MAX_SIZE; ++x) {
        execute(GET_INSTRUCTION(0b111, 0b00000));

        assert(get_x() == 0 && canvas[x] == color);
    }
    execute(GET_INSTRUCTION(0b111, 0b00000));
    assert(get_x() == 0 && canvas[x] == color);

    for (y = 0; y < MAX_SIZE; ++y) {
        execute(GET_INSTRUCTION(0b111, 0b00000));

        assert(get_y() == 0 && canvas[y] == color);
    }
    execute(GET_INSTRUCTION(0b111, 0b00000));
    assert(get_x() == 0 && canvas[y] == color);

    // move right
    for (x = 1; x < MAX_SIZE; ++x) {
        execute(GET_INSTRUCTION(0b111, 0b00100));

        assert(get_x() == x && canvas[x] == color);
    }
    execute(GET_INSTRUCTION(0b111, 0b00100));
    assert(get_x() == 0 && canvas[x] == color);

    // move up
    for (y = MAX_SIZE - 1; (char)y >= 0; --y) {
        execute(GET_INSTRUCTION(0b111, 0b00001));

        assert(get_y() == y && canvas[y] == color);
    }

    // move left
    for (x = MAX_SIZE - 1; (char)x >= 0; --x) {
        execute(GET_INSTRUCTION(0b111, 0b01000));

        assert(get_x() == x && canvas[x] == color);
    }

    //move down
    for (y = 1; y < MAX_SIZE; ++y) {
        execute(GET_INSTRUCTION(0b111, 0b00010));

        assert(get_y() == y && canvas[y] == color);
    }
    execute(GET_INSTRUCTION(0b111, 0b00010));
    assert(get_y() == 0 && canvas[y] == color);
}


static void draw_heart()
{
    unsigned char canvas[MAX_SIZE * MAX_SIZE];

    int x;
    int y;

    memset(canvas, ' ', sizeof(char) * MAX_SIZE * MAX_SIZE);

    set_canvas(canvas);

    execute(GET_INSTRUCTION(0b101, 0b00011));

    for (y = 0; y < MAX_SIZE; ++y) {

        for (x = 0; x < MAX_SIZE; ++x) {
            // math.h
            if (pow(((x - 16) * (x - 16) + (y - 16) * (y - 16)) - 10, 3) <= -25 * (x - 16) * (x - 16) * pow((y - 16), 3)) {
                execute(GET_INSTRUCTION(0b111, 0b10100));
            } else {
                execute(GET_INSTRUCTION(0b111, 0b00100));
            }
        }

        execute(GET_INSTRUCTION(0b111, 0b00010));
    }

    for (y = 0; y < MAX_SIZE; ++y) {

        for (x = 0; x < MAX_SIZE; ++x) {
            printf("%c", canvas[y * MAX_SIZE + x]);
        }
        printf("\n");
    }

    /*
                                    
                                
                                
                                
                                
                                
                                
                                
                                
                                
           wwww    wwww         
           wwwww  wwwww         
           wwwwwwwwwwww         
           wwwwwwwwwwww         
            wwwwwwwwww          
            wwwwwwwwww          
             wwwwwwww           
              wwwwww            
                ww              
                ww              
                                
                                
                                
                                
                                
                                
                                
                                
                                
                                
                                
                                
    */
}

