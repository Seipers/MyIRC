/*
** part_cmd.c for my_irc in /home/bibzor/rendu/NETWORK/PSU_2016_myirc/src/cmd
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Thu Jun  8 15:13:32 2017 bibzor
** Last update Sun Jun 11 18:04:03 2017 bibzor
*/

#include <string.h>
#include <stdio.h>
#include "my_irc.h"
#include "reply.h"

static int	spread_part(t_client_list *user, t_server *server)
{
  t_client_list	*tmp;

  tmp = user->chan->users;
  while (tmp != NULL)
    {
      if (FD_ISSET(tmp->fd, &server->writefds))
	if (dprintf(tmp->fd, ":%s PART :%s%s", user->nick,
		    user->chan->name, REPLY_END) < 0)
	  return (ERROR);
      tmp = tmp->next;
    }
  return (SUCCESS);
}

static void	remove_chan(t_server *server, int fd)
{
  t_client_list	*tmp;

  tmp = server->head;
  while (tmp != NULL)
    {
      if (tmp->fd == fd)
	{
	  tmp->chan = NULL;
	  return ;
	}
      tmp = tmp->next;
    }
}

static int	check_chan(t_client_list *user, char *chan, t_server *server)
{
  if (user->chan == NULL || strcmp(user->chan->name, chan) != 0)
    {
      if (FD_ISSET(user->fd, &server->writefds))
	if (dprintf(user->fd, ":%s 442 %s %s %s%s", HOST_NAME, user->nick,
		    chan, REPLY_442, REPLY_END) < 0)
	  return (ERROR);
      return (FAILURE);
    }
  return (SUCCESS);
}

int		part_cmd(t_server *server, char *input, int fd)
{
  t_client_list	*tmp;
  char		**tab;
  int		ret;

  if ((tmp = get_client(server, fd)) == NULL
      || (input = epur_str(input)) == NULL
      || (tab = my_str_to_wordtab(input, ' ')) == NULL)
    return (ERROR);
  if (FD_ISSET(fd, &server->writefds))
    {
      if ((ret = is_logged(tmp, "PART")) != SUCCESS
	  || (ret = check_chan(tmp, tab[1], server)) != SUCCESS
	  || (ret = nb_params(tab, tmp, "PART", server)) != SUCCESS
	  || (ret = check_format(tab[1], server, tmp) != SUCCESS))
	return ((ret == ERROR) ? ERROR : SUCCESS);
      else
	{
	  if (spread_part(tmp, server) == ERROR
	      || remove_user(&tmp->chan, tmp->fd) == ERROR)
	    return (ERROR);
	  remove_chan(server, fd);
	}
    }
  return (SUCCESS);
}
