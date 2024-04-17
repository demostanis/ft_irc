NAME 		= ircserv

CXX			= c++
RM			= rm -f
CLONE 		= git clone --depth=1

CXXFLAGS	+= -Wall -Wextra -Werror -std=c++98 -I.
LDLIBS		=

KDO			= kdolib
KDOLIB		= $(KDO)/kdolib.a

SRC 		= Config.cpp\
			  IrcClient.cpp\
			  IrcMessage.cpp\
			  IrcServer.cpp\
			  IrcChannel.cpp\
			  main.cpp\
			  common/lusers.cpp\
			  common/motd.cpp\
			  common/quit.cpp

			  # lusers and motd fucking required because
			  # of recursive references whatever

BOT_SRC     = $(filter-out main.cpp, $(SRC))\
			  bot.cpp

OBJ 		= $(SRC:.cpp=.o)
BOT_OBJ		= $(BOT_SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(KDOLIB) $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) $(KDOLIB) $(LDLIBS)

bot: $(KDOLIB) $(BOT_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(BOT_OBJ) $(KDOLIB) $(LDLIBS)

$(KDOLIB): $(KDO)
	$(MAKE) -C $(KDO)

$(KDO):
	$(CLONE) https://github.com/kodokaii/kdolib_cpp.git $(KDO)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	if [ -d "$(KDO)" ]; then $(MAKE) clean -C $(KDO); fi
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(KDOLIB)
	$(RM) $(NAME)

clear: fclean
	$(RM) -r $(KDO)

re: fclean fast

fast: fclean
	$(MAKE) -j$$(nproc)

.PHONY:		all clean fclean clear re
