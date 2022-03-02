SRC_SERVER = ft_server.c ft_memset.c ft_putnbr_fd.c ft_atoi.c
OBJS_SERVER = $(SRC_SERVER:.c=.o)
SRC_CLIENT = ft_client.c ft_memset.c ft_putnbr_fd.c ft_atoi.c
OBJS_CLIENT = $(SRC_CLIENT:.c=.o)
CC = gcc
DEPS = $(OBJS_SERVER:.o=.d)
DEPS_CLIENT = $(OBJS_CLIENT:.o=.d)
CFLAGS  = -Wall -Wextra -Werror
SERVER = server
CLIENT = client

all: $(SERVER) $(CLIENT)

$(CLIENT): $(OBJS_CLIENT)
	$(CC) $(OBJS_CLIENT) -o $@

$(SERVER): $(OBJS_SERVER)
	$(CC) $(OBJS_SERVER) -o $@

.PHONY: clean fclean all re

-include $(DEPS)
-include $(DEPS_CLIENT)

.c.o:
	$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT) $(DEPS) $(DEPS_CLIENT)

fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

bonus: all