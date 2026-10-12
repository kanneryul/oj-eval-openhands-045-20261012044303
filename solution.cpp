#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

struct ElevatorSystem {
    int currentFloor;
    int direction; // 1 for up, -1 for down
    
    // Heaps for pending requests
    priority_queue<int, vector<int>, greater<int>> minHeapUp;   // min heap for upward requests
    priority_queue<int> maxHeapDown;                           // max heap for downward requests
    
    // Sets to track which requests are still active (for lazy deletion)
    set<int> activeRequestsUp;
    set<int> activeRequestsDown;
    
    ElevatorSystem() {
        currentFloor = 0;
        direction = 1; // start going up
    }
    
    void addRequest(int x) {
        if (x >= currentFloor) {
            minHeapUp.push(x);
            activeRequestsUp.insert(x);
        } else {
            maxHeapDown.push(x);
            activeRequestsDown.insert(x);
        }
    }
    
    void cancelRequest(int x) {
        if (x >= currentFloor) {
            activeRequestsUp.erase(x);
        } else {
            activeRequestsDown.erase(x);
        }
    }
    
    void cleanHeaps() {
        // Clean up cancelled requests from heaps (lazy deletion)
        while (!minHeapUp.empty() && activeRequestsUp.find(minHeapUp.top()) == activeRequestsUp.end()) {
            minHeapUp.pop();
        }
        while (!maxHeapDown.empty() && activeRequestsDown.find(maxHeapDown.top()) == activeRequestsDown.end()) {
            maxHeapDown.pop();
        }
    }
    
    void action() {
        cleanHeaps();
        
        if (minHeapUp.empty() && maxHeapDown.empty()) {
            // No pending requests, stay still
            return;
        }
        
        if (direction == 1) {
            // Going up
            if (!minHeapUp.empty()) {
                // Serve the nearest upward request
                int target = minHeapUp.top();
                minHeapUp.pop();
                activeRequestsUp.erase(target);
                currentFloor = target;
            } else {
                // No more upward requests, reverse direction
                direction = -1;
                if (!maxHeapDown.empty()) {
                    int target = maxHeapDown.top();
                    maxHeapDown.pop();
                    activeRequestsDown.erase(target);
                    currentFloor = target;
                }
            }
        } else {
            // Going down
            if (!maxHeapDown.empty()) {
                // Serve the nearest downward request
                int target = maxHeapDown.top();
                maxHeapDown.pop();
                activeRequestsDown.erase(target);
                currentFloor = target;
            } else {
                // No more downward requests, reverse direction
                direction = 1;
                if (!minHeapUp.empty()) {
                    int target = minHeapUp.top();
                    minHeapUp.pop();
                    activeRequestsUp.erase(target);
                    currentFloor = target;
                }
            }
        }
    }
    
    int locate() {
        return currentFloor;
    }
};

int main() {
    int n;
    scanf("%d", &n);
    
    ElevatorSystem elevator;
    
    for (int i = 0; i < n; i++) {
        char command[20];
        scanf("%s", command);
        
        if (command[0] == 'a') {
            if (command[1] == 'c') {
                // action
                elevator.action();
            } else {
                // add
                int x;
                scanf("%d", &x);
                elevator.addRequest(x);
            }
        } else if (command[0] == 'c') {
            // cancel
            int x;
            scanf("%d", &x);
            elevator.cancelRequest(x);
        } else if (command[0] == 'l') {
            // locate
            printf("%d\n", elevator.locate());
        }
    }
    
    return 0;
}