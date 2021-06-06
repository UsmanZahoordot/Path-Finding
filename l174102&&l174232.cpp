#include<iostream>
#include<fstream>
#include<conio.h>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
struct State
{
	int x;
	int y;
	int cost;
	State* parent;
	State(int x, int y, int cost)
	{
		parent = nullptr;
		this->x = x;
		this->y = y;
		this->cost = cost;
	}
	bool operator == (State rhs)
	{
		return (this->x == rhs.x && this->y == rhs.y);
	}
};
void printPath(State* p)
{
	if (p == nullptr)
		return;

	printPath(p->parent);
	cout << "(" << p->x << " , " << p->y << ")";
}/*
void getPath(State*p, vector <State*> &s)
{
	while (p->parent != nullptr)
	{
		s.push_back(p);
		p = p->parent;
	}

}*/
int calculateCost(State* p)
{
	int sum = 0;
	for (State* temp = p; temp; temp = temp->parent)
	{
		sum += temp->cost;
	}
	return sum;
}
bool checkState(State current, State goal)
{
	return (current.x == goal.x && current.y == goal.y);
}
void succesorFunction(vector<State*> & ret, State start, State size)
{
	if (start.y < size.y)
		ret.push_back(new State(start.x, start.y + 1, 2));
	if (start.x < size.x)
		ret.push_back(new State(start.x + 1, start.y, 2));
	if (start.x < size.x && start.y < size.y)
		ret.push_back(new State(start.x + 1, start.y + 1, 3));
}
bool BFS(vector<vector<int>> & a, State * start, State * &goal, State * size)
{
	vector<vector<bool> > visited(size->x + 1, vector<bool>(size->y + 1));
	stack<State*>s;
	queue<State*> q;
	vector<State*> r;

	bool flag = false;
	int count = 1;
	for (int i = 0; i < visited.size(); i++)
	{
		for (int j = 0; j < visited[i].size(); j++)
			visited[i][j] = false;
	}
	visited[start->x][start->y] = true;
	q.push(start);
	while (!q.empty())
	{
		succesorFunction(r, *q.front(), *size);
		for (State* i : r)
		{
			i->parent = q.front();
		}
		q.pop();
		for (State* i : r)
		{
			if (!visited[i->x][i->y])
			{
				visited[i->x][i->y] = true;
				if (a[i->x][i->y] != 1)
				{
					q.push(i);
				}
				count++;
				if (checkState(*i, *goal))
				{
					goal = i;
					printPath(i);
					cout << " Cost :" << calculateCost(i) << endl;
					return true;
				}
			}
		}
		r.clear();
	}
	return false;
}

bool DFS(vector<vector<int>>& a, State* start, State* &goal, State* size)
{
	vector<vector<bool> > visited(size->x + 1, vector<bool>(size->y + 1));
	stack<State*> s;
	vector<State*> r;
	for (int i = 0; i < visited.size(); i++)
	{
		for (int j = 0; j < visited[i].size(); j++)
			visited[i][j] = false;
	}
	visited[start->x][start->y] = true;
	s.push(start);
	while (!s.empty())
	{
		succesorFunction(r, *s.top(), *size);
		for (State* i : r)
		{
			i->parent = s.top();
		}

		s.pop();
		for (State* i : r)
		{
			if (!visited[i->x][i->y])
			{
			//	cout << "( " << i->x << " ," << i->y << " ) ";
				visited[i->x][i->y] = true;
				if (a[i->x][i->y] != 1)
				{
					s.push(i);
				}
				if (checkState(*i, *goal))
				{
					goal = i;
					//printPath(i);
					cout << " Cost :" << calculateCost(i) << endl;
					return true;
				}
			}
		}
		r.clear();
	}
	return false;
}

bool IDFS(vector<vector<int>>& a, State* start, State* &goal, State* size,int u)
{
	int san = 0;

	vector<vector<bool> > visited(size->x + 1, vector<bool>(size->y + 1));
	stack<State*> s;
	vector<State*> r;
	for (int i = 0; i < visited.size(); i++)
	{
		for (int j = 0; j < visited[i].size(); j++)
			visited[i][j] = false;
	}
	visited[start->x][start->y] = true;
	s.push(start);
	while (!s.empty())
	{
		if (san >3*u)
		{
			return 0;
		}
		succesorFunction(r, *s.top(), *size);
		for (State* i : r)
		{
			san++;
			i->parent = s.top();
		}

		s.pop();
		for (State* i : r)
		{
			if (!visited[i->x][i->y])
			{
					cout << "( " << i->x << " ," << i->y << " ) ";
				visited[i->x][i->y] = true;
				if (a[i->x][i->y] != 1)
				{
					s.push(i);
				}
				if (checkState(*i, *goal))
				{
					//printPath(i);
					cout << " Cost :" << calculateCost(i) << endl;
					return true;
				}
			}
		}
		r.clear();
	}
	return false;
}
bool IDS(vector<vector<int>>& a, State* start, State* goal, State* size, int max_depth)
{
	for (int i = 0; i <= max_depth; i++)
	{
		cout << "depth" << i;
		if (IDFS(a, start, goal, size, i) == true)
			return true;
	}
	return false;
}
void printPath(stack<State*>s)
{
	int cost = 0;
	while (!s.empty())
	{
		cout << " (" << s.top()->x << "," << s.top()->y << ")";
		cost = cost + s.top()->cost;
		s.pop();
	}
		cout << " Cost : " << cost<<endl;
}
bool IDFS(vector<vector<int>>& a, State* start, State* goal, State* size, int maxDepth, stack<State *> &s)
{
	if (*start == *goal)
		return true;
	if (maxDepth <= 0)
		return false;
	vector<State*> r;
	succesorFunction(r, *start, *size);
	for (State* i : r)
	{
			if (IDFS(a, i, goal, size, maxDepth - 1, s))
				s.push(i);
		//cout << "( " << i->x << " ," << i->y << ")";
		return true;
	}
}

void printMaze(int row, int col,vector<vector<int> > &maze)
{
	for (int i = row - 1; i >= 0; i--) {
		for (int j = 0; j <= col - 1; j++) {
			if (maze[i][j] == 9)
				cout << "*" << " ";
			else
				cout << maze[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl<<endl;
}
int main()
{
	ifstream fin;
	fin.open("grid.txt");
	if (fin.is_open())
	{
		int row, col;
		fin >> row >> col;
		int xStart, yStart, xGoal, yGoal;
		fin >> xStart >> yStart >> xGoal >> yGoal;

		State* start = new State(xStart, yStart, 0);
		State* goal = new State(xGoal, yGoal, 0);
		State* size = new State(row - 1, col - 1, 0);


		vector<vector<int> > maze(row, vector<int>(col));
		vector<vector<int> > path_maze(row, vector<int>(col));


		for (int i = 0; i <= row - 1; i++) {
			for (int j = 0; j <= col - 1; j++) {
				fin >> maze[i][j];
			}
		}
		cout << "------------------MAZE----------------------------"<<endl;
		printMaze(row, col, maze);
		cout << "-----------------------BFS path------------------------------";
		if (!BFS(maze, start, goal, size))
			cout << "Not found";
		else
		{
			path_maze = maze;
			State * p = goal;
			while (p->parent != nullptr)
			{
				path_maze[p->x][p->y] = 9;
				p = p->parent;
			}
			printMaze(row, col, path_maze);
		
		}
		cout << "----------------------------DFS path-------------------------------------------";
		if (!DFS(maze, start, goal, size))
			cout << "Not found";
		else
		{
			path_maze = maze;
			State * p = goal;
			while (p->parent != nullptr)
			{
				path_maze[p->x][p->y] = 9;
				p = p->parent;
			}
			printMaze(row, col, path_maze);
			
		}
		cout << "----------------------------IDFS path-------------------------------------------";

		stack<State*> s;
		if (!IDFS(maze, start, goal, size, 20, s))
			cout << "Not found";
		else
		{

			printPath(s);
			path_maze = maze;

				while (!s.empty())
				{

					path_maze[s.top()->x][s.top()->y] = 9;
					s.pop();
				}


			printMaze(row, col, path_maze);
		}
		delete start;
		delete goal;
		delete size;
	}
	else
		cout << "Error Opening file";
	system("PAUSE");
	return 0;
}