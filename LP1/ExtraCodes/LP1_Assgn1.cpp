//============================================================================
// Name        : CPUSchedulingCPP.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <limits>
#include <bits/stdc++.h>
using namespace std;

void FCFS()
{
    int n;
    cout << "Enter number of processes " << endl;
    cin >> n;

    int arr[n], bur[n], comp[n], proc[n], TAT[n], WT[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter process number " << endl;
        cin >> proc[i];
        cout << "Enter arrive time " << endl;
        cin >> arr[i];
        cout << "Enter burst time " << endl;
        cin >> bur[i];
    }

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n - j - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                int t = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = t;

                t = bur[i];
                bur[i] = bur[i + 1];
                bur[i + 1] = t;

                t = proc[i];
                proc[i] = proc[i + 1];
                proc[i + 1] = t;
            }
        }
    }

    comp[0] = arr[0] + bur[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] <= comp[i - 1])
        {
            comp[i] = comp[i - 1] + bur[i];
        }
        else
        {
            comp[i] = arr[i] + bur[i];
        }
    }
    int sumTAT = 0;
    int sumWT = 0;
    for (int i = 0; i < n; i++)
    {
        TAT[i] = comp[i] - arr[i];
        sumTAT += TAT[i];
        WT[i] = TAT[i] - bur[i];
        sumWT += WT[i];
    }

    for (int i = 0; i < n; i++)
    {

        cout << proc[i] << " " << arr[i] << " " << bur[i] << " " << comp[i] << " " << TAT[i] << " " << WT[i] << endl;
    }
    cout << endl;
    cout << "Average TAT : " << (float)(sumTAT / n) << endl;
    cout << "Average WT  : " << (float)(sumWT / n) << endl;
}

void priority()
{
    int n;
    cout << "Enter number of processes " << endl;
    cin >> n;

    int arr[n], bur[n], comp[n], proc[n], TAT[n], WT[n], prio[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter process number " << endl;
        cin >> proc[i];
        cout << "Enter priority " << endl;
        cin >> prio[i];
        cout << "Enter arrive time " << endl;
        cin >> arr[i];
        cout << "Enter burst time " << endl;
        cin >> bur[i];
    }

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n - j - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                int t = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = t;

                t = bur[i];
                bur[i] = bur[i + 1];
                bur[i + 1] = t;

                t = proc[i];
                proc[i] = proc[i + 1];
                proc[i + 1] = t;
            }
        }
    }

    comp[0] = arr[0] + bur[0];
    map<int, int> mp;
    mp[proc[0]] = 1;
    int currCT = comp[0];

    for (int i = 1; i < n; i++)
    {
        int index = -1;
        int prt = INT_MAX;
        cout << currCT << endl;
        for (int j = 1; j < n; j++)
        {
            if (mp[proc[j]] != 1 && arr[j] <= currCT)
            {
                if (prio[j] < prt)
                {
                    prt = prio[j];
                    index = j;
                }
            }
        }
        cout << "index : " << index << endl;
        if (mp[proc[index]] != 1)
        {
            mp[proc[index]] = 1;
            comp[index] = currCT + bur[index];
            currCT = comp[index];
        }
    }

    int sumTAT = 0;
    int sumWT = 0;
    for (int i = 0; i < n; i++)
    {
        TAT[i] = comp[i] - arr[i];
        sumTAT += TAT[i];
        WT[i] = TAT[i] - bur[i];
        sumWT += WT[i];
    }
    cout<<"Pr Prio Arr Bur Comp TAT WT  "<<endl;
    for (int i = 0; i < n; i++)
    {

        cout << proc[i] << "   " << prio[i] << "   " << arr[i] << "   " << bur[i] << "   " << comp[i] << "   " << TAT[i] << "   " << WT[i]<<endl;
    }
}


int mintill(int BT[], int t) {
    int mini = numeric_limits<int>::max();
    int shind = 0;
    for (int i = 0; i <= t; i++) {
        if (BT[i] < mini && BT[i] != 0) {
            mini = BT[i];
            shind = i;
        }
    }
    return shind;
}

void SJF() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    int PRO[n], AT[n], BT[n];

    cout << "Enter processes:\n";
    for (int i = 0; i < n; i++) {
        cin >> PRO[i];
    }

    cout << "Enter arrival time of processes:\n";
    for (int i = 0; i < n; i++) {
        cin >> AT[i];
    }

    cout << "Enter burst time of processes:\n";
    for (int i = 0; i < n; i++) {
        cin >> BT[i];
    }

    cout << "Input:\n";
    cout << "Process  AT    BT\n";
    for (int i = 0; i < n; i++) {
        cout << PRO[i] << "        " << AT[i] << "    " << BT[i] << "\n";
    }

    int temp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - (i + 1); j++) {
            if (AT[j] > AT[j + 1]) {
                temp = AT[j];
                AT[j] = AT[j + 1];
                AT[j + 1] = temp;
                temp = BT[j];
                BT[j] = BT[j + 1];
                BT[j + 1] = temp;
                temp = PRO[j];
                PRO[j] = PRO[j + 1];
                PRO[j + 1] = temp;
            }
        }
    }

    int BT1[n];
    for (int i = 0; i < n; i++) {
        BT1[i] = BT[i];
    }

    cout << "After sorting:\n";
    cout << "Process  AT    BT\n";
    for (int i = 0; i < n; i++) {
        cout << PRO[i] << "        " << AT[i] << "     " << BT[i] << "\n";
    }

    int CT[n], TAT[n], WT[n];
    float avgwt = 0, avgta = 0;
    for (int i = 0; i < n; i++) {
        CT[i] = 0;
    }

    int c = 0;
    int sho = 0;
    int i = 0;
    int cmp = 0;
    int nat = AT[1];

    while (c < n) {
        if (cmp >= AT[n - 1]) {
            sho = mintill(BT, n - 1);
            cmp += BT[sho];
            CT[sho] = cmp;
            BT[sho] = 0;
            c++;
        } else {
            BT[sho] -= nat - cmp;
            cmp += nat - cmp;

            if (BT[sho] == 0) {
                CT[sho] = cmp;
                c++;
            }
            i++;
            if (i < n - 1) {
                nat = AT[i + 1];
                sho = mintill(BT, i);
            }
        }
    }

    for (int j = 0; j < n; j++) {
        TAT[j] = CT[j] - AT[j];
        WT[j] = TAT[j] - BT1[j];
        avgwt += WT[j];
        avgta += TAT[j];
    }

    cout << "PRO    AT    BT    CT    TAT    WT\n";
    for (int j = 0; j < n; j++) {
        cout << PRO[j] << "      " << AT[j] << "     " << BT1[j] << "     " << CT[j] << "     " << TAT[j] << "      " << WT[j] << "\n";
    }

    cout << "Avg WT=" << avgwt / n << "\n";
    cout << "Avg TAT=" << avgta / n << "\n";
}



int main()
{
    cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
    SJF();
    return 0;
}
