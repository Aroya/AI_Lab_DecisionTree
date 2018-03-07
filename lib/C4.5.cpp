#include<vector>
using namespace std;

#include"C4.5.h"

//����һ������vector<int>�е�index
static int inline findInVector(const vector<int>&, const int&);

int C45(const vector<vector<int>>& data, const vector<int>& flag) {
	//���ȼ������ݼ�����
	double setEntropy;
	int posi = 0, nega = 0;
	for (int i = 0; i < flag.size(); i++) {
		if (flag[i] > 0)posi++;
		else nega++;
	}
	setEntropy = -double(posi) / double(posi + nega)*log2(double(posi) / double(posi + nega))
		- double(nega) / double(posi + nega)*log2(double(nega) / double(posi + nega));

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
	double thisEntropy, thisEntropy_;
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
					- double(positive[j]) / double(count[j])*log2((double(positive[j]) + 0.01) / double(count[j]))
					- double(negative[j]) / double(count[j])*log2((double(negative[j]) + 0.01) / double(count[j]))
					)
				);//+0.01 ��ֹlog2(0/count)���½������nan
		}
		
		//��������ֵ����
		thisEntropy_ = 0;
		for (int j = 0; j < index; j++) {
			thisEntropy_ -= (
				double(count[j]) / double(rows)*log2(double(count[j]) / double(rows))
			);
		}
		//�õ���Ϣ������
		entropy.push_back((setEntropy - thisEntropy)/thisEntropy_);
	}
	//ѡ��������Ϣ������
	double max = entropy[0];
	index = 0;
	for (int i = 1; i < columns; i++) {
		if (entropy[i] > max) {
			index = i;
			max = entropy[i];
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