#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>

uint64_t factorial(unsigned int n) { // Вычисление факториала
    if (n == 0 || n == 1) {
        return 1;
    } else {
        uint64_t result = 1;
        for (unsigned int i = 2; i <= n; ++i) {
            // Проверка на переполнение
            if (result > UINT64_MAX / i) {
                printf("Overflow occurred during factorial calculation\n"); // Произошло переполнение во время вычисления факториала
                exit(EXIT_FAILURE);
            }
            result *= i;
        }
        return result;
    }
}

uint64_t fibonacci(unsigned int n) { // Вычисление фибоначчи
    if (n == 0) {
        return 0;
    } else if (n == 1 || n == 2) {
        return 1;
    } else {
        uint64_t a = 0, b = 1, temp;
        for (unsigned int i = 2; i <= n; ++i) {
            // Проверка на переполнение
            if (b > UINT64_MAX - a) {
                printf("Overflow occurred during Fibonacci calculation\n"); // Произошло переполнение во время вычисления числа Фибоначчи
                exit(EXIT_FAILURE);
            }
            temp = b;
            b += a;
            a = temp;
        }
        return b;
    }
}

void printProcessInfo(const char *label) { // Функция для вывода доп информации о процессе (на 10 баллов)
    printf("[%s] Process ID: %d, Parent ID: %d\n", label, getpid(), getppid());
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned int input = atoi(argv[1]);

    // Создание процесса-ребенка
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        // Процесс-ребенок
        printProcessInfo("Child");
        uint64_t result_factorial = factorial(input);
        printf("Factorial of %u is %llu\n", input, result_factorial);
    } else {
        // Процесс-родитель
        wait(nullptr);
        printProcessInfo("Parent");
        uint64_t result_fibonacci = fibonacci(input);
        printf("Fibonacci of %u is %llu\n", input, result_fibonacci);

        // Создание дополнительного процесса для вывода информации о текущем каталоге
        pid_t dirInfoPid = fork();

        if (dirInfoPid < 0) {
            perror("Fork for directory info failed");
            return EXIT_FAILURE;
        }

        if (dirInfoPid == 0) {
            // Процесс для вывода информации о текущем каталоге
            printProcessInfo("Directory Info");

            DIR *dir;
            struct dirent *ent;

            if ((dir = opendir(".")) != nullptr) {
                while ((ent = readdir(dir)) != nullptr) {
                    printf("%s\n", ent->d_name);
                }
                closedir(dir);
            } else {
                perror("Unable to open directory");
                return EXIT_FAILURE;
            }

            printf("Directory info process finished.\n");
        } else {
            // Процесс-родитель ждет завершения процесса вывода информации о каталоге, где расположен файл
            wait(nullptr);
            printf("All processes finished.\n");
        }
    }
    return EXIT_SUCCESS;
}
