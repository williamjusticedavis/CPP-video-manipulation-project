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
    } else {
        std::cerr << "Invalid choice." << std::endl;
        return 1;
    }

    std::cout << "Video processed and saved to " << outputPath << std::endl;

    return 0;
}