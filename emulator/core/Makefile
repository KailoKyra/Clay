NAME    = libclayCore.a

SRC	=						\
        src/main.c					\
        src/clay.c					\
        src/mmu.c					\
        src/io_handler.c				\
        src/components/74xx/74xx138.c                   \
        src/components/74xx/74xx145.c                   \
        src/components/74xx/74xx386.c                   \
        src/components/74xx/74xx574.c                   \
	src/components/ctc/z80ctc.c			\
	src/components/keyboard/keyboard.c		\
	src/components/sio/z80sio.c			\
        src/components/vdp/TMS9918A.c

OBJ	= $(SRC:.c=.o)

RM	= rm -rf

INCLUDES    +=  -I.				\
                -Iincludes			\
                -Ilib

DEFINES     =

#COMMONFLAGS = -Wall -Wextra -ggdb3 -pthread -fpic $(INCLUDES)
COMMONFLAGS = -Wall -Wextra -O3 -pthread -fpic $(INCLUDES)
#COMMONFLAGS = -Wall -Wextra -pthread -fpic $(INCLUDES)

CFLAGS = $(DEFINES) $(COMMONFLAGS)

LDFLAGS = -Wl,-R,'$$ORIGIN/.' 
LDFLAGS	+= -Llib/libz80

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

all: $(NAME)

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
