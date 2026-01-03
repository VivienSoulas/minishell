# minishell - A Minimal POSIX Shell

A compact shell that recreates essential POSIX behaviors: command parsing, pipelines, redirections, heredocs, builtins, and signal handling. The implementation focuses on disciplined memory management to prevent cascading failures during long-running interactive sessions.

## Overview

minishell interprets user input, builds an abstract representation of commands, and executes them with proper process control and I/O redirection.

## Core Features

- Command execution with environment variable expansion (including special parameters like `$?`)
- Pipelines with correct stdin/stdout wiring
- Input/output redirections (`>`, `>>`, `<`)
- Heredocs with delimiter handling and signal awareness
- Builtins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Exit status propagation across pipelines
- Signal handling for interactive use (e.g., `Ctrl+C`, `Ctrl+\`, `Ctrl+D`)

## Memory Management & Failure Containment

The primary engineering challenge is preventing memory leaks and ensuring that any allocation failure does not cascade through the shell lifecycle. The project addresses this by:
- Owning every allocation explicitly and freeing all transient data at the end of each command loop iteration
- Centralizing cleanup paths so errors unwind resources in a single place
- Validating allocations and inputs before use; if validation fails, execution is stopped for that command but the shell remains responsive
- Separating parsing structures from execution structures to avoid partial frees or double frees

This discipline keeps the shell stable even under sustained interactive use or under intentional misuse.

## Parsing and Execution Pipeline

1. **Lexing**: Tokenize input while respecting quotes and escape rules.
2. **Parsing**: Build command nodes with arguments, redirections, and pipeline links.
3. **Expansion**: Substitute environment variables and handle special parameters.
4. **Execution**: Run builtins in-process when possible; otherwise, fork/exec external commands with the correct file descriptor setup.
5. **Cleanup**: Release all per-command allocations before the next prompt.

## Redirections and Heredocs

- Supports `>`, `>>`, and `<` with proper error reporting if files cannot be opened
- Heredocs capture input until the delimiter is seen; signals during heredoc are handled to avoid leaving stale temporary data

## Signals

- `Ctrl+C` interrupts the current command and returns a fresh prompt
- `Ctrl+\` is ignored in the prompt but propagated correctly to child processes
- `Ctrl+D` (EOF) exits the shell cleanly, releasing resources

## Building & Running

```bash
make
./minishell
```

## Learning Outcomes

- Memory ownership discipline in a long-lived interactive process
- Robust error handling that prevents small failures from escalating
- Process control, forking, and file descriptor management for pipelines
- Practical parsing: tokenization, quoting, expansion, and syntax validation

---

*A 42 School project showcasing shell fundamentals with a focus on memory safety and failure isolation.*
