# 🐚 Minishell

Welcome to Minishell, a simplified recreation of a Linux shell! This project, developed at 42 Madrid, is designed to provide hands-on experience with process management, file descriptors, and fundamental shell functionalities.

# 📜 Table of Contents

- [📖 About the Project](#id1)

- [💡 Problem Statement](#id2)

- [⚙️ How It Works](#id3)

- [🚀 Features](#id4)


# 📖 About the Project<a name="id1"></a>

Minishell is a project aimed at building a minimalistic shell, mimicking essential features of Bash. It provides an opportunity to delve into UNIX process management, system calls, and the intricate workings of a shell.

This project is part of the curriculum at 42 Madrid and follows strict guidelines to encourage low-level programming skills, error handling, and robust software development practices.

Shells are the backbone of UNIX-like operating systems, acting as an interface between users and the system. Understanding how a shell works at a fundamental level is crucial for system programming, security, and performance optimization.

Minishell aims to provide a deep understanding of:

How processes are created and managed.

The role of file descriptors in input/output redirection.

Signal handling and built-in command execution.

Implementing pipelines and environment variable management.

# ⚙️ How It Works<a name="id3"></a>

Minishell functions similarly to Bash but with a limited scope. It handles user input, parses commands, executes built-in functions, and manages processes effectively. Key elements include:

**Lexing & Parsing**: User input is tokenized and structured into commands.

Execution: The shell handles both built-in commands and external programs.

Process & File Descriptor Management: Redirections and pipes are implemented using system calls.

Signal Handling: Properly managing signals like Ctrl+C, Ctrl+D, and Ctrl+Z.

Environment Handling: Managing $PATH, custom variables, and command execution.

# 🚀 Features<a name="id4"></a>

- ✅ Basic command execution (like ls, echo, cat).
- ✅ Built-in commands (cd, pwd, export, unset, env, exit).
- ✅ Redirections (>, >>, <).
- ✅ Pipes (|).
- ✅ Signal handling (Ctrl+C, Ctrl+D, Ctrl+Z).
- ✅ Environment variable management.
