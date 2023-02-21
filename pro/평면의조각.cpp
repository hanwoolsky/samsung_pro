using namespace std;
#include <set>
#define INF (100000000) // 0 하나 더 붙이고 밑에 2* 지워야 통과 why?

struct coord {
    int value;
    int id;
    bool operator<(const coord& t) const {
        return value < t.value;
    }
};

set<coord> x, y, xy; // x축에 평행, y축에 평행, 기울기 1

void init(int N, int ID[100000], int type[100000], int X[100000], int Y[100000]){
    x.clear(); y.clear(); xy.clear();
    for (int i = 0; i < N; i++) {
        if (type[i] == 2) xy.insert({ X[i] - Y[i], ID[i] });
        else if (type[i] == 1) y.insert({ X[i], ID[i] });
        else x.insert({ Y[i], ID[i] });
    }
    xy.insert({ 2 * INF, 0 }); xy.insert({ 2 * -INF, 0 });
    y.insert({ INF, 0 }); y.insert({ -INF, 0 });
    x.insert({ INF, 0 }); x.insert({ -INF, 0 });
}

int findPiece(int interiorX, int interiorY) {
    coord itx1, itx2, ity1, ity2, itxy1, itxy2;
    /*auto itxy = xy.lower_bound({ interiorX - interiorY, 0 });
    if (itxy == xy.end()) { 
        if (itxy != xy.begin()) itxy1 = { prev(itxy, 1)->value, prev(itxy, 1)->id };
        else itxy1 = { -2 * INF, 0 };
        itxy2 = { 2 * INF, 0 };
    }
    else itxy2 = { itxy->value, itxy->id };

    if (itxy == xy.begin()) {
        itxy1 = { -2 * INF, 0 };
        if (itxy != xy.end()) itxy2 = { itxy->value, itxy->id };
        else itxy2 = { 2 * INF, 0 };
    }
    else {
        itxy1 = { prev(itxy, 1)->value, prev(itxy, 1)->id };
    }

    auto itx = x.lower_bound({ interiorY, 0 });
    if (itx == x.end()) {
        if (itx != x.begin()) itx1 = { prev(itx, 1)->value, prev(itx, 1)->id };
        else itx1 = { -INF, 0 };
        itx2 = { INF, 0 };
    }
    else itx2 = { itx->value, itx->id };

    if (itx == x.begin()) {
        itx1 = { -INF, 0 };
        if (itx != x.end()) itx2 = { itx->value, itx->id };
        else itx2 = { INF, 0 };
    }
    else {
        itx1 = { prev(itx, 1)->value, prev(itx, 1)->id };
    }

    auto ity = y.lower_bound({interiorX, 0});
    if (ity == y.end()) {
        if (ity != y.begin()) ity1 = { prev(ity, 1)->value, prev(ity, 1)->id };
        else ity1 = { -INF, 0 };
        ity2 = { INF, 0 };
    }
    else ity2 = { ity->value, ity->id };

    if (ity == y.begin()) {
        ity1 = { -INF, 0 };
        if (ity != y.end()) ity2 = { ity->value, ity->id };
        else ity2 = { INF, 0 };
    }
    else {
        ity1 = { prev(ity, 1)->value, prev(ity, 1)->id };
    }*/

    auto itxy = xy.lower_bound({ interiorX - interiorY, 0 });
    itxy1 = { prev(itxy, 1)->value, prev(itxy, 1)->id };
    itxy2 = { itxy->value, itxy->id };

    auto itx = x.lower_bound({ interiorY, 0 });
    itx1 = { prev(itx, 1)->value, prev(itx, 1)->id };
    itx2 = { itx->value, itx->id };

    auto ity = y.lower_bound({ interiorX, 0 });
    ity1 = { prev(ity, 1)->value, prev(ity, 1)->id };
    ity2 = { ity->value, ity->id };
 
    int sum = 0;

    int value = itxy1.value, id = itxy1.id;					// 위 대각라인
    if (ity1.value < itx2.value + value) sum += id;
    if (ity1.value > itx1.value + value) sum += ity1.id;
    if (ity2.value > itx2.value + value) sum += itx2.id;

    value = itxy2.value, id = itxy2.id;					// 아래 대각라인
    if (ity2.value > itx1.value + value) sum += id;
    if (ity2.value < itx2.value + value) sum += ity2.id;
    if (ity1.value < itx1.value + value) sum += itx1.id;

    return sum;
}