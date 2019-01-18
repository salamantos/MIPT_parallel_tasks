## 2 Перемножение плотных матриц OpenMP

Программе на вход подаётся 2 файла с матрицами и число потоков, а также имя
файла, куда сохраняется результат перемножения матриц. Файл с матрицами
записасти, далее сами числа матрицы по строкам (1-ая строка матрицы, 2-ая, ...), как
наборн в бинарном формате первые 6 байт слово MATRIX, затем uint64_t размерно
чисел типа double. Требуется написать программу с использованием OpenMP, которая
осуществляет перемножение матриц в много потоков. Построить график зависимости
времени решения задачи от числа потоков и от размерности матрицы.
