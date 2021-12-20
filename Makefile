NAME	=		webserv

FILES	=		main Parser Server Socket Request utils_socket puterror Connection_storage Connection \
				set_error_pages open_log handle_requests utils parse_request make_response http_response \
				dir_listing_response cgi CgiClass
HEADERS =		Webserv Server ServConfig Socket Request Connection_storage Connection Cgi CgiClass

CXX		=		clang++

SRC_DIR	=		srcs/
OBJ_DIR	=		objs/
INCLUDE_DIR =	includes/

FLAGS	= -Wall -Wextra -Werror   -I $(INCLUDE_DIR) -g

SRCS 	= $(patsubst %, $(SRC_DIR)%.cpp, $(FILES))
HDRS	= $(patsubst %, $(INCLUDE_DIR)%.hpp, $(HEADERS))
OBJS 	= $(patsubst %, $(OBJ_DIR)%.o, $(FILES))

all: $(NAME)

$(NAME): $(OBJS) $(HDRS)
	$(CXX) -o $(NAME) $(OBJS) $(FLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(HDRS)
	mkdir -p $(OBJ_DIR)
	$(CXX) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f ./$(NAME)

re: fclean all

.PHONY: all clean fclean re