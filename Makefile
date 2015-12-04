# Makefile ******************************************************************* #
#                                                                              #
#        |- By: plo4ox <plo4ox@4ox.com>                                        #
#        |_                                                                    #
#          |- Created: 2015/12/04 10:51:18 by plo4ox                           #
#          |- Updated: 2015/12/04 10:51:26 by plo4ox                           #
#                                                                              #
# ******************************************************************* Makefile #

NAME = simpleWeather
CC = clang
SRC = srcs/main.c srcs/curl_function.c srcs/json_function.c \
    srcs/strings_function.c
OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Werror -Wextra
IFLAGS = -I include
LIB = -lcurl

T := $(words $(SRC))
N := x
C = $(words $N)$(eval N := x $N)
ECHO_PERCENT = echo "\r`expr " [ \`expr $C '*' 99 / $T\`" : '.*\(....\)$$'`%]"

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n[100%] \033[0;35mCreate $@\033[0;0m"
	$(CC) $(FLAGS) -o $@ $^ $(LIB)

%.o: %.c
	@$(ECHO_PERCENT) "\033[0;32mBuilding C object\033[1;32m $@\033[0;0m"
	$(CC) $(FLAGS) $(IFLAGS) -c $< -o $@

clean:
	@echo "\033[0;31m Clean C object files...\033[0;0m"
	rm -rf $(OBJ)

fclean: clean	
	@echo "\033[0;31m Delete $(NAME) \033[0;0m"
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
