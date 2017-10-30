#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv) {
	if ( argc != 2 )
	{
		printf("usage: DisplayImage.out <Image_Path>\n");
		return -1;
	}

	Mat image;
	image = imread( argv[1], 1 );

	Mat grayScale;

	cvtColor(image, grayScale, CV_RGB2GRAY);

	Mat equalized;

	equalizeHist(grayScale, equalized); //see: https://docs.opencv.org/2.4/modules/imgproc/doc/histograms.html?highlight=equalizehist

	Mat inverted;

	bitwise_not(equalized, inverted); //see: http://answers.opencv.org/question/3639/subtract-from-white-invert/

	Rect myROI(10,10,100,100); //crop: (x,y,width,height).  NOTE; program will crash if you provide width/height larger than the image

	Mat croppedImage = inverted(myROI); //see: https://stackoverflow.com/questions/8267191/how-to-crop-a-cvmat-in-opencv



	if ( !image.data )
	{
		printf("No image data \n");
		return -1;
	}
//	namedWindow("Before", WINDOW_AUTOSIZE );
	imshow("Original", image);
	imshow("Grayscaled", grayScale);
	imshow("Equalized", equalized);
	imshow("Inverted", inverted);
	imshow("Cropped", croppedImage);

	waitKey(0);

	return 0;
}