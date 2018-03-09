/*
** names_cmd.c for my_ir in /home/bibzor/rendu/NETWORK/PSU_2016_myirc/src/cmd
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Thu Jun  8 15:14:09 2017 bibzor
** Last update Sun Jun 11 17:52:14 2017 bibzor
*/

#include <stdio.h>
#include <string.h>
#include "my_irc.h"
#include "reply.h"

int		print_list_users(t_channel *chan, t_client_list *current)
{
  t_client_list	*tmp;

  tmp = chan->users;
  if (dprintf(current->fd, ":%s 353 %s = %s :", HOST_NAME,
	      current->nick, chan->name) < 0)
    return (ERROR);
  while (tmp->next != NULL)
    {
      if (dprintf(current->fd, "%s, ", tmp->nick) < 0)
	return (ERROR);
      tmp = tmp->next;
    }
  if (dprintf(current->fd, "%s%s:%s 366 %s %s %s%s", tmp->nick, REPLY_END,
	      HOST_NAME, current->nick, chan->name,
	      REPLY_NAMES_END, REPLY_END) < 0)
    return (ERROR);
  return (SUCCESS);
}

static int	print_g_users(t_server *server, t_client_list *current)
{
  t_client_list	*tmp;

  tmp = server->head;
  if (dprintf(current->fd, ":%s 353 %s :", HOST_NAME,
	      current->nick) < 0)
    return (ERROR);
  while (tmp->next != NULL)
    {
      if (tmp->nick != NULL)
	if (dprintf(current->fd, "%s, ", tmp->nick) < 0)
	  return (ERROR);
      tmp = tmp->next;
    }
  if (dprintf(current->fd, "%s%s:%s 366 %s * %s%s", tmp->nick, REPLY_END,
	      HOST_NAME, current->nick,
	      REPLY_NAMES_END, REPLY_END) < 0)
    return (ERROR);
  return (SUCCESS);
}

int		error_names(t_client_list *user, char *chan_name)
{
  if (dprintf(user->fd, ":%s 401 %s %s%s%s", HOST_NAME,
	      user->nick, chan_name, REPLY_401, REPLY_END) < 0)
    return (ERROR);
  return (SUCCESS);
}

static int	names_loop(t_server *server, char *input,
			   t_client_list *user)
{
  int		i;
  t_channel	*tmp;
  char		**tab;

  i = -1;
  if (!(tab = my_str_to_wordtab(input, ',')))
    return (ERROR);
  while (tab[++i])
    {
      tmp = server->chan;
      while (tmp != NULL)
	{
	  if (strcmp(tmp->name, tab[i]) == 0)
	    {
	      if (print_list_users(tmp, user) == ERROR)
		return (ERROR);
	      break ;
	    }
	  tmp = tmp->next;
	}
      if (tmp == NULL)
	if (error_names(user, tab[i]) == ERROR)
	  return (ERROR);
    }
  return (SUCCESS);
}

int		names_cmd(t_server *server, char *input, int fd)
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
      if ((ret = is_logged(tmp, "NAMES")) != SUCCESS)
	return ((ret == ERROR) ? ERROR : SUCCESS);
      else
	{
	  if (tab[1])
	    return (names_loop(server, tab[1], tmp));
	  else
	    return (print_g_users(server, tmp));
	}
    }
  return (SUCCESS);
}
