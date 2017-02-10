#include <string>
#include <vector>
#include <sstream>
#include "stringTools.h"
#include "Node.h"
using namespace std;
//tools method

stringTools::stringTools()
{
}

stringTools::~stringTools()
{
}
vector<node*>* stringTools::splitToNode(string s, char delim)
{
	vector<node*> *elems = new vector<node*>();
	stringstream ss;
	ss.str(s);
	std::string item;
	while (getline(ss, item, delim)) {
		node *x = new node(item);
		elems->push_back(x);
	}
	return elems;
}
string stringTools::trim(string s)
{
	int length = s.length();
	for (int i = s.length() - 1; i >= 0; i--)
	{
		if (s.at(i) == ' ')
		{
			s.erase(i, 1);
		}
	}
	return s;
}