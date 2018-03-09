/*
** exec_server.c for my_irc in /home/bibzor/rendu/NETWORK/PSU_2016_myirc
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Wed Jun  7 15:58:25 2017 bibzor
** Last update Fri Jun  9 17:54:41 2017 bibzor
*/

#include <stdio.h>
#include <sys/types.h>
#include <netdb.h>
#include "my_irc.h"

static int		new_client(t_server *server)
{
  int			fd_client;
  struct sockaddr_in	client;
  socklen_t		size;

  size = sizeof(client);
  if ((fd_client = accept(server->fd,
			  (struct sockaddr *)&client, &size)) == -1)
    return (FAILURE);
  if (list_add_elem(&server->head, NULL, fd_client) == FAILURE)
    return (FAILURE);
  printf("new client : %d\n", fd_client);
  return (SUCCESS);
}

int			exec_server(t_server *server)
{
  int			error;

  error = 0;
  while (error == 0)
    {
      init_readfds(server);
      init_writefds(server);
      if (select(max_fd(server), &server->readfds,
		 &server->writefds, NULL, NULL) == -1)
	{
	  fprintf(stderr, "select fail\n");
	  error = 1;
	}
      else
	{
	  if (FD_ISSET(server->fd, &server->readfds))
	    error = new_client(server);
	  error = read_fd(server);
	}
    }
  return (error);
}
