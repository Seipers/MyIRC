/*
** my_irc.h for my_irc in /home/bibzor/rendu/NETWORK/PSU_2016_myirc/include
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Wed Jun  7 11:50:31 2017 bibzor
** Last update Sun Jun 11 17:51:37 2017 bibzor
*/

#ifndef MY_IRC_H
# define MY_IRC_H

# include <sys/socket.h>

# define SUCCESS 0
# define FAILURE 1
# define ERROR 2
# define QUIT 3

# define USAGE "USAGE: ./server port\n"
# define INVALID_ARG "Invalid arguments\n"
# define HELP "--help"

typedef struct		s_client_list
{
  char			*user;
  char			*nick;
  int			fd;
  struct s_channel	*chan;
  struct s_client_list	*next;
}			t_client_list;

typedef struct		s_channel
{
  int			nb_users;
  char			*name;
  t_client_list		*users;
  struct s_channel	*next;
}			t_channel;

typedef struct		s_server
{
  int			port;
  int			fd;
  fd_set		readfds;
  fd_set		writefds;
  t_client_list		*head;
  t_channel		*chan;
}			t_server;

/* structure for functions pointers */
typedef struct		s_cmd
{
  char			*cmd;
  int			(*cmd_func)(t_server *, char *, int);
}			t_cmd;

/* tools */
int			is_num(char);
int			is_logged(t_client_list *, char *);
int			check_format(char *, t_server *,
				     t_client_list *);
int			nb_params(char **, t_client_list *, char *,
				  t_server *);
int			list_add_elem(t_client_list **, char *, int);
int			list_del_elem(t_client_list **, int);
int			remove_user(t_channel **, int);
int			add_user_to_chan(char *, t_client_list **,
					 t_channel **, t_server *);
int			max_fd(t_server *);
int			print_list_users(t_channel *, t_client_list *);
int			spread_to_other(t_channel *,
					t_client_list *, t_server *);
char			**my_str_to_wordtab(char *, char);
t_client_list		*get_client(t_server *, int);
char			*epur_str(char *);
void			init_client(t_client_list **, char *, int);
int			error_names(t_client_list *, char *);
char			*find_pos_msg(char *);

/* exec_server */
int			exec_server(t_server *);
void			init_readfds(t_server *);
void			init_writefds(t_server *);
int			read_fd(t_server *);
int			parse_cmd(t_server *, char *, int);

/* cmd_user */
int			user_cmd(t_server *, char *, int);
int			pass_cmd(t_server *, char *, int);
int			quit_cmd(t_server *, char *, int);
int			nick_cmd(t_server *, char *, int);
int			join_cmd(t_server *, char *, int);
int			part_cmd(t_server *, char *, int);
int			privmsg_cmd(t_server *, char *, int);
int			kill_cmd(t_server *, char *, int);
int			pong_cmd(t_server *, char *, int);
int			names_cmd(t_server *, char *, int);
int			list_cmd(t_server *, char *, int);
int			print_reply_authentication(t_server *,
						   t_client_list *);

#endif /* MY_IRC_H */
