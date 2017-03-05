#include <jni.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <vector>

using namespace std;
using namespace cv;

// generic version
#define GENERIC_ELEM(type,start,step,size,xpos,ypos) *((type*)(start+step*(ypos)+(xpos)*size))

// specific version
#define ELEM(mat,xpos,ypos) *((unsigned char*)(mat.data+mat.step*(ypos)+(xpos)))

extern "C" {

    const double EPSILON = 0.00001;
    
JNIEXPORT jobject JNICALL Java_edu_washington_cs_touchfreelibrary_sensors_CameraGestureSensor_DetectMovementPosition(JNIEnv* env, jobject,
                                                                                                                     jlong currentFrameAddr,
                                                                                                                     jlong previousFrameAddr/*,
                                                                                                                     jlong outputFrameAddr*/);

JNIEXPORT jobject JNICALL Java_edu_washington_cs_touchfreelibrary_sensors_CameraGestureSensor_DetectMovementPosition(JNIEnv* env, jobject,
                                                                                                                     jlong currentFrameAddr,
                                                                                                                     jlong previousFrameAddr/*,
                                                                                                                     jlong outputFrameAddr*/)
{
    Mat& currentFrame  = *(Mat*)currentFrameAddr;
    Mat& previousFrame  = *(Mat*)previousFrameAddr;
    //Mat& outputFrame  = *(Mat*)outputFrameAddr;
    
    //absdiff(currentFrame, previousFrame, outputFrame);
    
    //blur(outputFrame, outputFrame, Point(5, 5));
    
    Point2d avg(-1.0, -1.0);
    double pointsCounted = 0.0;
    double bottomLeft = 0.0;
    double bottomRight = 0.0;
    double topLeft = 0.0;
    double topRight = 0.0;

    for(int y = 2; y < currentFrame.rows - 2; y++)
    {
        for(int x = 2; x < currentFrame.cols - 2; x++) {
            int currPixel = abs(ELEM(currentFrame, x, y) - ELEM(previousFrame, x, y));
            if(currPixel > 20) {
                avg.x = (avg.x * pointsCounted + (double)x) / (pointsCounted + 1.0);
                avg.y = (avg.y * pointsCounted + (double)y) / (pointsCounted + 1.0);
                
                pointsCounted++;

                if (y > currentFrame.rows/2)
                {
                	if (x > currentFrame.cols/2)
                	{
                		bottomRight++;
                	}
                	else
                	{
                		bottomLeft++;
                	}
                }
                else
                {
                	if (x > currentFrame.cols/2)
                	{
                		topRight++;
                	}
                	else
                	{
                		topLeft++;
                	}
                }
                //ELEM(outputFrame, x, y) = 255;
            } //else ELEM(outputFrame, x, y) = 0;
        }
    }
    
    double area = (double)(currentFrame.rows/2 * currentFrame.cols/2);

    double totalFraction = pointsCounted / (double)(currentFrame.rows * currentFrame.cols);
    double bottomRightFraction = bottomRight / area;
    double bottomLeftFraction = bottomLeft / area;
    double topRightFraction = topRight / area;
    double topLeftFraction = topLeft / area;

    // create the point object to be returned
    jobject object;
    jmethodID constructor;
    jclass cls;
    
    cls = env->FindClass("Java/edu/washington/cs/touchfreelibrary/sensors/MotionDetectionReturnValue");
    constructor = env->GetMethodID(cls, "<init>", "(DDDDDDD)V");
    object = env->NewObject(cls, constructor, avg.x, avg.y, totalFraction, bottomRightFraction, bottomLeftFraction, topRightFraction, topLeftFraction);

    return object;
}

}
