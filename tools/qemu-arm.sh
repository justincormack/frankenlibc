#!/bin/sh

qemu-system-arm -M versatilepb -m 128M -nographic -monitor null -serial null -semihosting -kernel "$*"
