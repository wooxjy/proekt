#include <stdio.h>
#include <locale.h>
#include <../include/lab6.h>
#include <../include/add.h>
#define K 3
#define N 4
// === ВСЕ ФУНКЦИИ ВНЕ MAIN (УНИКАЛЬНЫЕ ИМЕНА) ===

// Функция установки русской локали
void configure_russian_locale(void) {
    setlocale(LC_ALL, "Russian");
}
// Функция ввода двумерного массива
void enter_matrix_elements(int rows, int cols, int matrix[rows][cols]) {
    printf("Введите элементы массива %d x %d:\n", rows, cols);
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            scanf("%d", &matrix[row][col]);
        }
    }
}
// Функция вычисления среднего арифметического одной строки
float compute_row_average(int cols, int row_data[cols]) {
    int total_sum = 0;
    for (int col = 0; col < cols; col++) {
        total_sum += row_data[col];
    }
    return (float)total_sum / cols;
}
// Функция вычисления средних арифметических для всех строк
void calculate_all_row_averages(int rows, int cols, int matrix[rows][cols], float averages[rows]) {
    for (int row = 0; row < rows; row++) {
        averages[row] = compute_row_average(cols, matrix[row]);
    }
}
// Функция обмена двух строк матрицы
void swap_matrix_rows(int cols, int row1_data[cols], int row2_data[cols]) {
    for (int col = 0; col < cols; col++) {
        int temporary = row1_data[col];
        row1_data[col] = row2_data[col];
        row2_data[col] = temporary;
    }
}
// Функция обмена двух значений (для средних арифметических)
void swap_float_values(float *first, float *second) {
    float temporary = *first;
    *first = *second;
    *second = temporary;
}
// Функция проверки необходимости обмена строк
int should_swap_rows(float left_average, float right_average) {
    return left_average < right_average; // по убыванию
}
// Функция выполнения одного обмена (если нужно)
void perform_row_swap_if_needed(float averages[], int left_idx, int right_idx,
                                  int cols, int matrix[][cols]) {
    if (should_swap_rows(averages[left_idx], averages[right_idx])) {
        swap_float_values(&averages[left_idx], &averages[right_idx]);
        swap_matrix_rows(cols, matrix[left_idx], matrix[right_idx]);
    }
}
// Функция одного прохода пузырьковой сортировки
void bubble_sort_pass(int rows, int cols, float averages[], int matrix[][cols], int pass_num) {
    int comparisons_count = rows - 1 - pass_num;
    for (int idx = 0; idx < comparisons_count; idx++) {
        perform_row_swap_if_needed(averages, idx, idx + 1, cols, matrix);
    }
}
// Функция сортировки строк по убыванию средних арифметических
void sort_rows_by_average_descending(int rows, int cols, float averages[], int matrix[][cols]) {
    for (int pass = 0; pass < rows - 1; pass++) {
        bubble_sort_pass(rows, cols, averages, matrix, pass);
    }
}
// Функция вывода двумерного массива
void display_matrix(int rows, int cols, int matrix[rows][cols]) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            printf("%4d ", matrix[row][col]);
        }
        printf("\n");
    }
}
// Функция выполнения полной обработки матрицы
void process_matrix_completely(int rows, int cols, int matrix[rows][cols]) {
    float row_averages[rows];
    calculate_all_row_averages(rows, cols, matrix, row_averages);
    sort_rows_by_average_descending(rows, cols, row_averages, matrix);
}
void lab6(void) {
    int data_matrix[K][N];
    configure_russian_locale();
    enter_matrix_elements(K, N, data_matrix);
    process_matrix_completely(K, N, data_matrix);
    display_matrix(K, N, data_matrix);
    return 0;
}
