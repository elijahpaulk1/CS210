#include <iostream>
#include <fstream>
#include <map>
#include <string>

class GroceryTracker {
private:
    std::map<std::string, int> itemFrequency; // Map to store item frequencies
    const std::string dataFilePath; // Path for backup data file

public:
    GroceryTracker() : dataFilePath("frequency.dat") {}

    void loadInputFile(const std::string& filename) {
        // Load item frequencies from input file
        std::ifstream inputFile(filename);
        if (!inputFile) {
            std::cerr << "Error opening input file.\n";
            return;
        }

        std::string itemName;
        int frequency;
        while (inputFile >> itemName >> frequency) {
            itemFrequency[itemName] = frequency;
        }
        inputFile.close();
    }

    int getItemFrequency(const std::string& itemName) const {
        // Lookup and return frequency of a specific item
        std::map<std::string, int>::const_iterator it = itemFrequency.find(itemName);
        if (it != itemFrequency.end()) {
            return it->second;
        }
        return 0;
    }

    void printItemFrequencyList() const {
        // Print list of items along with their frequencies
        std::cout << "Item Frequency List:\n";
        for (const auto& entry : itemFrequency) {
            std::cout << entry.first << " " << entry.second << "\n";
        }
    }

    void printHistogram() const {
        // Print histogram with item names and asterisks representing frequency
        std::cout << "Histogram:\n";
        for (const auto& entry : itemFrequency) {
            std::cout << entry.first << " ";
            for (int i = 0; i < entry.second; ++i) {
                std::cout << "*";
            }
            std::cout << "\n";
        }
    }

    void saveDataToFile() const {
        // Save item frequencies to backup data file
        std::ofstream outFile(dataFilePath);
        if (!outFile) {
            std::cerr << "Error creating output file.\n";
            return;
        }

        for (const auto& entry : itemFrequency) {
            outFile << entry.first << " " << entry.second << "\n";
        }
        outFile.close();
    }
};

int main() {
    GroceryTracker tracker;
    tracker.loadInputFile("CS210_Project_Three_Input_File.txt");

    int choice;
    do {
        // Display menu and handle user input
        std::cout << "Menu:\n";
        std::cout << "1. Lookup item frequency\n";
        std::cout << "2. Print item frequency list\n";
        std::cout << "3. Print histogram\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // Lookup item frequency
                std::string itemToLookup;
                std::cout << "Enter item to lookup: ";
                std::cin >> itemToLookup;
                int frequency = tracker.getItemFrequency(itemToLookup);
                std::cout << "Frequency: " << frequency << "\n";
                break;
            }
            case 2:
                tracker.printItemFrequencyList();
                break;
            case 3:
                tracker.printHistogram();
                break;
            case 4:
                // Save data and exit
                tracker.saveDataToFile();
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
