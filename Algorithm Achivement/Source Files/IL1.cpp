#include "IL.h"
using namespace std;

//这两个参数一定存在祖孙关系，或者相等。
node* descendant(node *v1, node *v2)
{
	if (v2->length>v1->length)
	{
		return v2;
	}
	else
	{
		return v1;
	}
}

//获取两个关键字集合的slca
vector<node*>* get_slca(vector<node*>* s1, vector<node*>* s2)
{
	vector<node*> *result = new vector<node*>();
	node *u=new node("1.1");//长度为1，节点编号为1.

	vector<node*>::iterator it;
	//end
	for (it = (*s1).begin(); it != (*s1).end(); it++)//根据pre从小到大的顺序
	{ 
		node *v = (*it);
		vector<node*> *lrm = v->lrm(s2);
		node *lm = lrm->at(0);//左匹配，因为最靠近的节点，最可能成为slca，越远的节点，lca越可能是祖先
		node *rm = lrm->at(1);//右匹配，道理同上
		node *lca1 = v->lca(lm);//最相近两个点的lca
		node *lca2 = v->lca(rm);
		node *x = descendant(lca1, lca2);//最相近两个点的lca的孙子节点即为slca({v},s2)
		if (u->pre <= x->pre)//根据论文中定理2
		{
			if (!u->Isancestor(x) && !u->equal(x))
			{
				result->push_back(u);
			}
			u = x;//根据定理一，满足x.pre>=u.pre,则x节点一定不是u节点的祖先节点。不是u的祖先节点，则就不是所有节点的祖先节点？为什么？
		}
	}
	result->push_back(u);
	return result;
}
/*如果设置P，每P个元素化成一段。因为后来不设置P，所以这块代码可以注释掉，若要使用P的时候，重新打开。
vector<vector<node*>*>* readNodesToVector(vector<node*>* s1, int P)
{
	vector<vector<node*>*> *result = new vector<vector<node*>*>();
	int i = 1;
	int startPos = 0;
	int s1size = s1->size();
	while (s1size > 0)
	{
		vector<node*> *temp = new vector<node*>();
		while (i <= P && startPos + i - 1<(int)s1->size())
		{
			temp->push_back(s1->at(startPos + i - 1));
			i++;
		}
		result->push_back(temp);
		s1size -= P;
		startPos += P;
		i = 0;
	}
	return result;
}*/
/*
//输出一个集合中的所有元素
void output(vector<node> B)
{
	vector<node>::iterator it1;
	for (it1 = B.begin(); it1 != B.end(); it1++)
	{
		cout << ((node)*it1).tostring() << endl;
	}
}*/
//若P为s1.size(),则根据性质4计算出所有的slca
//被注掉的代码为设P的时候需要使用。
int IL(list<vector<node*>*>* allnodelist)
{
	if (allnodelist->size() <= 1)
	{
		return 0;
	}
	int resultcount = 0;
	//node *v = new node();
	vector<node*> *B = allnodelist->front();
	allnodelist->pop_front();
	//int s1length = s1->size();
	//int P = 2000;//执行效率与P的选择有关。目前感觉P越大，执行时间越短
	//vector<vector<node*>*> *s1vector = readNodesToVector(s1, P);
	list<vector<node*>*>::iterator allnodes_Iter;
	//double allelatime = 0;
	//while (s1length>0)
	//{
		//vector<node*> *B = s1vector->at((s1->size() - s1length) / P);//优化部分。
		for (allnodes_Iter = allnodelist->begin(); allnodes_Iter != allnodelist->end(); allnodes_Iter++)
		{
			B = get_slca(B,*allnodes_Iter);
		}/*
		if (B->size() == 0)
		{
			s1length -= P;
			continue;
			return 0;
		}
		if (!(v->length==0)&& (B->front()->Isancestor(v) || B->front()->equal(v)))
		{
			B->erase(B->begin());
		}
		if (B->size() == 0)
		{
			s1length -= P;
			continue;
			return 0;
		}
		if (!(v->length == 0) && (!(v->Isancestor(B->front()))))
		{
			//cout << v.tostring() << endl;
			resultcount++;
		}
		v = B->back();
		B->pop_back();*/
		resultcount = resultcount + B->size();
		//output(B);
		//B->clear();
		//s1length -= P;
	//}
	//cout << v.tostring() << endl;
	//resultcount++;
	return resultcount;
}
