# Libasm
Summary: The aim of this project is to get familiar with assembly language.

# Assembly Language / Lenguaje Ensamblador

---

## English 🇬🇧

An assembly (or assembler) language, often abbreviated asm, is a low-level programming language for a computer, or other programmable device, in which there is a very strong (but often not one-to-one) correspondence between the language and the architecture’s machine code instructions. Each assembly language is specific to a particular computer architecture. In contrast, most high-level programming languages are generally portable across multiple architectures but require interpreting or compiling. Assembly language may also be called symbolic machine code.

---

## Español 🇪🇸

Un lenguaje ensamblador (o de ensamblaje), a menudo abreviado asm, es un lenguaje de programación de bajo nivel para una computadora, u otro dispositivo programable, en el que existe una correspondencia muy fuerte (pero a menudo no uno a uno) entre el lenguaje y las instrucciones de código máquina de la arquitectura. Cada lenguaje ensamblador es específico de una arquitectura de computadora particular. Por el contrario, la mayoría de los lenguajes de programación de alto nivel son generalmente portátiles entre múltiples arquitecturas, pero requieren interpretación o compilación. El lenguaje ensamblador también puede denominarse código máquina simbólico.


# Project Libasm - Subject / Project Subject

---

## English 🇬🇧

### Common Instructions

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

---

## Español 🇪🇸

### Instrucciones Comunes

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
