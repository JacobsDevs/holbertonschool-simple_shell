<picture>
 <img alt="Holberton Logo" src="./Holberton LinkedIn Cover FINAL.png">
</picture>
<hr>

# __HOLBERTON SCHOOL: SIMPLE SHELL__
<hr>

## __./hsh (Holberton Shell)__
This project is a simple UNIX command-line interpreter, or shell, built as part of a C programming curriculum. <br>The shell replicates basic functionalities of standard shells like `sh` or `bash`.
<hr>

## __Table of Contents__
1. [Features](#features)
2. [Requirements](#requirements)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Built-in commands](#built-in-commands)
6. [Examples](#examples)
7. [Authors](#authors)

<hr>

## __Features__
- Display a prompt and wait for user input.
- Execute built-in commands like `exit` and `env`.
- Execute system commands found in PATH.
- Handle command arguments.
- Implement input redirection (`<`), output redirection (`>`), and piping (`|`).
- Manage process creation and termination.
<hr>

## __Requirements__
- All C source files are compiled with `gcc` using `-Wall -Werror -Wextra -pedantic -std=gnu89`.
- The shell runs on Ubuntu 20.04 LTS.
___

## __Installation__
1. Clone the repository:
```
git clone https://github.com/username/simple_shell.git
```
2. Compile the source files:
```
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```
___

## __Usage__
1. Launch the shell:
```
./hsh
```
2. Use commands like:
```
ls -l
pwd
echo "Hello, World!"
exit
```
___

## __Built-in commands__
- `exit [status]` - Exit the shell with an optional status code.
- `env` - Print the current environment variables.
___

## __Examples__
```
$ ./hsh
$ ls -la
$ echo "Simple shell project"
$ exit 0
```
___

## __Authors__
- Dew Doan <bongban2003@gmail.com>
- Jacob Phelan <Jacobsdevsmail@gmail.com>
- Michael Ludice <Vaetal98@gmail.com>
___
