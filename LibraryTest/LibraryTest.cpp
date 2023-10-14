#include <string>
#include <iostream>
#include "Dll2.h"
#include <windows.h>
#include <cstdlib>
typedef std::string(*encrypt_ptr_t)(std::string, int);
typedef std::string(*decrypt_ptr_t)(std::string, int);

int main(int argc, char* argv[])
{
   

    std::string choice = argv[1];
    int key = std::atoi(argv[2]);
    std::string str = argv[3];

    HINSTANCE handle = LoadLibrary(TEXT("Dll2.dll"));
    if (handle == nullptr || handle == INVALID_HANDLE_VALUE)
    {
        std::cout << "Lib not found" << std::endl;
        return 1;
    }

    if (choice == "encrypt")
    {
        encrypt_ptr_t encrypt_ptr = (encrypt_ptr_t)GetProcAddress(handle, "Encrypt");
        if (encrypt_ptr == nullptr)
        {
            std::cout << "Function 'Encrypt' not found" << std::endl;
            return 1;
        }
        std::cout << encrypt_ptr(str, key) << std::endl;
    }
    else if (choice == "decrypt")
    {
        decrypt_ptr_t decrypt_ptr = (decrypt_ptr_t)GetProcAddress(handle, "Decrypt");
        if (decrypt_ptr == nullptr)
        {
            std::cout << "Function 'Decrypt' not found" << std::endl;
            return 1;
        }
        std::cout << decrypt_ptr(str, key) << std::endl;
    }
    FreeLibrary(handle);

    return 0;
}