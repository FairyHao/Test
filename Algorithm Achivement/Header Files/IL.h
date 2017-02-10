#pragma once
#include <string>
#include <vector>
#include <list>
#include <map>
#include "Node.h"
#include <iostream>
#include <windows.h>
using namespace std;

#define QUERYCOUNT 32

vector<node*>* get_slca(vector<node*>* s1, vector<node*>* s2);
int IL(list<vector<node*>*>* allnodelist);
vector<vector<node*>*>* readNodesToVector(vector<node*>* s1, int P);
node* descendant(node *v1,node *v2);