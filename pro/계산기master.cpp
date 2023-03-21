// 1. 연산자 우선순위 있음, 괄호 있음
#include <string>
using namespace std;

int sN, oN;
int su[100];
char op[100];
int value[26];

void calc() {
    int& l = su[sN - 1], r = su[sN];             // 연산자 앞쪽 수, 연산자 뒤쪽 수
    if (op[oN] == '*') l = (l * r);
    if (op[oN] == '/') l = l / r;
    if (op[oN] == '+') l = (l + r);
    if (op[oN] == '-') l = l - r;
    sN--, oN--;
}

int getValue(string& str) {
    sN = oN = 0;
    for (char ch : str) {
        if (ch == ')') {                                        // ')' 인 경우
            while (op[oN] != '(') calc();                       // 괄호 시작까지 계산
            oN--;
        }
        else if (ch == '(') op[++oN] = '(';
        else if (ch == '*' || ch == '/') {                      // '*', '/' 인 경우
            if (op[oN] == '*' || op[oN] == '/') calc();         // 앞쪽 연산이 '*', '/' 인 경우 앞쪽 연산 수행
            op[++oN] = ch;
        }
        else if (ch == '+' || ch == '-') {                      // '+', '-' 인 경우,
            while (oN > 0 && op[oN] != '(') calc();                       // 앞쪽 연산이 '*', '/', '+', '-' 인 경우 앞쪽 연산 수행
            op[++oN] = ch;
        }
        else if (ch >= 'A') su[++sN] = value[ch - 'A'];         // 변수인 경우
        else su[++sN] = ch - '0';                               // 숫자인 경우
    }
    while(oN > 0) calc();
    return su[1];
}
// 32라인의 oN > 0 조건(괄호가 없으면?)과 38라인이 없어도 pass인 이유

int main() {
	string s = "(2+3)*2";
	printf("%d", getValue(s));
}


// 2. 연산자 우선순위 없음, 괄호 있음, 한 자리수
#include <list>
struct Data {
    string cmd;
    int val[26];        // 'A'=0, 'Z'=25
};
list<Data>::iterator pre, cur;
char op[203];
int val[203];
int otop, vtop;

void calc() {               // 마지막에 등록된 사칙연산자의 연산 수행 (없거나 여는 괄호면 무시)
    if (otop && op[otop - 1] != '(') {
        otop--, vtop--;
        if (op[otop] == '+') val[vtop - 1] += val[vtop];
        if (op[otop] == '-') val[vtop - 1] -= val[vtop];
        if (op[otop] == '*') val[vtop - 1] *= val[vtop];
        if (op[otop] == '/') val[vtop - 1] = val[vtop] ? val[vtop - 1] / val[vtop] : 0;
        val[vtop - 1] = max(0, val[vtop - 1]) % 10000;
    }
}

int calcExpression(string s) {      // s 수식 결과 반환
    vtop = otop = 0;
    for (int i = 0; i < s.size(); i++) {
        if (isdigit(s[i])) val[vtop++] = s[i] - '0';
        else if (isalpha(s[i])) val[vtop++] = pre->val[s[i] - 'A'];

        else { // 연산자 우선순위가 없으므로 ( 만 아니면 바로바로 calc()
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

// 3. 연산자 우선순위 있음, 최대 2자리, 곱하기 연속 없음, 괄호 없음
int val[5], op[5], vn, on;
void calc() {
    while (on) {
        if (op[on] == '*') val[vn - 1] *= val[vn];
        if (op[on] == '+') val[vn - 1] += val[vn];
        if (op[on] == '-') val[vn - 1] -= val[vn];
        vn--, on--;
    }
}

// [s:e-1) 계산결과 반환
// 숫자  : value stack 추가
// +,-  : 이전 연산 수행 후 op stack 추가
// : op stack 추가

int calc(int s, int e) {
    vn = on = 0;
    if (!isdigit(S[s])) val[++vn] = 0;  // 맨 앞이 숫자가 아닌 경우

    for (int i = s; i < e; i++) {
        if (isdigit(S[i])) {
            if (i > s && isdigit(S[i - 1])) val[vn] = val[vn] * 10 + S[i] - '0';
            else val[++vn] = S[i] - '0';
            continue;
        }
        else if (S[i] != '*') calc(); // 더하기, 빼기는 바로바로 계산, 곱하기는 먼저 계산해야하므로 한번 넘겼다가(*를 넣은 후) 계산
        op[++on] = S[i];
    }
    calc();
    return val[1];
}

// whole 계산기 : 우선 순위 있음, 괄호 있음, N자리 수 있음
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int ni, oi;
long long int numStack[100];
char operStack[100];

void calculate() {
	ni--; oi--;
	if (operStack[oi] == '*') numStack[ni - 1] *= numStack[ni];
	else if (operStack[oi] == '+') numStack[ni - 1] += numStack[ni];
	else if (operStack[oi] == '-') numStack[ni - 1] -= numStack[ni];
	else numStack[ni - 1] /= numStack[ni];
}

int main() {
	string s;
	cin >> s;

	ni = oi = 0;
	int numb = 0;
	for (int i = 0; s[i]; i++) {
		if (isdigit(s[i])) {
			numb = numb * 10 + s[i] - '0';
			if (i == s.size() - 1 || !isdigit(s[i + 1])) {
				numStack[ni++] = numb;
				numb = 0;
			}
		}
		else if (s[i] == '(') operStack[oi++] = '(';
		else if (s[i] == ')') {
			while (operStack[oi - 1] != '(') calculate();
			oi--;
		}
		else {
			if (s[i] == '*' || s[i] == '/') {
				if (operStack[oi - 1] == '*' || operStack[oi - 1] == '/') calculate();
			}
			else if (s[i] == '+' || s[i] == '-') {
				while (oi > 0 && operStack[oi - 1] != '(')  calculate();
			}
			operStack[oi++] = s[i];
		}
	}
	while (oi > 0) calculate();
	cout << numStack[0];
}

// Whole 계산기 (두 자리 이상, 괄호, 우선순위)
#include <iostream>
#include <typeinfo>
#include <string>
#include <cctype>

using namespace std;

int ni, oi;
long long int numStack[100];
char operStack[100];

void calculate() {
	ni--; oi--;
	if (operStack[oi] == '*') numStack[ni - 1] *= numStack[ni];
	else if (operStack[oi] == '+') numStack[ni - 1] += numStack[ni];
	else if (operStack[oi] == '-') numStack[ni - 1] -= numStack[ni];
	else numStack[ni - 1] /= numStack[ni];
}

int main() {
	string s;
	cin >> s;

	ni = oi = 0;
	int numb = 0;
	for (int i = 0; s[i]; i++) {
		if (isdigit(s[i])) {
			numb = numb * 10 + s[i] - '0';
			if (i == s.size() - 1 || !isdigit(s[i + 1])) {
				numStack[ni++] = numb;
				numb = 0;
			}
		}
		else if (s[i] == '(') operStack[oi++] = '(';
		else if (s[i] == ')') {
			while (operStack[oi - 1] != '(') calculate();
			oi--;
		}
		else {
			if (s[i] == '*' || s[i] == '/') {
                if(oi > 0) {
				    if (operStack[oi - 1] == '*' || operStack[oi - 1] == '/') calculate();
                }
			}
			else if (s[i] == '+' || s[i] == '-') {
				while (oi > 0 && operStack[oi - 1] != '(')  calculate();
			}
			operStack[oi++] = s[i];
		}
	}
	while (oi > 0) calculate();
	cout << numStack[0];
}