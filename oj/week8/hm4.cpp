#include <iostream>
#include <vector>
using namespace std;

int main() {
    int S, N, a, ans;
    vector<int> train;
    vector<int> len;

    cin >> S; // 讀取測試案例數量
    while (S-- && cin >> N) {
        train.assign(N * 2, 0); // 初始化火車車廂重量的向量，大小為 2N
        len.assign(N * 2, 1); // 初始化每個位置的最長序列長度，大小為 2N，初始值為 1
        ans = 0; // 初始化答案為 0

        for (int i = 0; i < N; ++i) {
            cin >> a; // 讀取每個車廂的重量
            train[N + i] = train[N - i - 1] = a; // 以鏡像的方式填充 train 向量
        }

        // 動態規劃計算最長的火車長度
        for (int i = 0; i < N * 2; ++i) {
            for (int j = 0; j < i; ++j) {
                // 如果第 i 個車廂的重量大於第 j 個車廂的重量
                if (train[i] > train[j]) {
                    len[i] = max(len[i], len[j] + 1); // 更新以第 i 個車廂結尾的最長序列長度
                }
                ans = max(ans, len[i]); // 更新最長的火車長度
            }
        }
        cout << ans << "\n"; // 輸出結果
    }
    return 0;
}