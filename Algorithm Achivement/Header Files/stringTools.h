#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "Node.h"
using namespace std;
//tools method
class stringTools
{
public:
	stringTools();
	~stringTools();
	static vector<node*>* splitToNode(string s, char delim);//将关键字列表转换成vector<Node>的形式
	static string trim(string s);//去掉空格
private:
};


