/*
** read.c for my_irc in /home/le-gui_s/Rendu/PSU_2016_myirc/src/server
**
** Made by Sébastien Le Guischer
** Login   <le-gui_s@epitech.net>
**
** Started on  Wed Jun  7 15:55:38 2017 Sébastien Le Guischer
** Last update Sun Jun 11 19:11:03 2017 bibzor
*/

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my_irc.h"
#include "reply.h"

static int		unknown_cmd(t_server *server,
				    t_client_list *user,
				    char *input)
{
  char			**tab;

  if (!(tab = my_str_to_wordtab(input, ' ')))
    return (ERROR);
  if (tab[0][strlen(tab[0]) - 2] == '\r')
    tab[0][strlen(tab[0]) - 2] = '\0';
  if (FD_ISSET(user->fd, &server->writefds))
    if (dprintf(user->fd, ":%s 421 %s %s :Unknown command%s",
		HOST_NAME, user->nick, tab[0], REPLY_END) < 0)
      return (ERROR);
  return (SUCCESS);
}

static int		write_to_other(t_server *server, int fd)
{
  size_t		n;
  char			*str;
  t_client_list		*tmp;
  int			err;

  str = NULL;
  n = 0;
  if ((getline(&str, &n, fdopen(fd, "r+"))) == -1)
    str = strdup("QUIT\r\n");
  printf("%s\n", str);
  err = parse_cmd(server, strdup(str), fd);
  if (err != FAILURE)
    return (err);
  else
    {
      if (strcmp("\r\n", str) != 0)
	{
	  if ((tmp = get_client(server, fd)) == NULL)
	    return (ERROR);
	  if (unknown_cmd(server, tmp, strdup(str)) == ERROR)
	    return (ERROR);
	}
    }
  return (SUCCESS);
}

int			read_fd(t_server *server)
{
  t_client_list		*tmp;
  int			retval;

  tmp = server->head;
  retval = SUCCESS;
  while (tmp != NULL)
    {
      if (FD_ISSET(tmp->fd, &server->readfds))
	retval = write_to_other(server, tmp->fd);
      if (retval == FAILURE)
	return (FAILURE);
      else if (retval == ERROR)
	return (ERROR);
      else if (retval == QUIT)
	break ;
      else
	tmp = tmp->next;
    }
  return (SUCCESS);
}
