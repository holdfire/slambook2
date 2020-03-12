#include<iostream>
#include<chrono>

using namespace std;
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

int main(int argc, char **argv){
    // 读取argv[1] 指定的图像
    cv::Mat image;
    image = cv::imread(argv[1]);       

    // 判断图像文件是否读取正确
    if (image.data == nullptr){
        cerr<<"文件"<<argv[1]<<"不存在"<<endl;
        return 0;
    }

    // 文件顺利读取，首先输出一些基本信息
    cout<<"Image width: "<<image.cols<<",height："<<image.rows<<",channels："<<image.channels
    ()<<endl;

    // 判断image的类型
    if(image.type() != CV_8UC1 && image.type() != CV_8UC3){
        cout<<"Please input a RGB or gray image."<<endl;
        return 0;
    }

    // 遍历图片，请注意以下遍历方式亦可使用于随机像素访问
    // 使用std::chrono 来给算法计时
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    for (size_t y=0; y < image.rows; y++){
        // 用cv::Mat::ptr获得图像的行指针
        unsigned char *row_ptr = image.ptr<unsigned char>(y);
        for (size_t x=0; x < image.cols; x++){
            // 访问位于x, y 处的像素
            unsigned char *data_ptr = &row_ptr[x * image.channels()];
            for(int c =0; c < image.channels(); c++){
                unsigned char data = data_ptr[c];
            }
        }
    }
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 -t1);
    cout<<"The traversal spend"<<time_used.count()<<"seconds."<<endl;

    // 关于cv::Mat的拷贝
    // 直接赋值并不会拷贝数据，浅层复制？？？
    cv::Mat image_another = image;
    // 修改image_another 会导致image发生变化
    image_another(cv::Rect(0, 0, 100, 100)).setTo(0); //将左上角块置零
    cv::imwrite("image_another.jpg", image_another);

    // 使用clone函数来拷贝数据，深层复制？？？
    cv::Mat image_clone = image.clone();
    image_clone(cv::Rect(0, 0, 100, 00)).setTo(255);
    cv::imwrite("image_clone.jpg", image_clone);

    cv::destroyAllWindows();
    return 0;
}
