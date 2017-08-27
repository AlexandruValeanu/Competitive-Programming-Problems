#include <iostream>
#include <array>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    array<int, 3> cnt;

    int N;
    cin >> N;

    long long answer = 0;

    for (int i = 0; i < N; i++){
        int x;
        cin >> x;

        answer += cnt[(3 - x % 3) % 3];
        cnt[x % 3]++;
    }

    cout << answer << endl;

    return 0;
}
