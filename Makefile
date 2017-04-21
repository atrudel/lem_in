# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atrudel <atrudel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/07 16:08:49 by atrudel           #+#    #+#              #
#    Updated: 2017/04/21 10:25:54 by atrudel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB_PATH = ./libft
OBJ_PATH = ./obj

SRC = 	parsing1.c \
		parsing2.c \
		bfs.c \
		path_optimizing.c \
		path_utils.c \
		path_utils2.c \
		visualizer1.c \
		visualizer2.c \
		vis.line.c \
		vis.draw.c \
		vis.utils.c \
		utils.c \
		list_utils.c \
		ants.c \
		output.c \
		instructions.c \
		data.deletion.c

OBJ = 	$(addprefix $(OBJ_PATH)/, $(SRC:.c=.o))

INC = 	lem_in.h\
		visualizer.h \
		$(LIB_PATH)/includes/libft.h

FLAGS = -Wall -Wextra -Werror

all: lem-in visu-hex

lem-in: $(OBJ_PATH)/main.lem_in.o $(OBJ) $(LIB_PATH)/libft.a
	gcc -o lem-in $(OBJ_PATH)/main.lem_in.o $(OBJ) -lmlx -framework OpenGL -framework AppKit -L $(LIB_PATH) -lft

visu-hex: $(OBJ_PATH)/main.visu_hex.o $(OBJ) $(LIB_PATH)/libft.a
	gcc -o visu-hex $(OBJ_PATH)/main.visu_hex.o $(OBJ) -lmlx -framework OpenGL -framework AppKit -L $(LIB_PATH) -lft

$(LIB_PATH)/libft.a: $(LIB_PATH)/Makefile $(LIB_PATH)/includes/libft.h
	@make -C $(LIB_PATH)/ fclean && make -C $(LIB_PATH)
	@echo "libft created"

$(OBJ_PATH)/%.o: %.c $(INC)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	gcc -o $@ -c $< $(FLAGS) -I $(LIB_PATH)/includes

clean:
	rm -Rf $(OBJ_PATH)

fclean: clean
	rm -f lem-in visu-hex
	@make -C $(LIB_PATH)/ fclean

re: fclean all

test: lem-in
	@sh test/test.sh

norme:
	make -C $(LIB_PATH)/ norme
	norminette $(SRC) $(INC)

git:
	git add $(SRC) $(INC) Makefile
	git commit -m "automatic upload"
	git push

.PHONY: clean fclean re test norme
