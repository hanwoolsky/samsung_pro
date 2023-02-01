#if 0
/***********************************************************/
// [1-1] A0. 배열 구간의 합 구하기
/***********************************************************/
#include <iostream>
using namespace std;
int arr[50001];

void prefixSum(int n) {
    for (int i = 1; i <= n; i++) {
        arr[i] += arr[i - 1];
    }
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int N, Q, s, e;
    cin >> N >> Q;
    arr[0] = 0;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
    prefixSum(N);
    for (int i = 0; i < Q; i++) {
        cin >> s >> e;
        cout << arr[e] - arr[s-1] << "\n";
    }
    return 0;
}

#endif

#if 0
/***********************************************************/
// [1-2] A1. 월동 준비 : 나의 풀이
/***********************************************************/
#include <iostream>
#include <algorithm>
using namespace std;
int arr[100001];
int dp[100001];
int N, smart, fool;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    arr[0] = 0; dp[0] = 0; smart = 0; fool = -10000;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }

    int smartFlag = 1;
    int foolFlag = 1;
    int minN = -10000;

    for (int i = 1; i <= N; i++) {
        if (arr[i] < 0 && arr[i] > minN) minN = arr[i];
        if (arr[i] >= 0) {
            smartFlag = 0;
            smart += arr[i];
        }

        if (i > 1 && dp[i - 1] >= 0) {
            foolFlag = 0;
            dp[i] = dp[i - 1] + arr[i];
        }
        else {
            dp[i] = arr[i];
            if(arr[i] > 0) foolFlag = 0;
        }
        fool = max(fool, dp[i]);
    }
    if (smartFlag) smart = minN;
    if (foolFlag) fool = minN;

    cout << fool << " " << smart;
    return 0;
}

#endif

#if 0
/***********************************************************/
// [1-2] A1. 월동 준비 : 강사님의 풀이
/***********************************************************/
#include <iostream>
#include <algorithm>
using namespace std;
int num[100001];
int N;

void Input_Data() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> num[i];
    }
}

void Solve(int *smart, int *fool) {
    int s_smart = 0;
    int s_fool = -10000;

    int sum = 0;
    for (int i = 1; i <= N; i++) {
        if (num[i] > 0) s_smart += num[i];
        sum += num[i];
        if (s_fool < sum) s_fool = sum;
        if (sum < 0) sum = 0;
    }
    if (s_smart == 0) s_smart = s_fool; // 양수가 하나도 없을 때의 최솟값 = 멍청한 다람쥐가 먹는 값
    // 이렇게 하면 음수 + 0 값만 있었을 때에도 s_fool이 0을 가지게 되면서 smart도 0이 된다.

    *smart = s_smart;
    *fool = s_fool;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    int sol_smart, sol_fool;
    Solve(&sol_smart, &sol_fool);

    cout << sol_fool << " " << sol_smart << '\n';
}

#endif

#if 0
/***********************************************************/
// [1-3] A2. 용액 SPJ : 나의 풀이 - 절댓값 정렬
/***********************************************************/
#include <iostream>
#include <algorithm>
using namespace std;
int arr[100001];
int N, ans;

void Input_Data() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
}

bool Comp(int a, int b) {
    int abs_a = a, abs_b = b;
    if (a < 0) abs_a = (-1) * a;
    if (b < 0) abs_b = (-1) * b;

    return abs_a < abs_b;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    sort(arr, arr+N, Comp);

    int min = 2000000000;
    int abs_min, x, y;
    for (int i = 0; i < N - 1; i++) {
        abs_min = arr[i] + arr[i + 1] > 0 ? arr[i] + arr[i + 1] : (-1) * (arr[i] + arr[i + 1]);
        if (abs_min <= min) {
            min = abs_min;
            if (arr[i] > arr[i + 1]) {
                x = arr[i + 1];
                y = arr[i];
            }
            else {
                x = arr[i];
                y = arr[i + 1];
            }
        }
        if (abs_min == 0) break;
    }
    cout << x << " " << y;
}

#endif

#if 0
/***********************************************************/
// [1-3] A2. 용액 SPJ : 강사님의 풀이 - 투 포인터 and 이진탐색
/***********************************************************/
#include <iostream>

using namespace std;

#define MAX_N (100000)

int N;
int spec[MAX_N];

void Inupt_Data(void) {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> spec[i];
    }
}

int Binary_Search_Lower(int s, int e, int d) {
    int sol = -1;
    while (s <= e) {
        int m = (s + e) / 2;
        if (spec[m] >= d) {
            sol = m;
            e = m - 1;
        }
        else s = m + 1;
    }
    return sol;
}

int Binary_Search_Upper(int s, int e, int d) {
    int sol = -1;
    while (s <= e) {
        int m = (s + e) / 2;
        if (spec[m] <= d) {
            sol = m;
            s = m + 1;
        }
        else e = m - 1;
    }
    return sol;
}


void Solve_Bin(int& sol_small, int& sol_big) {
    // Binary Search : O(NlogN)
    int min_sum = 0x7fffffff; // 32bit에서 최상위만 0, 나머지는 1인 값 -> 양수값 중 가장 큰 값
    for (int i = 0; i < N; i++) {
        int ret = Binary_Search_Lower(i + 1, N - 1, -spec[i]);
        if (ret != -1) {
            int sum = spec[i] + spec[ret];
            int abs_sum = sum < 0 ? -sum : sum;
            if (min_sum > abs_sum) {
                sol_small = spec[i];
                sol_big = spec[ret];
                min_sum = abs_sum;
            }
        }

        ret = Binary_Search_Upper(i + 1, N - 1, -spec[i]);
        if (ret != -1) {
            int sum = spec[i] + spec[ret];
            int abs_sum = sum < 0 ? -sum : sum;
            if (min_sum > abs_sum) {
                sol_small = spec[i];
                sol_big = spec[ret];
                min_sum = abs_sum;
            }
        }

    }

}

void Solve_TP(int& sol_small, int& sol_big) {
    // Two pointers : O(N)
    int l = 0, r = N - 1;
    int min_sum = 0x7fffffff;
    while (l < r) {
        int sum = spec[l] + spec[r];
        int abs_sum = sum < 0 ? -sum : sum;

        if (min_sum > abs_sum) {
            sol_small = spec[l];
            sol_big = spec[r];
            min_sum = abs_sum;
        }

        if (sum < 0) l++;
        else r--;
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Inupt_Data();

    int sol_small, sol_big;

    Solve_TP(sol_small, sol_big);
    //Solve_Bin(sol_small, sol_big);

    cout << sol_small << ' ' << sol_big << '\n';

    return 0;
}

#endif

#if 0
/***********************************************************/
// [1-4] A3. Best Friends : 나의 풀이 - Sliding Window
/***********************************************************/
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

#define MAX_N (300000)

struct DATA {
    int nameLength;
    int rank;
} student[MAX_N + 1];

bool Comp(const DATA& x, const DATA& y) {
    return x.nameLength != y.nameLength ? x.nameLength < y.nameLength : x.rank < y.rank;
}

int N, K;
string name[MAX_N + 10];

void Input_Data(void) {
    string str;
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> name[i];
        student[i].nameLength = name[i].length();
        student[i].rank = i;
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // 입력 받는 부분
    Input_Data();

    sort(student, student + N, Comp);

    long long bf = 0;
    int p = 1;
    // 여기서부터 작성
    for (int i = 0; i < N;) {
        if (i == p) p++;
        if (p == N) {
            bf += ((p - i - 1) * (p - i - 2) / 2);
            break;
        }
        if (student[i].nameLength == student[p].nameLength) {
            if (student[p].rank - student[i].rank <= K) {
                bf++;
                p++;
            }
            else {
                i++;
                if (p - i - 1 > 0) bf += (p - i - 1);
            }
        }
        else {
            bf += (p - i - 1) * (p - i - 2) / 2;
            i = p;
            p++;
        }
    }

    // 출력하는 부분
    cout << bf << '\n';

    return 0;
}

#endif

#if 0
/***********************************************************/
// [1-4] A3. Best Friends : 강사님 풀이 - Sliding Window
/***********************************************************/
#include <iostream>
#include <cstring>
using namespace std;

#define MAX_N (300000)
#define MAX_K (K)
#define MAX_LEN (20)

int N, K;
int len[MAX_N];
int cnt_len[MAX_LEN + 1];

void Input_Data(void) {
    char s[MAX_LEN + 1];
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> s;
        len[i] = strlen(s);
    }
}

long long Solve(void) {
    long long sol = 0;
    for (int e = 0; e <= K; e++) {
        sol += cnt_len[len[e]];
        cnt_len[len[e]]++;
    }
    for (int e = K + 1; e < N; e++) {
        cnt_len[len[e - K - 1]]--;
        sol += cnt_len[len[e]];
        cnt_len[len[e]]++;
    }
    return sol;
}


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    cout << Solve() << '\n';

    return 0;
}

#endif

#if 0
/***********************************************************/
// [1-5] A4. 회전 초밥 : 강사님의 풀이
/***********************************************************/
#include <iostream>

using namespace std;

#define MAX_N (3000000)
#define MAX_K (3000)
#define MAX_D (3000)

int N, d, k, c;
int dish[MAX_N + MAX_K];
int cnt_sushi[MAX_D + 1];
void Input_Data(void) {
    cin >> N >> d >> k >> c;
    for (int i = 0; i < N; i++) {
        cin >> dish[i];
    }
}


int Solve(void) {
    for (int i = 0; i < k - 1; i++) {
        dish[N + i] = dish[i];
    } // % SIZE 대신 아예 앞에 K-1개를 뒤에 복사

    int max_cnt;
    int cnt = 1;
    cnt_sushi[c] = 1;

    for (int i = 0; i < k; i++) {
        cnt_sushi[dish[i]]++;
        if (cnt_sushi[dish[i]] == 1) cnt += 1;
    }
    max_cnt = cnt;

    for (int i = 1; i < N; i++) {
        cnt_sushi[dish[i - 1]]--;
        if (cnt_sushi[dish[i - 1]] == 0) cnt -= 1;
        cnt_sushi[dish[i + k - 1]]++;
        if (cnt_sushi[dish[i + k - 1]] == 1) cnt += 1;
        if (max_cnt < cnt) max_cnt = cnt;
    }
    return max_cnt;
}


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    cout << Solve() << '\n';

    return 0;
}

#endif

#if 0
/***********************************************************/
// [1-6] A5. 색종이 : 강사님의 풀이
/***********************************************************/
#include <iostream>

using namespace std;

#define MAX_SIZE (100)

// paper[r][c] : 도화지 밑변으로 부터 r, 왼쪽변으로부터 c만큼 떨어진 위치의 1*1 격자 공간의 상태
int paper[MAX_SIZE][MAX_SIZE];


void Put(int sr, int sc) {
    // sr,sc에서부터 색종이 놓기
    for (int r = sr; r < sr + 10; r++) {
        for (int c = sc; c < sc + 10; c++) {
            paper[r][c] = 1; // 해당 격자 위치 종이 높임
        }
    }
}

void Input_Data_And_Make_Paper(void) {
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int r, c;
        cin >> r >> c;
        Put(r, c);
    }
}

bool Check(int sr, int sc, int er, int ec) {
    for (int r = sr; r <= er; r++) {
        for (int c = sc; c <= ec; c++) {
            if (paper[r][c] == 0) return false;
        }
    }
    return true;
}

int Get_Answer_N6(void) {
    // O(N^6) : 사각형 선택의 모든 경우의 수 (좌상단 지점 선택/ 우하단 지점 선택 - N^4)
    //        : 선택된 사각형 영역이 모두 종이 놓여져 있는지 확인 (N^2)
    int max_area = 0;
    for (int sr = 0; sr < MAX_SIZE; sr++) {
        for (int sc = 0; sc < MAX_SIZE; sc++) {
            if (paper[sr][sc] == 0) continue;

            for (int er = sr; er < MAX_SIZE; er++) {
                for (int ec = sc; ec < MAX_SIZE; ec++) {
                    if (paper[er][ec] == 0) break;
                    if (!Check(sr, sc, er, ec)) break;
                    int area = (ec - sc + 1) * (er - sr + 1);
                    if (max_area < area) max_area = area;
                }
            }
        }
    }
    return max_area;
}

void Make_Info() {
    for (int c = 0; c < MAX_SIZE; c++) {
        for (int r = 1; r < MAX_SIZE; r++) {
            if (paper[r][c] == 1) paper[r][c] += paper[r - 1][c];
        }
    }
}


int Get_Answer_N3(void) {
    // O(N^3) : 밑변 선택 (밑변의 r, 열의 시작지점, 끝지점 선택) - O(N^3)
    //        : 해당 밑변에서 만들 수 있는 직사각형 최대 높이 선택 - O(1)
    Make_Info(); // 밑변 높이 선택을 돕기 위해 각 격자위치에서 올라갈 수 있는 최대 높이 미리 계산
    int max_area = 0;
    for (int r = 0; r < MAX_SIZE; r++) {
        for (int sc = 0; sc < MAX_SIZE; sc++) {
            int h = 100;
            for (int ec = sc; ec < MAX_SIZE; ec++) {
                if (h > paper[r][ec]) h = paper[r][ec];
                if (h == 0) break;
                int area = h * (ec - sc + 1);
                if (max_area < area) max_area = area;
            }
        }
    }
    return max_area;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data_And_Make_Paper();

    cout << Get_Answer_N3() << '\n';


    return 0;
}

#endif

#if 0
/***********************************************************/
// [2-1] A6. 크게 만들기 : 강사님 풀이 - Stack
/***********************************************************/
#include <iostream>
#include <deque>
#include <string>

using namespace std;

#define MAX_N (500000)

int N, K;
string num;
deque<char> stk;

void Input_Data(void) {
    cin >> N >> K;
    cin >> num;
}

void Solve(void) {
    stk.clear(); // 초기화
    for (char n : num) {
        while (!stk.empty() && K && stk.back() < n) {
            stk.pop_back();
            K--;
        }
        stk.push_back(n);
    }
    for (int i = 0; i < K; i++) stk.pop_back();
}

void Print_Result(void) {
    for (char n : stk) {
        cout << n;
    }
    cout << '\n';
}


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    Solve();

    Print_Result();

    return 0;
}

#endif

#if 0
/***********************************************************/
// [2-2] A7. 불쾌한 날 : 나의 풀이 - 배열
/***********************************************************/
#include <iostream>
#include <deque>

using namespace std;
int stk[80000];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, height, top;
    long long ans;
    cin >> N;

    ans = top = 0;
    for (int i = 0; i < N; i++) {
        cin >> height;
        while (top > 0 && stk[top - 1] <= height) top -= 1;
        ans += top;
        stk[top] = height;
        top += 1;
    }

    cout << ans << '\n';


    return 0;
}

#endif

#if 0
/***********************************************************/
// [2-2] A7. 불쾌한 날 : 강사님의 풀이 - Stack
/***********************************************************/
#include <iostream>
#include <deque>

using namespace std;

#define MAX_N (80000)

int N;
int height[MAX_N];
deque<int> stk;


void Input_Data(void) {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> height[i];
    }
}

long long Solve(void) {
    long long sol = 0;
    stk.clear();

    for (int i = 0; i < N; i++) {
        while (!stk.empty() && stk.back() <= height[i]) {
            stk.pop_back();
        }
        sol += stk.size();
        stk.push_back(height[i]);
    }

    return sol;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    cout << Solve() << '\n';

    return 0;
}

#endif

#if 0
/***********************************************************/
// [2-3] A8. 카드 건네기
/***********************************************************/
#include <iostream>
#include <deque>

using namespace std;
deque<int> queue;


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, j, card;
    cin >> N;
    

    for (int i = 1; i <= N; i++) queue.push_back(i);
   
    for (int i = 1; i < N; i++) {
        card = queue.back();
        for (j = 0; j < card / 2; j++) {
            int top = queue.front();
            queue.pop_front();
            queue.push_back(top);
        }
        cout << queue.front() << " ";
        queue.pop_front();
    }
    cout << queue.front() << " ";
    return 0;
}

#endif

#if 0
/***********************************************************/
// [2-3] A8. 카드 건네기 : 강사님 풀이
/***********************************************************/
#include <iostream>
#include <deque>

using namespace std;

int N;
deque<int> deck;

void Input_Data(void) {
    cin >> N;
}

int Simulation(void) {
    for (int i = 1; i <= N; i++) {
        deck.push_back(i);
    }

    for (int i = 0; i < N - 1; i++) {
        int cnt = deck.back() / 2;
        for (int j = 0; j < cnt; j++) {
            deck.push_back(deck.front());
            deck.pop_front();
        }
        cout << deck.front() << ' ';
        deck.pop_front();
    }
    cout << deck.front() << ' ';
    deck.pop_front();
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    Simulation();

    return 0;
}

#endif

#if 0
/***********************************************************/
// [2-4] A9. 프린터 큐 : 나의 풀이
/***********************************************************/
#include <iostream>
#include <cstring>
#include <deque>

using namespace std;

struct DATA {
    int order;
    int priority;
};

int N, ord;
int cnt[9];
deque<DATA> queue;

void InputData() {
    queue.clear();
    memset(cnt, 0, 9 * sizeof(int));
    cin >> N >> ord;
    int pri;
    for (int i = 0; i < N; i++) {
        cin >> pri;
        cnt[pri - 1]++;
        queue.push_back({ i, pri });
    }
}

void Solve() {
    int maxN = 1;
    for (int i = 8; i >= 0; i--) {
        if (cnt[i]) {
            maxN = i + 1;
            cnt[maxN - 1]--;
            break;
        }
    }
    while (queue.front().priority != maxN) {
        queue.push_back(queue.front());
        queue.pop_front();
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int ans;
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        ans = 1;
        InputData();//입력받는 부분

        Solve();
        while (queue.front().order != ord) {
            ans++;
            queue.pop_front();
            Solve();
        }
        cout << ans << "\n";//출력하는 부분
    }
    return 0;
}

#endif

#if 0
/***********************************************************/
// [2-4] A9. 프린터 큐 : 강사님의 풀이
/***********************************************************/
#include <iostream>
#include <deque>

using namespace std;

struct JOB {
    int prio;
    int no;
};

int N, M;
deque<JOB> printer_queue;
int cnt_prio[10];

void Init(void) {
    printer_queue.clear();
    for (int i = 1; i <= 9; i++) cnt_prio[i] = 0;
}

void Input_Data(void) {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        JOB  temp;
        temp.no = i;
        cin >> temp.prio;
        printer_queue.push_back(temp);
        cnt_prio[temp.prio]++;
    }
}

int Simulation(void) {
    int cnt_print = 0;
    JOB j;
    for (int prio = 9; prio >= 1; prio--) {
        for (int i = 0; i < cnt_prio[prio]; i++) {
            for (;;) {
                j = printer_queue.front(); printer_queue.pop_front();
                if (j.prio == prio) break;
                printer_queue.push_back(j);
            }
            cnt_print++;
            if (j.no == M) return cnt_print;
        }
    }

    return -1;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        Init();
        Input_Data();

        cout << Simulation() << '\n';
    }
    return 0;
}

#endif

#if 0
/***********************************************************/
// [2-5] A10. 히스토그램에서 가장 큰 직사각형 : 나의 풀이 - 불쾌한 날 문제와 달리 왼쪽이 더 커도 투과할 수 있다.
/***********************************************************/
#include <iostream>
#include <deque>

using namespace std;

#define MAX_N (100000)

struct DATA {
    int h;
    int order;
};

int N;//히스토그램수
int height[MAX_N + 10]; //히스토그램 높이
deque<DATA> stk;

bool InputData() {
    cin >> N;
    if (N == 0) return false;

    for (int i = 0; i < N; i++) {
        cin >> height[i];
    }
    return true;
}

long long Solve(void) {
    long long sol = 0;
    stk.clear();

    long long area = 0;
    for (int i = 0; i < N; i++) {
        DATA newdata = { height[i], i };
        while (!stk.empty() && stk.back().h >= height[i]) {
            newdata.order = stk.back().order; // 왼쪽을 보는 코드 (왼쪽이 더 크면 왼쪽의 시작 인덱스를 나의 시작 인덱스로)
            area = (long long)(i - stk.back().order) * stk.back().h; // (long long으로 타입 캐스팅을 안해주면 틀린다.)
            sol = sol > area ? sol : area;
            stk.pop_back();
        }
        stk.push_back(newdata);
    }
    while (!stk.empty()) {
        area = (long long)(N - stk.back().order) * stk.back().h;
        sol = sol > area ? sol : area;
        stk.pop_back();
    }

    return sol;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (InputData()) {
        cout << Solve() << '\n';
    }

    return 0;
}

#endif

#if 0
/***********************************************************/
// [2-5] A10. 히스토그램에서 가장 큰 직사각형 : 강사님의 풀이
/***********************************************************/
#include <iostream>
#include <deque>

using namespace std;

#define MAX_N (100000)

struct INFO {
    int h;
    int s;
};

int N;
int height[MAX_N];
deque<INFO> stk;

int Input_Data(void) {
    cin >> N;
    if (N == 0) return 0;
    for (int i = 0; i < N; i++) {
        cin >> height[i];
    }
    return 1;
}

long long Solve(void) {
    long long max_area = 0;
    for (int i = 0; i < N; i++) {
        INFO info = { height[i], i };
        while (!stk.empty() && stk.back().h >= info.h) {
            info.s = stk.back().s;
            long long area = (long long)stk.back().h * (i - stk.back().s);
            if (max_area < area) max_area = area;
            stk.pop_back();
        }
        stk.push_back(info);
    }

    while (!stk.empty()) {
        long long area = (long long)stk.back().h * (N - stk.back().s);
        if (max_area < area) max_area = area;
        stk.pop_back();
    }
    return max_area;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (Input_Data()) {
        cout << Solve() << '\n';
    }

    return 0;
}

#endif

#if 0
/***********************************************************/
// [3-1] B1. 도약 : 나의 풀이 - Binary Search
/***********************************************************/
#include <iostream>
#include <algorithm>

using namespace std;
int N, cnt;
int lotus[1001];

int lower_bound(int s, int e, int dist) {
    int mid, idx;
    idx = 0;
    while (s <= e) {
        mid = (s + e) / 2;
        if (lotus[mid] >= dist) {
            idx = mid;
            e = mid - 1;
        }
        else {
            s = mid + 1;
        }
    }
    return idx;
}

int upper_bound(int s, int e, int dist) {
    int mid, idx;
    idx = 0;
    while (s <= e) {
        mid = (s + e) / 2;
        if (lotus[mid] <= dist) {
            idx = mid;
            s = mid + 1;
        }
        else {
            e = mid - 1;
        }
    }
    return idx;
}

void Solve() {
    cnt = 0;
    int lidx, uidx, dist;
    for (int i = 0; i < N - 2; i++) {
        for (int j = i + 1; j < N - 1; j++) {
            dist = lotus[j] - lotus[i];
            lidx = lower_bound(j + 1, N - 1, lotus[j] + dist);
            uidx = upper_bound(j + 1, N - 1, lotus[j] + 2 * dist);
            if (uidx && lidx && uidx - lidx >= 0) {
                cnt += (uidx - lidx + 1);
            } // else break;를 넣어서 계속 틀렸었음
        }
    }
}

void Input_Data() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> lotus[i];
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    sort(lotus, lotus + N);
    Solve();

    cout << cnt << '\n';


    return 0;
}

#endif

#if 0
/***********************************************************/
// [3-1] B1. 도약 : 강사님의 풀이 - Binary Search
/***********************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N (1000)

int N;
int pos[MAX_N];

void Input_Data(void) {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> pos[i];
    }
}

int Solve_N3(void) {
    int cnt = 0;

    // 연잎 위치 오름차순 정렬 (pos[i], pos[i+1] 비교시 무조건 pos[i+1]이 더 오른쪽 연잎)
    sort(pos, pos + N);

    for (int s1 = 0; s1 < N - 2; s1++) { // 첫번째 연잎 index 선택
        for (int s2 = s1 + 1; s2 < N - 1; s2++) { // 두번째 연잎 index 선택
            int dist = pos[s2] - pos[s1];
            int rs = pos[s2] + dist;
            int re = pos[s2] + 2 * dist;
            for (int s3 = s2 + 1; s3 < N; s3++) { //세번째 연잎 index 선택
                if (rs <= pos[s3] && pos[s3] <= re) cnt++;
            }
        }
    }
    return cnt;
}

int Binary_Search_Lower(int s, int e, int d) {
    int sol = -1;
    while (s <= e) {
        int m = (s + e) / 2;
        if (pos[m] >= d) {
            sol = m;
            e = m - 1;
        }
        else s = m + 1;
    }
    return sol;
}

int Binary_Search_Upper(int s, int e, int d) {
    int sol = -1;
    while (s <= e) {
        int m = (s + e) / 2;
        if (pos[m] <= d) {
            sol = m;
            s = m + 1;
        }
        else e = m - 1;
    }
    return sol;
}

int Solve(void) {
    int cnt = 0;

    // 연잎 위치 오름차순 정렬 (pos[i], pos[i+1] 비교시 무조건 pos[i+1]이 더 오른쪽 연잎)
    sort(pos, pos + N);

    for (int s1 = 0; s1 < N - 2; s1++) { // 첫번째 연잎 index 선택
        for (int s2 = s1 + 1; s2 < N - 1; s2++) { // 두번째 연잎 index 선택
            int dist = pos[s2] - pos[s1];
            int rs = pos[s2] + dist;
            int re = pos[s2] + 2 * dist;
            int lower = Binary_Search_Lower(s2 + 1, N - 1, rs);
            if (lower != -1 && pos[lower] <= re) {
                int upper = Binary_Search_Upper(lower, N - 1, re);
                cnt += (upper - lower + 1);
            }
        }
    }
    return cnt;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    //cout << Solve_N3() << '\n';
    cout << Solve() << '\n';

    return 0;
}

#endif

#if 0
/***********************************************************/
// [3-2] B2. 사냥꾼
/***********************************************************/
#include <iostream>
#include <algorithm>

using namespace std;
int M, N, L, maxN, minN, cnt;
int sade[100001];

int lower_bound(int s, int e, int dist) {
    int mid, idx;
    idx = 0;
    while (s <= e) {
        mid = (s + e) / 2;
        if (sade[mid] >= dist) {
            idx = mid;
            e = mid - 1;
        }
        else {
            s = mid + 1;
        }
    }
    return idx;
}

int upper_bound(int s, int e, int dist) {
    int mid, idx;
    idx = 0;
    while (s <= e) {
        mid = (s + e) / 2;
        if (sade[mid] <= dist) {
            idx = mid;
            s = mid + 1;
        }
        else {
            e = mid - 1;
        }
    }
    return idx;
}

void Solve(int x, int y) {
    int lidx = lower_bound(0, M - 1, x);
    int uidx = upper_bound(0, M - 1, x);
    if (abs(sade[lidx] - x) + y <= L || abs(sade[uidx] - x) + y <= L) cnt++;
}

void Input_Data() {
    int x, y;
    cnt = 0;

    cin >> M >> N >> L;
    for (int i = 0; i < M; i++) {
        cin >> sade[i];
    }
    sort(sade, sade + M);
    maxN = sade[M - 1], minN = sade[0];

    for (int i = 0; i < N; i++) {
        cin >> x >> y;
        if (y <= L) Solve(x, y);
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    cout << cnt << '\n';


    return 0;
}

#endif

#if 0
/***********************************************************/
// [2-1] A6. 사냥꾼 : 강사님의 풀이
/***********************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_M ((int)1e5)
#define MAX_N ((int)1e5)

int M, N, L;//사대수, 동물수, 사거리
int shoot[MAX_M];
struct POS {
    int x;
    int y;
};
POS animal[MAX_N];

void InputData() {
    cin >> M >> N >> L;
    for (int i = 0; i < M; i++) {
        cin >> shoot[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> animal[i].x >> animal[i].y;
    }
}

int BS_Lower(int s, int e, int d) {//d보다 크거나 같은 값중에 제일 작은 인덱스
    int sol = -1;
    while (s <= e) {
        int m = (s + e) / 2;
        if (shoot[m] >= d) {
            sol = m; e = m - 1;
        }
        else {
            s = m + 1;
        }
    }
    return sol;
}

int Solve() {
    int cnt = 0;

    //1.사대 오름차순 정렬
    sort(shoot, shoot + M);

    //2.동물 기준으로 탐색
    for (int i = 0; i < N; i++) {
        if (animal[i].y > L) continue; //무조건 못잡음
        int rs = animal[i].x - (L - animal[i].y);
        int re = animal[i].x + (L - animal[i].y);
        int idx = BS_Lower(0, M - 1, rs);
        if ((idx < 0) || (shoot[idx] > re)) continue; //못잡음
        cnt++;
    }

    return cnt;
}

int main() {
    InputData();
    int ans = Solve();
    cout << ans << endl;// 출력하는 부분
    return 0;
}

#endif

#if 0
/***********************************************************/
// [3-3] B3. 예산 : 나의 풀이
/***********************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

int N, limit;
int req[10001];
long long reqSum[10001];

int upper_bound(int s, int e, int target) {
    int mid, idx;
    idx = -1;
    while (s <= e) {
        mid = (s + e) / 2;
        if (req[mid] <= target) {
            idx = mid;
            s = mid + 1;
        }
        else {
            e = mid - 1;
        }
    }
    return idx;
}

long long calc(int idx, int mon) { // 상한액이 mon일 때 필요한 예산
    if (idx == -1) return mon * N;
    else return reqSum[idx] + mon * (N - idx - 1);
}

int Solve(int s, int e) {
    int mid, idx, money;
    money = 0;
    while (s <= e) {
        mid = (s + e) / 2;
        idx = upper_bound(0, N - 1, mid);
        if (calc(idx, mid) <= (long long)limit) {
            money = mid;
            s = mid + 1;
        }
        else {
            e = mid - 1;
        }
    }
    return money;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for (int i = 0; i < N; i++) cin >> req[i];
    cin >> limit;

    sort(req, req + N);

    reqSum[0] = req[0];
    for (int i = 1; i < N; i++) reqSum[i] = reqSum[i - 1] + req[i];

    cout << Solve(1, req[N - 1]) << '\n';


    return 0;
}

#endif

#if 0
/***********************************************************/
//  [3-3] B3. 예산 : 강사님의 풀이 - Parametric Search
/***********************************************************/
#include <iostream>

using namespace std;

#define MAX_N (10000)

int N;
int req[MAX_N];
int M;
int max_req;


void Input_Data(void) {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> req[i];
        if (max_req < req[i]) max_req = req[i];
    }
    cin >> M;
}

bool Check(int limit) {
    int budget = M;
    for (int i = 0; i < N; i++) {
        if (req[i] > limit) budget -= limit;
        else budget -= req[i];
    }
    return budget >= 0;
}

int Solve(void) {
    int sol = -1;
    int s = 0, e = max_req;
    while (s <= e) {
        int m = (s + e) / 2;
        if (Check(m)) {
            sol = m;
            s = m + 1;
        }
        else e = m - 1;
    }
    return sol;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    cout << Solve() << '\n';

    return 0;
}

#endif

#if 0
/***********************************************************/
// [3-4] B4. 어민 : 강사님의 풀이 - Parametric Search
/***********************************************************/
#include <iostream>

using namespace std;

#define MAX_N (100000)

struct TOWN {
    int pos;
    int fish;
};

int N;
TOWN town[MAX_N];
int min_fish = 0x7fffffff;
int max_fish;


void Input_Data(void) {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> town[i].pos >> town[i].fish;
        if (min_fish > town[i].fish) min_fish = town[i].fish;
        if (max_fish < town[i].fish) max_fish = town[i].fish;
    }
}

bool Check(int child) { // 부족하면 오른쪽 마을에서 빌려오고, 남으면 오른쪽 마을로 보내준다.
    long long c = 0;
    for (int i = 0; i < N - 1; i++) {
        long long remain = town[i].fish + c - child;
        c = remain - (town[i + 1].pos - town[i].pos); // remain - 거리(세금)
        if (remain >= 0 && c < 0) c = 0; // 남는건 있지만 거리가 멀어 안 주는게 나은 상황
    }
    return town[N - 1].fish + c >= child;
}

int Solve(void) {
    int s = min_fish, e = max_fish;
    int sol = -1;
    while (s <= e) {
        int m = (s + e) / 2;
        if (Check(m)) {
            sol = m;
            s = m + 1;
        }
        else e = m - 1;
}
    return sol;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    cout << Solve() << '\n';

    return 0;
}

#endif

#if 0
/***********************************************************/
// [3-5] B5. 사회적 거리두기
/***********************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_M (100000)

int N, M;

struct INTERVAL {
    long long s, e;
    bool operator<(const INTERVAL& d) {
        return s < d.s;
    }
};

INTERVAL interval[MAX_M];

void Input_Data(void) {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        cin >> interval[i].s >> interval[i].e;
    }
}

/*
// 소 기반 루프
bool Check(long long d) {
    long long last = interval[0].s; // 이전 소의 인덱스
    int idx = 0; // 잔디의 인덱스
    for (int i = 0; i < N - 1; i++) {
        last += d;
        while (idx < M && interval[idx].e < last) idx++;
        if (idx == M) return false;
        if (last < interval[idx].s) last = interval[idx].s;
    }
    return true;
}
*/

/*
// 잔디 기반 루프
bool Check(long long d) {
    long long cow_pos = -1;
    int cnt_cow = 0;
    for (int i = 0; i < M; i++) {
        if (cow_pos < interval[i].s) cow_pos = interval[i].s;
        while (cow_pos <= interval[i].e) {
            cnt_cow++;
            if (cnt_cow >= N) return true;
            cow_pos += d;
        }
    }
    return false;
}
*/


// 잔디 기반 루프 - 잔디 내 세울 수 있는 소의 수 연산
bool Check(long long d) {
    long long cow_pos = -1;
    int cnt_cow = 0;
    for (int i = 0; i < M; i++) {
        if (cow_pos < interval[i].s) cow_pos = interval[i].s;
        if (cow_pos > interval[i].e) continue;
        long long width = interval[i].e - cow_pos;
        long long cnt = (width / d) + 1;
        cnt_cow += cnt;
        cow_pos += d * cnt;
        if (cnt_cow >= N) return true;
    }
    return false;
}

long long Solve(void) {
    long long sol = -1;
    long long s, e;
    sort(interval, interval + M);
    s = 1; e = (interval[M - 1].e - interval[0].s) / (N - 1);

    while (s <= e) {
        long long m = (s + e) / 2;
        if (Check(m)) {
            sol = m;
            s = m + 1;
        }
        else e = m - 1;
    }
    return sol;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    cout << Solve() << '\n';

    return 0;
}

#endif

#if 0
/***********************************************************/
// [4-1] B6. 에디터 : 나의 풀이
/***********************************************************/
#include <iostream>
#include <list>

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    list<char> LL;
    list<char>::iterator cursor;
    string word;
    int N;
    char com, alpha;

    cin >> word;
    for (char c : word) {
        LL.push_back(c);
    }

    cin >> N;
    cursor = LL.end();
    for (int i = 0; i < N; i++) {
        cin >> com;
        if (com == 'L') {
            if (cursor != LL.begin()) cursor--;
        }
        else if (com == 'D') {
            if (cursor != LL.end()) cursor++;
        }
        else if (com == 'B') {
            if (cursor != LL.begin()) cursor = LL.erase(prev(cursor));
        }
        else {
            cin >> alpha;
            LL.insert(cursor, alpha);
        }
    }

    for (auto iter = LL.begin(); iter != LL.end(); iter++) cout << *iter;

    return 0;
}

#endif

#if 0
/***********************************************************/
// [4-1] B6. 에디터 : 강사님의 풀이
/***********************************************************/
#include <iostream>
#include <list>
#include <string>

using namespace std;

list<char> editor;
list<char>::iterator cursor;
string initstr;

void Init_Editor(void) {
    cin >> initstr;
    /*
    for (char ch: initstr) {
        editor.push_back(ch);
    }*/
    editor = list<char>(initstr.begin(), initstr.end());
    cursor = editor.end();
}

void Move_Left(void) {
    if (cursor != editor.begin()) cursor--;
}

void Move_Right(void) {
    if (cursor != editor.end()) cursor++;
}

void Delete_Char(void) {
    if (cursor == editor.begin()) return;
    editor.erase(prev(cursor));
}

void Insert_Char(char ch) {
    editor.insert(cursor, ch);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Init_Editor();

    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        char cmd;
        char ch;
        cin >> cmd;
        switch (cmd) {
        case 'L':
            Move_Left();
            break;
        case 'D':
            Move_Right();
            break;
        case 'B':
            Delete_Char();
            break;
        case 'P':
            cin >> ch;
            Insert_Char(ch);
            break;
        }
    }

    for (char ch : editor) {
        cout << ch;
    }

    return 0;
}

#endif


#if 0
/***********************************************************/
// [4-2] B7. 메모리 관리 함수 : 강사님의 풀이
/***********************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <list>

#define MAXN ((int)1e5)
#define MAXT ((int)1e3)

using namespace std;

#define MAX_HASH (26*26*26*26)

struct MEM {
    int s;
    int size;

    MEM* init(int s, int size) {
        this->s = s;
        this->size = size;
        return this;
    }
};

int cnt_mem;
MEM mem[MAXN + 1];

list<MEM*> memory;
MEM* ht[MAX_HASH];

int Get_Hash(string name) {
    int hash = 0;
    for (int i = 0; i < 4; i++) {
        hash = hash * 26 + (name[i] - 'a');
    }
    return hash;
}

MEM* Alloc_Memory(int size) {
    for (auto it = memory.begin(); it != memory.end(); it++) {
        if ((*it)->size >= size) {
            int s = (*it)->s;
            MEM* ret;
            if ((*it)->size == size) {
                ret = *it;
                memory.erase(it);
            }
            else {
                (*it)->s += size;
                (*it)->size -= size;

                ret = mem[cnt_mem++].init(s, size);
            }
            return ret;
        }
    }
    return (MEM*)0;
}

int N;//명령어 개수
void Init() {
    cnt_mem = 0;
    memory.clear();
    memory.push_back(mem[cnt_mem++].init(1, 100000));
}

void usermalloc(string name, int size) {
    MEM* m = Alloc_Memory(size);
    int hash = Get_Hash(name);
    ht[hash] = m;
}

void Free_Memory(MEM* m) {
    auto it = memory.begin();
    while (it != memory.end()) {
        if (m->s < (*it)->s) break;
        it++;
    }
    it = memory.insert(it, m);

    if (it != memory.begin()) {
        auto it_prev = prev(it);
        if ((*it_prev)->s + (*it_prev)->size == (*it)->s) {
            (*it)->s = (*it_prev)->s;
            (*it)->size += (*it_prev)->size;
            memory.erase(it_prev);
        }
    }

    auto it_next = next(it);
    if (it_next != memory.end() && (*it)->s + (*it)->size == (*it_next)->s) {
        (*it)->size += (*it_next)->size;
        memory.erase(it_next);
    }
}

void userfree(string name) {
    int hash = Get_Hash(name);
    if (ht[hash]) {
        Free_Memory(ht[hash]);
        ht[hash] = (MEM*)0;
    }
}

void userprint(string name) {
    int hash = Get_Hash(name);
    if (ht[hash]) cout << ht[hash]->s << '\n';
    else cout << "0\n";
}

void InputData() {
    cin >> N;
}

void Solve() {
    string cmd;
    string name;
    int size;
    for (int i = 1; i <= N; i++) {

        cin >> cmd;
        if (cmd[4] == '=') {//malloc 함수 baka=malloc(214);
            name = cmd.substr(0, 4); // 변수명 복사
            sscanf(&cmd[12], "%d", &size);
            usermalloc(name, size);
        }
        else if (cmd[0] == 'f') {//free 함수 free(baka);
            name = cmd.substr(5, 4); // 변수명 복사
            userfree(name);
        }
        else {//print 함수 print(deda);
            name = cmd.substr(6, 4); // 변수명 복사
            userprint(name);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Init();
    InputData();
    Solve();
    return 0;
}
#endif


#if 0
/***********************************************************/
// [4-3] B8. 개구리 공주 : 강사님의 풀이 
/***********************************************************/
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#define MAX_N (100000)
#define MAX_K (100000)

enum _DIR { A, B, C, D };

struct PLANTS {
    int x, y;
    int diff;
    int add;
    PLANTS* link[4];
};

int N, K;
PLANTS plants[MAX_N];
PLANTS* sorting[MAX_N];
string jump;

void Input_Data(void) {
    cin >> N >> K;
    cin >> jump;

    for (int i = 0; i < N; i++) {
        cin >> plants[i].x >> plants[i].y;
        plants[i].diff = plants[i].x - plants[i].y;
        plants[i].add = plants[i].x + plants[i].y;
        sorting[i] = &plants[i];
    }
}

// x + y 값으로 정렬을 했을 때 같으면 x 크기 순서대로 기울기 -1로 이어진다.
// y = -x + m 위에 있다 -> x + y가 같다.
bool comp_AD(PLANTS* p1, PLANTS* p2) {
    if (p1->diff == p2->diff) return p1->x < p2->x;
    return p1->diff < p2->diff;
}

// x - y 값으로 정렬을 했을 때 같으면 x 크기 순서대로 기울기 1로 이어진다.
// y = x + m 위에 있다 -> x - y가 같다.
bool comp_BC(PLANTS* p1, PLANTS* p2) {
    if (p1->add == p2->add) return p1->x < p2->x;
    return p1->add < p2->add;
}

void Make_Link(void) {
    sort(sorting, sorting + N, comp_AD);
    for (int i = 0; i < N - 1; i++) {
        // A(0),D(3) 연결 : i D<->A i+1
        if (sorting[i]->diff == sorting[i + 1]->diff) {
            sorting[i]->link[A] = sorting[i + 1];
            sorting[i + 1]->link[D] = sorting[i];
        }
    }

    sort(sorting, sorting + N, comp_BC);
    for (int i = 0; i < N - 1; i++) {
        // B(1),C(2) 연결 : i B<->C i+1
        if (sorting[i]->add == sorting[i + 1]->add) {
            sorting[i]->link[B] = sorting[i + 1];
            sorting[i + 1]->link[C] = sorting[i];
        }
    }
}

PLANTS* Process_Jump(void) {
    int i, j, dir;
    PLANTS* cur = &plants[0], * next;
    int dir_oppo[4] = { D,C,B,A };
    for (char dir : jump) {
        dir -= 'A';
        if (cur->link[dir]) {
            next = cur->link[dir];
            for (j = 0; j < 4; j++) {
                if (cur->link[j])
                    cur->link[j]->link[dir_oppo[j]] = cur->link[dir_oppo[j]];
            }
            cur = next;
        }
    }
    return cur;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    PLANTS* cur;
    Input_Data();

    Make_Link();

    cur = Process_Jump();
    cout << cur->x << ' ' << cur->y;

    return 0;
}

#endif

#if 0
/***********************************************************/
// [5-1] C0. 최소 비용으로 포장 다시 하기
/***********************************************************/
#include <iostream>
#include <queue>

using namespace std;
priority_queue<int, vector<int>, greater<int>> pq;
int N;

void Input_Data() {
    int candy;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> candy;
        pq.push(candy);
    }
}

int Solve() {
    int sum = 0;
    while (pq.size() != 1) {
        int first = pq.top();
        pq.pop();
        int second = pq.top();
        sum += (first + second);
        pq.pop();
        pq.push(first + second);
    }
    return sum;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    cout << Solve() << '\n';

    return 0;
}
#endif


#if 0
/***********************************************************/
// [5-1] C0. 최소 비용으로 포장 다시 하기 : 강사님의 풀이
/***********************************************************/
/*
// case 1 : 매번 전체 데이터 정렬 O(N^2logN)
#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N (5000)

int N;
int pac[MAX_N];

void Input_Data(void) {
    cin >> N;
    for (int i = 0; i < N;i++) {
        cin >> pac[i];
    }
}

int Solve(void) {
    int total_cost = 0;
    for (int i = 0; i < N - 1;i++) {
        sort(pac + i, pac + N);
        pac[i + 1] += pac[i];
        total_cost += pac[i + 1];
    }
    return total_cost;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    cout << Solve() << '\n';

    return 0;
}

*/


/*
// case 2 : 최소 전체 정렬 + 처리 과정에서 새로운 데이터 부분 정렬 O(NlogN + N^2)
#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N (5000)

int N;
int pac[MAX_N];

void Input_Data(void) {
    cin >> N;
    for (int i = 0; i < N;i++) {
        cin >> pac[i];
    }
}

int Solve(void) {
    int total_cost = 0;
    sort(pac, pac + N); // O(NlogN)
    for (int i = 0; i < N - 1;i++) {
        pac[i + 1] += pac[i];
        total_cost += pac[i + 1];

        int temp = pac[i + 1];
        int j;
        for (j = i + 1; j < N - 1;j++) {
            if (temp <= pac[j + 1]) break;
            else pac[j] = pac[j + 1];
        }
        pac[j] = temp;
    }
    return total_cost;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    cout << Solve() << '\n';

    return 0;
}
*/

// case 3 : Priority Queue 사용 O(NlogN)
#include <iostream>
#include <queue>

using namespace std;

#define MAX_N (5000)

int N;
priority_queue<int, vector<int>, greater<int>> pq;

void Input_Data(void) {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int p;
        cin >> p;
        pq.push(p);
    }
}

int Solve(void) {
    int total_cost = 0;
    for (int i = 0; i < N - 1; i++) {
        int wrap = pq.top(); pq.pop();
        wrap += pq.top(); pq.pop();
        pq.push(wrap);
        total_cost += wrap;
    }
    return total_cost;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    cout << Solve() << '\n';

    return 0;
}
#endif


#if 0
/***********************************************************/
// [5-2] C1. 중앙값 : 강사님 풀이
/***********************************************************/
// 두 그룹으로 나누어 작은 그룹이 항상 한 개 더 많게 넣는다.
// 작은 그룹에서 가장 큰 값이 중앙값
#include <iostream>
#include <queue>

using namespace std;

struct COMP {
    bool operator()(int a, int b) {
        return a > b;
    }
};

priority_queue<int> pq_small; // 작은 수 그룹, 크면 클수록 우선순위 높음
priority_queue<int, vector<int>, COMP> pq_big; // 큰 수 그룹, 작으면 작을수록 우선순위 높음

void Add_Data(int n) {
    if (pq_small.empty() || pq_small.top() > n) {
        pq_small.push(n);
        if (pq_small.size() > pq_big.size() + 1) {
            pq_big.push(pq_small.top());
            pq_small.pop();
        }
    }
    else {
        pq_big.push(n);
        if (pq_big.size() > pq_small.size()) {
            pq_small.push(pq_big.top());
            pq_big.pop();
        }
    }

}

int Get_Median(void) {
    return pq_small.top();
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;
    int n;
    cin >> n;
    Add_Data(n);
    cout << Get_Median() << '\n';
    N /= 2;
    for (int i = 0; i < N; i++) {
        int n1, n2;
        cin >> n1 >> n2;
        Add_Data(n1);
        Add_Data(n2);
        cout << Get_Median() << '\n';
    }
    return 0;
}
#endif


#if 0
/***********************************************************/
// [5-3] C2. 컴퓨터실
/***********************************************************/
#include <iostream>
#include <queue>

using namespace std;

struct DATA {
    int s;
    int e;
    int len;
    bool operator<(const DATA& t) const {
        return len != t.len ? len < t.len : s > t.s;
    }
};

priority_queue<DATA> pq;
priority_queue<int, vector<int>, greater<int>> allPq;
int M, N, Q;
int loc[300001];
int friends[100001];

int Solve() {
    DATA tg = pq.top();
    pq.pop();
    int start = tg.s;
    int end = tg.e;
    int newidx = (start + end) / 2;
    if (start < newidx) pq.push({ start, newidx - 1, newidx - start });
    if (end > newidx) pq.push({ newidx + 1, end, end - newidx });

    return newidx;
}

void clean() {
    int idxS = 1;
    int idxE = M + 1;
    while (!allPq.empty()) {
        idxE = allPq.top();
        allPq.pop();
        if (idxS == idxE) idxS += 1;
        if (idxS < idxE) {
            pq.push({ idxS, idxE - 1, idxE - idxS });
            idxS = idxE + 1;
        }
    }
    if (idxE < M) pq.push({ idxS, M, M - idxS + 1 });
    else if (idxE == M + 1) pq.push({ 1, M, M });
}

void Input_Data() {
    cin >> M >> N >> Q;
    for (int i = 1; i <= N; i++) {
        cin >> loc[i];
        allPq.push(loc[i]);
    }
    clean();
    for (int i = 0; i < Q; i++) cin >> friends[i];
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    for (int i = N + 1; i <= M; i++) loc[i] = Solve();

    for (int i = 0; i < Q; i++) cout << loc[friends[i]] << "\n";

    return 0;
}

#endif


#if 0
/***********************************************************/
// [5-3] C2. 컴퓨터실 : 강사님 풀이
/***********************************************************/
#include <iostream>
#include <queue>

using namespace std;

#define MAX_N (100000)
#define MAX_M (300000)
#define MAX_Q (100000)

struct GROUP {
    int s;
    int e;
    int size;
};

struct COMP {
    bool operator()(const GROUP& a, const GROUP& b) {
        if (a.size == b.size) return a.s > b.s;
        else return a.size < b.size;
    }
};

int M, N, Q;
int A[MAX_M + 1];
int B[MAX_Q];

int cnt_group;

priority_queue<GROUP, vector<GROUP>, COMP> pq;
inline int Get_Size(int s, int e) {
    return e - s + 1;
}


void Input_Data_And_Init(void) {
    cin >> M >> N >> Q;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        int size = Get_Size(A[i - 1] + 1, A[i] - 1);
        if (size > 0) {
            pq.push({ A[i - 1] + 1, A[i] - 1, size });
        }
    }
    if (M - A[N] != 0) {
        pq.push({ A[N] + 1, M , Get_Size(A[N] + 1, M) });
    }
    for (int i = 0; i < Q; i++) {
        cin >> B[i];
    }
}

void Simulation(void) {
    for (int i = N + 1; i <= M; i++) {
        GROUP g = pq.top(); pq.pop();
        A[i] = (g.s + g.e) / 2;

        // 쪼개진 왼쪽 그룹 : g.s ~ A[i]-1
        int size = Get_Size(g.s, A[i] - 1);
        if (size > 0) {
            pq.push({ g.s, A[i] - 1, size });
        }

        // 쪼개진 오른쪽 그룹 : A[i]+1, g.e
        size = Get_Size(A[i] + 1, g.e);
        if (size > 0) {
            pq.push({ A[i] + 1, g.e,size });
        }
    }
}

void Print_Result(void) {
    for (int i = 0; i < Q; i++) {
        cout << A[B[i]] << '\n';
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data_And_Init();

    Simulation();

    Print_Result();

    return 0;
}
#endif


#if 0
/***********************************************************/
// Test 1. 조깅
/***********************************************************/
#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, pos, vel, before;
    deque<int> stack;

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> pos >> vel;
        while (!stack.empty()) {
            before = stack.back();
            if (before > vel) stack.pop_back();
            else break;
        }
        stack.push_back(vel);
    }
    cout << stack.size();
}
#endif


#if 0
/***********************************************************/
// Test 2. 용돈 관리
/***********************************************************/
#include <iostream>

using namespace std;

#define MAX_N (100000)

int N, M;
int money[MAX_N + 1];
int maxN, sumN, add;


void Input_Data(void) {
    sumN = 0;
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> money[i];
        sumN += money[i];
        if (maxN < money[i]) maxN = money[i];
    }
}

int Check(int limit) {
    int popCnt, mon;

    mon = popCnt = add = 0;
    for (int i = 0; i < N; i++) {
        if (money[i] > mon) {
            popCnt += 1;
            mon = limit - money[i];
        }
        else {
            mon -= money[i];
            add += 1;
        }
    }
    return popCnt;
}

int Solve(void) {
    int sol = -1;
    int s = maxN, e = sumN;
    while (s <= e) {
        int m = (s + e) / 2;
        int trys = Check(m);
        if (trys <= M && trys + add > M) {
            sol = m;
            e = m - 1;
        }
        else {
            s = m + 1;
        }
    }
    return sol;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    cout << Solve() << '\n';

    return 0;
}
#endif


#if 0
/***********************************************************/
// Test 3. 쇼핑왕 루이 : 강사님 풀이
/***********************************************************/
#include <iostream>
#include <queue>

using namespace std;

#define MAX_N (50000)

struct PROD {
    int id;
    int P;
    int C;
    bool sold;
};

int N, K;
long long M;
PROD prod[MAX_N];

struct COMP_P {
    bool operator( )(PROD* a, PROD* b) {
        return a->P > b->P;
    }
};

struct COMP_C {
    bool operator()(PROD* a, PROD* b) {
        return a->C > b->C;
    }
};

struct COMP_DIFF {
    bool operator()(int a, int b) {
        return a > b;
    }
};

priority_queue<PROD*, vector<PROD*>, COMP_P> pq_P;
priority_queue<PROD*, vector<PROD*>, COMP_C> pq_C;
priority_queue<int, vector<int>, COMP_DIFF> pq_benefit;

void Input_Data(void) {
    cin >> N >> K >> M;
    for (int i = 0; i < N; i++) {
        cin >> prod[i].P >> prod[i].C;
        prod[i].id = i;
        pq_P.push(&prod[i]);
        pq_C.push(&prod[i]);
    }
}

int Solve(void) {
    int cnt = 0;
    for (int k = 0; k < K; k++) {
        pq_benefit.push(0);
    }

    while (M > 0) {
        while (!pq_P.empty() && pq_P.top()->sold) pq_P.pop();
        PROD* prod_P = pq_P.empty() ? (PROD*)0 : pq_P.top();

        while (!pq_C.empty() && pq_C.top()->sold) pq_C.pop();
        PROD* prod_C = pq_C.empty() ? (PROD*)0 : pq_C.top();
        int benefit = pq_benefit.top();

        if ((prod_P == (PROD*)0) && (prod_C == (PROD*)0)) break;
        if (prod_P->P <= prod_C->C + benefit) {
            M -= prod_P->P;
            if (M < 0) break;
            prod_P->sold = true;
            pq_P.pop();
            cnt++;
        }
        else {
            M -= prod_C->C + benefit;
            if (M < 0) break;
            pq_benefit.pop();
            pq_benefit.push(prod_C->P - prod_C->C);
            prod_C->sold = true;
            pq_C.pop();
            cnt++;
        }
    }
    return cnt;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    cout << Solve() << '\n';

    return 0;
}
#endif

#if 0
/***********************************************************/
// [6-1]. C6. 회원관리
/***********************************************************/
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
unordered_map<string, int> hmap;
int totalCnt;
int loginCnt;

void UserInit() {
    hmap.clear();
    totalCnt = loginCnt = 0;
}

int ChkJoin(string name) {
    auto it = hmap.find(name);
    if (it != hmap.end()) return 1;
    return 0;
}

int ChkLogin(string name) {
    auto it = hmap.find(name);
    if (it != hmap.end()) {
        if (it->second == 1) return 1;
    }
    return 0;
}

int Joining(string name) {
    auto it = hmap.find(name);
    if (it == hmap.end()) {
        hmap.insert({ name, 0 });
        totalCnt++;
    }
    return totalCnt;
}

int DeleteJoin(string name) {
    auto it = hmap.find(name);
    if (it != hmap.end()) {
        if (it->second == 1) loginCnt--;
        hmap.erase(it);
        totalCnt--;
    }
    return totalCnt;
}

int Login(string name) {
    auto it = hmap.find(name);
    if (it != hmap.end()) {
        if (it->second == 0) {
            hmap[name] = 1;
            loginCnt++;
        }
    }
    return loginCnt;
}

int Logout(string name) {
    auto it = hmap.find(name);
    if (it != hmap.end()) {
        if (it->second == 1) {
            hmap[name] = 0;
            loginCnt--;
        }
    }
    return loginCnt;
}

int main(void) {
    int N;//명령개수
    int cmd;
    string name;

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    UserInit();
    for (int i = 0; i < N; i++) {
        cin >> cmd >> name;
        switch (cmd) {
        case 1://가입유무
            cout << ChkJoin(name) << "\n";
            break;
        case 2://로그인유무
            cout << ChkLogin(name) << "\n";
            break;
        case 3:
            cout << Joining(name) << "\n";
            break;
        case 4:
            cout << DeleteJoin(name) << "\n";
            break;
        case 5:
            cout << Login(name) << "\n";
            break;
        case 6:
            cout << Logout(name) << "\n";
        }
    }
    return 0;
}
#endif


#if 0
/***********************************************************/
// [6-1]. C6. 회원관리 : 강사님의 풀이
/***********************************************************/
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, bool> ht;
int cnt_login;

void UserInit() {
    ht.clear();
    cnt_login = 0;
}

int ChkJoin(string name) {
    auto iter = ht.find(name);
    return iter != ht.end();
}

int ChkLogin(string name) {
    auto iter = ht.find(name);
    return iter != ht.end() && iter->second;
}

int Joining(string name) {
    auto iter = ht.find(name);
    if (iter == ht.end()) {
        ht.insert({ name, false });
    }
    return ht.size();
}

int DeleteJoin(string name) {
    auto iter = ht.find(name);
    if (iter != ht.end()) {
        if (iter->second) cnt_login--;
        ht.erase(iter);
    }
    return ht.size();
}

int Login(string name) {
    auto iter = ht.find(name);
    if (iter != ht.end()) {
        if (!iter->second) {
            iter->second = true;
            cnt_login++;
        }
    }
    return cnt_login;
}

int Logout(string name) {
    auto iter = ht.find(name);
    if (iter != ht.end()) {
        if (iter->second) {
            iter->second = false;
            cnt_login--;
        }
    }
    return cnt_login;
}

int main(void) {
    int N;//명령개수
    int cmd;
    string name;

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    UserInit();
    for (int i = 0; i < N; i++) {
        cin >> cmd >> name;
        switch (cmd) {
        case 1://가입유무
            cout << ChkJoin(name) << "\n";
            break;
        case 2://로그인유무
            cout << ChkLogin(name) << "\n";
            break;
        case 3:
            cout << Joining(name) << "\n";
            break;
        case 4:
            cout << DeleteJoin(name) << "\n";
            break;
        case 5:
            cout << Login(name) << "\n";
            break;
        case 6:
            cout << Logout(name) << "\n";
        }
    }
    return 0;
}
#endif


#if 0
/***********************************************************/
// [6-2]. C7. 암소 라인업
/***********************************************************/
#include <iostream>
#include <unordered_map>
#include <algorithm>

struct DATA {
    int xLoc;
    int id;
    bool operator<(const DATA& t) const {
        return xLoc < t.xLoc;
    }
};

#define MAX_N (50000)

using namespace std;
unordered_map<int, int> hmap;

DATA pos[MAX_N + 1];

int main(void)
{
    int N, maxCnt, cnt, sol, k;

    k = cnt = 0;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> pos[i].xLoc >> pos[i].id;
    }
    sort(pos, pos + N);

    sol = pos[N - 1].xLoc - pos[0].xLoc;
    for (int i = 0; i < N; i++) {
        auto it = hmap.find(pos[i].id);
        if (it == hmap.end()) hmap.insert({ pos[i].id, 0 });
    }
    maxCnt = hmap.size();

    int j = 0;
    for (int i = 0; i < N; i++) {
        while (j < N && cnt < maxCnt) {
            hmap[pos[j].id]++;
            if (hmap[pos[j].id] == 1) cnt++;
            j++;
        }
        if (cnt < maxCnt) break;
        sol = sol < pos[j - 1].xLoc - pos[i].xLoc ? sol : pos[j - 1].xLoc - pos[i].xLoc;
        hmap[pos[i].id]--;
        if (hmap[pos[i].id] == 0) cnt--;
    }
    cout << sol;
    return 1;
}
#endif


#if 0
/***********************************************************/
// [6-2]. C7. 암소 라인업 : 강사님의 풀이
/***********************************************************/
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define MAX_N (50000)

struct COW {
    int pos;
    int id;
};


int N;
COW cow[MAX_N];
unordered_map<int, int> cnt_cow;

bool comp(COW& a, COW& b) {
    return a.pos < b.pos;
}


void Input_Data(void) {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> cow[i].pos >> cow[i].id;
        if (cnt_cow.find(cow[i].id) == cnt_cow.end()) {
            cnt_cow.insert({ cow[i].id, 0 });
        }
    }
}

int Solve(void) {
    int range, min_range = 0x7fffffff; // int에서 정의할 수 있는 max값
    int cnt = 0;
    int total = cnt_cow.size();
    int e = 0;
    sort(cow, cow + N, comp);

    for (int s = 0; s < N; s++) {
        while (e < N && cnt < total) {
            auto iter = cnt_cow.find(cow[e].id);
            iter->second++;
            if (iter->second == 1) cnt++;
            e++;
        }

        if (e == N && cnt < total) break;

        //s ~ e-1
        range = cow[e - 1].pos - cow[s].pos;
        if (min_range > range) min_range = range;

        auto iter = cnt_cow.find(cow[s].id);
        iter->second--;
        if (iter->second == 0) cnt--;
    }
    return min_range;
}



int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    cout << Solve() << '\n';

    return 0;
}
#endif


#if 0
/***********************************************************/
// [6-3]. C8. UNIQUENESS2 : 들어온 순서대로 출력해야함
/***********************************************************/
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;
unordered_map<string, vector<int>> hmap;

int main(void)
{
    int N;
    string name;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> name;
        auto it = hmap.find(name);
        if (it != hmap.end()) {
            hmap[name].push_back(i + 1);
        }
        else {
            hmap.insert({ name, vector<int>(0) });
            hmap[name].push_back(i + 1);
        }
    }
    int flag = 1;
    for (auto it = hmap.begin(); it != hmap.end(); it++) {
        if (hmap[it->first].size() > 1) {
            flag = 0;
            cout << it->first << " ";
            for (int i = 0; i < hmap[it->first].size(); i++) {
                cout << it->second[i] << " ";
            }
            cout << "\n";
        }
    }
    if (flag) cout << "unique";

    return 0;
}
#endif


#if 0
/***********************************************************/
// [6-3]. C8. UNIQUENESS2 : 강사님의 풀이
/***********************************************************/
#include <iostream>
#include <list>
#include <unordered_map>
#include <string>

#define MAX_N (100000)

using namespace std;

int N;

unordered_map<string, int> words;
struct WORDINFO {
    string word;
    list<int> l;
};

int idx_info;
WORDINFO wordinfo[MAX_N];

void Input_Data(void) {
    string word;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> word;
        auto it = words.find(word);
        if (it == words.end()) {
            words.insert({ word, idx_info });
            wordinfo[idx_info].word = word;
            wordinfo[idx_info].l.push_back(i);
            idx_info++;
        }
        else wordinfo[it->second].l.push_back(i);
    }
}

void Print_Output(void) {
    if (idx_info == N) cout << "unique\n";
    else
    {
        for (int i = 0; i < idx_info; i++) {
            WORDINFO& w = wordinfo[i];
            if (w.l.size() > 1) {
                cout << w.word << " ";
                for (int a : w.l) {
                    cout << a << " ";
                }
                cout << "\n";
            }
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();
    Print_Output();

    return 0;
}
#endif


#if 0
/***********************************************************/
// [6-4]. C9. Administrative Difficulties : 강사님의 풀이
/***********************************************************/
#include <iostream>
#include <unordered_map>
#include <string>
#include <map>

using namespace std;

#define MAX_CAR (500)

struct CAR {
    int p; //원가
    int q; // 초기 대여 비용
    int k; // 단위 거리당 비용
};

struct SPY {
    bool consistance; // 일관성 유지 여부 (true : 유지, false : X)
    CAR* car; // null pointer : 빌린 차량 없음!
    int sum_cost;
};

int N, M;
CAR car[MAX_CAR];
unordered_map<string, CAR*> ht_car;
map<string, SPY> ht_spy;

void Init(void) {
    ht_car.clear();
    ht_spy.clear();
}

void Input_Car(void) {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        string name;
        cin >> name >> car[i].p >> car[i].q >> car[i].k;
        ht_car.insert({ name, &car[i] });
    }
}

void Process(void) {
    for (int m = 0; m < M; m++) {
        int t;
        string name_spy;
        char type_event;
        string name_car;
        int kilo;
        int perc;

        cin >> t >> name_spy >> type_event;
        auto it = ht_spy.find(name_spy);

        if (it == ht_spy.end()) { // 처음 등장!
            ht_spy.insert({ name_spy, {true, (CAR*)0, 0 } });
            it = ht_spy.find(name_spy);
        }
        SPY& spy = it->second;

        switch (type_event) {
        case 'p':
            cin >> name_car;
            if (spy.consistance == false) break;
            if (spy.car) {
                spy.consistance = false;
                break;
            }
            spy.car = ht_car[name_car];
            spy.sum_cost += spy.car->q;
            break;
        case 'r':
            cin >> kilo;
            if (spy.consistance == false) break;
            if (spy.car == (CAR*)0) {
                spy.consistance = false;
                break;
            }
            spy.sum_cost += kilo * spy.car->k;
            spy.car = (CAR*)0;
            break;
        case 'a':
            cin >> perc;
            if (spy.consistance == false) break;
            if (spy.car == (CAR*)0) {
                spy.consistance = false;
                break;
            }
            spy.sum_cost += (spy.car->p * perc + 99) / 100;
            break;
        }
    }
}

void Print_Result(void) {
    for (auto it = ht_spy.begin(); it != ht_spy.end(); it++) {
        if (it->second.consistance == false || it->second.car)
            cout << it->first << ' ' << "INCONSISTENT\n";
        else
            cout << it->first << ' ' << it->second.sum_cost << "\n";
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        Init();
        Input_Car();
        Process();
        Print_Result();
    }

    return 0;
}
#endif


#if 0
/***********************************************************/
// [7-1]. D0. 영화 블루레이 수집 : 나의 풀이
/***********************************************************/
#include <iostream>
using namespace std;

#define NUM_DATA	(200000)
#define MAX_TREE	(262144*2) // 262144 = 200000보다 큰 2의 제곱수 중 최솟값
#define LAST_NODE	(NUM_DATA*2-1)

int tree[MAX_TREE];
int pos[100000];

void Update_New_Data(int node, int s, int e, int idx, int data);
void Update_Add(int node, int s, int e, int us, int ue, int add);
int Query(int node, int s, int e, int qs, int qe);

#define PRINT_TREE {int j;printf("( ");	for(j=1;j<=LAST_NODE;j++){printf("%3d ",tree[j]);}printf(")\n");}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T, N, M, movie, newPos;
    cin >> T;
    while (T--) {
        cin >> N >> M;
        // Init
        for (int i = 1; i <= M; i++) Update_New_Data(1, 1, N + M, i, 0);
        for (int i = M + 1; i <= M + N; i++) Update_New_Data(1, 1, N + M, i, 1);
        for (int i = 1; i <= N; i++) pos[i] = M + i;

        //
        newPos = M;
        for (int i = 0; i < M; i++) {
            cin >> movie;
            cout << Query(1, 1, N + M, 1, pos[movie] - 1) << " ";
            // newPos는 1로, 원래 pos는 0으로
            Update_Add(1, 1, N + M, newPos, newPos, 1);
            Update_Add(1, 1, N + M, pos[movie], pos[movie], -1);
            pos[movie] = newPos;
            newPos--;
        }
        cout << "\n";
    }

    return 0;
}

void Update_New_Data(int node, int s, int e, int idx, int data) // node : node 번호, s ~ e : 구간, idx : 해당 노드에 들어갈 데이터의 인덱스 = leaf 노드만 봤을 때 인덱스
{
    int mid;
    if (s == e) { // 데이터 한개짜리 leaf node
        tree[node] = data;
        return;
    }
    // 왼쪽으로 내려갈까 오른쪽으로 내려갈까?
    mid = (s + e) / 2;
    if (idx <= mid) Update_New_Data(node * 2, s, mid, idx, data);
    else Update_New_Data(node * 2 + 1, mid + 1, e, idx, data);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int Query(int node, int s, int e, int qs, int qe) // 앞에 3개는 노드 정보, 뒤에 2개는 쿼리 정보
{
    int Lresult, Rresult;
    if (qs <= s && e <= qe) { // 노드 구간이 질문 구간의 내부 구간인가?     qs <-----> qe
        return tree[node]; // 해당 노드의 값 return								s <--> e
    }
    else if (e < qs || qe < s) { // 노드 구간과 질문 구간이 전혀 관계가 없다면?       qs <-----> qe
        return 0;	// 연산에 영향을 주지 않을만한 값 return				s <--> e		or		s <--> e
    }
    // 일부만 겹침										qs <-----> qe
    int mid = (s + e) / 2;						//	   s <--> e
    Lresult = Query(node * 2, s, mid, qs, qe); // s ~ mid와 쿼리 구간을 다시 비교
    Rresult = Query(node * 2 + 1, mid + 1, e, qs, qe); // mid + 1 ~ e와 쿼리 구간을 다시 비교
    return Lresult + Rresult;
}

void Update_Add(int node, int s, int e, int us, int ue, int add)
{
    if (e < us || ue < s) { // 노드 구간과 질문 구간이 전혀 관계가 없다면?       us <-----> ue
        return;													  //   s <--> e		or		s <--> e
    }
    if (s == e) { // 데이터 한개짜리 leaf node
        tree[node] += add;
        return;
    }
    // 위의 두개의 if문 순서를 바꾸면 s = 1, e = 1이 들어왔을 때 범위에 맞지 않는데도 +add가 된다.

    int mid = (s + e) / 2;
    Update_Add(node * 2, s, mid, us, ue, add);
    Update_Add(node * 2 + 1, mid + 1, e, us, ue, add);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

#endif


#if 0
/***********************************************************/
// [7-1]. D0. 영화 블루레이 수집 : 강사님의 풀이
/***********************************************************/
#include <iostream>
#include <iostream>

using namespace std;

#define MAX_TREE (1<<19)
#define MAX_N (100000)

int N, M;

int tree[MAX_TREE];
int pos_bluray[MAX_N + 1];


void Build_Tree(int node, int s, int e) {
    if (s == e) {
        tree[node] = s > M ? 1 : 0;
        return;
    }

    int m = (s + e) / 2;
    Build_Tree(node * 2, s, m);
    Build_Tree(node * 2 + 1, m + 1, e);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int Query(int node, int s, int e, int qs, int qe) {
    if (qs <= s && e <= qe) return tree[node];
    if (e < qs || qe < s) return 0;
    int m = (s + e) / 2;
    int l = Query(node * 2, s, m, qs, qe);
    int r = Query(node * 2 + 1, m + 1, e, qs, qe);
    return l + r;
}

void Update(int node, int s, int e, int idx, int data) {

    if (s == e) {
        tree[node] = data;
        return;
    }

    int m = (s + e) / 2;
    if (idx <= m) Update(node * 2, s, m, idx, data);
    else  Update(node * 2 + 1, m + 1, e, idx, data);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}


void Init(void) {
    Build_Tree(1, 1, M + N);
    for (int i = 1; i <= N; i++) {
        pos_bluray[i] = M + i;
    }
}

void Search_And_Move_Bluray(void) {
    for (int newpos = M; newpos >= 1; newpos--) {
        int b;
        cin >> b;
        cout << Query(1, 1, M + N, 1, pos_bluray[b] - 1) << ' ';
        Update(1, 1, M + N, pos_bluray[b], 0);
        pos_bluray[b] = newpos;
        Update(1, 1, M + N, pos_bluray[b], 1);
    }
    cout << '\n';
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T, t;

    cin >> T;
    for (t = 0; t < T; t++) {
        cin >> N >> M;
        Init();
        Search_And_Move_Bluray();
    }

    return 0;
}
#endif


#if 0
/***********************************************************/
// [7-2]. D1. 절호의 기회 : 강사님의 풀이 - LIS with Segment Tree
/***********************************************************/
#include <iostream>

#define MAX_N (1000000)
#define MAX_TREE (1<<18)

using namespace std;

int N, Q;
int max_num;
int num[MAX_N];
int tree[MAX_TREE];

void Input_Data(void) {
    int i;
    cin >> N;
    for (i = 0; i < N; i++) {
        cin >> num[i];
        if (max_num < num[i]) max_num = num[i];
    }
}

inline int MAX(int& A, int& B) {
    return A > B ? A : B;
}

int Query(int node, int rs, int re, int qs, int qe) {
    if (qs <= rs && re <= qe) return tree[node];
    if (re < qs || qe < rs) return 0;

    int m = (rs + re) / 2;
    int l = Query(node * 2, rs, m, qs, qe);
    int r = Query(node * 2 + 1, m + 1, re, qs, qe);

    return MAX(l, r);
}

void Update(int node, int rs, int re, int idx, int len) {
    if (rs == re) {
        tree[node] = len;
        return;
    }
    int m = (rs + re) / 2;
    if (idx <= m)
        Update(node * 2, rs, m, idx, len);
    else
        Update(node * 2 + 1, m + 1, re, idx, len);
    tree[node] = MAX(tree[node * 2], tree[node * 2 + 1]);
}


int Solve(void) {
    int i;
    int len;

    for (i = 0; i < N; i++) {
        len = Query(1, 0, max_num, 0, num[i] - 1) + 1;
        Update(1, 0, max_num, num[i], len);
    }

    return Query(1, 0, max_num, 0, max_num); // tree[1]도 같은 결과
}


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    cout << Solve() << '\n';

    return 0;
}
#endif

#if 0
/***********************************************************/
// [7-3]. D2. 스위치
/***********************************************************/
#include <iostream>

#define MAX_N (100000)
#define MAX_TREE (1<<18)

using namespace std;

int N, M;
int tree[MAX_TREE];
int lazy[MAX_TREE];

void Propagate(int node, int s, int e)
{
    if (lazy[node]) {
        if (s != e) { // 자식이 하나일 수는 없다! = 둘이거나 없거나
            lazy[node * 2] ^= 1;
            lazy[node * 2 + 1] ^= 1;
        }
        tree[node] = (e - s + 1) - tree[node];
        lazy[node] = 0;
    }
}

int Query(int node, int rs, int re, int qs, int qe) {
    Propagate(node, rs, re);
    if (qs <= rs && re <= qe) return tree[node];
    if (re < qs || qe < rs) return 0;

    int m = (rs + re) / 2;
    int l = Query(node * 2, rs, m, qs, qe);
    int r = Query(node * 2 + 1, m + 1, re, qs, qe);

    return l + r;
}

void Update(int node, int s, int e, int us, int ue) {
    Propagate(node, s, e);
    if (ue < s || e < us) return;
    if (us <= s && e <= ue) {
        lazy[node] ^= 1;
        Propagate(node, s, e);
        return;
    }

    int m = (s + e) / 2;
    Update(node * 2, s, m, us, ue);
    Update(node * 2 + 1, m + 1, e, us, ue);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void Input_Data(void) {
    int O, S, T;
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        cin >> O >> S >> T;
        if (!O) Update(1, 1, N, S, T);
        else {
            cout << Query(1, 1, N, S, T) << "\n";
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    return 0;
}
#endif

#if 0
/***********************************************************/
// [7-3]. D2. 스위치
/***********************************************************/
#include <iostream>

using namespace std;

#define MAX_N (100000)
#define MAX_TREE (1<<18)

int tree[MAX_TREE];
int lazy[MAX_TREE];

inline void Propagate(int node, int s, int e) {
    if (lazy[node]) {
        tree[node] = (e - s + 1) - tree[node];

        if (s != e) {
            lazy[node * 2] = !lazy[node * 2];
            lazy[node * 2 + 1] = !lazy[node * 2 + 1];
        }
        lazy[node] = 0;
    }
}

int Query(int node, int s, int e, int qs, int qe) {
    Propagate(node, s, e);

    if (qs <= s && e <= qe) return tree[node];
    if (qe < s || e < qs) return 0;

    int m = (s + e) / 2;
    int l = Query(node * 2, s, m, qs, qe);
    int r = Query(node * 2 + 1, m + 1, e, qs, qe);

    return l + r;
}

void Update(int node, int s, int e, int us, int ue) {
    Propagate(node, s, e);

    if (ue < s || e < us) return;
    if (us <= s && e <= ue) {
        lazy[node] = 1;
        Propagate(node, s, e);
        return;
    }
    int m = (s + e) / 2;
    Update(node * 2, s, m, us, ue);
    Update(node * 2 + 1, m + 1, e, us, ue);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int O, S, T;
    int N, Q;
    cin >> N >> Q;

    for (int i = 0; i < Q; i++) {
        cin >> O >> S >> T;
        switch (O) {
        case 0:
            Update(1, 1, N, S, T);
            break;
        case 1:
            cout << Query(1, 1, N, S, T) << '\n';
            break;
        }
    }

    return 0;
}
#endif


#if 0
/***********************************************************/
// [7-4]. D3. 미술평가 : 강사님의 풀이
/***********************************************************/
#include <iostream>

using namespace std;

#define MAX_N (100000)
#define MAX_TREE (1<<18)

int N;
int T[MAX_N + 1];

struct NODE {
    int id;
    int cnt;
};

NODE tree[MAX_TREE];
int lazy[MAX_TREE];

void Input_Data(void) {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> T[i];
    }
}

inline NODE& max(NODE& a, NODE& b) {
    return a.cnt >= b.cnt ? a : b;
}

void Build_Tree(int n, int s, int e) {
    int m;
    lazy[n] = 0;
    if (s == e) {
        tree[n].id = s;
        tree[n].cnt = 0;
        return;
    }
    m = (s + e) / 2;
    Build_Tree(n * 2, s, m);
    Build_Tree(n * 2 + 1, m + 1, e);
    tree[n] = max(tree[n * 2], tree[n * 2 + 1]);
}

void Propagation(int n, int s, int e) {
    if (lazy[n]) {
        tree[n].cnt += lazy[n];
        if (s != e) {
            lazy[n * 2] += lazy[n];
            lazy[n * 2 + 1] += lazy[n];
        }
        lazy[n] = 0;
    }
}

void Update(int n, int s, int e, int us, int ue) {
    int m;
    Propagation(n, s, e);
    if (us <= s && e <= ue) {
        lazy[n] += 1;
        Propagation(n, s, e);
        return;
    }
    if (ue < s || e < us) return;
    m = (s + e) / 2;
    Update(n * 2, s, m, us, ue);
    Update(n * 2 + 1, m + 1, e, us, ue);
    tree[n] = max(tree[n * 2], tree[n * 2 + 1]);
}

int Solve(void) {
    for (int i = 1; i <= N; i++) {
        if (T[i] >= N) continue;
        if (T[i] == 0) {
            Update(1, 1, N, 1, N);
        }
        else {
            int s = i % N + 1;
            int e = (i - 1 - T[i] + N) % N + 1;
            if (s <= e) {
                Update(1, 1, N, s, e);
            }
            else {
                Update(1, 1, N, s, N); Update(1, 1, N, 1, e);
            }
        }
    }
    return tree[1].id;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    Build_Tree(1, 1, N);

    cout << Solve() << '\n';
    return 0;
}
#endif

#if 1
/***********************************************************/
// [7-5]. D4. 아날로그 다이얼
/***********************************************************/
#include <iostream>
#include <string>

using namespace std;

#define MAX_N (250000)
#define MAX_M (100000)

#define MAX_TREE (1<<19)

struct Q {
    int A, B;
};

int N, M;
string init_dial;
Q q[MAX_M];

int tree[MAX_TREE][10]; // 해당 구간 다이얼의 특정 수 개수!
int lazy[MAX_TREE];
int res[10];


void Input_Data(void) {
    cin >> N >> M;
    cin >> init_dial;
    for (int i = 0; i < M; i++) {
        cin >> q[i].A >> q[i].B;
    }
}

void Merge(int n) {
    for (int i = 0; i < 10; i++) {
        tree[n][i] = tree[n * 2][i] + tree[n * 2 + 1][i];
    }
}

void Build_Tree(int n, int s, int e) {
    if (s == e) {
        tree[n][init_dial[s - 1] - '0'] = 1;
        return;
    }
    int m = (s + e) / 2;
    Build_Tree(n * 2, s, m);
    Build_Tree(n * 2 + 1, m + 1, e);

    Merge(n);
}

inline void Init_Res(void) {
    for (int i = 0; i < 10; i++) res[i] = 0;
}

inline void Rotate(int n, int r) {
    int tmp[10];
    for (int i = 0; i < 10; i++) {
        tmp[i] = tree[n][i];
    }
    for (int i = 0; i < 10; i++) {
        tree[n][(i + r) % 10] = tmp[i];
    }
}

void Propagate(int n, int s, int e) {
    if (lazy[n]) {
        Rotate(n, lazy[n]);
        if (s != e) {
            lazy[n * 2] += lazy[n];
            lazy[n * 2 + 1] += lazy[n];
        }
        lazy[n] = 0;
    }
}

void Query(int n, int s, int e, int qs, int qe) {
    Propagate(n, s, e);
    if (qs <= s && e <= qe) {
        for (int i = 0; i < 10; i++) {
            res[i] += tree[n][i];
        }
        return;
    }
    if (e < qs || qe < s) return;

    int m = (s + e) / 2;
    Query(n * 2, s, m, qs, qe);
    Query(n * 2 + 1, m + 1, e, qs, qe);
}

void Update(int n, int s, int e, int us, int ue) {
    Propagate(n, s, e);
    if (ue < s || e < us) return;
    if (us <= s && e <= ue) {
        lazy[n] += 1;
        Propagate(n, s, e);
        return;
    }

    int m = (s + e) / 2;
    Update(n * 2, s, m, us, ue);
    Update(n * 2 + 1, m + 1, e, us, ue);

    for (int i = 0; i < 10; i++) {
        tree[n][i] = tree[n * 2][i] + tree[n * 2 + 1][i];
    }
}

int Get_Sum_Res(void) {
    int sum = 0;
    for (int i = 1; i < 10; i++) {
        sum += i * res[i];
    }
    return sum;
}


void Solve(void) {
    Build_Tree(1, 1, N);

    for (int i = 0; i < M; i++) {
        Init_Res();
        Query(1, 1, N, q[i].A, q[i].B);
        cout << Get_Sum_Res() << '\n';
        Update(1, 1, N, q[i].A, q[i].B);
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input_Data();

    Solve();

    return 0;
}
#endif


#if 0
/***********************************************************/
// Test 1. 조깅 (Silver)
/***********************************************************/
/*
교장 선생님은 학생들의 체력을 위해 아침마다 조깅을 시키기로 했다.
무한히 긴 단일 트랙에서 N(1 <= N <= 100, 000)명의 학생들이 조깅 중이다.각 학생은 트랙의 별개의 위치에서 시작하고 조깅 속도는 같거나 다르다.
트랙에 차선이 하나 밖에 없기 때문에 다른 학생을 추월할 수 없다.그래서 더 빠른 학생이 다른 학생을 따라 잡았을 때, 느린 학생의 속도에 맞춰서 천천히 달릴 수 밖에 없다.
그래서 그 학생들은 같은 그룹이 되어 조깅하게 된다.
학생들은 T(1 <= T <= 1, 000, 000, 000)분 동안 뛰게 될 것이다.이 시간 동안 교장 선생님은 몇 개의 그룹이 만들어지는지 궁금하다.
데이터가 주어질 때 몇 그룹이 만들어지는지 구하는 프로그램을 작성하시오. (두 명의 학생이 T분이 끝날 때 같은 위치에 있다면 같은 그룹으로 간주합니다.)
*/

#include <iostream>
#include <queue>

using namespace std;

struct DATA {
    int pos;
    int vel;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, T, before_pos, before_vel, pos, vel;
    deque<DATA> stack;

    cin >> N >> T;
    for (int i = 0; i < N; i++) {
        cin >> pos >> vel;
        while (!stack.empty()) {
            before_pos = stack.back().pos;
            before_vel = stack.back().vel;
            if (before_vel > vel && (long long)before_pos + (long long)(before_vel - vel) * T >= (long long)pos) stack.pop_back();
            else break;
        }
        stack.push_back({ pos, vel });
    }
    cout << stack.size();
}
#endif

#if 0
/***********************************************************/
// Test 2. 투표
/***********************************************************/
/*
사내직원 인기투표가 진행되었다.M명의 직원이 인기 투표에 참여를 해서 N명의 후보 중 한 명을 선택해서 1 이상 10 이하의 점수를 주었다.
1~3등까지 뽑아서 상품을 주기로 하였다.투표에 참여한 M명은 후보자 N명 중 한 명의 이름과 1 이상 10 이하의 점수를 투표 용지에 적어서 제출한다.
그러면 직원 별 총점을 계산해서 가장 높은 점수를 받은 사람부터 차례대로 선정해서 1~3등을 선정하는 것이다.
만약 점수가 같은 경우에는 사번이 빠른 사람을 선택한다.(입력 순서가 사번 순임) 그런데 문제가 발생했다.
고의인지 실수인지 모르겠지만 투표 용지에 후보자 N명의 명단에 없는 이름들이 적혀있는 것이다.
어쩔 수 없이 후보자 명단에 없는 이름이 적힌 투표 용지는 무효 처리하기로 했다.
후보자 수 N과 후보자 명단, 투표 참가 인원 M과 투표 내용이 주어질 때, 1~3등을 찾으시오
*/
#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

struct DATA {
    int id;
    int score;
};
unordered_map<string, DATA> hmap;

struct idScore {
    string name;
    int id;
    int score;
};
struct COMP {
    bool operator()(idScore& x, idScore& y) {
        return x.score != y.score ? x.score < y.score : x.id > y.id;
    }
};
priority_queue<idScore, vector<idScore>, COMP> pq;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, score;
    string name;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> name;
        hmap.insert({ name, {i, 0} });
    }
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> name >> score;
        auto it = hmap.find(name);
        if (it != hmap.end()) hmap[name].score += score;
    }
    for (auto it = hmap.begin(); it != hmap.end(); it++) {
        pq.push({ it->first, it->second.id, it->second.score });
    }
    for (int i = 0; i < 3; i++) {
        cout << pq.top().name << " " << pq.top().score << "\n";
        pq.pop();
    }

    return 0;
}
#endif

#if 0
/***********************************************************/
// Test 3. 
/***********************************************************/
/*
나대충 감독은 N명으로 이뤄진 팀을 구성하려고 한다.총 100,000명의 선수가 있는데 이 중에서 N(1≤N≤50,000)명의 선수를 선발해야 한다.
선수들은 등번호 ID(1≤ID≤100,000)가 있는데 모두 고유한 번호가 있다.능력치를 나타내는 X(1≤X≤100,000)가 있는데
선수끼리 같은 능력치가 있을 수도 있고 다를 수도 있다.
초기에 N명의 선수들이 선발된 명단을 받았는데 나대충 감독 마음에 들지 않아서 일부 선수들을 교체해 보면서 완벽한 팀구성으로 하려고 한다.
교체하는 방법은 최소 능력치 선수, 또는 최대 능력치 선수, 또는 중간 능력치 선수를 빼고 다른 선수를 넣어보려고한다.
최소 능력치 선수가 여럿이 있을 경우 ID가 작은 선수를 선택한다.
최대 능력치 선수가 여럿이 있을 경우 ID가 큰 선수를 선택한다.
중간 능력치 선수는 N 명의 선수를 1순위 능력치 오름차순, 2순위 ID 오름차순으로 정렬했을 때 중간에 위치한 선수를 선택한다.
그런데 선수가 너무 많고 능력치가 다양해서 수작업으로는 힘들어서 당신에게 프로그램을 의뢰했다.
초기에 N명의 ID와 능력치 X가 입력되고 M개의 명령이 입력된다.
명령은 총 5가지이다.
1.    0명령은 최소 능력치 선수의 ID와 능력치를 출력하고 해당 선수를 제거한다.
2.    1명령은 최대 능력치 선수의 ID와 능력치를 출력하고 해당 선수를 제거한다.
3.    2명령은 중간 능력치 선수의 ID와 능력치를 출력하고 해당 선수를 제거한다.N명이 홀수 일 경우 N명을 정렬했을 때[(N + 1) / 2] 번째 선수이다.
N명이 짝수일 경우에는[N / 2], [N / 2 + 1] 번째 선수로 두명이고 순서대로 출력한다.
4.    3명령은 선수를 추가한다. 0~2 명령이 있은 후 항상 3명령이 들어온다. 2명령이 수행된 경우 두명을 선택해야하는 경우에는 3명령이 두 번 들어온다.
5.    4 명령은 N명을 정렬했을 때, N이 홀수이면[1]~[(N + 1) / 2] 까지 능력치 합과[(N + 1) / 2 + 1]~[N]까지 능력치 합을 공백으로 구분해서 출력한다.
N이 짝수일 경우[1]~[N / 2]까지 능력치 합과[N / 2 + 1]~[N]까지 능력치 합을 공백으로 구분해서 출력한다. (합은 int 범위를 벗어날 수 있음)
*/
#include <iostream>
#include <queue>

#define MAX_P (100000)
using namespace std;

struct DATA {
    int idx;
    int skill;
    bool isDeleted;

    DATA* init(int idx, int skill) {
        this->idx = idx;
        this->skill = skill;
        this->isDeleted = false;
        return this;
    }
};

struct MINCOMP {
    bool operator()(DATA* a, DATA* b) {
        return a->skill != b->skill ? a->skill < b->skill : a->idx < b->idx;
    }
};

struct MAXCOMP {
    bool operator()(DATA* a, DATA* b) const {
        return a->skill != b->skill ? a->skill > b->skill : a->idx > b->idx;
    }
};

priority_queue<DATA*, vector<DATA*>, MAXCOMP> minPQ; // skill 오름차순, id 오름차순
priority_queue<DATA*, vector<DATA*>, MINCOMP> maxPQ; // skill 내림차순, id 내림차순

priority_queue<DATA*, vector<DATA*>, MINCOMP> middleMinPQ; // 작은 수 그룹, 크면 클수록 우선순위 높음
priority_queue<DATA*, vector<DATA*>, MAXCOMP> middleMaxPQ; // 큰 수 그룹, 작으면 작을수록 우선순위 높음

int minNum, maxNum;
long long minSkill, maxSkill;

DATA realMem[MAX_P + 1];
int memIdx;

void median(DATA* pdata) {
    if (middleMinPQ.empty() || middleMinPQ.top()->skill > pdata->skill || (middleMinPQ.top()->skill == pdata->skill && middleMinPQ.top()->idx > pdata->idx)) {
        middleMinPQ.push(pdata);
        minNum++;
        minSkill += (long long)pdata->skill;
        if (minNum > maxNum + 1) {
            while (middleMinPQ.top()->isDeleted) middleMinPQ.pop();
            middleMaxPQ.push(middleMinPQ.top());
            maxSkill += middleMinPQ.top()->skill;
            minSkill -= middleMinPQ.top()->skill;
            middleMinPQ.pop();
            maxNum++;
            minNum--;
        }
    }
    else {
        middleMaxPQ.push(pdata);
        maxNum++;
        maxSkill += (long long)pdata->skill;
        if (maxNum > minNum) {
            while (middleMaxPQ.top()->isDeleted) middleMaxPQ.pop();
            middleMinPQ.push(middleMaxPQ.top());
            maxSkill -= middleMaxPQ.top()->skill;
            minSkill += middleMaxPQ.top()->skill;
            middleMaxPQ.pop();
            minNum++;
            maxNum--;
        }
    }
}

// 능력치의 합은 long long
int main() {
    DATA* data;
    memIdx = 0;
    minNum = maxNum = 0;
    minSkill = maxSkill = 0;
    int N, M, idx, skill;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> idx >> skill;
        data = realMem[memIdx++].init(idx, skill);
        minPQ.push(data);
        maxPQ.push(data);
        median(data);
    }

    int com;
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> com;
        switch (com) {
        case 0:
            cout << minPQ.top()->idx << " " << minPQ.top()->skill << "\n";
            minSkill -= minPQ.top()->skill;
            minPQ.top()->isDeleted = true;
            minPQ.pop();
            minNum--;
            if (maxNum > minNum) {
                while (middleMaxPQ.top()->isDeleted) middleMaxPQ.pop();
                middleMinPQ.push(middleMaxPQ.top());
                maxSkill -= middleMaxPQ.top()->skill;
                minSkill += middleMaxPQ.top()->skill;
                middleMaxPQ.pop();
                minNum++;
                maxNum--;
            }
            break;
        case 1:
            cout << maxPQ.top()->idx << " " << maxPQ.top()->skill << "\n";
            maxSkill -= maxPQ.top()->skill;
            maxPQ.top()->isDeleted = true;
            maxPQ.pop();
            maxNum--;
            if (minNum > maxNum + 1) {
                while (middleMinPQ.top()->isDeleted) middleMinPQ.pop();
                middleMaxPQ.push(middleMinPQ.top());
                maxSkill += middleMinPQ.top()->skill;
                minSkill -= middleMinPQ.top()->skill;
                middleMinPQ.pop();
                maxNum++;
                minNum--;
            }
            break;
        case 2:
            if ((maxNum + minNum) % 2 == 1) { // 홀수
                cout << middleMinPQ.top()->idx << " " << middleMinPQ.top()->skill << "\n";
                minSkill -= middleMinPQ.top()->skill;
                middleMinPQ.pop();
                minNum--;
            }
            else {
                cout << middleMinPQ.top()->idx << " " << middleMinPQ.top()->skill << "\n";
                minSkill -= middleMinPQ.top()->skill;
                middleMinPQ.pop();
                minNum--;

                cout << middleMaxPQ.top()->idx << " " << middleMaxPQ.top()->skill << "\n";
                maxSkill -= middleMaxPQ.top()->skill;
                middleMaxPQ.pop();
                maxNum--;
            }
            break;
        case 3:
            cin >> idx >> skill;
            data = realMem[memIdx++].init(idx, skill);
            minPQ.push(data);
            maxPQ.push(data);
            median(data);
            break;
        case 4:
            cout << minSkill << " " << maxSkill << "\n";
            break;
        }
    }


    return 0;
}
#endif