#include <iostream>
using namespace std;

#define TOTAL_FRAMES 8  // Total available memory frames
#define PAGE_SIZE 4      // Each page is of size 4KB (example)

// Page Table Structure
struct PageTable {
    int pages[10]; // Max 10 pages
    int frame[10]; // Store which frame is assigned
    int pageCount;
    bool allocated; // To check if memory is allocated
};

// Memory Frames
bool frames[TOTAL_FRAMES] = {false}; // False means frame is free

// Function to check available frames
int availableFrames() {
    int count = 0;
    for (int i = 0; i < TOTAL_FRAMES; i++) {
        if (!frames[i]) count++;
    }
    return count;
}

// Function to allocate pages using First Fit
void allocatePages(PageTable &pt, int numPages) {
    if (numPages > availableFrames()) {
        cout << "Error: Not enough memory available! Allocation failed.\n";
        return;
    }

    pt.pageCount = numPages;
    pt.allocated = true;

    for (int i = 0; i < numPages; i++) {
        for (int j = 0; j < TOTAL_FRAMES; j++) {
            if (!frames[j]) { // If frame is free
                frames[j] = true;
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
        frames[pt.frame[i]] = false; // Free the frame
    }
    pt.allocated = false;
    cout << "Memory freed successfully!\n";
}

// Function to display page table
void displayPageTable(PageTable &pt) {
    if (!pt.allocated) {
        cout << "No memory allocated yet!\n";
        return;
    }

    cout << "Page Table:\n";
    cout << "Page Number -> Frame Number\n";
    for (int i = 0; i < pt.pageCount; i++) {
        cout << "   " << pt.pages[i] << " -> " << pt.frame[i] << "\n";
    }
}

// Function to display available frames
void displayFrames() {
    cout << "Memory Frames Status:\n";
    for (int i = 0; i < TOTAL_FRAMES; i++) {
        cout << "Frame " << i << ": " << (frames[i] ? "Allocated" : "Free") << "\n";
    }
}

// Main function with user interaction
int main() {
    PageTable process;
    int choice, numPages;

    while (true) {
        cout << "\n=== Memory Allocation System ===\n";
        cout << "1. Allocate Pages\n";
        cout << "2. Deallocate Pages\n";
        cout << "3. Display Page Table\n";
        cout << "4. Display Memory Frames\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (process.allocated) {
                    cout << "Error: Memory already allocated! Deallocate first.\n";
                } else {
                    cout << "Enter number of pages to allocate: ";
                    cin >> numPages;
                    allocatePages(process, numPages);
                }
                break;

            case 2:
                deallocatePages(process);
                break;

            case 3:
                displayPageTable(process);
                break;

            case 4:
                displayFrames();
                break;

            case 5:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}
