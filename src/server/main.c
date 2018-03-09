/*
** main.c for myirc in /home/bibzor/rendu/NETWORK/PSU_2016_myirc/src
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Wed Jun  7 11:49:07 2017 bibzor
** Last update Sun Jun 11 18:13:53 2017 bibzor
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include "my_irc.h"

static int		*g_fd_socket = NULL;

static void		sigint_handler(int a)
{
  (void)a;
  if (close(*g_fd_socket) == -1)
    return ;
  exit(SUCCESS);
}

static int		parse_av(t_server *server, char *str)
{
  int			i;

  i = 0;
  if (strcmp(str, HELP) == 0)
    {
      printf("%s", USAGE);
      return (FAILURE);
    }
  while (str[i])
    {
      if (is_num(str[i]) == FAILURE)
	return (FAILURE);
      ++i;
    }
  server->port = atoi(str);
  return (SUCCESS);
}

static int		init_server(t_server *server)
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;

  if (!(pe = getprotobyname("TCP")))
    return (FAILURE);
  if ((server->fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (FAILURE);
  g_fd_socket = &server->fd;
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(server->port);
  s_in.sin_addr.s_addr = INADDR_ANY;
  if (bind(server->fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1
      || listen(server->fd, 42) == -1)
    {
      if (close(server->fd) == -1)
	return (FAILURE);
      return (FAILURE);
    }
  server->head = NULL;
  server->chan = NULL;
  return (SUCCESS);
}

int			main(const int ac, char *av[])
{
  t_server		server;

  signal(SIGINT, sigint_handler);
  if (ac != 2)
    {
      printf("%s", USAGE);
      return (FAILURE);
    }
  server.port = 0;
  if (parse_av(&server, av[1]) == FAILURE
      || init_server(&server) == FAILURE)
    return (FAILURE);
  if (exec_server(&server) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}
