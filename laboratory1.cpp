#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;


void listFiles() {
    int choice;
    std::cout << "\n[1] List All Files\n";
    std::cout << "[2] List by Extension\n";
    std::cout << "[3] List by Pattern\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;

    std::string filter;
    switch (choice) {
        case 1:
            std::cout << "\n--- All Files ---\n";
            break;
        case 2:
            std::cout << "Enter extension (e.g., .txt): ";
            std::cin >> filter;
            std::cout << "\n--- Files with extension " << filter << " ---\n";
            break;
        case 3:
            std::cout << "Enter pattern (e.g., test): ";
            std::cin >> filter;
            std::cout << "\n--- Files matching pattern '" << filter << "' ---\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
            return;
    }

    for (auto &entry : fs::directory_iterator(fs::current_path())) {
        std::string filename = entry.path().filename().string();
        if (choice == 2 && entry.path().extension() != filter) continue;
        if (choice == 3 && filename.find(filter) == std::string::npos) continue;
        std::cout << filename << std::endl;
    }
}

void createDirectory() {
    std::string dirname;
    std::cout << "Enter directory name: ";
    std::cin >> dirname;

    if (fs::exists(dirname))
        std::cout << "Error: Directory already exists!\n";
    else if (fs::create_directory(dirname))
        std::cout << "Directory created successfully.\n";
    else
        std::cout << "Error creating directory.\n";
}

void changeDirectory() {
    std::string dirname;
    std::cout << "Enter directory path: ";
    std::cin >> dirname;

    try {
        fs::current_path(dirname);
        std::cout << "Changed to: " << fs::current_path() << std::endl;
    } catch (...) {
        std::cout << "Error: Directory does not exist.\n";
    }
}

void mainMenu() {
    int choice;
    do {
        std::cout << "\n=== DIRECTORY MANAGEMENT ===\n"
                  << "[1] List Files\n"
                  << "[2] Create Directory\n"
                  << "[3] Change Directory\n"
                  << "[4] Exit\n"
                  << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: listFiles(); break;
            case 2: createDirectory(); break;
            case 3: changeDirectory(); break;
            case 4: std::cout << "Exiting...\n"; break;
            default: std::cout << "Invalid choice.\n";
        }
    } while (choice != 4);
}

int main() {
    mainMenu();
    return 0;
}

