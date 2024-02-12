# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsteinka <jsteinka@student.42Wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 15:15:48 by jsteinka          #+#    #+#              #
#    Updated: 2024/02/09 10:50:22 by jsteinka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: server client

server:
	gcc -Wall -Wextra -Werror server.c -o server

client:
	gcc -Wall -Wextra -Werror client.c -o client

fclean:
	rm -f server client

clean:
	rm -f server client

re:	clean all
