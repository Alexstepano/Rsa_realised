// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <iostream>
#include <openssl/applink.c>
#include <cstdlib> // для system
/* Имена ключевых файлов */


using namespace std;

void create_keys(char* passphrase)
{
    //Указатель на структуру для хранения ключей
    RSA* rsa = NULL;
    //Длина ключа в битах
    unsigned long bits = 4096;//2^12 
    FILE* priv_key_file = NULL, * pub_key_file = NULL;
    //контекст алгоритма шифрования
    const EVP_CIPHER* cipher = NULL;

    priv_key_file = fopen("privfilekey.txt", "wb");
    cout << "A" << endl;

    pub_key_file = fopen("pubfilekey.txt", "wb");
    cout << "B" << endl;
    //Генерируем ключи
    rsa = RSA_generate_key(bits, 65537, NULL, NULL);
    cout << "C" << endl;
    //Формируем контекст алгоритма шифрования
    OpenSSL_add_all_ciphers();//
    cipher = EVP_get_cipherbyname("bf-ofb");
    cout << "D" << endl;
    //Получаем из структуры rsa открытый и секретный ключи и сохраняем в файлах.
    //Секретный ключ шифруем с помощью парольной фразы "hello"
    PEM_write_RSAPrivateKey(priv_key_file, rsa, cipher, NULL, 0, NULL, passphrase);
    PEM_write_RSAPublicKey(pub_key_file, rsa);
    cout << "E" << endl;
    //Освобождаем память, выделенную под структуру rsa
    RSA_free(rsa);
    cout << "F" << endl;
    //закрываем файлы с ключами
    fclose(priv_key_file);
    fclose(pub_key_file);
    cout << "Z" << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    char parole[500] = {};
    cout << "введите пароль для закрытого ключа"<<endl;
    cin >> parole;
    create_keys(parole);
 cout << "Ключи сгенерированы и помещены в папку с исполняемым файлом" << endl;
 system("pause"); // Только для тех, у кого MS Visual Studio
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
