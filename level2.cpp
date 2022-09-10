#include <bits/stdc++.h>
#include <unordered_map>>
using namespace std;

string board[5][5];
unordered_map<string, pair<int, int>> moves;

unordered_map<string, pair<int, int>> movesh1;

unordered_map<string, pair<int, int>> movesh2;
unordered_map<string, pair<int, int>> mA;
unordered_map<string, pair<int, int>> mB;
void initialize()
{
    int i = 0, j = 0;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
            board[i][j] = "-";
    }
    moves["F"] = {-1, 0};
    moves["B"] = {1, 0};
    moves["L"] = {0, -1};
    moves["R"] = {0, 1};

    movesh1["F"] = {-2, 0};
    movesh1["B"] = {2, 0};
    movesh1["L"] = {0, -2};
    movesh1["R"] = {0, 2};

    movesh2["FL"] = {-2, -2};
    movesh2["FR"] = {-2, 2};
    movesh2["BL"] = {2, -2};
    movesh2["BR"] = {2, 2};
}
void initialinput(int row)
{
    string p;
    if (row == 4)
    {
        p = "A";
        cout << "Player1 ";
    }
    else
    {
        p = "B";
        cout << "Player2 ";
    }
    cout << "Input: ";
    string s;
    int k = 0;
    string c = "";
    getline(cin, s);
    s.erase(0, s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ',')
        {
            c.erase(0, c.find_first_not_of(" "));
            c.erase(c.find_last_not_of(" ") + 1);
            if (row == 4)
            {

                mA[c] = {row, k};
            }
            else
            {
                mB[c] = {row, k};
            }
            board[row][k++] = p + "-" + c;

            c = "";
        }
        else
            c += s[i];
    }

    c.erase(0, c.find_first_not_of(" "));
    c.erase(c.find_last_not_of(" ") + 1);
    if (row == 4)
    {

        mA[c] = {row, k};
    }
    else
    {
        mB[c] = {row, k};
    }
    board[row][k++] = p + "-" + c;
    c = "";
}
void currBoard()
{
    int i = 0, j = 0;
    cout << "Current Grid:\n";
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
            cout << board[i][j] << "\t";
        cout << endl;
    }
}
bool validatepiece(int p, string pawn)
{
    if (p == 1)
    {
        if (mA.find(pawn) != mA.end())
            return true;
    }

    if (p == -1)
    {
        if (mB.find(pawn) != mB.end())
            return true;
    }
    return false;
}
bool validatemv(string mv)
{

    if (moves.find(mv) != moves.end())
        return true;
    return false;
}
bool checkFriend(pair<int, int> finalpos, int p)
{
    if (p == 1)
    {
        for (auto m : mA)
        {
            if (m.second == finalpos)
                return true;
        }
    }
    else
    {
        for (auto m : mB)
        {
            if (m.second == finalpos)
                return true;
        }
    }
    return false;
}
string checkEnemy(pair<int, int> finalpos, int p)
{
    if (p == -1)
    {
        for (auto m : mA)
        {
            if (m.second == finalpos)
                return m.first;
        }
    }
    else
    {
        for (auto m : mB)
        {
            if (m.second == finalpos)
                return m.first;
        }
    }
    return "";
}
void input(int p)
{
    while (true)
    {
        if (p == 1)
        {
            cout << "PlayerA's ";
        }
        else
        {
            cout << "PlayerB's ";
        }
        cout << "Move: ";
        string s;

        getline(cin, s);
        s.erase(0, s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
        string pawn = s.substr(0, s.find_first_of(":"));
        string mv = s.substr(s.find_first_of(":") + 1);
        pair<int, int> dir;
        if (pawn[0] == 'P')
        {
            if (!(validatepiece(p, pawn) && validatemv(mv)))
            {
                continue;
            }

            dir = moves[mv];
        }
        else if (pawn == "H1")
        {
            if (movesh1.find(mv) == movesh1.end())
            {
                continue;
            }
            dir = movesh1[mv];
        }
        else if (pawn == "H2")
        {
            if (movesh2.find(mv) == movesh2.end())
            {
                continue;
            }
            dir = movesh2[mv];
        }
        dir.first *= p;
        dir.second *= p;
        pair<int, int> currpos;
        if (p == 1)
        {
            currpos = mA[pawn];
        }
        else
        {
            currpos = mB[pawn];
        }
        if (currpos.first + dir.first >= 5 || currpos.first + dir.first < 0)
        {
            cout << "Out of bounds" << endl;
            continue;
        }

        if (currpos.second + dir.second >= 5 || currpos.second + dir.second < 0)
        {
            cout << "Out of bounds" << endl;
            continue;
        }
        pair<int, int> finalpos;
        finalpos.first = currpos.first + dir.first;
        finalpos.second = currpos.second + dir.second;
        if (checkFriend(finalpos, p))
        {
            cout << "Friend" << endl;
            continue;
        }
        if (p == 1)
            mA[pawn] = finalpos;
        else
            mB[pawn] = finalpos;
        board[finalpos.first][finalpos.second] = board[currpos.first][currpos.second];
        if (pawn[0] == 'H')
        {
            if (!checkFriend({(finalpos.first + currpos.first) / 2, (finalpos.second + currpos.second) / 2}, p))
            {
                string opp = checkEnemy({(finalpos.first + currpos.first) / 2, (finalpos.second + currpos.second) / 2}, p);
                if (opp != "")
                {
                    if (p == 1)
                        mB.erase(opp);
                    else
                        mA.erase(opp);
                }
                board[(finalpos.first + currpos.first) / 2][(finalpos.second + currpos.second) / 2] = "-";
            }
        }
        board[currpos.first][currpos.second] = "-";

        string opp = checkEnemy(finalpos, p);
        if (opp != "")
        {
            if (p == 1)
                mB.erase(opp);
            else
                mA.erase(opp);
        }
        break;
    }
}
int main()
{
    initialize();
    initialinput(4);
    currBoard();
    initialinput(0);
    currBoard();
    bool gameEnd = false;
    int p = 1;
    while (gameEnd == false)
    {
        input(p);
        p *= -1;
        currBoard();
        if (mA.size() == 0)
        {
            gameEnd = true;
            cout << "Player2 Wins" << endl;
        }
        else if (mB.size() == 0)
        {
            gameEnd = true;
            cout << "Player1 wins" << endl;
        }
    }
}