/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 14:27:06 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/23 14:01:27 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHELL_H
# define FT_SHELL_H
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "../libft/includes/libft.h"
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>

# define HISTORY_COUNT		15
# define MAX_HASH_SIZE		4096
# define BAD_ACCESS			2
# define SUCCESS			1
# define NO_SUCH			1
# define IS_DIR				3
# define NO_CMD				4
# define ARGWL(x) x != '\0' && x != ' ' && x != '\t' && x != ';' && x != '|'
# define KEY(x) x == 8 || x == 127 || x == 27 || x == 9 || x == 18
# define KEY2(x) x == 11 || x == 12
# define QUOTE(x) x == '\'' || x == '\"' || x == '`'
# define SPEC(x) x == ';' || x == '|' || x == '>' || x == '<' || x == '&'
# define MYCMD(x) ft_strequ(x, "cd") || ft_strequ(x, "setenv")
# define MYCMD2(x) ft_strequ(x, "unsetenv")

t_list			*g_hist;
pid_t			g_proc;
int				g_width;
int				g_height;
int				g_success;

typedef struct termios	t_term;
typedef struct dirent	t_dirent;

typedef struct	s_quote
{
	int		es;
	int		dq;
	int		sq;
	int		bq;
}				t_quote;

typedef struct	s_cap
{
	char	*tgo;
	char	*left;
	char	*deline;
	int		x;
	int		y;
	int		mx;
	int		my;
}				t_cap;

typedef struct	s_inp
{
	int		ind;
	char	*arg;
	int		hist;
	char	*hst;
	t_list	*cpl;
	int		cplind;
	int		cplen;
	int		cplprev;
}				t_inp;

typedef struct	s_item
{
	char			*name;
	char			*value;
	struct s_item	*next;
}				t_item;

typedef struct	s_hash
{
	int		size;
	t_item	**table;
}				t_hash;

typedef	struct	s_read
{
	char			*cmd;
	int				linez;
	int				size;
	int				work;
	int				remember_insert;
	int				pos;
	int				heredoc;
	int				height;
	int				width;
	char			key[1];
	char			key_extended[5];
	char			cpy[1024];
	char			**env;
	struct s_hash	*hash;
	int				cursor_start;
	int				his_pos;
	char			*prompt;
	char			**his;
}				t_read;

typedef struct	s_sh
{
	int				terminal;
	int				is_interactive;
	pid_t			pgid;
	char			**history;
	struct s_read	*read;
	char			*prompt;
	char			**env;
	struct termios	term;
	struct termios	term_backup;
}				t_sh;

typedef int		(*t_action) (t_read *read);

typedef struct	s_spec_keys
{
	t_action	function;
	int			value[5];
}				t_spec_keys;

t_hash			*g_hash;
t_sh			*g_shell;

typedef struct	s_fds
{
	int		fd[2];
	int		in;
	int		close;
	int		open;
	int		file;
	int		hdoc;
	char	*hered;
	int		mem1;
	int		mem2;
	int		mem3;
	int		ex[2];
}				t_fds;

int				ft_arrlen(char **array);
char			**dup_env(char **envi);
int				make_glob(t_list **lst);
int				need_glob(char *str);
void			push_n_glob(t_list *st, char *s, char *path);
void			parse_file_tool(t_list **new, char *name, char *path);
int				file_valid(char *file, char *s);
int				file_is_dir(char *path, char *name);
void			figure_glob(t_list *st, char *s, char *path);
int				msh_logical(t_list *split, char ***env);
int				ft_chrlen(char *str, char c);
int				find_env_var(char *n, char **env);
void			execute_command(char *cmd, char **argv, char **env);
void			make_hash_table(char **env);
t_hash			*create_hash_table(int size);
void			free_table(t_hash *hash);
void			update_winsize(int sig);
void			shell_error(char *cmd, int error_code);
int				add_string(t_hash *hash, char *name, char *path);
t_item			*lookup_string(t_hash *hash, char *str);
unsigned int	hash_function(const char *data, int size);
char			*read_input(void);
void			ft_shell(char *arg, char ***env);
void			ft_sig_cont(int sig);
void			ft_reset_tab(t_inp *inp);
void			ft_home_end(char ch, t_inp *inp);
void			ft_21sh(char ***env);
t_term			ft_init_term(void);
void			make_intro(void);
int				is_builtin_command(char *str);
int				ft_is_executable(char *cmd, int flag);
char			**ft_init_env(char **env);
t_cap			*ft_init_cap(void);
int				ft_put(int ch);
char			*ft_input(t_cap *cap);
t_inp			*ft_init_inp(void);
void			place_env(char *n, char **env);
t_list			*ft_get_args(char **read, char ***env, t_list *node, int i);
void			ft_backspace(t_cap *cap, t_inp *inp, char **arg);
void			ft_arrows(t_cap *cap, t_inp *inp, char **arg);
void			ft_tab(t_cap *cap, t_inp *inp, char **arg);
void			ft_up_arrow(t_cap *cap, t_inp *inp, char **arg);
void			ft_down_arrow(t_cap *cap, t_inp *inp, char **arg);
void			ft_lst_cmd(t_list *list, char **env, t_cap *cap);
t_list			*ft_node_split(t_list *node, char *split);
int				ft_lst_len(t_list *list);
char			**ft_lstochar(t_list **list);
void			ft_exe_list(t_list *node, char **env, t_cap *cap);
void			ft_go_home(t_inp *inp);
char			*ft_findexe(char *cmd);
char			*ft_findpath(char *env, char *cmd);
int				ft_fileexist(char *name);
int				ft_tofile(char **arg, int *file);
void			ft_del_split(t_list **list);
void			ft_del_list(t_list **list);
void			ft_del_arg(char ***str);
void			ft_del_tmp(t_list **tmp);
t_fds			*ft_init_fds(void);
void			ft_check_for_file(t_fds *fds, t_list **list);
void			ft_set_fds(t_fds *fds, char ***str);
int				ft_check_redirect(char *str);
int				ft_check_amper(char *str);
void			ft_hist_search(t_cap *cap, t_inp *inp, char **arg);
void			ft_execute(t_list *node, char ***env, t_fds *fds);
void			ft_command(char *cmd, t_list *node, char ***env);
void			ft_un_fds(t_fds **del);
void			ft_exe_pipes(t_list **node, char ***env);
void			ft_exec_pipe(t_fds *fds, char **arg, char **env);
void			ft_error_cmd(char *cmd);
void			ft_m_setenv(t_list *list, char ***env);
void			ft_m_unsetenv(t_list *list, char **env);
void			ft_mini_cd(t_list *list, char **env);
void			ft_heredoc(t_fds *fds, char **arg, char **env, int fl);
void			ft_dup_fds(t_fds *fds, int fl);
void			ft_fdsfile(t_fds *fds, int *flag);
int				ft_check_arg(char **arg);
void			ft_lstpushback(t_list **lst, void *content, size_t size);
void			ft_exe_quote(char **str, int *a, t_list **node, char ***env);
void			ft_is_quote(char **str, int *a, char **ar, char ***env);
void			skip_quotes(char *s, int *i);
void			ft_print_multicolumn(t_read *read, t_list *lst, int k, int col);
void			clear_slash(char **str);
void			read_exe_quote(char *s, char ***env, int fd[], t_list **node);
void			put_heredoc(char *ret, int fd[]);
void			delete_it(t_read *new_read, char *tmp);
char			*clear_quotes(char *argv);
int				mini_echo(char **argv, int i, int j, int z);
int				ft_is_dir(char *path);
int				mini_env(char **env);
int				find_spec(char *str, int j);
int				builtin_command(char *exe, char **argv, char **env);
int				mini_history(void);

/*
** LINE EDITION
*/

void			ft_lstpushsort(t_list **lst, t_list *tmp, int (*cmp)());
int				check_correct(t_read *r);
int				ft_first_cmd(char *line, int count);
char			*take_path(char *tmp, t_read *read);
t_list			*ft_builtin(char *str);
char			*take_word(char *line, int count, char ch);
char			*take_exe(char *tmp);
t_list			*ft_find_in_dir(char *path, char *exe);
char			ft_getchar(void);
int				tab_complete(t_read *read);
int				history_search(t_read *r);
int				paste_str(t_read *read);
int				cut_line_right(t_read *read);
int				cut_line_left(t_read *read);
int				cursor_left_word(t_read *read);
int				cursor_right_word(t_read *read);
int				cursor_up_key(t_read *read);
int				cursor_down_key(t_read *read);
int				cursor_left_key(t_read *read);
int				cursor_right_key(t_read *read);
int				delete_key(t_read *read);
int				backspace(t_read *read);
int				history_up(t_read *read);
int				history_down(t_read *read);
int				reset_line(t_read *read);
int				end_reading(t_read *read);
int				termcap_home(t_read *read);
int				termcap_end(t_read *read);
int				term_go_backward(t_read *r);
int				term_go_forward(t_read *r);
char			*ft_strnchr(char const *src, int c, int len);
int				ft_strrnchr_pos(char const *src, int c, int len);
void			go_up(t_read *read);
int				actions_regular(t_read *read);
int				actions_extended(t_read *read);

void			print_str(t_read *read);
void			update_history(void);
int				insert_enter(t_read *read);
void			print_rest(t_read *read);
void			place_cursor(t_read *read);
void			get_line(t_read *read);
int				check_quote(t_read *read);
int				termcap_home(t_read *r);
void			upwrite_quote(t_read *read);
int				processing_key(t_read *read);
void			get_line_again(t_read *read);
int				check_correct(t_read *read);
void			insert_char(t_read *read, char key);
void			controlled_termios(t_sh *shell);
void			reset_termios(t_sh *shell);
t_read			*read_init(char **his, char *prompt, char **env, t_hash *hash);
void			delete_read(t_read *read);
int				termcap_putchar(int c);
int				termcap_do(char *key);
void			termcap_cursor(t_read *read);
int				termcap_goto(char *key, int col, int row);
void			print(t_read *read);

#endif
