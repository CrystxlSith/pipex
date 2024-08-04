# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crystal <crystal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/22 12:06:36 by jopfeiff          #+#    #+#              #
#    Updated: 2024/08/01 13:11:32 by crystal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c process.c utils.c
CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -I./includes/
RM = rm -rf
EXEC = pipex
NAME = pipex.a
OBJS = $(SRCS:.c=.o)

RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m
MAGENTA= \033[35m
CYAN   = \033[36m
RESET  = \033[0m

.SILENT:

all: pipex 

# so_long: $(NAME) $(OBJS)
# 	echo "${CYAN}Compiling so_long...${RESET}"
# 	cc so_long.a libft.a mlx/libmlx.a mlx/libmlx_Linux.a -lX11 -lXext -o so_long
# 	echo "${GREEN}Succes!!!${RESET}"

pipex: $(NAME) $(OBJS)
	echo "${CYAN}Compiling pipex...${RESET}"
	cc pipex.a libft/libft.a -o pipex
	echo "${GREEN}Succes!!!${RESET}"
$(NAME): $(OBJS)
	echo "${CYAN}Compiling libft...${RESET}"
	$(MAKE) --no-print-directory -C ./libft
	ar rc $(NAME) $(OBJS)
clean:
	echo "${RED}Cleaning libft && Push_swap...${RESET}"
	$(MAKE) clean --no-print-directory -C ./libft
	$(RM) $(OBJS) objs
	$(RM) libft.a
	echo "${GREEN}Succes!!!${RESET}"
	
fclean: clean
	$(MAKE) fclean --no-print-directory -C ./libft
	echo "${RED}Cleaning exucutable files...${RESET}"
	$(RM) $(NAME) so_long
	echo "${GREEN}Succes!!!${RESET}"
re: fclean all

.PHONY: all clean fclean re