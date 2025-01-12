#include "Game.h"
#include "InterfaceBook.h"

int main()
{
    InterfaceBook book(1640, 912);
    book.init();
    book.run();
    return 0;
}