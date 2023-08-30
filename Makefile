# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/30 17:48:56 by dkurcbar          #+#    #+#              #
#    Updated: 2023/08/30 17:48:56 by dkurcbar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



	#Library Name
NAME	=   minitalk
CLIENT	=	client
SERVER	=	server

	#libft Variables
LIBFT		=	./ft_libft/libft.a
LIBFT_DIR	=	./ft_libft

	# Mandatory Variables #
SRC_C	=	client.c
SRC_S	=	server.c

CC		:=	gcc
CFLAGS	:=	-Wall -Werror -Wextra
AR		:=	ar rcs
RM		:=	rm -f
MODE	:=	normal
INC		=	-I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft

all: 
	@ $(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@ $(MAKE) --no-print-directory $(SERVER)
	@ $(MAKE) --no-print-directory $(CLIENT)

$(NAME): all

$(SERVER): $(LIBFT) $(SRC_S) Makefile
	@ $(CC) $(CFLAG) $(SRC_S) $(INC) -o $(SERVER)
	@printf "$(_SUCCESS) server ready.\n"

$(CLIENT): $(LIBFT) $(SRC_C) Makefile
	@ $(CC) $(CFLAG) $(SRC_C) $(INC) -o $(CLIENT)
	@printf "$(_SUCCESS) client ready.\n"

$(LIBFT): 
	@ $(MAKE) -C $(LIBFT_DIR)

clean:
	@ $(RM) $(CLIENT) $(SERVER)
	@printf "$(_INFO) client removed.\n"
	@printf "$(_INFO) server removed.\n"

fclean: clean
	@ $(MAKE) fclean -C $(LIBFT_DIR)
	@ $(RM) $(CLIENT) $(SERVER)
	@printf "$(_INFO) client removed.\n"
	@printf "$(_INFO) server removed.\n"

re:	fclean all

.PHONY: all clean fclean re

