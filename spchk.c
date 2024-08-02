#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

//Max amount of words 
#define MAX_WORDS 10000

char dictionary[MAX_WORDS][100];
int num_words = 0;

//All of the methods
void load_dictionary(char *filename);
int is_valid_word(char *word);
void process_file(char *filename);
void traverse_directory(char *dirpath);
void capitalize_word(char *word);

//Main Method
int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <dictionary_file> <text_files/directories>...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    load_dictionary(argv[1]);

    for (int i = 2; i < argc; i++) {
        traverse_directory(argv[i]);
    }
}

//Loads all the words from the dict file into the dictionary
void load_dictionary(char *filename) {

        int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening dictionary file");
        exit(EXIT_FAILURE);
    }

    char word[100];
    int word_index = 0;
    char ch;
    while (read(fd, &ch, 1) > 0) {
        if (ch == '\n') {
            word[word_index] = '\0';
            if (num_words < MAX_WORDS) {
                int upper =0;
                strcpy(dictionary[num_words], word);
                num_words++;
                //Handles case where the dictionary has a capital letter ex. MacDonald
               for (int i = 0; word[i]; i++) {
                    if(isupper(word[i])!=0){
                        upper = 1;
                        break;
                    }
                } 
                if(upper==0){
                //  lowercase
                for (int i = 0; word[i]; i++) {
                    word[i] = tolower(word[i]);
                }
                strcpy(dictionary[num_words], word);
                num_words++;
                // first letter capitalized
                word[0] = toupper(word[0]);
                for (int i = 1; word[i]; i++) {
                    word[i] = tolower(word[i]);
                }
                strcpy(dictionary[num_words], word);
                num_words++;
                // uppercase
                for (int i = 0; word[i]; i++) {
                    word[i] = toupper(word[i]);
                }
                strcpy(dictionary[num_words], word);
                num_words++;
                } 
            } else {
                fprintf(stderr, "dictionary full: %s\n", word);
            }
            word_index = 0;
        } else {
            word[word_index] = ch;
            word_index++;
        }
    }

    close(fd);
}

//Checks if the word exists in the dictionary
int is_valid_word(char *word) {
    char *hyphen = strchr(word, '-');
    if (hyphen != NULL) {
        // Handle hyphenated words
        *hyphen = '\0';
        int is_valid = is_valid_word(word) && is_valid_word(hyphen + 1);
        *hyphen = '-';
        return is_valid;
    }

    for (int i = 0; i < num_words; i++) {
        if (strcmp(dictionary[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

//Processes the file
void process_file(char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening text file");
        return;
    }

    printf("file: %s\n", filename);
    int line_num = 1, col_num = 1;
    char word_buffer[100];
    int word_index = 0;
    char c;

    while (read(fd, &c, 1) > 0) {
        if (isalpha(c) || c == '-' || c == '\'') {
            word_buffer[word_index++] = c;
            col_num++;
        } else if (word_index > 0) {
            word_buffer[word_index] = '\0';

            // Handle trailing punctuation
            int word_len = strlen(word_buffer);
            while (word_len > 0 && !isalpha(word_buffer[word_len - 1])) {
                word_buffer[--word_len] = '\0';
            }

            if (!is_valid_word(word_buffer)) {
                fprintf(stderr, "%s (%d,%d): %s\n", filename, line_num, col_num - word_index, word_buffer);
            }

            word_index = 0;
        }

        if (c == '\n') {
            line_num++;
            col_num = 1;
        }
    }

    close(fd);
}


//Traverses the directory for text files
void traverse_directory(char *dirpath) {
    DIR *dir = opendir(dirpath);
    if (!dir) {
        perror("Error opening directory");
        return;
    }

    printf("Traversing directory: %s\n", dirpath);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dirpath, entry->d_name);

        struct stat statbuf;
        if (stat(path, &statbuf) == 0) {
            if (S_ISREG(statbuf.st_mode) && ends_with(".txt", entry->d_name)) {
                process_file(path);
            } else if (S_ISDIR(statbuf.st_mode) && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                traverse_directory(path);
            }
        } else {
            perror("Error getting file status");
        }
    }

    closedir(dir);
}

int ends_with(const char *suffix, const char *str) {
    int str_len = strlen(str);
    int suffix_len = strlen(suffix);
    if (str_len < suffix_len) return 0;
    return strcmp(str + str_len - suffix_len, suffix) == 0;
}

