#ifndef AROYA_READER
#define AROYA_READER

class Reader {//֮ǰLab�ļ���ȡ����
public:
	Reader(const char*);
	//~Reader();
	vector<vector<int>>data;
	vector<int>flag;
	int columns, rows;
};

#endif