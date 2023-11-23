#include <iostream>
using namespace std;

class CPUS
{

public:
    int n;
    int *arr, *bur, *proc, *comp, *tat, *wt, *prio;
    CPUS()
    {
        cout << "Enter total number of processes " << endl;

        cin >> n;
        arr = new int[n];
        bur = new int[n];
        proc = new int[n];
        comp = new int[n];
        tat = new int[n];
        wt = new int[n];
        cout << "Enter Process No, Arrival Time and Burst Time of Each Process " << endl;
        for (int i = 0; i < n; i++)
        {
            cin >> proc[i];
            cin >> arr[i];
            cin >> bur[i];
        }
    }
    void FCFS()
    {
        // Sort All records according to the arrival time
        for (int j = 0; j < n; j++)
        {
            for (int i = 0; i < n - j - 1; i++)
            {
                if (arr[i] > arr[i + 1])
                {
                    swap(arr[i],arr[i+1]);
                    swap(bur[i],bur[i+1]);
                    swap(proc[i],proc[i+1]);
                }
            }
        }

        int curr = 0;
        for (int i = 0; i < n; i++)
        {
            if (arr[i] <= curr)
            {
                comp[i] = curr + bur[i];
                curr = comp[i];
            }
            else
            {
                comp[i] = arr[i] + bur[i];
                curr = comp[i];
            }
            tat[i] = comp[i] - arr[i];
            wt[i] = tat[i] - bur[i];
        }
    }

    void SJF()
    {
    }
    void priority()
    {
        prio = new int[n];
        cout << "Enter the priorities of processes " << endl;
        for (int i = 0; i < n; i++)
        {
            cin >> prio[i];
        }

        // Sort All records according to the arrival time
        for (int j = 0; j < n; j++)
        {
            for (int i = 0; i < n - j - 1; i++)
            {
                if (arr[i] > arr[i + 1])
                {
                    swap(arr[i],arr[i+1]);
                    swap(bur[i],bur[i+1]);
                    swap(proc[i],proc[i+1]);
                    swap(prio[i],prio[i+1]);
                }
            }
        }

        
    }
};

int main()
{
}