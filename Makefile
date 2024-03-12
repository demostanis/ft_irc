NAME 		= ircserv
MITM		= mitm

CXX			= c++
RM			= rm -f
CLONE 		= git clone --depth=1

CXXFLAGS	+= -Wall -Wextra -Werror -std=c++98
LDLIBS		=

KDO			= kdolib
KDOLIB		= $(KDO)/kdolib.a

SRC 		= BNF/BNFAlts.cpp\
			  BNF/BNFCat.cpp\
			  BNF/BNFChar.cpp\
			  BNF/BNFFind.cpp\
			  BNF/BNFInher.cpp\
			  BNF/BNFParser.cpp\
			  BNF/BNFRange.cpp\
			  BNF/BNFRep.cpp\
			  BNF/BNFString.cpp\
			  IrcMessage.cpp\
			  IrcServer.cpp\
			  main.cpp\
			  Mitm.cpp\
			  Socket.cpp\
			  SocketTcpClient.cpp\
			  SocketTcpServer.cpp\
			  Config.cpp

SRC_MITM	= Mitm.cpp\
			  Socket.cpp\
			  SocketTcpClient.cpp\
			  SocketTcpServer.cpp

OBJ 		= $(SRC:.cpp=.o)
OBJ_MITM	= $(SRC_MITM:.cpp=.o)

all: $(NAME)

$(NAME): $(KDOLIB) $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) $(KDOLIB) $(LDLIBS)

$(MITM): $(KDOLIB) $(OBJ_MITM)
	$(CXX) $(CXXFLAGS) -o $(MITM) $(OBJ_MITM) $(KDOLIB) $(LDLIBS)

$(KDOLIB): $(KDO)
	$(MAKE) -C $(KDO)

$(KDO):
	$(CLONE) https://github.com/kodokaii/kdolib_cpp.git $(KDO)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	if [ -d "$(KDO)" ]; then $(MAKE) clean -C $(KDO); fi
	$(RM) $(OBJ)
	$(RM) $(OBJ_MITM)

fclean: clean
	$(RM) $(KDOLIB)
	$(RM) $(NAME)
	$(RM) $(MITM)

clear: fclean
	$(RM) -r $(KDO)

re: fclean all

fast: fclean
	$(MAKE) -j$$(nproc)

.PHONY:		all clean fclean clear re
