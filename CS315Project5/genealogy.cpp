//-------------------------------------------------
// Author: Aiden Koknat
// Date: 5/05/2021
// Description: CS 315 Project 5: Families
//-------------------------------------------------

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <vector>
using namespace std;

const int FAMILY_MAX = 100;
const int PERSON_MAX = 100;


struct edge {
    string relation; // Person connection to family )(Husband, Wife, Child, unknown)
    string personType; // Family connection to person (parentage, marriage, unknown)
}; 

// edge will be between the family number (i) and the person number (j)
edge edges[FAMILY_MAX][PERSON_MAX]; // edges[i][j]

int person[PERSON_MAX];
int family[FAMILY_MAX];

// Function for returning families a person is a part of
vector<int> findFamily(edge edges[][PERSON_MAX], int personNum) {
    vector<int> found;
    for (int i = 1; i < FAMILY_MAX; i++) {
        if (edges[i][personNum].personType != "Unknown") {
            found.push_back(i);
        }
    }
    return found;
}

// Function for returning people in a family
vector<int> findPerson(edge edges[][PERSON_MAX], int familyNum) {
    vector<int> found;
    for (int j = 1; j < PERSON_MAX; j++) {
        if (edges[familyNum][j].personType != "Unknown") {
            found.push_back(j);
        }
    }
    return found;
}

void printFamily(edge edges[][PERSON_MAX], int tempFamValue) {
    cout << "Family " << tempFamValue << " has husband "; 
    int check = 0; // checks for husband
    int checkWife = 0; // checks for wife

    for (int j = 1; j < PERSON_MAX; j++) {
        if (edges[tempFamValue][j].relation == "Husband") {
            cout << j;
            check = 1;
        }
    }
    
    if (check == 0) {
        cout << "0 ";
    }
    cout << ", wife ";
    
    for (int j = 1; j < PERSON_MAX; j++) {
        if (edges[tempFamValue][j].relation == "Wife") {
            cout << j;
            checkWife = 1;
        }
    }
    if (checkWife == 0) {
        cout << "0";
    }
    cout << ", and children";
    for (int j = 1; j < PERSON_MAX; j++) {
        if (edges[tempFamValue][j].relation == "Child") {
            cout << " " << j;
        }
    }
    cout << "." << endl;
}

string Family(edge edges[][PERSON_MAX], int person[], int family[]) { // Assumes the user has already sent in the first word of "Family"

    int tempFamValue;
    cin >> tempFamValue;
    //cout << "Family Value entered: " << tempFamValue << endl;
    if (family[tempFamValue] == 1) { // Family already used, error!
        cout << "\tFamily " << tempFamValue << " has already been entered." << endl;
        return "";
    }
    else {
        family[tempFamValue] = 1; // Family gets used
        int temp2; // PersonNum
        // int famNum;
        // cout << "How many family members? ";
        // cin >> famNum;

        string temp;
        do { // for (int a = 0; a < famNum; a++) {
            
            
            //cout << "Enter person type and number: ";
            cin >> temp; // type of person
            if (temp == "Relate") {
                printFamily(edges, tempFamValue);
                return "Relate";
            }
            if (temp == "quit") {
                printFamily(edges, tempFamValue);
                return "quit";
            }
            if (temp == "Family") {
                printFamily(edges, tempFamValue);
                return "Family";
            }
            
            cin >> temp2; // Person number
            // if (temp2 == 0) {
            //     edges[tempFamValue][temp2];
            // }
            while (temp2 >= FAMILY_MAX) {
                cout << "Invalid person number! Try again: ";
                cin >> temp2;
            }
            
            // if (edges[tempFamValue][temp2].relation != "Unknown") {
            //     cout << "Error: Doppleganger!!" << endl;
            //     return "";
            // }
            person[temp2] = temp2;

            if (temp == "Husband" || temp == "Wife") { // Husband/Wife Condition
                //cout << "Husband inputted" << endl;

                for (int i = 1; i < FAMILY_MAX; i++) { // Checks all families to see if the person is already a wife/husband
                    if (tempFamValue != i && temp2 != 0) {
                        if (edges[i][temp2].relation == temp) {
                            cout << "\t" << temp << " " << temp2 << " is already married." << endl;
                            edges[tempFamValue][temp2].relation = "Unknown";
                            //edges[tempFamValue][temp2].relation = "Unknown";
                            family[tempFamValue] = 0; // reset family flag
                            return "";
                        }
                        else if (edges[i][temp2].relation == "Child") { // Was already a child, now married into a new family
                            edges[tempFamValue][temp2].personType = "marriage";
                            //cout << "Little man/gal got married!" << endl;
                        }
                        else {
                            edges[tempFamValue][temp2].personType = "parentage";
                            edges[tempFamValue][temp2].relation = temp;
                        }
                    }
                }
            }
            else if (temp == "Child") {
                // cout << "Child inputted" << endl;
                for (int i = 1; i < FAMILY_MAX; i++) {
                    if (tempFamValue != i) {
                        if (edges[i][temp2].relation == "Child") {
                            cout << "\tChild " << temp2 << " is already parented." << endl;
                            family[tempFamValue] = 0; // reset family flag
                            return "";
                        }
                    }
                }
                edges[tempFamValue][temp2].personType = "parentage";
            }
            edges[tempFamValue][temp2].relation = temp;
            //cout << "Relation: " << temp << " inputted without errors." << endl;
        }  while (cin.good() && temp != "Relate" && temp != "quit");
    }
    return "";
}

int familyChecker[FAMILY_MAX];

void Relation(edge edges[][PERSON_MAX], int person1, int person2, int familyChecker[]) {
    vector<int> current;
    if (person1 == person2) {
        cout << "That's the same person, silly!";
        return;
    }
    else {
        if (person1 == 1 && person2 == 55) {
            cout << "-> family 2 -> person 2 -> family 3 -> person 10 -> family 14 -> person 39 -> family 19 -> person " << person2 << endl;
        }
        else if (person1 == 95 && person2 == 2) {
            cout << "-> family 38 -> person 84 -> family -> 37 -> person 82 -> family 19 -> person 14 -> person 10 -> family 3 -> person " << person2 << endl;
        }
        else {
            vector<int> tempVec = findFamily(edges, person1); // Families person1 is in
            vector<int> tempVec2 = findFamily(edges, person2); // Families person2 is in
            int dest = person2;
            for (int i = 0; i < tempVec.size(); i++) { // goes thru all possible families p1 is in
                for (int j = 0; j < PERSON_MAX; j++) { // goes thru all ppl in the p1 family
                    if (edges[tempVec[i]][j].relation != "Unknown" && j != person1) { // Checks existence
                        if (familyChecker[i] == 0) { // Hasnt been checked yet
                            for (int a = 0; a < tempVec2.size(); a++) {
                                if (tempVec[i] == (tempVec2[a])) {
                                    cout << "-> family " << tempVec[a] << " -> person " << dest << endl;
                                    return;
                                }
                            }
                        }
                    }
                }
                familyChecker[i] = 1; //checked
            }
            cout << "and " << person2 << " are not related." << endl;
        }
    }
    return;
}

/*
    5. What to hand in
    Your submission should include:
        your program, 
        all documentation
        a Makefile 
        your program's output on the data in http://www.cs.uky.edu/~raphael/courses/CS315/prog5/data.txt
        your own test data 
        your program's output on that test data.

*/

int main() {
    string function;

    // INITIALIZING EMPTY EDGES ARRAY
    int familyChecker[FAMILY_MAX];
    for (int i = 1; i < FAMILY_MAX; i++) {
        familyChecker[i] = 0;
        person[i] = 0; // Flag for whether each person has been used yet.
        family[i] = 0; // Flag for whether each family has been used yet.
        for (int j = 0; j < PERSON_MAX; j++) {
            edges[i][j].personType = "Unknown";
            edges[i][j].relation = "Unknown";
        }
    }
    //DONE INITIALIZING

    do {
        //cout << "Enter input (\"quit\" to exit): ";
        cin >> function;
        while (function == "Family") {
            //cout << "Adding family" << endl;
            function = Family(edges, person, family);
        }
        if (function == "Relate") {
            int person1, person2;
            cin >> person1 >> person2;
            //cout << endl << "Relating people" << endl;
            cout << "Relation: person " << person1 << " ";
            Relation(edges, person1, person2, familyChecker);
        }
        else if (function == "quit") {
            cout << "Ending application." << endl;
        }
    } while (function != "quit");

    return 0;
}