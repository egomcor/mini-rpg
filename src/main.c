#include <stdio.h>

int main(void)
{
    int vida_heroe = 30;
    int vida_criatura = 20;
    const int VIDA_MAXIMA = 30;

    printf(
        "=== MINI-RPG ===\n"
        "Héroe:    %d/%d PV\n"
        "Criatura: %d PV\n",
        vida_heroe,
        VIDA_MAXIMA,
        vida_criatura
    );

    printf(
        "\n"
        "1. Atacar\n"
        "2. Curarse\n"
        "Elige una acción: "
    );

    int opcion = 0;
    int datos_leidos = scanf("%d", &opcion);

    if (datos_leidos != 1) {
        printf("Error: debes introducir un número.\n");
        return 1;
    }

    if (opcion == 1) {
        printf("\nAtacas a la criatura.\n");
        vida_criatura = vida_criatura - 5;
        printf("La criatura tiene %d PV.\n", vida_criatura);
    } else if (opcion == 2) {
        printf("\nTe curas.\n");
    } else {
        printf("\nOpción no válida.\n");
    }

    return 0;
}
