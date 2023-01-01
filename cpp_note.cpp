// unordered_map은 해시테이블로 구현한 자료구조
// 중복을 허용하지 않는다.
// 1. 탐색 O(1)
// 함수
// unordered_map <string, int> hash;로 선언
// 1) empty() : 맵이 비어있는지 확인하는 함수
// 2) size() : 맵의 크기를 확인하는 함수
// 3) find(key) : key에 해당하는 원소를 찾는 함수
// 4) count(key) : key에 해당하는 원소의 갯수를 반환
// 5) insert(make_pairt(key, value)) or insert({key, value}) : 맵에 pair<key, key>를 추가하는 함수
// 6) erase(key) : 맵에서 key에 해당하는 원소를 제거
// 7) clear() : 맵을 초기화하는 함수
// for (auto i : hash){
//    cout << i.first << i.second << endl;
//}
// for (pair<string, int> i : hash){
//    cout << i.first << i.second << endl;
//}



// map은 Binary Search Tree
// 1. 탐색 O(logn)


// maxHeap을 위한 queue
// priority_queue<pair<int , int>>
// priority_queue<pair<int , int>> pq;
    
//     pq.push({1,2});
//     pq.push({1,3});
//     pq.push({2,2});
//     pq.push({2,5});
//     pq.push({3,1});

//     while(!pq.empty()){
//         cout << pq.top().first << pq.top().second << endl;
//         pq.pop();
//     }