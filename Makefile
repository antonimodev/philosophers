# Variables #
NAME = philosophers
CC = gcc
CFLAGS = -Wall -Wextra -g -pthread #-Werror
RM = rm -rf

# Libraries #
INC             = -I lib
MAKE_LIB        = make --no-print-directory

# Philosophers sources #
PHILOSOPHER_SRC =	philo/parse.c \
                    philo/philosophers.c \
					philo/philosophers_utils.c \
					philo/philosophers_threads.c \

# Philosophers objects #
PHILOSOPHER_OBJ = $(addprefix obj/, $(PHILOSOPHER_SRC:.c=.o))

all: $(NAME)

obj/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(PHILOSOPHER_OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(PHILOSOPHER_OBJ)
	@echo "$(NAME) created!"

clean:
	@$(RM) obj
	@$(RM) .DS_Store
	@$(RM) .vscode
	@echo Objects removed

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(PLACEHOLDER_DIR)/PLACEHOLDER.a

re: fclean all

.PHONY: all clean fclean re