using namespace std;

#include <string> // string keyword, substring
#include <algorithm> // max, min, sort, fill, memset(? string.h)
#include <cstring>
#include <cctype> // isdigit, isalpha

const int INF = (int)1e9; // INF 설정 방법

int M;
int main(){
    // 문자열 "2X^2Y^2+3XY" 등이 있을 때 순회하는 방법
    string poly = "2X^2Y^2+3XY";
    for(int i = 0; poly[i]; i++){
        if(poly[i] == '^') continue; // 넘어가고 싶은 문자열 ex) ^, i++ 같은 것 필요없이, 그냥 continue
    }

    // 배열을 옮겨 붙이거나, 덮어쓸 때
    int A[6], B[6];
    int n;
    for(int i = 0; i < M; i++, n++){
        A[n] = B[i]; // n은 전역 변수이므로 계속 다음 자리에 원소가 채워진다.
    }

    // 11110000111100111 군데군데가 빈 배열에서 K번째 수의 idx를 찾고 싶을 때
    int exist[] = {11110000111100111};
    int k;
    for(int i = 0;;i++){ // 언제까지 돌지 모르니 비워두기
        k -= exist[i];
        if(k == 0) return i;
    }





    // fill
    void fill(ForwardIterator first, ForwardIterator last, const T& val);

    int min[SIZE];
    fill(min, min + SIZE, val);

    // 최적화
    #define f(i, x, n) for (register int i = x; i < n; i++)


}