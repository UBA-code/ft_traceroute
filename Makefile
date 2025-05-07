UTILS_FLDR=./utils
SRC=ft_traceroute.c \
	$(UTILS_FLDR)/errors/ft_error.c \
	$(UTILS_FLDR)/errors/ft_error_printf.c \
	$(UTILS_FLDR)/options/usage.c \
	$(UTILS_FLDR)/parsing/parser.c \
	$(UTILS_FLDR)/helpers/freeResources.c \
	$(UTILS_FLDR)/helpers/calcCksum.c \
	$(UTILS_FLDR)/helpers/initializer.c \
	$(UTILS_FLDR)/helpers/ft_itoa.c \
	$(UTILS_FLDR)/helpers/ft_putNumber.c \
	$(UTILS_FLDR)/pinger/pinger.c \
	$(UTILS_FLDR)/pinger/sendPacket.c \
	$(UTILS_FLDR)/pinger/receivePacket.c \
	# $(UTILS_FLDR)/utils2.c
OBJ=$(SRC:.c=.o)
INC=./includes
CC=gcc
CFLAGS=-Wall -Wextra -Werror -I$(INC)
RM=rm -f
NAME=ft_traceroute

GREEN=\033[0;32m
RED=\033[0;31m
YELLOW=\033[0;33m
NC=\033[0m

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lm
	@echo "$(GREEN)Compilation successful!$(NC)"
	@echo "$(YELLOW)Executable created: $(NAME)$(NC)"
	@echo "$(YELLOW)To run the program, use: ./$(NAME) <IP_ADDRESS>$(NC)"

clean:
	$(RM) $(OBJ)
	@echo "$(RED)Cleaned up object files!$(NC)"

fclean: clean
	$(RM) $(NAME)
	@echo "$(RED)Cleaned up executable!$(NC)"

re: fclean all
	@echo "$(GREEN)Recompiled everything!$(NC)"
