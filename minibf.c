/* minibf - minimal Brainfuck interpreter by grunfink - public domain */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *load_file(char *fn)
{
    FILE *f;
    char *prg = NULL;
    int z = 0, i = 0;

    if ((f = fopen(fn, "r")) != NULL) {
        int c;

        while ((c = getc(f)) != EOF) {
            if (i <= z) {
                z += 32;
                prg = realloc(prg, z + 1);
            }

            prg[i++] = c;
        }

        if (prg != NULL)
            prg[i] = '\0';

        fclose(f);
    }

    return prg;
}


int bf(char *prg)
{
    int db[30000];
    int pc, ptr, o, l;

    /* basic syntax check: balanced brackets */
    for (pc = l = 0; (o = prg[pc]); pc++)
        l += o == '[' ? 1 : o == ']' ? -1 : 0;

    if (o != 0)
        return -1;

    memset(db, 0, sizeof(db));
    pc = ptr = 0;

    while ((o = prg[pc])) {
        if (o == '>')
            ptr++;
        else
        if (o == '<')
            ptr--;
        else
        if (o == '+')
            db[ptr]++;
        else
        if (o == '-')
            db[ptr]--;
        else
        if (o == '.')
            putchar(db[ptr]);
        else
        if (o == ',')
            db[ptr] = (o = getchar()) == EOF ? 0 : o;
        else
        if (o == '[') {
            if (db[ptr] == 0)
                for (l = 1; l && (o = prg[++pc]); )
                    l += o == '[' ? 1 : o == ']' ? -1 : 0;
        }
        else
        if (o == ']') {
            if (db[ptr] != 0)
                for (l = 1; l && (o = prg[--pc]); )
                    l += o == ']' ? 1 : o == '[' ? -1 : 0;
        }

        pc++;
    }

    return 0;
}


int main(int argc, char *argv[])
{
    int ret = 1;

    if (argc == 2) {
        char *prg = load_file(argv[1]);

        if (prg == NULL)
            fprintf(stderr, "%s: cannot open file %s\n", argv[0], argv[1]);
        else
        if ((ret = bf(prg)) != 0)
            fprintf(stderr, "%s: %s: syntax error\n", argv[0], argv[1]);
    }
    else
        printf("%s: {brainfuck program}\n", argv[0]);

    return ret;
}
