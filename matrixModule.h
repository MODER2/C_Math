#include <stdio.h>
#include <stdlib.h>

#pragma once

/**
* @brief функция инициализации матрицы
* @param rows: количество строк
* @param cols: количество столбцов
* @return: инициализированная матрица
*/
double** init_matr(int rows, int cols);

/**
* @brief функция заполнение матрицы с консоли
* @param rows: количество строк
* @param cols: количество столбцов
* @return: заполненная матрица
*/
double** read_matr(double** matrix, int rows, int cols);

/**
* @brief функция перестановки значений
* @param matrix: матрица со значениями
* @param rows_1: строка с ячейкой для замены
* @param rows_2: строка куда заменить
* @param coll_count: количество столбцов
* @return: результат замены
*/
double** row_change(double** matrix, int rows_1, int rows_2, int coll_count);

/**
* @brief процедура вывода матрицы на экран
* @param matr: вещественная матрица
* @param rows: количество строк
* @param cols: количество столбцов
*/
void print_matr(double **matr, int rows, int cols);

/**
* @brief процедура освобождение памяти матрицы
* @param matrix: вещественная матрица
* @param rows: количество строк
*/
void matrix_free(double** matrix, int rows);

/**
* @brief функция записи значений матрицы из файла
* @param fileName: имя файла для открытия
* @param rows: количество строк
* @param cols: количество столбцов
* @return: матрица со всеми значениями
*/
double** matrixReadFile(char fileName[], int rows, int cols);