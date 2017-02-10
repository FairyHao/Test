#pragma once
#include <map>
#include <string>
#include <vector>

using namespace std;
//每个节点的封装类
class node
{
public:
	node();
	~node();
	node(string v);
	int length;//长度
	int pre;//前序深度优先遍历序列中，节点的位置
	vector<int> nodeName;//节点的序列。最开始使用的是string来表示1.3.2,但是string处理起来太慢，所以选择了vector<int>,即存储为1 3 2 
	node* lca(node* v);//寻找两个节点的共同祖先
	bool equal(node* v);//两个节点是否相等（根据Pre是否相等）
	vector<node*>* lrm(vector<node*>* s2);//找到此节点在s2中的左右匹配
	bool Isancestor(node *v2);//此节点是否是v2的祖先节点
	string tostring();//为了输出使用，将一个Node类型的节点输出为3.1.12.3;
private:
};