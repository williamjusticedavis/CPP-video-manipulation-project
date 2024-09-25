#include "video_processing.h"
#include <opencv2/opencv.hpp>
#include <iostream>

//Resizing function
void resizeVideo(const std::string& inputPath, const std::string& outputPath, int width, int height, int codec) {
    std::cout << "Preparing to resize video..." << std::endl;

    cv::VideoCapture cap(inputPath);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file for resizing." << std::endl;
        return;
    }

    
    cv::VideoWriter writer(outputPath, codec, cap.get(cv::CAP_PROP_FPS), cv::Size(width, height));

    std::cout << "Resizing video frames..." << std::endl;
    cv::Mat frame;
    int frameCount = 0;
    while (cap.read(frame)) {
        cv::Mat resizedFrame;
        cv::resize(frame, resizedFrame, cv::Size(width, height));
        writer.write(resizedFrame);
        frameCount++;
    }
    std::cout << "Video resized successfully. Output saved to " << outputPath << std::endl;
}

// Adding text function
void addTextOverlay(const std::string &inputPath, const std::string &outputPath, const std::string &text, int x, int y, int codec) {
    std::cout << "Starting text overlay process..." << std::endl;

    cv::VideoCapture cap(inputPath);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open the video file for text overlay." << std::endl;
        return;
    }

    int frameWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int frameHeight = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    int fps = static_cast<int>(cap.get(cv::CAP_PROP_FPS));

    // Use the user-provided codec
    cv::VideoWriter writer(outputPath, codec, fps, cv::Size(frameWidth, frameHeight));
    if (!writer.isOpened()) {
        std::cerr << "Error: Could not open output video file for text overlay." << std::endl;
        return;
    }
    std::cout << "Overlaying text on video frames..." << std::endl;

    cv::Mat frame;
    int frameCount = 0;
    while (cap.read(frame)) {
        cv::putText(frame, text, cv::Point(x, y), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 0, 255), 3);
        writer.write(frame);
        frameCount++;
    }
    std::cout << "Text overlay applied successfully. Output saved to " << outputPath << std::endl;
}

// Trimming function
void trimVideo(const std::string& inputPath, const std::string& outputPath, double startTime, double endTime, int codec) {
    std::cout << "Preparing to trim video..." << std::endl;

    cv::VideoCapture cap(inputPath);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file for trimming." << std::endl;
        return;
    }

    double fps = cap.get(cv::CAP_PROP_FPS);
    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    int totalFrames = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));

    int startFrame = static_cast<int>(startTime * fps);
    int endFrame = static_cast<int>(endTime * fps);

    if (startFrame >= totalFrames || endFrame >= totalFrames || startFrame >= endFrame) {
        std::cerr << "Error: Invalid start or end time for trimming." << std::endl;
        return;
    }

    cv::VideoWriter writer(outputPath, codec, fps, cv::Size(width, height));

    if (!writer.isOpened()) {
        std::cerr << "Error: Could not open output video file for trimming." << std::endl;
        return;
    }

    std::cout << "Trimming video from " << startTime << " to " << endTime << " seconds..." << std::endl;

    cv::Mat frame;
    int frameIndex = 0;
    while (cap.read(frame)) {
        if (frameIndex >= startFrame && frameIndex <= endFrame) {
            writer.write(frame);
        }

        if (frameIndex > endFrame) {
            break;
        }

        frameIndex++;
    }
    std::cout << "Video trimmed successfully. Output saved to " << outputPath << std::endl;
}

// Rotating function
void rotateVideo(const std::string& inputPath, const std::string& outputPath, int angle, int codec) {
    std::cout << "Rotating video by " << angle << " degrees..." << std::endl;  // Ensure the right message

    cv::VideoCapture cap(inputPath);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file for rotating." << std::endl;
        return;
    }

    int fps = static_cast<int>(cap.get(cv::CAP_PROP_FPS));
    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    // Swap width and height for 90 or 270-degree rotations
    if (angle == 90 || angle == 270) {
        std::swap(width, height);
    }

    cv::VideoWriter writer(outputPath, codec, fps, cv::Size(width, height));

    if (!writer.isOpened()) {
        std::cerr << "Error: Could not open output video file for rotating." << std::endl;
        return;
    }

    std::cout << "Applying " << angle << " degree rotation on video frames..." << std::endl;

    cv::Mat frame;
    while (cap.read(frame)) {
        cv::Mat rotatedFrame;
        switch (angle) {
            case 90:
                cv::rotate(frame, rotatedFrame, cv::ROTATE_90_CLOCKWISE);
                break;
            case 180:
                // Rotate twice by 90 degrees to achieve 180 degrees
                cv::rotate(frame, rotatedFrame, cv::ROTATE_90_CLOCKWISE);
                cv::rotate(rotatedFrame, rotatedFrame, cv::ROTATE_90_CLOCKWISE);
                break;
            case 270:
                cv::rotate(frame, rotatedFrame, cv::ROTATE_90_COUNTERCLOCKWISE);
                break;
            default:
                std::cerr << "Error: Invalid rotation angle." << std::endl;
                return;
        }
        writer.write(rotatedFrame);
    }
    std::cout << "Video rotation complete. Output saved to " << outputPath << std::endl;
}

//Applying GrayScale function
void applyGrayscale(const std::string& inputPath, const std::string& outputPath, int codec) {
    std::cout << "Applying grayscale filter..." << std::endl;

    cv::VideoCapture cap(inputPath);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file for grayscale filter." << std::endl;
        return;
    }

    int fps = static_cast<int>(cap.get(cv::CAP_PROP_FPS));
    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    cv::VideoWriter writer(outputPath, codec, fps, cv::Size(width, height));

    if (!writer.isOpened()) {
        std::cerr << "Error: Could not open output video file for grayscale filter." << std::endl;
        return;
    }

    std::cout << "Converting video frames to grayscale..." << std::endl;

    cv::Mat frame;
    int frameCount = 0;
    while (cap.read(frame)) {
        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        cv::cvtColor(grayFrame, grayFrame, cv::COLOR_GRAY2BGR);  // Convert back to BGR for writer
        writer.write(grayFrame);
        frameCount++;
    }
    std::cout << "Grayscale filter applied successfully. Output saved to " << outputPath << std::endl;
}

// Applying blur function
void applyBlur(const std::string& inputPath, const std::string& outputPath, int codec) {
    std::cout << "Applying blur filter..." << std::endl;

    cv::VideoCapture cap(inputPath);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file for blur filter." << std::endl;
        return;
    }

    int fps = static_cast<int>(cap.get(cv::CAP_PROP_FPS));
    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    cv::VideoWriter writer(outputPath, codec, fps, cv::Size(width, height));

    if (!writer.isOpened()) {
        std::cerr << "Error: Could not open output video file for blur filter." << std::endl;
        return;
    }

    std::cout << "Blurring video frames..." << std::endl;

    cv::Mat frame;
    int frameCount = 0;
    while (cap.read(frame)) {
        cv::Mat blurredFrame;
        cv::GaussianBlur(frame, blurredFrame, cv::Size(15, 15), 0);
        writer.write(blurredFrame);
        frameCount++;
    }
    std::cout << "Blur filter applied successfully. Output saved to " << outputPath << std::endl;
}