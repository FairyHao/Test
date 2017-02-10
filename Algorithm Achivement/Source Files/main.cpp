/*主函数，主要功能如下：1.读文件，将倒叙表读成map<关键字，vector<节点>>的形式
2.读取测试关键字,读成list<vector<节点>>的形式
3.调用IL算法*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <list>
#include <map>
#include <windows.h>
#include "stringTools.h"
#include "IL.h"
#include "readFileTools.h"
#include "Node.h"
using namespace std;

#define QUERYCOUNT 40

int main()
{
	//测试关键字，每一行代表关键字的集合，即寻找每一行关键字的SLCA。
	//xmark开头的文件的关键字
	string strKWQuery[QUERYCOUNT][7] = { //the length of each element in the first column denotes the # of keywords in a query
		//{ "6","  ","David","XML","","","" }
		{ "6","  ","villages","hooks","","","" },                        //11111111  1
		{ "6","   ","baboon","patients","arizona","","" },          //            2
		{ "6","    ","cabbage","tissue","shocks","baboon","" },          //            3
		{ "6","     ","shocks","necklace","cognition","cabbage","tissue" },  //            4

		{ "6","  ","female","order","","","" },                       //22222222    5
		{ "6","   ","privacy","check","male","","" }  ,               //            6
		{ "6","    ","takano","province","school","gender","" },            //            7
		{ "6","     ","school","gender","education","takano","province" },  //            8

		{ "6","  ","bold","increase","","","" },                           //33333333    9
		{ "6","   ","date","listitem","emph","","" },                       //            10
		{ "6","    ","incategory","text","bidder","date","" },            //            11
		{ "6","     ","bidder","date","keyword","incategory","text" },    //            12

		{ "6","  ","text","tissue","","","" },      //1,3                                13
		{ "6","  ","takano","province","","","" },   //2,2                                14
		{ "6","  ","incategory","cabbage","","","" }, //1,3                            15
		{ "6","  ","check","bidder","","","" },       //2,3                            16
		{ "6","  ","baboon","patients","","","" },   //1,1                            17

		{ "6","   ","tissue","shocks","order","","" },        //1,1,2                    18
		{ "6","   ","province","bold","increase","","" },        //233                    19
		{ "6","   ","cabbage","male","female","","" },         //122                    20
		{ "6","   ","listitem","emph","arizona","","" },        //133                    21
		{ "6","   ","patients","school","gender","","" },        //122                    22

		{ "6","    ","patients","school","gender","text","" },        //1223            23
		{ "6","    ","bold","increase","hooks","takano","" },            //1233            24
		{ "6","    ","male","female","keyword","incategory","" },        //2233            25
		{ "6","    ","emph","arizona","villages","education","" },    //1123            26
		{ "6","    ","check","bidder","date","baboon","" },           //1233            27

		{ "6","     ","school","gender","time","baboon","patients" },             //11223    28
		{ "6","     ","tissue","shocks","order","province","bold" },           //11223    29
		{ "6","     ","female","keyword","incategory","cabbage","male" },         //12233    30
		{ "6","     ","arizona","villages","education","listitem","emph" },   //11233    31
		{ "6","     ","bidder","date","necklace","cognition","check" }  //11233    32
	};
	//dblp文件开头的关键字
	/*string strKWQuery[QUERYCOUNT][7] = { //the length of each element in the first column denotes the # of keywords in a query
		{ "6","  ","article","book","","","" },                            //11111111  1
		{ "6","   ","article","","algorithm","","" },                //            2
		{ "6","    ","article","data","","","" },            //            3
		{ "6","     ","article","database","","","" },//            4
		{ "6","  ","article","xml","","","" },  //22222222    5

		{ "6","   ","year","2001","","","" }, //            6
		{ "6","   ","article","book","mining","","" },                //            7     
		{ "6","    ","article","algorithm","2001","","" },            //            8
		{ "6","     ","article","data","mining","","" },//33333333    9
		{ "6","  ","article","data","xml","","" }, //            10 


		{ "6","  ","article","book","","","" },                            //11111111  1
		{ "6","   ","article","","algorithm","","" },                //            2
		{ "6","    ","article","data","","","" },            //            3
		{ "6","     ","article","database","","","" },//            4
		{ "6","  ","article","xml","","","" },  //22222222    5

		{ "6","   ","year","2001","","","" }, //            6
		{ "6","   ","article","book","mining","","" },                //            7     
		{ "6","    ","article","algorithm","2001","","" },            //            8
		{ "6","     ","article","data","mining","","" },//33333333    9
		{ "6","  ","article","data","xml","","" } ,//      10


		{ "6","  ","article","book","","","" },                            //11111111  1
		{ "6","   ","article","","algorithm","","" },                //            2
		{ "6","    ","article","data","","","" },            //            3
		{ "6","     ","article","database","","","" },//            4
		{ "6","  ","article","xml","","","" },  //22222222    5

		{ "6","   ","year","2001","","","" }, //            6
		{ "6","   ","article","book","mining","","" },                //            7     
		{ "6","    ","article","algorithm","2001","","" },            //            8
		{ "6","     ","article","data","mining","","" },//33333333    9
		{ "6","  ","article","data","xml","","" }, //      10

		{ "6","  ","article","book","","","" },                            //11111111  1
		{ "6","   ","article","","algorithm","","" },                //            2
		{ "6","    ","article","data","","","" },            //            3
		{ "6","     ","article","database","","","" },//            4
		{ "6","  ","article","xml","","","" },  //22222222    5

		{ "6","   ","year","2001","","","" }, //            6
		{ "6","   ","article","book","mining","","" },                //            7     
		{ "6","    ","article","algorithm","2001","","" },            //            8
		{ "6","     ","article","data","mining","","" },//33333333    9
		{ "6","  ","article","data","xml","","" } //      
	};*/
	//读取文件start
	DWORD start1, end1;//DWORD is 32 bit unsigned long;即范围从0-4294967295，这个是windows提供的，需include window.h
	start1 = GetTickCount();//获取自系统开启之后过去的毫秒数，return DWORD，每４９.７天归０
	map<string, vector<node*>*> *m1 = readFileTools::ReadFileByLine("xmark500.txt");//读取文件，并直接返回Map形式。
	end1 = GetTickCount();//获取结束毫秒                                                            
	double elapsedtime1 = double(end1 - start1);//相减即获得运行时间
	cout << "read file time:" << elapsedtime1 << endl;
	//读取文件end

	double alltime = 0;
	for (int i=0;i<40;i++)
	{
		list<vector<node*>*> *allnodelist = new list<vector<node*>*>();
		string *keyList = strKWQuery[i];//获取关键字
		keyList++;
		int k = 0;
		int min = 1000000000;
		while(k++<6)//每一行的关键字封装为一个list
		{ 
			if (stringTools::trim(*keyList).empty())
			{
				keyList++;
				continue;
			}
			auto result = (*m1).find(*keyList);//map find 关键字
			if (result==(*m1).end())//未找到的情况下
			{
				keyList++;
				continue;
			}
			vector<node*> *nodeslist = result->second;//获取value。获取key用first
			//性能优化部分 start。将最小size的关键字节点放在第一个位置。
			if ((*nodeslist).size() < min)
			{
				(*allnodelist).push_front(nodeslist);
				min = (*nodeslist).size();
			}
			else
			{
				(*allnodelist).push_back(nodeslist);
			}
			//性能优化部分end
			keyList++;
		}
		//若长度大于2，则将所有的关键字按照节点多少排序，数量越少，排在前面。
		if (allnodelist->size()>2)
		{
			list<vector<node*>*> *allnodelisttemp = new list<vector<node*>*>();
			allnodelisttemp->push_back(allnodelist->front());//第一个已经是最小的了。
			int mint = 100000000000000;
			list<vector<node*>*>::iterator allnodes_Iter;
			vector<node*> *x = new vector<node*>();
			int j = allnodelist->size() - 1;
			while (j-->=1)
			{
				//每次循环找到节点数量最少的关键字。
				for (allnodes_Iter = ++allnodelist->begin(); allnodes_Iter != allnodelist->end(); allnodes_Iter++)
				{
					if ((*allnodes_Iter)->size() < mint)
					{
						mint = (*allnodes_Iter)->size();
						x = *allnodes_Iter;
					}
				}
				allnodelisttemp->push_back(x);//将关键字放在temp中。
				allnodelist->remove(x);//要将已经找到的关键字序列移除
				mint = 1000000000000000;
			}
			allnodelist = allnodelisttemp;//拍好序的list赋值给allnodelist。引用传送
		}
		//调用IL算法start，并计算时间
		DWORD start, end;
		start = GetTickCount();
		//cout << i<<"th " << "result count:" << IL(allnodelist) << endl;
		//cout << IL(allnodelist) << endl;
		IL(allnodelist);
		end = GetTickCount();
		double elapsedtime = double(end - start);
		//cout << "query time:" << elapsedtime << endl;
		cout << elapsedtime << endl;
		alltime += elapsedtime;
		//调用IL算法end
	}
	cout << alltime << endl;
	while (1)
    {
    }
	return 0;
}
