/*
** user_cmd.c for my_irc in /home/bibzor/rendu/NETWORK/PSU_2016_myirc/src/cmd
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Thu Jun  8 15:09:48 2017 bibzor
** Last update Sun Jun 11 14:19:46 2017 bibzor
*/

#include <stdio.h>
#include <string.h>
#include "my_irc.h"
#include "reply.h"

int		print_reply_authentication(t_server *server,
					   t_client_list *current)
{
  if (FD_ISSET(current->fd, &server->writefds))
    {
      if (dprintf(current->fd, "%s%s%s%s%s%s%s", ":", HOST_NAME, REPLY_NICK,
		  current->nick, REPLY_NICK2, current->nick, REPLY_END) < 0
	  || dprintf(current->fd, "%s%s%s%s%s%s%s%s", ":", HOST_NAME,
		     REPLY_002_BEGIN, current->nick, REPLY_002_NEXT, HOST_NAME,
		     REPLY_002_END, REPLY_END) < 0
	  || dprintf(current->fd, "%s%s%s%s%s%s", ":", HOST_NAME, REPLY_003,
		     current->nick, REPLY_003_END, REPLY_END) < 0
	  || dprintf(current->fd, "%s%s%s%s%s%s", ":" , HOST_NAME, REPLY_004,
		     current->nick, REPLY_004_END, REPLY_END) < 0)
	return (ERROR);
    }
  return (SUCCESS);
}

static int	nb_param(char *input, int fd, t_server *server)
{
  int		i;
  int		nb_spaces;

  i = 0;
  nb_spaces = 0;
  while (input[i] && input[i] != ':')
    {
      if (input[i] == ' ')
	++nb_spaces;
      ++i;
    }
  if (nb_spaces != 4)
    {
      if (FD_ISSET(fd, &server->writefds))
	if (dprintf(fd, "%s%s%s%s%s%s", ":", HOST_NAME, REPLY_461, "USER",
		    REPLY_461_END, REPLY_END) < 0)
	  return (FAILURE);
      return (FAILURE);
    }
  return (SUCCESS);
}

char		*get_user(char *input)
{
  int		i;
  char		*new;

  i = 0;
  new = NULL;
  while (input[i] && input[i] != ':')
    ++i;
  if (input[i] == ':')
    {
      ++i;
      if (!(new = strdup(input + i)))
	return (NULL);
    }
  return (new);
}

int		 user_cmd(t_server *server, char *input, int fd)
{
  t_client_list	*tmp;
  char		*user;

  printf("%s\n", input);
  if (!(tmp = get_client(server, fd)))
    return (ERROR);
  if (tmp->user != NULL)
    {
      if (dprintf(fd, "%s%s%s%s", ":", HOST_NAME, REPLY_462, REPLY_END) < 0)
	return (ERROR);
      return (SUCCESS);
    }
  if (!(input = epur_str(input)))
    return (ERROR);
  if (nb_param(input, fd, server) == FAILURE)
    return (SUCCESS);
  if ((user = get_user(input)) == NULL)
    return (SUCCESS);
  tmp->user = user;
  return (SUCCESS);
}
