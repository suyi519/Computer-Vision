#pragma once
#include "CImg.h"
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include "fstream"
using namespace std;
using namespace cimg_library;

typedef unsigned char uchar;

#define BinaryGap 135            //ͼ���ֵ��ȫ����ֵ
#define BoundaryRemoveGap 7      //��Եȫ��Ϊ��ɫ�ľ���
#define Infinite 249480          //���������

#define SingleNumberImgBoundary 5                //��������ͼ���Ե������
#define YHistogramValleyMaxPixelNumber 0         //��Y����ֱ��ͼ���ȵ����ٺ�ɫ���ظ���
#define XHistogramValleyMaxPixelNumber 4         //��X����ֱ��ͼ���ȵ����ٺ�ɫ���ظ���
#define XHistogramLargerScaleThanAvgDist 3       //X����ֱ��ͼ���ָ�����ڼ���ƽ������ı���

#define SubImgBlackPixelPercentage 0.001         //һ����ͼ�ں�ɫ���س���һ���ٷֱȲ���������
#define NumberImageBlackPixelPercentage 0.35     //��������ͼ���ɫ���ظ���������������ͼ��
//��ɫ���ظ�����ֵ��һ������������������

struct PointPos {
	int x;
	int y;
	PointPos() : x(-1), y(-1) {}
	PointPos(int posX, int posY) : x(posX), y(posY) {}
};

class ImageSegmentation {
public:
	ImageSegmentation(const CImg<int>& _SrcImg);
	~ImageSegmentation();

	void processBinaryImage();                    //�����ɶ�ֵͼ��
	CImg<int> getBinaryImage();                   //��ȡ��ֵͼ��

	//���������ַ�����
	void numberSegmentationMainProcess(const string baseAddress);
	CImg<int> getHistogramImage();                //��ȡy�����ֱ��ͼ
	CImg<int> getImageWithDividingLine();         //��ȡ�������ߵĶ�ֵͼ
	CImg<int> getColoredNumberDividedImg();       //��ȡ���ֳɲ�ͬ��ɫ���ַ�ͼƬ
	CImg<int> getNumberDividedCircledImg();       //��ȡ�����ÿ��ָ��ͼƬ

private:
	//��y�����ֱ��ͼ���ҵ�������֮��ķָ���
	void findDividingLine();

	//ͨ���ָ��ߣ���ͼƬ����Ϊһ���е�����
	void divideIntoBarItemImg();

	//��ÿһ�Ż��ֵ�ͼ�����֣�������
	void doDilationForEachBarItemImg(int barItemIndex);

	//��ͨ�������㷨
	void connectedRegionsTagging();
	void connectedRegionsTaggingOfBarItemImg(int barItemIndex);

	//�����µ���tag
	void addNewClass(int x, int y, int barItemIndex);

	//�����ϡ����ϡ����С��������ĸ��ڵ����ҵ���С��tag
	void findMinTag(int x, int y, int &minTag, PointPos &minTagPointPos, int barItemIndex);

	//�ϲ�ĳ����(x,y)�������
	void mergeTagImageAndList(int x, int y, const int minTag, const PointPos minTagPointPos, int barItemIndex);

	//�洢ͼƬ�������һ��txt��ͼ���б�
	void saveSingleNumberImageAndImglist(int barItemIndex);

	//��ȡ�������ֵİ�Χ��
	void getBoundingOfSingleNum(int listIndex, int& xMin, int& xMax, int& yMin, int& yMax);


private:
	CImg<int> SrcGrayImg, BinaryImg, TagImage, HistogramImage, DividingImg;
	vector<CImg<int>> subImageSet;     //һ��������ͼ��
	int imgW, imgH;

	vector<int> inflectionYPointSet;    //�յ�
	vector<PointPos> divideLinePointSet;    //ֱ��ͼ��ֵ�����ߵ㼯

	int tagAccumulate = -1;            //���tag�ۼ�ֵ

	vector<int> classTagSet;                   //���tag�б�
	vector<list<PointPos>> pointPosListSet;    //װ�����tag��Ӧ�����е��λ�õ�list���б�
	vector<list<PointPos>> pointPosListSetForDisplay;

	string basePath;    //��������ͼƬ���ɡ�Ԥ�����ı����·��
	string imglisttxt = "";
};