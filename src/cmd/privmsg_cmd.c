/*
** privmsg_cmd.c for my_irc in /home/bibzor/rendu/NETWORK/PSU_2016_myirc/src/cmd
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Thu Jun  8 15:13:42 2017 bibzor
** Last update Sun Jun 11 17:50:29 2017 bibzor
*/

#include <stdio.h>
#include <string.h>
#include "my_irc.h"
#include "reply.h"

static int	check_arg(char **arg, t_client_list *user,
			  t_server *server)
{
  int		i;

  i = 0;
  while (arg[i])
    ++i;
  if (i < 3)
    {
      if (FD_ISSET(user->fd, &server->writefds))
	if (dprintf(user->fd, ":%s 461 %s PRIVMSG %s%s", HOST_NAME,
		    user->nick, REPLY_461_END, REPLY_END) < 0)
	  return (ERROR);
      return (FAILURE);
    }
  return (SUCCESS);
}

static int	send_msg_to_chan(t_server *server, t_channel *chan,
				 t_client_list *user, char *msg)
{
  t_client_list	*tmp;

  tmp = chan->users;
  while (tmp != NULL)
    {
      if (tmp->fd != user->fd && FD_ISSET(tmp->fd, &server->writefds))
	{
	  if (dprintf(tmp->fd, ":%s PRIVMSG %s :%s%s", user->nick,
		      chan->name, msg, REPLY_END) < 0)
	    return (ERROR);
	}
      tmp = tmp->next;
    }
  return (SUCCESS);
}

static int	find_user(t_server *server, char *target,
			  char *msg,
			  t_client_list *user)
{
  t_client_list	*tmp;

  tmp = server->head;
  while (tmp != NULL)
    {
      if (strcmp(target, tmp->nick) == 0)
	{
	  if (FD_ISSET(tmp->fd, &server->writefds))
	    if (dprintf(tmp->fd, ":%s PRIVMSG %s :%s%s", user->nick,
			target, msg, REPLY_END) < 0)
	      return (ERROR);
	  break ;
	}
      tmp = tmp->next;
    }
  if (tmp == NULL)
    if (error_names(user, target) == ERROR)
      return (ERROR);
  return (SUCCESS);
}

static int	find_target(t_server *server, char *target,
			    char *msg,
			    t_client_list *user)
{
  t_channel	*tmp2;

  if (target[0] == '#')
    {
      tmp2 = server->chan;
      while (tmp2 != NULL)
	{
	  if (strcmp(target, tmp2->name) == 0)
	    {
	      if (send_msg_to_chan(server, tmp2, user,
				   find_pos_msg(msg)) == ERROR)
		return (ERROR);
	      break ;
	    }
	  tmp2 = tmp2->next;
	}
      if (tmp2 == NULL)
	if (error_names(user, target) == ERROR)
	  return (ERROR);
    }
  else
    return (find_user(server, target, find_pos_msg(msg), user));
  return (SUCCESS);
}

int		privmsg_cmd(t_server *server, char *input, int fd)
{
  t_client_list	*tmp;
  char		**tab;
  int		ret;

  if ((tmp = get_client(server, fd)) == NULL
      || (input = epur_str(input)) == NULL
      || (tab = my_str_to_wordtab(input, ' ')) == NULL)
    return (ERROR);
  if (check_arg(tab, tmp, server) == FAILURE)
    return (SUCCESS);
  if (FD_ISSET(fd, &server->writefds))
    {
      if ((ret = is_logged(tmp, "PRIVMSG")) != SUCCESS)
	return ((ret == ERROR) ? ERROR : SUCCESS);
      if (find_target(server, tab[1], input, tmp) == ERROR)
	return (ERROR);
    }
  return (SUCCESS);
}
