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
	HandleUsers* mp_user1;//일단은 user1명에 대해서
	unsigned int m_max_user_cnt;
	HandleUsers** mp_users;//여러명의 user
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
			//if (*(*(p + i) + 0) + 0 != NULL) {//이건 char (*p)[MAX_LEN]으로 배열포인터의 상황이라면 동적메모리할당을 썼을 때
			//이렇게 아래주석처럼 써야 한다
			{	//delete[] (*(p + i) + 0);
				delete[] pp[i];
				cout << "pp[" << i << "] 동적메모리해제 및 객체소멸완료!" << endl;
			}
		}
		delete[] pp;
		cout << "pp 동적메모리해제 및 객체소멸완료!" << endl;
		/*HandleUsers* p_handle = mp_user1;
		for (unsigned int i = 0; i < m_max_count; i++) {
			if (p_handle->h != NULL) {
				delete[] p_handle->p_string;
			}
			p_handle++;
			cout << i << "번째 구조체 요소 p_string 동적메모리해제 및 객체소멸완료!" << endl;
		}
		delete[] mp_user1;
		cout << "핸들객체관리자 mp_user1 동적메모리해제 및 객체소멸완료!" << endl;
		*/
		/*
		HandleUsers** p_handle = mp_users;
		unsigned int i;
		for (unsigned int j = 0; j < m_max_user_cnt; j++) {
			for (i = 0; i < m_max_count; i++) {
				if ((*p_handle)->h!=NULL) {//주석1참고
					cout << "mp_users[" << j << "][" << i << "]";
					printf("의 주소 %p ", &mp_users[j][i]);
					delete[] p_handle[j]->p_string;//주석2참고_방법1
					//delete[] p_handle[j][i].p_string;//방법2
				}
				p_handle[j]++;//주석3참고_방법1 한명의 user에서 문자열총개수m_max_count만큼 돌기위해 1차원구조체변수 원소하나 메모리크기만큼 증가
				cout << "동적메모리 해제 및 객체 소멸 완료" << endl;
			}
			delete[] mp_users[j];
			cout << "핸들객체관리자 mp_users[" << j << "]"<< "동적메모리해제 및 객체소멸완료!" << endl;

		}
		delete[] mp_users;
		cout << "핸들객체관리자 mp_users 동적메모리해제 및 객체소멸완료!" << endl;
		*/

		HandleUsers* p_handle = mp_users[0];
		//printf("sizeof(HandleUsers)= %ld\n", sizeof(HandleUsers));//멤버변수 합 = int형 + char*(주소는 무조건 4바이트입니다) = 8바이트
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
				if (p_handle->h != 0) {//주석1참고
					cout << "mp_users[" << j << "][" << i << "]";
					printf("의 주소 %p ", &mp_users[j][i]);
					delete[] p_handle->p_string;//주석2참고_방법1
				}
				cout << "구조체 요소 p_string 동적메모리 해제 및 객체 소멸 완료" << endl;
				p_handle++;//주석3참고_방법1 한명의 user에서 문자열총개수m_max_count만큼 돌기위해 구조체변수 크기만큼 증가
				printf("%p :동적메모리해제하고 ++증가연산시킨 p_handle변수값=&mp_user[%d][%d]\n", p_handle, j,i+1);
			}
			delete[] mp_users[j];
			cout << "핸들객체관리자 1차원 구조체 포인터=포인터배열=mp_users[" << j << "]" << "동적메모리해제 및 객체소멸완료!" << endl;

		}
		delete[] mp_users;
		cout << "핸들객체관리자 2차원구조체포인터=1차원 구조체포인터변수의 1차원배열 mp_users 동적메모리해제 및 객체소멸완료!" << endl;
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
			//문자열이 제대로 복사된 것이 확인되었다면 2차원구조체포인터변수의 1차원구조체포인터변수에도 복사한다
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
				cout << "선택하신 문자열은 요오~" << ": " << p_handle->p_string << endl;
			}
			else p_handle++;
		}
		cout << "일치하는 메모리주소가 없습니다!" << endl;
	}
	void DeleteData(HANDLE h_str)
	{
		HandleUsers* p_handle = mp_user1;
		unsigned int i;
		for (i = 0; i < m_max_count; i++) {
			if (p_handle->h == h_str) {
				cout << p_handle->p_string << "삭제하겠니다!" << endl;
				delete[] p_handle->p_string;
				p_handle->h = 0;
				return;
			}
			p_handle++;
		}
		cout << "일치하는 메모리주소가 없습니다!" << endl;
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
	HANDLE h_str_user1_1 = str_list_user1.SetString("헬로우");
	cout << h_str_user1_1 << ": HANDLE h_str_user1_1" << endl;

	HANDLE h_str_user1_2 = str_list_user1.SetString("제이름은누구,");
	cout << h_str_user1_2 << ": HANDLE h_str_user1_2" << endl;

	HANDLE h_str_user1_3 = str_list_user1.SetString(",이고요,");
	cout << h_str_user1_3 << ": HANDLE h_str_user1_3" << endl;

	HANDLE h_str_user1_4 = str_list_user1.SetString("사는곳은어디고,");
	cout << h_str_user1_4 << ": HANDLE h_str_user1_4" << endl;

	HANDLE h_str_user1_5 = str_list_user1.SetString("성별은무엇이고,");
	cout << h_str_user1_5 << ": HANDLE h_str_user1_5" << endl;

	HANDLE h_str_user1_6 = str_list_user1.SetString("좋아하는음식은");
	cout << h_str_user1_6 << ": HANDLE h_str_user1_6" << endl;

	HANDLE h_str_user1_7 = str_list_user1.SetString("뭐뭐입니다");
	cout << h_str_user1_7 << ": HANDLE h_str_user1_7" << endl;



	int select_num;
	unsigned int genValue = str_list_user1.getGenValue();
	unsigned int i;
	//char* p;
	char* buf = new char[2];
	while (1) {
		cout << "몇번째 문자열을 출력하시겠어요? (8 or 9 For Exit): " << endl;
		cin >> select_num;
		rewind(stdin);
		if (select_num == 8 || select_num == 9)	break;
		//p = _itoa(select_num, buf, 10);

		//if (strcmp(p, "8") || strcmp(p, "7")) {
		//	cout << "출력게임끄읕~" << endl;
		//	break;
		//}
		for (i = 0; i < genValue; i++) {
			if (select_num == i)	break;
			else continue;
		}
		if (i < genValue)	str_list_user1.PrintData(i);
		else
		{
			cout << "일치하는 핸들값이 없습니다!" << endl;
		}
		fflush(stdout);
	}
	while (1) {
		cout << "몇번째 문자열을 삭제하시겠어요? (8 or 9 For Exit): " << endl;
		cin >> select_num;
		rewind(stdin);
		if (select_num == 8 || select_num == 9)	break;

		//p = _itoa(select_num, buf, 10);

		//if (strcmp(p, "8") || strcmp(p, "7")) {
		//	cout << "게임종료!" << endl;
		//	break;
		//}

		for (i = 0; i < genValue; i++) {
			if (select_num == i)	break;
			else continue;
		}
		if (i < genValue)	str_list_user1.DeleteData(i);
		else
		{
			cout << "일치하는 핸들값이 없습니다!" << endl;
		}
	}


	return 0;
}