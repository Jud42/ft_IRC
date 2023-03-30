TARGET				:= ircserv
BUILD				:=

# sources --------------------------------------------------

include Makefile_SRCS.mk

# sources --------------------------------------------------

UNAME := $(shell uname -s)

ifeq ($(UNAME), Darwin)
CXX	=	g++-12
CFLAGS	=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Werror
CFALGS	+=  -Wfatal-errors
CFLAGS	+=	-g
CFLAGS	+=	-std=c++98
endif

ifeq ($(UNAME), Linux)
CXX	=	g++
CFLAGS	=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Werror
CFLAGS	+=	-g
CFLAGS	+=	-std=c++98
CFLAGS	+=	-lstdc++
endif

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR				:= srcs
INCDIR				:= includes
BUILDDIR			:= objs
TARGETDIR			:= ./
SRCEXT				:= cpp
DEPEXT				:= d
OBJEXT				:= o

OBJECTS				:= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))
OBJECTS_BONUS		:= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES_BONUS:.$(SRCEXT)=.$(OBJEXT)))

#Flags, Libraries and Includes
cflags.release		:= -Wall -Werror -Wextra #-DDEBUG -DDEBUG_SV -DDEBUG_US
cflags.valgrind		:= -Wall -Werror -Wextra -DDEBUG -DDEBUG_SV 
cflags.debug		:= -Wall -Werror -Wextra -DDEBUG -ggdb -fsanitize=address -fno-omit-frame-pointer
CFLAGS				:= $(cflags.$(BUILD))
CPPFLAGS			:= $(cflags.$(BUILD))

lib.release			:= 
lib.valgrind		:= $(lib.release)
lib.debug			:= $(lib.release) -fsanitize=address -fno-omit-frame-pointer
LIB					:= $(lib.$(BUILD))

INC					:= -I$(INCDIR) -I/usr/local/include
INCDEP				:= -I$(INCDIR)



#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
DEFAULT = \033[0m

# Multi platforms
ECHO				:= echo

# Escape sequences (ANSI/VT100)
ES_ERASE			:= "\033[1A\033[2K\033[1A"
ERASE				:= $(ECHO) $(ES_ERASE)

GREP				:= grep --color=auto --exclude-dir=.git
NORMINETTE			:= norminette `ls`

# Default Make
all: $(TARGETDIR)/$(TARGET)
	@printf "$(GREEN)Executable created.. $(TARGET) $(DEFAULT)\n"

# Remake
re: fclean all

# Clean only Objects
clean:
	@printf "$(RED)Removed ./$(TARGET)  $(DEFAULT)\n"
	@$(RM) -f *.d *.o
	@printf "$(RED)Removed ./$(BUILDDIR)  $(DEFAULT)\n"
	@$(RM) -rf $(BUILDDIR)


# Full Clean, Objects and Binaries
fclean: clean
	@printf "$(RED)Removed $(TARGET)  $(DEFAULT)\n"
	@$(RM) -rf $(TARGETDIR)/$(TARGET)


# Link
$(TARGETDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@printf "$(YELLOW)linking.. $^ $(DEFAULT)\n"
	$(CXX) -o $(TARGETDIR)/$(TARGET) $^ $(LIB)
	@$(ERASE)
	@$(ERASE)
	@printf "$(GREEN)Linking completed $(TARGET)  $(DEFAULT)\n"

$(BUILDIR):
	@mkdir -p $@

# Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)Creating executable.. $@ $(DEFAULT)\n"
	$(CXX) $(CPPFLAGS) $(INC) -c -o $@ $<
	@$(CXX) $(CPPFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@$(ERASE)
	@$(ERASE)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp


# Non-File Targets
.PHONY: all re clean fclean


