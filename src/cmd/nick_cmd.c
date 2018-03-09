/*
** user_nick.c for my_irc$ in /home/bibzor/rendu/NETWORK/PSU_2016_myirc/src/cmd
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Thu Jun  8 15:10:53 2017 bibzor
** Last update Sat Jun 10 17:13:16 2017 bibzor
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "my_irc.h"
#include "reply.h"

static int	nb_arg(char **tab, int fd, t_server *server)
{
  int		i;
  int		cnt;

  i = 0;
  cnt = 0;
  while (tab[i])
    {
      ++i;
      ++cnt;
    }
  if (cnt < 2)
    {
      if (FD_ISSET(fd, &server->writefds))
	if (dprintf(fd, "%s%s%s%s%s%s", ":", HOST_NAME, REPLY_461, "NICK",
		    REPLY_461_END, REPLY_END ) < 0)
	  return (FAILURE);
      return (FAILURE);
    }
  return (SUCCESS);
}

static int	is_alpha_num(char *str, int fd, t_server *server)
{
  int		i;

  i = 0;
  printf("%s\n", str);
  while (str[i])
    {
      if (isalnum(str[i]) == 0)
	{
	  if (FD_ISSET(fd, &server->writefds))
	    if (dprintf(fd, "%s%s%s%s%s%s", ":", HOST_NAME, REPLY_432, str,
			REPLY_432_END, REPLY_END ) < 0)
	      return (FAILURE);
	  return (FAILURE);
	}
      ++i;
    }
  return (SUCCESS);
}

static void	format_input(char *str)
{
  int		i;

  i = 0;
  while (str[i])
    {
      if (str[i] == ':')
	str[i] = ' ';
      ++i;
    }
  return ;
}

static int	check_duplicates_nick(t_server *server, int fd, char *nick)
{
  t_client_list *tmp;

  tmp = server->head;
  while (tmp != NULL)
    {
      if (tmp->nick != NULL)
	if (strcmp(tmp->nick, nick) == 0)
	  {
	    if (FD_ISSET(fd, &server->writefds))
	      if (dprintf(fd, "%s%s%s%s%s%s", ":", HOST_NAME, REPLY_433, nick,
			  REPLY_433_END, REPLY_END ) < 0)
		return (FAILURE);
	    return (FAILURE);
	  }
      tmp = tmp->next;
    }
  return (SUCCESS);
}

int		nick_cmd(t_server *server, char *input, int fd)
{
  t_client_list	*tmp;
  char		**tab;
  int		bool;

  format_input(input);
  if (!(tab = my_str_to_wordtab(input, ' ')))
    return (ERROR);
  if (nb_arg(tab, fd, server) == FAILURE
      || is_alpha_num(tab[1], fd, server) == FAILURE
      || check_duplicates_nick(server, fd, tab[1]) == FAILURE)
    return (SUCCESS);
  else
    {
      if (!(tmp = get_client(server, fd)))
	return (ERROR);
      bool = (tmp->nick == NULL) ? 0 : 1;
      if (bool == 1)
	if (dprintf(fd, ":%s NICK %s%s", tmp->nick, tab[1], REPLY_END)< 0)
	  return (ERROR);
      tmp->nick = tab[1];
    }
  if (bool == 0)
    return (print_reply_authentication(server, tmp));
  return (SUCCESS);
}
