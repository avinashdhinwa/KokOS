#!/bin/bash

set -e

${BASH_SOURCE%/*}/build.sh

if grub-file --is-x86-multiboot ${BASH_SOURCE%/*}/../bin/kokos.bin; then
	echo multiboot confirmed	
	echo copying OS binary and GRUB config
	cp ../bin/kokos.bin ${BASH_SOURCE%/*}/../isodir/boot/kokos.bin
	cp ../src/grub.cfg ${BASH_SOURCE%/*}/../isodir/boot/grub/grub.cfg
	echo building iso
	grub-mkrescue -o ${BASH_SOURCE%/*}/../iso/kokos.iso ${BASH_SOURCE%/*}/../isodir/
	#qemu-system-i386 -cdrom ${BASH_SOURCE%/*}/../iso/kokos.iso
else
	echo the file is not multiboot
fi