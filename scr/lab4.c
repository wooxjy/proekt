#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <../include/lab4.h>
#include <../include/add.h>
#define YES  1
#define NO   0
#define MAXLINE 1000
#define MAX_WORDS 1000
// === ВСЕ ФУНКЦИИ ===

static void set_console_cp(void) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}
static void remove_newline(char str[]) {
    int len = 0;
    while (str[len] != '\0' && str[len] != '\n') {
        len++;
    }
    if (str[len] == '\n') {
        str[len] = '\0';
    }
}
static int is_delimiter(char c) {
    return (c == ' ' || c == '.' || c == ',' || c == '\n');
}
static void add_char_to_word(char word[], int *pos, char c) {
    word[*pos] = c;
    (*pos)++;
}
static void finish_word(char words[][MAXLINE], int *count, char current_word[], int *word_pos) {
    current_word[*word_pos] = '\0';
    int p = 0;
    while (current_word[p] != '\0') {
        words[*count][p] = current_word[p];
        p++;
    }
    words[*count][p] = '\0';
    (*count)++;
    *word_pos = 0;
}
static int split_into_words(char buffer[], char words[][MAXLINE]) {
    int count = 0;
    int i = 0;
    int inword = NO;
    int word_pos = 0;
    char current_word[MAXLINE];
    while (buffer[i] != '\0') {
        if (!is_delimiter(buffer[i])) {
            if (inword == NO) {
                inword = YES;
                word_pos = 0;
            }
            add_char_to_word(current_word, &word_pos, buffer[i]);
        } else {
            if (inword == YES) {
                finish_word(words, &count, current_word, &word_pos);
                inword = NO;
            }
        }
        i++;
    }
    if (inword == YES) {
        finish_word(words, &count, current_word, &word_pos);
    }
    return count;
}
static void write_word_to_buffer(char buffer[], int *pos, char word[]) {
    int p = 0;
    while (word[p] != '\0') {
        buffer[*pos] = word[p];
        (*pos)++;
        p++;
    }
}
static void reverse_words_order(char buffer[], char words[][MAXLINE], int word_count) {
    int pos = 0;
    for (int k = word_count - 1; k >= 0; k--) {
        write_word_to_buffer(buffer, &pos, words[k]);
        if (k != 0) {
            buffer[pos] = ' ';
            pos++;
        }
    }
    buffer[pos] = '\0';
}
static void read_line(char buffer[], int max_size) {
    fgets(buffer, max_size, stdin);
}
static void process_line(char buffer[]) {
    char words[MAX_WORDS][MAXLINE];
    int word_count;
    word_count = split_into_words(buffer, words);
    reverse_words_order(buffer, words, word_count);
}
void lab4(void) {
    char a[MAXLINE];
    set_console_cp();  // Устанавливаем кодировку консоли
    printf("Enter string:\n");
    read_line(a, MAXLINE);
    remove_newline(a);
    process_line(a);
    puts(a);
    return 0;
}
// === ВСЕ ФУНКЦИИ ВНЕ MAIN (УНИКАЛЬНЫЕ ИМЕНА) ===

// Функция замены символа конца строки
void replace_newline_with_null(char buffer[], int max_len) {
    for (int i = 0; i < max_len && buffer[i] != '\0'; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            break;
        }
    }
}
// Функция безопасного чтения строки из stdin
void safe_read_line(char destination[], int max_len) {
    fgets(destination, max_len, stdin);
}
// Функция записи строки в файл
void write_string_to_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fwrite(content, 1, strlen(content), file);
        fclose(file);
    }
}
// Функция обмена двух символов местами
void swap_characters(char *first, char *second) {
    char temp = *first;
    *first = *second;
    *second = temp;
}
// Функция разворота последовательности символов
void reverse_character_sequence(char *start_ptr, char *end_ptr) {
    while (start_ptr < end_ptr) {
        swap_characters(start_ptr, end_ptr);
        start_ptr++;
        end_ptr--;
    }
}
// Функция разворота всей строки
void reverse_whole_string(char *str_ptr) {
    int length = strlen(str_ptr);
    if (length > 0) {
        reverse_character_sequence(str_ptr, str_ptr + length - 1);
    }
}
// Функция поиска начала следующего слова
char *find_next_word_start(char *current_pos) {
    while (*current_pos != '\0' && *current_pos == ' ') {
        current_pos++;
    }
    return current_pos;
}
// Функция разворота слов в строке (основная логика)
void reverse_words_in_string(char *input_str) {
    // Сначала переворачиваем всю строку
    reverse_whole_string(input_str);
    // Затем переворачиваем каждое слово обратно
    char *word_begin = input_str;
    char *current_pos = input_str;
    while (*current_pos != '\0') {
        if (*current_pos == ' ') {
            if (word_begin < current_pos) {
                reverse_character_sequence(word_begin, current_pos - 1);
            }
            word_begin = current_pos + 1;
        }
        current_pos++;
    }
    // Переворачиваем последнее слово
    if (word_begin < current_pos) {
        reverse_character_sequence(word_begin, current_pos - 1);
    }
}
// Функция вывода строки на экран
void display_string(const char *str_ptr) {
    printf("%s\n", str_ptr);
}
void lab4_add(void) {
    char text_buffer[MAXLINE];
    printf("");
    safe_read_line(text_buffer, MAXLINE);
    replace_newline_with_null(text_buffer, MAXLINE);
    reverse_words_in_string(text_buffer);
    display_string(text_buffer);
    write_string_to_file("output.txt", text_buffer);
    return 0;
}
