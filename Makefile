# Executable Names
NAME_SERVER = server
NAME_CLIENT = client

# Compiler and Flags
CC         = cc
CFLAGS     = -Wall -Wextra -Werror

# Source Files
SRCS_SERVER = server.c
SRCS_CLIENT = client.c client_utils.c

# Object Files
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

# Default rule (compile both server and client)
all: $(NAME_SERVER) $(NAME_CLIENT)

# Compile server
$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJS_SERVER)

# Compile client
$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJS_CLIENT)

# Compile .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)

# Clean everything including binaries
fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)

# Recompile everything
re: fclean all

# Phony Targets
.PHONY: all clean fclean re


