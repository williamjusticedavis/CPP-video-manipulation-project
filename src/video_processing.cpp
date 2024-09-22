#include "video_processing.h"
#include <opencv2/opencv.hpp>
#include <iostream>

void resizeVideo(const std::string& inputPath, const std::string& outputPath, int width, int height) {
    std::cout << "Preparing your video..." << std::endl;

    cv::VideoCapture cap(inputPath);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file." << std::endl;
        return;
    }

    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    cv::VideoWriter writer(outputPath, codec, cap.get(cv::CAP_PROP_FPS), cv::Size(width, height));

    cv::Mat frame;
    while (cap.read(frame)) {
        cv::Mat resizedFrame;
        cv::resize(frame, resizedFrame, cv::Size(width, height));
        writer.write(resizedFrame);
    }
}

void addTextOverlay(const std::string& inputPath, const std::string& outputPath, const std::string& text) {
    std::cout << "Preparing your video..." << std::endl;

    cv::VideoCapture cap(inputPath);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file." << std::endl;
        return;
    }

    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    cv::VideoWriter writer(outputPath, codec, cap.get(cv::CAP_PROP_FPS), 
                           cv::Size(static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)), 
                                    static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT))));

    cv::Mat frame;
    while (cap.read(frame)) {
        cv::putText(frame, text, cv::Point(frame.cols / 4, frame.rows / 2), 
                    cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
        writer.write(frame);
    }
}

void trimVideo(const std::string& inputPath, const std::string& outputPath, double startTime, double endTime) {
    std::cout << "Trimming your video..." << std::endl;

    cv::VideoCapture cap(inputPath);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file." << std::endl;
        return;
    }

    int fps = static_cast<int>(cap.get(cv::CAP_PROP_FPS));
    int startFrame = static_cast<int>(startTime * fps);
    int endFrame = static_cast<int>(endTime * fps);

    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    cv::VideoWriter writer(outputPath, codec, fps, 
                           cv::Size(static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)), 
                                    static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT))));

    cv::Mat frame;
    for (int i = 0; i < endFrame; ++i) {
        if (!cap.read(frame)) {
            break; // End of video
        }
        if (i >= startFrame) {
            writer.write(frame);
        }
    }
}

void rotateVideo(const std::string& inputPath, const std::string& outputPath, int angle) {
    std::cout << "Rotating your video..." << std::endl;

    cv::VideoCapture cap(inputPath);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file." << std::endl;
        return;
    }

    int fps = static_cast<int>(cap.get(cv::CAP_PROP_FPS));
    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    // Adjust width and height based on rotation angle
    if (angle == 90 || angle == 270) {
        std::swap(width, height);
    }

    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    cv::VideoWriter writer(outputPath, codec, fps, cv::Size(width, height));

    cv::Mat frame;
    while (cap.read(frame)) {
        cv::Mat rotatedFrame;
        switch (angle) {
            case 90:
                cv::rotate(frame, rotatedFrame, cv::ROTATE_90_CLOCKWISE);
                break;
            case 180:
                cv::rotate(frame, rotatedFrame, cv::ROTATE_180);
                break;
            case 270:
                cv::rotate(frame, rotatedFrame, cv::ROTATE_90_COUNTERCLOCKWISE);
                break;
            default:
                std::cerr << "Invalid rotation angle." << std::endl;
                return;
        }
        writer.write(rotatedFrame);
    }
}

void applyGrayscale(const std::string& inputPath, const std::string& outputPath) {
    std::cout << "Applying grayscale filter..." << std::endl;

    cv::VideoCapture cap(inputPath);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file." << std::endl;
        return;
    }

    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    cv::VideoWriter writer(outputPath, codec, cap.get(cv::CAP_PROP_FPS), 
                           cv::Size(static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)), 
                                    static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT))));

    cv::Mat frame;
    while (cap.read(frame)) {
        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        cv::cvtColor(grayFrame, grayFrame, cv::COLOR_GRAY2BGR); // Convert back to BGR
        writer.write(grayFrame);
    }
}

void applyBlur(const std::string& inputPath, const std::string& outputPath) {
    std::cout << "Applying blur filter..." << std::endl;

    cv::VideoCapture cap(inputPath);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file." << std::endl;
        return;
    }

    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    cv::VideoWriter writer(outputPath, codec, cap.get(cv::CAP_PROP_FPS), 
                           cv::Size(static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)), 
                                    static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT))));

    cv::Mat frame;
    while (cap.read(frame)) {
        cv::Mat blurredFrame;
        cv::GaussianBlur(frame, blurredFrame, cv::Size(15, 15), 0);
        writer.write(blurredFrame);
    }
}