//-------------------------------------------------
// Author: Aiden Koknat
// Class: CS 315
// Date: 2/12/21
// Description: Trains project cpp file
//-------------------------------------------------

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct node {
    int size;
    node* next;
    node* previous;
};

struct train {
    int carNum;
    int value;
    node* head;
};

void pushFront(node* old_head, int sizeInput) {
    node* new_car = new node();
    new_car->size = sizeInput;
    new_car->previous = NULL;
    new_car->next = old_head;
    old_head->previous = new_car;
}

void pushRear(node* old_rear, int sizeInput) {
    node* new_car = new node();
    new_car->size = sizeInput;
    old_rear->next = new_car;
    new_car->previous = old_rear;
    new_car->next = NULL;
    
}

node* identifyHead(node* input) {
    if (input->previous != NULL) {
        return identifyHead(input->previous);
    }
    else return input;
}

node* identifyRear(node* input) {
    if (input->next != NULL) {
        return identifyRear(input->next);
    }
    else return input;

}

void printTrains(train d, int dNum, int rearOrFront, int rNum) {
    cout << "Train " << dNum;
    if (rearOrFront == 1) {
        cout << " donated it's front car to Train " << rNum << "!" << endl;

    }
    if (rearOrFront == 2) {
        cout << " donated it's rear car to Train " << rNum << "!" << endl;
    }
}

void printValue(train d[], int tNum) {
    cout << "Value of Train " << tNum << ": " << d[tNum].value << endl;
}

void printHighest(int trainNum, train t[]) {
    int highestValue = 0;
    int highestValueTrain = 0;
    for (int i = 0; i < trainNum; i++) {
        if (t[i].value > highestValue) {
            highestValue = t[i].value;
            highestValueTrain = i;
        }
    }
    cout << "Train with highest value: Train " << highestValueTrain << "!" << endl;
}

bool fixArguments(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Invalid number of arguments!" << endl;
        return false;
    }
    if (atoi(argv[1]) < 1) {
        cout << "Invalid number of Trains!" << endl;
        return false;
    }
    if (atoi(argv[2]) < 1) {
        cout << "Invalid number of Train Cars!" << endl;
        return false;
    }
    if (atoi(argv[3]) < 0) {
        cout << "Invalid number of Steps!" << endl;
        return false;
    }
    else
        return true;
}

int main(int argc, char* argv[]) {
    if (fixArguments(argc, argv) == true) {
        cout << endl << "Train Switching!" << endl;
        cout << "----------------" << endl;
        int trainNum = atoi(argv[1]);
        int startCars = atoi(argv[2]);
        int numSteps = atoi(argv[3]);

        // Initialization/Setup
        // Trains Setup
        train* trains = new train[trainNum];
        for (int i = 0; i < trainNum; i++) {
            trains[i].carNum = startCars;

            for (int j = 1; j <= startCars; j++) { // Initializing Cars
                if (j == 1) {
                    node* first_car = new node();
                    first_car->size = j;
                    first_car->previous = NULL;
                    first_car->next = NULL;
                    trains[i].head = first_car;
                }
                else {
                    pushRear(identifyRear(trains[i].head), j);
                }
            }
            trains[i].value = startCars * (startCars + 1) * (2 * (startCars)+1) / 6; // Starting Value of Train
        }
        // End Setup

        // Train Switching
        for (int i = 0; i < numSteps; i++) {

            int trainDonator;
            cin >> trainDonator;
            trainDonator = trainDonator % trainNum; // randomly chooses a train to donate

            int frontOrBack;
            cin >> frontOrBack;
            frontOrBack = (frontOrBack % 2) + 1; // 1 is front, 2 is back; randomly chooses

            int trainReciever;
            cin >> trainReciever;
            trainReciever = trainReciever % trainNum; // randomly chooses a train to recieve
           
            for (int i = 0; i < trainNum; i++) { // Checks for 0 car trains
                if (trains[i].carNum == 0) {
                    cout << "Train " << i << " has no cars left!" << endl;
                    printHighest(trainNum, trains);
                    return 0; // Ends function
                }
            }

            printTrains(*trains, trainDonator, frontOrBack, trainReciever);
            if (frontOrBack == 1) { // Front car is donated
                pushFront(trains[trainReciever].head, trains[trainDonator].head->size); // Gives car to recieving train
                trains[trainReciever].carNum++;
                trains[trainReciever].head = identifyHead(trains[trainReciever].head); // Sets recieving trains head car
                trains[trainReciever].value = trains[trainReciever].value + (trains[trainDonator].head->size) * (trains[trainReciever].carNum);
                printValue(trains, trainReciever);

                // Removing head from Donator and Setting new head
                if (trains[trainDonator].head->next == NULL) {
                    delete(trains[trainDonator].head);
                    trains[trainDonator].carNum--;
                    trains[trainDonator].value = 0;
                    printValue(trains, trainDonator);
                }
                else {
                    node* temp = trains[trainDonator].head->next; // Sets Temporary Value for new head Node
                    temp->previous = NULL; // Cuts off the connection old head had to new head
                    trains[trainDonator].value = trains[trainDonator].value - (trains[trainDonator].head->size);
                    delete(trains[trainDonator].head); // Frees space from old head
                    trains[trainDonator].carNum--;
                    trains[trainDonator].head = temp; // Sets new 
                    printValue(trains, trainDonator);
                }
            }
            if (frontOrBack == 2) { // Back car is donated
                pushRear(identifyRear(trains[trainReciever].head), identifyRear(trains[trainDonator].head)->size); // Gives car to recieving train
                trains[trainReciever].carNum++;
                trains[trainReciever].value = trains[trainReciever].value + (identifyRear(trains[trainDonator].head)->size) * (trains[trainReciever].carNum);
                printValue(trains, trainDonator);
                // Removing rear from Donator
                if (trains[trainDonator].head->next == NULL) {
                    delete(trains[trainDonator].head);
                    trains[trainDonator].carNum--;
                    trains[trainDonator].value = 0;
                    printValue(trains, trainDonator);
                }
                else {
                    node* temp = identifyRear(trains[trainDonator].head); // Sets rear to temp for easy deletion
                    identifyRear(trains[trainDonator].head)->previous->next = NULL; // Gets rid of rear connectors
                    trains[trainDonator].value = trains[trainDonator].value - (identifyRear(trains[trainDonator].head)->size * trains[trainDonator].carNum);
                    delete(temp); // Frees space from old rear
                    trains[trainDonator].carNum--;
                    printValue(trains, trainDonator);
                }
            }
        }
        printHighest(trainNum, trains);
    }
        return 0;
}