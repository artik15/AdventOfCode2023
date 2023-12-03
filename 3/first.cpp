#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

const char* digits = "1234567890";


int CheckForNumber(std::string str, size_t beg, size_t end, size_t len)
{
    int ret = 0;
    size_t x1 = 0;
    size_t x2 = 0;
    std::string str_number;
    //printf("CHECK1 %s %d %d %zu %zu\n", str.c_str(), beg, end, x1, x2);

    while (x1 != std::string::npos)
    {
        x1 = str.find_first_of(digits, x2);
        if (x1 == std::string::npos)
        {
            printf("x1 not found %zu %zu\n", x1, x2);
            break;
        }

        x2 = str.find_first_not_of(digits, x1);
        str_number = str.substr(x1, x2 != std::string::npos ? x2-x1 : len-x1);
        printf("CHECK %s %zu %zu\n", str_number.c_str(), x1, x2);

        if (x1 <= end && ((x2-1) >= beg))
        {
            ret += stoi(str_number);
            printf("%s OK\n", str_number.c_str());
        }
        else printf("%s discarded\n", str_number.c_str());
    }
    
    
    

    return ret;
}


int FindPartNumbers(std::string new_str)
{
    /*
        Map structure:
            str[2]
            str[1]
            str[0]
    */
    int ret = 0;
    static std::string str[2];
    static size_t len = 0;
    size_t found = 0;
    str[0] = new_str;
    
    if (str[1].empty()) // gotta load up the buffer
    {
        len = new_str.length(); // Lines are same lenght
    }

    printf("\n%s\n%s\n\n", str[1].c_str(), str[0].c_str());
    
    // previous str
    for(int i = 0; i < 2; i++)
    {
        while(found != std::string::npos)
        {
            found = str[i].find_first_not_of(". 1234567890", found+1);
            
            if(found != std::string::npos)
            {
                printf("found %c at %zu\n", str[i][found], found);
                if (!i) // if previous then check only current
                {
                    ret += CheckForNumber(str[1], found - 1, found + 1, len);
                    printf("RET1= %d\n", ret);
                }
                ret += CheckForNumber(str[0], found - 1, found + 1, len);
                printf("RET2= %d\n", ret);
            }
        }
        found = 0;
    }


    str[1] = str[0];
    return ret;
}



int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("Usage: PartOne input.txt\n");
        return 0;
    }
    
    std::fstream file(argv[1]);
    if(!file.is_open())
    {
        printf("File cannot be opened!\n");
        return 0;
    }

    std::string str;
    int ret = 0;

    while (std::getline(file, str))
    {
        ret += FindPartNumbers(str);
        // if(ret > 1000) break; 
        printf("SUM: %d\n", ret);
    }
    
    printf("TOTAL SUM: %d\n", ret);
    return 0;
}