#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <../include/lab3.h>
#include <../include/add.h>
#define YES 1
#define NO  0
#define MAX 100
#define MAX_WORD_LENGTH 100
#define MAX_INPUT_LENGTH 1000
#define MAX_WORD_LENGTH 100
#define MAX_INPUT_SIZE 1000

// === ВСЕ ФУНКЦИИ ВНЕ MAIN (УНИКАЛЬНЫЕ ИМЕНА) ===

// Функция для проверки, является ли слово палиндромом
int verify_palindrome(const char *word_sequence) {
    int length = strlen(word_sequence);
    for (int position = 0; position < length / 2; position++) {
        if (word_sequence[position] != word_sequence[length - 1 - position]) {
            return 0; // Не палиндром
        }
    }
    return 1; // Палиндром
}
// Функция для приведения строки к нижнему регистру
void convert_to_lowercase(char *text_string) {
    for (int index = 0; text_string[index]; index++) {
        text_string[index] = tolower(text_string[index]);
    }
}
// Функция для получения длины строки (обёртка над strlen)
int get_string_length(const char *text_string) {
    return strlen(text_string);
}
// Функция для копирования слова в буфер
void copy_word_to_buffer(const char *source_word, char *destination_buffer) {
    strcpy(destination_buffer, source_word);
}
// Функция для обновления самого длинного палиндрома
void update_max_palindrome(const char *current_word, char *longest_word,
                           int *current_max_length, int word_length) {
    if (word_length > *current_max_length) {
        *current_max_length = word_length;
        copy_word_to_buffer(current_word, longest_word);
    }
}
// Функция для разбиения строки на слова (возвращает первый токен)
char *get_first_token(char *input_string, const char *delimiters) {
    return strtok(input_string, delimiters);
}
// Функция для получения следующего токена
char *get_next_token(const char *delimiters) {
    return strtok(NULL, delimiters);
}
// Функция для обработки одного слова (приведение к нижнему регистру и проверка)
void process_single_word(char *word_token, char *longest_palindrome, int *max_length) {
    // Приводим слово к нижнему регистру
    convert_to_lowercase(word_token);
    // Проверяем, является ли слово палиндромом
    if (verify_palindrome(word_token)) {
        int current_length = get_string_length(word_token);
        update_max_palindrome(word_token, longest_palindrome, max_length, current_length);
    }
}
// Функция для поиска самого длинного палиндрома в строке
void find_longest_palindrome_word(const char *input_text, char *result_palindrome, int *result_length) {
    char working_copy[MAX_INPUT_SIZE];
    char delimiters[] = " ,.!?;:\n";
    // Копируем входную строку (strtok изменяет оригинал)
    strcpy(working_copy, input_text);
    // Получаем первый токен
    char *current_token = get_first_token(working_copy, delimiters);
    // Обрабатываем все слова
    while (current_token != NULL) {
        process_single_word(current_token, result_palindrome, result_length);
        current_token = get_next_token(delimiters);
    }
}
// Функция для чтения строки из стандартного ввода
void read_text_input(char *buffer, int buffer_size) {
    printf("Enter string:\n");
    fgets(buffer, buffer_size, stdin);
}
// Функция для вывода результата
void display_palindrome_result(const char *longest_palindrome, int max_length) {
    if (max_length > 0) {
        printf("The longest palindrome: %s\n", longest_palindrome);
    } else {
        printf("No palindromes\n");
    }
}
// Функция для инициализации буфера результата
void initialize_result_buffer(char *buffer, const char *default_value) {
    strcpy(buffer, default_value);
}
// Функция для сброса счётчика длины
void reset_length_counter(int *length_counter) {
    *length_counter = 0;
}
void lab3() {
    char user_input[MAX_INPUT_SIZE];
    char found_palindrome[MAX_WORD_LENGTH];
    int longest_length;
    // Инициализация
    initialize_result_buffer(found_palindrome, "");
    reset_length_counter(&longest_length);
    // Ввод и обработка
    read_text_input(user_input, sizeof(user_input));
    find_longest_palindrome_word(user_input, found_palindrome, &longest_length);
    // Вывод результата
    display_palindrome_result(found_palindrome, longest_length);
    return 0;
}
// === ВСЕ ФУНКЦИИ ВНЕ MAIN ===
// Функция приведения символа к нижнему регистру
char to_lower(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch - 'A' + 'a';
    }
    return ch;
}
// Функция проверки, является ли слово палиндромом
int check_if_palindrome(char word[], int len) {
    for (int i = 0; i < len / 2; i++) {
        char left = to_lower(word[i]);
        char right = to_lower(word[len - 1 - i]);
        if (left != right) {
            return NO;
        }
    }
    return YES;
}
// Функция копирования слова
void copy_word(char source[], char destination[], int len) {
    for (int i = 0; i <= len; i++) {
        destination[i] = source[i];
    }
}
// Функция обновления самого длинного палиндрома
void update_longest(char word[], int len, char longest[], int *longest_len) {
    if (len > *longest_len) {
        *longest_len = len;
        copy_word(word, longest, len);
    }
}
// Функция обновления самого короткого палиндрома
void update_shortest(char word[], int len, char shortest[], int *shortest_len) {
    if (len < *shortest_len) {
        *shortest_len = len;
        copy_word(word, shortest, len);
    }
}
// Функция проверки, является ли символ разделителем
int is_delimiter(char c) {
    return (c == ' ' || c == '.' || c == '!' || c == ',' ||
            c == '?' || c == ';' || c == ':' || c == '\n');
}
// Функция добавления символа в слово
void add_char_to_word(char word[], int *len, char c) {
    if (*len < MAX - 1) {
        word[*len] = c;
        (*len)++;
    }
}
// Функция завершения слова и его обработки
void process_word(char word[], int *word_len, int *flag,
                  char longest[], int *longest_len,
                  char shortest[], int *shortest_len) {
    if (*flag == YES) {
        word[*word_len] = '\0';
        if (check_if_palindrome(word, *word_len) == YES) {
            update_longest(word, *word_len, longest, longest_len);
            update_shortest(word, *word_len, shortest, shortest_len);
        }

        *word_len = 0;
    }
    *flag = NO;
}
// Функция вывода слова
void print_word(char word[], int len) {
    for (int i = 0; i < len; i++) {
        putchar(word[i]);
    }
}
// Функция вывода результатов
void print_results(char longest[], int longest_len,
                   char shortest[], int shortest_len) {
    if (longest_len > 0) {
        printf("The longest palindrome: ");
        print_word(longest, longest_len);
        putchar('\n');
    } else {
        printf("No palindromes\n");
        return;
    }
    if (shortest_len < MAX && shortest_len > 0) {
        printf("The shortest palindrome: ");
        print_word(shortest, shortest_len);
        putchar('\n');
    } else if (shortest_len == MAX && longest_len > 0) {
        printf("The shortest palindrome: ");
        print_word(longest, longest_len);
        putchar('\n');
    }
}
void lab3_add(void) {
    int c;
    int flag = NO;
    char current_word[MAX];
    int word_len = 0;
    char longest_pal[MAX];
    int longest_len = 0;
    char shortest_pal[MAX];
    int shortest_len = MAX;
    printf("Enter string:\n");
    while ((c = getchar()) != EOF) {
        if (is_delimiter(c)) {
            process_word(current_word, &word_len, &flag,
                        longest_pal, &longest_len,
                        shortest_pal, &shortest_len);
        } else {
            add_char_to_word(current_word, &word_len, c);
            flag = YES;
        }
    }
    // Обрабатываем последнее слово, если оно есть
    if (flag == YES) {
        process_word(current_word, &word_len, &flag,
                    longest_pal, &longest_len,
                    shortest_pal, &shortest_len);
    }
    print_results(longest_pal, longest_len, shortest_pal, shortest_len);
    return 0;
}
