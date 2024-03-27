#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::VideoCapture cap("/mnt/c/Users/bruno.carvalho/Downloads/COQUINHADEEEEV.mp4");
    if (!cap.isOpened()) {
        std::cerr << "Failed to open video device\n";
        return EXIT_FAILURE;
    }

    std::string ffmpegCmd = "ffmpeg -y -f rawvideo -vcodec rawvideo -s 640x480 -pix_fmt bgr24 -i - -c:v libx264 -preset ultrafast -tune zerolatency -f flv rtmp://167.71.20.221/live/livestream";

    FILE *ffmpeg = popen(ffmpegCmd.c_str(), "w");
    if (!ffmpeg) {
        std::cerr << "Failed to open pipe to ffmpeg\n";
        return EXIT_FAILURE;
    }

    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "frame not grabbed\n";
            break;
        }

        // Resize frame if needed
        cv::resize(frame, frame, cv::Size(640, 480));

        // Write frame to ffmpeg pipe
        fwrite(frame.data, 1, frame.total() * frame.elemSize(), ffmpeg);
    }

    pclose(ffmpeg);
    return EXIT_SUCCESS;
}
