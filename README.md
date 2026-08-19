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
1. Atacar
2. Curarse
Elige una acción:1
Has elegido la opción 1.
```

### Retos

- [x] Crear la estructura mínima del programa.
- [x] Declarar y mostrar la vida de los combatientes.
- [x] Leer la acción del jugador y mostrar un menú.
- [x] Validar una entrada que no sea numérica.
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

### Entrada inicial con `scanf`

```c
int opcion = 0;
scanf("%d", &opcion);
```

- `%d` solicita la conversión de la entrada a un valor de tipo `int`.
- `&opcion` proporciona la dirección de memoria donde `scanf` debe escribir el resultado.
- Si se introduce un entero, `opcion` recibe su valor.
- Si se introduce texto como `hola`, la conversión falla y `opcion` conserva su valor anterior; el texto no se convierte en cero.
- `scanf` devuelve el número de conversiones realizadas correctamente. El programa guarda ese resultado y exige que sea `1`:

```c
int datos_leidos = scanf("%d", &opcion);

if (datos_leidos != 1) {
    printf("Error: debes introducir un número.\n");
    return 1;
}
```

- `return 0` comunica al sistema una terminación correcta.
- `return 1` comunica que el programa terminó debido a un error.
- Tras ejecutar directamente `./mini-rpg`, `echo $?` muestra el código devuelto por el programa.
- Tras ejecutar `make run`, un fallo `1` de `mini-rpg` hace fallar la receta y Make termina con su propio código `2`; en ese caso `echo $?` observa el estado de Make, no directamente el del juego.

### Criterios de orden y estilo

Las declaraciones se agrupan por finalidad. Primero se sitúan las constantes y después las variables de estado y de entrada:

```c
const int vida_maxima = 30;

int vida_heroe = 30;
int vida_criatura = 20;
int opcion = 0;
```

- Se utiliza un único espacio alrededor de `=` en vez de alinear columnas manualmente; así los cambios futuros son más sencillos y producen diferencias más limpias en Git.
- Las mayúsculas completas se reservan preferentemente para macros. Una constante local declarada con `const` puede conservar el estilo `snake_case`.
- Las líneas en blanco separan fases conceptuales: declarar, mostrar, leer, procesar y terminar.
- Se evita acumular varias líneas vacías consecutivas.

C permite dividir una cadena larga en literales consecutivos, que el compilador concatena:

```c
printf(
    "=== MINI-RPG ===\n"
    "Héroe:    %d/%d PV\n"
    "Criatura: %d PV\n",
    vida_heroe,
    vida_maxima,
    vida_criatura
);
```

El formato debe ayudar a reconocer la estructura del programa. Más adelante se podrá incorporar `clang-format` para automatizar espacios y saltos de línea, una vez decidido el estilo deseado.

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
