//
// Created by dimit on 05/04/2021.
//

#ifndef PUZZLE_PUZZLE_H
#define PUZZLE_PUZZLE_H

#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Puzzle
{
public:
    Puzzle(char [3][3]);
    bool goUp(Puzzle &n);
    bool goDown(Puzzle &n);
    bool goLeft(Puzzle &n);
    bool goRight(Puzzle &n);
    void setPrevious (Puzzle *p) { prev=p;}
    Puzzle& operator= (Puzzle o);
    bool operator==(const Puzzle& o) const ;
    static void swapCells(char&, char&);
    int getDepth();
    vector <Puzzle *> expand();
    void setHvalue(double);
    double getHvalue() const;
    int heuristicBFS (Puzzle *);
    int heuristicAStar(Puzzle *);
    static void findDistance(int , Puzzle *, int &, int &);
    Puzzle *getPrevious()const {return prev;}
    unsigned long getKey()
    {
        unsigned long k = 0;
        int p = 1;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                if (board [i][j] != ' ')
                    k += (board[i][j] - 48) * p;
                p *= 10;
            }
        return k;
    }

private:
    char board[3][3];
    int emptyI; //stores row index of the empty cell
    int emptyJ; //stores column index of the empty cell
    Puzzle *prev;
    double Hvalue;
};

class myComparator
{
public:
    int operator() (Puzzle *p1 , Puzzle *p2) const
    {
        return p1->getHvalue()>p2->getHvalue();
    }
};


#endif //PUZZLE_PUZZLE_H
