#include "macro.h"

int main(int argc, char* argv[]) // argc = num of strings (file names), argv = the names array
{
  if (argc < 0) error_handeling("\nno file name\n");

  int i;
  for (i = 1; i < argc; i++) {
    FILE* spread_macro_file = create_spread_macro_file(argv[i], i);
  }

  return 0;
}

void printList (Macro* head) { // To test the list structs
  while (head != NULL)
  {
    printf("%s ", head->macro_name);
    head = head->next;
  }
}

FILE* create_spread_macro_file (char* file_name, int i) {
  FILE* file_ptr;
  file_ptr = fopen(file_name, "r");
  if (file_ptr == NULL) {
    error_handeling("\nfile cannot be opened\n");
  }
  return spread_macro(file_ptr, i);
}


FILE* spread_macro(FILE* file_ptr, int i)
{
  Macro* head = NULL;
  Macro* macro_node = NULL;
  Macro* founded_macro;
  FILE* new_fp;
  int macro = 0;
  int bytes;
  char file_name[100];
  char* macro_name;
  char* first_word;
  char* str_to_put = (char*)malloc(sizeof(char) * LINE_LENGTH);
  char original_line[LINE_LENGTH];
  char copied_line[LINE_LENGTH];
  sprintf(file_name, "./new_file_%d.txt", i);
  new_fp = fopen(file_name, "wt");

  while (fgets(original_line, LINE_LENGTH, file_ptr) != NULL) {

  strcpy(copied_line, original_line);

  if (macro) {
    if (strcmp(original_line, "endmacro\n") == 0) {
      macro = 0;
      continue;
      } else {
        strcat(head->content, original_line);
        continue;
      }
    } else {
      first_word = strtok(copied_line, " \n");

      if (strcmp(first_word, "macro") == 0) {
        macro_name = strtok(NULL, " \n");
        macro_node = create_macro(macro_name);
        head = add_macro(head, macro_node);
        macro = 1;
      } else {

      if (copied_line[strlen(first_word) - 1] == ':' || is_opcode(first_word)) {
        str_to_put = original_line;
      } else {
        founded_macro = get_macro(first_word, head);

        printf("%s\n", founded_macro->content);
        str_to_put = founded_macro->content;
      }
      fprintf(new_fp, "%s", str_to_put);
    }
  }
}

  printList(head); // tester
  free_list(head);
  fclose(new_fp);
  fclose(file_ptr);
  return new_fp;
}


int is_opcode(char* name) {
  int i;
  for (i = 0; i < 7; i++) {
    if (strcmp(name, OPCODE[i]) == 0)
      return 1;
  }
  return 0;
}

Macro* create_macro(char* name) {
  Macro* new_macro = (Macro*)malloc(sizeof(Macro));
  if (new_macro != NULL) {
    strcpy(new_macro->macro_name, name);
    new_macro->next = NULL;
  }
  else
    error_handeling("mamory allocation problem");

  return new_macro;
}

Macro* add_macro(Macro* head, Macro* macro_node) {

  macro_node->next = head;
  return macro_node;
}

void error_handeling(char* str) {
  printf("%s\n", str);
  exit(0);
}

Macro* get_macro(char* name, Macro* head) {

  Macro* temp_head = head;
  while (temp_head != NULL && (strcmp(name, temp_head->macro_name) != 0))
  {
    temp_head = temp_head->next;
  }

  if (!temp_head) {
    error_handeling("Syntax error: word not recognized");
  }

  return temp_head;
}

void free_list(Macro* head) {
  Macro* tmp;
  while (head != NULL)
  {
    tmp = head;
    head = head->next;
    free(tmp);
  }
}
