#include<vector>
#include<cmath>
using namespace std;
#include"Gini.h"

//����һ������vector<int>�е�index
static int inline findInVector(const vector<int>&, const int&);

int Gini(const vector<vector<int>>& data, const vector<int>& flag) {
	//��ͳ�� �У��������� �У�������
	const int columns = data[0].size();
	const int rows = data.size();

	const int zero = 0;
	vector<int>value;
	vector<int>count;
	vector<int>positive;
	vector<int>negative;
	vector<double>gini;
	int index;
	double thisGini;
	//����������
	for (int i = 0; i < columns; i++) {
		//��ʼ��
		value.clear();
		count.clear();
		positive.clear();
		negative.clear();
		thisGini = 0;
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

		//����Giniָ��
		index = value.size();
		for (int j = 0; j < index; j++) {
			/*H(D|A) = sum all
			���ָ���*(
			1 - P(True|A)^2 - P(False|A)^2
			)*/
			thisGini += (
				double(count[j]) / double(rows)*
				(
					1.0 - pow(double(positive[j]) / double(count[j]), 2)
					- pow(double(negative[j]) / double(count[j]), 2)
				));
		}
		gini.push_back(thisGini);
	}
	//ѡ����С��Giniָ������ȷ����Ϣ����
	double min = gini[0];
	index = 0;
	for (int i = 1; i < columns; i++) {
		if (gini[i] < min) {
			index = i;
			min = gini[i];
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