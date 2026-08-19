#include <stdio.h>

int main(void)
{
    int         vida_heroe      = 30;
    int         vida_criatura   = 20;
    const int   VIDA_MAXIMA     = 30;

    int         opcion          = 0;

    printf("=== MINI-RPG ===\nHéroe:    %d/%d PV\nCriatura: %d PV\n", 
        vida_heroe, VIDA_MAXIMA, vida_criatura);
    printf("1. Atacar\n2. Curarse\nElige una acción:");
    scanf("%d", &opcion);
    printf("Has elegido la opción %d.\n", opcion);


    return 0;
}
