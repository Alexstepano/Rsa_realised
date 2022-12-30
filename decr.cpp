// encryptor.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <direct.h>
#include<io.h>
#include "sys/stat.h"
#include <fstream>
#include <clocale>
#include <windows.h>
#include <openssl/applink.c>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <fcntl.h>
#include <stdlib.h>
#include <openssl/evp.h>
using namespace std;
int main(void)
{
    setlocale(LC_ALL, "rus");//включаем русский язык
    char path1[255];
    char path2[255];
    char path3[255];
    char parole [255] ;
    char pathz[255];
    char costil[255];
    char path[255];//создаем буфферы,куда мы печатаем название деректории
    int h = 0;
    cout << "ВВЕДИТЕ 0, если желаете использовать ручной ввод; ВВедите 1, если с заготовленными условиями" << endl;
    cin >> h;
    if (h == 0) {
        gets_s(costil, 250);
        cout << "введите имя директории, в которой лежат файлы для дешифрования(можно использовать только латинские буквы)" << endl;
        gets_s(path, 255);//получаем название деректории откуда берем зашифрованные файлы
        cout << "введите имя директории, в которой лежат  расшифрованные файлы(можно использовать только латинские буквы)" << endl;
        gets_s(path1, 255);//получаем название деректории куда кладем дешифрованные файлы
        cout << "введите имя директории, в которой лежат  копии файлов для дешифрования(можно использовать только латинские буквы)" << endl;
        gets_s(path2, 255);
        cout << "close key" << endl;
        gets_s(path3, 250);
    }
    else {
        gets_s(costil, 250);
        gets_s(pathz, 250);
        fstream fil(pathz);
        fil.getline(path, 255);
        fil.getline(path1, 255);
        fil.getline(path2, 255);
        fil.getline(path3, 255);
        cout << path << 211 << endl;
        cout << path1 << endl;
        cout << path2 << endl;
        cout << path3 << endl;
        fil.close();
    }
    cout << "parole" << endl;
    gets_s(parole, 250);
    RSA* privKey = NULL;
    FILE* privKey_file;
    unsigned char* ptext, * ctext;
    int inlen, outlen;
    struct stat s;
    DIR* dir = opendir(path);//получая указатель на поток к папке и вставляем наш путь к ней, открывая ее
    struct dirent* ent;//структура данных в папке
    privKey_file = fopen(path3, "rb");
 if (privKey_file == NULL) {
       cout << "err:filekey do not open ";
       return -1;
   }
 privKey = PEM_read_RSAPrivateKey(privKey_file, NULL, NULL, parole);

  fclose(privKey_file);
  int key_size = RSA_size(privKey);
  ptext = (unsigned char*)malloc(key_size);
  ctext = (unsigned char*)malloc(key_size);
 
    cout << key_size << endl;
    cout << ptext << endl;
    cout << ctext << endl;

    _chdir(path);//меняет рабочую директорию на указанный путь
    if (dir)//если открылось
    {

        while ((ent = readdir(dir)) != NULL)
        {
            cout << (ent->d_name) << "\n";//из структуры мы получаем имя
            if (stat((ent->d_name), &s) == 0) {

                if (s.st_mode & S_IFDIR)//это директория
                {
                    cout << "direct" << "\n"; cout << "_____________________________________________" << endl;

                }
                else if (s.st_mode & S_IFREG)
                {
                    char nome[500] = { "crpt" };//если убрать в начало,то все ломается

                    char l_pyt1[1500] = { "crpt" };//пути
                    char l_pyt2[1500] = { "crpt" };
                    char l_pyt3[1500] = { "crpt" };
                    char l_pyt4[1500] = { "crpt" };
                    cout << "file" << "\n";//it a file
                    strcpy(nome, "de$");// добавляем crpt в начало
                    strcat(nome, ent->d_name);//а потом приписываем имя
                    cout << nome << endl;
                    //______закрипт.откуда__________________________________________________________________________________________
                    strcpy(l_pyt1, path);
                    strcat(l_pyt1, "\\");
                    strcat(l_pyt1, nome);
                    cout << l_pyt1 << endl;
                    //________сейв деректория________________________________________________________________________________________
                    strcpy(l_pyt2, path1);
                    strcat(l_pyt2, "\\");
                    strcat(l_pyt2, nome);
                    cout << l_pyt2 << endl;
                    //________куда. деректория________________________________________________________________________________________
                    strcpy(l_pyt3, path);
                    strcat(l_pyt3, "\\");
                    strcat(l_pyt3, ent->d_name);
                    cout << l_pyt3 << endl;
                    //________копия деректория_____
                    strcpy(l_pyt4, path2);
                    strcat(l_pyt4, "\\");
                    strcat(l_pyt4, ent->d_name);
                    cout << l_pyt4 << endl;
                    //FILE* file;
                    //FILE* ofs;
                   // file = fopen(ent->d_name, "rb");//открываем для чтения
                    //ofs = fopen(nome, "wb");//для записи и шифровки
                    int out = _open(nome, O_CREAT | O_TRUNC | O_RDWR| O_BINARY | O_APPEND, 0600);
                    int in = _open(ent->d_name, O_RDWR | O_BINARY);
                    if (in == NULL) {//проверяем,что открылся
                        cout << "err:file do not open ";
                        break;
                    }
                    else {
                        cout << "ok" << "\n";
                    }
                    while (1) {//читаем файл до конца файла и дешифруем по блокам
                        inlen = _read(in, ctext, key_size);
                        cout << inlen;
                        cout << "goood" << endl;
                        if (inlen <= 0) break;
                        cout << "goood" << endl;
                        cout << ptext << endl;
                        cout << ctext << endl;
                        outlen =  RSA_private_decrypt(inlen, ctext, ptext, privKey, RSA_PKCS1_PADDING);
                        cout << "goood" << endl;
                        if (outlen < 0) { cout << "mistake" << endl; break; }
                        cout << "goood" << endl;
                        _write(out, ptext, outlen);
                        cout << "goood" << endl;


                    }
                    //fclose(file);
                    //fclose(ofs);

                    CopyFileA(l_pyt1, l_pyt2, FALSE);//перемещаем декриптованный файл в защищенную директорию
                    CopyFileA(l_pyt3, l_pyt4, FALSE);//перемещаем файл в сейв. директорию

                   // DeleteFileA(l_pyt1);//удаляем лишний закрипт.файл из раб.деректории
                    //DeleteFileA(l_pyt3);//удаляем лишний исходный файл из раб.деректории
                    cout << "_____________________________________________" << endl;
                }
                else {
                    cout << "unknown" << "\n";//неизвестный объект
                    cout << "_____________________________________________" << endl;
                }

            }
        }
    }
    else
    {
        cout << "Error opening directory" << endl;
    }
    return 0;
}





// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
