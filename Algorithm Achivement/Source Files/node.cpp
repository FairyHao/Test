#include "Node.h"
#include "stringTools.h"
node::node()
{}

node::~node()
{
}

node::node(string v)
{
	if (v.empty())
	{
		return;
	}
	//获取pre
	int lastPointPos1 = v.find_last_of(".");
	this->pre = stoi(v.substr(lastPointPos1 + 1, v.length() - lastPointPos1 - 1));
	//获取length
	int x1 = v.find_first_of(".");
	this->length = stoi(v.substr(0, x1));
	//获取node
	string v1Node = v.substr(x1 + 1, v.length() - x1 - 1);
	int i = 1;
	int potPosition = 0;
	vector<int> nodeNametemp;
	while (i++ <= length)
	{
		v1Node.push_back('.');
		int tempPos = v1Node.find('.', potPosition);
		string temps1 = v1Node.substr(potPosition, tempPos - potPosition);
		int temp = stoi(temps1);
		nodeNametemp.push_back(temp);
		potPosition = tempPos + 1;
	}
	this->nodeName = nodeNametemp;
}

node* node::lca(node *v)
{
	node *x = new node();
	int length = this->length > v->length ? v->length : this->length;
	for (int i = 0;i<length;i++)
	{
		int x1 = (this->nodeName).at(i);
		int x2 = v->nodeName.at(i);
		if (x1 == x2)
		{
			x->nodeName.push_back(x1);
			x->length++;
		}
		else
		{
			break;
		}
	}
	if (x->length!=0)
	{
		x->pre = x->nodeName.back();
	}
	return x;
}
bool node::equal(node* v)
{
	return this->pre == v->pre;
}
//寻找左右匹配，使用的折半查找
vector<node*>* node::lrm(vector<node*>* s2)
{
	vector<node*> *nodes = new vector<node*>();//第一个元素是左匹配，第二个元素是右匹配
	if (this->pre < s2->at(0)->pre)
	{
		node *x = new node();
		(*nodes).push_back(x);
		(*nodes).push_back(s2->at(0));
	}else if (this->pre == s2->at(0)->pre)
	{
		(*nodes).push_back(s2->at(0));
		(*nodes).push_back(s2->at(0));
	}else if (this->pre > s2->at(s2->size() - 1)->pre)
	{
		node *x = new node();
		(*nodes).push_back(s2->at(s2->size() - 1));
		(*nodes).push_back(x);
	}
	else if (this->pre == s2->at(s2->size() - 1)->pre)
	{
		(*nodes).push_back(s2->at(s2->size() - 1));
		(*nodes).push_back(s2->at(s2->size() - 1));
	}
	else
	{
		int low = 0;
		int high = s2->size() - 1;
		int mid;
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (this->pre < s2->at(mid)->pre)
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
		}
		(*nodes).push_back(s2->at(high));
		(*nodes).push_back(s2->at(low));
	}
	return nodes;
}
//V1 is ancestor of v2,return true;else return false;
bool node::Isancestor(node* v2)
{
	if (this->length==0 || v2->length == 0)
	{
		return false;
	}
	node *lca = this->lca(v2);

	if (this->equal(lca) && !lca->equal(v2))
	{
		return true;
	}
	return false;
}

string node::tostring()
{
	string result;
	vector<int>::iterator it;
	for (it = this->nodeName.begin(); it != this->nodeName.end(); it++)
	{
		result += to_string(*it) + '.';
		
	}
	return result;
}