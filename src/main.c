#include <stdio.h>

int main(void)
{
    int vida_heroe          = 30;
    int vida_criatura       = 20;
    const int VIDA_MAXIMA   = 30;

    printf("=== MINI-RPG ===\nHéroe:    %d/%d PV\nCriatura: %d PV\n", 
        vida_heroe, VIDA_MAXIMA, vida_criatura);
    return 0;
}
