# ARProjection Read Me

## Overview
This is the source code file "ARProjection.cpp" for a program that performs Augmented Reality (AR) marker-based mapping. The code captures video from a camera, detects ArUco markers in the video stream, and then uses a marker to map a different image onto the detected marker. This README file provides an overview of the code and its functionality.

## Dependencies
The code relies on the following libraries:

- OpenCV: Used for camera input, image manipulation, and marker detection.

Make sure you have these dependencies installed on your system to successfully build and run the code.

## How to Build
To build the code, follow these general steps:

1. Set up a C++ development environment.
2. Install the required dependencies (OpenCV).
3. Create a new C++ project and add the source code file "ARRaumMapping.cpp" to your project.
4. Configure your project to include the necessary include paths and libraries for OpenCV.
5. Build and compile the code.

Specific instructions may vary depending on your development environment and operating system.

## How to Run
Once you have built the code, you can run it. The code performs the following actions:

1. Opens a camera stream (default camera).
2. Captures frames from the camera.
3. Detects ArUco markers in the frames.
4. If a specific ArUco marker (ID 9) is detected, it maps a predefined image onto the marker's position.
5. Displays the original frame and the mapped image side by side.
6. You can press the 's' key to save the concatenated image as "concatenateImage.png."
7. Press the 'Esc' key to exit the program.

## Usage
You can modify the code to suit your specific use case by changing the marker ID, source image, or the behavior upon marker detection. You may also adjust the transformation parameters and interpolation methods to refine the image mapping.

## Important Notes
- Ensure that you have the necessary permissions to access the camera on your system.
- Make sure to replace the source image file ("Mathtree.jpg") with your own image if you want to map a different image.

## Troubleshooting
If you encounter any issues while building or running the code, please refer to the documentation of the dependencies (especially OpenCV) and your development environment for troubleshooting guidance.

## License
This code is provided without any specific license. You are free to use, modify, and distribute it as needed. Please respect the licenses of the libraries and dependencies used in this project.

## Author
This code was authored by Ange Nguetsop. If you have any questions or need assistance, you can contact the author at nguetsopange@aol.com.

Enjoy experimenting with AR marker-based mapping with this code!
