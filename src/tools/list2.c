/*
** list2.c for my_irc in /home/bibzor/rendu/NETWORK/PSU_2016_myirc/src
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Sat Jun 10 16:22:20 2017 bibzor
** Last update Sat Jun 10 16:26:22 2017 bibzor
*/

#include <stdlib.h>
#include "my_irc.h"

void		init_client(t_client_list **user, char *str, int fd)
{
  (*user)->next = NULL;
  (*user)->user = str;
  (*user)->nick = NULL;
  (*user)->fd = fd;
  (*user)->chan = NULL;
  return ;
}
