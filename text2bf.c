/* text2bf - Converts STDIN to a Brainfuck program by grunfink - public domain */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define P1 9
#define P2 3

void text2bf(void)
{
    int n, m, max, c;
    int db[30000];
    int ptr = 0;

    /* reset the db */
    memset(db, 0, sizeof(db));

    /* fill the internal db according to the parameters */
    for (n = 0; n * P1 * P2 < 256; n++)
        db[n] = n * P1 * P2;
    max = n;

    /* build the cells with the db */
    for (n = 0; n < P1; n++)
        printf("+");
    printf("[>");
    for (n = 0; n < P2; n++)
        printf("+");
    printf("[");

    for (n = 0; n < max; n++) {
        printf(">");
        for (m = 0; m < n; m++)
            printf("+");
    }

    for (n = 0; n < max; n++)
        printf("<");
    printf("-]<-]>>");

    /* now iterate the input */
    while ((c = getchar()) != EOF) {
        /* find the optimal cell */
        int cell = ptr, dist = 0xffffff;

        for (n = 0; n < max; n++) {
            int d = db[n] - c;

            d *= d;

            if (d < dist) {
                dist = d;
                cell = n;
            }
        }

        /* move the ptr to this cell */
        if (ptr > cell)
            for (n = 0; n < ptr - cell; n++)
                printf("<");
        else
            for (n = 0; n < cell - ptr; n++)
                printf(">");

        ptr = cell;

        /* convert the content of the cell to the needed value and print */
        if (db[ptr] > c)
            for (n = 0; n < db[ptr] - c; n++)
                printf("-");
        else
            for (n = 0; n < c - db[ptr]; n++)
                printf("+");
        printf(".");

        db[ptr] = c;
    }
}


int main(int argc, char *argv[])
{
    text2bf();

    return 0;
}
