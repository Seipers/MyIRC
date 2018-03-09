/*
** reply.h for my_irc in /home/sebastien/Rendu/PSU_2016_myirc
**
** Made by Sebastien Le Guischer
** Login   <sebastien@epitech.net>
**
** Started on  Fri Jun  9 13:14:05 2017 Sebastien Le Guischer
** Last update Sun Jun 11 14:47:53 2017 bibzor
*/

#ifndef REPLY_H_
# define REPLY_H_

# define HOST_NAME "irc.seb*seb.epitech.eu"
# define REPLY_END "\r\n"

# define REPLY_NICK " 001 "
# define REPLY_NICK2 " :Welcome to the Internet Relay Network "
# define REPLY_NICK3 " !"
# define REPLY_002_BEGIN " 002 "
# define REPLY_002_NEXT " :Your host is "
# define REPLY_002_END ", running version InspIRCd-1.8"
# define REPLY_003 " 003 "
# define REPLY_003_END " This server was created 22:22:22 Jun 6 2017"
# define REPLY_004 " 004 "
# define REPLY_004_END " irc.seb*seb.epitech.eu InspIRCd-1.8 Open Open"
# define REPLY_LIST_START " List of currents channels:"
# define REPLY_LIST_END " End of list"

# define REPLY_NEED_MORE "461 Not enought parameters"
# define REPLY_NAMES_END ":End of name list"

# define REPLY_TOPIC "332 "
# define REPLY_TOPIC_END " :NO TOPIC"
# define REPLY_401 " :No such nick/channel"
# define REPLY_401_BIS " :No such channel"
# define REPLY_403 " :Invalid channel name"
# define REPLY_431 " 431 No nickname given"
# define REPLY_432 " 432 "
# define REPLY_432_END " :Erroneous Nickname"
# define REPLY_433 " 433 "
# define REPLY_433_END " :Nickname is already in use"
# define REPLY_442 ":You're not on that channel"
# define REPLY_451 ":You have not registered"
# define REPLY_461 " 461 "
# define REPLY_461_END " :Not enough parameters"
# define REPLY_462 " 462 :You may not reregister"

#endif /* !REPLY_H_ */
