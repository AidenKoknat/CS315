//-------------------------------------------------
// Author: Aiden Koknat
// Date: 3/28/21
// Description: CS 315 Project 3
//-------------------------------------------------

/*
One generalization of binary trees is the k-d tree, which stores k-dimensional data. 
Every internal node of a k-d tree indicates the dimension d and the value v in that dimension that it discriminates by. 
An internal node has exactly two children, containing data that is less-than-or-equal and data that is greater than v in dimension d. 
For example, if the node distinguishes on dimension 1, value 107, 
then the left child is for data with y value less than or equal to 107, 
and the right child is for data with y value greater than 107. 
Leaf nodes represent a bucket containing no more than b elements of k-dimensional data. 
All data are found in the leaves.

There are several strategies for building k-d trees. 
The offline method:
    (1) accumulates all the data in an array 
    (2) finds the best dimension to discriminate on, namely, the one with the widest range 
        (break ties by choosing the earliest dimension that has the widest range) 
    (3) finds the best value of that dimension to discriminate on, namely, the median value in that dimension 
        (using the QuickSelect algorithm with Lomuto's partitioning method) 
    (4) separates the data into two subarrays based on that discriminant 
    (5) recurses back to step 2 on each subarray. 
Recursion terminates when an array has size b or smaller. One can also devise online methods that add to existing trees.

Requirements:
Write a program called kd that: 
    (1) takes three parameters, all positive integers: k specifies the number of dimensions, 
        n specifies how many data points are to be placed in the tree, and p specifies the number of probes into the tree; 
    (2) reads from standard input a list of n k-dimensional integer data points; 
    (3) builds a k-d tree with those n values using the offline method, with b set to 10 (and ties going to the left subtree); 
    (4) reads p k-dimensional data values, called probes, and for each probe, 
        lists all the data points stored in the bucket where the probe would be found if it were in the tree.

In step 3, you may assume that all integer data are distinct.
*/

// COMPILE WITH g++ -g -o kd kd.cpp

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

// dimention (size) of each data point

//LIMITS (DELETE LATER!!!)
int k; // dimention (size) of each data point
//END LIMITS

int n; // number of data points in the tree
int p; // number of probes in the tree (will find other data points in a certain selected bucket) [[wtf is a bucket tho??]]
int const b = 10; // Maximum number of points in a bucket

// Internal nodes dont have data points, they just have boundaries for the numbers to flow into their left and right parts

void mySwap(vector<vector<int>> A, int a, int b) {
    vector<int> temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}

int findRange(vector<vector<int>> dataVal, int k) { // Max Range tells what dimension to discriminate with. With grouped points like (x,y,z),
    int maxRange = 0;                          // it finds the dimension that has the greatest range amoung the list of points.
    int maxIndex = 0;                          // it is a 3 dimensional point as of now because k = 3.
    for (int i = 0; i < k; i++) {
        int low, high;
        low = dataVal[0][i]; //dataVal[i][0]
        high = dataVal[0][i]; //dataVal[i][0]
        for (int j = 1; j < dataVal.size(); j++) {
            if (dataVal[j][i] > high) {
                high = dataVal[i][j];
            }
            if ((high-low) > maxRange) {
                maxRange = high - low;
                maxIndex = i;
            }
        }
    }
    return maxIndex;
}

int findMedianIndex(vector<vector<int>> A, int d) {
    for (int i = 0; i < A.size(); i++) {
        for(int j = i + 1; j < A.size(); j++) {
            if (A[i][d] > A[j][d]) {
                mySwap(A, i, j);
            }
        }
    }
    int medianIndex = (A.size()-1)/2;
    return medianIndex;
}

// int Lomuto(vector<vector<int>> A, int d) { // d = dimension with highest range
//     int hi = A.size()/k; 
//     int pivot = A[hi][d]; // rightmost value in the vector array (should always be the greatest, and if not, should swap accordingly)
//     int lo = 0;           // index of leftmost value in the array
//     for (int j = lo; j < hi - 1; j++) { // 
//         if (A[j][d] != pivot) {
//             if (A[j][d] >= pivot) {
//                 int p;
//                 int c = j + 1;
//                 for (p = j; p < pivot; p++) {

//                     if (A[j][d] > A[c][d]) {
//                          mySwap(A, j, c, d);
//                     }
//                     else {
//                         c++;
//                     }
//                 }
//                 pivot = A[p-1][d];
//             }
//         }   
//     }
//     return A[A.size()/(k * 2)][d];
// }

struct kdTree {
    vector<vector<int>> data;
    //int data[b]<k>;
    kdTree *left;
    kdTree *right;
    kdTree *parent;
};

kdTree* createTree(vector<vector<int>> A, kdTree* given) {
    kdTree* newNode = (kdTree*) malloc(sizeof(kdTree));
    newNode->parent = given;

    if (A.size() <= b) {
        newNode->data = A;
        newNode->left = NULL;
        newNode->right = NULL;

        return newNode;
    }
    else {
        vector<vector<int>> bottomHalf;
        vector<vector<int>> topHalf;
        int dimension = findRange(A, k);
        int medianIndex = findMedianIndex(A, dimension);
        int v = A[medianIndex][dimension];
        int i = 0;
        for (i = 0; i <= medianIndex; i++) {
            bottomHalf.push_back(A[i]);
        }
        for (i; i < A.size(); i++) {
            topHalf.push_back(A[i]);
        }
        vector<int> discriminant (k);
        discriminant[dimension] = v;
        vector<vector<int>> temp2;
        temp2.push_back(discriminant);
        newNode->data = temp2;
        newNode->left = createTree(bottomHalf, newNode);
        newNode->right = createTree(topHalf, newNode);
        return newNode;
    }
};

void probeSearch(kdTree* node, vector<int> probe) { // with Probes ;3
    if (node->left != NULL && node->right != NULL) {
        int d, v;
        for (int i = 0; i < k; i++) {
            if (node->data[0][i] != 0) {
                v = node->data[0][i];
                d = i;
                break;
            }
        }

        if (probe[d] <= v) {
            probeSearch(node->left, probe);
        }
        else {
            probeSearch(node->right, probe);
        }
    }
    else {
        cout << "probe ";
        for (int i = 0; i < k; i++) {
            cout << probe[i] << " ";
        }
        cout << "reaches bucket: " << node->data.size() << " elements\n";
        for (int i = 0; i < node->data.size(); i++) {
            for (int j = 0; j < k; j++) {
                cout << node->data[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cout << "Incorrect number of parameters.\n";
        exit(-3);
    }

    k = stoi(argv[1]);
    n = stoi(argv[2]);
    p = stoi(argv[3]);

    vector<vector<int>> tempVec;
    for (int i = 0; i < n; i++) {
        vector<int> temp;
        for (int j = 0; j < k; j++) {
            int val;
            cin >> val;
            temp.push_back(val);
        }
        tempVec.push_back(temp);
    }

    kdTree* root = createTree(tempVec, NULL);
    vector<vector<int>> probes;
    for (int i = 0; i < p; i++) {
        vector<int> firstProbe;
        for (int j = 0; j < k; j++) {
            int temp3;
            cin >> temp3;
            firstProbe.push_back(temp3);
        }
        probes.push_back(firstProbe);
    }
    for (int i = 0; i < p; i++) {
        probeSearch(root, probes[i]);
    }  
    return 0;
}
