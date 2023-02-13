#include<set>
#include<unordered_map>
using namespace std;
using pii = pair<int, int>;

unordered_map<int, int> used;                       // used[s] = e
set<pii> unused;                                    // unused : {size, s}
unordered_map<int, set<pii>::iterator> sit, eit;    // sit[s] = unused it , eit[e] = unused it

void init(int N) {
    used.clear();
    unused.clear();
    sit.clear();
    eit.clear();
    sit[0] = eit[N] = unused.insert({ N, 0 }).first;    // N ũ���� �� ���� �߰�
}

int allocate(int size) {
    auto it = unused.lower_bound({ size, 0 });          // {size, 0} ���� ũ�ų� ���� ���� ���� it ����
    if (it == unused.end()) return -1;                  // ������ -1

    int s = it->second, e = it->second + size;          // �Ҵ��� [s:e)
    int remainSize = it->first - size;                  // �Ҵ� �� ���� ������� ũ��

    used[s] = e;                                        // ��� ���·� ����

    unused.erase(it);                                   // �̻�� ������ ��� ����
    sit.erase(s);
    eit.erase(e);

    if (remainSize)                                     // ������� ���� �ִٸ� ���
        sit[e] = eit[e + remainSize] = unused.insert({ remainSize, e }).first;

    return s;
}

int deallocate(int start) {
    if (!used.count(start)) return -1;      // start�� �Ҵ�� ������ �� �� ��ȣ�� �ƴ� ���

    int s = start, e = used[start];
    int ret = e - s;
    used.erase(s);

    if (eit.count(s)) {                     // ���� ������ �� ������ ���
        auto it = eit[s];
        sit.erase(it->second);
        eit.erase(s);
        s = it->second;
        unused.erase(it);
    }
    if (sit.count(e)) {                     // ������ ������ �� ������ ���
        auto it = sit[e];
        sit.erase(e);
        eit.erase(it->first + e);
        e += it->first;
        unused.erase(it);
    }
    sit[s] = eit[e] = unused.insert({ e - s,s }).first;

    return ret;
}