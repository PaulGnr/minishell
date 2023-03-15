# Minishell

Minishell is a shell implementation project that enables communication with a computer using interactive lines of commands similar to human language. This project was an opportunity to explore the history of shells and travel back to the time when Windows didn't exist.

## Features

- **Display a prompt** when waiting for a new command.
- **History:** Minishell has a working history.
- **Path:** It searches and launches the right executable based on the PATH variable or using a relative or absolute path.
- **Single quotes:** It handles single quotes to prevent the shell from interpreting meta-characters in the quoted sequence.
- **Double quotes:** It handles double quotes to prevent the shell from interpreting meta-characters in the quoted sequence, except for the dollar sign.
- **Redirections:** Minishell implements input/output redirections. The less than symbol (<) redirects input, while the greater than symbol (>) redirects output. The double less than symbol (<<) is given a delimiter, and it reads input until it sees a line containing the delimiter. The double greater than symbol (>>) redirects output in append mode.
- **Pipes:** It implements pipes (| character), where the output of each command in the pipeline connects to the input of the next command through a pipe.
- **Environment variables:** It handles environment variables, where a dollar sign followed by a sequence of characters expands to their values.
- **Exit status:** It handles $? expansion, where it expands to the exit status of the most recently executed foreground pipeline.
- **Signal handling:** It handles ctrl-C, ctrl-D, and ctrl-\\, where they behave the same way as they do in bash.

## Built-ins

Minishell implements built-ins like:
- **echo** with the option -n
- **cd** with only a relative or absolute path
- **pwd** with no options
- **export** with no options
- **unset** with no options
- **env** with no options or arguments
- **exit** with no options.

___

Thank you for choosing Minishell. We hope you enjoy using it!
