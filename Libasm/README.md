Sure! Here's a single `README.md` file for your GitHub repository, combining all the lists we've created, presented in both Spanish and English.

---

# Libasm Project - Subject & ASM 64 Intel Abstractions

---

## English 🇬🇧

### Project Subject

Here are the common instructions for the Libasm project:

* Your functions shouldn't quit unexpectedly (segmentation fault, bus error, double free, etc.) except for undefined behaviors. If this happens, your project will be considered non-functional, and you'll receive a 0 during evaluation.
* Your Makefile must at least contain the rules `$(NAME)`, `all`, `clean`, `fclean`, and `re`. It must also recompile/relink only necessary files.
* To turn in bonuses for your project, you must include a `bonus` rule in your Makefile. This rule will add any headers, libraries, or functions forbidden in the main part of the project. Bonuses must be in a separate file `_bonus.{c/h}`. Mandatory and bonus part evaluation is done separately.
* We encourage you to create test programs for your project, even though this work won’t be submitted or graded. It will give you a chance to easily test your work and your peers’ work. You'll find these tests especially useful during your defense. Indeed, during defense, you're free to use your tests and/or the tests of the peer you're evaluating.
* Submit your work to your assigned Git repository. Only the work in the Git repository will be graded. If Deepthought is assigned to grade your work, it will be done after your peer-evaluations. If an error happens in any section of your work during Deepthought’s grading, the evaluation will stop.
* You must write **64-bit ASM**. Be careful with the "**calling convention**".
* You can't do **inline ASM**; you must use **.s files**.
* You must compile your assembly code with **nasm**.
* You must use the **Intel syntax**, not AT&T.
* It's forbidden to use the compilation flag: `-no-pie`.

### Common Abstractions in ASM 64 (Intel Syntax)

Here’s a list of common high-level programming abstractions and their corresponding instructions in 64-bit Intel Assembly. Keep in mind that a single high-level line can translate into multiple assembly instructions, and vice-versa. Context (registers, memory, stack) is crucial in assembly.

#### 1. Data Movement and Assignment

| High-Level Abstraction | 64-bit Intel Assembly | Description | Example (`RAX`, `RBX` are registers) |
| :--------------------- | :-------------------- | :---------- | :----------------------------------- |
| `a = b` | **`mov`** (move) | Moves a value from a source to a destination (register, memory). | `mov RAX, RBX` (RAX = RBX) |
| `int a;` | (No direct instruction; space is allocated on stack or in data section.) | Allocates space for a variable. | `sub RSP, 8` (for an 8-byte variable on the stack) |
| `*p = value` | **`mov`** | Writes a value to a memory address pointed to by a register. | `mov [RAX], RBX` (Writes value of RBX to address pointed by RAX) |
| `value = *p` | **`mov`** | Reads a value from a memory address pointed to by a register. | `mov RBX, [RAX]` (Reads from address pointed by RAX into RBX) |
| `push value` | **`push`** | Pushes a value onto the stack (decrements `RSP`). | `push RBX` |
| `value = pop()` | **`pop`** | Pops a value off the stack (increments `RSP`). | `pop RBX` |

#### 2. Arithmetic Operations

| High-Level Abstraction | 64-bit Intel Assembly | Description | Example |
| :--------------------- | :-------------------- | :---------- | :------ |
| `a = a + b` (`a += b`) | **`add`** | Adds the second operand to the first. | `add RAX, RBX` (RAX = RAX + RBX) |
| `a = a - b` (`a -= b`) | **`sub`** | Subtracts the second operand from the first. | `sub RAX, RBX` (RAX = RAX - RBX) |
| `a++` | **`inc`** (increment) | Increments the operand by 1. | `inc RAX` |
| `a--` | **`dec`** (decrement) | Decrements the operand by 1. | `dec RAX` |
| `a = a * b` | **`mul`**, **`imul`** | Multiplication (unsigned / signed). | `mul RBX` (RDX:RAX = RAX * RBX) or `imul RAX, RBX` (RAX = RAX * RBX, more flexible) |
| `a = a / b` | **`div`**, **`idiv`** | Division (unsigned / signed). Quotient goes to `RAX`, remainder to `RDX`. | `div RBX` (RAX = RAX / RBX, RDX = RAX % RBX) |
| `a = a % b` | (See `div`/`idiv`) | The remainder of the division is in the `RDX` register after `div` or `idiv`. | After `div RBX`, result is in `RDX`. |
| `neg a` (negation) | **`neg`** | Changes the sign of an operand (two's complement). | `neg RAX` |

#### 3. Bitwise Logical Operations

| High-Level Abstraction | 64-bit Intel Assembly | Description | Example |
| :--------------------- | :-------------------- | :---------- | :------ |
| `a & b` | **`and`** | Bitwise AND. | `and RAX, RBX` |
| `a \| b` | **`or`** | Bitwise OR. | `or RAX, RBX` |
| `a ^ b` | **`xor`** | Bitwise XOR. Often used for `RAX = 0` with `xor RAX, RAX`. | `xor RAX, RBX` |
| `~a` (NOT) | **`not`** | Bitwise NOT (one's complement). | `not RAX` |
| `a << n` | **`shl`** (shift left) | Logical left shift. | `shl RAX, 1` (RAX = RAX * 2) |
| `a >> n` (logical) | **`shr`** (shift right) | Logical right shift (fills with 0s). | `shr RAX, 1` (RAX = RAX / 2, unsigned) |
| `a >> n` (arithmetic) | **`sar`** (shift right) | Arithmetic right shift (preserves sign bit). | `sar RAX, 1` (RAX = RAX / 2, signed) |

#### 4. Comparison and Control Flow

| High-Level Abstraction | 64-bit Intel Assembly | Description | Example |
| :--------------------- | :-------------------- | :---------- | :------ |
| `if (cond)` | **`cmp`**, **`test`** and **`jxx`** | Compares two operands or checks bits, and conditionally jumps. | `cmp RAX, 10` `je label_if` |
| `==` | **`cmp`** followed by **`je`** (jump if equal) or **`jz`** (jump if zero) | Compares values. | `cmp RAX, RBX` `je is_equal` |
| `!=` | **`cmp`** followed by **`jne`** (jump if not equal) or **`jnz`** (jump if not zero) | Compares values. | `cmp RAX, RBX` `jne is_not_equal` |
| `<` (signed) | **`cmp`** followed by **`jl`** (jump if less) | Compares signed integers. | `cmp RAX, RBX` `jl is_less` |
| `>` (signed) | **`cmp`** followed by **`jg`** (jump if greater) | Compares signed integers. | `cmp RAX, RBX` `jg is_greater` |
| `<=` (signed) | **`cmp`** followed by **`jle`** (jump if less or equal) | Compares signed integers. | `cmp RAX, RBX` `jle is_less_or_equal` |
| `>=` (signed) | **`cmp`** followed by **`jge`** (jump if greater or equal) | Compares signed integers. | `cmp RAX, RBX` `jge is_greater_or_equal` |
| `goto Label` | **`jmp`** (jump) | Unconditional jump to a label. | `jmp end_program` |
| `function_call()` | **`call`** | Calls a subroutine (saves return address on stack and jumps). | `call my_function` |
| `return` | **`ret`** (return) | Returns from a subroutine (pops return address from stack and jumps). | `ret` |

#### 5. Operating System Interaction (Syscalls)

| High-Level Abstraction | 64-bit Intel Assembly | Description | Example (Linux) |
| :--------------------- | :-------------------- | :---------- | :-------------- |
| `printf()` | **`syscall`** | Calls kernel functions (like `write` to print). Requires setting up registers with syscall number and arguments. | `mov RAX, 1` (syscall write) `mov RDI, 1` (stdout) `mov RSI, msg_ptr` `mov RDX, msg_len` `syscall` |
| `exit()` | **`syscall`** | Calls kernel functions to terminate the program. | `mov RAX, 60` (syscall exit) `mov RDI, 0` (exit code) `syscall` |

---

## Español 🇪🇸

### Subject del Proyecto

Aquí están las instrucciones comunes para el proyecto Libasm:

* Tus funciones no deben cerrarse inesperadamente (fallo de segmentación, error de bus, doble liberación de memoria, etc.), salvo por comportamientos indefinidos. Si esto ocurre, tu proyecto se considerará no funcional y recibirás un 0 durante la evaluación.
* Tu Makefile debe contener al menos las reglas `$(NAME)`, `all`, `clean`, `fclean` y `re`. Y debe recompilar/relinkar solo los archivos necesarios.
* Para entregar los bonos de tu proyecto, debes incluir una regla `bonus` en tu Makefile, que añadirá todos los diversos encabezados, librerías o funciones prohibidas en la parte principal del proyecto. Los bonos deben estar en un archivo diferente `_bonus.{c/h}`. La evaluación de la parte obligatoria y la de bono se realiza por separado.
* Te animamos a crear programas de prueba para tu proyecto, aunque este trabajo no tendrá que ser entregado ni será calificado. Te dará la oportunidad de probar fácilmente tu trabajo y el de tus compañeros. Encontrarás estas pruebas especialmente útiles durante tu defensa. De hecho, durante la defensa, eres libre de usar tus pruebas y/o las pruebas del compañero que estés evaluando.
* Envía tu trabajo a tu repositorio Git asignado. Solo el trabajo en el repositorio Git será calificado. Si Deepthought está asignado para calificar tu trabajo, se hará después de tus evaluaciones entre compañeros. Si ocurre un error en cualquier sección de tu trabajo durante la calificación de Deepthought, la evaluación se detendrá.
* Debes escribir **ASM de 64 bits**. Ten cuidado con la "**convención de llamada**".
* No puedes hacer **ASM en línea**; debes usar **archivos .s**.
* Debes compilar tu código ensamblador con **nasm**.
* Debes usar la **sintaxis Intel**, no la AT&T.
* Está prohibido usar la bandera de compilación: `-no-pie`.

### Abstracciones Comunes en ASM 64 (Sintaxis Intel)

Aquí tienes un listado de abstracciones comunes de programación de alto nivel y sus instrucciones correspondientes en Ensamblador Intel de 64 bits. Ten en cuenta que una sola línea de alto nivel puede traducirse en varias instrucciones de ensamblador, y viceversa. El contexto (registros, memoria, pila) es crucial en ensamblador.

#### 1. Movimiento de Datos y Asignación

| Abstracción en Alto Nivel | Ensamblador 64-bit Intel | Descripción | Ejemplo (`RAX`, `RBX` son registros) |
| :------------------------ | :----------------------- | :---------- | :----------------------------------- |
| `a = b` | **`mov`** (mover) | Mueve un valor de una fuente a un destino (registro, memoria). | `mov RAX, RBX` (RAX = RBX) |
| `int a;` | (No hay una instrucción directa; se asigna espacio en la pila o en la sección de datos.) | Asignación de espacio para una variable. | `sub RSP, 8` (para una variable de 8 bytes en la pila) |
| `*p = value` | **`mov`** | Escribe un valor en una dirección de memoria apuntada por un registro. | `mov [RAX], RBX` (Escribe el valor de RBX en la dirección apuntada por RAX) |
| `value = *p` | **`mov`** | Lee un valor de una dirección de memoria apuntada por un registro. | `mov RBX, [RAX]` (Lee de la dirección apuntada por RAX y lo pone en RBX) |
| `push value` | **`push`** | Coloca un valor en la pila (decrementa `RSP`). | `push RBX` |
| `value = pop()` | **`pop`** | Extrae un valor de la pila (incrementa `RSP`). | `pop RBX` |

#### 2. Operaciones Aritméticas

| Abstracción en Alto Nivel | Ensamblador 64-bit Intel | Descripción | Ejemplo |
| :------------------------ | :----------------------- | :---------- | :------ |
| `a = a + b` (`a += b`) | **`add`** | Suma el segundo operando al primero. | `add RAX, RBX` (RAX = RAX + RBX) |
| `a = a - b` (`a -= b`) | **`sub`** | Resta el segundo operando al primero. | `sub RAX, RBX` (RAX = RAX - RBX) |
| `a++` | **`inc`** (incrementar) | Incrementa el operando en 1. | `inc RAX` |
| `a--` | **`dec`** (decrementar) | Decrementa el operando en 1. | `dec RAX` |
| `a = a * b` | **`mul`**, **`imul`** | Multiplicación (sin signo / con signo). | `mul RBX` (RDX:RAX = RAX * RBX) o `imul RAX, RBX` (RAX = RAX * RBX, más flexible) |
| `a = a / b` | **`div`**, **`idiv`** | División (sin signo / con signo). El cociente va a `RAX` y el resto a `RDX`. | `div RBX` (RAX = RAX / RBX, RDX = RAX % RBX) |
| `a = a % b` | (Ver `div`/`idiv`) | El resto de la división se encuentra en el registro `RDX` después de `div` o `idiv`. | Después de `div RBX`, el resultado es en `RDX`. |
| `neg a` (negación) | **`neg`** | Cambia el signo de un operando (complemento a dos). | `neg RAX` |

#### 3. Operaciones Lógicas a Nivel de Bit

| Abstracción en Alto Nivel | Ensamblador 64-bit Intel | Descripción | Ejemplo |
| :------------------------ | :----------------------- | :---------- | :------ |
| `a & b` | **`and`** | AND a nivel de bits. | `and RAX, RBX` |
| `a \| b` | **`or`** | OR a nivel de bits. | `or RAX, RBX` |
| `a ^ b` | **`xor`** | XOR a nivel de bits. A menudo usado para `RAX = 0` con `xor RAX, RAX`. | `xor RAX, RBX` |
| `~a` (NOT) | **`not`** | NOT a nivel de bits (complemento a uno). | `not RAX` |
| `a << n` | **`shl`** (shift left) | Desplazamiento a la izquierda. | `shl RAX, 1` (RAX = RAX * 2) |
| `a >> n` (lógico) | **`shr`** (shift right) | Desplazamiento a la derecha lógico (rellena con 0s). | `shr RAX, 1` (RAX = RAX / 2, sin signo) |
| `a >> n` (aritmético) | **`sar`** (shift right) | Desplazamiento a la derecha aritmético (mantiene el bit de signo). | `sar RAX, 1` (RAX = RAX / 2, con signo) |

#### 4. Comparación y Control de Flujo

| Abstracción en Alto Nivel | Ensamblador 64-bit Intel | Descripción | Ejemplo |
| :------------------------ | :----------------------- | :---------- | :------ |
| `if (cond)` | **`cmp`**, **`test`** y **`jxx`** | Compara dos operandos o comprueba bits, y salta condicionalmente. | `cmp RAX, 10` `je label_if` |
| `==` | **`cmp`** seguido de **`je`** (saltar si igual) o **`jz`** (saltar si cero) | Compara valores. | `cmp RAX, RBX` `je es_igual` |
| `!=` | **`cmp`** seguido de **`jne`** (saltar si no igual) o **`jnz`** (saltar si no cero) | Compara valores. | `cmp RAX, RBX` `jne no_es_igual` |
| `<` (con signo) | **`cmp`** seguido de **`jl`** (saltar si menor) | Compara valores enteros con signo. | `cmp RAX, RBX` `jl es_menor` |
| `>` (con signo) | **`cmp`** seguido de **`jg`** (saltar si mayor) | Compara valores enteros con signo. | `cmp RAX, RBX` `jg es_mayor` |
| `<=` (con signo) | **`cmp`** seguido de **`jle`** (saltar si menor o igual) | Compara valores enteros con signo. | `cmp RAX, RBX` `jle es_menor_o_igual` |
| `>=` (con signo) | **`cmp`** seguido de **`jge`** (saltar si mayor o igual) | Compara valores enteros con signo. | `cmp RAX, RBX` `jge es_mayor_o_igual` |
| `goto Label` | **`jmp`** (saltar) | Salto incondicional a una etiqueta. | `jmp fin_programa` |
| `function_call()` | **`call`** | Llama a una subrutina (guarda la dirección de retorno en la pila y salta). | `call mi_funcion` |
| `return` | **`ret`** (retornar) | Retorna de una subrutina (extrae la dirección de retorno de la pila y salta). | `ret` |

#### 5. Interacción con el Sistema Operativo (Syscalls)

| Abstracción en Alto Nivel | Ensamblador 64-bit Intel | Descripción | Ejemplo (Linux) |
| :------------------------ | :----------------------- | :---------- | :-------------- |
| `printf()` | **`syscall`** | Llama a funciones del kernel (como `write` para imprimir). Requiere preparar registros con número de syscall y argumentos. | `mov RAX, 1` (syscall write) `mov RDI, 1` (stdout) `mov RSI, msg_ptr` `mov RDX, msg_len` `syscall` |
| `exit()` | **`syscall`** | Llama a funciones del kernel para terminar el programa. | `mov RAX, 60` (syscall exit) `mov RDI, 0` (código de salida) `syscall` |