#ifndef VIDEO_PROCESSING_H
#define VIDEO_PROCESSING_H

#include <string>

// Functions declarations 
void resizeVideo(const std::string& inputPath, const std::string& outputPath, int width, int height, int codec);
void addTextOverlay(const std::string &inputPath, const std::string &outputPath, const std::string &text, int x, int y, int codec);
void trimVideo(const std::string& inputPath, const std::string& outputPath, double startTime, double endTime, int codec);
void rotateVideo(const std::string& inputPath, const std::string& outputPath, int angle, int codec);
void applyGrayscale(const std::string& inputPath, const std::string& outputPath, int codec);
void applyBlur(const std::string& inputPath, const std::string& outputPath, int codec);

#endif