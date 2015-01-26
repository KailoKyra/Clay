#!/bin/bash

if [ ! -d libz80 ] ; then
	git clone https://github.com/ggambetta/libz80.git --depth=1
	cd libz80
	make
fi