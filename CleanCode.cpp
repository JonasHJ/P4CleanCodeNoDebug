﻿#include "ExtractFeat.h"

using namespace cv;
using namespace std;

void undistortImg(Mat &img)
{
	Mat undistorted;

	double camMatrixData[] = {2898.4947, 0,		  1006.1504,
							0,		   2898.7942, 621.3726,
							0,		   0,		  1};
	double distCoeffsData[] = { -0.2296, -0.5837, 0, 0 };

	Mat camMatrix = Mat(3, 3, CV_64F, camMatrixData); //Float matrix with principal points and focal lengths
	Mat distCoeffs = Mat(1, 4, CV_64F, distCoeffsData); //4 element vector containing distortion coefficients

	undistort(img, undistorted, camMatrix, distCoeffs);
	img = undistorted;
}

void loadImages(const String &path, vector<Mat> &images)
{
	vector<String> fn;
	glob(path, fn, true); // recurse
	for (const auto &k : fn) {
		Mat im = imread(k);
		if (im.empty()) continue; //only proceed if successful

		undistortImg(im);

		im = im(Rect(0, 330, 1936, 722)); // This Rect is approx only the conveyor for test data billeder

		images.push_back(im);
	}
}

int main()
{
	// Vector for all images to be proccesed
	vector<Mat> images;
	loadImages(R"(C:\Users\Axel\Desktop\herring_pics_24_04\ArtistBehindSoulSister\*.tif)", images);

	ExtractFeat classifier;
	classifier.run(images);

	return 0;
}
