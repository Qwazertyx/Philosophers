# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/17 10:34:48 by vsedat            #+#    #+#              #
#    Updated: 2022/09/22 12:43:30 by vsedat           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


##**********##
### COLORS ###
##**********##
BLACK		= \033[1;30m
RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
VIOLET		= \033[1;35m
CYAN		= \033[1;36m
WHITE		= \033[1;37m

IBLACK		= \033[40m
IRED		= \x1b[41m
IGREEN		= \x1b[42m
IYELLOW		= \x1b[43m
IBLUE		= \x1b[44m
IPURPLE		= \x1b[45m
ICYAN		= \x1b[46m
IWHITE		= \x1b[47m

END			= \033[0m
UNDERLINE	= \x1b[4m
REV			= \x1b[7m

##********##
### NAME ###
##********##
NAME	= philo

##***************##
### COMPILATION ###
##**************###
CC		= gcc #-Ofast
CFLAGS	= -Wall -Wextra -Werror
#https://nafuka11.github.io/philosophers-visualizer/  #-g3 -fsanitize=address #leaks -atExit -- ./pipex #-fsanitize=thread 
CMLX	= -framework OpenGL -framework AppKit -g -lmlx -Lmlx

##*******************##
### DIRECTORY PATHS ###
##*******************##
HEADER		= ./incl/${NAME}.h
MLX			= ./mlx
OBJ_PATH	= ./objs
SRC_PATH	= ./srcs

##***********##
### OBJECTS ###
##***********##
SRCS = $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJS = $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

##****************##
### SOURCE FILES ###
##****************##
SOURCES	=	main.c		\
			parsing.c		\
			utils.c		\
			utils2.c		\
			utils3.c		\
			actions.c		\
			checker.c		\


##*********##
### RULES ###
##*********##
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER) Makefile
			@mkdir -p objs
			@echo "$(BLUE)Compiling:$(END)$(CYAN) $<"
			@${CC} ${CFLAGS} -c $< -o $@
			
all:	${NAME}

${NAME}:	${OBJS}
			@${CC} ${CFLAGS} ${OBJS} -o ${NAME}
			@echo "$(GREEN)$(REV)Successful compilation"

leaks:	all
		@echo "$(END)$(VIOLET)you enter an area of testing, be carefull$(END)"
		@leaks -atExit -- ./${NAME} 4 210 100 100 2
		@echo "$(RED)./philo 4 210 100 100 2$(END)"
		@sleep 3
		@leaks -atExit -- ./${NAME} 5 210 100 100
		@echo "$(RED)./philo 5 210 100 100$(END)"
		@sleep 3
		@leaks -atExit -- ./${NAME}
		@echo "$(RED)./philo$(END)"
		@sleep 3
		@leaks -atExit -- ./${NAME} 1 500 200 200
		@echo "$(RED)./philo 1 500 200 200$(END)"
		@sleep 3
		@leaks -atExit -- ./${NAME} 100 800 200 200 4
		@echo "$(RED)./philo 100 800 200 200 4$(END)"

test:	all
		@echo "$(END)$(VIOLET)you enter an area of testing, be carefull$(END)"
		@echo "$(RED)testing with the values:$(VIOLET) 5 800 200 200 20 $(BLUE)no philosopher should die$(END)"
		@sleep 5
		@leaks -atExit -- ./${NAME} 5 800 200 200 20
		@sleep 5
		@echo "$(RED)testing with the values:$(VIOLET) 5 800 200 200 7 $(BLUE)no philosopher should die, every philosopher should have eaten at least once$(END)"
		@sleep 5
		@leaks -atExit -- ./${NAME} 5 800 200 200 7
		@sleep 5
		@echo "$(RED)testing with the values:$(VIOLET) 4 410 200 200 20 $(BLUE)no philosopher should die$(END)"
		@sleep 5
		@leaks -atExit -- ./${NAME} 4 410 200 200 20
		@sleep 5
		@echo "$(RED)testing with the values:$(VIOLET) 4 310 200 100 $(BLUE)one philosopher should die$(END)"
		@sleep 5
		@leaks -atExit -- ./${NAME} 4 310 200 100
		@sleep 5
		@echo "$(RED)testing with the values:$(VIOLET) 2 100 100 100 $(BLUE)one philosopher should die, check the death timings please$(END)"
		@sleep 5
		@leaks -atExit -- ./${NAME} 2 100 100 100
		@sleep 3
		@echo "$(RED)Now it's time for your own tests$(END)"
		
	
clean:
		@rm -f ${OBJS}
		@echo "$(BLUE)$(REV)Object files cleaned$(DEF_COLOR)"

fclean:	clean
		@rm -f ${NAME}
		@echo "$(GREEN)$(REV)Executable files cleaned$(END)"

re:	fclean
	@${MAKE} all
	@echo "$(VIOLET)$(REV)Cleaned and rebuilt everything$(END)"

sus:
	@echo "$(IRED)           ⣠⣤⣤⣤⣤⣤⣶⣦⣤⣄⡀        $(END)"
	@echo "$(IRED)        ⢀⣴⣿⡿⠛⠉⠙⠛⠛⠛⠛⠻⢿⣿⣷⣤⡀     $(END)"
	@echo "$(IRED)        ⣼⣿⠋       ⢀⣀⣀⠈⢻⣿⣿⡄    $(END)"
	@echo "$(IRED)       ⣸⣿⡏   ⣠⣶⣾⣿⣿⣿⠿⠿⠿⢿⣿⣿⣿⣄   $(END)"
	@echo "$(IRED)       ⣿⣿⠁  ⢰⣿⣿⣯⠁       ⠈⠙⢿⣷⡄ $(END)"
	@echo "$(IRED)  ⣀⣤⣴⣶⣶⣿⡟   ⢸⣿⣿⣿⣆          ⣿⣷ $(END)"
	@echo "$(IRED) ⢰⣿⡟⠋⠉⣹⣿⡇   ⠘⣿⣿⣿⣿⣷⣦⣤⣤⣤⣶⣶⣶⣶⣿⣿⣿ $(END)"
	@echo "$(IRED) ⢸⣿⡇  ⣿⣿⡇    ⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃ $(END)"
	@echo "$(IRED) ⣸⣿⡇  ⣿⣿⡇     ⠉⠻⠿⣿⣿⣿⣿⡿⠿⠿⠛⢻⣿⡇  $(END)"
	@echo "$(IRED) ⠸⣿⣧⡀ ⣿⣿⡇                ⣿⣿⠃  $(END)"
	@echo "$(IRED)  ⠛⢿⣿⣿⣿⣿⣇     ⣰⣿⣿⣷⣶⣶⣶⣶⠶ ⢠⣿⣿   $(END)"
	@echo "$(IRED)       ⣿⣿     ⣿⣿⡇ ⣽⣿⡏⠁  ⢸⣿⡇   $(END)"
	@echo "$(IRED)       ⣿⣿     ⣿⣿⡇ ⢹⣿⡆   ⣸⣿⠇   $(END)"
	@echo "$(IRED)       ⢿⣿⣦⣄⣀⣠⣴⣿⣿⠁ ⠈⠻⣿⣿⣿⣿⡿⠏    $(END)"
	@echo "$(IRED)       ⠈⠛⠻⠿⠿⠿⠿⠋⠁              $(END)"

.PHONY:	all clean fclean re sus leaks test

