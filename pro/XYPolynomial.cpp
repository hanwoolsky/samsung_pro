#include<unordered_map>
#include<string>
using namespace std;

const int MOD = 10000;
const int BASE = 1001;

int LUT[10][1003]; // i^j를 다 계산해놓겠다. (-4)^0 ~ 4^1000 => -4 (idx : 0) ~ 4 (idx 8)
unordered_map<string, unordered_map<int, int>> poly;
// { name, { X지수*1001+Y지수, 계수 } }

void init()
{
	poly.clear();
	if (LUT[0][0] == 0) { // 모든 TC에 대해 같으므로 한번만 계산하기 위해 추가
		for (int i = 0; i <= 8; i++) {
			LUT[i][0] = 1; // 모든 수의 0승은 1
			for (int j = 1; j <= 1000; j++)
				LUT[i][j] = (LUT[i][j - 1] * (i - 4) % MOD + MOD) % MOD; // i^j = i^(j-1) * i (실제 값은 i - 4)
		}
	}
}

void calc(int&val, int c) { val = (val + c + MOD) % MOD; } // &로 넘겨 poly[][val] = poly[][val] + c로 만들기

void assign(char mName[], char mPoly[])
{
	int c = 1, x = 0, y = 0;	// c=계수, x=X지수, y=Y지수
	int type = 0;				// 계수:0, X지수:1, Y지수:2
	auto&P = poly[mName];
	for (int i = 0; mPoly[i]; i++) { // mPoly[i]가 있는 동안 loop를 돌아준다.
		if (mPoly[i] == '+' || mPoly[i] == '-') {
			calc(P[x * BASE + y], c); // poly의 mName -> (x * 1001 + y -> 계수 c) 
			type = x = y = 0;
			c = (mPoly[i] == '+' ? 1 : -1);
		}
		else if (mPoly[i] == 'X') type = 1, x = 1;
		else if (mPoly[i] == 'Y') type = 2, y = 1;
		else if (mPoly[i] == '^') continue; // type을 정해놓고 pass 해버리기
		else {
			int num = mPoly[i] - '0';
			if (type == 0) c *= num;
			else if (type == 1) x *= num;
			else y *= num;
		}
	}
	calc(P[x * BASE + y], c); // 마지막 항은 뒤에 +나 -가 없으므로 계수 저장 코드 추가
}

void compute(char mNameR[], char mNameA[], char mNameB[], int mOp)
{
	auto&A = poly[mNameA];
	auto&B = poly[mNameB];
	auto&C = poly[mNameR];

	if (mOp < 2) {
		for (auto p : A) calc(C[p.first], p.second); //p.first가 x * 1001 + y, p.second가 계수 c
		for (auto p : B) calc(C[p.first], mOp ? -p.second : p.second); // 0이면 더하기 1이면 빼기
	}
	else {
		for (auto p : A) for (auto q : B)
			calc(C[p.first + q.first], p.second * q.second); // tx^ay^b * mx^cy^d = (t*m)x^(a+c)y^(b+d) => (a + c) * 1001 + (b + d) = a * 1001 + b + c * 1001 + d
	}
}

int getCoefficient(char mName[], int mDegreeX, int mDegreeY)
{
	return poly[mName][mDegreeX * BASE + mDegreeY];
}

int calcPolynomial(char mName[], int mX, int mY)
{
	auto&P = poly[mName];

	int ret = 0;
	for (auto&p : P) {
		int x = p.first / BASE, y = p.first % BASE, c = p.second;
		ret = (ret + (long long)c * LUT[mX+4][x] * LUT[mY+4][y]) % MOD; // c*(mX^x)*(mY^y)
	}
	return ret;
}