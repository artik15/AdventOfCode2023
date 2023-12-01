#include <iostream>
#include <fstream>
#include <string>
#include <cctype>


int FindDigits(std::string str)
{
    int len = str.size();
    std::string first, last;
    int ret = 0;
    for(int i=0; i < len; i++)
    {
        if(isdigit(str[i]))
        {
            first = str[i];
            break;
        }
    }
    for(int i=len-1; i >= 0; i--)
    {
        if(isdigit(str[i]))
        {
            last = str[i];
            break;
        }
    }
    
    ret = stoi(first + last);
    return ret;
}



int main(int argc, char** argv)
{
    std::fstream file("./input.txt");
    std::string str;
    int sum = 0;

    while(std::getline(file , str))
    {
        std::cout << str << std::endl;
        sum = sum + FindDigits(str);
    }
    std::cout << sum << std::endl;
    file.close();
}