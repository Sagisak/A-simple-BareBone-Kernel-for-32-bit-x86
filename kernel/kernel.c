#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

/* Hardware text mode color constants. */
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
    return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str) 
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void);

void terminal_setcolor(uint8_t color);

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);

void terminal_scroll(void); // Forward declaration

void terminal_putchar(char c) 
{
    if (c != '\n') {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT) {
                terminal_row--;
                terminal_scroll(); // Perform scrolling
            }
        }
    } else {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) {
            terminal_row--;
            terminal_scroll(); // Perform scrolling
        }
    }
}

void terminal_scroll() {
    // Move each row up by one row
    for (size_t y = 1; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            size_t src_index = y * VGA_WIDTH + x;
            size_t dest_index = (y - 1) * VGA_WIDTH + x;
            terminal_buffer[dest_index] = terminal_buffer[src_index];
        }
    }
    
    // Clear the last row
    size_t last_row_index = (VGA_HEIGHT - 1) * VGA_WIDTH;
    for (size_t x = 0; x < VGA_WIDTH; x++) {
        terminal_buffer[last_row_index + x] = vga_entry(' ', terminal_color);
    }
}

void terminal_initialize(void) 
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*) 0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_setcolor(uint8_t color) 
{
    terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_write(const char* data, size_t size) 
{
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
    terminal_write(data, strlen(data));
}

void kernel_main(void) 
{
    /* Initialize terminal interface */
    terminal_initialize();

    /* Example of scrolling output */
    terminal_writestring("Welcome to the Kernel!\n");
    terminal_writestring("This is a demonstration of terminal scrolling in a VGA text mode.\n");
    terminal_writestring("The screen will scroll automatically when it fills up.\n");
    terminal_writestring("This is line 4.\n");
    terminal_writestring("This is line 5.\n");
    terminal_writestring("This is line 6.\n");
    terminal_writestring("This is line 7.\n");
    terminal_writestring("This is line 8.\n");
    terminal_writestring("This is line 9.\n");
    terminal_writestring("This is line 10.\n");
    terminal_writestring("This is line 11.\n");
    terminal_writestring("This is line 12.\n");
    terminal_writestring("This is line 13.\n");
    terminal_writestring("This is line 14.\n");
    terminal_writestring("This is line 15.\n");
    terminal_writestring("This is line 16.\n");
    terminal_writestring("This is line 17.\n");
    terminal_writestring("This is line 18.\n");
    terminal_writestring("This is line 19.\n");
    terminal_writestring("This is line 20.\n");
    terminal_writestring("This is line 21.\n");
    terminal_writestring("This is line 22.\n");
    terminal_writestring("This is line 23.\n");
    terminal_writestring("This is line 24.\n");
    terminal_writestring("This is line 25.\n");
    terminal_writestring("This is line 26.\n");
    terminal_writestring("This is line 27.\n");
    terminal_writestring("This is line 28.\n");
    terminal_writestring("This is line 29.\n");
    terminal_writestring("This is line 30.\n");
    terminal_writestring("This is line 31.\n");
    terminal_writestring("This is line 32.\n");
    terminal_writestring("This is line 33.\n");
    terminal_writestring("This is line 34.\n");
    terminal_writestring("This is line 35.\n");
    terminal_writestring("This is line 36.\n");
    terminal_writestring("This is line 37.\n");
    terminal_writestring("This is line 38.\n");
    terminal_writestring("This is line 39.\n");
    terminal_writestring("This is line 40.\n");
    terminal_writestring("This is line 41.\n");
    terminal_writestring("This is line 42.\n");
    terminal_writestring("This is line 43.\n");
    terminal_writestring("This is line 44.\n");
    terminal_writestring("This is line 45.\n");
    terminal_writestring("This is line 46.\n");
    terminal_writestring("This is line 47.\n");
    terminal_writestring("This is line 48.\n");
    terminal_writestring("This is line 49.\n");
    terminal_writestring("This is line 50.\n");
    terminal_writestring("This is line 51.\n");
    terminal_writestring("This is line 52.\n");
    terminal_writestring("This is line 53.\n");
    terminal_writestring("This is line 54.\n");
    terminal_writestring("This is line 55.\n");
    terminal_writestring("This is line 56.\n");
    terminal_writestring("This is line 57.\n");
    terminal_writestring("This is line 58.\n");
    terminal_writestring("This is line 59.\n");
    terminal_writestring("This is line 60.\n");
    terminal_writestring("Welcome to the Kernel!\n");
    terminal_writestring("This is a demonstration of terminal scrolling in a VGA text mode.\n");
    terminal_writestring("The screen will scroll automatically when it fills up. That is why the line start at 42.\n");
    terminal_writestring("You can check the kernel.c for further understanding.\n");
}

