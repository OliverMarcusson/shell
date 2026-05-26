# shell
This project is an implementation of a simple linux shell written completely in the C programming language. It is written as an assignment for the course `CH101U` from KTH.

## Build
### Dependencies
- `gcc`
- `make`

The project also depends on `GLIBC`.

The project's `Makefile` exposes two targets:
- `make` - Compiles the shell to the binary `cmd`.
- `make clean` - Deletes the `cmd` binary.

## Usage
```sh
./cmd
```
Spawns the shell.

## Commands
The shell supports the following commands:
- `echo args...`: Prints the supplied strings to the console. A maximum of 7 strings are supported.
- `pwd`: Prints the current working directory.
- `ls <optional-path>`: Lists the files and directories present at the provided path. Defaults to the current working directory if no path is specified.
- `cd <optional-path>`: Changes the working directory to the specified path. Defaults to the path in the HOME environment variable if no path is specified.
- `man <command>`: Prints the description for the specified command.
- `cat <path>`: Prints the contents of the file at the specified path.  
- `head <path> <optional-line-count>`: Prints the first n lines of the file at the specified path, where n is the specified line count. Defaults to 10 lines if no line count is specified.
- `touch <path>`: Creates a new file at the specified path.
- `rm <path>`: Deletes the file at the specified path.
- `cp <source> <destination>`: Copies the file at the source path to the destination path.
- `mv <source> <destination>`: Renames and/or moves the source file to the specified destination.
- `help`: Prints the help message.
- `exit`: Exits the shell.
- `clear`: Clears the console.
