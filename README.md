# <a name="краткое_описание"></a>Onegin sort

> WARNING!!!
Данная программа НЕ КОПИРУЕТ великое произведение мировой литературы - "Евгений Онегин" Александа Сергеевича Пушкина, а лишь ссылается на него ^^

Этот репозиторий содержит написанную в учебных целях программу сортировки текстовых файлов(в частности роман А. С Пушкина - Евгений Онегин). Программа создает файл в который записывает три версии текста: отсортированную, отсортированную от конца к началу и оригинальный текст.

---

* [Краткое описание](#краткое_описание)
* [Запуск](#запуск)
    * [Установка](#запуск/установка)
    * [Компиляция](#запуск/компиляция)
    * [Запуск программы](#запуск/запуск_программы)
* [Описание устройства программы](#Описание_устройства_программы)
    * [main](#Описание_устройства_программы/main)
    * [debugging](#Описание_устройства_программы/debugging)
    * [string_sort](#Описание_устройства_программы/string_sort)
---

## <a name="запуск"></a>Запуск

#### 1. <a name="запуск/установка"></a>Установка

Вставьте в терминал команду:
```
git clone https://github.com/Tamik13/onegin_sort/tree/main
```

#### 2. <a name="запуск/компиляция"></a>Компиляция

В файле ```onegin_sort/tmp/compile``` записана команда для компиляции программы

#### 3. <a name="запуск/запуск_программы"></a>Запуск программы

Для сортировки Евгения Онегина введите команду
```
 ./onegin_srt
```
  (работает только на Линуксе/Маке). Результат работы программы находится в файле ``` onegin_sort/sorted_onegin.txt ```

Если вы хотите отсортировать другой txt файл то добавьте путь до входного и выходного файлов. Например:
```
./onegin_srt input_file.txt output_file.txt
```

При успешном выполнении программа выводит ```SUCCESS```

---

## <a name="Описание_устройства_программы"></a>Описание устройства программы

#### <a name="Описание_устройства_программы/main"></a>main

В этом файле находится основная логика программы

Вызов каждой функции обернут в if для обработки ошибок (подробнее об обработке ошибок в описании файла [debugging](#Описание_устройства_программы/debugging))

Сначала программа считывает аргументы командной строки для получения имен файлов или, при отсутствие аргументов, устанавливает стандартные имена.

```cpp
command_line_processing(argc, argv, &input_file_name, &output_file_name);
```

Далее программа считывает текст из указанного файла и подсчитывает количество символов '\n', т.к. оно равно количеству строк.
Для считывания используются низкоуровневые функции open, read и close т.к. они не буферизированы, что ускоряет работу при однократном считывании.
Файл считывается в специальную структуру ```string``` в которой хранится указатель на строку и ее размер.
Для изначальной инициализации буфера для файла размер берется из ```stat``` обернутого в: ```#define STAT_GET_SIZE```. Конечный размер текста берется из возвращаемого значения ```read```

```cpp
read_file(&buffer, input_file_name);
count_slash_n(&buffer, &count_strings);
```

Следующим шагом программа создает и инициализирует массив динамической памяти для хранения указателей на структуру string в которых будут строки текста.

```cpp
ptr_on_str = (string*)calloc(count_strings, sizeof(char**));
initialization_ptr_on_str(&buffer, ptr_on_str);
```

Для первой сортировки этих указателей применяется собственная функция быстрой сортировки с компаратором, который сравнивает строки пропуская небуквенные символы.

```cpp
q_sort(ptr_on_str, count_strings, sizeof(ptr_on_str[0]), first_string_cmp);
```

Далее файл создается или очищается и в него записывается отсортированный текст.

```cpp
clear_file(output_file_name);
writing_in_file(ptr_on_str, count_strings, output_file_name);
```

Для второй сортировки используется библиотечная функция быстрой сортировки и компаратор, сравнивающий строки от конца к началу и пропускающий небуквенные символы.

```cpp
qsort(ptr_on_str, count_strings, sizeof(ptr_on_str[0]), second_string_cmp);
```

В конце программа записывает в файл текст отсортированный второй сортировкой и оригинальный текст.

```cpp
writing_in_file(ptr_on_str, count_strings, output_file_name)
```

---

#### <a name="Описание_устройства_программы/debugging">debugging

В этом файле содержатся функции для отладки и обработки ошибок.

---

```cpp
#define PRINT_ERROR
```

Макрос для вывода кода ошибки в формате:
>название_файла:строка ERROR CODE код_ошибки_из_enum ERRNO ошибка_errno название_функции

---
```cpp
#define ASSERT_FOR_ARR(ind, size)
```

Макрос для проверки выхода за пределы массива. Принимает на вход индекс к которому планируется обращаться и размер массива.

---

```cpp
#define $ANCHOR
#define $START_FUNCTION
#define $END_FUNCTION
```

Макросы для отслеживания пути исполнения программы. С их помощью легко находить место на котором программа падает.

---

```cpp
#define $PRINT_STR_ARR(arr, size)
#define $PRINT_PTR_ARR(arr, size)
#define $PRINT_INTPTR_ARR(int_arr, size)
```

Макросы выводящие массивы разных типов для отладки в формате:

>файл:строка ANCHOR название файла
название_массива[0] = значение
...
название_массива[size - 1] = значение

---

```cpp
#define $DEBUG_QSORT(reason)
```

Макрос, вызывающий функцию для отладки q_sort. Принимает на вход причину вызова для понимания на каком этапе исполнения q_sort мы находимся.

Вывод в следующем формате:

> маленькие_синие_элементы нетронутые_элементы большие_красные_элементы левый_указатель правый_указатель значение_целевого_элемента

---

```cpp
#define COLOR_TEXT(STR, COLOR)
#define COLOR_TEXT_START(COLOR)
#define COLOR_TEXT_END
```

Макросы для вывода цветного текста в терминал.

Список аргументов COLOR
```cpp
#define RED    "91"
#define GREEN  "92"
#define BLUE   "94"
#define YELLOW "33"
#define VIOLET "35"
```
COLOR_TEXT - окрашивает переданную строку в COLOR
COLOR_TEXT_START - окрашивает весь последующий текст до COLOR_TEXT_END
COLOR_TEXT_END - окончание цветного текста

---

```cpp
#define $название_типа(переменная_нужного_типа)
```

Набор макросов для удобного отладочного вывода переменных в формате:

>файл:строка ANCHOR название файла
название_переменной = значение_переменной

char выводиться вместе с числовым значением
string заключается в <>

---

```cpp
enum error_code_e {
    SUCCESS                  = 0,
    ERROR_IN_INPUT_PARAM     = 1,
    INCORRECT_MATRIX_SIZE    = 2,
    FIND_EOF                 = 3,
    UNDEFINED_TYPE           = 4,
    OPEN_FILE_ERROR          = 5,
    CLOSE_FILE_ERROR         = 6,
    STAT_READ_ERROR          = 7,
    ERROR_DURING_READING     = 8,
    ERROR_IN_MEM_ALLOCATION  = 9,
    ERROR_DURING_WRITING     = 10,
    INCORRECT_ARGC           = 11,
    INIT_VALUE               = -1
};
```

Enum ошибок возвращаемых большинством самописных функций.

---

## <a name="Описание_устройства_программы/string_sort"></a>string_sort

Файл содержащий различные сортировки

---

```cpp
error_code_e swap_symbol_by_symbol(char* first_str, char* second_str, const size_t size)
```

Функция меняющая две переменные first_str и second_str размера size значениями побайтово.

---

```cpp
error_code_e swap_all_strings(char* first_str, char* second_str, const size_t size);
```

Функция меняющая две переменные first_str и second_str размера size значениями через отдельный буфер.

---

```cpp
error_code_e swap_with_ll_buffer(char* first_str, char* second_str, const size_t size);
```

Функция меняющая две переменные first_str и second_str размера size значениями пакетами до 8 байт.

---

```cpp

error_code_e bubble_sort(char* str_array, const size_t size_x, const size_t size_y);
```

Функция сортировки массива строк str_array размером size_x на size_y пузырьком.

---

```cpp
error_code_e selection_sort(char* const str_array, const size_t size_x, const size_t size_y);
```
Функция сортировки массива строк str_array размером size_x на size_y выбором.

---

```cpp
error_code_e q_sort(void* const array, const size_t size, const size_t type_size, comparator cmp);
```

Алгоритм быстрой сортировки, для любого типа.
Принимает на вход сортируемый массив в виде void*, размер массива, размер сортируемого типа и указатель на функцию comparator - правило сравнения элементов

<a name="comparator"></a> Определение функции вида comparator:


```cpp
typedef int (comparator)(const void* first_element, const void* second_element);
```

---

```cpp
error_code_e merge_sort(void* const str_array, const size_t size, comparator cmp);
```

Алгоритм сортировки слиянием, для указателей на указатели. На вход принимает сортируемый массив в виде void*, размер массива и указатель на функцию вида comparator - правило сравнения элементов.

---

```cpp
error_code_e merge(const void* const first_arr, const size_t first_size, const void* const second_arr, const size_t second_size, void* const result_arr, const size_t result_size, comparator cmp);
```

Функция слияния двух отсортированных массивов в один отсортированный. На вход принимает два массива в виде void*,


---

```cpp
error_code_e copy_arr(const void* const lhs, const void* const rhs, const size_t size);
```

Функция копирования массива rhs указателей размера size в массив lhs

---

```cpp
int string_cmp(const void* const first_str, const void* const second_str);
```

Компаратор вида [comparator](#comparator), сравнивающий две строки в лексикографическом порядке.

---

```cpp
int int_cmp(const void* const first_element, const void* const second_element);
```

Компаратор вида [comparator](#comparator), сравнивающий два числа типа int.

```cpp
error_code_e test_bubble_sort   ();
error_code_e test_selection_sort();
error_code_e test_q_sort        ();
error_code_e test_merge_sort    ();
```

Функции для проверки работы сортировок.


