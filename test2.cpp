#include <vector> 
#include <list>
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cmath>

using namespace std;

class Graph
{
public:
	void initGraph()
	{
		_storage.resize(length);
		_inversed.resize(length);
		ifstream fin("1.txt");
		string line;
		stringstream stream;
		while(getline(fin, line))
		{
			long int vertex, adjacent;
			stream.clear();
			stream << line;
			stream >> vertex;
			while(stream >> adjacent)
			{
				_inversed[vertex-1].push_back(adjacent - 1);
				_storage[adjacent-1].push_back(vertex - 1);
			}
	//		length ++;
		}
	}
	
	void get_inversed()
	{
		_storage = _inversed;		
	}

	void print()
	{
		for(long int i = 0; i < length; i++)
		{
			cout << i << " ";
			list<long int> :: iterator iter;
			for( iter = _storage[i].begin();  iter != _storage[i].end(); iter++)
			{
				cout << *iter << " ";
			}
			cout << endl;	
		}
	}

	
	long int get_numbers()
	{
		return length;
	}
	
public:
	vector< list<long int> > _storage;
	vector< list<long int> > _inversed;
	long int length = 6400;

};

class DepthFirstSearch
{
public:
	void DFS_Init(Graph graph)
	{
		length = graph.get_numbers();
		marked.resize(length);
		leader.resize(length);
	}
	void marked_Init()
	{		
		for(long int i = 0; i < length; i++)
		{
			marked[i] = false;
		}
	}	
	void DFS_Loop( Graph graph, long int flag)
	{
		marked_Init();			
		if(flag == 1)				
		{
			time = 0;
			
			for(long int i = length - 1; i >= 0; i--)
			{
				if(!marked[i])
				{
	//				s = i;
					DFS(graph, i, flag);
				}
			}
		} else {
			while(!f.empty())		
			{
				long int temp = f.top();
				f.pop();
				if(!marked[temp])
				{
					s = temp;
					DFS(graph, temp, flag);
				}								
			}
		}
	
	}
	
	void DFS(Graph graph, long int i, long int flag)
	{
		marked[i] = true;
		if(flag == 1)			
		{
			list<long int>::iterator iter;
			for(iter = graph._storage[i].begin(); iter != graph._storage[i].end(); iter++)
			{
				long int temp = *iter;
				if(!marked[temp])
				{
					DFS(graph, temp, flag);
				}
			}
			time++;
			f.push(i);
		}
		if(flag == 2)
		{
			leader[i] = s;
			list<long int>::iterator iter;
			for(iter = graph._storage[i].begin(); iter != graph._storage[i].end(); iter++)	
			{
				
				long int temp = *iter;
				if(!marked[temp])
				{
					DFS(graph, temp, flag);
				}
			}
		}
	}
	
	long int  max(vector<long int> &_sto)
	{
		long int max = 0;
		long int index;
		int flag = 0;
		for(long int i = 0; i < length; i++)	
		{
			if(max < _sto[i])		
			{
				max = _sto[i];
				index = i;
				flag = 1;
			}
		}
		if(flag) 
		{
			_sto[index] = 0;
		}
		return max;
	}

	void fiveMax()
	{
		vector<long int >_sto;
		_sto.resize(length);
		for(long int i = 0; i < length; i++)
		{
			_sto[leader[i]] ++;
		}
		for(int i = 0; i < 5; i++)
		{
			cout << max(_sto) << endl;
		}
		
	}
	
private:
	long int time;
	long int s;
	stack<long int> f;
	long int length;
	vector<long int> leader;
	vector<bool> marked;
};

int main()
{
	clock_t start, end;
	start = clock();
	Graph graph;
	graph.initGraph();
	DepthFirstSearch search;
	search.DFS_Init(graph);
	search.DFS_Loop(graph, 1);
	graph.get_inversed();
	search.DFS_Loop(graph, 2);
	search.fiveMax();
	end = clock();
	cout << "running time:" << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}




