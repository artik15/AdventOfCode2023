#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>


/*NOT COMPLETED*/

const char* digits = "1234567890";

typedef struct gear {
    size_t beg;
    size_t end;
    unsigned long gear_ratio;
    unsigned int number[2];
    int gears;
    bool last_line;
} gears_t;


gears_t CheckForNumber(std::string str, size_t len, gears_t gear)
{
    int ret = 0;
    size_t x1 = 0;
    size_t x2 = 0;
    std::string str_number;
    printf("CHECK1 %s %zu %zu %zu %zu\n", str.c_str(), gear.beg, gear.end, x1, x2);

    while (x1 != std::string::npos)
    {
        x1 = str.find_first_of(digits, x2);
        if (x1 == std::string::npos)
        {
            //printf("x1 not found %zu %zu\n", x1, x2);
            break;
        }

        x2 = str.find_first_not_of(digits, x1);
        str_number = str.substr(x1, x2 != std::string::npos ? x2-x1 : len-x1);
        //printf("CHECK %s %zu %zu\n", str_number.c_str(), x1, x2);

        if (x1 <= gear.end && ((x2-1) >= gear.beg))
        {
            if(gear.gears < 2)
            {
                gear.number[gear.gears] = stoi(str_number);
                gear.gear_ratio *= stoi(str_number);
                gear.gears++;
                printf("%s OK gears: %d\n", str_number.c_str(), gear.gears);
            }
        }
        // else printf("%s discarded\n", str_number.c_str());
    }

    return gear;
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
    size_t vec_size = 0;
    str[0] = new_str;
    gears_t gear = {0,0,1, {0,0},0,false};
    static std::vector<gears_t> gears;

    if (str[1].empty()) 
    {
        len = new_str.length(); // Lines are same lenght
    }

    printf("\n%s\n%s\n\n", str[1].c_str(), str[0].c_str());
    
    // previous str
    while(found != std::string::npos)
    {
        found = str[0].find_first_of('*', found);
        
        if(found != std::string::npos)
        {
            printf("found %c at %zu\n", str[0][found], found);
            gear.beg = found - 1;
            gear.end = found + 1;
            gears.insert(gears.begin(), gear);
            gear = {0,0,1, {0,0},0,false};
            found++;
        }
        
    }

    vec_size = gears.size();
    
    printf("VECSIZE %zu\n", vec_size);

    while(vec_size > 0)
    {
        gear = gears[gears.size()-1];
        printf("BEG: %zu\n", gear.beg);
        gears.pop_back();

        if(gear.last_line)
        {
            gear = CheckForNumber(str[0], len, gear);
            if (gear.gears == 2)
            {
                printf("FOUND ACTUAL GEARS %d %d\n", gear.number[0], gear.number[1]);
                ret += gear.gear_ratio;
            }
        }
        else
        {
            gear = CheckForNumber(str[0], len, gear);
            gear = CheckForNumber(str[1], len, gear);
            gear.last_line = true;
            gears.insert(gears.begin(), gear);
        }
        vec_size--;
    }

    vec_size = gears.size();
    printf("VECSIZE AFTER %zu\n", vec_size);

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
    int line = 0;

    while (std::getline(file, str))
    {
        ret += FindPartNumbers(str);
        // if(line > 6) break; 
        
        printf("SUM: %d\n", ret);
        line++;
    }
    
    printf("TOTAL SUM: %d\n", ret);
    return 0;
}