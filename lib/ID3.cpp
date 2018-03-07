#include<vector>
#include<cmath>
#include<iostream>
using namespace std;

#include"ID3.h"

//����һ������vector<int>�е�index
static int inline findInVector(const vector<int>&, const int&);


//����ѡ����е�index
int ID3(const vector<vector<int>>& data, const vector<int>& flag) {

	//��ͳ�� �У��������� �У�������
	const int columns = data[0].size();
	const int rows = data.size();
	
	const int zero = 0;
	vector<int>value;
	vector<int>count;
	vector<int>positive;
	vector<int>negative;
	vector<double>entropy;
	int index;
	double thisEntropy;
	//����������
	for (int i = 0; i < columns; i++) {
		//��ʼ��
		value.clear();
		count.clear();
		positive.clear();
		negative.clear();
		thisEntropy = 0;
		//����
		for (int j = 0; j < rows; j++) {
			//������ɢֵֵ
			index = findInVector(value, data[j][i]);
			//û���򴴽�
			if (index < 0) {
				value.push_back(data[j][i]);
				count.push_back(zero);
				positive.push_back(zero);
				negative.push_back(zero);
				index = value.size() - 1;
			}
			//��ɢֵ����
			count[index]++;
			//��ɢֵ��Ӧ״̬ͳ��
			if (flag[j] > 0)positive[index]++;
			else negative[index]++;
		}
		//����������
		index = value.size();
		for (int j = 0; j < index; j++) {
			/*H(D|A) = sum all A
				P(A=a)*
				H(D|A=a)
				*/
			thisEntropy += (
				double(count[j]) / double(rows)*
				(
					- double(positive[j]) / double(count[j])*log2((double(positive[j])+0.01) / double(count[j]))
					- double(negative[j]) / double(count[j])*log2((double(negative[j])+0.01) / double(count[j]))
				)
			);//+0.01 ��ֹlog2(0/count)���½������nan
		}
		entropy.push_back(thisEntropy);
	}
	//���������ؼ�����ϣ�Ѱ����������С����ѡ�����Ϣ�������
	double min = entropy[0];
	index = 0;
	for (int i = 1; i < columns; i++) {
		if (entropy[i] < min) {
			index = i;
			min = entropy[i];
		}
	}
	return index;
}

static int inline findInVector(const vector<int>& thisVector, const int& num) {
	const int border = thisVector.size();
	for (int i = 0; i < border; i++) {
		if (thisVector[i] == num)return i;
	}
	return -1;
}