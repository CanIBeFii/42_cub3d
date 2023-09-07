# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 13:29:16 by mibernar          #+#    #+#              #
#    Updated: 2023/09/04 15:23:14 by mibernar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/
LIBFT = $(LIBFT_DIRECTORY)libft.a

MINILIBX_DIRECTORY = ./minilibx-linux/
MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)
MINILIBX = $(MINILIBX_DIRECTORY)libmlx.a

HEADERS_LIST = cub3d.h
HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_LIST = colors.c file_checker.c free.c handle_window.c keys.c main.c \
				map_checker.c map_info.c map_info_utils.c map_utils.c \
				map_validator.c error.c textures.c movements.c player.c dda.c \
				draw.c
SOURCES_DIRECTORY = ./sources/
SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS_DIRECTORY = objects/
OBJECTS = $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

CC = gcc
FLAGS = -Wall -Werror -Wextra -g3
LIBRARIES = -L$(LIBFT_DIRECTORY) -lft -L$(MINILIBX_DIRECTORY) -lmlx_Linux -lXext -lX11 -lm
INCLUDES = -I $(HEADERS_DIRECTORY) -I $(LIBFT_HEADERS) -I $(MINILIBX_HEADERS)

# COLORS

GREEN = \033[0;92m
RED = \033[0;91m
CYAN = \033[0;96m
BLUE = \033[0;94m
YELLOW = \033[0;93m
RESET = \033[0m

# ECHO

ifeq "$(TERM)" "xterm-256color"
	ECHO = echo
else
	ECHO = echo -e
endif

# RULES

all: ## Compiles the whole project
	@make -s $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(ECHO) "\n\nStarting compile, now have some $(BLUE)colorful $(RED)text $(YELLOW)slayyyy$(RESET)"
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS) $(LIBRARIES) -o $(NAME)
	@$(ECHO) "$(CYAN)$(NAME):$(RESET) $(GREEN)object files$(RESET) were created and have come to free us, $(YELLOW)monkeys$(RESET) united."
	@$(ECHO) "$(CYAN)$(NAME):$(RESET) $(GREEN)$(NAME)$(RESET) was created, like $(BLUE)god$(RESET) intended"
	@$(ECHO) "$(CYAN)$(NAME):$(RESET) now watch this video : $(RED)https://www.youtube.com/watch?v=xvFZjo5PgG0$(RESET)" 

$(OBJECTS_DIRECTORY): ## Creates the objects directory
	@mkdir -p $(OBJECTS_DIRECTORY)
	@$(ECHO) "$(CYAN)$(NAME): $(GREEN)$(OBJECTS_DIRECTORY)$(RESET) was created $(YELLOW)WOW $(BLUE)OMG$(RESET) i'm so $(GREEN)talented$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS) ## Compiles each '*.c'
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@$(ECHO) "$(GREEN).$(RESET)\c"

$(LIBFT): ## Compiles the libft
	@$(ECHO) "$(CYAN)$(NAME): $(RESET)Creating $(GREEN)$(LIBFT)$(RESET)"
	@make -sC $(LIBFT_DIRECTORY) --no-print-directory

$(MINILIBX): ## adeus
	@$(ECHO) "$(CYAN)$(NAME):$(RESET) Creating $(GREEN)$(MINILIBX)$(RESET) now a bunch of words will appear i have $(RED)no$(RESET) idea what they mean, but we $(YELLOW)roll$(RESET)"
	@make -sC $(MINILIBX_DIRECTORY)
	
clean: ## Cleans all the '*.o' files and deletes the objects directory
	@rm -rf $(OBJECTS_DIRECTORY)
	@$(ECHO) "$(CYAN)$(NAME): $(RED)$(OBJECTS_DIRECTORY)$(RESET) was deleted, *insert sadge emote*"
	@$(ECHO) "$(CYAN)$(NAME): $(RED)object files$(RESET) deleted, it was like Voldemort said *FETUS DELETUS*"
	@make -sC $(LIBFT_DIRECTORY) clean --no-print-directory

fclean: clean ## Calls clean and deletes all executables and compiled libs
	@rm -f $(MINILIBX)
	@$(ECHO) "$(CYAN)$(NAME): $(RED)$(MINILIBX)$(RESET) was deleted"
	@$(ECHO) "$(CYAN)$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@$(ECHO) "$(CYAN)$(NAME): $(RED)$(NAME) was deleted$(RESET)"
	@make -sC $(LIBFT_DIRECTORY) fclean --no-print-directory

re: ## Deep cleans the project and recompiles it
	@make -s fclean
	@make -s all
	
help: ## Shows all the options and it's uses
	@echo "usage: make [target]"
	@echo ""
	@egrep "^(.+)\:\ .*##\ (.+)" ${MAKEFILE_LIST} | sed 's/:.*##/#/' | column -t -c 2 -s '#'
	@curl -L https://raw.githubusercontent.com/keroserene/rickrollrc/master/roll.sh | bash

.PHONY	: re fclean clean all
