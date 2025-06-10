¡De nada! Me alegra que estés satisfecho con la ayuda.

---

¡Excelente! Me alegra mucho que tu implementación de `ft_strcmp` esté funcionando correctamente. Es un gran hito en tu proyecto `libasm`.

Aquí tienes la información ampliada sobre el proyecto y las abstracciones, incluyendo la tabla de *flags* en inglés y español, como solicitaste:

---

# Proyecto Libasm - Asignatura & Abstracciones ASM 64 Intel

---

## English 🇬🇧

### Project Subject

Here are the common instructions for the Libasm project:

* Your functions shouldn't quit unexpectedly (segmentation fault, bus error, double free, etc.) except for undefined behaviors. If this happens, your project will be considered non-functional, and you'll receive a 0 during evaluation.
* Your Makefile must at least contain the rules `$(NAME)`, `all`, `clean`, `fclean`, and `re`. It must also recompile/relink only necessary files.
* To turn in bonuses for your project, you must include a `bonus` rule in your Makefile. This rule will add any headers, libraries, or functions forbidden in the main part of the project. Bonuses must be in a separate file `_bonus.{c/h}`. Mandatory and bonus part evaluation is done separately.
* We encourage you to create test programs for your project, even though this work won’t be submitted or graded. It will give you a chance to easily test your work and your peers’ work. You'll find these tests especially useful during your defense. Indeed, during defense, you're free to use your tests and/or the tests of the peer you're evaluating.
* Submit your work to your assigned Git repository. Only the work in the Git repository will be graded. If Deepthought is assigned to grade your work, it will be done after your peer-evaluations. If an error happens in any section of your work during Deepthought’s grading, the evaluation will stop.
* You must write **64-bit ASM**. Be careful with the "**calling convention**". This is crucial for how arguments are passed to your functions and how return values are expected.
* You can't do **inline ASM**; you must use **.s files**. This means all your assembly code must be in separate assembly source files.
* You must compile your assembly code with **nasm**. This is the specific assembler you are required to use.
* You must use the **Intel syntax**, not AT&T. This affects the order of operands (destination, source) and how memory addresses are referenced.
* It's forbidden to use the compilation flag: `-no-pie`. This means your compiled code must be Position-Independent Executable, which is important for security and modern systems.

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
| `a = a * b` | **`mul`**, **`imul`** | Multiplication (unsigned / signed). Note: `mul` operates on `RAX` by default, storing result in `RDX:RAX`. `imul` can be more flexible. | `mul RBX` (RDX:RAX = RAX * RBX) or `imul RAX, RBX` (RAX = RAX * RBX, more flexible) |
| `a = a / b` | **`div`**, **`idiv`** | Division (unsigned / signed). Quotient goes to `RAX`, remainder to `RDX`. You must ensure `RDX` is cleared before `div` for unsigned division (e.g., `xor RDX, RDX`) or contains the sign extension of `RAX` for signed division (`cqo` instruction). | `div RBX` (RAX = RAX / RBX, RDX = RAX % RBX) |
| `a = a % b` | (See `div`/`idiv`) | The remainder of the division is in the `RDX` register after `div` or `idiv`. | After `div RBX`, result is in `RDX`. |
| `neg a` (negation) | **`neg`** | Changes the sign of an operand (two's complement). | `neg RAX` |

#### 3. Bitwise Logical Operations

| High-Level Abstraction | 64-bit Intel Assembly | Description | Example |
| :--------------------- | :-------------------- | :---------- | :------ |
| `a & b` | **`and`** | Bitwise AND. | `and RAX, RBX` |
| `a \| b` | **`or`** | Bitwise OR. | `or RAX, RBX` |
| `a ^ b` | **`xor`** | Bitwise XOR. Often used for `RAX = 0` with `xor RAX, RAX` as it's efficient. | `xor RAX, RBX` |
| `~a` (NOT) | **`not`** | Bitwise NOT (one's complement). | `not RAX` |
| `a << n` | **`shl`** (shift left) | Logical left shift. Fills vacated bits with 0s. Can be used for multiplication by powers of 2. | `shl RAX, 1` (RAX = RAX * 2) |
| `a >> n` (logical) | **`shr`** (shift right) | Logical right shift (fills with 0s). Used for unsigned division by powers of 2. | `shr RAX, 1` (RAX = RAX / 2, unsigned) |
| `a >> n` (arithmetic) | **`sar`** (shift right) | Arithmetic right shift (preserves sign bit). Used for signed division by powers of 2. | `sar RAX, 1` (RAX = RAX / 2, signed) |

#### 4. Comparison and Control Flow

| High-Level Abstraction | 64-bit Intel Assembly | Description | Example |
| :--------------------- | :-------------------- | :---------- | :------ |
| `if (cond)` | **`cmp`**, **`test`** and **`jxx`** | `cmp` (compare) performs a subtraction without storing the result, only setting CPU flags. `test` performs a bitwise AND without storing the result, only setting flags. `jxx` (jump conditional) uses these flags to decide whether to jump. | `cmp RAX, 10` `je label_if` |
| `==` | **`cmp`** followed by **`je`** (jump if equal) or **`jz`** (jump if zero) | Compares values. `jz` is often used after `test` or `sub` where the result of the operation is 0 if conditions are met. | `cmp RAX, RBX` `je is_equal` |
| `!=` | **`cmp`** followed by **`jne`** (jump if not equal) or **`jnz`** (jump if not zero) | Compares values. `jnz` is used after `test` or `sub` where the result is non-zero if conditions are met. | `cmp RAX, RBX` `jne is_not_equal` |
| `<` (signed) | **`cmp`** followed by **`jl`** (jump if less) | Compares signed integers. | `cmp RAX, RBX` `jl is_less` |
| `>` (signed) | **`cmp`** followed by **`jg`** (jump if greater) | Compares signed integers. | `cmp RAX, RBX` `jg is_greater` |
| `<=` (signed) | **`cmp`** followed by **`jle`** (jump if less or equal) | Compares signed integers. | `cmp RAX, RBX` `jle is_less_or_equal` |
| `>=` (signed) | **`cmp`** followed by **`jge`** (jump if greater or equal) | Compares signed integers. | `cmp RAX, RBX` `jge is_greater_or_equal` |
| `<` (unsigned) | **`cmp`** followed by **`jb`** (jump if below) or **`jc`** (jump if carry) | Compares unsigned integers. | `cmp RAX, RBX` `jb is_below_unsigned` |
| `>` (unsigned) | **`cmp`** followed by **`ja`** (jump if above) | Compares unsigned integers. | `cmp RAX, RBX` `ja is_above_unsigned` |
| `<=` (unsigned) | **`cmp`** followed by **`jbe`** (jump if below or equal) | Compares unsigned integers. | `cmp RAX, RBX` `jbe is_below_or_equal_unsigned` |
| `>=` (unsigned) | **`cmp`** followed by **`jae`** (jump if above or equal) or **`jnc`** (jump if no carry) | Compares unsigned integers. | `cmp RAX, RBX` `jae is_above_or_equal_unsigned` |
| `goto Label` | **`jmp`** (jump) | Unconditional jump to a label. | `jmp end_program` |
| `function_call()` | **`call`** | Calls a subroutine. It pushes the return address onto the stack and then jumps to the target address. | `call my_function` |
| `return` | **`ret`** (return) | Returns from a subroutine. It pops the return address from the stack and jumps to it. | `ret` |

#### 5. Operating System Interaction (Syscalls)

| High-Level Abstraction | 64-bit Intel Assembly | Description | Example (Linux) |
| :--------------------- | :-------------------- | :---------- | :-------------- |
| `printf()` | **`syscall`** | Calls kernel functions (like `write` to print to standard output). Requires setting up registers with the specific syscall number and its arguments according to the calling convention (e.g., `RAX` for syscall number, `RDI`, `RSI`, `RDX`, `R10`, `R8`, `R9` for arguments). | `mov RAX, 1` (syscall write) `mov RDI, 1` (stdout) `mov RSI, msg_ptr` `mov RDX, msg_len` `syscall` |
| `exit()` | **`syscall`** | Calls kernel functions to terminate the program. | `mov RAX, 60` (syscall exit) `mov RDI, 0` (exit code) `syscall` |

### CPU Flags (EFLAGS Register)

After most arithmetic, logical, and comparison operations, the CPU sets various **flags** in the **EFLAGS register** (or RFLAGS in 64-bit mode). These flags reflect the result of the operation and are used by conditional jump instructions (`jxx`).

| Flag Name (English) | Spanish Name | Abbreviation | Description (English) | Descripción (Español) |
| :------------------ | :----------- | :----------- | :-------------------- | :-------------------- |
| **Zero Flag** | **Bandera de Cero** | ZF | Set if the result of an operation is zero. Cleared otherwise. | Se establece si el resultado de una operación es cero. Se borra en caso contrario. |
| **Carry Flag** | **Bandera de Acarreo** | CF | Set if an unsigned arithmetic operation results in a carry (for addition) or a borrow (for subtraction) out of the most significant bit. Cleared otherwise. | Se establece si una operación aritmética sin signo produce un acarreo (para suma) o un préstamo (para resta) desde el bit más significativo. Se borra en caso contrario. |
| **Sign Flag** | **Bandera de Signo** | SF | Set if the most significant bit (MSB) of the result is 1 (indicating a negative result in two's complement). Cleared otherwise. | Se establece si el bit más significativo (MSB) del resultado es 1 (indicando un resultado negativo en complemento a dos). Se borra en caso contrario. |
| **Overflow Flag** | **Bandera de Desbordamiento** | OF | Set if a signed arithmetic operation results in an overflow (i.e., the result is too large/small to fit in the destination operand for signed numbers). Cleared otherwise. | Se establece si una operación aritmética con signo produce un desbordamiento (es decir, el resultado es demasiado grande/pequeño para caber en el operando de destino para números con signo). Se borra en caso contrario. |
| **Parity Flag** | **Bandera de Paridad** | PF | Set if the least significant byte of the result contains an even number of set bits (1s). Cleared otherwise. | Se establece si el byte menos significativo del resultado contiene un número par de bits (1s) activados. Se borra en caso contrario. |
| **Auxiliary Carry Flag** | **Bandera de Acarreo Auxiliar** | AF | Set if an arithmetic operation generates a carry or borrow out of bit 3 (used for BCD arithmetic). Less commonly used in general programming. | Se establece si una operación aritmética genera un acarreo o préstamo del bit 3 (utilizado para aritmética BCD). Menos común en programación general. |
| **Direction Flag** | **Bandera de Dirección** | DF | Controls the direction of string operations (e.g., `movs`, `stos`). Set to 0 for auto-increment (forward), 1 for auto-decrement (backward). | Controla la dirección de las operaciones de cadena (ej. `movs`, `stos`). Se establece en 0 para auto-incremento (hacia adelante), en 1 para auto-decremento (hacia atrás). |

---

## Español 🇪🇸

### Subject del Proyecto

Aquí están las instrucciones comunes para el proyecto Libasm:

* Tus funciones no deben cerrarse inesperadamente (fallo de segmentación, error de bus, doble liberación de memoria, etc.), salvo por comportamientos indefinidos. Si esto ocurre, tu proyecto se considerará no funcional y recibirás un 0 durante la evaluación.
* Tu Makefile debe contener al menos las reglas `$(NAME)`, `all`, `clean`, `fclean` y `re`. Y debe recompilar/relinkar solo los archivos necesarios.
* Para entregar los bonos de tu proyecto, debes incluir una regla `bonus` en tu Makefile, que añadirá todos los diversos encabezados, librerías o funciones prohibidas en la parte principal del proyecto. Los bonos deben estar en un archivo diferente `_bonus.{c/h}`. La evaluación de la parte obligatoria y la de bono se realiza por separado.
* Te animamos a crear programas de prueba para tu proyecto, aunque este trabajo no tendrá que ser entregado ni será calificado. Te dará la oportunidad de probar fácilmente tu trabajo y el de tus compañeros. Encontrarás estas pruebas especialmente útiles durante tu defensa. De hecho, durante la defensa, eres libre de usar tus pruebas y/o las pruebas del compañero que estés evaluando.
* Envía tu trabajo a tu repositorio Git asignado. Solo el trabajo en el repositorio Git será calificado. Si Deepthought está asignado para calificar tu trabajo, se hará después de tus evaluaciones entre compañeros. Si ocurre un error en cualquier sección de tu trabajo durante la calificación de Deepthought, la evaluación se detendrá.
* Debes escribir **ASM de 64 bits**. Ten cuidado con la "**convención de llamada**". Esto es crucial para cómo se pasan los argumentos a tus funciones y cómo se esperan los valores de retorno.
* No puedes hacer **ASM en línea**; debes usar **archivos .s**. Esto significa que todo tu código ensamblador debe estar en archivos de código fuente de ensamblador separados.
* Debes compilar tu código ensamblador con **nasm**. Este es el ensamblador específico que se te requiere usar.
* Debes usar la **sintaxis Intel**, no la AT&T. Esto afecta el orden de los operandos (destino, fuente) y cómo se referencian las direcciones de memoria.
* Está prohibido usar la bandera de compilación: `-no-pie`. Esto significa que tu código compilado debe ser un ejecutable independiente de la posición (Position-Independent Executable), lo cual es importante para la seguridad y los sistemas modernos.

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
| `a = a * b` | **`mul`**, **`imul`** | Multiplicación (sin signo / con signo). Nota: `mul` opera sobre `RAX` por defecto, almacenando el resultado en `RDX:RAX`. `imul` puede ser más flexible. | `mul RBX` (RDX:RAX = RAX * RBX) o `imul RAX, RBX` (RAX = RAX * RBX, más flexible) |
| `a = a / b` | **`div`**, **`idiv`** | División (sin signo / con signo). El cociente va a `RAX` y el resto a `RDX`. Debes asegurarte de que `RDX` esté despejado antes de `div` para la división sin signo (ej. `xor RDX, RDX`) o contenga la extensión de signo de `RAX` para la división con signo (instrucción `cqo`). | `div RBX` (RAX = RAX / RBX, RDX = RAX % RBX) |
| `a = a % b` | (Ver `div`/`idiv`) | El resto de la división se encuentra en el registro `RDX` después de `div` o `idiv`. | Después de `div RBX`, el resultado es en `RDX`. |
| `neg a` (negación) | **`neg`** | Cambia el signo de un operando (complemento a dos). | `neg RAX` |

#### 3. Operaciones Lógicas a Nivel de Bit

| Abstracción en Alto Nivel | Ensamblador 64-bit Intel | Descripción | Ejemplo |
| :------------------------ | :----------------------- | :---------- | :------ |
| `a & b` | **`and`** | AND a nivel de bits. | `and RAX, RBX` |
| `a \| b` | **`or`** | OR a nivel de bits. | `or RAX, RBX` |
| `a ^ b` | **`xor`** | XOR a nivel de bits. A menudo usado para `RAX = 0` con `xor RAX, RAX` ya que es eficiente. | `xor RAX, RBX` |
| `~a` (NOT) | **`not`** | NOT a nivel de bits (complemento a uno). | `not RAX` |
| `a << n` | **`shl`** (shift left) | Desplazamiento a la izquierda lógico. Rellena los bits vacantes con 0s. Puede usarse para multiplicación por potencias de 2. | `shl RAX, 1` (RAX = RAX * 2) |
| `a >> n` (lógico) | **`shr`** (shift right) | Desplazamiento a la derecha lógico (rellena con 0s). Utilizado para división sin signo por potencias de 2. | `shr RAX, 1` (RAX = RAX / 2, sin signo) |
| `a >> n` (aritmético) | **`sar`** (shift right) | Desplazamiento a la derecha aritmético (mantiene el bit de signo). Utilizado para división con signo por potencias de 2. | `sar RAX, 1` (RAX = RAX / 2, con signo) |

#### 4. Comparación y Control de Flujo

| Abstracción en Alto Nivel | Ensamblador 64-bit Intel | Descripción | Ejemplo |
| :------------------------ | :----------------------- | :---------- | :------ |
| `if (cond)` | **`cmp`**, **`test`** y **`jxx`** | `cmp` (comparar) realiza una resta sin almacenar el resultado, solo establece las banderas de la CPU. `test` realiza un AND a nivel de bits sin almacenar el resultado, solo establece las banderas. `jxx` (salto condicional) utiliza estas banderas para decidir si saltar. | `cmp RAX, 10` `je label_if` |
| `==` | **`cmp`** seguido de **`je`** (saltar si igual) o **`jz`** (saltar si cero) | Compara valores. `jz` se usa a menudo después de `test` o `sub` donde el resultado de la operación es 0 si se cumplen las condiciones. | `cmp RAX, RBX` `je es_igual` |
| `!=` | **`cmp`** seguido de **`jne`** (saltar si no igual) o **`jnz`** (saltar si no cero) | Compara valores. `jnz` se usa después de `test` o `sub` donde el resultado no es cero si se cumplen las condiciones. | `cmp RAX, RBX` `jne no_es_igual` |
| `<` (con signo) | **`cmp`** seguido de **`jl`** (saltar si menor) | Compara enteros con signo. | `cmp RAX, RBX` `jl es_menor` |
| `>` (con signo) | **`cmp`** seguido de **`jg`** (saltar si mayor) | Compara enteros con signo. | `cmp RAX, RBX` `jg es_mayor` |
| `<=` (con signo) | **`cmp`** seguido de **`jle`** (saltar si menor o igual) | Compara enteros con signo. | `cmp RAX, RBX` `jle es_menor_o_igual` |
| `>=` (con signo) | **`cmp`** seguido de **`jge`** (saltar si mayor o igual) | Compara enteros con signo. | `cmp RAX, RBX` `jge es_mayor_o_igual` |
| `<` (sin signo) | **`cmp`** seguido de **`jb`** (saltar si debajo) o **`jc`** (saltar si acarreo) | Compara enteros sin signo. | `cmp RAX, RBX` `jb es_debajo_sin_signo` |
| `>` (sin signo) | **`cmp`** seguido de **`ja`** (saltar si encima) | Compara enteros sin signo. | `cmp RAX, RBX` `ja es_encima_sin_signo` |
| `<=` (sin signo) | **`cmp`** seguido de **`jbe`** (saltar si debajo o igual) | Compara enteros sin signo. | `cmp RAX, RBX` `jbe es_debajo_o_igual_sin_signo` |
| `>=` (sin signo) | **`cmp`** seguido de **`jae`** (saltar si encima o igual) o **`jnc`** (saltar si no acarreo) | Compara enteros sin signo. | `cmp RAX, RBX` `jae es_encima_o_igual_sin_signo` |
| `goto Label` | **`jmp`** (saltar) | Salto incondicional a una etiqueta. | `jmp fin_programa` |
| `function_call()` | **`call`** | Llama a una subrutina. Empuja la dirección de retorno en la pila y luego salta a la dirección de destino. | `call mi_funcion` |
| `return` | **`ret`** (retornar) | Retorna de una subrutina. Extrae la dirección de retorno de la pila y salta a ella. | `ret` |

#### 5. Interacción con el Sistema Operativo (Syscalls)

| Abstracción en Alto Nivel | Ensamblador 64-bit Intel | Descripción | Ejemplo (Linux) |
| :------------------------ | :----------------------- | :---------- | :-------------- |
| `printf()` | **`syscall`** | Llama a funciones del kernel (como `write` para imprimir en la salida estándar). Requiere preparar registros con el número de syscall específico y sus argumentos según la convención de llamada (ej. `RAX` para el número de syscall, `RDI`, `RSI`, `RDX`, `R10`, `R8`, `R9` para los argumentos). | `mov RAX, 1` (syscall write) `mov RDI, 1` (stdout) `mov RSI, msg_ptr` `mov RDX, msg_len` `syscall` |
| `exit()` | **`syscall`** | Llama a funciones del kernel para terminar el programa. | `mov RAX, 60` (syscall exit) `mov RDI, 0` (código de salida) `syscall` |

### Banderas de la CPU (Registro EFLAGS)

Después de la mayoría de las operaciones aritméticas, lógicas y de comparación, la CPU establece varias **banderas** en el **registro EFLAGS** (o RFLAGS en modo de 64 bits). Estas banderas reflejan el resultado de la operación y son utilizadas por las instrucciones de salto condicional (`jxx`).

| Flag Name (English) | Spanish Name | Abbreviation | Description (English) | Descripción (Español) |
| :------------------ | :----------- | :----------- | :-------------------- | :-------------------- |
| **Zero Flag** | **Bandera de Cero** | ZF | Set if the result of an operation is zero. Cleared otherwise. | Se establece si el resultado de una operación es cero. Se borra en caso contrario. |
| **Carry Flag** | **Bandera de Acarreo** | CF | Set if an unsigned arithmetic operation results in a carry (for addition) or a borrow (for subtraction) out of the most significant bit. Cleared otherwise. | Se establece si una operación aritmética sin signo produce un acarreo (para suma) o un préstamo (para resta) desde el bit más significativo. Se borra en caso contrario. |
| **Sign Flag** | **Bandera de Signo** | SF | Set if the most significant bit (MSB) of the result is 1 (indicating a negative result in two's complement). Cleared otherwise. | Se establece si el bit más significativo (MSB) del resultado es 1 (indicando un resultado negativo en complemento a dos). Se borra en caso contrario. |
| **Overflow Flag** | **Bandera de Desbordamiento** | OF | Set if a signed arithmetic operation results in an overflow (i.e., the result is too large/small to fit in the destination operand for signed numbers). Cleared otherwise. | Se establece si una operación aritmética con signo produce un desbordamiento (es decir, el resultado es demasiado grande/pequeño para caber en el operando de destino para números con signo). Se borra en caso contrario. |
| **Parity Flag** | **Bandera de Paridad** | PF | Set if the least significant byte of the result contains an even number of set bits (1s). Cleared otherwise. | Se establece si el byte menos significativo del resultado contiene un número par de bits (1s) activados. Se borra en caso contrario. |
| **Auxiliary Carry Flag** | **Bandera de Acarreo Auxiliar** | AF | Set if an arithmetic operation generates a carry or borrow out of bit 3 (used for BCD arithmetic). Less commonly used in general programming. | Se establece si una operación aritmética genera un acarreo o préstamo del bit 3 (utilizado para aritmética BCD). Menos común en programación general. |
| **Direction Flag** | **Bandera de Dirección** | DF | Controls the direction of string operations (e.g., `movs`, `stos`). Set to 0 for auto-increment (forward), 1 for auto-decrement (backward). | Controla la dirección de las operaciones de cadena (ej. `movs`, `stos`). Se establece en 0 para auto-incremento (hacia adelante), en 1 para auto-decremento (hacia atrás). |
