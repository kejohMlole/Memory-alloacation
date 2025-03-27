#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace std;

#define TOTAL_FRAMES 8   // Total available memory frames
#define PAGE_SIZE 4      // Each page is of size 4KB (example)

// Memory Representation
vector<bool> memory(TOTAL_FRAMES, false); // False = free, True = allocated

// Page Table Structure
struct PageTable {
    int pages[10];  // Max 10 pages
    int frame[10];  // Store which frame is assigned
    int pageCount;
    bool allocated; // To check if memory is allocated
};

// Function to check available frames
int availableFrames() {
    int count = 0;
    for (int i = 0; i < TOTAL_FRAMES; i++) {
        if (!memory[i]) count++;
    }
    return count;
}

// Function to allocate pages
void allocatePages(PageTable &pt, int numPages) {
    if (numPages > availableFrames()) {
        cout << "Error: Not enough memory available! Allocation failed.\n";
        return;
    }

    pt.pageCount = numPages;
    pt.allocated = true;

    for (int i = 0; i < numPages; i++) {
        for (int j = 0; j < TOTAL_FRAMES; j++) {
            if (!memory[j]) { // If frame is free
                memory[j] = true;
                pt.pages[i] = i;  // Page number
                pt.frame[i] = j;  // Assigned frame
                break;
            }
        }
    }
    cout << "Pages allocated successfully.\n";
}

// Function to deallocate pages
void deallocatePages(PageTable &pt) {
    if (!pt.allocated) {
        cout << "Error: No memory allocated to free!\n";
        return;
    }

    for (int i = 0; i < pt.pageCount; i++) {
        memory[pt.frame[i]] = false; // Free the frame
    }
    pt.allocated = false;
    cout << "Memory freed successfully!\n";
}

// Function to display memory visualization
void displayMemory() {
    system("cls");  // Clear screen (for Windows)

    cout << "Real-Time Memory Visualization\n\n";
    cout << "Legend: # Allocated, . Free\n\n";

    for (int i = 0; i < TOTAL_FRAMES; i++) {
        cout << (memory[i] ? '#' : '.') << " ";  // Show # for allocated, . for free
        if ((i + 1) % 10 == 0) cout << endl;  // New line every 10 blocks
    }
    cout << endl;
}

int main() {
    PageTable process1;

    cout << "\n=== Allocating Pages ===\n";
    allocatePages(process1, 4); // Allocate 4 pages
    displayMemory(); // Display memory after allocation
    this_thread::sleep_for(chrono::seconds(2)); // Wait for 2 seconds

    cout << "\n=== Deallocating Pages ===\n";
    deallocatePages(process1); // Deallocate pages
    displayMemory(); // Display memory after deallocation
    this_thread::sleep_for(chrono::seconds(2)); // Wait for 2 seconds

    return 0;
}
