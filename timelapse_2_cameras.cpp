// Threading currently does not work. They record sequentially. Debugging it

#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread> // For std::thread
#include <chrono> // For std::chrono

using namespace cv;

// Function to capture video from a camera and write to file
void captureVideo(int deviceNumber, const std::string& outputFilename, int captureInterval, int totalDuration) {
    VideoCapture cap(deviceNumber);
    if (!cap.isOpened()) {
        printf("Error: Could not open video capture device %d.\n", deviceNumber);
        return;
    }

    int frameWidth = cap.get(CAP_PROP_FRAME_WIDTH);
    int frameHeight = cap.get(CAP_PROP_FRAME_HEIGHT);
    VideoWriter video(outputFilename, VideoWriter::fourcc('M', 'P', '4', 'V'), 10, Size(frameWidth, frameHeight));
    
    if (!video.isOpened()) {
        printf("Error: Could not open the video file for writing from camera %d.\n", deviceNumber);
        return;
    }

    auto startTime = std::chrono::high_resolution_clock::now();
    int framesToCapture = totalDuration / captureInterval;
    printf("Starting capture from camera %d for %d seconds.\n", deviceNumber, totalDuration);

    for (int i = 0; i < framesToCapture; i++) {
        Mat frame;
        cap >> frame;

        if (frame.empty()) {
            printf("Error: Captured empty frame from camera %d.\n", deviceNumber);
            break;
        }

        video.write(frame);

        std::this_thread::sleep_for(std::chrono::seconds(captureInterval));

        // Check elapsed time
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::high_resolution_clock::now() - startTime
        ).count();

        if (elapsedTime >= totalDuration) {
            printf("Camera %d capture completed.\n", deviceNumber);
            break;
        }
    }

    cap.release();
    video.release();
    printf("Timelapse video from camera %d created successfully.\n", deviceNumber);
}

int main(int argc, char** argv) {
    // Check for the correct number of arguments
    if (argc != 5) {
        printf("Usage: %s <device number 1> <device number 2> <capture interval (seconds)> <total duration (seconds)>\n", argv[0]);
        return -1;
    }

    int deviceNumber1 = atoi(argv[1]);
    int deviceNumber2 = atoi(argv[2]);
    int captureInterval = atoi(argv[3]);
    int totalDuration = atoi(argv[4]);

    // Create threads for each camera
    std::thread t1(captureVideo, deviceNumber1, "timelapse1.mp4", captureInterval, totalDuration);
    std::thread t2(captureVideo, deviceNumber2, "timelapse2.mp4", captureInterval, totalDuration);

    // Wait for both threads to finish
    t1.join();
    t2.join();

    return 0;
}

