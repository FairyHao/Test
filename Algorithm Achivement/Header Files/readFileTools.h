#pragma once
#include <map>
#include <string>
#include <vector>
#include "node.h"
#include <algorithm>

using namespace std;

class readFileTools
{
public:
	readFileTools();
	~readFileTools();
	static map<string,vector<node*>*>* ReadFileByLine(string filename);//读成关键字和节点列表对应的形式
private:
}; 