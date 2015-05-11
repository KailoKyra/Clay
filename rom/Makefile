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
defines.asm \
basic/basic.asm \
basic/basic_data.asm \
devices/devices_defines.asm \
devices/ctc/z80ctc/ctc.asm \
devices/ctc/z80ctc/ctc_defines.asm \
devices/ctc/z80ctc/ctc_interrupts.asm \
devices/ctc/z80ctc/ctc_registers_defines.asm \
devices/mmu/mmu_defines.asm \
devices/sio/z80sio/sio.asm \
devices/sio/z80sio/sio_defines.asm \
devices/sio/z80sio/sio_interrupts.asm \
devices/sio/z80sio/sio_registers_defines.asm \
devices/sound/ay_3_8912/ay_defines.asm \
devices/sound/ay_3_8912/ay_registers_defines.asm \
devices/sound/ay_3_8912/ay.asm \
devices/vdp/tms9918/vdp.asm \
kernel/kernel.asm \
kernel/kernel_data.asm \
bootloader/copy_rom_to_ram.asm \
bootloader/init.asm \
kernel/interrupts/interrupts.asm \
kernel/interrupts/interrupts_vector_table.asm

RM		= rm -rf

$(NAME): $(SRC)
	$(CC) main.asm -o $(NAME)

all: $(NAME)

fclean:
	@$(RM) $(NAME)

re: fclean all

.PHONY: all fclean re
