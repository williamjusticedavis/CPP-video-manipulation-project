#ifndef VIDEO_PROCESSING_H
#define VIDEO_PROCESSING_H

#include <string>

void resizeVideo(const std::string& inputPath, const std::string& outputPath, int width, int height);
void addTextOverlay(const std::string& inputPath, const std::string& outputPath, const std::string& text);
void trimVideo(const std::string& inputPath, const std::string& outputPath, double startTime, double endTime);
void rotateVideo(const std::string& inputPath, const std::string& outputPath, int angle);
void applyGrayscale(const std::string& inputPath, const std::string& outputPath); // New function
void applyBlur(const std::string& inputPath, const std::string& outputPath); // New function

#endif // VIDEO_PROCESSING_H