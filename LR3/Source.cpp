#include<iostream>
#include<algorithm>
#include<vector>
#include <string> 
#define INF 9999999

struct Edge
{
	int A, B;
	int size;
};

struct route
{
	std::string put = "";
	int weight = 0;
};

const int SIZE = 7;
int Graph[SIZE][SIZE] = {
  {0, 9, 2, 0, 0, 0, 0},
  {0, 0, 0, 4, 2, 0, 0},
  {0, 6, 0, 0, 28, 10, 0},
  {0, 0, 0, 0, 16, 0, 19},
  {0, 0, 0, 0, 0, 0, 3},
  {0, 0, 0, 0, 15, 0, 25},
  {0, 0, 0, 0, 0, 0, 0}
};

//int Graph[SIZE][SIZE] = {
//  {0, 5, 3, 7, 0},
//  {5, 0, 1, 3, 3},
//  {3, 1, 0, 2, 0},
//  {0, 3, 2, 0, 6},
//  {0, 3, 0, 6, 0}
//};

void printGrath()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            printf("%5d ", Graph[i][j]);
        printf("\n");
    }
}

route DynamicProg(int begin_index, int end_index)
{
    if (begin_index == end_index) 
        return { (std::to_string(begin_index + 1) + " - "), 0};

    route Route, Opt_Route;
    Opt_Route.weight = INF;

    for (int i = 0; i < SIZE; i++) {
        if (Graph[i][end_index] != 0) {
            
            Route = DynamicProg(begin_index, i);
            Route.weight += Graph[i][end_index];
            
            if (Route.weight < Opt_Route.weight) {
                Opt_Route = Route;
            }
        }
    }

    Opt_Route.put += std::to_string(end_index + 1) + " - ";
    return Opt_Route;
}

void getDP_Ans(int begin_index, int end_index)
{
    begin_index--;
    end_index--;

    route Ans = DynamicProg(begin_index, end_index);
    Ans.put.pop_back();
    Ans.put.pop_back();

    std::cout << " DP - Min weight route " << Ans.weight << std::endl
        << " Route is: " << Ans.put;
}

void Dijkstra(int begin_index, int end_index)
{
    Edge  MinRoute[SIZE];
    bool AddEdge[SIZE] = { false }; 
    int temp, CurIndex, min_R;
    begin_index--;
    end_index--;

    for (int i = 0; i < SIZE; i++) {
        MinRoute[i].A = i;
        MinRoute[i].size = INF;
    }
    MinRoute[begin_index].size = 0;

    while (!AddEdge[end_index])
    {
        CurIndex = -1;
        min_R = INF;
        for (int i = 0; i < SIZE; i++)
        {
            if ((AddEdge[i] == false) && (MinRoute[i].size < min_R))
            {
                min_R = MinRoute[i].size;
                CurIndex = i;
            }
        }
        if (CurIndex != -1)
        {
            for (int i = 0; i < SIZE; i++)
            {
                if (Graph[CurIndex][i] > 0)
                {
                    temp = min_R + Graph[CurIndex][i];
                    if (temp < MinRoute[i].size) {
                        MinRoute[i].B = CurIndex;
                        MinRoute[i].size = temp;
                    }
                }
            }
            AddEdge[CurIndex] = true;
        }
    } 
    printf("\n Min weight route to '%d': %3d\n", end_index + 1, MinRoute[end_index].size);

    std::cout << " Route is: ";
    CurIndex = end_index;
    while (CurIndex != begin_index)
    {
        printf("%d - ", CurIndex + 1);
        CurIndex = MinRoute[CurIndex].B;
    }
    std::cout << begin_index + 1 << std::endl;
}

int main() 
{
    Dijkstra(1,6);
    getDP_Ans(1, 6);

	return 0;
}