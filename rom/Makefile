##
## Makefile for emulator in /home/kailokyra/clay/emulator
## 
## Made by maxime croizer
## Login   <croize_m@epitech.net>
## 
## Started on  Mon Jul 29 02:12:25 2013 maxime croizer
## Last update Tue Feb 11 05:34:21 2014 maxime croizer
##

CC		= z80asm -v

NAME		= clayrom.rom

SRC		= main.asm		\
	ay_registers_defines.asm	\
	basic/basic.asm			\
	basic/basic_data.asm		\
	copy_rom_to_ram.asm 		\
	ctc.asm 			\
	ctc_interrupts.asm 		\
	ctc_registers_defines.asm 	\
	defines.asm 			\
	init.asm 			\
	interrupts.asm 			\
	interrupts_vector_table.asm 	\
	kernel/kernel.asm 		\
	kernel/kernel_data.asm 		\
	pio.asm 			\
	pio_registers_defines.asm 	\
	sio.asm 			\
	sio_interrupts.asm 		\
	sio_registers_defines.asm 	\
	vdp.asm

RM		= rm -rf

$(NAME): $(SRC)
	$(CC) main.asm -o $(NAME)

all: $(NAME)

fclean:
	@$(RM) $(NAME)

re: fclean all

.PHONY: all fclean re
