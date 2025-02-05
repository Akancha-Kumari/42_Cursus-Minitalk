
NAME_SERVER = server
NAME_CLIENT = client

CC         = cc
CFLAGS     = -Wall -Wextra -Werror

SRC_DIR = src
PRINTF_DIR = ft_printf

SRCS_SERVER = $(SRC_DIR)/server.c 
SRCS_CLIENT = $(SRC_DIR)/client.c $(SRC_DIR)/client_utils.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

PRINTF = $(PRINTF_DIR)/libftprintf.a

all: $(PRINTF) $(NAME_SERVER) $(NAME_CLIENT)

$(PRINTF):
	make -C $(PRINTF_DIR)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(PRINTF) -o $(NAME_SERVER)


$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(PRINTF) -o $(NAME_CLIENT)


clean:
	make clean -C $(PRINTF_DIR)
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)


fclean: clean
	make fclean -C $(PRINTF_DIR)
	rm -f $(NAME_SERVER) $(NAME_CLIENT) $(PRINTF)

re: fclean all

.PHONY: all clean fclean re

