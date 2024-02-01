# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/12 11:02:58 by lilizarr          #+#    #+#              #
#    Updated: 2024/01/31 14:21:44 by lilizarr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	gnl

SRC =	./gnl_main.c
FLAGS = -Wall -Wextra  #-Werror


all : $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(SRC) -o $@ -D BUFFER_SIZE=$b
	./gnl
fclean:	clean
		rm -f $(NAME)

re: 	fclean all
# use mode: make git m="msg" #
# git:	fclean
# 	@echo $(GREEN)
# 	git add ./
# 	git commit -m "$m"
# 	@echo $(YELLOW)
# 	git push

.PHONY:	all clean fclean re 
