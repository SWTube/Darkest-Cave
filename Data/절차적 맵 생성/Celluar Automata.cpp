#include <vector>
#include <iostream>
#include <cstdlib>

std::vector<std::vector<int> > initialiseMap(int width, int height);//function initialisation, returns a 2d array, takes a 2d array
std::vector<std::vector<int> > simStep(std::vector<std::vector<int> > oldMap, int width, int height); //"game of life" style simulation
int countAliveNeighbours(std::vector<std::vector<int> > map, int x, int y); //checks how many of the squares around a certain square are walls
int main()
{
    //allows you to change size of map
    int mapXSize = 100;
    int mapYSize = 45;

    std::vector<std::vector<int> > map = initialiseMap(mapXSize, mapYSize); //setting up the map grid
    int simSteps = 4;
    for (int k = 0; k <= simSteps; k++) //run sim a few times to smooth out map
    {
        map = simStep(map, mapXSize, mapYSize);
    }
    //prints out ascii representation
    for (int y = 0; y < mapYSize; y++)
    {
        for (int x = 0; x < mapXSize; x++)
        {
            if (map[y][x] == 1)
            {
                std::cout << "X";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    return 0;
}
std::vector<std::vector<int> > initialiseMap(int width, int height) //returns a 2d array of bools
{
    int chanceToStartAlive = 41; //percentage of being a wall tile at start
    std::vector<std::vector<int> > map; //create map to return
    map.resize(height, std::vector<int>(width, false));

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++) //initialising values here
        {
            if (rand() % 100 + 1 < chanceToStartAlive) //it has a chance of being a wall or not
            {
                map[h][w] = 1;
            }
            else
            {
                map[h][w] = 0;
            }
        }
    }
    //return our new map
    return map;
}
std::vector<std::vector<int> > simStep(std::vector<std::vector<int> > oldMap, int width, int height) //this is the magic "game of life" thingy, google it
{
    std::vector<std::vector<int> > newMap;
    newMap.resize(height, std::vector<int>(width));

    int birthLimit = 4;
    int deathLimit = 3;

    //iterates through every tile in the map and decides if needs to be born, die, or remain unchanged
    for (int h = 0; h < oldMap.size(); h++)
    {
        for (int w = 0; w < oldMap[0].size(); w++)
        {
            int newVal = countAliveNeighbours(oldMap, w, h);
            if (oldMap[h][w])
            {
                if (newVal < deathLimit)
                {
                    newMap[h][w] = 0;
                }
                else
                {
                    newMap[h][w] = 1;
                }
            }
            else
            {
                if (newVal > birthLimit)
                {
                    newMap[h][w] = 1;
                }
                else
                {
                    newMap[h][w] = 0;
                }
            }
        }
    }
    return newMap;
}
//counts the number of "alive" cells around the target cell, given a current map and a target x and y coord
int countAliveNeighbours(std::vector<std::vector<int> > map, int x, int y)
{
    int count = 0;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            int neighbour_x = x + i;
            int neighbour_y = y + j;

            if (i == 0 && j == 0)
            {
                //do nothing as its our target cell
            }
            //if out of bounds, obviously don't check it, but add one anyway as it counts as an alive neighbour
            else if (neighbour_x < 0 || neighbour_y < 0 || neighbour_x >= map[0].size() || neighbour_y >= map.size())
            {
                count += 1;
            }
            else if (map[neighbour_y][neighbour_x] == 1)
            {
                count += 1;
            }
        }
    }
    return count;
}