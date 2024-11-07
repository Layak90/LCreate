#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <sstream>

class Layak90AppGenerator {
public:
    Layak90AppGenerator(const std::string& sourceFile, const std::string& outputName)
        : sourceFile(sourceFile), outputName(outputName) {}

    void generateExe() {
        if (!fileExists(sourceFile)) {
            std::cerr << "Error: The source file does not exist." << std::endl;
            return;
        }

        compileSource();
        cleanUp();
    }

private:
    std::string sourceFile;
    std::string outputName;

    bool fileExists(const std::string& filename) {
        return std::filesystem::exists(filename);
    }

    void compileSource() {
        std::string command = "g++ " + sourceFile + " -o " + outputName;
        int result = system(command.c_str());

        if (result == 0) {
            std::cout << "Executable file generated successfully: " << outputName << std::endl;
        } else {
            std::cerr << "Error during the generation of the .exe file." << std::endl;
        }
    }

    void cleanUp() {
        std::cout << "Cleaning up temporary files..." << std::endl;
        std::string tempFile = sourceFile.substr(0, sourceFile.find_last_of('.')) + ".o";
        if (std::filesystem::exists(tempFile)) {
            std::filesystem::remove(tempFile);
            std::cout << "Temporary file removed: " << tempFile << std::endl;
        }
    }
};

void layak90Welcome() {
    std::cout << "Welcome to Layak90's Application Generator" << std::endl;
}

std::string layak90GetSourceFile() {
    std::string sourceFile;
    std::cout << "Enter the name of the C++ source file (with .cpp): ";
    std::cin >> sourceFile;
    return sourceFile;
}

std::string layak90GetOutputName() {
    std::string outputName;
    std::cout << "Enter the output name for the .exe file: ";
    std::cin >> outputName;
    return outputName;
}

void layak90ShowGeneratedFiles(const std::string& outputName) {
    std::cout << "Files generated in the current directory:" << std::endl;
    for (const auto& entry : std::filesystem::directory_iterator(".")) {
        std::cout << entry.path().filename().string() << std::endl;
    }
}

void layak90GetCompilationOptions(std::vector<std::string>& options) {
    std::string inputOptions;
    std::cout << "Enter compilation options (separated by spaces, or press Enter to skip): ";
    std::cin.ignore(); // Clear the newline character from the input buffer
    std::getline(std::cin, inputOptions);
    
    std::istringstream iss(inputOptions);
    std::string option;
    while (iss >> option) {
        options.push_back(option);
    }
}

std::string layak90BuildCommand(const std::string& sourceFile, const std::string& outputName, const std::vector<std::string>& options) {
    std::string command = "g++ ";
    for (const auto& option : options) {
        command += option + " ";
    }
    command += sourceFile + " -o " + outputName;
    return command;
}

int main() {
    layak90Welcome();
    
    std::string sourceFile = layak90GetSourceFile();
    std::string outputName = layak90GetOutputName();

    std::vector<std::string> options;
    layak90GetCompilationOptions(options);

    Layak90AppGenerator generator(sourceFile, outputName);
    generator.generateExe();

    layak90ShowGeneratedFiles(outputName);

    return 0;
}