/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:14:46 by omougel           #+#    #+#             */
/*   Updated: 2024/06/25 16:26:39 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"

void	ft_exit(t_minishell *msh);
void	do_builtins(char **cmd, t_ht_table *env, t_minishell *sh);
int		check_input(t_minishell *msh, char **input_redir, int fd_in);
int		check_output(char **output_redir, int fd_out);
char	**find_command(char **cmd, t_minishell *sh);
void	echo(char **cmd, int fd_out);
void	pwd(char **cmd, t_minishell *sh, int fd_out);
void	bt_env(char **cmd, t_ht_table *env, int fd_out, t_minishell *sh);
void	bt_exit(char **cmd, t_minishell *msh);
void	execute_correct_exit(t_minishell *msh);
void	cd(char **cmd, t_ht_table *env);
char	*ft_strjoin_cmd(char const *s1, char const *s2);
char	*expend_heredoc(t_minishell *msh, char *buffer);
int		here_doc(t_minishell *msh, char *lim, char *quoted);
int		redir_input(char *infile);
int		redir_output(char *outfile);
int		append_output(char *outfile);
int		is_input(char *redir);
int		is_output(char *redir);
int		is_builtin(char *cmd);
int		is_there_pipe(char ***cmd_tab);
int		is_lim(char *buffer, char *lim);
void	exec_cmd(char **cmd, t_minishell msh);
void	secure_close(int *fd_out, int *fd_in, int *pipe_out, int *pipe_in);
size_t	keylen(char *str);
size_t	valuelen(char *str);
char	**replacefront(char **cmd, char *path);
int		go_to_next_pipe(char ***cmd_tab);
int		export_error(char *key, char *value, t_ht_table *env);
void	err_msg(t_minishell *msh);
int		read_path(int i, char *path, char *newpwd);
int		set_oldpwd(char *newpwd, t_ht_table *env);
int		prev(char *newpwd);
int		next(char *path, char *newpwd);
#endif
