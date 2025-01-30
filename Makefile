CC = cc
CFLAGS = ${CC} -Wall -Wextra -Werror

SERVER = server
CLIENT = client
SRCS_SERVER = server.c
SRCS_CLIENT = client.c
SRCS_UTILS = client_utils.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_UTILS  = $(SRCS_UTILS:.c=.o)

RM = rm -rf

all: $(SERVER) $(CLIENT)

$(SERVER) $(CLIENT): $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_UTILS)
	${CCFLAGS} ${OBJS_SERVER} -o ${SERVER}
	${CCFLAGS} ${OBJS_CLIENT} $(OBJS_UTILS) -o ${CLIENT}

%.o: %.c
	$(CCFLAGS) -c $< -o $@

clean:
	$(MAKE) clean
	$(RM) $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_UTILS)

fclean: clean
	$(MAKE) fclean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
