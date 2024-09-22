#include "video_processing.h"
#include <opencv2/opencv.hpp>
#include <iostream>

void resizeVideo(const std::string& inputPath, const std::string& outputPath, int width, int height) {
    std::cout << "Preparing your video..." << std::endl; // New message

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
    std::cout << "Preparing your video..." << std::endl; // New message

    cv::VideoCapture cap(inputPath);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file." << std::endl;
        return;
    }

    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    cv::VideoWriter writer(outputPath, codec, cap.get(cv::CAP_PROP_FPS), cv::Size(static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)), static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT))));

    cv::Mat frame;
    while (cap.read(frame)) {
        cv::putText(frame, text, cv::Point(frame.cols / 4, frame.rows / 2), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
        writer.write(frame);
    }
}