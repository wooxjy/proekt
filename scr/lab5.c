#include <stdio.h>
#include <locale.h>
#include <../include/lab5.h>
#include <../include/add.h>
#define N 10
// === ВСЕ ФУНКЦИИ ВНЕ MAIN (УНИКАЛЬНЫЕ ИМЕНА) ===

// Функция установки русской локали
void enable_russian_locale(void) {
    setlocale(LC_ALL, "Russian");
}
// Функция ввода одного целого числа
void input_integer(int *destination) {
    scanf("%d", destination);
}
// Функция ввода массива целых чисел
void fill_integer_array(int arr[], int size) {
    for (int idx = 0; idx < size; idx++) {
        scanf("%d", &arr[idx]);
    }
}
// Функция вычисления суммы подмассива (с заданного индекса, заданной длины)
int compute_subarray_sum(int arr[], int start_idx, int length) {
    int total = 0;
    for (int offset = 0; offset < length; offset++) {
        total += arr[start_idx + offset];
    }
    return total;
}
// Функция поиска индекса начала подмассива с минимальной суммой
int find_start_of_min_sum_subarray(int arr[], int subarray_len, int array_size) {
    // Вычисляем сумму первого подмассива
    int min_sum = compute_subarray_sum(arr, 0, subarray_len);
    int best_start_index = 0;
    // Перебираем все возможные начальные позиции
    for (int start = 1; start <= array_size - subarray_len; start++) {
        int current_sum = compute_subarray_sum(arr, start, subarray_len);
        if (current_sum < min_sum) {
            min_sum = current_sum;
            best_start_index = start;
        }
    }
    return best_start_index;
}
// Функция обнуления подмассива
void zero_out_subarray(int arr[], int start_idx, int length) {
    for (int offset = 0; offset < length; offset++) {
        arr[start_idx + offset] = 0;
    }
}
// Функция вывода массива на экран
void display_integer_array(int arr[], int size) {
    for (int idx = 0; idx < size; idx++) {
        printf("%d ", arr[idx]);
    }
    printf("\n");
}
// Функция запроса и получения длины подмассива от пользователя
int get_subarray_length_from_user(void) {
    int length;
    printf("введите кол-во соседних элементов для обнуления: ");
    scanf("%d", &length);
    return length;
}
// Основная функция обработки: найти подмассив с минимальной суммой и обнулить его
void find_and_zero_min_sum_subarray(int arr[], int array_size, int subarray_len) {
    int best_start = find_start_of_min_sum_subarray(arr, subarray_len, array_size);
    zero_out_subarray(arr, best_start, subarray_len);
}
void lab5(void) {
    int numbers[N];
    enable_russian_locale();
    // Ввод массива
    fill_integer_array(numbers, N);
    // Ввод длины подмассива
    int segment_length = get_subarray_length_from_user();
    // Обработка: поиск минимальной суммы и обнуление
    find_and_zero_min_sum_subarray(numbers, N, segment_length);
    // Вывод результата
    display_integer_array(numbers, N);
    return 0;
}
// === ВСЕ ФУНКЦИИ ВНЕ MAIN (УНИКАЛЬНЫЕ ИМЕНА) ===

// Функция установки русской локали
void setup_russian_locale(void) {
    setlocale(LC_ALL, "Russian");
}
// Функция ввода массива
void input_array_elements(int arr[], int size) {
    printf("Введите %d элементов массива:\n", size);
    for (int idx = 0; idx < size; idx++) {
        scanf("%d", &arr[idx]);
    }
}
// Функция проверки существования левого соседа
int has_left_neighbor(int index) {
    return index - 1 >= 0;
}
// Функция проверки существования правого соседа
int has_right_neighbor(int index, int array_size) {
    return index + 1 < array_size;
}
// Функция забора левого соседа
int absorb_left_neighbor(int arr[], int index) {
    int absorbed_value = arr[index - 1];
    arr[index - 1] = 0;
    return absorbed_value;
}
// Функция забора правого соседа
int absorb_right_neighbor(int arr[], int index) {
    int absorbed_value = arr[index + 1];
    arr[index + 1] = 0;
    return absorbed_value;
}
// Функция обработки чётного элемента (забор соседей и суммирование)
void process_even_index_element(int arr[], int index, int array_size) {
    int total_sum = arr[index];
    if (has_left_neighbor(index)) {
        total_sum += absorb_left_neighbor(arr, index);
    }
    if (has_right_neighbor(index, array_size)) {
        total_sum += absorb_right_neighbor(arr, index);
    }

    arr[index] = total_sum;
}
// Функция обработки всех чётных элементов массива
void process_all_even_elements(int arr[], int array_size) {
    for (int idx = 0; idx < array_size; idx += 2) {
        process_even_index_element(arr, idx, array_size);
    }
}
// Функция запроса длины подмассива у пользователя
int request_subarray_length(void) {
    int length;
    printf("Введите кол-во соседних элементов для проверки суммы: ");
    scanf("%d", &length);
    return length;
}
// Функция вычисления суммы подмассива
int calculate_subarray_total(int arr[], int start_idx, int length) {
    int total = 0;
    for (int offset = 0; offset < length; offset++) {
        total += arr[start_idx + offset];
    }
    return total;
}
// Функция поиска индекса начала подмассива с минимальной суммой
int locate_min_sum_subarray_start(int arr[], int subarray_len, int array_size) {
    if (subarray_len <= 0 || subarray_len > array_size) {
        return -1;
    }
    int min_total = calculate_subarray_total(arr, 0, subarray_len);
    int best_start = 0;
    for (int start = 1; start <= array_size - subarray_len; start++) {
        int current_total = calculate_subarray_total(arr, start, subarray_len);
        if (current_total < min_total) {
            min_total = current_total;
            best_start = start;
        }
    }
    return best_start;
}
// Функция отметки исключённых индексов
void mark_excluded_indices(int excluded[], int start_idx, int length, int array_size) {
    for (int idx = start_idx; idx < start_idx + length && idx < array_size; idx++) {
        if (idx >= 0) {
            excluded[idx] = 1;
        }
    }
}
// Функция вывода информации об исключённых индексах
void print_excluded_indices_info(int start_idx, int length, int array_size) {
    printf("\nИндексы, исключенные из сортировки");
    if (start_idx >= 0) {
        int end_idx = start_idx + length - 1;
        if (end_idx >= array_size) end_idx = array_size - 1;
        printf(" (с %d по %d):\n", start_idx, end_idx);
    } else {
        printf(" (нет исключенных):\n");
    }
}
// Функция вывода исключённых элементов
void display_excluded_elements(int arr[], int start_idx, int length, int array_size) {
    for (int idx = start_idx; idx < start_idx + length && idx < array_size; idx++) {
        if (idx >= 0) {
            printf("x[%d]=%d ", idx, arr[idx]);
        }
    }
    printf("\n");
}
// Функция проверки, можно ли вставить элемент
int can_insert(int excluded[], int position) {
    return position >= 0 && !excluded[position];
}
// Функция поиска предыдущей позиции для вставки
int find_previous_valid_position(int excluded[], int current_pos) {
    int pos = current_pos - 1;
    while (pos >= 0 && excluded[pos]) {
        pos--;
    }
    return pos;
}
// Функция сдвига элементов при сортировке
void shift_element_right(int arr[], int excluded[], int from_pos, int to_pos) {
    for (int k = from_pos; k > to_pos; k--) {
        if (!excluded[k - 1]) {
            arr[k] = arr[k - 1];
        }
    }
}
// Функция выполнения одного прохода сортировки вставками
void perform_insertion_sort_pass(int arr[], int excluded[], int current_idx) {
    if (excluded[current_idx]) return;
    int key_value = arr[current_idx];
    int previous_idx = current_idx - 1;
    // Находим позицию для вставки
    while (previous_idx >= 0 && !excluded[previous_idx] && arr[previous_idx] > key_value) {
        arr[previous_idx + 1] = arr[previous_idx];
        previous_idx--;
    }
    // Пропускаем исключённые элементы
    while (previous_idx >= 0 && excluded[previous_idx]) {
        previous_idx--;
    }
    arr[previous_idx + 1] = key_value;
}
// Функция сортировки вставками с пропуском исключённых элементов
void insertion_sort_with_skipping(int arr[], int excluded[], int array_size) {
    for (int idx = 1; idx < array_size; idx++) {
        perform_insertion_sort_pass(arr, excluded, idx);
    }
}
// Функция вывода итогового массива (исключённые в скобках)
void print_final_array_with_excluded(int arr[], int excluded[], int array_size) {
    printf("\nИтоговый массив:\n");
    for (int idx = 0; idx < array_size; idx++) {
        if (excluded[idx]) {
            printf("[%d] ", arr[idx]);
        } else {
            printf("%d ", arr[idx]);
        }
    }
    printf("\n");
}
// Функция выполнения всей обработки (забор соседей, поиск минимума, исключение)
void execute_full_processing(int arr[], int excluded[], int array_size) {
    // Шаг 1: чётные элементы забирают соседей
    process_all_even_elements(arr, array_size);
    // Шаг 2: запрос длины подмассива
    int segment_length = request_subarray_length();
    // Шаг 3: поиск подмассива с минимальной суммой
    int min_start = -1;
    if (segment_length > 0 && segment_length <= array_size) {
        min_start = locate_min_sum_subarray_start(arr, segment_length, array_size);
    }
    // Шаг 4: отметка исключённых индексов
    if (min_start >= 0) {
        mark_excluded_indices(excluded, min_start, segment_length, array_size);
        print_excluded_indices_info(min_start, segment_length, array_size);
        display_excluded_elements(arr, min_start, segment_length, array_size);
    } else {
        print_excluded_indices_info(-1, 0, array_size);
    }
    // Шаг 5: сортировка вставками
    insertion_sort_with_skipping(arr, excluded, array_size);
}
void lab5_add(void) {
    int numbers[N];
    int excluded_indices[N] = {0};
    setup_russian_locale();
    input_array_elements(numbers, N);
    execute_full_processing(numbers, excluded_indices, N);
    print_final_array_with_excluded(numbers, excluded_indices, N);
    return 0;
}
