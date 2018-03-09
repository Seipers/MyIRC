/*
** init_fd.c for my_irc in /home/bibzor/rendu/NETWORK/PSU_2016_myirc/src/server
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Wed Jun  7 16:27:03 2017 bibzor
** Last update Fri Jun  9 14:15:38 2017 bibzor
*/

#include <stdlib.h>
#include "my_irc.h"

int		max_fd(t_server *server)
{
  t_client_list	*tmp;
  int		max;

  max = 0;
  tmp = server->head;
  if (server->fd > max)
    max = server->fd;
  while (tmp != NULL)
    {
      if (tmp->fd > max)
	max = tmp->fd;
      tmp = tmp->next;
    }
  return (max + 1);
}

void		init_readfds(t_server * server)
{
  t_client_list	*tmp;

  tmp = server->head;
  FD_ZERO(&server->readfds);
  FD_SET(server->fd, &server->readfds);
  while (tmp != NULL)
    {
      FD_SET(tmp->fd, &server->readfds);
      tmp = tmp->next;
    }
}

void		init_writefds(t_server * server)
{
  t_client_list	*tmp;

  tmp = server->head;
  FD_ZERO(&server->writefds);
  while (tmp != NULL)
    {
      FD_SET(tmp->fd, &server->writefds);
      tmp = tmp->next;
    }
}
