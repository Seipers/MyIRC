/*
** main.c for exam in /home/exam/rendu/epur_str
**
** Made by exam user
** Login   <exam@epitech.net>
**
** Started on  Tue May  2 18:05:58 2017 exam user
** Last update Sun Jun 11 14:11:27 2017 bibzor
*/

#include <string.h>
#include <stdlib.h>

char		*epur_str(char *str)
{
  int		i;
  int		cnt;
  char		*new;

  i = 0;
  cnt = 0;
  if (!(new = malloc(sizeof(char) * (strlen(str) + 1))))
    return (NULL);
  while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v')
    ++i;
  while (str[i])
    {
      if ((str[i] == ' ' || str[i] == '\t' || str[i] == '\v')
	  && (str[i + 1] != ' ' && str[i + 1] != '\t'
	      && str[i + 1] != '\v' && str[i + 1] != '\0'))
	new[cnt++] = ' ';
      else if (str[i] != ' ' && str[i] != '\t' && str[i] != '\v')
	new[cnt++] = str[i];
      ++i;
    }
  new[i] = '\0';
  return (new);
}
