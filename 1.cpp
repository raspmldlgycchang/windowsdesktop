#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#define MAX_LEN 16
using namespace std;
typedef unsigned int HANDLE;
struct HandleUsers {
	HANDLE h;
	char* p_string;
};
class Dim2_dynamic_GYC {
private:
	char** pp;
	unsigned int m_max_count, m_max_len = MAX_LEN, m_gen_value;
	HandleUsers* mp_user1;//�ϴ��� user1���� ���ؼ�
public:
	Dim2_dynamic_GYC(unsigned int a_max_count = 8) {
		m_max_count = a_max_count;
		pp = new char* [m_max_count];
		for (unsigned int i = 0; i < m_max_count; i++) {
			*(pp + i) = new char[m_max_len];
		}
		mp_user1 = new HandleUsers[m_max_count];
		memset(mp_user1, 0, sizeof(HandleUsers) * m_max_count);
		m_gen_value = 1;
	}
	~Dim2_dynamic_GYC()
	{
		char pp_tmp[8][MAX_LEN] = { {0,}, };
		CopyPtrToStr(pp_tmp);
		char(*p)[MAX_LEN] = pp_tmp;
		printf("%p : *(p + 0) + 0\n", *(p + 0) + 0);
		printf("%p : *(p + 1) + 0\n", *(p + 1) + 0);
		printf("%p : *(p + 2) + 0\n", *(p + 2) + 0);
		printf("%p : *(p + 3) + 0\n", *(p + 3) + 0);
		printf("%p : *(p + 4) + 0\n", *(p + 4) + 0);
		printf("%p : *(p + 5) + 0\n", *(p + 5) + 0);
		printf("%p : *(p + 6) + 0\n", *(p + 6) + 0);
		printf("%p : *(p + m_max_count-1) + 0\n", *(p + m_max_count - 1) + 0);

		for (unsigned int i = 0; i < m_max_count; i++) {
			//if (*(*(p + i) + 0) + 0 != NULL) {//�̰� char (*p)[MAX_LEN]���� �迭�������� ��Ȳ�̶�� �����޸��Ҵ��� ���� ��
			//�̷��� �Ʒ��ּ�ó�� ��� �Ѵ�
			{	//delete[] (*(p + i) + 0);
				delete[] pp[i];
				cout << "pp[" << i << "] �����޸����� �� ��ü�Ҹ�Ϸ�!" << endl;
			}
		}
		delete[] pp;
		cout << "pp �����޸����� �� ��ü�Ҹ�Ϸ�!" << endl;
		HandleUsers* p_handle = mp_user1;
		for (unsigned int i = 0; i < m_max_count; i++) {
			if (p_handle->h != NULL) {
				delete[] p_handle->p_string;
			}
			p_handle++;
			cout << i << "��° ����ü ��� p_string �����޸����� �� ��ü�Ҹ�Ϸ�!" << endl;
		}
		delete[] mp_user1;
		cout << "�ڵ鰴ü������ mp_user1 �����޸����� �� ��ü�Ҹ�Ϸ�!" << endl;
	}
	HANDLE SetString(const char* ap_string)
	{
		int len = strlen(ap_string) + 1;
		char* p;
		p = new char[len];
		strcpy_s(p, len, ap_string);
		cout << p << ": p" << endl;
		//strncpy_s(p, len, ap_string, len - 1);
		//p[len] = 0;
		//len = strlen(ap_string);
		//memcpy(p, ap_string, len);
		//p[len] = 0;

		unsigned int i;
		HandleUsers* p_handle = mp_user1;
		for (i = 0; i < m_max_count; i++) {
			if (p_handle->h == 0)	break;
			else
			{
				p_handle++;
			}
		}

		if (i < m_max_count) {
			p_handle->p_string = new char[len];
			strncpy_s(p_handle->p_string, len, p, len);
			cout << p_handle->p_string << ": p_handle->p_string" << endl;
			memcpy(pp[i], p_handle->p_string, len);
			cout << pp[i] << ": pp[" << i << "]" << endl;
			p_handle->h = m_gen_value++;
			return p_handle->h;
		}
		return 0xFFFFFFFF;
	}
	void CopyPtrToStr(char buf[8][MAX_LEN])
	{
		HandleUsers* p_handle = mp_user1;
		for (unsigned int i = 0; i < m_max_count; i++) {
			if (p_handle->h != 0) {
				int len = MAX_LEN;
				strcpy_s(buf[i], len, pp[i]);
				printf("%p : buf[%d]\n", buf[i], i);
				printf("%s : pp[%d]\n", pp[i], i);
				cout << buf[i] << ": buf[ " << i << " ]" << endl;
				p_handle++;
			}
			else {
				return;
			}
		}
	}
	void PrintData(HANDLE h_str)
	{
		HandleUsers* p_handle = mp_user1;
		unsigned int i;
		for (i = 0; i < m_max_count; i++) {
			if (p_handle->h == h_str) {
				cout << "�����Ͻ� ���ڿ��� ���~" << ": " << p_handle->p_string << endl;
			}
			else p_handle++;
		}
		cout << "��ġ�ϴ� �޸��ּҰ� �����ϴ�!" << endl;
	}
	void DeleteData(HANDLE h_str)
	{
		HandleUsers* p_handle = mp_user1;
		unsigned int i;
		for (i = 0; i < m_max_count; i++) {
			if (p_handle->h == h_str) {
				cout << p_handle->p_string << "�����ϰڴϴ�!" << endl;
				delete[] p_handle->p_string;
				p_handle->h = 0;
				return;
			}
			p_handle++;
		}
		cout << "��ġ�ϴ� �޸��ּҰ� �����ϴ�!" << endl;
	}
	unsigned int getGenValue() {
		return m_gen_value;
	}
};
int main(void)
{
	Dim2_dynamic_GYC str_list_user1;
	HANDLE h_str_user1_1 = str_list_user1.SetString("�ȳ��ϼ���");
	cout << h_str_user1_1 << ": HANDLE h_str_user1_1" << endl;

	HANDLE h_str_user1_2 = str_list_user1.SetString(" ����");
	cout << h_str_user1_2 << ": HANDLE h_str_user1_2" << endl;

	HANDLE h_str_user1_3 = str_list_user1.SetString(" gycchang");
	cout << h_str_user1_3 << ": HANDLE h_str_user1_3" << endl;

	HANDLE h_str_user1_4 = str_list_user1.SetString(" �Դϴ�");
	cout << h_str_user1_4 << ": HANDLE h_str_user1_4" << endl;

	int select_num;
	unsigned int genValue = str_list_user1.getGenValue();
	unsigned int i;
	char* p;
	char* buf = new char[2];
	while (1) {
		cout << "���° ���ڿ��� ����Ͻðھ��? (8 or 7 For Exit): " << endl;
		cin >> select_num;
		rewind(stdin);
		if (select_num == 8 || select_num == 7)	break;
		//p = _itoa(select_num, buf, 10);

		//if (strcmp(p, "8") || strcmp(p, "7")) {
		//	cout << "��°��Ӳ���~" << endl;
		//	break;
		//}
		for (i = 0; i < genValue; i++) {
			if (select_num == i)	break;
			else continue;
		}
		if (i < genValue)	str_list_user1.PrintData(i);
		else
		{
			cout << "��ġ�ϴ� �ڵ鰪�� �����ϴ�!" << endl;
		}
		fflush(stdout);
	}
	while (1) {
		cout << "���° ���ڿ��� �����Ͻðھ��? (8 or 7 For Exit): " << endl;
		cin >> select_num;
		rewind(stdin);
		if (select_num == 8 || select_num == 7)	break;

		//p = _itoa(select_num, buf, 10);

		//if (strcmp(p, "8") || strcmp(p, "7")) {
		//	cout << "��������!" << endl;
		//	break;
		//}

		for (i = 0; i < genValue; i++) {
			if (select_num == i)	break;
			else continue;
		}
		if (i < genValue)	str_list_user1.DeleteData(i);
		else
		{
			cout << "��ġ�ϴ� �ڵ鰪�� �����ϴ�!" << endl;
		}
	}


	return 0;
}