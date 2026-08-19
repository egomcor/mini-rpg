# Laboratorio C

Espacio de práctica para recuperar C mientras se trabajan en paralelo los temas 31 y 32 del temario oficial y, más adelante, su conexión con el tema 33 de ensamblador.

## Compilar

Desde esta carpeta:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -g src/main.c -o mini-rpg
```

## Ejecutar

```bash
./mini-rpg
```

## Primer reto

Construir gradualmente un combate por turnos. La primera versión utilizará variables, entrada y salida, decisiones y bucles, sin estructuras ni memoria dinámica.
