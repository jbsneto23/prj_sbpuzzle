#include "block.h"

Block::Block()
{
    //ctor
}

Block::Block(int n, int r, int c, int w, int h, char d)
{
    set_number(n);
    set_row(r);
    set_column(c);
    set_width(w);
    set_height(h);
    set_direction(d);
}

Block::~Block()
{
    //dtor
}

int Block::get_number()
{
    return number;
}

void Block::set_number(int n)
{
    number = n;
}

int Block::get_row()
{
    return row;
}

void Block::set_row(int r)
{
    row = r;
}

int Block::get_column()
{
    return column;
}

void Block::set_column(int c)
{
    column = c;
}

int Block::get_width()
{
    return width;
}

void Block::set_width(int w)
{
    width = w;
}

int Block::get_height()
{
    return height;
}

void Block::set_height(int h)
{
    height = h;
}

char Block::get_direction()
{
    return direction;
}

void Block::set_direction(char d)
{
    direction = d;
}
