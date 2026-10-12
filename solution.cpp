#include <cstdio>
#include <iostream>
using namespace std;

const int MAX_REQUESTS = 500000;

struct ElevatorSystem {
    int currentFloor;
    int direction; // 1 for up, -1 for down
    
    // Pending requests
    int requests[MAX_REQUESTS];
    int requestCount;
    
    ElevatorSystem() {
        currentFloor = 0;
        direction = 1; // start going up
        requestCount = 0;
    }
    
    void addRequest(int x) {
        requests[requestCount++] = x;
    }
    
    void cancelRequest(int x) {
        for (int i = 0; i < requestCount; i++) {
            if (requests[i] == x) {
                // Shift elements to remove
                for (int j = i; j < requestCount - 1; j++) {
                    requests[j] = requests[j + 1];
                }
                requestCount--;
                break;
            }
        }
    }
    
    void action() {
        if (requestCount == 0) {
            // No pending requests, stay still
            return;
        }
        
        int target = -1;
        int minDistance = 1000000000; // Large number
        
        // Find nearest request in current direction
        for (int i = 0; i < requestCount; i++) {
            int floor = requests[i];
            int distance = floor - currentFloor;
            
            if (direction == 1) {
                // Going up - look for floors >= currentFloor
                if (distance >= 0 && distance < minDistance) {
                    minDistance = distance;
                    target = floor;
                }
            } else {
                // Going down - look for floors <= currentFloor
                if (distance <= 0 && -distance < minDistance) {
                    minDistance = -distance;
                    target = floor;
                }
            }
        }
        
        if (target != -1) {
            // Found request in current direction
            cancelRequest(target);
            currentFloor = target;
        } else {
            // No request in current direction, reverse direction
            direction = -direction;
            
            // Find nearest request in new direction
            minDistance = 1000000000;
            target = -1;
            
            for (int i = 0; i < requestCount; i++) {
                int floor = requests[i];
                int distance = floor - currentFloor;
                
                if (direction == 1) {
                    // Now going up
                    if (distance >= 0 && distance < minDistance) {
                        minDistance = distance;
                        target = floor;
                    }
                } else {
                    // Now going down
                    if (distance <= 0 && -distance < minDistance) {
                        minDistance = -distance;
                        target = floor;
                    }
                }
            }
            
            if (target != -1) {
                cancelRequest(target);
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