#include <iostream>
#include <fstream>
#include <string>
#include <cctype>


/*ITS BAD I KNOW, DID NOT HAVE MUCH TIME*/

std::string FindFirstDigit(std::string str)
{
    int len = str.size();
    size_t found;
    std::string digit;
    size_t first_pos = 0;
    for(int i=0; i < len; i++)
    {
        if(isdigit(str[i]))
        {
            digit = str[i];
            first_pos = i;
            break;
        }
    }

    found = str.find("one");
    if(found != std::string::npos && ( found < first_pos))
    {
        digit = "1";
        first_pos = found;
    }
    found = str.find("two");
    if(found != std::string::npos && (found < first_pos))
    {
        digit = "2";
        first_pos = found;
    }
    found = str.find("three");
    if(found != std::string::npos && (found < first_pos))
    {
        digit = "3";
        first_pos = found;
    }
    found = str.find("four");
    if(found != std::string::npos && (found < first_pos))
    {
        digit = "4";
        first_pos = found;
    }
    found = str.find("five");
    if(found != std::string::npos && (found < first_pos))
    {
        digit = "5";
        first_pos = found;
    }
    found = str.find("six");
    if(found != std::string::npos && (found < first_pos))
    {
        digit = "6";
        first_pos = found;
    }
    found = str.find("seven");
    if(found != std::string::npos && (found < first_pos))
    {
        digit = "7";
        first_pos = found;
    }
    found = str.find("eight");
    if(found != std::string::npos && (found < first_pos))
    {
        digit = "8";
        first_pos = found;
    }
    found = str.find("nine");
    if(found != std::string::npos && (found < first_pos))
    {
        digit = "9";
        first_pos = found;
    }

    return digit;
}

std::string FindLastDigit(std::string str)
{
    int len = str.size();
    size_t found;
    std::string digit;
    size_t last_pos = 0;
    size_t next = 0;
    for(int i=len-1; i >= 0; i--)
    {
        if(isdigit(str[i]))
        {
            digit = str[i];
            last_pos = i;
            break;
        }
    }

    next = 0;
    do
    {
        found = str.find("one", next);
        if(found != std::string::npos)
        {
            if (found > last_pos)
            {
                digit = "1";
                last_pos = found;
            }
            next = found+1;
        }
    } while (found != std::string::npos);

    next = 0;
    do
    {
        found = str.find("two", next);
        if(found != std::string::npos)
        {
            if (found > last_pos)
            {
            digit = "2";
            last_pos = found;
            }
            next = found+1;
        }
    } while (found != std::string::npos);

    next = 0;
    do
    {
        found = str.find("three", next);
        if(found != std::string::npos)
        {
            if (found > last_pos)
            {
            digit = "3";
            last_pos = found;
            }
            next = found+1;
        }
    } while (found != std::string::npos);

    next = 0;
    do
    {
        found = str.find("four", next);
        if(found != std::string::npos)
        {
            if (found > last_pos)
            {
            digit = "4";
            last_pos = found;
            }
            next = found+1;
        }
    } while (found != std::string::npos);

    next = 0;
    do
    {
        found = str.find("five", next);
        if(found != std::string::npos)
        {
            if (found > last_pos)
            {
            digit = "5";
            last_pos = found;
            }
            next = found+1;
        }
    } while (found != std::string::npos);

    next = 0;
    do
    {
        found = str.find("six", next);
        if(found != std::string::npos)
        {
            if (found > last_pos)
            {
            digit = "6";
            last_pos = found;
            }
            next = found+1;
        }
    } while (found != std::string::npos);

    next = 0;
    do
    {
        found = str.find("seven", next);
        if(found != std::string::npos)
        {
            if (found > last_pos)
            {
            digit = "7";
            last_pos = found;
            }
            next = found+1;
        }
    } while (found != std::string::npos);

    next = 0;
    do
    {
        found = str.find("eight", next);
        if(found != std::string::npos)
        {
            if (found > last_pos)
            {
            digit = "8";
            last_pos = found;
            }
            next = found+1;
        }
    } while (found != std::string::npos);

    next = 0;
    do
    {
        found = str.find("nine", next);
        if(found != std::string::npos)
        {
            if (found > last_pos)
            {
            digit = "9";
            last_pos = found;
            }
            next = found+1;
        }
    } while (found != std::string::npos);

    return digit;
}

int main(int argc, char** argv)
{
    std::fstream file("./input.txt");
    std::string str, first, last;
    int sum = 0;

    while(std::getline(file , str))
    {
        first = FindFirstDigit(str);
        last = FindLastDigit(str);
        sum = sum + stoi(first + last);
    }
    std::cout << sum << std::endl;
    file.close();
}