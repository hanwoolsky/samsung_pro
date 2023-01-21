#include<list>
#include<string.h>
#include<string>
#include<ctype.h>
using namespace std;

struct Data {
    string cmd;
    int val[26];        // 'A'=0, 'Z'=25
};
list<Data> line;
list<Data>::iterator pre, cur;
char op[203];
int val[203];
int lineID, otop, vtop;

void init() {
    line.clear();
    line.push_back({});     // 0번 라인에 모든 변수 0으로 추가
    cur = line.end();       // cursor를 1번 라인(빈 라인)으로 설정
    lineID = 1;
}

void calc() {               // 마지막에 등록된 사칙연산자의 연산 수행 (없거나 여는 괄호면 무시)
	if (otop && op[otop-1] != '(') {
		otop--, vtop--;
		if (op[otop] == '+') val[vtop - 1] += val[vtop];
		if (op[otop] == '-') val[vtop - 1] -= val[vtop];
		if (op[otop] == '*') val[vtop - 1] *= val[vtop];
        if (op[otop] == '/') val[vtop - 1] = val[vtop] ? val[vtop-1] / val[vtop] : 0;
        val[vtop - 1] = max(0, val[vtop - 1]) % 10000;
	}
}

int calcExpression(string s) {      // s 수식 결과 반환
    vtop = otop = 0;
    for (int i=0; i<s.size(); i++) {
        if (isdigit(s[i]))
            val[vtop++] = s[i] - '0';

        else if (isalpha(s[i])) 
            val[vtop++] = pre->val[s[i] - 'A'];

        else {
            if (s[i] != '(') calc();
            if (s[i] == ')') otop--;
            else op[otop++] = s[i];
        }
    }
    calc();
    return val[0];
}

void calcLine() {
    pre = prev(cur, 1);                     // 현재 변수 값으로 계산하기 위해 cursor 직전 라인 표시
    memcpy(cur->val, pre->val, 26 * 4);     // 현재 라인의 변수값들을 현재 값으로 복사

    string cmd = cur->cmd + ",";
    int idx = 0, s, e;
    for (s = cmd.find('=') + 1; s < cmd.size(); s = e + 1) {    // s: 수식의 시작
        e = cmd.find(',', s);                                   // e: 수식의 끝(,)
                                                                // cmd[idx]: 현재 선택된 수식 결과가 할당되는 변수
        cur->val[cmd[idx] - 'A'] = calcExpression(cmd.substr(s, e - s));
        idx += 2;
    }
}

int addCommand(char mCommand[]) {
    cur = line.insert(cur, { mCommand });
    return lineID;
}

int moveCursor(int mPos) {
    for (int i = 1; i <= mPos && cur != line.end(); i++) {
        calcLine();
        ++cur;
        lineID++;
    }
    for (int i = 1; i <= -mPos && lineID > 1; i++) {
        --cur;
        lineID--;
    }
    return lineID;
}

void eraseCommand() {
    if (cur != line.end()) cur = line.erase(cur);
}

int getValue(char mVariable) {
    return prev(cur, 1)->val[mVariable - 'A'];
}

void destroy() {
}