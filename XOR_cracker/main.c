#define _CRT_SECURE_NO_WARNINGS

#include "wchar.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define KeyLen 50 //длина ключа в шифровании
#define Alph 100 //предположим, что заглавных, строчных букв и спецсимволов в сумме не больше 100

char* code(char *msg, int size, char *chipertext) {
    printf("Шифруем сообщение... \n");
    //FILE *f = fopen("C:\\XOR\\chipertext.txt", "wb");
    FILE *f = fopen("chipertext.txt", "wb");
    char key[KeyLen];
    /*for (int i = 0; i < KeyLen; i++) {
     key[i] = 0;
     }*/
    memset(key, 0, sizeof(char)*KeyLen);
    printf("Введите ключ: ");
    printf("\n");
    //scanf("%s", &key);
    srand(clock());
    int maxLen = rand() % 25+4;
    for (int i = 0; i < maxLen; i+=4) {
        if (rand() % 2) {
            key[i] = rand() % 25 + 65;
            printf("%c", key[i]);
        }
        else {
            key[i] = rand() % 25 + 97;
            printf("%c", key[i]);
        }
        if (rand() % 2) {
            key[i+1] = rand() % 25 + 65;
            printf("%c", key[i+1]);
        }
        else {
            key[i+1] = rand() % 25 + 97;
            printf("%c", key[i+1]);
        }
        if (rand() % 2) {
            key[i+2] = rand() % 25 + 65;
            printf("%c", key[i+2]);
        }
        else {
            key[i+2] = rand() % 25 + 97;
            printf("%c", key[i+2]);
        }
        if (rand() % 2) {
            key[i+3] = rand() % 25 + 65;
            printf("%c", key[i+3]);
        }
        else {
            key[i+3] = rand() % 25 + 97;
            printf("%c", key[i+3]);
        }
    }
    printf("\n");
    int keylen = strlen(key);
    for (int n = 0, k = 0; n < size; n++, k++) {
        if (k == keylen) k = 0;
        *(chipertext + n) = *(msg + n) ^ key[k]; //Шифрование
        fprintf(f, "%c", *(chipertext+n));
        /*if (k+1 == keylen) k = 0;
         *(chipertext + n+1) = *(msg + n+1) ^ key[k+1]; //Шифрование
         if (k+2 == keylen) k = 0;
         *(chipertext + n+2) = *(msg + n+2) ^ key[k+2]; //Шифрование
         if (k+3 == keylen) k = 0;
         *(chipertext + n+3) = *(msg + n+3) ^ key[k+3]; //Шифрование
         */
    }
    /*for (int i = 0; i < size; i++) {
     fprintf(f, "%c", chipertext[i]);
     }*/
    fclose(f);
    return chipertext;
}

char *decode(char *msg, int size, char *chipertext, char *key, int keylen) {
    printf("Дешифруем сообщение... \n");
    for (int n = 0, k = 0; n < size; n+=4, k+=4) {
        if (k == keylen) k = 0;
        *(msg + n) = *(chipertext + n) ^ key[k]; //Дешифрование
        if (k+1 == keylen) k = 0;
        *(msg + n+1) = *(chipertext + n+1) ^ key[k+1]; //Дешифрование
        if (k+2 == keylen) k = 0;
        *(msg + n+2) = *(chipertext + n+2) ^ key[k+2]; //Дешифрование
        if (k+3 == keylen) k = 0;
        *(msg + n+3) = *(chipertext + n+3) ^ key[k+3]; //Дешифрование
    }
    return msg;
}

void XOR_shifted(char **shiftedArr, int size, int keylen, char *answ) {
    printf("Ксорим нулевую строку и строку со сдвигом... \n");
    for (int i = 0; i < size; i+=16) {
        answ[i] = shiftedArr[0][i] ^ shiftedArr[keylen][i];
        answ[i+1] = shiftedArr[0][i+1] ^ shiftedArr[keylen][i+1];
        answ[i+2] = shiftedArr[0][i+2] ^ shiftedArr[keylen][i+2];
        answ[i+3] = shiftedArr[0][i+3] ^ shiftedArr[keylen][i+3];
        answ[i+4] = shiftedArr[0][i+4] ^ shiftedArr[keylen][i+4];
        answ[i+5] = shiftedArr[0][i+5] ^ shiftedArr[keylen][i+5];
        answ[i+6] = shiftedArr[0][i+6] ^ shiftedArr[keylen][i+6];
        answ[i+7] = shiftedArr[0][i+7] ^ shiftedArr[keylen][i+7];
        answ[i+8] = shiftedArr[0][i+8] ^ shiftedArr[keylen][i+8];
        answ[i+9] = shiftedArr[0][i+9] ^ shiftedArr[keylen][i+9];
        answ[i+10] = shiftedArr[0][i+10] ^ shiftedArr[keylen][i+10];
        answ[i+11] = shiftedArr[0][i+11] ^ shiftedArr[keylen][i+11];
        answ[i+12] = shiftedArr[0][i+11] ^ shiftedArr[keylen][i+12];
        answ[i+13] = shiftedArr[0][i+12] ^ shiftedArr[keylen][i+13];
        answ[i+14] = shiftedArr[0][i+13] ^ shiftedArr[keylen][i+14];
        answ[i+15] = shiftedArr[0][i+15] ^ shiftedArr[keylen][i+15];
    }
}

int getKeyLen(char *chipertext, int size, char** shiftedArr) {
    printf("Получаем длину ключа... \n");
    int number_of_collumns = size;
    //int number_of_lines = size / 2; /**/
    int number_of_lines = sqrt(size);
    
    for (int j = 0; j<number_of_collumns; j+=16) {
        *(*(shiftedArr + 0) + j) = *(chipertext + j);//заполняем первую строку без сдвига.
        *(*(shiftedArr + 0) + j + 1) = *(chipertext + j + 1);
        *(*(shiftedArr + 0) + j + 2) = *(chipertext + j + 2);
        *(*(shiftedArr + 0) + j + 3) = *(chipertext + j + 3);
        *(*(shiftedArr + 0) + j + 4) = *(chipertext + j + 4);
        *(*(shiftedArr + 0) + j + 5) = *(chipertext + j + 5);
        *(*(shiftedArr + 0) + j + 6) = *(chipertext + j + 6);
        *(*(shiftedArr + 0) + j + 7) = *(chipertext + j + 7);
        *(*(shiftedArr + 0) + j + 8) = *(chipertext + j + 8);
        *(*(shiftedArr + 0) + j + 9) = *(chipertext + j + 9);
        *(*(shiftedArr + 0) + j + 10) = *(chipertext + j + 10);
        *(*(shiftedArr + 0) + j + 11) = *(chipertext + j + 11);
        *(*(shiftedArr + 0) + j + 12) = *(chipertext + j + 12);
        *(*(shiftedArr + 0) + j + 13) = *(chipertext + j + 13);
        *(*(shiftedArr + 0) + j + 14) = *(chipertext + j + 14);
        *(*(shiftedArr + 0) + j + 15) = *(chipertext + j + 15);
        
    }
    
    
    
    /*****************
     i -- строка, с которой работаем
     j -- элемент начального текста, с которым работаем
     k -- столбец, с которым работаем
     m -- столбец, с которым работаем, когда заполняем начало
     ****************/
    
    for (int i = 1; i<number_of_lines; i++) { //по каждой строке
        for (int j = 0, k = i; k<number_of_collumns; j++, k++) { //по каждому столбцу
            *(*(shiftedArr + i) + k) = *(chipertext + j);
        }
        for (int m = i - 1, l = 0; m >= 0; m--, l++) {
            *(*(shiftedArr + i) + l) = *(chipertext + number_of_collumns - m - 1);
        }
    }
    
    //тестовый вывод
    /*number_of_collumns = 15;
     for (int i = 0; i<number_of_lines && i<number_of_collumns; i++) {
     for (int j = 0; j<number_of_collumns; j++) {
     printf("%c", *(*(shiftedArr + i) + j));
     }
     printf("\n");
     }*/
    
    
    
    
    int count = 0;
    double percent;
    double posibleProc;
    int j = 0;
    int keylen = 0;
    int flag = 0;
    for (int k = 1, counter = 0, posibleKeylen = 0; k < 50 || counter < 5; k++) { //предполагаем что длина ключа не больше 100 /*поменяли на 50*/
        count = 0;
        for (int i = 0; i<size; i++) {
            if (shiftedArr[0][i] == shiftedArr[k][i]) {
                count++;
            }
        }
        percent = (((double) count) / ((double) size))*(double) 100;
        if (percent > 6) { //Если обнаружили всплеск
            switch (counter) { //counter -- переменная, считающая, сколько у нас уже было всплесков
                case 0: //если 0
                    posibleKeylen = k; // запоминаем строку, в которой произошел первый всплеск
                    posibleProc = percent; // и увеличиваем переменную подсчета процента
                    counter++;  //и счетчик
                    break;
                case 1:
                    if (k - posibleKeylen == posibleKeylen*counter) { //если наш всплеск периодичен
                        //printf("Первый всплеск периодичен!\n");
                        posibleProc += percent;
                        counter++;
                    }
                    break;
                case 2:
                    if (k - posibleKeylen == posibleKeylen*counter) {
                        //printf("Второй всплеск периодичен!\n");
                        posibleProc += percent;
                        counter++;
                    }
                    break;
                case 3:
                    if (k - posibleKeylen == posibleKeylen*counter) {
                        //printf("Третий всплеск периодичен!\n");
                        posibleProc += percent;
                        counter++;
                    }
                    break;
                case 4:
                    if (k - posibleKeylen == posibleKeylen*counter) {
                        //printf("Четвертый всплеск периодичен!\n");
                        posibleProc += percent;
                        counter++;
                        if (posibleProc / 5 > 5.5) { //если сумма процентов всплеска, деленная на кол-во всплесков, больше 5,5
                            keylen = posibleKeylen; //считаем, что наша предполагаемая длина ключа и есть длина ключа
                            return keylen;
                        }
                    }
                    break;
            }
        }
        else if (k - posibleKeylen == posibleKeylen*counter) { //если строка периодичена, но всплеска нет, делаем одну скидку на ошибку
            if (flag) { //проверка, были ли у нас уже такие скидки на ошибку. Если были, возвращаемся на позицию первого всплеска
                k = posibleKeylen;
                flag = 0;
                counter = 0;
            }
            else { //если не было, делаем все то же, будто тут есть всплеск
                flag = 1;
                posibleProc += percent;
                counter++;
                //printf("Увеличили флаг \n");
                if (counter >= 4) {
                    if (posibleProc / 5 > 5.5) {
                        keylen = posibleKeylen;
                        return keylen;
                    }
                }
            }
        }
        //printf("Процент совпадений в строке %d равен %.4f%%\n", k, percent);
    }
    printf("Длина равна %d \n", keylen);
    
    
    return 0;
}

void to_the_group(char *chipertext, char **groups_of_simbols, int size, int keylen) {
    printf("Раскидываем сообщение по группам... \n");
    for (int i = 0; i < keylen; i++) {
        for (int j = 0, k = i; j < Alph && k<size; j++, k += keylen) {
            *(*(groups_of_simbols + i) + j) = *(chipertext + k);
        }
    }
    
}

void XOR_groups(char **groups_of_simbols, int keylen) {
    printf("Ксорим символы в группах с пробелом... \n");
    for (int i = 0; i < keylen; i++) {
        for (int j = 0; j < Alph; j++) {
            *(*(groups_of_simbols + i) + j) = (*(*(groups_of_simbols + i) + j) ^ (int)' ');
            /*(*(groups_of_simbols + i) + j + 1) = (*(*(groups_of_simbols + i) + j + 1) ^ (int)' ');
             *(*(groups_of_simbols + i) + j + 2) = (*(*(groups_of_simbols + i) + j + 2) ^ (int)' ');
             *(*(groups_of_simbols + i) + j + 3) = (*(*(groups_of_simbols + i) + j + 3) ^ (int)' ');
             *(*(groups_of_simbols + i) + j + 4) = (*(*(groups_of_simbols + i) + j + 4) ^ (int)' ');
             *(*(groups_of_simbols + i) + j + 5) = (*(*(groups_of_simbols + i) + j + 5) ^ (int)' ');
             *(*(groups_of_simbols + i) + j + 6) = (*(*(groups_of_simbols + i) + j + 6) ^ (int)' ');
             *(*(groups_of_simbols + i) + j + 7) = (*(*(groups_of_simbols + i) + j + 7) ^ (int)' ');
             *(*(groups_of_simbols + i) + j + 8) = (*(*(groups_of_simbols + i) + j + 8) ^ (int)' ');
             *(*(groups_of_simbols + i) + j + 9) = (*(*(groups_of_simbols + i) + j + 9) ^ (int)' ');
             *(*(groups_of_simbols + i) + j + 10) = (*(*(groups_of_simbols + i) + j + 10) ^ (int)' ');
             *(*(groups_of_simbols + i) + j + 11) = (*(*(groups_of_simbols + i) + j + 11) ^ (int)' ');
             *(*(groups_of_simbols + i) + j + 12) = (*(*(groups_of_simbols + i) + j + 12) ^ (int)' ');
             *(*(groups_of_simbols + i) + j + 13) = (*(*(groups_of_simbols + i) + j + 13) ^ (int)' ');
             *(*(groups_of_simbols + i) + j + 14) = (*(*(groups_of_simbols + i) + j + 14) ^ (int)' ');
             *(*(groups_of_simbols + i) + j + 15) = (*(*(groups_of_simbols + i) + j + 15) ^ (int)' ');*/
        }
    }
}



char * getKey(char **groups_of_simbols, int keylen) {
    printf("Получаем ключ... \n");
    //английские буквы по частоте, сначала строчные, потом заглавные
    char alph[53] = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'x', 'j', 'q', 'z', 'E', 'T', 'A', 'O', 'I', 'N', 'S', 'H', 'R', 'D', 'L', 'C', 'U', 'M', 'W', 'F', 'G', 'Y', 'P', 'B', 'V', 'K', 'X', 'J', 'Q', 'Z', '\0'};
    int *maxi = (int*) malloc(keylen*sizeof(int));
    int freq[53];
    int *maxfreq = (int*) malloc(keylen*sizeof(int));
    /*for (int i = 0; i < 53; i++) {
     freq[i] = 0;
     }
     for (int i = 0; i < keylen; i++) {
     maxi[i] = 0;
     }
     for (int i = 0; i < keylen; i++) {
     maxfreq[i] = 0;
     }*/
    memset(freq, 0, sizeof(int)*53);
    memset(maxi, 0, sizeof(int) * keylen);
    memset(maxfreq, 0, sizeof(int) * keylen);
    for (int n = 0; n < keylen; n++) {
        for (int i = 0; i < Alph; i++) {
            for (int j = 0; j < 53; j++) {
                if (groups_of_simbols[n][i] == alph[j]) {
                    freq[j]++;
                    break;
                }
            }
        }
        for (int i = 0; i < 53; i++) {
            if (maxfreq[n] < freq[i]) {
                maxi[n] = i;
                maxfreq[n] = freq[i];
            }
            freq[i] = 0;
        }
        /*for (int i = 0; i < 53; i++) {
         freq[i] = 0;
         }*/
        //printf("\n%d -- %c", n, alph[maxi[n]]);
    }
    //printf("\n");
    char* key = (char*) malloc((keylen + 1)*sizeof(char));
    for (int i = 0; i < keylen; i++) {
        key[i] = alph[maxi[i]];
    }
    key[keylen] = '\0';
    printf("Ключ: %s\n", key);
    return key;
}



int main() {
    //setlocale(LC_ALL, "Russian");
    double time_start = (double) clock();
    for (int iter = 0; iter < 10; iter++) {
        printf("\nИтерация номер: %d\n", iter);
        printf("Время с запуска программы: %f\n", ((double) clock() - time_start) / CLOCKS_PER_SEC);
        FILE *input = fopen("/Users/sobieg/input_xor.txt", "rb");
        FILE *output = fopen("/Users/sobieg/output_xor.txt", "wb");
        //FILE *input = fopen("C:\\XOR\\input_xor_e.txt", "rb");
        
        /*FILE *input = fopen("input_xor.txt", "rb");
         FILE *output = fopen("output_xor.txt", "wb");*/
        if (input == NULL) {
            printf("Ошибка чтения файла!\n");
            exit(1);
        }
        int size = 0;/**/
        /*while (fgetc(input) != EOF) {
         size++; //В size теперь длина нашего текста
         }*/
        fseek(input, 0, SEEK_END);
        size = ftell(input);
        fseek(input, 0, SEEK_SET);
        
        char* msg = (char*) malloc(size*sizeof(char)); //памяти на хранение открытого сообщениия
        char* uncoded = (char*) malloc(size*sizeof(char)); //выделяем памяти под расшифрованный текст. Просто для того, чтобы быть уверенным, что мы никак не использовали открытый текст
        char* chipertext = (char*) malloc(size*sizeof(char)); //памяти на хранение зашифрованного сообщения
        char* answ = (char*) malloc(size*sizeof(char)); //памяти еще памяти, чтобы ту не перезаписывать
        char* xored = (char*) malloc(size*sizeof(char)); //больше памяти богу памяти
        char**shiftedArr = (char**) malloc((size / 2)*sizeof(char*)); // выделяем память на массив ссылок на ссылки.
        for (int i = 0; i < (size/2); i++) {
            *(shiftedArr + i) = (char*) malloc(size * sizeof(char)); //выделяем памяти на каждую строку.
            if ((shiftedArr + i) == NULL) {
                exit(1);
            }
        }
        int keylen;
        if (msg == NULL || chipertext == NULL || answ == NULL || xored == NULL || shiftedArr == NULL || uncoded == NULL) {
            exit(1);
        }
        
        
        
        
        for (int i = 0; i<size; i++) {
            msg[i] = fgetc(input); //в msg теперь хранится наш открытый текст
        }
        fclose(input);
        
        
        keylen = getKeyLen(code(msg, size, &(*chipertext)), size, &(*shiftedArr)); //находим длину ключа
        char **groups_of_simbols = (char**) malloc((keylen) *sizeof(char*)); // выделяем память на массив ссылок на ссылки
        if (groups_of_simbols == NULL) {
            exit(1);
        }
        for (int i = 0; i < (keylen); i++) {
            *(groups_of_simbols + i) = (char*) malloc(Alph * sizeof(char)); //выделяем памяти на каждую строку.
            if ((groups_of_simbols + i) == NULL) {
                exit(1);
            }
        }
        char *key = (char*) malloc(keylen*sizeof(char)); //выделяем памяти под хранение ключа
        if (key == NULL) {
            exit(1);
        }
        
        
        XOR_shifted(&(*shiftedArr), size, keylen, &(*xored)); //ксорим 0 строку с keylen строкой, результат в xored
        to_the_group(chipertext, &(*groups_of_simbols), size, keylen); //распределяем символы по группам, всего keylen групп, в каждой группе символы, которые кодируются одним и тем же символом ключа, соответственно, одна группа -- один символ ключа
        XOR_groups(&(*groups_of_simbols), keylen); //ксорим кажду из этих групп с самым распространенным символом языка, в нашем случае с пробелом
        //XOR_groups_e(&(*groups_of_simbols), keylen);
        key = getKey(&(*groups_of_simbols), keylen); //получаем ключ при помощи нахождения самого частовстречающегося символа в каждой группе, считаем, что это наш символ ключа
        decode(&(*uncoded), size, &(*chipertext), key, keylen); //дешифруем
        
        for (int i = 0; i < size; i++) {
            fprintf(output, "%c", uncoded[i]);
        }
        printf("Расшифрованное сообщение в файле output.txt \n");
        
        
        
        free(msg);
        free(chipertext);
        free(uncoded);
        free(answ);
        free(key);
        free(xored);
        
        for (int i = 0; i < (size/2); i++) {
            free(shiftedArr[i]);
        }
        free(shiftedArr);
        for (int i = 0; i < (keylen); i++) {
            free(groups_of_simbols[i]);
        }
        free(groups_of_simbols);
        
        msg = NULL;
        chipertext = NULL;
        uncoded = NULL;
        answ = NULL;
        key = NULL;
        xored = NULL;
        shiftedArr = NULL;
        groups_of_simbols = NULL;
    }
    printf("\n\n");
    printf("Общее время работы: %f\n", ((double) clock() - time_start) / CLOCKS_PER_SEC);
    //getchar();
}
