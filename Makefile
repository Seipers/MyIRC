##
## Makefile for myir in /home/bibzor/rendu/NETWORK/PSU_2016_myirc
## 
## Made by bibzor
## Login   <sebastien.vidal@epitech.eu>
## 
## Started on  Wed Jun  7 11:46:32 2017 bibzor
## Last update Sun Jun 11 19:22:52 2017 bibzor
##

NAME	=	server

NAME2	=	client

DIR	=	src/

S_DIR	=	src/server/

CMD_DIR	=	src/cmd/

TOOLS	=	src/tools/

I_DIR	=	include/

SRC	=	$(S_DIR)main.c \
		$(TOOLS)tools.c \
		$(TOOLS)epur_str.c \
		$(TOOLS)my_str_to_wordtab.c \
		$(TOOLS)list.c \
		$(TOOLS)list2.c \
		$(S_DIR)exec_server.c \
		$(S_DIR)init_fd.c \
		$(S_DIR)read.c \
		$(S_DIR)channel.c \
		$(S_DIR)handle_cmd.c \
		$(CMD_DIR)join_cmd.c\
		$(CMD_DIR)kill_cmd.c\
		$(CMD_DIR)list_cmd.c\
		$(CMD_DIR)names_cmd.c\
		$(CMD_DIR)nick_cmd.c\
		$(CMD_DIR)part_cmd.c\
		$(CMD_DIR)pass_cmd.c\
		$(CMD_DIR)pong_cmd.c\
		$(CMD_DIR)privmsg_cmd.c\
		$(CMD_DIR)quit_cmd.c\
		$(CMD_DIR)user_cmd.c\

SRC2	=	./src/client/client.c \

OBJ	=	$(SRC:.c=.o)

OBJ2	=	$(SRC2:.c=.o)

CFLAGS	+=	-W -Wall -Wextra -Werror -I $(I_DIR)

CC	=	gcc

all:		server client

server:		$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

client:		$(OBJ2)
		$(CC) -o $(NAME2) $(OBJ2)

clean:
		rm -f $(OBJ)
		rm -f $(OBJ2)

fclean:		clean
		rm -f $(NAME)
		rm -f $(NAME2)

re:		fclean all

.PHONY:		re clean fclean all
