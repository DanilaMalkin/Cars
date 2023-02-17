#include <stdio.h>
#include <string.h>
#include "time.h"
#include <stdlib.h> //exit()
#define lmax 100
struct car {
    char firma[lmax], colour[lmax];
    struct {
        char series[lmax], number[lmax];
    } model;
    int price;
    int engine;
    struct {
        int year, month;
    } date;
};

int pr(int min, int max, FILE* f)
{
    int k = 0;
    fscanf(f, "%d", &k);
    if ( k < min || k>max)
        k = 0;
    return k;
}

void pr2(FILE *f, char s[])
{
    fscanf(f, "%s", s);
}


// просмотр файла
int finput(struct car at[])
{
    int k, i = 0;
    FILE* f;
    struct car* uat;
    time_t t;
    time(&t);
    struct tm* today = localtime(&t);
    int year = today->tm_year + 1900;
    if (!(f = fopen("/Users/danila/CLionProjects/lekzia25/untitled33/Cars.txt", "r")))
    {
        puts("файл не найден");
        exit(1);
    }
    else
    {
        printf("Файл содержит количество структур:");
        while (!feof(f))
        {
            fscanf(f, "%d", &k);
            printf("%d\n", k);
            for (uat = at; uat < at + k; uat++)
            {
                pr2(f, uat->firma);
                pr2(f, uat->model.series);
                pr2(f, uat->model.number);
                uat->date.year = pr(1885, year, f);
                uat->date.month = pr(1, 12, f);
                pr2(f, uat->colour);
                uat->engine = pr(200, 8000, f);
                uat->price = pr(100, 20000000, f);
            }
        }
    }
    fclose(f);
    return k;
}


void output(struct car at[], int k)
{
    struct car *uat;
    int i = 0;
    for (uat = at; uat < at+k; uat++) {
        printf("Машина №%d\n", ++i);
        printf("фирма: %s\nмодель серия: %s\nмодель номер: %s\n", uat->firma, uat->model.series, uat->model.number);
        printf("год выпуска: %d\nмесяц выпуска: %d\n", uat->date.year, uat->date.month);
        printf("цвет: %s\nобъем двигателя: %dml\nцена: %d$\n", uat->colour, uat->engine, uat->price);
        printf("\n");
    }
}

int find(struct car at[], int k, char firma2[][lmax],int enginein)
{
    struct car* uat;
    int j, f,e1;
    e1 = enginein;
    for (f = 0, uat = at; uat < at + k; uat++)
        if (uat->engine >= e1)
        {
            for(j = 0; j < f && strcmp(uat->firma, firma2[j]); j++);
            if (j == f)
            {
                strcpy(firma2[f], uat->firma);
                f++;
            }
        }
    return f;
}

void result(int f, char firma2[][lmax])
{
    printf("Машины имеющие объём двигателя больше заданного:\n");
    for (int i = 0; i < f; i++)
        printf("%d. %s\n", i + 1, firma2[i]);
}

void resultf(char filename[], FILE* fout, int f, char firma2[][lmax])
{
    int i;
    fprintf(fout, "Машины имеющие объём двигателя больше заданного:\n");
    for (i = 0; i < f; i++)
        fprintf(fout, "%d. %s\n", i + 1, firma2[i]);
}

int main()
{
    struct car at[lmax];
    int f, k,enginein;
    char firma2[lmax][lmax];
    FILE* fout;
    char filename[81];

    k = finput(at);
    output(at, k);
    do {
        printf("Введите минимальный объём двигателя для поиска ");
        scanf("%d", &enginein);
        while (getchar() != '\n');
    } while (enginein <= 200 || enginein > 8000);

    f = find(at, k, firma2,enginein);

    printf("введите файл вывода:  ");
    fout = fopen(gets(filename), "w");

    if (!f)
    {
        printf("нет подходящих машин");
        fputs("нет подходящих машин", fout);
    }
    else
    {
        result(f, firma2);
        resultf(filename, fout, f, firma2);
    }
    fclose(fout);
    return 0;
}

