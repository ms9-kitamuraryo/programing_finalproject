#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Gomoku {
public:
    int h, w;
    int player;
    int goal_len;
    vector<string> board;

    Gomoku() {
        goal_len = 5;
        h = 10, w = 10;
        player = 0;
        board.resize(h, string(w, '.'));
    }

    Gomoku(int h_, int w_, int goal_ = 5) {
        goal_len = goal_;
        h = h_, w = w_;
        player = 0;
        board.resize(h, string(w, '.'));
    }

    void play() {
        while (play_one()) {
            for (int i = 0; i < h; ++i)for (int j = 0; j < w; ++j) board[i][j] = '.';
            player = 0;
        }
        cout << "Game Over" << endl;
    }

    bool play_one() {
        int mxturn = h * w;
        for (int turn = 1; turn <= mxturn; ++turn) {
            cout << "\n**********TURN " << turn << "**********\n";
            display_board();
            pair<int, int> retp = query();
            int ry = retp.first, rx = retp.second;
            board[ry][rx] = (player == 0 ? 'O' : 'X');
            if (check_board(ry, rx)) {
                display_board();
                cout << "********Player \"" << (player == 0 ? 'O' : 'X') << "\" WIN!********" << endl;
                break;
            }
            if (turn == mxturn) {
                display_board();
                cout << "*********DRAW********" << endl;
            }
            player ^= 1;
        }
        while (1) {
            cout << "\nPlay next game? {Y/n}" << endl;
            string ret;
            cin >> ret;
            if (ret == "Y") {
                return true;
            }
            else if (ret == "N" || ret == "n") {
                return false;
            }
        }
    }

    bool check_board(int ry, int rx) {
        char pre = '*';
        int cnt = 0;
        for (int i = ry, j = max(rx - goal_len + 1, 0); j < min(rx + goal_len, w); ++j) {
            if (pre == board[i][j]) ++cnt;
            else cnt = 1;
            if (cnt >= goal_len) return true;
            pre = board[i][j];
        }
        pre = '*';
        cnt = 0;
        for (int j = rx, i = max(ry - goal_len + 1, 0); i < min(ry + goal_len, h); ++i) {
            if (pre == board[i][j]) ++cnt;
            else cnt = 1;
            if (cnt >= goal_len) return true;
            pre = board[i][j];
        }
        pre = '*';
        cnt = 0;
        int rg = min(goal_len - 1, min(ry, rx));
        for (int i = ry - rg, j = rx - rg; i < min(ry + goal_len, h) && j < min(rx + goal_len, w); ++i, ++j) {
            if (pre == board[i][j]) ++cnt;
            else cnt = 1;
            if (cnt >= goal_len) return true;
            pre = board[i][j];
        }
        pre = '*';
        cnt = 0;
        rg = min(goal_len - 1, min(ry, w - rx - 1));
        for (int i = ry - rg, j = rx + rg; i < min(ry + goal_len, h) && j >= max(rx - goal_len + 1, 0); ++i, --j) {
            if (pre == board[i][j]) ++cnt;
            else cnt = 1;
            if (cnt >= goal_len) return true;
            pre = board[i][j];
        }
        return false;
    }

    void display_board() {
        cout << setw(3) << " ";
        for (int i = 0; i < w; ++i) {
            cout << setw(3) << i;
        }
        cout << "\n";
        int cy = 0;

        for (auto bi : board) {
            cout << setw(3) << cy;
            for (auto c : bi) {
                cout << setw(3) << c;
            }
            ++cy;
            cout << "\n";
        }
    }

    pair<int, int> query() {
        cout << "*****Player " << (player == 0 ? "\"O\"" : "\"X\"") << "\'s turn.*****\nPut your stone.\ny x\n";
        int y = -1, x = -1;
        while (1) {
            cin >> y >> x;
            if (y >= 0 && x >= 0 && y < h && x < w && board[y][x] == '.') {
                break;
            }
            cout << "input invalid. Input again.\n";
        }
        return pair<int, int>(y, x);
    }
};

int main() {

    cout << string(20, '-') << "\n";
    cout << "  GOMOKU NARABE  \n";
    cout << string(20, '-') << "\n";

    int h = 10, w = 10;
    while (1) {
        cout << "Please Set Board Size. (y x)" << endl;
        cin >> h >> w;
        if (h >= 5 && w >= 5) {
            break;
        }
        cout << "Please input at least 5" << endl;
    }

    Gomoku g(h, w);
    g.play();

    return 0;
}