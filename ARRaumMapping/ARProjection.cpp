// ARRaumMapping.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>


int main() 
{
    cv::VideoCapture cap(1);  // Open the default camera (change the argument if you have multiple cameras)

    cv::Mat im_src = cv::imread("Mathtree.jpg");

    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open the camera." << std::endl;
        return -1;
    }

    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_1000);

    while (true) 
    {
        cv::Mat frame;
        cap >> frame;
        // Warped image
        cv::Mat warpedImage = frame.clone();
        cv::Mat concatenatedOutput = frame.clone();

        if (frame.empty()) {
            std::cerr << "Error: No frame received from the camera." << std::endl;
            break;
        }

        std::vector<int> markerIds;
        std::vector<std::vector<cv::Point2f>> markerCorners;
        cv::aruco::detectMarkers(frame, dictionary, markerCorners, markerIds);

        if (!markerIds.empty()) {
            cv::aruco::drawDetectedMarkers(frame, markerCorners, markerIds);

            for (int i = 0; i < markerIds.size(); i++) {
                std::cout << "Detected ArUco Marker ID: " << markerIds[i] << std::endl;
            }
        }
        if (!markerIds.empty() && markerIds[0] == 9)
        {
            std::vector<cv::Point> pts_dst;
            for (int i = 0; i < markerCorners[0].size(); i++)
            {
                pts_dst.push_back((cv::Point)(markerCorners[0][i]));
            }


            // Get the corner points of the new scene image.
            std::vector<cv::Point2f> pts_src;
            pts_src.push_back(cv::Point(0, 0));
            pts_src.push_back(cv::Point(im_src.cols, 0));
            pts_src.push_back(cv::Point(im_src.cols, im_src.rows));
            pts_src.push_back(cv::Point(0, im_src.rows));

            // Compute homography from source and destination points
            cv::Mat h = cv::findHomography(pts_src, pts_dst);

            // Warp source image to destination based on homography
            warpPerspective(im_src, warpedImage, h, frame.size(), cv::INTER_CUBIC);

            // Prepare a mask representing region to copy from the warped image into the original frame.
            cv::Mat mask = cv::Mat::zeros(frame.rows, frame.cols, CV_8UC1);
            fillConvexPoly(mask, pts_dst, cv::Scalar(255, 255, 255), cv::LINE_AA);

            // Erode the mask to not copy the boundary effects from the warping
            cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
            // Mat element = getStructuringElement( MORPH_RECT, Size(3,3));
            erode(mask, mask, element);

            // Copy the warped image into the original frame in the mask region.
            cv::Mat imOut = frame.clone();
            warpedImage.copyTo(imOut, mask);

            // Showing the original image and the new output image side by side
            hconcat(frame, imOut, concatenatedOutput);
        }
 

        cv::imshow("Image", concatenatedOutput);

        int key = cv::waitKey(30);

        if (key == 's')
            cv::imwrite("concatenateImage.png", concatenatedOutput);

        if (key == 27)  // Break the loop on Esc key
            break;

    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}






