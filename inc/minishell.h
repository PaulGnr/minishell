/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:18:37 by sgaubert          #+#    #+#             */
/*   Updated: 2023/03/01 17:22:48 by paulguign        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../src/libft/src/libft.h"

typedef int	t_bool;
typedef int	(*t_pipe)[2];

extern int	g_exit_status;

typedef struct s_point
{
	int	i;
	int	j;
}	t_point;

typedef struct s_cmd
{
	char			*cmd;
	char			**split_cmd;
	int				pid;
	int				fd_in;
	int				fd_out;
	struct s_redir	*redir;
}	t_cmd;

typedef struct s_redir
{
	int				mode;
	char			*str;
	int				fd;
	struct s_redir	*next;
}	t_redir;

enum e_redir_mode
{
	OUT_TRUNC = O_TRUNC,
	OUT_APPEND = O_APPEND,
	IN_FILE,
	IN_LIMITER
};

enum e_flag
{
	ERROR = -1,
	FAIL = 0,
	SUCCESS = 1
};

typedef struct s_root
{
	int				nb_of_cmd;
	char			**shell_env;
	struct s_list	*env;
	t_pipe			pipe_fd;
	t_cmd			*cmds;
}	t_root;

typedef int	(*t_builtin)(t_cmd *cmd, t_root *root);

int			exec_all_cmd(t_cmd *cmds, int nb_of_cmd, t_root *root);
int			free_split_cmd(t_cmd *cmds, int nb_of_cmd);

t_bool		find_cmd(char *cmd, char **cmd_path, t_root *root);
int			exec_cmd(t_cmd *cmd, t_root *root);

t_builtin	detect_builtin(t_cmd *cmd);
int			exec_builtin(int (*builtin)(t_cmd *cmd, t_root *root),
				t_cmd *cmd, t_root *root);

char		**ft_expansion(char **str, t_list *env);
char		**ft_expansion_var(char **split, char *var, t_point *p, int quote);
int			ft_new_split(char ***split, t_point p, char *var, int size);
char		**ft_new_split_expansion(char **split, int i, int j);
char		**ft_double_free(char **s1, char **s2);
int			ft_add_back_split(char **dup, char **split, char *var, t_point p);
int			ft_add_front_split(char **dup, char **split, char *var, t_point p);
int			ft_end_split(char ***dup, char **split, int i, int size);
int			ft_end_new_split(char ***split, char **dup, int ret);
char		**ft_remove_quote(char **split, t_point *p, int quote, t_list *env);
char		*ft_remove_str(char **split, char *str, int pos, int size);
char		*ft_insert_str(char **split, char *s1, char *s2, int pos);
char		**ft_remove_case(char **split, int pos, char *var_name);
char		*ft_get_var_name(char *str);
int			ft_size_var(char *var);
char		*get_env(char *var_name, t_list *env);
char		*ft_expansion_heredoc(char *str, t_list *env);
char		*ft_remove_str_heredoc(char *str, int pos, int size);
char		*ft_insert_str_heredoc(char *s1, char *s2, int pos);
char		*expansion_redir(char *str, t_list *env);

int			find_last_fd_in_or_out(t_redir *redir, int test_one, int test_two);
int			select_fd_in(t_cmd *cmd, int cmd_index, int (*pipe_fd)[2]);
int			select_fd_out(t_cmd *cmd, int cmd_index, int (*pipe_fd)[2],
				int nb_of_cmd);

int			open_heredoc(t_cmd *cmds, t_root *root);
int			read_heredoc_pipe(char *limiter, t_root *root);
int			open_fd(t_redir *redir, t_root *root);
char		*ft_get_limiter(char *str);
void		close_fd(t_redir *redir);
t_pipe		open_pipe(int nb_of_cmd);
void		close_pipe(int (*pipe_fd)[2], int nb_of_cmd);

t_bool		error_catch(t_bool test, char *str, char *error_msg);
t_bool		not_a_valid_identifier(t_bool test, char *fct_name,
				char *identifier);

void		ft_check_quote(char c, int *quote);
int			ft_check_str(char *str);
int			ft_get_mode(char *s);
char		*ft_get_first_file(char *s);
char		*ft_get_other_files(char *s);
t_cmd		*ft_parser(char *str, t_root *root);
int			ft_splitlen(char **split);
char		**ft_split_quote(const char *s, char c);
char		**ft_split_chevron(const char *s);
char		*ft_strjoin_malloc(char *s1, char *s2);

int			create_env(char **envp, t_root *root);
int			update_shell_env(t_root *root);

int			ft_env(t_cmd *cmd, t_root *root);
int			ft_export(t_cmd *cmd, t_root *root);
int			ft_unset(t_cmd *cmd, t_root *root);
int			ft_cd(t_cmd *cmd, t_root *root);
int			error_catch_cd(char *path, char *err_msg);
char		*ft_get_pwd(void);
char		*ft_get_path(char *str, t_list *env);
int			ft_try_with_cdpath(t_list *env, char *path);
int			free_path_pwd(char *path, char *pwd);
int			ft_no_pwd(t_root *root);
int			ft_modify_pwd(t_root *root, char *path);
int			ft_echo(t_cmd *cmd, t_root *root);
int			ft_pwd(t_cmd *cmd, t_root *root);
int			ft_exit(t_cmd *cmd, t_root *root);

int			export_without_arg(t_list *env, t_cmd *cmd);

int			sig_handling_parent_proc(void);
int			sig_handling_child_proc(void);
int			sig_handling_heredoc_proc(void);

t_cmd		init_cmd(void);
void		ft_free_cmds(t_cmd *cmds, t_root *root);
int			ft_free_split(char **split);
char		**ft_free_split_char(char **split);
t_cmd		*ft_free_split_cmd(char **split);

#endif
