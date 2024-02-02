# HW3-Operating-Systems
## Задание на 10 баллов: ***Для всех процессов вывести дополнительную информацию об их потомках и родителях. Организовать в программе дополнительно запуск процесса, который по завершении вычислений и выводе результатов выводит информацию о содержимом текущего каталога.***
### Решение расположено в файле [main.cpp](https://github.com/AMGureev/HW3-Operating-Systems/blob/main/main.cpp)
Для выполнения задания на 10 баллов была разработана функция `printProcessInfo()`, которая выводит на экран информацию о процессе. </br> Также с **`78`** строки функции `main()` создается процесс, который по завершении вычислений и выводе результатов выводит информацию о содержимом текущего каталога. 
## Задание на 8 баллов: ***Разработать программу, в которой родительский процесс вычисляет число Фибоначчи, а процесс-ребенок вычисляет значение факториала. В качестве исходного значения используется аргумент из командной строки. Использовать беззнаковую 64-разрядную целочисленную арифметику. Не забыть зафиксировать возникновение переполнения.***
Код имеет подробные комментарии, благодаря которым становится понятна логика работы отдельных функций и используемых решений.</br>
Ниже продемонстрированы 2 проверки на переполнения:
```c++
            if (result > UINT64_MAX / i) { // factorial
                printf("Overflow occurred during factorial calculation\n");
                exit(EXIT_FAILURE);
            }

            if (b > UINT64_MAX - a) { // fibonacci
                printf("Overflow occurred during Fibonacci calculation\n");
                exit(EXIT_FAILURE);
            }
```
## Работу выполнил студент 2 курса БПИ227 Гуреев Александр Михайлович
