/*
** user_quit.c for my_ir in /home/bibzor/rendu/NETWORK/PSU_2016_myirc/src/cmd
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Thu Jun  8 15:10:31 2017 bibzor
** Last update Sat Jun 10 19:38:53 2017 bibzor
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "my_irc.h"
#include "reply.h"

static int	spread_quit(t_server *server, t_client_list *user,
			    char *msg)
{
  t_client_list	*tmp;

  if (user->chan == NULL)
    return (SUCCESS);
  tmp = user->chan->users;
  while (tmp != NULL)
    {
      if (FD_ISSET(tmp->fd, &server->writefds) && tmp->fd != user->fd)
	{
	  if (msg == NULL)
	    {
	      if (dprintf(tmp->fd, ":%s QUIT :Client exited%s", user->nick,
			  REPLY_END) < 0)
		return (ERROR);
	    }
	  else
	    if (dprintf(tmp->fd, ":%s QUIT :Self-Quit: %s%s", user->nick,
			msg, REPLY_END) < 0)
	      return (ERROR);
	}
      tmp = tmp->next;
    }
  return (SUCCESS);
}

int		quit_cmd(t_server *server, char *input, int fd)
{
  t_client_list	*tmp;

  if (FD_ISSET(fd, &server->writefds))
    if (dprintf(fd, "%s\r\n", "Connection closed, GoodBye !") < 0)
      return (ERROR);
  if ((tmp = get_client(server, fd)) == NULL)
    return (ERROR);
  if (strlen(input) < 5)
    {
      if (spread_quit(server, tmp, NULL) == ERROR)
      return (ERROR);
    }
  else
    if (spread_quit(server, tmp, input + 5) == ERROR)
      return (ERROR);
  if (remove_user(&tmp->chan, fd) == FAILURE)
    return (FAILURE);
  if (list_del_elem(&server->head, fd) == FAILURE)
    return (ERROR);
  if (close(fd) == -1)
    return (ERROR);
  return (QUIT);
}
