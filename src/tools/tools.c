/*
** tools.c for my_irc in /home/bibzor/rendu/NETWORK/PSU_2016_myirc/src
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Wed Jun  7 13:13:05 2017 bibzor
** Last update Sun Jun 11 17:48:45 2017 bibzor
*/

#include <stdio.h>
#include "my_irc.h"
#include "reply.h"

char	*find_pos_msg(char *msg)
{
  int	i;
  int	cnt;

  i = 0;
  cnt = 0;
  while (msg[i])
    {
      if (cnt == 2)
	break ;
      if (msg[i] == ' ')
	++cnt;
      ++i;
    }
  if (msg[i] == ':')
    ++i;
  return (msg + i);
}

int	check_format(char *chan_name, t_server *server,
			     t_client_list *user)
{
  if (chan_name[0] != '#')
    {
      if (FD_ISSET(user->fd, &server->writefds))
	if (dprintf(user->fd, ":%s 403 %s %s %s%s", HOST_NAME, user->nick,
		    chan_name, REPLY_403, REPLY_END ) < 0)
	  return (ERROR);
      return (FAILURE);
    }
  return (SUCCESS);
}

int	nb_params(char **tab, t_client_list *user, char *cmd, t_server *server)
{
  int	i;

  i = 0;
  while (tab[i])
    ++i;
  if (i < 2)
    {
      if (FD_ISSET(user->fd, &server->writefds))
	if (dprintf(user->fd, ":%s 461 %s %s %s%s", HOST_NAME, user->nick, cmd,
		    REPLY_461_END, REPLY_END) < 0)
	  return (ERROR);
      return (FAILURE);
    }
  return (SUCCESS);
}

int	is_logged(t_client_list *user, char *cmd)
{
  if (user->nick == NULL || user->user == NULL)
    {
      if (dprintf(user->fd, ":%s 451 %s %s%s",
		  HOST_NAME, cmd, REPLY_451, REPLY_END) < 0)
	return (ERROR);
      return (FAILURE);
    }
  return (SUCCESS);
}

int	is_num(char c)
{
  if (c >= '0' && c <= '9')
    return (SUCCESS);
  return (FAILURE);
}
