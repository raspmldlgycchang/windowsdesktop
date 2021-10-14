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
	HandleUsers* mp_user1;//�ϴ��� user1�� ���ؼ�
	unsigned int m_max_user_cnt;
	HandleUsers** mp_users;//�������� user
public:
	Dim2_dynamic_GYC(unsigned int a_max_count = 8, unsigned int a_max_user_cnt = 5) {
		m_max_user_cnt = a_max_user_cnt;
		m_max_count = a_max_count;
		pp = new char* [m_max_count];
		for (unsigned int i = 0; i < m_max_count; i++) {
			*(pp + i) = new char[m_max_len];
		}
		mp_user1 = new HandleUsers[m_max_count];
		memset(mp_user1, 0, sizeof(HandleUsers) * m_max_count);
		m_gen_value = 1;

		mp_users = new HandleUsers * [m_max_user_cnt];
		for (unsigned int j = 0; j < m_max_user_cnt; j++) {
			for (unsigned int i = 0; i < m_max_count; i++) {
				mp_users[j] = new HandleUsers[m_max_count];
			}
		}
		/*memset(mp_users, 0, sizeof(HandleUsers*) * m_max_user_cnt);
		for (unsigned int i = 0; i < m_max_count; i++) {
			memset(mp_users[i], 0, sizeof(HandleUsers) * m_max_count);
		}*/
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
		/*HandleUsers* p_handle = mp_user1;
		for (unsigned int i = 0; i < m_max_count; i++) {
			if (p_handle->h != NULL) {
				delete[] p_handle->p_string;
			}
			p_handle++;
			cout << i << "��° ����ü ��� p_string �����޸����� �� ��ü�Ҹ�Ϸ�!" << endl;
		}
		delete[] mp_user1;
		cout << "�ڵ鰴ü������ mp_user1 �����޸����� �� ��ü�Ҹ�Ϸ�!" << endl;
		*/
		/*
		HandleUsers** p_handle = mp_users;
		unsigned int i;
		for (unsigned int j = 0; j < m_max_user_cnt; j++) {
			for (i = 0; i < m_max_count; i++) {
				if ((*p_handle)->h!=NULL) {//�ּ�1����
					cout << "mp_users[" << j << "][" << i << "]";
					printf("�� �ּ� %p ", &mp_users[j][i]);
					delete[] p_handle[j]->p_string;//�ּ�2����_���1
					//delete[] p_handle[j][i].p_string;//���2
				}
				p_handle[j]++;//�ּ�3����_���1 �Ѹ��� user���� ���ڿ��Ѱ���m_max_count��ŭ �������� 1��������ü���� �����ϳ� �޸�ũ�⸸ŭ ����
				cout << "�����޸� ���� �� ��ü �Ҹ� �Ϸ�" << endl;
			}
			delete[] mp_users[j];
			cout << "�ڵ鰴ü������ mp_users[" << j << "]"<< "�����޸����� �� ��ü�Ҹ�Ϸ�!" << endl;

		}
		delete[] mp_users;
		cout << "�ڵ鰴ü������ mp_users �����޸����� �� ��ü�Ҹ�Ϸ�!" << endl;
		*/

		HandleUsers* p_handle = mp_users[0];
		//printf("sizeof(HandleUsers)= %ld\n", sizeof(HandleUsers));//������� �� = int�� + char*(�ּҴ� ������ 4����Ʈ�Դϴ�) = 8����Ʈ
		/*for (unsigned int j = 0; j < m_max_user_cnt; j++) {
			for (unsigned int i = 0; i < m_max_count; i++) {
				printf("%p = &mp_users[%d][%d]\n", &mp_users[j][i], j,i);
				printf("%p = p_handle\n", p_handle);
				printf("----------------------------------------------\n");
				p_handle++;

			}
		}
		printf("========================================\n");*/
		for (unsigned int j = 0; j < m_max_user_cnt; j++) {
			for (unsigned int i = 0; i < m_max_count; i++) {
				if (p_handle->h != 0) {//�ּ�1����
					cout << "mp_users[" << j << "][" << i << "]";
					printf("�� �ּ� %p ", &mp_users[j][i]);
					delete[] p_handle->p_string;//�ּ�2����_���1
				}
				cout << "����ü ��� p_string �����޸� ���� �� ��ü �Ҹ� �Ϸ�" << endl;
				p_handle++;//�ּ�3����_���1 �Ѹ��� user���� ���ڿ��Ѱ���m_max_count��ŭ �������� ����ü���� ũ�⸸ŭ ����
				printf("%p :�����޸������ϰ� ++���������Ų p_handle������=&mp_user[%d][%d]\n", p_handle, j,i+1);
			}
			delete[] mp_users[j];
			cout << "�ڵ鰴ü������ 1���� ����ü ������=�����͹迭=mp_users[" << j << "]" << "�����޸����� �� ��ü�Ҹ�Ϸ�!" << endl;

		}
		delete[] mp_users;
		cout << "�ڵ鰴ü������ 2��������ü������=1���� ����ü�����ͺ����� 1�����迭 mp_users �����޸����� �� ��ü�Ҹ�Ϸ�!" << endl;
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
			//���ڿ��� ����� ����� ���� Ȯ�εǾ��ٸ� 2��������ü�����ͺ����� 1��������ü�����ͺ������� �����Ѵ�
			SetStringDim2Ptr(len, i);
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
	void SetStringDim2Ptr(int len, int index) {
		printf("%p\n", mp_users[0]);
		HandleUsers* p_handle_Dim2 = mp_users[0];
		p_handle_Dim2->p_string = new char[len];
		memcpy(p_handle_Dim2->p_string, pp[index], len);
		cout << p_handle_Dim2->p_string << ": p_handle_Dim2->p_string" << endl;
		p_handle_Dim2->h++;
	}
};
class childHandleUsers : public HandleUsers {

};
int main(void)
{
	Dim2_dynamic_GYC str_list_user1;
	HANDLE h_str_user1_1 = str_list_user1.SetString("��ο�");
	cout << h_str_user1_1 << ": HANDLE h_str_user1_1" << endl;

	HANDLE h_str_user1_2 = str_list_user1.SetString("���̸�������,");
	cout << h_str_user1_2 << ": HANDLE h_str_user1_2" << endl;

	HANDLE h_str_user1_3 = str_list_user1.SetString(",�̰��,");
	cout << h_str_user1_3 << ": HANDLE h_str_user1_3" << endl;

	HANDLE h_str_user1_4 = str_list_user1.SetString("��°�������,");
	cout << h_str_user1_4 << ": HANDLE h_str_user1_4" << endl;

	HANDLE h_str_user1_5 = str_list_user1.SetString("�����������̰�,");
	cout << h_str_user1_5 << ": HANDLE h_str_user1_5" << endl;

	HANDLE h_str_user1_6 = str_list_user1.SetString("�����ϴ�������");
	cout << h_str_user1_6 << ": HANDLE h_str_user1_6" << endl;

	HANDLE h_str_user1_7 = str_list_user1.SetString("�����Դϴ�");
	cout << h_str_user1_7 << ": HANDLE h_str_user1_7" << endl;



	int select_num;
	unsigned int genValue = str_list_user1.getGenValue();
	unsigned int i;
	//char* p;
	char* buf = new char[2];
	while (1) {
		cout << "���° ���ڿ��� ����Ͻðھ��? (8 or 9 For Exit): " << endl;
		cin >> select_num;
		rewind(stdin);
		if (select_num == 8 || select_num == 9)	break;
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
		cout << "���° ���ڿ��� �����Ͻðھ��? (8 or 9 For Exit): " << endl;
		cin >> select_num;
		rewind(stdin);
		if (select_num == 8 || select_num == 9)	break;

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