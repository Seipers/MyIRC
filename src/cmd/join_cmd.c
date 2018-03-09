/*
** join_cmd.c for my_irc in /home/bibzor/rendu/NETWORK/PSU_2016_myirc/src/cmd
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Thu Jun  8 15:13:25 2017 bibzor
** Last update Sun Jun 11 17:49:18 2017 bibzor
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_irc.h"
#include "reply.h"

int		spread_to_other(t_channel *chan, t_client_list *user,
				t_server *server)
{
  t_client_list	*tmp;

  tmp = chan->users;
  while (tmp != NULL)
    {
      if (FD_ISSET(tmp->fd, &server->writefds))
	if (dprintf(tmp->fd, ":%s JOIN :%s%s", user->nick,
		    chan->name, REPLY_END) < 0)
	  return (ERROR);
      tmp = tmp->next;
    }
  return (SUCCESS);
}

int		join_cmd(t_server *server, char *input, int fd)
{
  t_client_list	*tmp;
  char		**tab;
  int		ret;

  if ((tmp = get_client(server, fd)) == NULL
      ||(input = epur_str(input)) == NULL
      ||(tab = my_str_to_wordtab(input, ' ')) == NULL)
    return (ERROR);
  if (nb_params(tab, tmp, "JOIN", server) == FAILURE
      || check_format(tab[1], server, tmp) == FAILURE
      || tmp->chan != NULL)
    return (SUCCESS);
  if ((ret = is_logged(tmp, "JOIN")) != SUCCESS)
    return ((ret == ERROR) ? ERROR : SUCCESS);
  if (FD_ISSET(fd, &server->writefds))
    if (dprintf(fd, ":%s %s%s %s%s%s", HOST_NAME, REPLY_TOPIC,
		tmp->nick, tab[1], REPLY_TOPIC_END, REPLY_END) < 0)
      return (ERROR);
  return (add_user_to_chan(tab[1], &tmp, &server->chan, server));
}
