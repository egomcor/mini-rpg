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

### Atajos utilizados en VS Code

- `Ctrl + →` desplaza el cursor hasta el comienzo de la palabra siguiente; pulsándolo sucesivamente se llega al final de la línea.
- En el teclado utilizado, al configurar la rueda en modo de desplazamiento, pulsarla funciona como la tecla `Fin` y lleva directamente al final de la línea.
- `Ctrl + J` muestra u oculta el panel inferior, donde se encuentra el terminal integrado cuando está seleccionado.
- `Ctrl + B` muestra u oculta la barra lateral izquierda.

Estos atajos agilizan la alternancia entre la edición del código, el terminal y el explorador del proyecto.

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
Atacas a la criatura.
La criatura tiene 15 PV.
```

### Retos

- [x] Crear la estructura mínima del programa.
- [x] Declarar y mostrar la vida de los combatientes.
- [x] Leer la acción del jugador y mostrar un menú.
- [x] Validar una entrada que no sea numérica.
- [x] Distinguir ataque, curación y opciones enteras no válidas.
- [x] Reducir la vida de la criatura al atacar.
- [x] Implementar ataque, curación y límites de vida.
- [x] Añadir el turno de la criatura.
- [x] Repetir turnos hasta la victoria o la derrota.
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

### Decisiones con `if`, `else if` y `else`

El valor introducido se compara para elegir una única acción:

```c
if (opcion == 1) {
    printf("\nAtacas a la criatura.\n");
} else if (opcion == 2) {
    printf("\nTe curas.\n");
} else {
    printf("\nOpción no válida.\n");
}
```

- `==` compara dos valores; no debe confundirse con `=`, que realiza una asignación.
- Las condiciones se evalúan en orden y solo se ejecuta la primera rama aplicable.
- `else` recoge cualquier entero distinto de `1` y `2`.
- Se mantienen las llaves incluso en bloques de una sola instrucción para facilitar cambios posteriores.

### Modificación del estado

El ataque modifica la vida de la criatura antes de mostrar su nuevo valor:

```c
vida_criatura = vida_criatura - 5;
printf("La criatura tiene %d PV.\n", vida_criatura);
```

La expresión situada a la derecha se calcula primero y el resultado se asigna de nuevo a `vida_criatura`. Así, partiendo de `20`, el primer ataque deja la vida en `15`. Más adelante se estudiará una escritura abreviada para esta operación.

La curación recupera `5 PV` sin superar la vida máxima:

```c
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
```

- Un `if` puede contener otro `if` para distinguir decisiones dependientes.
- Si faltan al menos `5 PV`, se suma la curación completa.
- Si faltan menos de `5 PV`, se asigna directamente `VIDA_MAXIMA` para no sobrepasarla.
- Si la vida ya está completa, el `else` exterior informa de que no es posible curarse más.
- Se probaron los estados iniciales `20`, `27` y `30`: producen respectivamente `25`, `30` y el aviso de vida máxima.

### Turno de la criatura y operador lógico `||`

Después de una acción válida, la criatura contraataca y resta `4 PV` al héroe:

```c
if (opcion == 1 || opcion == 2) {
    printf("La criatura te ataca.\n");
    vida_heroe = vida_heroe - 4;
    printf("El héroe tiene %d/%d PV.\n", vida_heroe, VIDA_MAXIMA);
}
```

- `||` representa el operador lógico «o».
- La condición es verdadera cuando `opcion` vale `1` o cuando vale `2`.
- El contraataque se escribe una sola vez después de procesar la acción del jugador.
- Una opción inválida no cumple ninguna de las dos comparaciones y, por tanto, no concede turno a la criatura.

### Bucle de combate con `while` y `&&`

El combate se repite mientras ambos personajes continúan vivos:

```c
while (vida_criatura > 0 && vida_heroe > 0) {
    /* mostrar el estado, leer y procesar el turno */
}
```

- `while` comprueba la condición antes de cada vuelta y ejecuta nuevamente su bloque mientras sea verdadera.
- `&&` representa el operador lógico «y»: ambas comparaciones deben ser verdaderas para comenzar otro turno.
- El estado y el menú se muestran dentro del bucle para reflejar las vidas actualizadas.
- Las variables `opcion` y `datos_leidos` se declaran antes del bucle y reciben nuevos valores durante cada turno.
- Una opción entera distinta de `1` y `2` no provoca el contraataque y permite comenzar otro turno.
- El contraataque exige además que `vida_criatura > 0`, por lo que la criatura no actúa después del golpe definitivo.
- Al finalizar el bucle se comprueba qué personaje llegó a cero y se anuncia la victoria o la derrota.

Se intentó inicialmente usar `continue` después de una conversión fallida de `scanf`. Esto produjo un bucle infinito: el texto no convertible permanecía en la entrada y cada vuelta volvía a encontrarlo. Hasta estudiar cómo limpiar el búfer de entrada, el programa informa del error y termina con `return 1`.

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

### Unificar commits locales

Para reemplazar varios commits locales consecutivos por uno solo se identificó primero el último commit que debía conservarse sin cambios:

```text
7b93db5 Valida la entrada numérica del jugador
a3f2f14 Solucionado la variable opcion no estaba declarada
10a8e22 Corrige el estilo de main.c
011b984 Documenta los criterios de estilo del código C
```

Se movió `main` hasta `011b984`, manteniendo preparados todos los cambios posteriores:

```bash
git reset --soft 011b984
```

`--soft` mueve `HEAD` y la rama, pero no modifica los archivos de trabajo ni el área de preparación. Los cambios acumulados de los tres commits quedaron listos para crear uno nuevo:

```bash
git commit -m "Valida la entrada numérica del jugador"
```

Antes de reescribir el historial se comprobó que el árbol estuviera limpio y que no existiera un remoto con esos commits publicados:

```bash
git status --short
git remote -v
git log --oneline --graph
```

Esta técnica debe limitarse a commits locales. Si ya se han compartido, reescribirlos puede complicar el trabajo de otras personas. Los commits retirados de la historia normal suelen poder localizarse temporalmente mediante `git reflog`.
