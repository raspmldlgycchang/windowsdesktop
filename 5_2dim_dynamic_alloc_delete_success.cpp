#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
typedef unsigned int HANDLE;
struct HandleData {
	HANDLE h;
	char* p_string;
};
void printInfo(HandleData** mp_users);
class HandleManager {
private:
	HandleData** mp_users;
	unsigned int m_len, m_max_count, m_max_user_cnt, m_gen_value;
public:
	HandleManager(unsigned int a_max_user_cnt, unsigned int a_max_count);
	~HandleManager();
	HANDLE SetString(const char* ap_string);
	void printString(HANDLE h_str);
};
HandleManager::HandleManager(unsigned int a_max_user_cnt, unsigned int a_max_count) {
	m_gen_value = 1;
	m_max_count = a_max_count, m_max_user_cnt = a_max_user_cnt;
	mp_users = new HandleData * [m_max_user_cnt];
	for (unsigned int j = 0; j < m_max_user_cnt; j++){
		for (unsigned int i = 0; i < m_max_count; i++) {
			mp_users[j] = new HandleData[m_max_count];

		}
	}
	for (unsigned int j = 0; j < m_max_user_cnt; j++) {
			memset(mp_users[j], 0, sizeof(HandleData) * m_max_count);
	}


	printInfo(mp_users);
}
void printInfo(HandleData** mp_users)
{
	unsigned int m_max_count = 2, m_max_user_cnt = 2;
	for (unsigned int j = 0; j < m_max_user_cnt; j++) {
		for (unsigned int i = 0; i < m_max_count; i++) {
			cout << "mp_users["<< j << "][" << i<< "]" << mp_users[j][i].h<< endl;
		}
		cout << endl;
	}
}
HandleManager::~HandleManager() {
	HandleData* p_handle;
	for (unsigned int j = 0; j < m_max_user_cnt; j++) {
		p_handle = &mp_users[j][0];
		for (unsigned int i = 0; i < m_max_count; i++) {
			if (p_handle->h) {
				delete[] p_handle->p_string;
				p_handle++;//sizeof(HandleData)만큼 증가
			}
		}
		delete[] mp_users[j];
	}
	delete[] mp_users;
}
HANDLE HandleManager::SetString(const char* ap_string)
{
	int len = strlen(ap_string) + 1;
	unsigned int j=0;
	HandleData* p_handle = mp_users[0];
	for (; j < m_max_user_cnt; j++) {
		unsigned int i;
		p_handle = &mp_users[j][0];
		for (i = 0; i < m_max_count; i++) {
			if (p_handle->h == 0)	break;
			//p_handle++;means 포인터자료형만큼 증가(sizeof(HandleData)만큼 증가)
			else
			{
				p_handle++;
			}
		}
		cout << "i : " << i << endl;
		if (i < m_max_count) {
			p_handle->p_string = new char[len];
			memcpy(p_handle->p_string, ap_string, len);
			cout << p_handle->p_string << ": p_handle->p_string" << endl;
			p_handle->h = m_gen_value++;
			return p_handle->h;
		}
		else if(j<m_max_user_cnt){
			p_handle = &mp_users[j++][0];
			for (i = 0; i < m_max_count; i++) {
				if (p_handle->h == 0)	break;
				//p_handle++;means 포인터자료형만큼 증가(sizeof(HandleData)만큼 증가)
				else
				{
					p_handle++;
				}
			}
			if (i < m_max_count) {
				p_handle->p_string = new char[len];
				memcpy(p_handle->p_string, ap_string, len);
				cout << p_handle->p_string << ": p_handle->p_string" << endl;
				p_handle->h = m_gen_value++;
				return p_handle->h;
			}
			else {
				p_handle = mp_users[j++];
				cout << "아직 증가할 사용자 수가 남았습니다" << endl;
				for (i = 0; i < m_max_count; i++) {
					if (p_handle->h == 0)	break;
					//p_handle++;means 포인터자료형만큼 증가(sizeof(HandleData)만큼 증가)
					else
					{
						p_handle++;
					}
				}
				cout << "i : " << i << endl;
				if (i < m_max_count) {
					p_handle->p_string = new char[len];
					memcpy(p_handle->p_string, ap_string, len);
					cout << p_handle->p_string << ": p_handle->p_string" << endl;
					p_handle->h = m_gen_value++;
					return p_handle->h;
				}
			}
		}
		else
		{
			cout << "정해주신 사용자수가 넘었습니다" << endl;
			return 0xFFFFFFFF;
		}
	}

}
void HandleManager::printString(HANDLE h_str)
{
	HandleData* p_handle = &mp_users[0][0];
	unsigned int i;
	for (unsigned int j = 0; j < m_max_user_cnt; j++) {
		p_handle = &mp_users[j][0];
		for (i = 0; i < m_max_user_cnt; i++) {
			if (p_handle->h == h_str) {
				cout << "일치하는 메모리주소를 찾았고 반환합니다" << endl;
				cout << p_handle->p_string << ": printString함수 요청하신 문자열입니다" << endl;
				return;
			}
			else if (i < m_max_count)
			{
				p_handle++;
			}
		}
		
	}
	cout << "핸들값과 일치하는 메모리 주소가 없습니다" << endl;
}
int main(void)
{
	const int MAX_LEN = 240;
	int max_user_cnt=2, max_count=2;
	const char* ap_string = "우리동동이가젤조아하는고옹";
	HandleManager handle_user_lists(max_user_cnt, max_count);
	HANDLE h_user1_str1=handle_user_lists.SetString(ap_string);
	char ap_str_tmp[MAX_LEN] = "커피맛우유좋아";
	ap_string = ap_str_tmp;
	HANDLE h_user1_str2 = handle_user_lists.SetString(ap_string);
	strcpy_s(ap_str_tmp, 17, "딸기맛케이크좋아");
	ap_string = ap_str_tmp;
	HANDLE h_user2_str1 = handle_user_lists.SetString(ap_string);
	handle_user_lists.printString(h_user1_str1);
	handle_user_lists.printString(h_user1_str2);
	handle_user_lists.printString(h_user2_str1);

	return 0;
}