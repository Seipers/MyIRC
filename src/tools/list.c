/*
** list.c for objdump in /home/bibzor/rendu/MEMOIRE/PSU_2016_nmobjdump
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Sat Feb 18 16:33:46 2017 bibzor
** Last update Sun Jun 11 14:17:14 2017 bibzor
*/

#include <stdlib.h>
#include <stdio.h>
#include "my_irc.h"

void		print_list(t_client_list *head)
{
  t_client_list	*tmp;

  tmp = head;
  if (tmp != NULL)
    {
      while (tmp->next != NULL)
	{
	  printf("%d, ", tmp->fd);
	  tmp = tmp->next;
	}
      printf("%d\n", tmp->fd);
    }
}

t_client_list	*get_client(t_server *server, int fd)
{
  t_client_list	*tmp;

  tmp = server->head;
  while (tmp != NULL)
    {
      if (tmp->fd == fd)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

static int	list_del_elem_at_front(t_client_list **front_ptr)
{
  t_client_list	*tmp;

  printf("delete head\n");
  tmp = (*front_ptr)->next;
  if (*front_ptr == NULL)
    return (FAILURE);
  free(*front_ptr);
  *front_ptr = tmp;
  return (SUCCESS);
}

int		list_del_elem(t_client_list **head, int fd)
{
  t_client_list	*tmp;
  t_client_list	*save;

  if (*head == NULL)
    return (FAILURE);
  if (fd == (*head)->fd)
    return (list_del_elem_at_front(head));
  tmp = *head;
  while (tmp != NULL)
    {
      if (fd == tmp->fd)
	break ;
      save = tmp;
      tmp = tmp->next;
    }
  if (tmp != NULL)
    {
      save->next = tmp->next;
      free(tmp);
    }
  return (SUCCESS);
}

int		list_add_elem(t_client_list **head, char *str, int fd)
{
  t_client_list	*new;
  t_client_list	*tmp;

  if (*head == NULL)
    {
      if (!(*head = malloc(sizeof(t_client_list))))
	return (FAILURE);
      init_client(head, str, fd);
      return (SUCCESS);
    }
  tmp = *head;
  if (!(new = malloc(sizeof(t_client_list))))
    return (FAILURE);
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = new;
  init_client(&new, str, fd);
  return (SUCCESS);
}
