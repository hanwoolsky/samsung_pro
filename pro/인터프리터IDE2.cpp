using namespace std;
 
#include<list>
#include<string>
#include<cstring> // memcpy
#include<ctype.h> // isdigit(), isalpha() -> 왜 없어도 통과할까?
#include<algorithm> // max -> 왜 없어도 통과할까?
 
struct Data {
    string com;
    int alpha[26];
};
 
list<Data> linkedList;
list<Data>::iterator pre, cur; // list 원소 순회를 위한 iterator 선언
int pos, vtop, otop;
int expr[201];
char oper[201];
 
void calc() {
    if (otop && oper[otop - 1] != '(') {
        otop--, vtop--;
        if (oper[otop] == '+') expr[vtop - 1] += expr[vtop];
        if (oper[otop] == '-') expr[vtop - 1] -= expr[vtop];
        if (oper[otop] == '*') expr[vtop - 1] *= expr[vtop];
        if (oper[otop] == '/') expr[vtop - 1] = expr[vtop] ? expr[vtop - 1] / expr[vtop] : 0;
        expr[vtop - 1] = max(0, expr[vtop - 1]) % 10000;
    }
}
 
int calcExpr(string s) {
    vtop = otop = 0;
    for (int i = 0; i < s.size(); i++) {
        if (isdigit(s[i])) expr[vtop++] = s[i] - '0';
        else if (isalpha(s[i])) expr[vtop++] = pre->alpha[s[i] - 'A'];
        else {
            if (s[i] != '(') calc();
            if (s[i] == ')') otop--;
            else oper[otop++] = s[i];
        }
    }
    calc();
    return expr[0];
}
 
void calcLine() {
    pre = prev(cur, 1);
    memcpy(cur->alpha, pre->alpha, 26 * 4);
    string cmd = cur->com + ",";
    int idx = 0, s, e;
    for (s = cmd.find('=') + 1; s < cmd.size(); s = e + 1) {
        e = cmd.find(',', s);
        cur->alpha[cmd[idx] - 'A'] = calcExpr(cmd.substr(s, e - s));
        idx += 2;
    }
}
 
void init(){
    linkedList.clear();
    linkedList.push_back({}); // 초기화 목록에 일부 멤버의 초기값이 포함되어 있지 않으면 해당 멤버는 기본(default)값으로 초기화 된다. -> 전부 0인 값을 삽입한 셈
    cur = linkedList.end(); // cursor를 1번 빈라인으로 설정
    pos = 1;
}
 
void destroy(){
}
 
int addCommand(char mCommand[]){
    cur = linkedList.insert(cur, { mCommand });
    return pos;
}
 
int moveCursor(int mPos) {
    for(int i = 0; i < mPos && cur != linkedList.end(); i++) {
        calcLine();
        cur = next(cur, 1); // ++cur (o)
        pos++;
    }
    for (int i = 0; i < -mPos && pos > 1; i++) {
        cur = prev(cur, 1); // --cur (o)
        pos--;
    }
    return pos;
}
 
void eraseCommand(){
    if (cur != linkedList.end()) { // 만약 커서가 빈 줄에 있지 않다면 = 마지막 줄에 있지 않다면
        cur = linkedList.erase(cur);
    }
}
 
int getValue(char mVariable){
    return prev(cur, 1)->alpha[mVariable - 'A']; // prev(cur, 1) != --cur, 여기서는 --cur를 사용하면 cur의 값이 아예 바뀌어버린다.
}
 
// erase(iter it)의 반환값은 삭제한 반환값 뒤의 iter
// pit = erase(iter it)를 통해 iter를 받아놔야 계속해서 그 iter를 증감으로 활용할 수 있다.


// 2023.02.05 stack 계산이 부족
#include <string>
#include <cstring>
#include <cctype>
#include <list>
#include <algorithm>
using namespace std;

struct LINE {
	string com;
	int value[26];
};

list<LINE> dataList;
list<LINE>::iterator pre, cur;

int numStack[200];
char operStack[200];
int numIdx, operIdx;

void calc() {
	if (operIdx && operStack[operIdx - 1] != '(') {
		numIdx--, operIdx--;
		if (operStack[operIdx] == '+') numStack[numIdx - 1] += numStack[numIdx];
		if (operStack[operIdx] == '-') numStack[numIdx - 1] -= numStack[numIdx];
		if (operStack[operIdx] == '*') numStack[numIdx - 1] *= numStack[numIdx];
		if (operStack[operIdx] == '/') numStack[numIdx - 1] = numStack[numIdx] ? numStack[numIdx - 1] / numStack[numIdx] : 0;
		numStack[numIdx - 1] = max(0, numStack[numIdx - 1]) % 10000;
	}
}

int calcResult(string command) {
	numIdx = operIdx = 0;
	for (int i = 0; i < command.size(); i++) {
		if (isdigit(command[i])) numStack[numIdx++] = command[i] - '0';
		else if (isalpha(command[i])) numStack[numIdx++] = pre->value[command[i] - 'A'];
		else {
			if (command[i] != '(') calc();
			if (command[i] == ')') operIdx--;
			else operStack[operIdx++] = command[i];
		}
	}
	calc();
	return numStack[0];
}

void calculate() {
	pre = prev(cur, 1);
	memcpy(cur->value, pre->value, sizeof(int) * 26);
	string command = cur->com + ',';
	int idx = 0, s, e; // idx는 변수의 위치, s는 식의 시작 위치, e는 식의 끝 , 위치
	for (s = command.find('=') + 1; s < command.size(); s = e + 1) {
		e = command.find(',', s); // s 위치 이후의 ,를 찾는다.
		cur->value[command[idx] - 'A'] = calcResult(command.substr(s, e - s));
		idx += 2;
	}
}

int pos;
void init(){
	dataList.clear();
	dataList.push_back({});
	cur = dataList.end();
	pos = 1;
}

void destroy(){
}

int addCommand(char mCommand[]){
	cur = dataList.insert(cur, { mCommand });
	return pos;
}

int moveCursor(int mPos) {
	for (int i = 0; i < mPos && cur != dataList.end(); i++) {
		calculate();
		cur = next(cur, 1);
		pos++;
	}
	for (int i = 0; i < -mPos && pos > 1; i++) {
		cur = prev(cur, 1);
		pos--;
	}
	return pos;
}

void eraseCommand(){
	if (cur != dataList.end()) { // 만약 커서가 빈 줄에 있지 않다면 = 마지막 줄에 있지 않다면
		cur = dataList.erase(cur);
	}
}

int getValue(char mVariable){
	return prev(cur, 1)->value[mVariable - 'A'];;
}

// 23.03.21 : 85% 계산 쪽, init에서 {}주고 end로 설정하는 것 부족
#include <list>
#include <memory.h>
#include <cctype>
#include <string>
#include <algorithm>

using namespace std;

struct listData {
	string form;
	int value[26];
};
list<listData> interpreter;
list<listData>::iterator pre, cur;

int lineIdx;
int numIdx, operIdx;
int numStack[100];
char operStack[100];

void calc() {
	numIdx--; operIdx--;
	if (operStack[operIdx] == '*') numStack[numIdx - 1] *= numStack[numIdx];
	else if (operStack[operIdx] == '+') numStack[numIdx - 1] += numStack[numIdx];
	else if (operStack[operIdx] == '-') numStack[numIdx - 1] = max(0, numStack[numIdx - 1] - numStack[numIdx]);
	else if (operStack[operIdx] == '/') numStack[numIdx - 1] = numStack[numIdx] == 0 ? 0 : numStack[numIdx - 1] / numStack[numIdx];
	numStack[numIdx - 1] %= 10000;
}

//void calc() {
//	if (operIdx && operStack[operIdx - 1] != '(') {
//		numIdx--, operIdx--;
//		if (operStack[operIdx] == '+') numStack[numIdx - 1] += numStack[numIdx];
//		if (operStack[operIdx] == '-') numStack[numIdx - 1] -= numStack[numIdx];
//		if (operStack[operIdx] == '*') numStack[numIdx - 1] *= numStack[numIdx];
//		if (operStack[operIdx] == '/') numStack[numIdx - 1] = numStack[numIdx] ? numStack[numIdx - 1] / numStack[numIdx] : 0;
//		numStack[numIdx - 1] = max(0, numStack[numIdx - 1]) % 10000;
//	}
//}

int calculate(string str) {
	numIdx = operIdx = 0;
	for (char ch : str) {
		if (isdigit(ch)) numStack[numIdx++] = ch - '0';
		else if (isalpha(ch)) numStack[numIdx++] = prev(cur, 1)->value[ch - 'A'];
		else if (ch == ')') {
			if (operIdx > 0 && operStack[operIdx - 1] != '(') calc(); // 어차피 바로 바로 계산하니 while이든 if든 한개
			operIdx--;
		}
		else if (ch == '(') {
			operStack[operIdx++] = ch;
		}
		else {
			if (operIdx > 0 && operStack[operIdx - 1] != '(') calc(); // operStack[] != '(' 빼먹으면 안됨, ) 들어오기 전까지는 계산을 하고 있으니까
			operStack[operIdx++] = ch;
		}
	}
	calc();
	return numStack[0];
}

//int calculate(string command) {
//	numIdx = operIdx = 0;
//	for (int i = 0; i < command.size(); i++) {
//		if (isdigit(command[i])) numStack[numIdx++] = command[i] - '0';
//		else if (isalpha(command[i])) numStack[numIdx++] = pre->value[command[i] - 'A'];
//		else {
//			if (command[i] != '(') calc();
//			if (command[i] == ')') operIdx--;
//			else operStack[operIdx++] = command[i];
//		}
//	}
//	calc();
//	return numStack[0];
//}

void parsing() {
	pre = prev(cur, 1);
	memcpy(cur->value, pre->value, sizeof(int) * 26);
	int s, e;
	int i = 0;

	string com = cur->form + ',';
	for (s = com.find('=') + 1; s < com.size(); s = e+1) {
		e = com.find(',', s);
		cur->value[com[i] - 'A'] = calculate(com.substr(s, e - s));
		i += 2;
	}
}

void init(){
	lineIdx = 1;
	interpreter.clear();
	interpreter.push_back({});
	cur = interpreter.end();
}

void destroy() {}

int addCommand(char mCommand[]){
	cur = interpreter.insert(cur, { mCommand });
	return lineIdx;
}

int moveCursor(int mPos){
	for (int i = 0; i < mPos; i++) {
		if (cur != interpreter.end()) {
			parsing();
			lineIdx++;
			cur++;
		}
		else break;
	}
	for (int i = 0; i < -mPos; i++) {
		if (lineIdx > 1) {
			lineIdx--;
			cur--;
		}
		else break;
	}
	return lineIdx;
}

void eraseCommand(){
	if (cur != interpreter.end()) cur = interpreter.erase(cur);
}

int getValue(char mVariable){
	pre = prev(cur, 1);
	return pre->value[mVariable - 'A'];
}