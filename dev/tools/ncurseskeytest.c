#include <stdio.h>
#include <ncurses.h>
#include <locale.h>
#include <wchar.h>

int main()
{
    setlocale(LC_CTYPE, ""); initscr(); raw(); noecho(); keypad(stdscr, TRUE);
    wint_t c;
    get_wch(&c);
    endwin();
    printf("Keycode: %d\n", c);
    return 0;
}
