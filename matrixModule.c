#include <stdio.h>
#include <stdlib.h>
#include "matrixModule.h"

/**
* @brief функция инициализации матрицы
* @param rows: количество строк
* @param cols: количество столбцов
* @return: инициализированная матрица
*/
double** init_matr(int rows, int cols) {

    //выделение памяти под первую строку
    double **matr = malloc(rows * sizeof(double*));
    
    //выделение памяти под столбцы матрицы
    for (int i = 0; i < rows; i++) {
        matr[i] = malloc(cols * sizeof(double));
    } 

    //возвращение инициализированной матрицы
    return matr;
}

/**
* @brief функция заполнение матрицы с консоли
* @param rows: количество строк
* @param cols: количество столбцов
* @return: заполненная матрица
*/
double** read_matr(double** matrix, int rows, int cols) {

    //временная переменная для заполнения матрицы
    double value;

    //цикл для прохода по элементам матрицы
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            
            //вывод сообщения с просьбой ввести число
            printf("Введите элемент матрицы[%d, %d]: ", i + 1, j + 1);
            //сканирование числа в переменную
            scanf("%lf", &value);
            //запись элемента в матрицу
            matrix[i][j] = value;
        }
    } 
    return matrix;
}

/**
* @brief функция перестановки значений
* @param matrix: матрица со значениями
* @param rows_1: строка с ячейкой для замены
* @param rows_2: строка куда заменить
* @param coll_count: количество столбцов
* @return: результат замены
*/
double** row_change(double** matrix, int rows_1, int rows_2, int coll_count) {
    
    double temp = 0;

    for(int i = 0; i < coll_count; i++) {
        
        //переставляем переменные
        temp = matrix[rows_1][i];
        matrix[rows_1][i] = matrix[rows_2][i];
        matrix[rows_2][i] = temp;
    }

    return matrix;
}

/**
* @brief процедура вывода матрицы на экран
* @param matr: вещественная матрица
* @param rows: количество строк
* @param cols: количество столбцов
*/
void print_matr(double **matr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            printf("%6.2lf ", matr[i][j]);
        }
        //переход на новую строку после вывода
        printf("\n");
    }
    //переход на новую строку после вывода матрицы
    printf("\n");
}

/**
* @brief процедура освобождение памяти матрицы
* @param matrix: вещественная матрица
* @param rows: количество строк
*/
void matrix_free(double** matrix, int rows) {  // ДОБАВЛЕНА РЕАЛИЗАЦИЯ
    
    //цикл очистки памяти столбцов
    for(int i = 0; i < rows; i++) {
        free(matrix[i]);
    }

    //цикл очистки памяти от строки
    free(matrix);
}

/**
* @brief функция записи значений матрицы из файла
* @param fileName: имя файла для открытия
* @param rows: количество строк
* @param cols: количество столбцов
* @return: матрица со всеми значениями
*/
double** matrixReadFile(char fileName[], int rows, int cols) {

    //задаём временную матрицу для записи значений
    double **matrix;
    FILE *openFile;

    //открываем файл для чтения
    openFile = fopen(fileName, "r");

    //проверяем, открылся ли файл
    if (openFile == NULL) {
        printf("Ошибка: не удалось открыть файл '%s'\n", fileName);
        return NULL;  //возвращаем NULL при ошибке
    }

    //инициализируем матрицу
    matrix = init_matr(rows, cols);

    //проходимся циклом по матрице
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) { 
            //сканируем значение в матрицу
            if (fscanf(openFile, "%lf", &matrix[i][j]) != 1) {
                printf("Ошибка: неверные данные в файле на строке %d, столбце %d\n", i+1, j+1);
                fclose(openFile);
                matrix_free(matrix, rows);
                return NULL;
            }
        }
    }

    //завершаем работу с файлом
    fclose(openFile); 

    printf("Матрица успешно загружена из файла '%s'\n", fileName);

    //возвращаем матрицу
    return matrix;
}