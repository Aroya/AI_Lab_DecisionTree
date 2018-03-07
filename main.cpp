#include<vector>
#include<iostream>
using namespace std;

#include"lib\Reader.h"
#include"lib\ID3.h"
#include"lib\C4.5.h"
#include"lib\Gini.h"
#include"lib\Tree.h"
#include"lib\Divider.h"
#include"lib\AnsStream.h"

//����ܵĿ���
#define ENABLE_ID3
#define ENABLE_C45
#define ENABLE_Gini
#define ENABLE_Test
//#define TREE_ONLY

int main() {
	//�ָ�ѵ��������֤����
	//Divider("origin.csv");

	Reader trainReader("train.csv");
#ifndef TREE_ONLY
	Reader valiReader("validation.csv");
	Reader testReader("test.csv");
#endif
	
#ifdef ENABLE_ID3//ʹ��ID3������
	Tree treeID3(trainReader.data, trainReader.flag, ID3);
#ifndef TREE_ONLY
	cout << "ID3��֦ǰ:\n";
	AnsStream ansStreamID3_(treeID3.getGroupAns(valiReader.data));
	ansStreamID3_.test(valiReader.flag);
	
	cout << "ID3��֦��:\n";
	treeID3.cut(valiReader.data, valiReader.flag);
	AnsStream ansStreamID3(treeID3.getGroupAns(valiReader.data));
	ansStreamID3.test(valiReader.flag);
#endif // !TREE_ONLY
	
#endif // ENABLE_ID3


#ifdef ENABLE_C45//ʹ��C4.5������
	Tree treeC45(trainReader.data, trainReader.flag, C45);
#ifndef TREE_ONLY
	cout << "C4.5��֦ǰ:\n";
	AnsStream ansStreamC45_(treeC45.getGroupAns(valiReader.data));
	ansStreamC45_.test(valiReader.flag);
	
	cout << "C4.5��֦��:\n";
	treeC45.cut(valiReader.data, valiReader.flag);
	AnsStream ansStreamC45(treeC45.getGroupAns(valiReader.data));
	ansStreamC45.test(valiReader.flag);
#endif // !TREE_ONLY
	
#endif //ENABLE_C45

#ifdef ENABLE_Gini//ʹ��Giniָ��������
	Tree treeGini(trainReader.data, trainReader.flag, Gini);
#ifndef TREE_ONLY
	cout << "Gini��֦ǰ:\n";
	AnsStream ansStreamGini_(treeGini.getGroupAns(valiReader.data));
	ansStreamGini_.test(valiReader.flag);
	
	cout << "Gini��֦��:\n";
	treeGini.cut(valiReader.data, valiReader.flag);
	AnsStream ansStreamGini(treeGini.getGroupAns(valiReader.data));
	ansStreamGini.test(valiReader.flag);
#endif // !TREE_ONLY

#endif // ENABLE_GINI

	
	
#ifdef ENABLE_Test//test
	AnsStream ansID3(treeID3.getGroupAns(testReader.data));//ID3
	ansID3.writeFile("15352014_Caizheng.txt");
#endif
	system("pause");
	return 0;
}