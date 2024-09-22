#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "video_processing.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <video_path>" << std::endl;
        return 1;
    }

    std::string videoPath = argv[1];
    std::string outputPath = "../output/processed_video.avi";

    std::cout << "Select a processing option:" << std::endl;
    std::cout << "1. Resize video" << std::endl;
    std::cout << "2. Add text overlay" << std::endl;
    std::cout << "3. Trim video" << std::endl;
    std::cout << "4. Rotate video" << std::endl;
    std::cout << "5. Apply filter" << std::endl;  // Added filter option
    std::cout << "Enter your choice: ";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        int width, height;
        std::cout << "Enter width: ";
        std::cin >> width;
        std::cout << "Enter height: ";
        std::cin >> height;
        resizeVideo(videoPath, outputPath, width, height);
    } else if (choice == 2) {
        std::string text;
        std::cout << "Enter text to overlay: ";
        std::cin.ignore();
        std::getline(std::cin, text);
        addTextOverlay(videoPath, outputPath, text);
    } else if (choice == 3) {
        double startTime, endTime;
        std::cout << "Enter start time (in seconds): ";
        std::cin >> startTime;
        std::cout << "Enter end time (in seconds): ";
        std::cin >> endTime;
        trimVideo(videoPath, outputPath, startTime, endTime);
    } else if (choice == 4) {
        int rotationChoice;
        std::cout << "Select rotation angle:" << std::endl;
        std::cout << "1. 90 degrees" << std::endl;
        std::cout << "2. 180 degrees" << std::endl;
        std::cout << "3. 270 degrees" << std::endl;
        std::cout << "4. Go back" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> rotationChoice;

        if (rotationChoice == 1) {
            rotateVideo(videoPath, outputPath, 90);
        } else if (rotationChoice == 2) {
            rotateVideo(videoPath, outputPath, 180);
        } else if (rotationChoice == 3) {
            rotateVideo(videoPath, outputPath, 270);
        } else {
            std::cout << "Going back." << std::endl;
            return 0;
        }
    } else if (choice == 5) {
        int filterChoice;
        std::cout << "Select a filter:" << std::endl;
        std::cout << "1. Grayscale" << std::endl;
        std::cout << "2. Blur" << std::endl;
        std::cout << "3. Go back" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> filterChoice;

        if (filterChoice == 1) {
            applyGrayscale(videoPath, outputPath);
        } else if (filterChoice == 2) {
            applyBlur(videoPath, outputPath);
        } else {
            std::cout << "Going back." << std::endl;
            return 0;
        }
    } else {
        std::cerr << "Invalid choice." << std::endl;
        return 1;
    }

    std::cout << "Video processed and saved to " << outputPath << std::endl;

    return 0;
}