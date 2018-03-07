#ifndef AROYA_DECISION_TREE
#define AROYA_DECISION_TREE

#define persent_border 0.9

struct node {
	bool type;//true��ans��false��data
	int dataIndex;//��¼�ǵڼ��е�����
	int data;//��¼���ݵ�����
	int ans;//���õ�������������¼�������
	node *above;//�ϲ�֦��
	vector<node>below;
	node();
};

class Tree {
private:
	node root;
	void cutNode(node&, const vector<vector<int>>&, const vector<int>&);
public:
	//ֱ�Ӵ�����,�����������ݡ�flag���ݡ��б���
	Tree(const vector<vector<int>>&, const vector<int>&,
		int(*)(const vector<vector<int>>&, const vector<int>&));
	//����ans
	int getAns(const vector<int>&);
	vector<int> getGroupAns(const vector<vector<int>>&);

	//���֦
	void cut(const vector<vector<int>>&,const vector<int>&);
	
};

#endif