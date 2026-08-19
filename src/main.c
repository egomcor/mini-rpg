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
        printf("Atacas a la criatura.\n");
        vida_criatura = vida_criatura - 5;
        printf("La criatura tiene %d PV.\n", vida_criatura);
    } else if (opcion == 2) {
        if (vida_heroe < VIDA_MAXIMA) {
            if ((VIDA_MAXIMA - vida_heroe) >= 5) {
                vida_heroe = vida_heroe + 5;
            } else {
                vida_heroe = VIDA_MAXIMA;
            }

            printf("Te curas.\n");
            printf("El héroe tiene %d/%d PV.\n", vida_heroe, VIDA_MAXIMA);
        } else {
            printf("Ya tienes la vida al máximo.\n");
        }
    } else {
        printf("Opción no válida.\n");
    }

    if (opcion == 1 || opcion == 2) {
        printf("La criatura te ataca.\n");
        vida_heroe = vida_heroe - 4;
        printf("El héroe tiene %d/%d PV.\n", vida_heroe, VIDA_MAXIMA);
    }

    return 0;
}
