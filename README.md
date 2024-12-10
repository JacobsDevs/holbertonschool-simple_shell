<picture>
 <source media="(prefers-color-scheme: dark)" srcset="YOUR-DARKMODE-IMAGE">
 <source media="(prefers-color-scheme: light)" srcset="YOUR-LIGHTMODE-IMAGE">
 <img alt="YOUR-ALT-TEXT" src="YOUR-DEFAULT-IMAGE">
</picture>

# __Introduction__
This project is a simple UNIX command-line interpreter, or shell, built as part of a C programming curriculum. The shell replicates basic functionalities of standard shells like sh or bash.

Features
Display a prompt and wait for user input.
Execute built-in commands like exit and env.
Execute system commands found in PATH.
Handle command arguments.
Implement input redirection (<), output redirection (>), and piping (|).
Manage process creation and termination.
Requirements
All C source files are compiled with gcc using -Wall -Werror -Wextra -pedantic -std=gnu89.
The shell runs onUbuntu 20.04 LTS.
