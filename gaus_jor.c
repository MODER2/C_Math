#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#include "matrixModule.h"

int main() {
    SetConsoleOutputCP(CP_UTF8); 
    
    //Создаём константу, для хранения размерности системы (5 уравнений = 5 неизвестных)
    const int N = 4; 
    //Создаём константу для хранения точности вычисления
    const double epsilon = 0.00001;
    //Переменная для хранения количества итераций
    int count = 0;

    //Создаём указатель на матрицу
    double **matrix;
    //Выделяем память под массив ответов
    double *result = malloc(N * sizeof(double));

    int choice;
    printf("Выберите способ ввода матрицы:\n");
    printf("1 - Ручной ввод\n");
    printf("2 - Загрузка из файла\n");
    printf("Ваш выбор: ");
    scanf("%d", &choice);

    if (choice == 1) {
        //Ручной ввод
        //Выделяем память под расширенную матрицу
        matrix = init_matr(N, N + 1);
        //Записываем значения в матрицу
        matrix = read_matr(matrix, N, N + 1);
    } 
    else if (choice == 2) {
        //Загрузка из файла
        char filename[100];
        printf("Введите имя файла: ");
        scanf("%s", filename);
        
        matrix = matrixReadFile(filename, N, N + 1);
        
        //Проверяем, успешно ли загрузилась матрица
        if (matrix == NULL) {
            printf("Не удалось загрузить матрицу из файла. Программа завершена.\n");
            free(result);
            return 1;  //Выход с ошибкой
        }
    }
    else {
        printf("Неверный выбор. Программа завершена.\n");
        free(result);
        return 1;
    }

    //Выводим расширенную матрицу на экран
    printf("Ваша расширенная матрица:");
    print_matr(matrix, N, N + 1);

    //Основной цикл программы для метода Жордана-Гаусса
    for(int k = 0; k < N; k++) {  // k - номер текущего шага

        //Проверка условия, что элемент диагонали не равен 0
        if(fabs(matrix[k][k]) < epsilon) {

            //Спускаемся на строку ниже
            int m = k + 1;

            //Ищем строку, где элемент диагонали не равен нулю
            while((m < N) && (fabs(matrix[m][k]) < epsilon)) {
                //Переходим на следующую строку
                m++; 
            }

            //Проверка на выход за пределы массива
            if(m == N) {
                puts("Система не имеет решения (не возможно найти ненулевой элемент таблицы)");
                matrix_free(matrix, N);
                free(result);
                return 1;  //Выход с ошибкой
            }

            //меняем строки местами, чтобы избежать деления на 0
            matrix = row_change(matrix, k, m, N + 1);
        }

        //Исключаем переменную xk из ВСЕХ уравнений, кроме k-го
        for(int i = 0; i < N; i++) {
            //Пропускаем текущую строку k (её мы будем нормировать)
            if(i != k) {
                //Вычисляем множитель для исключения xk из строки i
                double multiplier = matrix[i][k] / matrix[k][k];
                
                //Преобразуем все элементы строки i, начиная с текущего столбца k
                for(int j = k; j <= N; j++) {
                    matrix[i][j] = matrix[i][j] - multiplier * matrix[k][j];
                }
                //Явно обнуляем элемент в столбце k (для наглядности)
                matrix[i][k] = 0.0;
            }
        }

        //Нормируем текущую строку k - делаем диагональный элемент равным 1
        double pivot = matrix[k][k];
        for(int j = k; j <= N; j++) {
            matrix[k][j] = matrix[k][j] / pivot;
        }

        //вывод результата итераций
        count = count + 1;
        printf("%d-ая итерация (обработана переменная x%d): \n", count, k);
        print_matr(matrix, N, N + 1);
    }

    printf("Результат: \n");
    for(int i = 0; i < N; i++) {
        result[i] = matrix[i][N];  //Решение берется прямо из последнего столбца
        printf("x%d = %lf\n", i, result[i]);
    }

    //освобождаем память указателя
    matrix_free(matrix, N);
    free(result);
    matrix = NULL;

    return 0;
}