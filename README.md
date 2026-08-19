# Mini-RPG · Laboratorio C

Proyecto para recuperar la programación en C de forma práctica mientras se trabajan los temas 31 y 32 del temario oficial y, más adelante, su conexión con el tema 33 de ensamblador.

Este README es un cuaderno de laboratorio vivo: Codex lo actualiza automáticamente al cerrar cada paso relevante y cada modificación queda registrada en un commit.

## Compilador y herramientas

### GCC

El código fuente está en `src/main.c`. La orden completa de compilación es:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -g src/main.c -o mini-rpg
```

- `gcc`: compilador de C del sistema.
- `-std=c17`: utiliza el estándar C17.
- `-Wall -Wextra -Wpedantic`: activa advertencias útiles.
- `-g`: incorpora información para depurar con GDB.
- `-o mini-rpg`: establece el nombre del ejecutable.

El ejecutable generado se inicia con:

```bash
./mini-rpg
```

El archivo `mini-rpg` es un binario regenerable y no se edita directamente.

### Makefile

El `Makefile` evita repetir manualmente la orden de GCC:

```bash
make        # Compila si el fuente ha cambiado
make run    # Compila si es necesario y ejecuta
make clean  # Elimina el ejecutable generado
```

Conceptos vistos:

- Variables de Make: `CC`, `CFLAGS`, `TARGET` y `SOURCE`.
- Una regla relaciona un objetivo con sus dependencias.
- Las órdenes de una regla comienzan con una tabulación.
- Make compara fechas y evita compilaciones innecesarias.

## El ejercicio: mini-RPG

Construiremos gradualmente un combate por turnos entre un héroe y una criatura. Cada hito debe compilar sin advertencias y producir un cambio visible o comprobable.

Salida actual:

```text
=== MINI-RPG ===
Héroe:    30/30 PV
Criatura: 20 PV
```

### Retos

- [x] Crear la estructura mínima del programa.
- [x] Declarar y mostrar la vida de los combatientes.
- [ ] Leer la acción del jugador y mostrar un menú.
- [ ] Implementar ataque, curación y límites de vida.
- [ ] Añadir el turno de la criatura.
- [ ] Repetir turnos hasta la victoria o la derrota.
- [ ] Separar responsabilidades mediante funciones.
- [ ] Representar personajes mediante `struct`.
- [ ] Incorporar daño aleatorio.
- [ ] Crear un inventario con arrays.
- [ ] Separar el programa en archivos `.c` y `.h`.
- [ ] Trabajar con punteros y memoria dinámica.
- [ ] Guardar partidas y depurar errores.
- [ ] Examinar en ensamblador algunas funciones compiladas.

## C aprendido

### Estructura del programa

- `#include <stdio.h>` declara las funciones de entrada y salida estándar.
- `main` es el punto de entrada del programa.
- `int main(void)` indica que no recibe argumentos y devuelve un entero.
- `return 0` comunica una terminación correcta.
- Las llaves delimitan bloques y las instrucciones terminan normalmente en `;`.

### Tipos, variables y constantes

```c
int vida_heroe = 30;
int vida_criatura = 20;
const int VIDA_MAXIMA = 30;
```

- `int` representa números enteros.
- Una declaración asocia un nombre y un tipo a una zona de memoria.
- La inicialización proporciona el primer valor de una variable.
- `const` expresa que el valor no debe modificarse.
- Se utilizan nombres descriptivos y `snake_case` para las variables.

### Salida con `printf`

```c
printf("Héroe: %d/%d PV\n", vida_heroe, VIDA_MAXIMA);
```

- `%d` inserta un valor de tipo `int`.
- Los valores se proporcionan en el mismo orden que sus marcadores.
- `\n` introduce un salto de línea.

## Git aprendido

El repositorio utiliza la rama principal `main`.

```bash
git status                 # Muestra el estado del repositorio
git add .                  # Prepara los cambios actuales
git commit -m "Mensaje"    # Guarda un punto estable
git log --oneline          # Muestra el historial resumido
```

El primer commit estable es:

```text
Inicia el laboratorio y muestra los combatientes
```

El archivo `.gitignore` excluye elementos regenerables:

```gitignore
mini-rpg
*.o
build/
```

Criterio de trabajo: crear un commit cuando se complete un reto que compile y funcione, no por cada pequeña edición.
