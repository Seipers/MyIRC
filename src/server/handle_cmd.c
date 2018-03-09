/*
** handle_cmd.c for my_irc in /home/bibzor/rendu/NETWORK/PSU_2016_myirc/src/server
**
** Made by bibzor
** Login   <sebastien.vidal@epitech.eu>
**
** Started on  Thu Jun  8 14:37:13 2017 bibzor
** Last update Sun Jun 11 16:36:15 2017 bibzor
*/

#include <string.h>
#include <stdlib.h>
#include "my_irc.h"

static const t_cmd		cmd[] =
  {
    {"USER", &user_cmd},
    {"USERS", &user_cmd},
    {"PASS", &pass_cmd},
    {"QUIT", &quit_cmd},
    {"NICK", &nick_cmd},
    {"JOIN", &join_cmd},
    {"PART", &part_cmd},
    {"PRIVMSG", &privmsg_cmd},
    {"KILL", &kill_cmd},
    {"PONG", &pong_cmd},
    {"NAMES", &names_cmd},
    {"LIST", &list_cmd},
    {NULL, NULL}
  };

static int			check_cmd(char *input, char *cmd)
{
  int				cnt;

  cnt = -1;
  while (input[++cnt] && input[cnt] != ' ')
    if (input[cnt] != cmd[cnt])
      break ;
  if (cmd[cnt] == '\0' && (input[cnt] == '\0' || input[cnt] == ' '))
    return (SUCCESS);
  return (FAILURE);
}

int				parse_cmd(t_server *server,
					  char *input, int fd)
{
  int				i;
  int				err;

  i = -1;
  err = FAILURE;
  if (input[strlen(input) - 2] == '\r')
    input[strlen(input) - 2] = '\0';
  while (cmd[++i].cmd != NULL)
    if (check_cmd(input, cmd[i].cmd) == SUCCESS)
      err = cmd[i].cmd_func(server, input, fd);
  return (err);
}
