#include <set>
#include <unordered_map>
using namespace std;
 
const int LM = 35005; // 왜 35005 였을까? => 호출 횟수 35000 이하 조건
struct Data {
    int s, e, len, flag;
    bool operator<(const Data&t) const {
        return len != t.len ? len > t.len : s < t.s;
    }
} ids[LM];
struct Comp {
    bool operator() (const Data&a, const Data&b) const {
        return a.s < b.s;
    }
};
 
unordered_map<int, int> hmap;
set<Data, Comp> allSet;
set<Data> emptySet;
int empLocker, numLocker, idx;
 
void init(int N) {
    empLocker = numLocker = N;
    idx = 0;
    allSet.clear(), emptySet.clear(), hmap.clear();
 
    allSet.insert({ 1, N, N, 0 });
    emptySet.insert({ 1, N, N, 0 });
}
 
int getID(int mid) {
    if (!hmap[mid]) return hmap[mid] = ++idx;
    return hmap[mid];
}
 
int arrive(int mId) {
    empLocker--;
 
    Data tg = *emptySet.begin();
    emptySet.erase(tg);
    allSet.erase(tg);
 
    int s = tg.s, e = tg.e;
    int newIdx = (s + e) / 2;
 
    if (s == 1) newIdx = 1;
    else if (e == numLocker) newIdx = numLocker;
 
    if (s < newIdx) { // 사물함 번호가 1번이나 N번이면 같을 수도 있다.
        Data tmp = { s, newIdx - 1, newIdx - s, 0 };
        emptySet.insert(tmp);
        allSet.insert(tmp);
    }
    if (newIdx < e) {
        Data tmp1 = { newIdx + 1, e, e - newIdx, 0 };
        emptySet.insert(tmp1);
        allSet.insert(tmp1);
    }
 
    tg.s = tg.e = newIdx;
    tg.len = tg.flag = 1;
    int id = getID(mId);
    ids[id] = tg;
    allSet.insert(tg);
     
    return newIdx;
}
 
int leave(int mId) {
    empLocker++;
 
    int id = hmap[mId];
    Data tg = ids[id];
 
    auto it = allSet.find(tg);
    auto nit = next(it, 1);
    if (it != allSet.begin()) {
        auto pit = prev(it, 1);
        if (pit->flag == 0) {
            tg.s = pit->s;
            tg.len += pit->len;
            emptySet.erase(*pit);
            allSet.erase(*pit);
        }
    }
    if (nit != allSet.end() && nit->flag == 0) {
        tg.e = nit->e;
        tg.len += nit->len;
        emptySet.erase(*nit);
        allSet.erase(*nit);
    }
 
    allSet.erase(it);
    tg.flag = 0;
    allSet.insert(tg);
    emptySet.insert(tg);
 
    // idx[id]는 정리 안해줘도 되나? -> 같은 자리에 arrive 되면 덮어씌어진다.
 
    return empLocker;
}