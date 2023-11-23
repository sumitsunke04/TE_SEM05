#include <bits/stdc++.h>
using namespace std;

void SUBNET()
{
    int ip[4];
    cout << "Enter a IP address : ";
    string ips;
    cin >> ips;
    string word = "";
    int j = 0;
    for (int i = 0; i < ips.length(); i++)
    {
        if (ips[i] == '.')
        {
            ip[j] = stoi(word);
            j++;
            word = "";
        }
        else
        {
            word += ips[i];
        }
    }
    ip[3] = stoi(word);

    int no_subnets;
    cout << "Enter a number of subnets : ";
    cin >> no_subnets;

    int N = log2(no_subnets);
    int H = 8 - N;
    string v = "00000000";

    for (int i = 0; i < N; i++)
    {
        v[i] = '1';
    }

    int val = 0;
    for (int i = 0; i < 8; i++)
    {
        val += ((v[i] - '0') * pow(2, (7 - i)));
    }

    int arr2[4] = {255, 255, 255, 255};
    int arr3[4] = {255, 255, 255, 255};
    arr3[3] = val;

    for (int i = 0; i < 4; i++)
    {
        arr3[i] = arr2[i] - arr3[i];
    }

    cout << endl;
    for (int i = 0; i < no_subnets; i++)
    {
        cout << "Subnet " << i + 1 << "\t";
        cout << ip[0] << '.' << ip[1] << '.' << ip[2] << '.' << ip[3];
        cout << "\t\t";
        ip[3] = ip[3] + arr3[3];
        cout << ip[0] << '.' << ip[1] << '.' << ip[2] << '.' << ip[3];
        ip[3] = ip[3] + 1;
        cout << endl;
    }
}
int main()
{
    SUBNET();
    return 0;
}