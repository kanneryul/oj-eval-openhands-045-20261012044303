#include <cstdio>
#include <iostream>
using namespace std;

const int MAX_REQUESTS = 500000;

struct ElevatorSystem {
    int currentFloor;
    int direction; // 1 for up, -1 for down
    
    // Pending requests stored in sorted array
    int requests[MAX_REQUESTS];
    int requestCount;
    
    ElevatorSystem() {
        currentFloor = 0;
        direction = 1; // start going up
        requestCount = 0;
    }
    
    // Binary search to find insertion position
    int findInsertPosition(int x) {
        int left = 0, right = requestCount;
        while (left < right) {
            int mid = (left + right) / 2;
            if (requests[mid] < x) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
    
    // Binary search to find element
    int findElement(int x) {
        int left = 0, right = requestCount - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (requests[mid] == x) {
                return mid;
            } else if (requests[mid] < x) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }
    
    void addRequest(int x) {
        int pos = findInsertPosition(x);
        
        // Shift elements to make space
        for (int i = requestCount; i > pos; i--) {
            requests[i] = requests[i - 1];
        }
        
        requests[pos] = x;
        requestCount++;
    }
    
    void cancelRequest(int x) {
        int pos = findElement(x);
        if (pos != -1) {
            // Shift elements to remove
            for (int i = pos; i < requestCount - 1; i++) {
                requests[i] = requests[i + 1];
            }
            requestCount--;
        }
    }
    
    void action() {
        if (requestCount == 0) {
            // No pending requests, stay still
            return;
        }
        
        int target = -1;
        
        if (direction == 1) {
            // Going up - find smallest floor >= currentFloor
            int left = 0, right = requestCount - 1;
            int result = -1;
            
            while (left <= right) {
                int mid = (left + right) / 2;
                if (requests[mid] >= currentFloor) {
                    result = mid;
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            
            if (result != -1) {
                target = requests[result];
            }
        } else {
            // Going down - find largest floor <= currentFloor
            int left = 0, right = requestCount - 1;
            int result = -1;
            
            while (left <= right) {
                int mid = (left + right) / 2;
                if (requests[mid] <= currentFloor) {
                    result = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            
            if (result != -1) {
                target = requests[result];
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
            if (direction == 1) {
                // Now going up
                int left = 0, right = requestCount - 1;
                int result = -1;
                
                while (left <= right) {
                    int mid = (left + right) / 2;
                    if (requests[mid] >= currentFloor) {
                        result = mid;
                        right = mid - 1;
                    } else {
                        left = mid + 1;
                    }
                }
                
                if (result != -1) {
                    target = requests[result];
                }
            } else {
                // Now going down
                int left = 0, right = requestCount - 1;
                int result = -1;
                
                while (left <= right) {
                    int mid = (left + right) / 2;
                    if (requests[mid] <= currentFloor) {
                        result = mid;
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                }
                
                if (result != -1) {
                    target = requests[result];
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