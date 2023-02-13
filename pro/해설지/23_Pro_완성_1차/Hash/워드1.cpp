/*
* string을 단어별로 뽑아내고
* 사전 단어를 한자리씩 *로 만든 문자열에 번호를 부여하여 해당하는 사전의 단어들을 리스트업
* 리스트는 vector로 생성
*
* string을 단어별로 뽑아낼 필요는 없어보이고, 리스트를 set으로 해도 무방해보임
*/
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<string.h>
#include<vector>
using namespace std;

int n, m;                           // str 길이, dict2 번호 부여
string S[10003];                    // str을 단어별로 뽑아냄
int wordID[40003];                  // str의 각 단어가 시작하는 index에 단어의 번호를 부여, wordID[str[단어시작index]]=단어번호
unordered_set<string> dict;         // 사전 단어 등록
unordered_map<string, int> dict2;   // 사전 단어의 각 자리를 *로 만든 단어 번호 부여 (abc=> *bc, a*c, ab*)
vector<string> v[10003];            // dict2에서 부여한 id index에 해당하는 실제 사전 단어 등록

void init(int N, char str[])
{
    n = m = 0;
    dict.clear();
    dict2.clear();
    S[0].clear();
    str[N] = '_';                   // 마지막에 _ 추가해서 예외처리 생략
    for (int i = 0; i <= N; i++) {
        if (str[i] == '_') {
            S[++n].clear();         // 다음 단어 초기화
            wordID[i + 1] = n;      // 다음 단어 번호 부여
        }
        else S[n] += str[i];
    }
}

int getId(string&str) {
    if (dict2.count(str)) return dict2[str];
    v[m].clear();               // dict2에 새로 등장한 경우 v도 초기화(init에서 전부 해도됨)
    return dict2[str] = m++;    // 0부터 번호 부여
}

void addDict(char word[])
{
    string str = word;
    dict.insert(str);
    for (int i = 0; word[i]; i++) {
        str[i] = '*';
        int id = getId(str);
        v[id].push_back(word);
        str[i] = word[i];
    }
}

void removeDict(char word[])
{
    string str = word;
    dict.erase(str);
    for (int i = 0; word[i]; i++) {
        str[i] = '*';
        int id = getId(str);
        v[id].erase(find(v[id].begin(), v[id].end(), word));
        if (v[id].empty()) dict2.erase(str);
        str[i] = word[i];
    }
}

int correctWord(int start, int end)
{
    string str;
    int cnt = 0;
    for (int i = wordID[start]; i < wordID[end + 2]; i++) {
        if (dict.count(S[i])) continue;         // 사전에 등록된 단어는 건너뜀

        str = S[i];
        string ret = { 'z' + 1 };               // 첫번째 문자를 z보다 큰 값으로 초기화
        for (int j = 0; j < str.size(); j++) {  // 각 자리를 *로 만들고 변경가능한 사전 단어 중 가장 작은 값 선택
            str[j] = '*';
            if (dict2.count(str)) {
                int id = dict2[str];

                /* 1. min_element 활용 */
                auto it = min_element(v[id].begin(), v[id].end());              // O(n)
                ret = min(ret, *it);

                /* 2. partial_sort 활용 */
                //partial_sort(v[id].begin(), v[id].begin() + 1, v[id].end());    // O(n log m)
                //ret = min(ret, v[id][0]);
            }
            str[j] = S[i][j];
        }
        if (ret.size() != 1) {  // 단어는 3자리 이상이므로 size가 1이면 초기값에서 변경되지 않음을 의미
            S[i] = ret;
            cnt++;
        }
    }
    return cnt;
}

void destroy(char result[])
{
    int len = 0;
    for (int i = 0; i < n; i++) {
        strcpy(result + len, S[i].c_str());
        len += S[i].size();
        result[len++] = '_';
    }
    result[len - 1] = 0;
}