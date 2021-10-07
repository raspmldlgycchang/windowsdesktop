#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<iostream>
#include<stdlib.h>
using namespace std;

typedef int HANDLE;
#define MAX_COUNT 32
struct HandleData {
	HANDLE h;
	char* p_string;
};
class HandleManager{
private:
	unsigned int m_gen_value;
	unsigned int m_max_count;

	HandleData* mp_data;

	/*2��������ü ������ ��� : 2���������Ҵ��̿�*/
	HandleData** pp_data;
	unsigned int m_len, m_max_len, m_max_two_count;

	/*�����-c���: 1���� �����Ҵ�, ���Ҵ��̿�*/
	char* mp_string;
	unsigned int m_str_len, m_str_max_len=1;

	/*[Q&A,Quiz]-cpp���: 2���� �����Ҵ��̿�*/
	char** pp_string;
	unsigned int m_str_two_len, m_str_max_two_len = 1;

public:
	HandleManager(unsigned int a_max_count =50){
		InitString();
		cout << "1���� �����Ҵ� ��������� �����Ǿ����ϴ�" << endl;

		m_gen_value = 1;
		m_max_count = a_max_count;
		mp_data = new HandleData[m_max_count];
		memset(mp_data, 0, sizeof(HandleData) * m_max_count);
		cout << "�ڵ� �����ڰ� �����Ǿ����ϴ�" << endl;
		pp_data = new HandleData * [m_max_two_count];//�����͹迭�����ϴ¹��_new������
		memset(pp_data, 0, sizeof(HandleData*)*m_max_two_count);
		cout << "2���� �����͹迭��ü�� �����Ǿ����ϴ�" << endl;
	}
	~HandleManager() {
		HandleData* p = mp_data;
		for (int i = 0; i < m_max_count; i++) {
			if (p->h) {
				delete[] p->p_string;
			}
			p++;
		}
		delete[] mp_data;

		DeleteString();//char* mp_string;����
		DeleteString_two_cpp();//char** pp_string;����
		//HandleData** pp_data;����
		p = pp_data[0];
		for (unsigned int i = 0; i < m_max_two_count; i++) {
			delete[] * (pp_data + i);
			for (int j = 0; j < m_max_len; j++) {
				if (p->h) {
					delete[] p->p_string;
				}
				p++;
			}
		}
		delete[] pp_data;
	}
	HANDLE InsertData(const char* ap_string) {
		m_len = strlen(ap_string) + 1;
		/*mp_data = new HandleData[m_max_count];
		memcpy(mp_data, 0, sizeof(HandleData)* m_max_count);*/
		HandleData* p = mp_data;
		int len = strlen(ap_string) + 1;
		unsigned int i;
		for (i= 0; i < m_max_count; i++) {
			if (p->h == 0)	break;
			else
			{
				p++;
			}
		}
		if (i<m_max_count) {
			p->p_string = new char[len];
			strcpy_s(p->p_string, strlen(ap_string)+1, ap_string);
			cout << p->p_string << ": ���ڿ� �߰�" << endl;
			p->h = m_gen_value++;
			return p->h;
		}
		return 0xFFFFFFFF;
	}
	void printData(HANDLE ah_str)
	{
		HandleData* p = mp_data;
		for (unsigned int i = 0; i < m_max_count; i++) {
			if (p->h) {
				cout << p->p_string << ": ����" << endl;
				delete[] p->p_string;
			}
			p++;
		}
		cout << "��ġ�ϴ� �޸� �ּҸ� ã�� ���߽��ϴ�" << endl;
	}
	void DeleteData(HANDLE ah_str) {
		HandleData* p = mp_data;//���Ḯ��Ʈ ��ü������ſ��� ���������
		//����Ű���� mp_data(�ڵ� ��ü�����ڰ� �����ϴ� �޸���(�����͹迭)
		//�����ּ� ����Ŵ
		for (unsigned int i = 0; i < m_max_count; i++) {
			if (p->h == ah_str) {
				cout << p->p_string << ": �����Ҳ�����!" << endl;
				delete[] p->p_string;
				p->h = 0;
				return;
			}
			p++;
		}
		cout << "�޸𸮿� ��ġ�ϴ� �ּҰ� ���� �ڵ鰪�Դϴ�!!" << endl;
	}
	/*�����: c��� -1���� �����Ҵ�,���Ҵ��̿�*/
	void InitString()
	{
		mp_string = (char*)malloc(2);
		strcpy_s(mp_string, 2, "a");

	}
	void SetString(const char* ap_string)
	{
		m_str_len = strlen(ap_string)+1;
		if (m_str_max_len < m_str_len) {
			m_str_max_len = m_str_len;
			free(mp_string);
			mp_string = (char*)malloc(m_str_max_len);
		}
		memcpy(mp_string, ap_string, m_str_max_len);
	}
	char* method1(const char* ap) {
		char arr[MAX_COUNT];
		for (int i = 0; i < strlen(ap) + 1; i++)
			arr[i] = *(ap + i);
		//Ȥ��
		//memcpy(arr, ap, strlen(ap)+1);
		char(*ptr)[MAX_COUNT];
		ptr = &arr;
		return *ptr;
	}
	void InsertString(const char* ins, int index)
	{
		char ori[29] = { 0, };//9+19+1(�ι��ڿ�) = 29
		char* p = (char*)malloc(29);
		p=method1(mp_string);
		strcpy_s(ori, strlen(p) + 1, p);
		cout << ori << ": ori" << endl;
		char temp_left[10] = { 0, };//9����+1(�ι��ڻ��Կ�)
		char temp_right[20] = { 0, };//19����+1(�ι��ڻ��Կ�)
		int total_size = m_str_max_len;
		char* message = (char*)malloc(10);
		for (int i = 0; i < index; i++) {
			temp_left[i] = ori[i];
			if (i == index - 1)	temp_left[i] = 0;
		}
		for (int i = index; i < m_str_max_len; i++) {
			temp_right[i - index] = ori[i];
			if (i == m_str_max_len - 1)	temp_right[i] = 0;
		}
		strcpy_s(message, 10, temp_left);
		total_size += strlen(ins);
		message = (char*)realloc(message, total_size);
		strcat_s(message, total_size, ins);
		total_size += strlen(temp_right);
		strcat_s(message, total_size, temp_right);
		cout << message << ": message" << endl;

	}
	void DeleteString()
	{
		free(mp_string);
	}
	/*�����: 1���������Ҵ� cpp��*/
	/*1���� �����Ҵ� cpp���� new�� delete�����ڸ� �Ἥ ����*/
	void SetString_cpp(const char* ap_string)
	{
		SetString(ap_string);//1���� �����Ҵ� c����� ����
	}
	void InsertString_cpp(const char* ins, int index)
	{
		char ori[29] = { 0, };
		char temp_left[10] = { 0, };
		char temp_right[20] = { 0, };
		char* p = new char[29];
		p = method1(mp_string);
		//�迭�������� p�� �迭�� ����
		strcpy_s(ori, strlen(p) + 1, p);
		cout << ori << ": ori" << endl;
		int toal_size = m_str_max_len;
		char* message = new char[10];
		for (int i = 0; i < index; i++) {
			temp_left[i] = ori[i];
			if (i == index - 1)	temp_left[i] = 0;
		}
		strcpy_s(message, 10, temp_left);
		int total_size = strlen(temp_left)+1;
		total_size += strlen(ins);
		strcat_s(message, total_size, ins);
		total_size += strlen(temp_right);
		strcat_s(message, total_size, temp_right);
		cout << message << ": message" << endl;

	}
	/*[Q&A,Quiz] 2���������޸��Ҵ�-cpp��*/
	void SetString_two_cpp(unsigned int a_str_max_two_count = 50)
	{
		m_str_max_two_len = a_str_max_two_count;
		pp_string = new char* [m_str_max_two_len];//�����͹迭 �Ҵ�
		for (unsigned int i = 0; i < m_str_max_two_len; i++) {
			*(pp_string + i) = new char[MAX_COUNT];
		}
	}
	void DeleteString_two_cpp()
	{
		for (unsigned int i = 0; i < m_str_max_two_len; i++)
			delete[] * (pp_string + i);
		delete[] pp_string;
	}
};

int GetMyString(char buffer[], int limit)
{
	int i;
	if (buffer != NULL)	rewind(stdin);
	for (i = 0; i < limit; i++) {
		buffer[i] = getchar();
		if (buffer[i] == '\n') {
			buffer[i] = 0;
			cout << buffer << " is your input" << endl;
			break;
		}
	}
	if (i < limit)	return 1;
	//���ǥ���������� 1�� ���ϸ� ��Ʈ�������� 1�� ���ϴ� ���̹Ƿ�
	//��Ʈ�� ���� �ֻ�����Ʈ�� 1�� �ǰ� �������� ��� 0���� �ǹǷ�
	//�׸��� �̴� ���, ������ȯ�� ������ ȿ���� �������⿡
	//���� �ּڰ��� �ֻ��� ��ȣ��Ʈ 1�����ϰ� ��� 0�̰�
	//�ű⼭ ��Ʈ���� 1�� ������ ����(�� ������ ����� �����ϰ� 1�� ����)
	//���� �������鼭 ���� �ִ�(���� Ŀ���� ��, ��, -1�� ���� ��)�� �ȴ�
	buffer[i] = 0;
	cout << buffer << ": your buffer is out of range" << endl;
	rewind(stdin);
	return 0x7FFFFFFF+1;//�ֻ��� 1��Ʈ ��ȣ��Ʈ
	//�ֻ��� ��Ʈ�� 0���� ��ȣ��Ʈ�̰� ���� 0111�� 2^3-1=7
	//= 2^24*(2^7-1)+2^16*(2^8-1)+2^8*(2^8-1)+ 2^8-1
	//= 0x7FFFFFFF
	//= 2,147,483,647(long int �ִ�)
	//= 2^24*(2^8-1)+2^16*(2^8-1)+2^8*(2^8-1)+ 2^8-1
	// =0xFFFFFFFF
	//= 4,294,967,295(unsigned long int �ִ�)
}
int main(void)
{
	HandleManager str_list;
	str_list.SetString("�ȳ��ϼ���!");
	HANDLE h_str = str_list.InsertData("�ȳ��ϼ���~");
	
	//str_list.SetString_cpp("�ȳ��ϼ���!");

	str_list.DeleteString();
	//str_list.DeleteString_two_cpp();
	str_list.printData(h_str);
	str_list.DeleteData(h_str);
	//char buffer[2];
	//int status = GetMyString(buffer, 1);
	char buffer[MAX_COUNT];
	int status = GetMyString(buffer, MAX_COUNT-1);
	cout << status << endl;
	return 0;
}