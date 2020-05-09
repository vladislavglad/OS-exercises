/**
 * @file algs.cpp
 * @purpose: Simulate 3 different disk scheduling algorithms.
 * 
 * @author vladislavglad
 * @version 1.0 
 * @date 05/08/20
 */

#include <iostream>
#include <string>

#define CYLINDERS 5000
#define REQUESTS 1000

using namespace std;

//Function headers. 
void generateRequests(int *arr);
int* copyArr(int *arr);
void printRequests(int *arr);
void sort(int *arr);
int FCFS(int *arr, int start);
int CSCAN(int *arr, int start);
int CLOOK(int *arr, int start);

int main(int argc, char *argv[]) {

    int startingIndex;
    int requests[REQUESTS];

    //Check validity of arguments or lack thereof.
    if (argc >= 2) {
        startingIndex = atoi(argv[1]); //convert string to an integer.
    } else {
        cout << "Invalid number of command line arguments:" << endl;
        cout << "\tProvide at least 1 numerical argument for ";
        cout << "the initial position of the disk head." << endl;
        cout << "\tExample usage: " << argv[0] << " 3320" << endl;
        exit(1);
    }

    if (startingIndex > CYLINDERS - 1 || startingIndex < 0) {
        cout << "Invalid initial position of the disk head:" << endl;
        cout << "\tThe initial position you provided is out of bounds."<< endl;
        cout << "\tPlease provide a valid position in the range 0-"<< CYLINDERS - 1 << endl;
        exit(1);
    }

    cout << "Your startingIndex is: " << startingIndex << endl;

    generateRequests(requests);

    // cout << "Disk requests queue: ";
    // printRequests(requests);

    cout << "Total head movements FCFS: " << FCFS(requests, startingIndex) << endl;
    cout << "Total head movements C-SCAN: " << CSCAN(requests, startingIndex) << endl;
    cout << "Total head movements C-LOOK: " << CLOOK(requests, startingIndex) << endl;

    return 0;
}

/**
 * Populates passed array with random integers in the range 0 to CYLINDERS.
 *
 * @param arr - Array that will be populated with random integers.  
 */
void generateRequests(int *arr) {
    /*
    Seed random number generator with current time
    to truly randomize generated requests.
    */
    srand(time(NULL));

    for (int i = 0; i < REQUESTS; i++) {
        //Generates random numbers in the range [0 to CYLINDERS].
        arr[i] = rand() % CYLINDERS; 
    }
}

/**
 * Prints out passed array in {...} brackets.
 * 
 * @param arr - Array that will be printed.
 */
void printRequests(int *arr) {
    cout << "{";
    for (int i = 0; i < REQUESTS; i++) {
        cout << arr[i] << (i != REQUESTS - 1 ? ", " : "}\n");
    }
}

/**
 * Copies contents of the passed array into a temporary array
 * which is returned upon exit.
 * 
 * @param arr - Array that will be copied.
 * @return pointer to the new copy array.
 */
int* copyArr(int *arr) {
    int *temp = new int[REQUESTS];

    for (int i = 0; i < REQUESTS; i++) {
        temp[i] = arr[i];
    }

    return temp;
}

/**
 * Sort contents of the passed array in the ascending order,
 * using "selection sort" algorithm.
 * 
 * @param - Array that needs to be sorted.
 */
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

/**
 * Algorithm that services requests based on when they come in into the queue.
 * Thus, First Come First Serve.
 * 
 * @param - Array of requests that needs to be serviced.
 * @param - Initial position of the disk head.
 * @return total number of disk head movements.
 */
int FCFS(int *arr, int start) {
    int headMovement = 0;
    int lastPosition = start;

    for (int i = 0; i < REQUESTS; i++) {
        headMovement += abs(lastPosition - arr[i]);

        lastPosition = arr[i];
    }
    return headMovement;
}

/**
 * Algorithm that moves the disk head from one end of the disk to the other, 
 * servicing requests as it goes. When it reaches the other end it immediately 
 * returns to the beginning of the disk to service remaining requests.
 * 
 * @param - Array of requests that needs to be serviced.
 * @param - Initial position of the disk head.
 * @return total number of disk head movements.
 */
int CSCAN(int *arr, int start) {
    int headMovements = 0;
    int lastPosition = start;

    /*
    Make a copy of the requests array 
    to preserve the original order
    */
    int *temp = copyArr(arr);
    sort(temp);

    /*
    Since the array is sorted, 
    find an index (within temp array) with a requested position 
    that is greater than the initial position of the disk head. 
    */
    int nextHighest = 0;
    while(lastPosition > temp[nextHighest]) {
       nextHighest++;
    }

    //Save this index now to later process the remaining left part.
    int midwayIndex = nextHighest;

    //Proccess right part of the array.
    for (nextHighest; nextHighest < REQUESTS; nextHighest++) {
        headMovements+= abs(lastPosition - temp[nextHighest]);
        lastPosition = temp[nextHighest];
    }

    //Move completely until the end.
    headMovements+= abs(lastPosition - (CYLINDERS-1));

    //Move completely back to the begining.
    headMovements+= CYLINDERS - 1;
    lastPosition = 0;

    //Finally, proccess left part of the array.
    for (int i = 0; i < midwayIndex; i++) {
        headMovements+= abs(lastPosition - temp[i]);
        lastPosition = temp[i];
    }

    delete [] temp;
    return headMovements;    
}

/**
 * Algorithm that is closly resembles C-SCAN discussed before.
 * However, this one moves the disk head from one extreme element 
 * to another instead of moving all the to one end of the CYLINDER 
 * and then all the way back to the begining
 *  
 * @param - Array of requests that needs to be serviced.
 * @param - Initial position of the disk head.
 * @return total number of disk head movements.
 */
int CLOOK(int *arr, int start) {
    int headMovement = 0;
    int lastPosition = start;

    int *temp = copyArr(arr);
    sort(temp);

    int nextHighest = 0;
    while (lastPosition > temp[nextHighest])
        nextHighest++;

    int midwayIndex = nextHighest;

    for (nextHighest; nextHighest < REQUESTS; nextHighest++) {
        headMovement+= abs(lastPosition - temp[nextHighest]);
        lastPosition = temp[nextHighest];
    }

    //Move until the extreme element in the array (on the other end).
    headMovement+= abs(lastPosition - temp[0]);
    lastPosition = temp[0];

    //Process the remainig requests.
    for (int i = 1; i < midwayIndex; i++) {
        headMovement+= abs(lastPosition - temp[i]);
        lastPosition = temp[i];
    }

    delete [] temp;
    return headMovement;
}
