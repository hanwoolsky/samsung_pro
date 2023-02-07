using namespace std;

#include <string> // string keyword, substring(command.substr(시작 위치, 개수)), reverse(str.begin(), str.end())(문자열 뒤집기)
#include <algorithm> // max, min, sort, fill)
#include <cstring> // memset, memcpy
#include <cctype> // isdigit, isalpha

const int INF = (int)1e9; // INF 설정 방법

int M;
int main(){
    // 1. 문자열 "2X^2Y^2+3XY" 등이 있을 때 순회하는 방법
    string poly = "2X^2Y^2+3XY";
    for(int i = 0; poly[i]; i++){
        if(poly[i] == '^') continue; // 넘어가고 싶은 문자열 ex) ^, i++ 같은 것 필요없이, 그냥 continue
    }

    // 2. 배열을 옮겨 붙이거나, 덮어쓸 때
    int A[6], B[6];
    int n;
    for(int i = 0; i < M; i++, n++){
        A[n] = B[i]; // n은 전역 변수이므로 계속 다음 자리에 원소가 채워진다.
    }

    // 3. 11110000111100111 군데군데가 빈 배열에서 K번째 수의 idx를 찾고 싶을 때
    int exist[] = {11110000111100111};
    int k;
    for(int i = 0;;i++){ // 언제까지 돌지 모르니 비워두기
        k -= exist[i];
        if(k == 0) return i;
    }

    // 4. string find
    string com;
    int pos, cnt;
    com.find("원하는 문자", pos); // pos(default 0)번째부터 시작하여 원하는 문자를 찾고, 그 문자의 위치를 return
    com.find("원하는 문자", pos, cnt); // 원하는 문자의 위치부터 cnt개만큼을 취한 부분 문자열을 return한다.
    // 문자열을 찾는데 실패하면 string::npos로 정의되는 상수 npos를 리턴한다.

    // 5. string reverse, string strncmp
    string str = "";
    reverse(str.begin(), str.end());

    char str1[10], str2[10]; // string으로 하면 안됨
    int cnt;
    strncmp(str1, str2, cnt) < 0; // str1[0:cnt] < str2[0:cnt] 

    // 6. fill
    void fill(ForwardIterator first, ForwardIterator last, const T& val);

    int min[SIZE];
    fill(min, min + SIZE, val);

    // 7. 최적화
    #define f(i, x, n) for (register int i = x; i < n; i++)


}