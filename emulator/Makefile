all:
	./core/lib/compile_libz80.sh
	make -C core
	`locate qmake|head -n1` -makefile -o gui/gui.mk gui/gui.pro
	cd gui; make -f gui.mk

clean:
	make clean -C core

fclean: clean
	make fclean -C core
	rm claymulator

re: fclean all

.PHONY: all clean fclean re
