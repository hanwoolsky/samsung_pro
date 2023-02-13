struct Result {
    int finish;
    int param;
};

#include<vector>
#include<algorithm>
#include<set>
using namespace std;
using pii = pair<int, int>;

int curTime;
set<pii> S;         // {end, id} 작은 순
struct Node {
    int parent;                 // 부모노드 번호, -1 이면 삭제됐음을 의미
    int speed, size;            // 전송 속도, 남은 데이터 크기
    int start, end;             // 남은 size부터 다운로드 시작시각, 끝나는 시각
    int dlCnt;                  // 다운로드 중인 자식노드 개수
    vector<int> child;          // 자식노드 리스트

    void update(int newSpeed) {
        size = max(0, size - (curTime - start) * speed); // 현재시각까지 다운로드 후 남은 양 설정
        if (size) {                 // 더 다운로드 해야하는 경우
            speed = newSpeed;       // 새로운 스피드 설정
            start = curTime;        // 새로운 시작시각 설정
            end = speed ? start + (size + speed - 1) / speed : 1e9; // 끝나는시각 설정
        }
    }
}node[50003];

void init(int capa) {
    curTime = 0;
    S.clear();
    node[0] = { -2, capa };
}

// cid 노드 삭제: 1. 부모노드의 자식리스트에서 삭제, 2. 부모노드 값 -1로 설정
void eraseNode(int cid) {
    auto& v = node[node[cid].parent].child;
    v.erase(find(v.begin(), v.end(), cid));
    node[cid].parent = -1;
}

// c=1 : id인 pc 추가 , c=-1 : id인 pc 제거
// dlCnt가 변경되는 가장 상위 노드까지 업데이트 후 해당 노드 반환
int updateDLcount(int id, int c) {
    for (; id >= 0; id = node[id].parent) {     // root까지 부모노드 타고 올라감
        node[id].dlCnt += c;                    // data link 개수 변경
        if (c == 1 && node[id].dlCnt > 1) return id;
        if (c == -1 && node[id].dlCnt > 0) return id;
    }
    return 0;
}

void updateSpeed(int id, int speed) {
    if (node[id].start) {               // 1)PC인 경우
        S.erase({ node[id].end, id });  //    기존 정보 set에서 삭제
        node[id].update(speed);         //    새롭게 size, speed, start, end 설정
        S.insert({ node[id].end, id }); //    새롭게 변경된 정보 set에 등록
        return;
    }
    node[id].speed = speed;             // 2)hub인 경우
    for (int cid : node[id].child)      //    전송중인 자식노드들에 새로운 속도 적용
        if (node[cid].dlCnt) updateSpeed(cid, speed / node[id].dlCnt);
}

// destTime까지 업데이트
void updateTime(int destTime) {
    while (S.size()) {
        curTime = S.begin()->first;
        int id = S.begin()->second;
        if (curTime > destTime) break;      // 가장 빨리 끝나는 시각이 목표 시각 이후인 경우

        int x = updateDLcount(id, -1);      // dlCnt 업데이트
        S.erase(S.begin());
        eraseNode(id);
        updateSpeed(x, node[x].speed);      // speed 업데이트
    }
}

void addHub(int Time, int pid, int cid) {
    updateTime(Time);
    node[cid] = { pid };
    node[pid].child.push_back(cid);
}

int removeHub(int Time, int cid) {
    updateTime(Time);
    if (node[cid].dlCnt) return 0;          // 전송중인 경우 삭제 실패
    eraseNode(cid);
    return 1;
}

void requestDL(int Time, int pid, int pcID, int size) {
    updateTime(Time);
    node[pid].child.push_back(pcID);
    node[pcID] = { pid, 0, size, Time, Time };

    curTime = Time;
    int x = updateDLcount(pcID, 1);
    updateSpeed(x, node[x].speed);
}

Result checkPC(int Time, int pcID) {
    updateTime(Time);

    curTime = Time;
    node[pcID].update(node[pcID].speed);                // pcID를 curTime까지 다운로드(남은 size 구하기 위해)

    if (node[pcID].size) return { 0, node[pcID].size }; // 아직 다운로드 중인 경우
    return { 1, node[pcID].end };                       // 다운로드 끝난 경우
}