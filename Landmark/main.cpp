#include <opencv2\opencv.hpp>
#include <opencv2\face.hpp>
#include <ctime>
#include <iostream>

using namespace std;
using namespace cv;
using namespace cv::face;

void detectAndDisplay(Mat& frame, CascadeClassifier& faceCascade, Ptr<Facemark>& facemark, double scale, bool& startTime, clock_t time, clock_t endtime);
void drawLandmarks(Mat& img, vector<Point2f> &landmarks);
//string cascadeName, nestedCascadeName;

int main(int argc, const char** argv) {
	clock_t time, endtime;
	bool startTime = false;
	VideoCapture capture; //initialize video capture
	Mat frame; //initialize frame and image matrices

	Ptr<Facemark> facemark = FacemarkLBF::create();

	CascadeClassifier faceCascade; //predefined trained XML classifiers of face and facial features
	double scale = 1.0;
	time = clock();
	endtime = clock();
	facemark->loadModel("lbfmodel.yaml"); //load trained model

	faceCascade.load("C:/opencv/etc/haarcascades/haarcascade_frontalface_default.xml"); // load face detection xml file

	capture.open(0); // open first video camera

	if (capture.isOpened()) {
		cout << "Face Detection Started...." << endl;
		while (1) {

			capture >> frame; //capture video onto frame

			if (frame.empty()) //error prevention
				break;

			Mat frame1 = frame.clone(); //clone frame onto new matrix
			detectAndDisplay(frame1, faceCascade, facemark, scale, startTime, time, endtime); //perform detection on cloned frame

			char x = (char)waitKey(10); //Press q to exit window

			if (x == 27 || x == 'q' || x == 'Q')
				break;
		}
	}
	else
		cout << "Could not open camera";

	return 0;
}

void detectAndDisplay(Mat& frame, CascadeClassifier& faceCascade, Ptr<Facemark>& facemark, double scale, bool& startTime, clock_t time, clock_t endtime) {
	float left_eye_height1, left_eye_height2, left_eye_height, left_eye_length, left_EAR;;
	float right_eye_height1, right_eye_height2, right_eye_height, right_eye_length, right_EAR;
	bool warning = false;
	vector <Rect> faces;
	Mat gray;
	float seconds;

	cvtColor(frame, gray, COLOR_BGR2GRAY); //convert to gray scale
	double fx = 1 / scale;

	faceCascade.detectMultiScale(gray, faces); //detect faces and store in vector faces

	vector< vector<Point2f> > landmarks; //vector of vector to store landmarks of each face

	bool success = facemark->fit(frame, faces, landmarks); //check if landmark detector ran

	if (success) {
		for (int i = 0; i < landmarks.size(); i++) {
			//draw dots
			drawLandmarks(frame, landmarks[i]);

			//left eye EAR calculation
			left_eye_height1 = landmarks[i][41].y - landmarks[i][37].y;
			left_eye_height2 = landmarks[i][40].y - landmarks[i][38].y;
			left_eye_height = (left_eye_height1 + left_eye_height2) / 2;
			left_eye_length = landmarks[i][39].x - landmarks[i][36].x;
			if (left_eye_length == 0)
				left_eye_length = 1.0;
			left_EAR = left_eye_height / left_eye_length;

			//right eye EAR calculation
			right_eye_height1 = landmarks[i][47].y - landmarks[i][43].y;
			right_eye_height2 = landmarks[i][46].y - landmarks[i][44].y;
			right_eye_height = (right_eye_height1 + right_eye_height2) / 2;
			right_eye_length = landmarks[i][45].x - landmarks[i][42].x;
			if (right_eye_length == 0)
				right_eye_length = 1.0;
			right_EAR = right_eye_height / right_eye_length;


			//cout << left_EAR << "\n" << right_EAR << endl << endl;

			if (right_EAR <= 0.2 && left_EAR <= 0.2 && startTime == false) {
				time = clock();
				startTime = true;
				cout << "start timer" << endl;
			}
			else if (right_EAR <= 0.2 && left_EAR <= 0.2 && startTime == true) {
				cout << "continue timer" << endl;
			}
			else if (right_EAR > 0.2 && left_EAR > 0.2 && startTime == true) {
				time = clock();
				startTime = false;
				cout << "end timer" << endl;
			}
			else if (right_EAR > 0.2 && left_EAR > 0.2 && startTime == false) {
				time = clock();
				cout << "normal" << endl;
			}
			else {
				time = clock();
				cout << "other" << endl;
			}

			endtime = clock() - time;
			seconds = (float)endtime / CLOCKS_PER_SEC;
			cout << seconds << endl;

			if (seconds > 0.4)
				warning = true;
		}
	}

	if (warning) {
		putText(frame, "Warning!", Point(10, 100), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 3, 8, false);
	}

	imshow("face Detection", frame); //show processed image with detected face

}

void drawLandmarks(Mat& img, vector<Point2f>& landmarks) {
	for (int i = 0; i < landmarks.size(); i++) {
		circle(img, Point(landmarks[i].x, landmarks[i].y), 1, Scalar(0, 0, 255), 1, 8, 0);
		
	}
}

