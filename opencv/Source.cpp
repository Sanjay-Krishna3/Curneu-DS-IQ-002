# include<opencv2/imgcodecs.hpp>
# include<opencv2/highgui.hpp>
# include<opencv2/imgproc.hpp>
# include<opencv2/objdetect.hpp>
# include<iostream>

using namespace cv;
using namespace std;

void main() {
	string path = "DS-IQ-002-ObjectDetect-Video.mp4";
	VideoCapture cap(path);
	Mat img, gray, blur;
	CascadeClassifier fullBody, lowerBody, car;
	fullBody.load("haarcascade_fullbody.xml");
	lowerBody.load("haarcascade_lowerbody.xml");
	car.load("haarcascade_cars.xml");
	vector<Rect> fullBodies, lowerBodies, cars;

	while (true) {
		cap.read(img);
		cvtColor(img, gray, COLOR_BGR2GRAY);
		GaussianBlur(gray, blur, Size(3, 3), 3);
		fullBody.detectMultiScale(blur, fullBodies);
		lowerBody.detectMultiScale(blur, lowerBodies);
		car.detectMultiScale(blur, cars);

		for (int i = 0; i < fullBodies.size(); i++) {
			rectangle(img, fullBodies[i].tl(), fullBodies[i].br(), Scalar(255, 0, 0), 4);
			putText(img, "Human", fullBodies[i].tl(), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2, false);
		}
		for (int i = 0; i < lowerBodies.size(); i++) {
			rectangle(img, lowerBodies[i].tl(), lowerBodies[i].br(), Scalar(255, 0, 0), 4);
			putText(img, "Human", lowerBodies[i].tl(), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2, false);
		}
		for (int i = 0; i < cars.size(); i++) {
			rectangle(img, cars[i].tl(), cars[i].br(), Scalar(0, 0, 255), 4);
			putText(img, "Car", cars[i].tl(), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2, false);
		}
		imshow("Output", img);
		waitKey(1);
	}
}