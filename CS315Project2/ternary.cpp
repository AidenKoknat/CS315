//-------------------------------------------------
// Author: Aiden Koknat
// Date: 3/3/21
// Description: ternary trees project
//-------------------------------------------------

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// p =< a
// a < p <= b
// b < p

struct treeNode {
    int min;
    int max;
    treeNode * left;
    treeNode * mid;
    treeNode * right;
};

void runDown(treeNode * tree, int num) {
    if (tree->min != NULL) {
        if (tree->max != NULL) {
            if (num <= tree->min) {
                if (tree->left != NULL);
                    // Do Nothing
                else {
                    treeNode * new_treeNode = new treeNode();
                    tree->left = new_treeNode;
                }
                runDown(tree->left, num);
            }
            if ((num > tree->min) && (num <= tree->max)) {
                if (tree->mid != NULL);
                    // Do Nothing
                else {
                    treeNode * new_treeNode = new treeNode();
                    tree->mid = new_treeNode;
                }
                runDown(tree->mid, num);
            }
            if (num > tree->max){
                if (tree->right != NULL);
                    // Do Nothing
                else {
                    treeNode * new_treeNode = new treeNode();
                    tree->right = new_treeNode;
                }
                runDown(tree->right, num);
            }
        }
        else {
            if (num > tree->min)
            tree->max = num;
            else {
                if (tree->left != NULL); 
                else {
                    treeNode * new_treeNode = new treeNode();
                    tree->left = new_treeNode;
                }
                runDown(tree->left, num);
            }
        }
    }
    else {
        tree->min = num;
    }
} // symmetric()

void printTree(treeNode * tree) {
    if (tree == 0x0);
        // DO nothing

    else {
            printTree(tree->left);
            cout << tree->min << " ";
            cout << tree->max << " ";
            printTree(tree->mid);
            cout << tree->min << " ";
            cout << tree->max << " ";
            printTree(tree->right);
            cout << tree->min << " ";
            cout << tree->max << " ";  
    }
}

int main(int argc, char * argv[]) {
    int n = atoi(argv[0]); //Amount of Numbers
    int a = 0;

        // Setup top of tree
        treeNode * treeHead = new treeNode();
        int temp;
        int temp2;
        cin >> temp2;
        treeHead->min = temp2;
        if (temp == treeHead->min);
            cin >> temp;

        if (temp < treeHead->min) {
            int replace = treeHead->min;
            treeHead->min = temp;
            treeHead->max = replace;
        }
        else {
            treeHead->max = temp;
        } 
        // End Top of tree setup

    for (a; a < n; a++) {
        cin >> temp;
        runDown(treeHead, temp);
    }
    printTree(treeHead);
    return 0;
}