#ifndef CANVAS_H
#define CANVAS_H

void set_canvas(unsigned char* canvas32x32);

void execute(unsigned char instruction);

void clear(unsigned char color);

void move_direction(unsigned char direction);

#endif /* CANVAS_H */
