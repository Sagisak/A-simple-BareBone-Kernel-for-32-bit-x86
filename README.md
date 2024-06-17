# A-simple-BareBone-Kernel-for-32-bit-x86
This is a respitory to make a simple kernel from the tutorial OS dev wiki. All of the creation will revolve and followed from that paticular website. Information is also get from searching the web or simply asking an AI chatbot, like CHATGPT, as an assitance. Below is the link from the documentation I read from:

https://wiki.osdev.org/Bare_Bones

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




