#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <unistd.h>

using namespace cv;

int main(int argc, char** argv) {
    // Check for the correct number of arguments
    if (argc != 5) {
        printf("Usage: %s <device number> <capture interval (seconds)> <total duration (seconds)> <filename>\n", argv[0]);
        return -1;
    }

    // Parse command line arguments
    int deviceNumber = atoi(argv[1]);
    int captureInterval = atoi(argv[2]);
    int totalDuration = atoi(argv[3]);
    char* fileName = argv[4];
    
    // Open the video capture device
    VideoCapture cap(deviceNumber);
    if (!cap.isOpened()) {
        printf("Error: Could not open video capture device.\n");
        return -1;
    }

    // Define the codec and create a VideoWriter object
    int frameWidth = cap.get(CAP_PROP_FRAME_WIDTH);
    int frameHeight = cap.get(CAP_PROP_FRAME_HEIGHT);
    VideoWriter video(fileName, VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(frameWidth, frameHeight));
    
    if (!video.isOpened()) {
        printf("Error: Could not open the video file for writing.\n");
        return -1;
    }

    // Calculate the number of frames to capture
    int framesToCapture = totalDuration / captureInterval;

    for (int i = 0; i < framesToCapture; i++) {
        Mat frame;
        cap >> frame; // Capture a frame

        if (frame.empty()) {
            printf("Error: Captured empty frame.\n");
            break;
        }

        video.write(frame); // Write the frame to the video file

        sleep(captureInterval); // Wait for the specified interval
    }

    // Release the video capture and writer objects
    cap.release();
    video.release();

    printf("Timelapse video created successfully.\n");

    return 0;
}

