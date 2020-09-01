/*
 名称：快排算法
 作者：sgjzfzzf
 时间：2020.9.1
 自己尝试复原快排算法，感觉其中还是有一些步骤的处理有些玄学。总的来说主要还是利用递归的思想先利用一个标准值对数组成员进行分类，分成大于和小于两类，再分别继续递归处理直到完成
 */


#include<iostream>
using namespace std;

//交换函数，交换两个变量的值
void swap(int& a,int& b){
    int tmp=a;
    a=b;
    b=tmp;
}


//快排函数，第一个参数为int数组。第二个参数为int类型的起始位置，使用时为0，第二个参数为int类型的终止位置，使用时为数组最后一位的索引值
void qsort(int* array,int start,int end){
    int length=end-start+1;//定义长度
    if (length==2){
        if (array[start]>array[end])
            swap(array[start],array[end]);
    }//长度小于2直接结束，等于2进行简单判断后结束
    else if (length>2){
        int lh=start,rh=end;
        while (rh>lh) {
            while (array[lh]<=array[rh]&&rh>lh){
                --rh;
            }//从右向左进行检索，找到一位小于目标值的数组成员
            if (rh>lh){
                swap(array[lh],array[rh]);
            }//进行交换，确保大于目标值的成员在右侧
            while (array[lh]<=array[rh]&&rh>lh){
                ++lh;
            }//从左向右进行检索，找到一位大于目标值的数组成员
            if (rh>lh){
                swap(array[lh],array[rh]);
            }//进行交换，确保大于目标值的成员在左侧
        }
        qsort(array,start,lh-1);//对比目标值小的数组成员进行快排
        qsort(array,lh+1,end);//对比目标值大的数组成员进行快排
    }
}
