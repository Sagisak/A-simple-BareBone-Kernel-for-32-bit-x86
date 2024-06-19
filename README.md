# A-simple-BareBone-Kernel-for-32-bit-x86
This is a respitory to make a simple kernel from the tutorial OS dev wiki. All of the creation will revolve and followed from that paticular website. Information is also get from searching the web or simply asking an AI chatbot, like CHATGPT, as an assitance. Below is the link from the documentation I read from:

https://wiki.osdev.org/Bare_Bones

This is still a minimal system so it is not an example for a properly structure project

# GCC cross compiler needed
For this project, GCC cross compiler needed to be created first before the project can be started. I have created a protable GCC cross compiler just for this particular problem and the link for that github and how to use it is below:

https://github.com/Sagisak/GCC-Cross-Compiler-Creation

# making boot.o
Head to boot folder and do this command:
```sh
i686-elf-as boot.s -o boot.o
```

# Making kernel.o
Head to kernel folder and do this command:
```sh
i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
```

# Linking the kernel.o with boot.o
To create the myos.bin you need to make link between boot.o and kernel.o. This is the code below:

```sh
i686-elf-gcc -T kernel/linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot/boot.o kernel/kernel.o -lgcc
```

# Verifying Multiboot

To verify, while GRUB is also install, you can use the file name "grub-file_checker" to check it:

```sh
source grub-file_checker 
```

# Booting the Kernel
with the directory isodir already been made, with the child directory of boot and grub as the most inner child, use this command to make the myos.iso by the help of grub-mkreskue:

```sh
cp myos.bin isodir/boot/myos.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o myos.iso isodir
```

# Testing the operating System
You can use the command below to start the os:

```sh
qemu-system-i386 -cdrom myos.iso
```

Though is only saying "Hello, kernel world!", I thinks it's a good start.


## Licensing and Source Code Disclosure

# GRUB Bootloader

This ISO contains the GNU GRUB bootloader, which is licensed under the GNU General Public License (GPL). In compliance with the GPL, we are providing access to the source code for the version of GRUB used to build this ISO.

The exact source package corresponding to the GRUB package installed and used at the time of creating this ISO has been included in this repository. You can find the GRUB source tarball in the root directory of this repository: grub-2.13.tar.gz.


