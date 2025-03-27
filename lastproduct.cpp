#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

#define TOTAL_FRAMES 10  

vector<bool> frames(TOTAL_FRAMES, false); // Track memory allocation

void updateMemoryFile() {
    while (true) {
        ofstream file("memory_data.txt");
        if (!file) {
            cout << "Error opening file!" << endl;
            return;
        }

        file << "ProcessID,MemoryAllocated\n";
        for (int i = 0; i < TOTAL_FRAMES; i++) {
            frames[i] = rand() % 2; // Randomly allocate/free memory
            file << i + 1 << "," << (frames[i] ? 100 : 0) << "\n";
        }

        file.close();
        cout << "Memory data updated!\n";

        this_thread::sleep_for(chrono::seconds(2)); // Update every 2 seconds
    }
}

int main() {
    srand(time(0));
    updateMemoryFile();
    return 0;
}
