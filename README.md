*This project has been created as part of the 42 curriculum by dtereshc and olcherno.*

<div align="center">

# 🐚 minishell

**A POSIX-flavoured Unix shell, written from scratch in C.**

*Prompt · tokenizer · parser · expander · executor — no `system()`, no shortcuts.*

![C](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c)
![42](https://img.shields.io/badge/42-Prague-000000?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS-lightgrey?style=flat-square)
![readline](https://img.shields.io/badge/GNU-readline-blue?style=flat-square)
![Built-ins](https://img.shields.io/badge/built--ins-7-orange?style=flat-square)

</div>

---

## 📖 Description

`minishell` is a small but complete command interpreter — our own little **bash**.

It reads a line from the terminal, breaks it into tokens, resolves quoting and
variable expansion, builds an executable command pipeline, wires up file
descriptors and processes with `fork`/`pipe`/`dup2`/`execve`, and finally
reports an exit status — exactly the way a real shell does.

The goal of the project is to understand what actually happens between pressing
**Enter** and seeing output: **process creation, file descriptor inheritance,
signal handling and inter-process communication**.

Everything is implemented by hand in C99 with only the allowed system calls.
No `system()`, no `popen()`, no external parsing library.

```console
minishell$ cat Makefile | grep -c "^" > lines.txt ; wc -l < lines.txt
minishell$ export USER_GREETING="hello" && echo "$USER_GREETING, $USER ($?)"
hello, dtereshc (0)
```

---

## ✨ Features

| Area | What is supported |
|:--|:--|
| **Prompt & history** | Interactive prompt via GNU `readline`, persistent history in `.minishell_history` |
| **Execution** | Binary lookup through `PATH`, plus relative and absolute paths |
| **Pipes** | Arbitrarily long pipelines `cmd1 \| cmd2 \| cmd3 …` with correct fd plumbing |
| **Redirections** | `<` input, `>` output, `>>` append, `<<` heredoc with delimiter |
| **Quoting** | `'single'` disables all interpretation, `"double"` keeps `$` expansion alive |
| **Expansion** | `$VAR` environment expansion and `$?` — the last foreground exit status |
| **Built-ins** | `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, `exit` |
| **Signals** | `ctrl-C` fresh prompt, `ctrl-D` clean exit, `ctrl-\` ignored — bash-identical |
| **Exit codes** | Faithful status propagation: `127` not found, `126` not executable, `130`/`131` on signals |
| **Memory** | Every allocation is owned and freed; a `valgrind` suppression file for `readline` internals ships with the repo |

---

## 🧠 How it works

A command line travels through five clearly separated stages, each living in its
own group of source files:

```
   "echo $HOME | wc -c > out.txt"
              │
    ┌─────────▼──────────┐
    │  1. VALIDATION     │   validate_input_*.c
    │     unclosed quotes, stray  |  ; \  <<<  redirections
    └─────────┬──────────┘
    ┌─────────▼──────────┐
    │  2. TOKENIZER      │   tokenizer*.c
    │     → t_input list: WORD | PIPE | RDR_IN | RDR_OUT | APPND | HERE
    └─────────┬──────────┘
    ┌─────────▼──────────┐
    │  3. EXPANDER       │   dollar_ls_*.c
    │     $VAR and $? resolved, quote-aware, length pre-computed
    └─────────┬──────────┘
    ┌─────────▼──────────┐
    │  4. COMMAND LIST   │   crt_cmnd_ls*.c
    │     → t_cmnd list: argv[] + its own t_rdrs redirection list
    └─────────┬──────────┘
    ┌─────────▼──────────┐
    │  5. EXECUTOR       │   what_command.c · pipes*.c · implem_redir*.c
    │     built-in?  → run in the parent (so `cd`/`export` persist)
    │     external?  → fork + dup2 + execve, parent waits, status kept
    └────────────────────┘
```

**Design notes**

- **Environment as a linked list.** `t_env` (key/value nodes) is the source of
  truth; a flat `char **` array is rebuilt only when `execve` needs one. That
  makes `export`, `unset` and appending (`VAR+=value`) trivial and leak-free.
- **Built-ins run in the parent process** when they are alone in the pipeline,
  otherwise the shell could never change its own directory or environment.
  Inside a pipeline they run in the child, like bash does.
- **Heredocs are collected before execution** into temporary files, with their
  own `SIGINT` handler so `ctrl-C` aborts the heredoc, not the shell.
- **Exactly one global variable** — `g_exit_status` — as the subject demands.
  The signal handlers touch nothing else: no data structures, no allocations.
- **stdin/stdout are backed up with `dup`** before every command and restored
  afterwards, so a failed redirection can never corrupt the interactive shell.

---

## 🚀 Instructions

### Requirements

- `cc` / `clang` or `gcc`, and `make`
- **GNU readline** development files

```bash
# Debian / Ubuntu
sudo apt install libreadline-dev

# macOS (Apple's libedit is *not* GNU readline)
brew install readline
```

> The Makefile auto-detects a Homebrew `readline` on macOS and falls back to the
> system one on Linux — no manual path editing required. Run `make info` to see
> what it picked.

### Build & run

```bash
git clone git@github.com:DT-sudo/minishell.git
cd minishell
make
./minishell
```

### Makefile targets

| Target | Description |
|:--|:--|
| `make` | Build `libft`, `libftprintf` and the shell |
| `make clean` | Remove object files |
| `make fclean` | Remove objects, archives and the binary |
| `make re` | Full rebuild |
| `make run` | Build, then launch the shell |
| `make debug` | Rebuild with `-g3 -DDEBUG` |
| `make fsanitize` | Rebuild with AddressSanitizer + UBSan |
| `make leaks` | Run under `valgrind` with the readline suppression file |
| `make norm` | Run `norminette` over the whole codebase |
| `make info` / `make help` | Show the detected build setup / all targets |

Incremental builds are dependency-tracked (`-MMD -MP`), so touching a header
recompiles exactly the files that need it — and nothing relinks unnecessarily.

---

## 🎬 Usage examples

```console
minishell$ echo -n "no newline here"
no newline here
minishell$ export GREET="hello world" && echo "$GREET" | tr a-z A-Z
HELLO WORLD

minishell$ cat << EOF > note.txt
> minishell can do heredocs
> EOF
minishell$ cat < note.txt
minishell can do heredocs

minishell$ ls src | grep "pipe" | wc -l
       6
minishell$ /bin/echo 'single quotes keep $HOME literal'
single quotes keep $HOME literal

minishell$ nosuchcommand
bash: nosuchcommand: command not found
minishell$ echo $?
127
```

---

## 🗂️ Project structure

```
minishell/
├── Makefile                    self-configuring, colourised, dependency-tracked
├── minishell.h                 structures + every prototype
├── minishell2.h                forward declarations, keeps the norm happy
├── readline.supp               valgrind suppressions for readline internals
├── libs/
│   ├── libft/                  our own libc subset (strings, lists, GNL)
│   └── libftprintf/            our own printf / fprintf
└── src/
    ├── main*.c                 REPL loop, shell init, cleanup
    ├── validate_input_*.c      syntax checks before anything is allocated
    ├── tokenizer*.c            lexer → typed token list
    ├── dollar_ls_*.c           $VAR / $? expansion engine
    ├── crt_cmnd_ls*.c          token list → command list
    ├── what_command*.c         dispatcher: built-in vs external
    ├── pipes*.c                fork/pipe/dup2 pipeline execution
    ├── implem_redir*.c         redirections + heredocs
    ├── free_funcs_*.c          every allocation has a matching free
    ├── signal.c                SIGINT / SIGQUIT handling
    └── buildin_commands/       echo · cd · pwd · export · unset · env · exit
```

---

## 🛠️ Technologies & concepts

<div align="center">

| | |
|:--|:--|
| **Language** | C, compiled with `-Wall -Wextra -Werror` under the 42 Norm |
| **Build** | GNU Make — auto platform detection, `-MMD -MP` header dependencies, recursive sub-library builds |
| **Libraries** | GNU `readline` / `history`; our own `libft` and `ft_printf` |
| **Processes** | `fork`, `execve`, `waitpid`, exit-status decoding (`WIFEXITED`, `WTERMSIG`) |
| **IPC & I/O** | `pipe`, `dup`, `dup2`, `open`, `close`, `access`, `unlink` |
| **Signals** | `signal`, `sigaction`, `SIGINT` / `SIGQUIT`, readline redisplay hooks |
| **Data structures** | Singly linked lists for tokens, commands, redirections and the environment |
| **Tooling** | `valgrind` (+ suppression file), AddressSanitizer, `norminette`, Git |

</div>

---

## 📚 Resources

- **GNU Bash Reference Manual** — the behavioural reference for every edge case
  → <https://www.gnu.org/software/bash/manual/bash.html>
- **GNU Readline Library documentation** — prompt, history, `rl_*` redisplay API
  → <https://tiswww.case.edu/php/chet/readline/readline.html>
- **Advanced Programming in the UNIX Environment**, W. R. Stevens — chapters on
  process control, process relationships and signals
- **The Linux Programming Interface**, M. Kerrisk — pipes, file descriptors,
  terminal handling
- `man` pages: `execve(2)`, `pipe(2)`, `dup2(2)`, `waitpid(2)`, `sigaction(2)`,
  `readline(3)`

### Use of AI

AI assistance was used as a **support tool**, never as a source of unreviewed code:

- **Documentation** — drafting this `README.md` and inline comments.
- **Build tooling** — refining the `Makefile` (platform detection for readline,
  dependency tracking, output formatting).
- **Rubber-ducking & review** — explaining `readline` redisplay behaviour inside
  signal handlers, comparing our exit statuses against bash, and suggesting edge
  cases to test (unclosed quotes, `$?` inside double quotes, heredoc interruption).

Every suggestion was read, tested and rewritten by us to fit the project's
architecture and the 42 Norm. The parsing, expansion and execution logic is our
own work — we can explain and defend every line of it.

---

## 👥 Authors

| | 42 login | GitHub |
|:--|:--|:--|
| 🧑‍💻 | **dtereshc** | [@DT-sudo](https://github.com/DT-sudo) |
| 🧑‍💻 | **olcherno** | — |

<div align="center">
<sub>Built at <b>42 Prague</b> · <i>“As beautiful as a shell.”</i></sub>
</div>
