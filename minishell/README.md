# Minishell

A simple shell implementation in C, developed as part of the 42 School curriculum.

## 📚 Project Description

This project is about creating a minimal Unix shell capable of parsing and executing commands with features like pipes, redirections, environment variables, and built-in functions. The objective is to deepen understanding of system calls, process handling, and terminal behavior.

> This repository is maintained privately for educational purposes and team collaboration.

---

## 🧠 Features

- Interactive prompt that waits for user input
- Tokenization and parsing of simple command lines
- Execution of binary and built-in commands
- Support for the following redirections:
  - `>`: output redirection
  - `<`: input redirection
  - `>>`: append output
  - `<<`: here-document (heredoc)
- Pipe support (`|`)
- Environment variable management
- Handling of exit status (`$?`)
- Basic signal handling (`Ctrl+C`, `Ctrl+\`, `Ctrl+D`)

---

## ⚙️ Built-in Commands

- `echo`
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

---

## 👥 Team Members

- Samet Can İncesu - [@sincesu](https://github.com/sincesu)
- Mert Özcan - [@iammertozcan](https://github.com/iammertozcan)
