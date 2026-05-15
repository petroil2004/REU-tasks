#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int BASE = 1000000000;

bool checkNumber(string s)
{
    if (s.empty())
        return false;

    for (char c : s)
    {
        if (c < '0' || c > '9')
            return false;
    }

    return true;
}

vector<int> toList(string s)
{
    vector<int> a;

    while (!s.empty())
    {
        int len;

        if (s.size() > 9)
            len = 9;
        else
            len = s.size();

        string part = s.substr(s.size() - len, len);

        a.push_back(stoi(part));

        s.erase(s.size() - len, len);
    }

    return a;
}

vector<int> add(vector<int> a, vector<int> b)
{
    vector<int> res;

    int carry = 0;
    int n;

    if (a.size() > b.size())
        n = a.size();
    else
        n = b.size();

    for (int i = 0; i < n; i++)
    {
        int x = 0;
        int y = 0;

        if (i < a.size())
            x = a[i];

        if (i < b.size())
            y = b[i];

        long long sum = (long long)x + y + carry;

        res.push_back(sum % BASE);

        carry = sum / BASE;
    }

    if (carry > 0)
        res.push_back(carry);

    return res;
}

void printNumber(vector<int> a)
{
    if (a.empty())
    {
        cout << 0;
        return;
    }

    cout << a.back();

    for (int i = a.size() - 2; i >= 0; i--)
    {
        string part = to_string(a[i]);

        while (part.size() < 9)
            part = "0" + part;

        cout << part;
    }
}

int main()
{
    string s1, s2;

    cout << "First number: ";
    cin >> s1;

    cout << "Second number: ";
    cin >> s2;

    if (!checkNumber(s1) || !checkNumber(s2))
    {
        cout << "Input error!";
        return 0;
    }

    vector<int> a = toList(s1);
    vector<int> b = toList(s2);

    vector<int> result = add(a, b);

    cout << "Result: ";
    printNumber(result);

    return 0;
}