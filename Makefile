NAME	=	ircserv
# sources --------------------------------------------------
SRCD	=	/
SRCS	=	$(SRCD)/main.cpp 
# sources --------------------------------------------------

UNAME := $(shell uname -s)

ifeq ($(UNAME), Darwin)
CC		=	g++-12
CFLAGS	=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Werror
CFALGS	+=  -Wfatal-errors
CFLAGS	+=	-g
CFLAGS	+=	-std=c++98
endif

ifeq ($(UNAME), Linux)
CC		=	g++
CFLAGS	=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Werror
CFLAGS	+=	-g
CFLAGS	+=	-std=c++98
CFLAGS	+=	-lstdc++
endif

OFLAGS	=	-fsanitize=address

OBJD	=	objs
OBJS	=	$(addprefix $(OBJD)/, $(notdir $(SRCS:.cpp=.o)))

RM		=	rm -rf

all : $(NAME)

$(NAME):	$(OBJS)
	@printf "$(YELLOW)Creating executable..$(DEFAULT)\n"
	@$(CC) $(OBJS) $(OFLAGS) $(CLIB) -o $(NAME)
	@printf "$(GREEN)---> $(NAME) is ready$(DEFAULT)\n"

$(OBJD)/%.o : %.cpp | $(OBJD)
	@printf "$(YELLOW)----------------------------------------- $<\n"
	@printf "$(YELLOW)Compiling $(DEFAULT)$<\n"
	@$(CC) $(CFLAGS) -I$(SRCD) -o $@ -c $<

$(OBJD) :
	@mkdir -p $(OBJD)

clean:
	@$(RM) $(OBJD)
	@printf "$(RED)Removed $(CYAN)$(OBJD)$(DEFAULT)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(RED)Removed $(CYAN)$(NAME)$(DEFAULT)\n"

re:	fclean all


.PHONY: all clean fclean re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
DEFAULT = \033[0m
