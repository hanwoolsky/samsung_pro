using namespace std;
 
#include<list>
#include<stack>
#include<string>
#include<cstring> // memcpy
#include<ctype.h> // isdigit(), isalpha()
#include<algorithm> // max
 
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