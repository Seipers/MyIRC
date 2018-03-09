/*
** channel.c for my_irc in /home/le-gui_s/Rendu/PSU_2016_myirc/src/server
**
** Made by Sébastien Le Guischer
** Login   <le-gui_s@epitech.net>
**
** Started on  Thu Jun  8 12:53:13 2017 Sébastien Le Guischer
** Last update Sun Jun 11 17:39:29 2017 bibzor
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_irc.h"
#include "reply.h"

int		remove_user(t_channel **chan, int fd)
{
  if (*chan == NULL)
    return (SUCCESS);
  (*chan)->nb_users -= 1;
  return (list_del_elem(&(*chan)->users, fd));
}

static int	add_user(t_channel **chan, t_client_list **user,
			 t_server *server)
{
  t_client_list	*tmp;

  if (list_add_elem(&((*chan)->users), (*user)->user, (*user)->fd) == FAILURE)
    return (FAILURE);
  tmp = (*chan)->users;
  while (tmp->fd != (*user)->fd)
    tmp = tmp->next;
  tmp->nick = strdup((*user)->nick);
  tmp->chan = (*chan);
  (*chan)->nb_users += 1;
  (*user)->chan = (*chan);
  if (spread_to_other(*chan, *user, server) == ERROR
    || print_list_users(*chan, *user) == ERROR)
    return (ERROR);
  return (SUCCESS);
}

static int	new_chan(t_channel **head, t_client_list **user, char *name,
			 t_server *server)
{
  t_channel	*tmp;
  t_channel	*new;

  if (*head == NULL)
    {
      if (!(*head = malloc(sizeof(t_channel))))
	return (FAILURE);
      (*head)->next = NULL;
      (*head)->nb_users = 0;
      (*head)->users = NULL;
      (*head)->name = strdup(name);
      return (add_user(head, user, server));
    }
  tmp = *head;
  if (!(new = malloc(sizeof(t_channel))))
    return (FAILURE);
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = new;
  new->name = strdup(name);
  new->next = NULL;
  new->nb_users = 0;
  new->users = NULL;
  return (add_user(&new, user, server));
}

int		add_user_to_chan(char *name,
				 t_client_list **user,
				 t_channel **head,
				 t_server *server)
{
  t_channel	*tmp;

  tmp = (*head);
  while (tmp != NULL)
    {
      if (strcmp(name, tmp->name) == 0)
	return (add_user(&tmp, user, server));
      tmp = tmp->next;
    }
  return (new_chan(head, user, name, server));
}
