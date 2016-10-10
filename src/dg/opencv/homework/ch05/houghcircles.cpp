#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

/*
检测作业素材中“algori_hw.jpg”中的三个圆，
把圆的部分用红色标出来，上传效果图。
*/

static void help()
{
    cout << "\nThis program demonstrates circle finding with the Hough transform.\n"
            "Usage:\n"
            "./houghcircles <image_name>, Default is ./algori_hw.jpg\n" << endl;
}

int main(int argc, char** argv)
{
    cv::CommandLineParser parser(argc, argv,
        "{help h ||}{@image|./algori_hw.jpg|}"
    );
    if (parser.has("help"))
    {
        help();
        return 0;
    }
    string filename = parser.get<string>("@image");
    if (filename.empty())
    {
        help();
        cout << "no image_name provided" << endl;
        return -1;
    }
    Mat img = imread(filename, 0);
    if(img.empty())
    {
        help();
        cout << "can not open " << filename << endl;
        return -1;
    }

    Mat cimg;
    medianBlur(img, img, 5);
    cvtColor(img, cimg, COLOR_GRAY2BGR);

    vector<Vec3f> circles;
    // HoughCircles(img, circles, HOUGH_GRADIENT, 1, 10,
    //              100, 30, 1, 30 // change the last two parameters
    //                             // (min_radius & max_radius) to detect larger circles
    //              );
    HoughCircles(img, circles, HOUGH_GRADIENT, 1, 210,
                 100, 30,
                 40, 120 // change the last two parameters
                         // (min_radius & max_radius) to detect larger circles
                 );
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        circle( cimg, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, LINE_AA);
        circle( cimg, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, LINE_AA);
    }

    imwrite("detected circles.jpg", cimg);
    imshow("detected circles", cimg);
    waitKey();

    return 0;
}
