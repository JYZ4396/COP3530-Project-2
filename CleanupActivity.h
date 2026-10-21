//
// Created by 13402 on 2026/10/21.
//

#ifndef CLEANUPACTIVITY_H
#define CLEANUPACTIVITY_H

#include <string>

//Here I create a struct CleanupActivity
//id is Cleanup ID, col A in CSV
//date is Cleanup Date, col I
//location is Zone, which is col B
//totalCount is Total Items Collected, col BJ
//If the total item collected for a cleanup activity is empty then we assume it's 0

//This will be similar to the gatorID stuff in the project 1, and we will implement it
//in maxheap and red black tree

struct CleanupActivity {
    std::string id;
    std::string date;
    std::string location;
    int totalCount;

    CleanupActivity() {
        totalCount=0;
    }

    CleanupActivity(
        const std::string& id,
        const std::string& date,
        const std::string& location,
        long long totalCount
    ) {
        this->id=id;
        this->date=date;
        this->location=location;
        this->totalCount=totalCount;
    }
};

#endif //CLEANUPACTIVITY_H