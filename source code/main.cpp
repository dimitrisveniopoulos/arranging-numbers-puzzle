#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <chrono>
#include "Puzzle.h"
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

Puzzle *DFS(Puzzle *initial, Puzzle *goal, long long &examined, long long &mem)
{
    stack<Puzzle *> agenda;
    unordered_map <unsigned long,Puzzle *> closed;

    agenda.push(initial);
    examined=0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        Puzzle *s = agenda.top();
        agenda.pop();
        if (closed.count(s->getKey())==0)
        {
            examined++;
            if (*s==*goal)
                return s;
            pair<unsigned long,Puzzle *> k (s->getKey(), s);
            closed.insert(k);
            vector<Puzzle *> children =s->expand();
            for (unsigned int i=0;i<children.size();i++)
                if (closed.count(children[i]->getKey())==0)
                    agenda.push(children[i]);
        }
    }
    return nullptr;
}

Puzzle *BFS(Puzzle *initial, Puzzle *goal, long long &examined, long long &mem)
{
    queue<Puzzle *> agenda;
    unordered_map <unsigned long,Puzzle *> closed;

    agenda.push(initial);
    examined=0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        Puzzle *s = agenda.front();
        agenda.pop();
        if (closed.count(s->getKey())==0)
        {
            examined++;
            if (*s==*goal)
                return s;
            pair<unsigned long,Puzzle *> k (s->getKey(), s);
            closed.insert(k);
            vector<Puzzle *> children =s->expand();
            for (unsigned int i=0;i<children.size();i++)
                if (closed.count(children[i]->getKey())==0)
                    agenda.push(children[i]);
        }
    }
    return nullptr;
}

Puzzle *BestFS(Puzzle *initial, Puzzle *goal, long long &examined, long long &mem)
{
    priority_queue <Puzzle*, vector<Puzzle *>, myComparator > agenda;
    unordered_map <unsigned long,Puzzle*> closed;
    agenda.push(initial);
    examined = 0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        Puzzle *s = agenda.top();
        agenda.pop();

        if (closed.count(s->getKey())==0)
        {
            examined++;
            if (*s==*goal)
                return s;
            pair<unsigned long,Puzzle*> k (s->getKey(), s);
            closed.insert(k);
            vector<Puzzle *> children = s->expand();
            for (unsigned int i=0;i<children.size();i++)
            {
                if (closed.count(children[i]->getKey())==0)
                {
                    children.at(i)->setHvalue(children.at(i)->heuristicBFS(goal));
                    agenda.push(children.at(i));
                }
            }
        }
    }
    return nullptr;
}

Puzzle *AStar(Puzzle *initial, Puzzle *goal, long long &examined, long long &mem)
{
    priority_queue <Puzzle*, vector<Puzzle *>, myComparator > agenda;
    unordered_map <unsigned long,Puzzle*> closed;
    agenda.push(initial);
    examined = 0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        Puzzle *s = agenda.top();
        agenda.pop();

        if (closed.count(s->getKey())==0)
        {
            examined++;
            if (*s==*goal)
                return s;
            pair<unsigned long,Puzzle*> k (s->getKey(), s);
            closed.insert(k);
            vector<Puzzle *> children = s->expand();
            for (unsigned int i=0;i<children.size();i++)
            {
                if (closed.count(children[i]->getKey())==0)
                {
                    children.at(i)->setHvalue(children.at(i)->heuristicAStar(goal));
                    agenda.push(children.at(i));
                }
            }
        }
    }
    return nullptr;
}

int main()
{
    long long mem,examined;

    char initialBoard[3][3] = {'3', '6', ' ','1', '4', '2', '7', '5', '8'};
    Puzzle *initial = new Puzzle(initialBoard);

    char goalBoard[3][3] = {'1', '2', '3','4', '5', '6', '7', '8', ' '};
    Puzzle *goal = new Puzzle(goalBoard);

    double DFS_time, BFS_time, BestFS_time, AStar_time;
    chrono::time_point<chrono::steady_clock> start,end;

    cout<<endl<<"DFS: ";
    start=chrono::steady_clock::now();
    Puzzle *bsol= DFS(initial,goal,examined,mem);
    end=chrono::steady_clock::now();
    DFS_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000000.0;
    if (bsol!=nullptr)
    {
        cout << "Depth = " << bsol->getDepth() << ", Memory: " << mem << ", Examined: " << examined <<
             ", Time Elapsed: " << DFS_time << " ms" << endl;
    }
    else
        cout<<"Problem unsolvable"<<endl;

    cout<<endl<<"BFS: ";
    start=chrono::steady_clock::now();
    bsol= BFS(initial,goal,examined,mem);
    end=chrono::steady_clock::now();
    BFS_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000000.0;
    if (bsol!=nullptr)
    {
        cout << "Depth = " << bsol->getDepth() << ", Memory: " << mem << ", Examined: " << examined <<
             ", Time Elapsed: " << BFS_time << " ms" << endl;
    }
    else
        cout<<"Problem unsolvable"<<endl;

    cout<<endl<<"BestFS: ";
    start=chrono::steady_clock::now();
    bsol= BestFS(initial,goal,examined,mem);
    end=chrono::steady_clock::now();
    BestFS_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000000.0;
    if (bsol!=nullptr)
    {
        cout << "Depth = " << bsol->getDepth() << ", Memory: " << mem << ", Examined: " << examined <<
             ", Time Elapsed: " << BestFS_time << " ms" << endl;
    }
    else
        cout<<"Problem unsolvable"<<endl;

    cout<<endl<<"A*: ";
    start=chrono::steady_clock::now();
    bsol= AStar(initial,goal,examined,mem);
    end=chrono::steady_clock::now();
    AStar_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000000.0;
    if (bsol!=nullptr)
    {
        cout << "Depth = " << bsol->getDepth() << ", Memory: " << mem << ", Examined: " << examined <<
             ", Time Elapsed: " << AStar_time << " ms" << endl;
    }
    else
        cout<<"Problem unsolvable"<<endl;

    return 0;

}