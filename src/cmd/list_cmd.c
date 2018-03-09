/*
** list_cmd.c for my_irc in /home/bibzor/rendu/NETWORK/PSU_2016_myirc/src/cmd
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Thu Jun  8 15:14:16 2017 bibzor
** Last update Sun Jun 11 14:15:56 2017 bibzor
*/

#include <stdio.h>
#include <string.h>
#include "my_irc.h"
#include "reply.h"

static int	print_list_channel(t_server *server,
				   t_client_list *user, char *chan)
{
  t_channel	*tmp;

  tmp = server->chan;
  while (tmp != NULL)
    {
      if (strstr(tmp->name, chan) != NULL)
	if (dprintf(user->fd, ":%s 322 %s %s %d : NO TOPIC%s", HOST_NAME,
		    user->nick, tmp->name, tmp->nb_users, REPLY_END) < 0)
	  return (ERROR);
      tmp = tmp->next;
    }
  if (dprintf(user->fd, ":%s 323 %s%s%s", HOST_NAME, user->nick,
	      REPLY_LIST_END, REPLY_END) < 0)
    return (ERROR);
  return (SUCCESS);
}

int		list_cmd(t_server *server, char *input, int fd)
{
  t_client_list	*user;

  user = get_client(server, fd);
  if (!FD_ISSET(user->fd, &server->writefds))
    return (ERROR);
  if (user->user != NULL && user->nick != NULL)
    {
      if (dprintf(fd, ":%s 321 %s%s%s", HOST_NAME, user->nick,
		  REPLY_LIST_START, REPLY_END) < 0)
	return (ERROR);
      if (strlen(input) > 5)
	return (print_list_channel(server, user, input + 5));
      else
	return (print_list_channel(server, user, ""));
    }
  else
    if (dprintf(user->fd, ":%s 451 LIST %s%s",
		HOST_NAME, REPLY_451, REPLY_END) < 0)
      return (ERROR);
  return (SUCCESS);
}
