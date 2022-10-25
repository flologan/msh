#pragma once

int get_input(char input_str[], int max_size);
int tokenize(char *s, char ***argv);
int execute(int argc, char **argv);
int free_vec(int argc, char **argv);
