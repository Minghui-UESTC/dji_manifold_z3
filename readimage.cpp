#include <iostream>
#include <unistd.h>
#include<opencv2/opencv.hpp>   
 
#define DISPLAY_MODE            (1 << 0)
#define GETBUFFER_MODE          (1 << 1)
#define TRANSFER_MODE           (1 << 2)

#define	imageWidth 1280
#define	imageHeight 720
#define	imageChannels 3

#define MODE GETBUFFER_MODE | TRANSFER_MODE
//  Note: DISPLAY_MODE and GETBUFFER_MODE cannot be set at the same time

#define CAM_BLOCK 1


using namespace cv;

extern "C" {
	int manifold_cam_read(unsigned char *buffer, unsigned int *nframe, unsigned int block);
	int manifold_cam_init(int mode);
	int manifold_cam_exit();
}

bool grabFrame(cv::Mat &frame)
{
	// Check if new frame is available
	unsigned char buffer[imageWidth * imageHeight * imageChannels / 2 + 8];
	unsigned int nFrame = 0;

	int ret = manifold_cam_read(buffer, &nFrame, CAM_BLOCK);
	
	if(ret == -1)
	{
		return false;
	}
	else
	{
		// Create openCV Mat to store the image
		cv::Mat frameYcbCr = cv::Mat(imageHeight * imageChannels / 2, imageWidth, CV_8UC1, buffer);
		cv::cvtColor(frameYcbCr, frame, CV_YUV2BGR_NV12); 
		std::cout << "Frame: " << nFrame << std::endl;

	}
	return true;
}


int main()
{
	int ret = manifold_cam_init(0 | MODE);
 
	if(-1 == ret)
	{
		std::cout << "manifold init error \n";
		return -1;
	}

	cv::Mat frame;
	cvNamedWindow("img", CV_WINDOW_NORMAL); 
	waitKey(300);		
	
	while (1)
	{
		
                   
		if (grabFrame(frame) == false)
		{
			break;
		}	            
		else
		{
			imshow("img", frame); 
		}
		 waitKey(3); //延时3ms 

		if(manifold_cam_exit())
		{ 
			//to check if threads stop working
			destroyAllWindows();
			break;  
		}
	}

	while(!manifold_cam_exit()) //make sure all threads exit ok
	{
		sleep(1);
	}

	

	return 0;
	
}



