# Exit Codes in Minishell

In a shell, exit codes are crucial for indicating command success/failure. Here's what you should do with exit codes in your minishell:

## 1. Global Exit Status Variable

You already have this declared in your header:
```c
extern int g_exit_status;
```

You need to define it in one of your `.c` files (usually `main.c`):
```c
int g_exit_status = 0;
```

## 2. Update Exit Status After Each Command

In your `which_buildin_command` function, make sure to capture the return value of each command and update the global `g_exit_status`:

```c
void which_buildin_command(char **input, t_env **my_env, char **array_env)
{
    extern int g_exit_status;

    if (ft_strncmp(input[0], "echo", 4) == 0)
        g_exit_status = echo_command_implementation(input);
    else if (ft_strncmp(input[0], "pwd", 3) == 0)
        g_exit_status = pwd_command_implementation(*my_env);
    else if (ft_strncmp(input[0], "export", 6) == 0)
        g_exit_status = export_command_implementation(input, my_env, array_env);
    else if (ft_strncmp(input[0], "unset", 5) == 0)
        g_exit_status = unset_command_implementation(my_env, input);
    else if (ft_strncmp(input[0], "cd", 2) == 0)
        g_exit_status = cd_command_implementation(input, *my_env);
    else if (ft_strncmp(input[0], "exit", 4) == 0)
        exit_command_implementation(input, g_exit_status);
    else if (ft_strncmp(input[0], "env", 3) == 0)
    {
        print_my_env(*my_env);
        g_exit_status = 0; // env command always succeeds
    }
}
```

## 3. Handle Non-Builtin Commands

For commands that are not built-in, set appropriate exit codes:

```c
void what_command(char** input, t_env **my_env, char** array_env)
{
    extern int g_exit_status;

    if (is_command_buildin(input))
        which_buildin_command(input, my_env, array_env);
    else
    {
        // For non-builtin commands, you'll need to implement execve
        // and capture the exit status from the child process
        g_exit_status = 127; // Command not found (temporary)
        printf("minishell: %s: command not found\n", input[0]);
    }
}
```

## 4. Common Exit Codes You Should Use

Here are the standard exit codes your commands should return:

### Builtin Commands:
- **0**: Success
- **1**: General error (invalid arguments, permission denied, etc.)
- **2**: Misuse of shell builtin (syntax error)

### For `cd`:
- **0**: Success
- **1**: Directory doesn't exist, permission denied, etc.

### For `export`:
- **0**: Success
- **1**: Invalid identifier

### For `unset`:
- **0**: Success (even if variable doesn't exist)
- **1**: Invalid identifier

### For external commands:
- **127**: Command not found
- **126**: Command found but not executable
- **1-255**: Whatever the command returns

## 5. Special Variables

You might also want to implement these special variables:
- **`$?`**: Should expand to the exit status of the last command
- **`$$`**: Should expand to the process ID of the shell

## 6. Example Usage

After implementing this, users can check exit status:
```bash
Minishell % export VALID_VAR=value
Minishell % echo $?  # Should print 0
Minishell % export 123INVALID
Minishell % echo $?  # Should print 1
```

## 7. Implementation Notes

- Every command should update `g_exit_status`
- The `g_exit_status` should be accessible via `$?` expansion
- For external commands, use `fork()` and `waitpid()` to capture child process exit status
- The shell itself should exit with the last command's exit status when `exit` is called without arguments

The key is that every command should update `g_exit_status`, and this value should be accessible via `$?` expansion later.




______________________________________________________________________________

tester
cd minishell
git clone https://github.com/LucasKuhn/minishell_tester.git
cd minishell_tester
./tester
