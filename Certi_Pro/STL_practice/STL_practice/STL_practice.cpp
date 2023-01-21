#if 0
/***********************************************************/
// [2-1] Stack, Queue (STL Deque 이용)
/***********************************************************/
#include <iostream>
#include <deque>

using namespace std;

// deque : double-ended queue

// deque <저장하고자 하는 타입> 컨테이너명
deque <int> que;//FIFO queue 구현
deque <int> stk;//LIFO stack 구현

// 주로 사용할 method
// front() - 가장 앞 데이터 얻기 (리턴 -> 컨테이터에 저장한 data reference)
// back() - 가장 마지막 데이터 얻기

// push_front(데이터) - 앞쪽에 데이터 넣기
// push_back(데이터) - 뒤쪽에 데이터 넣기

// pop_front() - 가장 앞 데이터 꺼내기 (리턴 없음)
// pop_back() - 가장 뒤 데이터 꺼내기 (리턴 없음)

int main(void) {

	//FIFO queue 구현
	que.clear();//초기화
	for (int i = 1; i <= 5; i++) {
		que.push_back(i);
	}
	cout << "저장된 개수 = " << que.size() << endl;

	while (!que.empty()) {
		cout << que.front() << endl;//제일 먼저 저장된 값 읽기
		que.pop_front();//제일 먼저 저장된 값 제거
	}


	//LIFO stack 구현
	stk.clear();//초기화
	for (int i = 1; i <= 5; i++) {
		stk.push_back(i);
	}
	cout << "저장된 개수 = " << stk.size() << endl;

	while (!stk.empty()) {
		cout << stk.back() << endl;//제일 나중에 저장된 값 읽기
		stk.pop_back();//제일 나중에 저장된 값 제거
	}

	return 0;
}
#endif


#if 0
/***********************************************************/
// [3-1] Cpp Sort
/***********************************************************/
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct ST {
	string name;
	int age;
	int score;

	bool operator<(ST& d) const { // 연산자 오버라이딩
		if (score == d.score) return age < d.age;
		else return score > d.score;
	}
};

// 앞자료의 우선순위가 높으면 참 (정렬 비교함수)
bool Comp_Up(int& a, int& b) {
	return a < b;
}

bool Comp_Down(int& a, int& b) {
	return a > b;
}

int main(void)
{
	// 정렬함수 : sort
	// #include <algorithm> 필요함
	// sort(start,      end) - start,         end : 정렬할 자료 주소 시작과 끝,         [start,        end) 범위의 자료를 정렬 ( < 연산 결과 기준으로 정렬 )
	// sort(start,      end,      comp) - comp : 비교함수 주소,         [start,        end) 범위의 자료를 comp 함수의 비교 결과를 기준으로 정렬

	// int 배열 정렬
	int num[] = { 3,  10,  6,  8,  4,  9,  1,  7,  5,  2 };

	// 오름차순 정렬
	sort(num, num + 10);
	// sort(num,      num + 10,      Comp_Up);


	for (int i = 0; i < 10; i++) {
		cout << num[i] << " ";
	}
	cout << "\n\n";

	// 내림차순 정렬
	sort(num, num + 10, Comp_Down);

	for (int i = 0; i < 10; i++) {
		cout << num[i] << " ";
	}
	cout << "\n\n";

	// 구조체 배열 정렬
	ST test[10] = {
	{"Kim",          20,         75},
	{"Lee",          31,         90},
	{"Choi",         29,         90},
	{"Park",         43,         78},
	{"Hong",         25,         68},
	{"Cha",          33,         77},
	{"Shin",         15,         100},
	{"Ha",           16,         73},
	{"Beak",         23,         90},
	{"Pyo",          37,         60} };

	sort(test, test + 10);
	for (int i = 0; i < 10; i++) {
		cout << test[i].name << " " << test[i].score << " " << test[i].age << "\n";
	}

	return 0;
}

#endif


#if 0
/***********************************************************/
// [4-1] Linked List (STL list 이용)
/***********************************************************/
#include <list>
#include <iostream>

using namespace std;

int main(void) {
	list <int> c1;

	//0.초기화
	c1.clear();

	//1.뒤에 추가
	cout << "\n뒤에 추가 push_back(값)\n";
	for (int i = 1; i <= 5; i++) {
		c1.push_back(i);
	}

	// 현재 list의 iterator 정확한 타입 : list <int>::iterator
	// begin() ~ end()
	for (auto iter = c1.begin(); iter != c1.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;

	//2.앞에 추가
	cout << "\n앞에 추가 push_front(값)\n";
	c1.push_front(10);

	for (auto iter = c1.begin(); iter != c1.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;

	//3. 앞노드 제거
	cout << "\n앞노드 제거 pop_front(값)\n";
	c1.pop_front(); // return 값 없음

	for (auto iter = c1.begin(); iter != c1.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;

	//4. 뒷노드 제거
	cout << "\n뒷노드 제거 pop_back(값)\n";
	c1.pop_back();

	for (auto iter = c1.begin(); iter != c1.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;

	//5. 원하는 값을 가진 모든 노드 제거(remove) : O(n)
	cout << "\n원하는 값을 가진 노드 제거 remove(값)\n";
	c1.remove(3);

	for (auto iter = c1.begin(); iter != c1.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;

	//6. 원하는 값을 가진 노드 제거(erase)
	cout << "\n원하는 값을 가진 노드 제거 erase(iterator)\n";
	for (auto iter = c1.begin(); iter != c1.end(); iter++) {
		if (*iter == 2) {
			c1.erase(iter);
			break;
		}
	}

	for (auto iter = c1.begin(); iter != c1.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;

	//7. 원하는 노드 앞에 추가(insert)
	cout << "\n원하는 노드 앞에 추가 insert(iterator, 값)\n";
	for (auto iter = c1.begin(); iter != c1.end(); iter++) {
		if (*iter == 4) {
			c1.insert(iter, 1004); // 새로 추가된 데이터의 iterator 값 return
			break;
		}
	}

	for (auto iter = c1.begin(); iter != c1.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;

	//8. 요소를 원본 목록에서 제거한 다음 대상 목록에 삽입합니다. (slice)
	cout << "\n요소를 원본 목록에서 제거한 다음 대상 목록에 삽입합니다\n";
	list <int> c2{ 20,         21,         22 };
	list <int> c4{ 40,         41,         42,         43 };

	c2.splice(c2.end(), c4);

	for (auto iter = c2.begin(); iter != c2.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;

	for (auto iter = c4.begin(); iter != c4.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;

	return 0;
}

// 데이터가 하나도 없는 list => tail만 있는 리스트 => begin()의 iterator == end()의 iterator
#endif


#if 0
/***********************************************************/
// [5-1] Priority Queue : int 저장
/***********************************************************/
#include <iostream>
#include <queue> // Priority Queue 사용 위한 Header

using namespace std;

#if 0
priority_queue <int> pq_int;

#else
struct COMP { // Compare 객체
	bool operator()(int a, int b) {
		return a > b;
	}
};
priority_queue<int, vector<int>, COMP> pq_int;
#endif

int main() {
	int test[10] = { 7, 10, 2, 9, 3, 6, 4, 8, 1, 5 };

	// 1. 데이터 추가 : push()
	cout << "1. 데이터 추가 : push()\n";
	for (int i = 0; i < 10; i++) {
		pq_int.push(test[i]);
	}

	// 2. 최우선순위 Data 확인 및 꺼내기 : top(),        pop()
	cout << "\n2. 최우선순위 Data 확인 및 꺼내기 : top(), pop()\n";
	while (!pq_int.empty()) {
		int d = pq_int.top();
		pq_int.pop();
		cout << d << " ";
	}
	cout << "\n";

	// 3. 초기화
	cout << "\n3. 초기화\n";
	for (int i = 0; i < 10; i++) {
		pq_int.push(test[i]);
	}

	while (!pq_int.empty()) pq_int.pop();
	// pq_int =  priority_queue <int>();

	// pq_int = priority_queue<int, vector<int>, COMP>(); 빈 객체를 대입해서 초기화
	// pq_int = {}; // 간단한 초기화

	cout << (pq_int.empty() ? "비워졌음\n" : "비워지지않음\n");

	return 0;
}
#endif


#if 0
/***********************************************************/
// [5-1] Priority Queue (구조체 저장)
/***********************************************************/
#include <iostream>
#include <queue> // Priority Queue 사용 위한 Header

using namespace std;

#if 1
priority_queue <int> pq_int;
#else
struct COMP { // Compare 객체
	bool operator()(int a, int b) {
		return a > b;
	}
};
priority_queue<int, vector<int>, COMP> pq_int;
#endif

int main() {
	int test[10] = { 7,       10,       2,       9,       3,       6,       4,       8,       1,       5 };

	// 1. 데이터 추가 : push()
	cout << "1. 데이터 추가 : push()\n";
	for (int i = 0; i < 10; i++) {
		pq_int.push(test[i]);
	}

	// 2. 최우선순위 Data 확인 및 꺼내기 : top(),        pop()
	cout << "\n2. 최우선순위 Data 확인 및 꺼내기 : top(),        pop()\n";
	while (!pq_int.empty()) {
		int d = pq_int.top();
		pq_int.pop();
		cout << d << " ";
	}
	cout << "\n";

	// 3. 초기화
	cout << "\n3. 초기화\n";
	for (int i = 0; i < 10; i++) {
		pq_int.push(test[i]);
	}

	while (!pq_int.empty()) pq_int.pop();
	// pq_int =  priority_queue <int>();

	// pq_int = priority_queue<int,        vector<int>,        COMP>();

	cout << (pq_int.empty() ? "비워졌음\n" : "비워지지않음\n");

	return 0;
}
#endif


#if 0
/***********************************************************/
// [5-1] Priority Queue (STL list 이용)
/***********************************************************/
#include <iostream>
#include <string>
#include <queue> // Priority Queue 사용 위한 Header

using namespace std;

struct DATA {
	string name;
	int age;
	int score;

	bool operator<(const DATA& d) const { // 연산자 오버라이딩
		if (score == d.score) return age > d.age;
		else return score < d.score;
	}
};

#if 1
priority_queue<DATA> pq_st;
#else
struct COMP { // Compare 객체 
	bool operator()(DATA a, DATA b) {
		if (a.score == b.score) return a.age > b.age;
		else return a.score < b.score;
	}
};
priority_queue<DATA, vector<DATA>, COMP> pq_st;
#endif

int main() {
	DATA test[10] = {
	{"Kim",         20,        75},
	{"Lee",         31,        90},
	{"Choi",        29,        90},
	{"Park",        43,        78},
	{"Hong",        29,        68},
	{"Cha",         33,        77},
	{"Shin",        15,        100},
	{"Ha",          16,        73},
	{"Beak",        23,        90},
	{"Pyo",         37,        60} };

	// 1. 데이터 추가 : push()
	cout << "1. 데이터 추가 : push()\n";
	for (int i = 0; i < 10; i++) {
		pq_st.push(test[i]);
	}

	// 2. 최우선순위 Data 확인 및 꺼내기 : top(),        pop()
	cout << "\n2. 최우선순위 Data 확인 및 꺼내기 : top(),        pop()\n";
	while (!pq_st.empty()) {
		DATA d = pq_st.top();
		pq_st.pop();
		cout << d.name << " " << d.age << " " << d.score << '\n';
	}
	cout << "\n";

	// 3. 초기화
	cout << "\n3. 초기화\n";
	for (int i = 0; i < 10; i++) {
		pq_st.push(test[i]);
	}

	pq_st = priority_queue <DATA>();
	//pq_st = priority_queue<DATA,        vector<DATA>,        COMP>();

	cout << (pq_st.empty() ? "비워졌음\n" : "비워지지않음\n");

	return 0;
}
#endif


#if 1
/***********************************************************/
// [6-1] Unordered_map
/***********************************************************/

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

struct DATA
{
	int age;
	int score;
};

unordered_map<string, DATA> ht;

int main(void) {
	// names[i] - datas[i] mapping

	string names[] = {"Kim", "Lee", "Choi", "Park", "Hong", "Cha", "Shin", "Ha", "Beak", "Pyo"};

	DATA datas[] = {
		{20,        75},        // "Kim"
		{31,        83},        // "Lee"
		{29,        99},        // "Choi"
		{43,        78},        // "Park"
		{25,        68},        // "Hong"
		{33,        77},        // "Cha"
		{15,        100},       // "Shin"
		{16,        73},        // "Ha"
		{23,        90},        // "Beak"
		{37,        60}			// "Pyo"
	};

	// 0. 초기화 
	ht.clear();

	// 1. 데이터 추가 : insert
	cout << "\n1. 데이터 추가 : insert\n";
	for (int i = 0; i < 10; i++) {
		ht.insert({ names[i],        datas[i] });
	}

	for (auto iter = ht.begin(); iter != ht.end(); iter++) {

		cout << iter->first << " " << iter->second.age << " " << iter->second.score << "\n";
	}

	/*
	for (pair<string,        DATA> p : ht) {
		cout << p.first << " " << p.second.age << " " << p.second.score << "\n";
	}*/

	// 2. 탐색 및 값 변경
	cout << "\n2. 탐색 및 값 변경\n";
	for (string n : {"Cha", "Na", "Kim"}) {
		unordered_map<string, DATA>::iterator iter = ht.find(n);
		if (iter != ht.end()) { // 탐색 성공
			string name = iter->first; // Key
			DATA& d = iter->second; // Data
			d.age = 30;
			d.score = 30;
			cout << "Search Success (" << name << "/" << d.age << "/" << d.score << ")\n";
		}
		else { // 탐색 실패
			cout << "Search Fail! (Name : " << n << ")\n";
		}
	}

	for (pair<string, DATA> p : ht) {
		cout << p.first << " " << p.second.age << " " << p.second.score << "\n";
	}

	// 3. 삭제 : erase(iter)
	cout << "\n3. 삭제 : erase(iter)\n";
	for (string n : {"Cha", "Na", "Kim"}) {
		unordered_map<string, DATA>::iterator iter = ht.find(n);
		if (iter != ht.end()) { // 탐색 성공
			ht.erase(iter);
			cout << "Erase Success! (Name : " << n << ")\n";
		}
		else {
			cout << "Erase Fail! (Name : " << n << ")\n";
		}
	}
	for (pair<string, DATA> p : ht) {
		cout << p.first << " " << p.second.age << " " << p.second.score << "\n";
	}

	// 4. 삭제 :  erase(key)
	cout << "\n4. 삭제 :  erase(key)\n";
	for (string n : {"Lee", "Na"}) {
		int ret = ht.erase(n);
		if (ret > 0) {
			cout << "Erase Success! (Name : " << n << ")\n";
		}
		else {
			cout << "Erase Fail! (Name : " << n << ")\n";
		}
	}

	for (pair<string, DATA> p : ht) {
		cout << p.first << " " << p.second.age << " " << p.second.score << "\n";
	}

	return 0;
}
#endif