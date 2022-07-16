
T <tohartohar3@gmail.com>
8:12 PM (36 minutes ago)
to me

#define _CRT_SECURE_NO_DEPRECATE
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LINE_LENGTH 80
#define OPCODE (const char*[16]){"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","get","prn","jsr","rts","hlt"}

typedef struct Macro {
char macro_name[10];
struct Macro* next;
char content[400];
} Macro;

FILE* create_spread_macro_file(char*, int);
FILE* spread_macro(FILE*, int); // Returns a new file pointer where macroes embedded into the text

Macro* create_macro(char*); // Creates a new macro struct whitch contains name bytes and next pointer (to Null)
Macro* add_macro(Macro*, Macro*); // Add the given macro to the start as the head of the list and return it

Macro* get_macro(char*, Macro*); // Returns the macro as a string if exist (and exit if not found)

void error_handeling(char*); // Prints the given error and exit the program
void printList(Macro*); // Prints the list for testing purposes
void free_list(Macro*);

int is_opcode(char*); // Return true (1) if there is opcode with that name
