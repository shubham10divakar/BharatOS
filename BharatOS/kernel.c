#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Function to output a character to the screen
static void putc(char c) {
    // Assuming a very simple VGA text mode screen at 0xB8000
    static uint16_t *video_memory = (uint16_t *)0xB8000;
    static size_t cursor = 0;
    video_memory[cursor++] = (uint16_t)c | (0x07 << 8); // character with light grey color
}

// Function to output a string to the screen
static void puts(const char *str) {
    while (*str) {
        putc(*str++);
    }
}

// Function to read input from keyboard (stub)
static char getc() {
    // This is a stub for reading keyboard input
    // You need to implement keyboard input handling
    return ' ';
}

// Function to compare strings
static int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

// Function to clear the screen
static void clear_screen() {
    uint16_t *video_memory = (uint16_t *)0xB8000;
    for (size_t i = 0; i < 80 * 25; i++) {
        video_memory[i] = (uint16_t)' ' | (0x07 << 8);
    }
}

// Function to read a line of input (simple implementation)
static void readline(char *buffer, size_t max) {
    size_t i = 0;
    while (i < max - 1) {
        char c = getc();
        if (c == '\n' || c == '\r') {
            putc('\n');
            break;
        }
        putc(c);
        buffer[i++] = c;
    }
    buffer[i] = '\0';
}

// Shell main function
void shell() {
    char buffer[128];

    while (true) {
        puts("myshell> ");
        readline(buffer, sizeof(buffer));

        if (strcmp(buffer, "clear") == 0) {
            clear_screen();
        } else if (strcmp(buffer, "hello") == 0) {
            puts("Hello, world!\n");
        } else if (strcmp(buffer, "exit") == 0) {
            puts("Exiting shell...\n");
            break;
        } else {
            puts("Unknown command\n");
        }
    }
}

// Kernel main function
void kernel_main() {
    clear_screen();
    puts("Welcome to My Simple Shell!\n");
    shell();
    while (1) {
        __asm__("hlt");
    }
}
