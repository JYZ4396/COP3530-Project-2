//
// Created by 13402 on 2026/11/1.
//
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono> //This is for checking how long the code run
using namespace std::chrono;

#include "CleanupActivity.h"
#include "maxheap.h"
#include "redblacktree.h"


using namespace std;

int main() {
    cout<<"check if program is running"<<endl;

    vector<CleanupActivity> vec;

    //these are all files we need to read
    vector<string> filenames={
        "detailed-summary-united-states 2019.csv",
        "detailed-summary-united-states 2020.csv",
        "detailed-summary-united-states 2021.csv",
        "detailed-summary-united-states 2022.csv",
        "detailed-summary-united-states 2023.csv",
        "detailed-summary-united-states 2024.csv",
        "detailed-summary-united-states 2025.csv",
        "detailed-summary-united-states 2026.csv"
    };

    for (string filename:filenames) {
        ifstream file(filename);

        if (!file.is_open()) {
            cout<<"Cannot open: "<<filename <<endl;
        }

        string line;
        getline(file, line); //this is to skip the top row where are variable names

        while (getline(file, line)) {

            stringstream ss(line);
            vector<string> cols; //This will store the value for each col in a row
            string col;

            //ss.eof() return true when we read till the end of ss
            while (!ss.eof()) {


                //some cell such as location has invisible quotation mark
                //if read directly county,state,country will be seperated to
                //three cell
                //this if condition will check whether cell has quote mark and
                //read all info in the mark as one col
                if(ss.peek() == '"') {
                    ss.get();
                    getline(ss, col, '"');
                    ss.get();
                }
                else {
                    getline(ss, col, ',');
                }
                cols.push_back(col);
            }
            //The last row is the summation of all cleanup activty in the year,
            //we also need to skip this row
            if (cols[0]=="Totals:") {
                continue;
            }

            CleanupActivity activity;
            //after reading a line of data, we start to create cleanupactivity
            //based on csv file, first column is the id, second is the location, ninth is the
            //date
            activity.id = cols[0];
            activity.location = cols[1];
            activity.date = cols[8];

            //After 2022, the csv file remove 13 cols, but the totol count
            //of a cleanup activity is still the last col, so we can use
            //cols.back() to read the totalCount.
            //However, because the file use empty space to represent 0
            //we have to check if cols.back() is empty or not then
            //assign value to it
            activity.totalCount = 0;

            if (!cols.back().empty()) {
                activity.totalCount = stoi(cols.back());
            }

            vec.push_back(activity);
        }
        cout << "Total cleanup activities: " << vec.size() <<endl;


    }
    //this is the setting for chrono that check the duration of code
    //I copy paste the code from the website and add the task I want to check
    //the executation time at the middle(correct) position
    //this is the geeksforgeeks page: https://www.geeksforgeeks.org/cpp/chrono-in-c/

    auto start = high_resolution_clock::now();

    //this is to build tree
    RedBlackTree tree;
    for (int i = 0; i < vec.size(); i++) {
        tree.insert(vec[i]);
    }

    auto end = high_resolution_clock::now();
    //default is microsecond, and that's unusual to check, so i divide 1000 make it
    //become ms
    double duration = duration_cast<microseconds>(end - start).count()/1000.0;

    cout << "Build Red-Black Tree: "
         << duration
         << "ms"<<endl;


    start=high_resolution_clock::now();

    //This function will reverseInorder a public vector called topCount,
    //It ranked cleanup activity count from highest to lowest, then we
    //only need to read first 20 cleanup activity and finished the task
    tree.getTopCount(20);
    vector<CleanupActivity> top20;
    //because topcount is a vector contained node, to read cleanup activity needs
    //to be tree.topcount[i].activity
    for (int i=0;i<20;i++) {
        top20.push_back(tree.topcount[i].activity);
    }

    end=high_resolution_clock::now();
    //default is microsecond, and that's unusual to check, so i divide 1000 make it
    //become ms
    duration=duration_cast<microseconds>(end - start).count() /1000.0;

    cout << "Time for finding top 20 count Cleanup Events: "
         << duration
         << "ms"<<endl;



    return 0;
}
