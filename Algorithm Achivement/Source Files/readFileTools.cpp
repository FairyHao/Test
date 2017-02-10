#pragma once
#include <iostream>
#include "readFileTools.h"
#include <fstream>
#include "stringTools.h"
#include "node.h"
using namespace std;
//tools method
readFileTools::readFileTools()
{
}

readFileTools::~readFileTools()
{
}
bool nodecom(node i, node j) { return (i.pre<j.pre); }

map<string, vector<node*>*>* readFileTools::ReadFileByLine(string fileName)
{
	string s;
	map<string, vector<node*>*> *keyNodeMap = new map<string, vector<node*>*>();
	ifstream infile;
	infile.open(fileName);
	if (!infile)
	{
		cout << "error";
		exit(-1);
	}
	while (infile >> s)
	{
		int x1 = s.find(':');
		string keyvalue = s.substr(1, x1 - 1);
		int x2 = s.find_last_of(':');
		string lengthstr = s.substr(x1 + 1, x2 - x1 - 1);
		int length = stoi(lengthstr, 0, 10);
		int allnodesstartpos = x2 + 1;
		int allnodeslength = s.length() - 2 - x2;
		string allNodes = s.substr(allnodesstartpos, allnodeslength);
		vector<node*>* nodevector = stringTools::splitToNode(allNodes, ';');
		//std::sort(nodevector.begin(), nodevector.end(), nodecom);
		keyNodeMap->emplace(keyvalue, nodevector);
	}
	infile.close();
	return keyNodeMap;
}

