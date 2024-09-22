# Video Processing Application

This C++ console application allows users to process videos by resizing them, adding text overlays, trimming, rotating, and applying filters. The application utilizes OpenCV for video processing and CMake as the build system.

## Features

- **Video Conversion**: Converts input videos to `.avi` format.
- **Resize Video**: Allows the user to resize the video to custom dimensions.
- **Add Text Overlay**: Adds a user-defined text overlay to the video.
- **Trim Video**: Trims a specific portion of the video based on user-defined start and end times.
- **Rotate Video**: Rotates the video by 90, 180, or 270 degrees.
- **Filter Application**: Applies filters like grayscale and blur to the video.

## Prerequisites

Before running the project, make sure you have the following installed on your machine:

- **CMake**: Required for building the project.
- **OpenCV**: Used for video processing. Ensure that OpenCV is properly installed and linked.

### Installing Dependencies

#### macOS (with Homebrew)

You can install the necessary dependencies using [Homebrew](https://brew.sh/):

brew install cmake
brew install opencv

#### Ubuntu/Linux

To install dependencies on Ubuntu/Linux, use the following commands:

sudo apt update
sudo apt install cmake
sudo apt install libopencv-dev

#### Windows

On Windows, you can install CMake and OpenCV manually:

1. Download and install [CMake](https://cmake.org/download/).
2. Download and set up [OpenCV](https://opencv.org/releases/) by following the official guide: [OpenCV Installation Guide](https://docs.opencv.org/master/d3/d52/tutorial_windows_install.html).

## Project Structure

CPProject/
├── CMakeLists.txt       # Build configuration file
├── README.md            # Project documentation
├── include/             # Header files
│   └── video_processing.h
├── src/                 # Source code
│   ├── main.cpp
│   └── video_processing.cpp
├── input/               # Input folder (contains the video to be processed)
│   └── myVideo.mp4
└── output/              # Output folder (where processed videos are saved)

## Build and Run the Application

To build and run the application, follow these steps:

1. **Clone the repository**:

   git clone <repository-url>
   cd CPProject

2. **Build the project**:

   mkdir build
   cd build
   cmake ..
   cmake --build .

3. **Run the application**:

   ./VideoProcessingApp ../input/myVideo.mp4 

## How to Use the Application

Once you run the application, you'll be presented with the following options:

1. **Resize the video**: Enter your desired width and height, and the program will resize the video and save it to the output folder.
2. **Add text overlay**: Type the text you want to overlay on the video, and the program will add it and save the new video to the output folder.
3. **Trim the video**: Enter the start and end times in seconds to trim the video.
4. **Rotate the video**: Choose to rotate the video by 90, 180, or 270 degrees.
5. **Apply filter**: Choose to apply a grayscale or blur filter to the video.

After processing, the program will convert the video into `.avi` format.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.