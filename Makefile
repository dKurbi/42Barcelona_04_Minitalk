# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/30 17:48:56 by dkurcbar          #+#    #+#              #
#    Updated: 2023/09/11 15:01:24 by dkurcbar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=   minitalk
CLIENT	=	client
C_BONUS = 	client_bonus
SERVER	=	server
S_BONUS = 	server_bonus
	#libft Variables
LIBFT		=	./ft_libft/libft.a
LIBFT_DIR	=	./ft_libft

	# Mandatory Variables #
SRC_C	=	client.c
SRC_S	=	server.c
SRC_C_B	=	client_bonus.c
SRC_S_B	=	server_bonus.c

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

bonus: 
	@ $(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@ $(MAKE) --no-print-directory $(SERVER)
	@ $(MAKE) --no-print-directory $(CLIENT)
	@ $(MAKE) --no-print-directory $(S_BONUS)
	@ $(MAKE) --no-print-directory $(C_BONUS)

$(NAME): all

$(SERVER): $(LIBFT) $(SRC_S) Makefile
	@ $(CC) $(CFLAG) $(SRC_S) $(INC) -o $(SERVER)
	@printf "$(_SUCCESS) server ready.\n"

$(S_BONUS): $(LIBFT) $(SRC_S_B) Makefile
	@ $(CC) $(CFLAG) $(SRC_S_B) $(INC) -o $(S_BONUS)
	@printf "$(_SUCCESS) BONUS server ready.\n"


$(CLIENT): $(LIBFT) $(SRC_C) Makefile
	@ $(CC) $(CFLAG) $(SRC_C) $(INC) -o $(CLIENT)
	@printf "$(_SUCCESS) client ready.\n"

$(C_BONUS): $(LIBFT) $(SRC_C_B) Makefile
	@ $(CC) $(CFLAG) $(SRC_C_B) $(INC) -o $(C_BONUS)
	@printf "$(_SUCCESS) BONUS client ready.\n"


$(LIBFT): 
	@ $(MAKE) -C $(LIBFT_DIR)

clean:
	@ $(MAKE) --no-print-directory clean -C $(LIBFT_DIR)
	@ $(RM) $(CLIENT) $(SERVER) $(C_BONUS) $(S_BONUS)
	@printf "$(_INFO) client removed.\n"
	@printf "$(_INFO) server removed.\n"
	@printf "$(_INFO) BONUS client removed.\n"
	@printf "$(_INFO) BONUS server removed.\n"

fclean: clean
	@ $(MAKE) --no-print-directory fclean -C $(LIBFT_DIR)
	@ $(RM) $(CLIENT) $(SERVER) $(C_BONUS) $(S_BONUS)
	@printf "$(_INFO) client removed.\n"
	@printf "$(_INFO) server removed.\n"
	@printf "$(_INFO) BONUS client removed.\n"
	@printf "$(_INFO) BONUS server removed.\n"

re:	fclean all

.PHONY: all clean fclean re

