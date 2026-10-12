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
    
    // All pending requests
    set<int> pendingRequests;
    
    ElevatorSystem() {
        currentFloor = 0;
        direction = 1; // start going up
    }
    
    void addRequest(int x) {
        pendingRequests.insert(x);
    }
    
    void cancelRequest(int x) {
        pendingRequests.erase(x);
    }
    
    void action() {
        if (pendingRequests.empty()) {
            // No pending requests, stay still
            return;
        }
        
        // Find nearest request in current direction
        int target = -1;
        
        if (direction == 1) {
            // Going up - find smallest floor >= currentFloor
            auto it = pendingRequests.lower_bound(currentFloor);
            if (it != pendingRequests.end()) {
                target = *it;
            }
        } else {
            // Going down - find largest floor <= currentFloor
            auto it = pendingRequests.upper_bound(currentFloor);
            if (it != pendingRequests.begin()) {
                --it;
                target = *it;
            }
        }
        
        if (target != -1) {
            // Found request in current direction
            pendingRequests.erase(target);
            currentFloor = target;
        } else {
            // No request in current direction, reverse direction
            direction = -direction;
            
            // Find nearest request in new direction
            if (direction == 1) {
                // Now going up
                auto it = pendingRequests.lower_bound(currentFloor);
                if (it != pendingRequests.end()) {
                    target = *it;
                }
            } else {
                // Now going down
                auto it = pendingRequests.upper_bound(currentFloor);
                if (it != pendingRequests.begin()) {
                    --it;
                    target = *it;
                }
            }
            
            if (target != -1) {
                pendingRequests.erase(target);
                currentFloor = target;
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