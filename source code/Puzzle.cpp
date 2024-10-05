#include "Puzzle.h"

Puzzle::Puzzle(char table[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = table[i][j];
            if (board[i][j] == ' ')
            {
                emptyI = i;
                emptyJ = j;
            }
        }
}

bool Puzzle::operator==(const Puzzle& s) const {

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (this->board[i][j] != s.board[i][j])
                return false;

    return true;
}

Puzzle& Puzzle::operator= (Puzzle o)
{
    emptyI = o.emptyI;
    emptyJ = o.emptyJ;
    prev = o.prev;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            this->board[i][j] = o.board[i][j];

    return *this;
}

void Puzzle::swapCells(char &a, char &b)
{
    char temp = a;
    a = b;
    b = temp;
}

bool Puzzle::goUp(Puzzle &n)
{
    if (emptyI - 1 >= 0)
    {
        n = *this;
        swapCells(n.board[emptyI][emptyJ], n.board[emptyI - 1][emptyJ]);
        n.emptyI -= 1;
        n.setPrevious(this);
        return true;
    }
    return false;
}

bool Puzzle::goDown(Puzzle &n)
{
    if (emptyI + 1 <= 2)
    {
        n = *this;
        swapCells(n.board[emptyI][emptyJ], n.board[emptyI + 1][emptyJ]);
        n.emptyI += 1;
        n.setPrevious(this);
        return true;
    }
    return false;
}

bool Puzzle::goLeft(Puzzle &n)
{
    if (emptyJ - 1 >= 0)
    {
        n = *this;
        swapCells(n.board[emptyI][emptyJ], n.board[emptyI][emptyJ - 1]);
        n.emptyJ -= 1;
        n.setPrevious(this);
        return true;
    }
    return false;
}
bool Puzzle::goRight(Puzzle &n)
{
    if (emptyJ + 1 <= 2)
    {
        n = *this;
        swapCells(n.board[emptyI][emptyJ], n.board[emptyI][emptyJ + 1]);
        n.emptyJ += 1;
        n.setPrevious(this);
        return true;
    }
    return false;
}
int Puzzle::getDepth()
{
    int counter = 0;
    Puzzle *p = this;
    while (p->prev!=nullptr)
    {
        p=p->prev;
        counter++;
    }
    return counter;
}

vector <Puzzle *> Puzzle::expand()
{
    vector <Puzzle *> children;
    Puzzle *child;
    child = new Puzzle(*this);
    if (goUp(*child))
        children.push_back(child);
    else
        delete child;
    child = new Puzzle(*this);
    if (goDown(*child))
        children.push_back(child);
    else
        delete child;
    child = new Puzzle(*this);
    if (goLeft(*child))
        children.push_back(child);
    else
        delete child;
    child = new Puzzle(*this);
    if (goRight(*child))
        children.push_back(child);
    else
        delete child;
    return children;
}

int Puzzle::heuristicBFS (Puzzle *goal)
{
    int manhattan = 0;
    int goalI, goalJ;

    for (int i = 0; i < 3; i ++)
        for (int j = 0; j < 3; j++)
        {
            findDistance(board[i][j], goal, goalI, goalJ);
            manhattan += abs(i - goalI) + abs(j - goalJ);
        }

    return manhattan;
}

void Puzzle::findDistance(int value, Puzzle *goal, int &goalI, int &goalJ)
{
    goalI = 0;
    goalJ = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            if (value == goal->board[i][j])
            {
                goalI = i;
                goalJ = j;
            }
        }
}

int Puzzle::heuristicAStar(Puzzle *goal)
{
    return heuristicBFS(goal) + getDepth();
}

void Puzzle::setHvalue(double h)
{
    Hvalue = h;
}

double Puzzle::getHvalue() const
{
    return Hvalue;
}
