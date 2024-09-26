#include <iostream>  // Needed for std::cin, std::cout
#include <string>    // Needed for std::string
#include <sys/stat.h> // For mkdir
#include <unistd.h>   // For access
#include <cstdio>     // For std::remove (to delete files)
#include "video_processing.h"  // Your project-specific header file
#include <opencv2/opencv.hpp>  // Include OpenCV header

// Helper function to check if a directory exists
bool directoryExists(const std::string& path) {
    return access(path.c_str(), F_OK) != -1;
}

// Helper function to create a directory
void createDirectory(const std::string& path) {
    mkdir(path.c_str(), 0777);  // Permissions: rwxrwxrwx
}

int main(int argc, char* argv[]) {
    // Check if the file path is provided as a command-line argument
    if (argc < 2) {
        std::cerr << "Error: No video file path provided. Usage: ./VideoProcessingApp <video file path>" << std::endl;
        return 1;  // Exit with error code
    }

    std::string videoPath = argv[1];  // Get the file path from the command-line argument

    // Prompt the user for output format
    std::string formatChoice;
    std::cout << "Select output video format (avi, mp4, mov): ";
    std::cin >> formatChoice;

    // Choose the appropriate codec and file extension
    int codec;
    std::string outputExtension;
    if (formatChoice == "avi") {
        codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');  // MJPEG for AVI
        outputExtension = ".avi";
    } else if (formatChoice == "mp4") {
        codec = cv::VideoWriter::fourcc('H', '2', '6', '4');  // H.264 for MP4
        outputExtension = ".mp4";
    } else if (formatChoice == "mov") {
        codec = cv::VideoWriter::fourcc('H', '2', '6', '4');  // H.264 for MOV
        outputExtension = ".mov";
    } else {
        std::cerr << "Error: Unsupported format. Defaulting to .avi format." << std::endl;
        codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
        outputExtension = ".avi";
    }

    std::string outputPathStep1 = "../output/processed_step1" + outputExtension;  // Intermediate output paths
    std::string outputPathStep2 = "../output/processed_step2" + outputExtension;
    std::string outputPathStep3 = "../output/processed_step3" + outputExtension;
    std::string outputPathStep4 = "../output/processed_step4" + outputExtension;
    std::string finalOutputPath = "../output/processedVideo_final" + outputExtension;  // Final output video path

    // Check if the output folder exists, if not create it
    if (!directoryExists("../output")) {
        createDirectory("../output");
        std::cout << "Created output folder: ../output" << std::endl;
    }

    int mainChoice;
    std::cout << "Select an option:" << std::endl;
    std::cout << "1. Apply all changes (text overlay, resize, trim, rotate, filter)" << std::endl;
    std::cout << "2. Proceed with individual modifications" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> mainChoice;

    // Clear the input buffer after `std::cin` to prevent issues with `std::getline`
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (mainChoice == 1) {
        // Option 1: Apply all changes sequentially
        std::string text;
        int width, height;
        double startTime, endTime;
        int filterChoice, angle;
        int x, y;  

        // Step 1: Collect Resize Video input
        std::cout << "Enter new width: ";
        std::cin >> width;
        std::cout << "Enter new height: ";
        std::cin >> height;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        // Step 2: Collect Trim Video input
        std::cout << "Enter start time (in seconds): ";
        std::cin >> startTime;
        std::cout << "Enter end time (in seconds): ";
        std::cin >> endTime;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        
        // Step 3: Collect Rotate Video input
        std::cout << "Select rotation angle (0, 1, 2 or 3):" << std::endl;
        std::cout << "0. No rotation" << std::endl;  // Added option for no rotation
        std::cout << "1. 90 degrees" << std::endl;
        std::cout << "2. 180 degrees" << std::endl;
        std::cout << "3. 270 degrees" << std::endl;
        std::cin >> angle;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Map user input to the correct angle
        if (angle != 0 && angle != 90 && angle != 180 && angle != 270) {
            std::cerr << "Invalid rotation choice. Exiting..." << std::endl;
            return 1;  // Exit with error code
        }

        // Step 4: Collect Text Overlay input
        std::cout << "Enter the text to overlay: ";
        std::getline(std::cin, text);  // Use getline to get the entire text, even if it contains spaces

        // Ask the user for the X and Y coordinates
        std::cout << "Enter the X position for the text: ";
        std::cin >> x;
        std::cout << "Enter the Y position for the text: ";
        std::cin >> y;

        // Step 5: Collect Filter input
        std::cout << "Select a filter:" << std::endl;
        std::cout << "1. Grayscale" << std::endl;
        std::cout << "2. Blur" << std::endl;
        std::cin >> filterChoice;

        // Apply all changes sequentially
        std::cout << "Applying text overlay..." << std::endl;
        addTextOverlay(videoPath, outputPathStep1, text, x, y, codec);  
        std::cout << "Text overlay applied to: " << outputPathStep1 << std::endl;

        std::cout << "Resizing video..." << std::endl;
        resizeVideo(outputPathStep1, outputPathStep2, width, height, codec); 
        std::cout << "Video resized and saved to: " << outputPathStep2 << std::endl;

        std::cout << "Trimming video..." << std::endl;
        trimVideo(outputPathStep2, outputPathStep3, startTime, endTime, codec);
        std::cout << "Video trimmed and saved to: " << outputPathStep3 << std::endl;

        std::cout << "Rotating video..." << std::endl;
        rotateVideo(outputPathStep3, outputPathStep4, angle, codec);
        std::cout << "Video rotated and saved to: " << outputPathStep4 << std::endl;

        if (filterChoice == 1) {
            std::cout << "Applying grayscale filter..." << std::endl;
            applyGrayscale(outputPathStep4, finalOutputPath, codec);
            std::cout << "Grayscale filter applied and final video saved to: " << finalOutputPath << std::endl;
        } else if (filterChoice == 2) {
            std::cout << "Applying blur filter..." << std::endl;
            applyBlur(outputPathStep4, finalOutputPath, codec);
            std::cout << "Blur filter applied and final video saved to: " << finalOutputPath << std::endl;
        }

        std::cout << "All changes applied. Final video saved to " << finalOutputPath << std::endl;

        // Delete intermediate files after the final video is created
        std::remove(outputPathStep1.c_str());
        std::remove(outputPathStep2.c_str());
        std::remove(outputPathStep3.c_str());
        std::remove(outputPathStep4.c_str());

        std::cout << "Intermediate files deleted." << std::endl;

    } else if (mainChoice == 2) {
        // Option 2: Apply individual modifications
        int choice;
        std::cout << "Select an operation:" << std::endl;
        std::cout << "1. Resize video" << std::endl;
        std::cout << "2. Add text overlay" << std::endl;
        std::cout << "3. Trim video" << std::endl;
        std::cout << "4. Rotate video" << std::endl;
        std::cout << "5. Apply filter" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            // Resize video
            int width, height;
            std::cout << "Enter new width: ";
            std::cin >> width;
            std::cout << "Enter new height: ";
            std::cin >> height;
            resizeVideo(videoPath, finalOutputPath, width, height, codec);
            std::cout << "Video resized and saved to " << finalOutputPath << std::endl;
        } else if (choice == 2) {
            // Add text overlay
            std::string text;
            int x, y;
            std::cout << "Enter the text to overlay: ";
            std::getline(std::cin, text);

            std::cout << "Enter the X position for the text: ";
            std::cin >> x;
            std::cout << "Enter the Y position for the text: ";
            std::cin >> y;

            addTextOverlay(videoPath, finalOutputPath, text, x, y, codec);
            std::cout << "Text overlay applied and saved to " << finalOutputPath << std::endl;
        } else if (choice == 3) {
            // Trim video
            double startTime, endTime;
            std::cout << "Enter start time (in seconds): ";
            std::cin >> startTime;
            std::cout << "Enter end time (in seconds): ";
            std::cin >> endTime;
            trimVideo(videoPath, finalOutputPath, startTime, endTime, codec);
            std::cout << "Video trimmed and saved to " << finalOutputPath << std::endl;
        } else if (choice == 4) {
            // Rotate video
            int angle;
            std::cout << "Select a rotation angle by entering the corresponding number:" << std::endl;
            std::cout << "0. No rotation" << std::endl;
            std::cout << "1. 90 degrees" << std::endl;
            std::cout << "2. 180 degrees" << std::endl;
            std::cout << "3. 270 degrees" << std::endl;
            std::cin >> angle;

            // Map user input to the correct angle
            if (angle != 0 && angle != 90 && angle != 180 && angle != 270) {
                std::cerr << "Invalid rotation choice. Exiting..." << std::endl;
                return 1;  // Exit with error code
            }

            rotateVideo(videoPath, finalOutputPath, angle, codec);
            std::cout << "Video rotated and saved to " << finalOutputPath << std::endl;

        } else if (choice == 5) {
            // Apply filter
            int filterChoice;
            std::cout << "Select a filter:" << std::endl;
            std::cout << "1. Grayscale" << std::endl;
            std::cout << "2. Blur" << std::endl;
            std::cin >> filterChoice;

            if (filterChoice == 1) {
                applyGrayscale(videoPath, finalOutputPath, codec);
                std::cout << "Grayscale filter applied and saved to " << finalOutputPath << std::endl;
            } else if (filterChoice == 2) {
                applyBlur(videoPath, finalOutputPath, codec);
                std::cout << "Blur filter applied and saved to " << finalOutputPath << std::endl;
            }
        } else {
            std::cerr << "Invalid choice. Exiting..." << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Invalid choice. Exiting..." << std::endl;
        return 1;
    }

    return 0;
}