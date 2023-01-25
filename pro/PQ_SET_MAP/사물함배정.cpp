#include <set>
#include <unordered_map>
 
using namespace std;
const int SIZE = 35001;
 
struct DATA {
    int s;
    int e;
    int len;
    int flag;
    bool operator<(const DATA& t) const {
        return len != t.len ? len > t.len : s < t.s;
    }
} allSpace[SIZE];
 
struct Comp {
    bool operator()(const DATA& x, const DATA& y) const {
        return x.s < y.s;
    }
};
 
set<DATA> emptySet;
set<DATA, Comp> allSet;
unordered_map<int, int> hmap;
int lockerCnt, totalLocker, hkey;
 
int getHash(int idx) {
    auto it = hmap.find(idx); // {idx, ???} 형태로 return
    if (it == hmap.end()) it = hmap.insert({ idx, ++hkey }).first; // {{idx, ++hkey}, true} 형태로 return
    return it->second; // find의 return, insert.first의 return의 second value, 즉 hkey
}
 
void init(int N) {
    emptySet.clear(); allSet.clear(), hmap.clear();
    emptySet.insert({1, N, N, 0});
    allSet.insert({ 1, N, N, 0 });
    totalLocker = lockerCnt = N;
    hkey = 0;
}
 
int arrive(int mId) {
    lockerCnt--;
 
    DATA tg = *emptySet.begin();
    emptySet.erase(tg);
    allSet.erase(tg);
 
    int s = tg.s, e = tg.e;
    int newIdx = (s + e) / 2;
 
    if (s == 1) newIdx = 1;
    else if (e == totalLocker) newIdx = totalLocker;
 
    if (s < newIdx) { // 사물함 번호가 1번이나 N번이면 같을 수도 있다.
        DATA tmp = { s, newIdx - 1, newIdx - s, 0 };
        emptySet.insert(tmp);
        allSet.insert(tmp);
    }
    if (newIdx < e) {
        DATA tmp1 = { newIdx + 1, e, e - newIdx, 0 };
        emptySet.insert(tmp1);
        allSet.insert(tmp1);
    }
 
    tg.s = tg.e = newIdx;
    tg.len = tg.flag = 1;
    int id = getHash(mId);
    allSpace[id] = tg;
    allSet.insert(tg);
 
    return newIdx;
}
 
int leave(int mId) {
    lockerCnt++;
 
    // mId인 사물함 찾기
    int key = getHash(mId);
    DATA leaveLocker = allSpace[key];
 
    auto it = allSet.find(leaveLocker);
    auto nit = next(it);
    if (it != allSet.begin()) {
        auto pit = prev(it);
        if (pit->flag == 0) { // 전 공간이 비어있다.
            leaveLocker.s = pit->s;
            leaveLocker.len += pit->len;
            emptySet.erase(*pit);
            allSet.erase(*pit);
        }
    }
    if (nit != allSet.end() && nit->flag == 0) {
        leaveLocker.e = nit->e;
        leaveLocker.len += nit->len;
        emptySet.erase(*nit);
        allSet.erase(*nit);
    }
 
    allSet.erase(it);
    leaveLocker.flag = 0;
    allSet.insert(leaveLocker);
    emptySet.insert(leaveLocker);
 
    return lockerCnt;
}