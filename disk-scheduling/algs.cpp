#include <iostream>
#include <string>

#define CYLINDERS 200
#define REQUESTS 8

using namespace std;

int startingIndex;
int requests[REQUESTS] = {98, 183, 37, 122, 14, 124, 65, 67};

void generateRequests(int *requests);
int* copyArr(int *requests);
void printRequests(int *requests);
void sort(int *arr);
int FCFS(int *requests);
int CSCAN(int *requests);

int main(int argc, char *argv[]) {

    if (argc >= 2) {
        startingIndex = atoi(argv[1]);
    } else {
        cout << "Invalid number of command line arguments!" << endl;
        exit(1);
    }

    if (startingIndex > CYLINDERS - 1) {
        cout << "Your startingIndex is out of bounds!" << endl;
        exit(1);
    }

    cout << "Your startingIndex is: " << startingIndex << endl;

    cout << "Disk requests: ";
    printRequests(requests);

    cout << "Total head movements FCFS: " << FCFS(requests) << endl;
    cout << "Total head movements CSCAN: " << CSCAN(requests) << endl;

    return 0;
}

void generateRequests(int *requests) {
    /*
    Seed random number generator with current time
    to truly randomize generated requests.
    */
    srand(time(NULL));

    for (int i = 0; i < REQUESTS; i++) {
        //Generates numbers in the range 0 to 5000
        requests[i] = rand() % CYLINDERS; 
    }
}

void printRequests(int *requests) {
    for (int i = 0; i < REQUESTS; i++) {
        cout << requests[i] << (i != REQUESTS - 1 ? ", " : " \n");
    }
}

int* copyArr(int *requests) {
    int *temp = new int[REQUESTS];

    for (int i = 0; i < REQUESTS; i++) {
        temp[i] = requests[i];
    }

    return temp;
}

void sort(int *arr) {
    for (int i = 0; i < REQUESTS-1; i++) {
        int min = i;
        for (int j = i + 1; j < REQUESTS; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

int FCFS(int *arr) {
    int headMovement = 0;
    int lastPosition = startingIndex;

    for (int i = 0; i < REQUESTS; i++) {
        headMovement += abs(lastPosition - arr[i]);

        lastPosition = arr[i];
    }
    return headMovement;
}

int CSCAN(int *arr) {
    int headMovements = 0;
    int lastPosition = startingIndex;

    int *temp = copyArr(arr);
    sort(temp);

    int nextHighest = 0;
    while(startingIndex > temp[nextHighest]) {
       nextHighest++;
    }

    //Save this index to proccess left part.
    int midwayIndex = nextHighest;

    //Proccess right part.
    for (int i = nextHighest; nextHighest < REQUESTS; nextHighest++) {
        headMovements+= abs(lastPosition - temp[nextHighest]);
        lastPosition = temp[nextHighest];
    }

    //move until the end.
    headMovements+= abs(lastPosition - (CYLINDERS-1));

    //move back to the begining.
    headMovements+= CYLINDERS - 1;
    lastPosition = 0;

    //Proccess left part.
    for (int i = 0; i < midwayIndex; i++) {
        headMovements+= abs(lastPosition - temp[i]);
        lastPosition = temp[i];
    }

    delete [] temp;
    return headMovements;    
}