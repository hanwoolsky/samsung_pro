// 2023.03.20 스스로 풀기 80% (계산기는 스스로 풀었다.)
#include <string>
#include <list>
#include <cctype>
#include <memory.h>

using namespace std;

int numIdx, operIdx;
int numStack[100];
char operStack[100];

int value[26];

struct listData {
	string form;
	char variable;
	int preValue; // variable의 이전 값
};

list<listData> cmd;
list<listData>::iterator cur;
int lineIdx;

void calc() {
	numIdx--, operIdx--;
	if (operStack[operIdx] == '*') numStack[numIdx - 1] *= numStack[numIdx];
	else if (operStack[operIdx] == '+') numStack[numIdx - 1] += numStack[numIdx];
	else if (operStack[operIdx] == '-') numStack[numIdx - 1] = max(0, numStack[numIdx - 1] - numStack[numIdx]);
	else if (operStack[operIdx] == '/') numStack[numIdx - 1] = numStack[numIdx] == 0 ? 0 : numStack[numIdx - 1] / numStack[numIdx];
	numStack[numIdx - 1] %= 10000;
}

int calculate(string str) {
	numIdx = operIdx = 0;
	for (int i = 2; str[i]; i++) {
		if (isdigit(str[i])) numStack[numIdx++] = str[i] - '0';
		else if (isalpha(str[i])) numStack[numIdx++] = value[str[i] - 'A'];
		else if (str[i] == '(') operStack[operIdx++] = '(';
		else if (str[i] == ')') {
			while (operStack[operIdx - 1] != '(') calc();
			operIdx--;
		}
		else if (str[i] == '*' || str[i] == '/') {
			if (operIdx > 0) {
				if (operStack[operIdx - 1] == '*' || operStack[operIdx - 1] == '/') calc();
			}
			operStack[operIdx++] = str[i];
		}
		else {
			while (operIdx > 0 && operStack[operIdx - 1] != '(') calc();
			operStack[operIdx++] = str[i];
		}
	}
	while (operIdx > 0) calc();
	return numStack[0];
}

void init(){
	lineIdx = 1;
	cmd.clear();
	cur = cmd.begin();
	memset(value, 0, sizeof(value));
}

void destroy(){
}

int addCommand(char mCommand[]){
	cur = cmd.insert(cur, { mCommand, mCommand[0], 0 }); // data가 cur의 앞에 넣어지고 해당 주소를 cur에 받아온다.
	return lineIdx;
}

int moveCursor(int mPos) {
	for (int i = 0; i < mPos; i++) {
		if (cur != cmd.end()) {
			cur->preValue = value[cur->variable - 'A'];
			value[cur->variable - 'A'] = calculate(cur->form);
			cur++; lineIdx++;
		}
		else break;
	}
	for (int i = 0; i < -mPos; i++) {
		if (cur != cmd.begin()) {
			cur--; lineIdx--;
			value[cur->variable - 'A'] = cur->preValue;
		}
		else break;
	}
	return lineIdx;
}

void eraseCommand(){
	if (cur != cmd.end()) cur = cmd.erase(cur);
}

int getValue(char mVariable){
	return value[mVariable - 'A'];
}