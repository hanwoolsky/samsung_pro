// 모든 사물함이 비어 있는 경우, 1번 사물함을 배정한다.
// 그렇지 않은 경우, 연속된 빈 사물함이 가장 큰 구간을 먼저 선택한다. 가장 큰 구간이 2개 이상일 경우, 사물함 번호가 작은 구간을 선택한다.
// 선택된 구간 내에서, 사용 중인 사물함과 거리가 가장 먼 곳의 사물함을 배정한다.
// 조건에 해당하는 사물함이 2개 이상일 경우, 번호가 작은 사물함을 배정한다. => 구간의 반에 해당하는 idx / 양 끝이 비어있으면 양 끝으로 무한대로 설정?
// 사용자가 퇴실하는 경우, 해당 사용자에게 배정되었던 사물함을 해제한다.

// 파이썬으로 풀기
// 정렬된 연결리스트 https://m.blog.naver.com/crm06217/221835403267
// https://danasn.tistory.com/214

#include <unordered_map>
#include <set>
#include <queue>
using namespace std;

int emptyLocker;
int locker;

unordered_map <int, int> lockerID;
set <int, int> lockerUpdate;
priority_queue <pair<int, int>> maxHeap;
// linked list

int calcLocker(int N){ // 총 사물함 N개
    int len, idx, newIdx;
    len = maxHeap.top().first;
    idx = maxHeap.top().second;
    maxHeap.pop();

    if (idx == 0){ // 첫 번째 칸이 비었음
        maxHeap.push({N-1, 1});
        newIdx = 1;
        // linked list 처음에 추가
    }
    else if (idx + len == N){ // 마지막 칸이 비었음
        maxHeap.push({0, N});
        newIdx = N;
        // idx.prev의 length 업데이트 (-1)
        // linked list 마지막에 추가
    }
    else{
        newIdx = idx + (len+1)/2;
        maxHeap.push({newIdx.next - newIdx - 1, newIdx});
        maxHeap.push({newIdx - newIdx.prev - 1, newIdx.prev}); // {.., newIdx.prev}인 것을 수정해야함
    }

    return newIdx;
};

void init(int N){ // N개의 사물함 (8<=N<=10^8)가 주어진다.
    emptyLocker = N;
    maxHeap.push({N, 0});
};

int arrive(int mID){ // mID(1<=mID<=10^9) 사용자가 입실한다. 호출 횟수 : 20000
    locker = calcLocker(); // 몇번 사물함을 배정받는지
    lockerID[mID] = locker; // locker번 사물함에 mID 사용자 입력 or mID에 locker 입력
    // 사물함 리스트에 locker 추가 (정렬되는 자료구조 + 앞 뒤를 쉽게 알 수 있는) => 이진 트리?
    emptyLocker--;
    return locker;// 사물함 번호
};

int leave(int mID){ // mID 사용자가 퇴실한다. 배정된 사물함을 해제한다. 호출 횟수 : 35000
    lockerID[mID] = 0;
    // maxHeap 삭제 & 앞에 노드 업데이트
    emptyLocker++;
    return emptyLocker; // 해제 후 빈 사물함의 개수
};



// leave는 해제하는 작업 따로, 빈 사물함 카운트 기능 따로 -> 사물함 개수는 arrive가 오면 무조건 +1, leave면 무조건 -1이므로
//  mID에 해당하는 key를 0으로 초기화 해야하므로 해시로 관리 -> unordered_map

// arrive는 투 포인터를 사용하여 구간 최대 길이 구하는 알고리즘 -> O(n)
// arrive할 때 마다 사물함의 번호 리스트에 저장 ex) 1 / 1, 8 / 1, 4, 8 -> 구간의 최대 길이는 3, 4 -> 8 - 4 / 2 인덱스 o(찬 사물함 개수)
// 정렬되는 곳에 사물함 idx를 넣어야하므로 map이나 set 사용


// leave 할 때마다 사물함 번호 리스트를 erase할 것인가 아니면 번호 리스트의 왼쪽의 구간길이를 +로 연결할 것인가.
// 1:mid 2 3 4 5:mid
// 1   2  3  4  5  6  7   8  9
// 8            5            (9 - 1) / 2
// N-1         


// 추가 될 때는 왼쪽 all update (오른쪽의 길이를 저장) 양 끝 고려 왼쪽이 1(0)이면 & 왼쪽이 N이면
// 떠날 때는 왼쪽 하나의 값만 update


// N = 8
// arrive()
// 비었으면 1추가 [1]
// 1개 있으므로 N번 추가. [1, 8]
// 2개 이상 있으므로 1 + [8-1] / 2 = 4추가 [1, 4, 8]
// 2개 이상 있으므로 


// maxheap 같은곳에 두번째원소(구간의 길이)가 큰 순서, 첫번째 원소(시작 인덱스)가 작은 순서로 정렬
// 새로운 사물함은 maxheap[0][0] +(+일지 -일지 모름) maxheap[0][1] / 2

// (1, 7)
// (1, 7), (8, 0)
// (1, 7), (8, 0) (4, 3)
// insert는 (사물함의 idx(위에서 계산한 것), 해당 idx 다음 원소 (idx만 저장된 리스트 등 BST?)


// 1, 8 => 8번째 1 + 4번째
// 2, 6 => 4번째 2 + 3번째
// 2, 2 / 5, 3 => 5, 3 선택 후 5 + 1 번째
// 2, 2 / 5, 1 / 7, 1 => 2, 2 선택 후 2 + 1 번째

// max대heap => 가장 큰 구간 + 시작 위치 알기 위해 => 이 친구의 구간이 반(계산)으로 줄고
// 새로운 인덱스, 새로운 구간을 넣어줘야함 -> 최 기존 인덱스 2개가 바뀜
// 

// 8, 0
// idx == 0 => 첫 번째에 넣기 & (N-1, 1) = (7, 1) & [1]
// idx + length = N -> 맨 끝에 넣기 & (7, 1)이 (6, 1)로 수정 & [1, 8]
// 1 + 6 / 2 = 4에 넣기 & (6, 1)가 (4-1-1, 1) = (2, 1), (8-4-1, 4) = (3, 4)로 수정 & [1, 4, 8]
// 4 + 반올림(3 / 2) = 6에 넣기 & (3, 4)가 (6 - 4 - 1, 4), (8 - 6 - 1, 6) & [1, 4, 6, 8]


// linked list와 maxheap 사용
//  =====      =====      =====
// | 1   | ~~ |  4  | ~~ |  8  |
//  =====      =====      =====

 // length, idx = maxheap.pop(0)
 // newidx = idx + 반올림(length/2)
 // maxheap.push(newidx - newidx.prev - 1, newidx.prev), maxheap.push(newidx.next - newidx - 1, newidx)

 // 양 끝이 비었을 때만, 즉 idx + length == N(끝 인덱스) & 
 // 1번이 비었을 때 : (길이, 0)이 들어가 있을 때 == 0일 때는 첫 번째 인덱스에 넣기


 // 빠질 때는 옆 인덱스의 length만 바꾸어주면 된다.
 // 1번이 빠질 때는 (길이, 0)을 추가

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