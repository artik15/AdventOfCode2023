#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

typedef struct game
{
    int id;
    int red_balls;
    int green_balls;
    int blue_balls;
} game_t;

int FindBallsInColor(std::string str, std::string color)
{
    int balls = -1;
    size_t found = str.find(color);
    if(found != std::string::npos)
    {
        // printf("CL %s\n", str.substr(found - 3, 3).c_str());
        balls = stoi(str.substr(found - 3, 3));
    }
    return balls;
}


game_t FindNeededBalls(std::string str)
{
    std::stringstream ss(str);
    game_t game = {};
    std::string temp_str;
    int temp;

    if(std::getline(ss, temp_str, ':'))
    {
        game.id = std::stoi(temp_str.substr(5, 3));
        // printf("%s %d\n", temp_str.c_str(), game.id);
    }

    while (std::getline(ss, temp_str, ';'))
    {
        // printf("STR %s\n", temp_str.c_str());
        temp = FindBallsInColor(temp_str, "red");
        if(temp > game.red_balls) game.red_balls = temp;
        temp = FindBallsInColor(temp_str, "green");
        if(temp > game.green_balls) game.green_balls = temp;
        temp = FindBallsInColor(temp_str, "blue");
        if(temp > game.blue_balls) game.blue_balls = temp; 
        // printf("Game %d Red %d Green %d Blue %d\n", game.id, game.red_balls, game.green_balls, game.blue_balls);
    }

    return game;
}




/*
    Call: PartOn input.txt R G B
        R - number of red balls
        G - number of green balls
        B - number of blue balls
*/

int main(int argc, char** argv)
{
    if(argc < 5)
    {
        printf("Usage: PartOn input.txt R G B\nR - number of red balls\nG - number of green balls\nB - number of blue balls\n");
        return 0;
    }
    
    std::fstream file(argv[1]);
    if(!file.is_open())
    {
        printf("File cannot be opened!\n");
        return 0;
    }

    std::string str;
    int id_sum, max_red, max_green, max_blue;
    game_t game;

    max_red = atoi(argv[2]);
    max_green = atoi(argv[3]);
    max_blue = atoi(argv[4]);

    while (std::getline(file, str))
    {
        game = FindNeededBalls(str);
        // printf("Game %d Red %d Green %d Blue %d\n", game.id, game.red_balls, game.green_balls, game.blue_balls);
        if (game.red_balls <= max_red &&
             game.green_balls <= max_green &&
             game.blue_balls <= max_blue)
        {
            id_sum += game.id;
        }
    }
    
    printf("Sum of game IDs: %d\n", id_sum);
    return 0;
}