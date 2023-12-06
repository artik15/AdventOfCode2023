#include <stdio.h>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <cmath>


const char *digits = "1234567890";


std::vector<int> GetNumbers(std::string str)
{
    std::vector<int> ret_vec;
    size_t x1 = 0;
    size_t x2 = 0;
    int test = 0;
    
    while (x1 != std::string::npos)
    {
        x1 = str.find_first_of(digits, x2);
        x2 = str.find_first_of(' ', x1);
        if(x1 != std::string::npos)
        {
            test = stoi(str.substr(x1, x2 != std::string::npos ? x2-x1 : str.length()-x1));
            ret_vec.push_back(test);
            //printf("Found %d\n", test);
        }
    }
    

    return ret_vec; 
}

unsigned int GetTotalPoints(std::vector<int> win_numbers, std::vector<int> picked_numbers)
{
    unsigned int result = 0;
    size_t win_vec_size = win_numbers.size();
    size_t pick_vec_size = picked_numbers.size();

    for(size_t i = 0; i < win_vec_size; i++)
    {
        for(size_t j = 0; j < pick_vec_size; j++)
        {
            //printf("%d vs %d\n", win_numbers[i], picked_numbers[j]);
            if(win_numbers[i] == picked_numbers[j])
            {
                result++;
                //printf("%d win\n", picked_numbers[j]);
                continue;
            }
        }

    }
    return (unsigned int)pow(2, result-1);
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

    std::vector<int> win_numbers, picked_numbers;
    std::string str, win_str, pick_str;
    size_t x1 = 0;
    size_t x2 = 0;
    int ret = 0;

    while (std::getline(file, str))
    {
        x1 = str.find_first_of(':');
        x2 = str.find_first_of('|');

        win_str = str.substr(x1+1, x2-x1-1);
        pick_str = str.substr(x2+1, str.length()-x2-1);
        
        win_numbers = GetNumbers(win_str);
        picked_numbers = GetNumbers(pick_str);

        ret += GetTotalPoints(win_numbers, picked_numbers);
        // if(ret > 1000) break; 
        // printf("WIN: %s PICK: %s\n", win_str.c_str(), pick_str.c_str());
    }
    
    printf("TOTAL SUM: %d\n", ret);
    return 0;
}