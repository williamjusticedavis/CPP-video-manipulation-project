#ifndef VIDEO_PROCESSING_H
#define VIDEO_PROCESSING_H

#include <string>

void resizeVideo(const std::string& inputPath, const std::string& outputPath, int width, int height);
void addTextOverlay(const std::string& inputPath, const std::string& outputPath, const std::string& text);

#endif // VIDEO_PROCESSING_H