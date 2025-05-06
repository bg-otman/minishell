# 🔥 Minishell 🔥

Minishell is a minimalistic Unix shell implemented in C, replicating core behaviors of Bash with a focus on learning system calls, process handling, and parsing logic. Built as part of the 42 curriculum, this project introduces you to building your own command-line shell with custom parsing, environment management, and execution logic.

---

## 🛠️ Features

### ✅ Supported:

* Execution of binaries from PATH and with absolute/relative paths
* Built-in commands:

  * `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
* Redirections:

  * `>`, `>>`, `<`, `<<` (heredoc with correct handling of quotes and signals)
* Pipes: `cmd1 | cmd2 | cmd3`
* Environment variables: `$VAR`, including proper expansion
* Quote handling:

  * Single quotes `'` prevent expansion
  * Double quotes `"` allow expansion
* Signal handling (`Ctrl+C`, `Ctrl+D`) with prompt restoration
* Exit status propagation
* Wildcard (`*`) expansion for current directory
* Logical operators (Bonus):

  * `&&`, `||` for conditional execution
* Parentheses `( )` (Bonus) for grouped commands and prioritization

---

## 📚 Project Structure

### 1. **Lexer**

The first step splits the user input into tokens while respecting shell grammar (quotes, operators, etc.).

### 2. **Parser**

The lexer output is parsed into an **Abstract Syntax Tree (AST)** representing command execution flow.

### 3. **Execution**

The AST is traversed to execute commands:

* Pipes are forked and connected via `dup2`
* Redirections are opened and applied before command execution
* Built-ins are executed in the parent or child depending on context
* Logical operators (`&&`, `||`) are handled via AST nodes

### 4. **Heredoc Handling**

Heredocs are processed in a forked child and stored in temporary files. They respect quotes and stop on correct delimiters or on signal `SIGINT`.

### 5. **Wildcard Expansion**

When encountering `*`, minishell expands it to match filenames in the current directory using `opendir()` and `readdir()`.

---

## 🧪 Bonus Features

* ✅ Logical operators: `&&`, `||`
* ✅ Parenthesis grouping: `(...)`
* ✅ Wildcard expansion: `*`

---

## 🧑‍💻 Usage

```bash
make
./minishell
```

Type commands just like in bash:

```bash
🤖 minishell echo Hello $USER
Hello othmane

🤖 minishell ls -l | grep minishell
-rwxr-xr-x  1 othmane  staff  134528 May  6 15:42 minishell

🤖 minishell cat << EOF
Hello minishell
EOF
Hello minishell

🤖 minishell mkdir test && cd test || echo fail

🤖 minishell (echo one && echo two) || echo three
one
two

🤖 minishell echo *
file1.txt file2.c minishell README.md

💀 minishell ls no_such_file
ls: cannot access 'no_such_file': No such file or directory
```

---

## ⚠️ Signals

* `Ctrl+C` interrupts the current input or heredoc and restores the prompt
* `Ctrl+D` exits the shell or ends input when appropriate

---


## 👨‍👩‍👧 Authors

This project was developed collaboratively by a team of students at \[1337 School / 42 Network].

@bg-otman

@Aymanesaj



