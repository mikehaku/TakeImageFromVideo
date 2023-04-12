// Take images from video

#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using cv::Mat;
using std::string;

int main()
{
    // read the path of video from a text file
    std::ifstream file;
    file.open("../videoPath.txt");
    string videoPath;
    getline(file, videoPath);
    // close file
    file.close();
    cout << "Video path: " << videoPath << endl;

    // read the name of video from a text file
    file.open("../videoName.txt");
    string videoName;
    getline(file, videoName);
    // close file
    file.close();

    // create a folder with the name of video in the video path if it does not exist
    string folderPath = videoPath + "/" + videoName;
    // check if the folder exists
    std::ifstream folder(folderPath);
    if(folder)
    {
        cout << "Folder exists" << endl;
    }
    else
    {
        cout << "Folder does not exist" << endl;
        cout << "Create folder" << endl;
        // create folder
        string command = "mkdir " + folderPath;
        system(command.c_str());
    }

    cout << "Choose image acquisition mode:" << endl;
    cout << "1 - by pressing keyboard" << endl;
    cout << "2 - by input [interval start end]" << endl;
    int mode;
    cin >> mode;

    if(mode != 1 && mode != 2)
    {
        cout << "Wrong mode!" << endl;
        return 0;
    }
    else
    {
        cout << "Mode " << mode << " chosen" << endl;
        if(mode == 1)
        {
            cout << "Press 't' key to take image" << endl;
            cout << "Press 'q' key to quit" << endl;

            // open video
            cv::VideoCapture cap(videoPath + "/" + videoName + ".avi");
            cout << "Video path: " << videoPath + "/" + videoName + ".avi" << endl;
            if(!cap.isOpened())
            {
                cout << "Cannot open video" << endl;
                return 0;
            }

            // take image from video
            int frameIndex = 0;
            while(1)
            {
                Mat frame;
                cap >> frame;
                if(frame.empty())
                {
                    cout << "Frame is empty" << endl;
                    break;
                }
                frameIndex++;

                cv::imshow("Frame", frame);

                char c = (char)cv::waitKey(25);
                if(c == 't')
                {
                    cout << "Image taken Frame index = " << frameIndex <<   endl;
                    // save image with frame index
                    string imagePath = folderPath + "/" + std::to_string(frameIndex) + ".png";
                    cv::imwrite(imagePath, frame);
                }
                else if(c == 'q')
                {
                    cout << "Quit" << endl;
                    break;
                }
            }
        }
        else
        {
            cout << "Input frame interval" << endl;
            int frameInterval;
            cin >> frameInterval;

            cout << "Input start frame index" << endl;
            int startFrameIndex;
            cin >> startFrameIndex;

            cout << "Input end frame index" << endl;
            int endFrameIndex;
            cin >> endFrameIndex;

            // open video
            cv::VideoCapture cap(videoPath + "/" + videoName + ".avi");
            if(!cap.isOpened())
            {
                cout << "Cannot open video" << endl;
                return 0;
            }

            // take image from video
            int frameIndex = 0;
            while(1)
            {
                Mat frame;
                cap >> frame;
                if(frame.empty())
                {
                    cout << "Frame is empty" << endl;
                    break;
                }

                frameIndex++;

                if(frameIndex % frameInterval == 0 && frameIndex >= startFrameIndex)
                {
                    cout << "Image taken Frame index = " << frameIndex <<   endl;
                    // save image with frame index
                    string imagePath = folderPath + "/" + std::to_string(frameIndex) + ".png";
                    cv::imwrite(imagePath, frame);
                }

                if(frameIndex >= endFrameIndex)
                {
                    cout << "End frame" << endl;
                    break;
                }
            }
        }
    }
    return 0;
}