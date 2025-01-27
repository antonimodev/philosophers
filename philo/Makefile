# Variables #
NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -pthread
# SANITIZE = -fsanitize=thread -pie
RM = rm -rf

# Libraries #
INC             = -I lib
MAKE_LIB        = make --no-print-directory

# Philosophers sources #
PHILOSOPHER_SRC =	actions/philosophers_actions_utils.c \
					actions/philosophers_eat.c \
					actions/philosophers_sleep.c \
					actions/philosophers_think.c \
					mutex/philosophers_mutex.c \
					parse/philosophers_parse_utils.c \
					parse/philosophers_parse.c \
					src/philosophers_routine.c \
					src/philosophers_time.c \
					src/philosophers.c \
					src/philosophers_monitor.c \
					src/philosophers_initialization.c \
					src/philosophers_malloc.c

# Philosophers objects #
PHILOSOPHER_OBJ = $(addprefix obj/, $(PHILOSOPHER_SRC:.c=.o))

all: $(NAME)

obj/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
# $(SANITIZE) Va con los cc y las flags
$(NAME): $(PHILOSOPHER_OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(PHILOSOPHER_OBJ)
	@echo "$(NAME) created!"
# $(SANITIZE) va antes de -o

clean:
	@$(RM) obj
	@$(RM) .DS_Store
	@$(RM) .vscode
	@echo Objects removed

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re