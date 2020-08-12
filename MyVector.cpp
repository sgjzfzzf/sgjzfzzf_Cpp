/*
    项目名称：MyVector(模仿C++Vector库内置的vector，利用链表结构，创作一种新的类vector类)
    作者：sgjzfzzf
    完成时间：2020.8.11
    卑微菜鸡的第一次尝试，错误很多，效率也有限
 */

//引入所需要的库
#include <iostream>
#include <string>
using namespace std;


//MyVector类的节点结构，利用模版类的方法提升兼容性
template <class T>
struct MyVectorNode{
    
    T data;//储存的数据
    MyVectorNode *to_last_node_pointer;//指向上一个节点的指针
    MyVectorNode *to_next_node_pointer;//指向下一个节点的指针
    int index;//-1代表起始节点，-2代表终止节点
    
};

//节点类的类定义
template<class T>
class MyVector{
private:
    
    MyVectorNode<T> *head,*tail;//头节点和尾节点的命名
    const string pass_end_warn_string="You have passed the tail of this vector, please check you code , please make sure the safety of this step.";//越界的异常语句，作为错误抛出使用
    const string is_not_all_int_or_double_warn_string="Your vector doesn't consists of allowed data type , please check it , and we will return the first data.";//数据检查的异常语句，作为错误抛出使用
    
    bool comparePattern(bool is_increase,T i1,T i2){
        if (is_increase)
            return i1<i2;
        else
            return i1>i2;
    }
    bool checkDataType(){
        try{
            if (typeid(head->to_next_node_pointer->data).name()!=typeid(int).name()&&
                typeid(head->to_next_node_pointer->data).name()!=typeid(double).name()&&
                typeid(head->to_next_node_pointer->data).name()!=typeid(float).name()&&
                typeid(head->to_next_node_pointer->data).name()!=typeid(long).name()&&
                typeid(head->to_next_node_pointer->data).name()!=typeid(double).name())
            throw is_not_all_int_or_double_warn_string;
        }catch(string warn_string){
            cout<<warn_string<<endl;
            return false;
        }
        return true;//检验数据类型是否是int,float,long int,double或char，否则结束函数并打印警示信息
    }
    
public:
    
    //构造函数
    MyVector(){
        head=new MyVectorNode<T>;
        tail=new MyVectorNode<T>;//申请堆上的动态空间
        head->to_next_node_pointer=tail;
        tail->to_last_node_pointer=head;//头尾节点的互联
        head->to_last_node_pointer=nullptr;
        tail->to_next_node_pointer=nullptr;//无用节点指向空
        head->index=-1;
        tail->index=-2;//利用特殊的index值标记头尾节点
    }
    
    //析构函数
    ~MyVector(){
        MyVectorNode<T>* p=head;
        while(p->index!=-2){
            MyVectorNode<T> *tmp=p->to_next_node_pointer;
            delete p;
            p=tmp;
        }//从头节点开始，依次删除各个节点申请的动态空间释放内存
        delete tail;
    }
    
    //返回MyVector的长度
    int size(){
        return tail->to_last_node_pointer->index+1;
    }
    
    //返回目标索引值对应的数据，为引用返回，传入参数为int类型目标索引值
    T& search(int target_index){
        MyVectorNode<T>* p=head;
        try{
            while(p->index!=-2&&p->index!=target_index){
                p=p->to_next_node_pointer;
            }//尝试检索目标索引值
            if(p->index==-2)
                throw pass_end_warn_string;//未检索到抛出异常
        }catch(string pass_end_warn_string){
            cout<<pass_end_warn_string<<" Now this function may return the last data."<<endl;//捕捉到异常打印危险提示语句
        }
        T& return_result=p->data;
        return return_result;//返回饮用值
    }
    
    //打印MyVector内的所有内容
    void printAll(){
        MyVectorNode<T>* p=head->to_next_node_pointer;
        cout<<"[";
        while(p->index!=-2){
            cout<<p->data<<" ";
            p=p->to_next_node_pointer;
        }//依次读取直到末尾
        cout<<"]"<<endl;
    }
    
    //在MyVector末尾添加数据，传入参数为所需要传入末尾的数据
    void pushBack(T input_data){
        MyVectorNode<T>* p_to_last_one=tail->to_last_node_pointer;
        tail->to_last_node_pointer=new MyVectorNode<T>;//添加新的节点
        MyVectorNode<T>* p_to_new_one=tail->to_last_node_pointer;
        p_to_last_one->to_next_node_pointer=p_to_new_one;
        p_to_new_one->to_next_node_pointer=tail;
        p_to_new_one->to_last_node_pointer=p_to_last_one;//链表结构重新构造
        p_to_new_one->data=input_data;//传入所需要存储的数据
        p_to_new_one->index=p_to_last_one->index+1;//后续数据索引值依次增加
    }
    
    //删除MyVector末尾的数据，并返回末尾数据
    T popBack(){
        T return_result=tail->to_last_node_pointer->data;
        deleteIndex(size()-1);
        return return_result;
    }
    
    //删除目标索引值处的数据，传入参数为int类型目标索引值
    void deleteIndex(T delete_index){
        MyVectorNode<T>* p=head->to_next_node_pointer;
        try{
            while(p->index!=delete_index&&p->index!=-2){
                p=p->to_next_node_pointer;
            }//依次读取直到读取到目标索引值
            if (p->index==-2)
                throw pass_end_warn_string;//读取越界抛出异常
        }catch(string pass_end_warn_string){
            cout<<pass_end_warn_string<<endl;
            return;
        }//捕捉异常并打印警告结束函数
        MyVectorNode<T>* ap=p->to_next_node_pointer;
        p->to_last_node_pointer->to_next_node_pointer=p->to_next_node_pointer;
        p->to_next_node_pointer->to_last_node_pointer=p->to_last_node_pointer;//重新构造删除处的链表结构
        while (ap->index!=-2) {
            --ap->index;
            ap=ap->to_next_node_pointer;
        }//后方索引值依次减1
        delete p;//释放内存空间
    }
    
    //在目标索引值处插入目标数据，第一个参数为int类型目标索引值，第二个参数为所需存入的目标数据
    void insert(int target_index,T data){
        MyVectorNode<T>* p=head->to_next_node_pointer;
        try{
            while(p->index!=target_index){
                p=p->to_next_node_pointer;
            }
            if (p->index==-2)
            throw pass_end_warn_string;
        }catch(string pass_end_warn_string){
            cout<<pass_end_warn_string<<endl;
            return;
        }//遍历找到目标索引值的位置
        MyVectorNode<T>* pl=p->to_last_node_pointer;
        pl->to_next_node_pointer=new MyVectorNode<T>;
        pl->to_next_node_pointer->to_next_node_pointer=p;
        p->to_last_node_pointer=pl->to_next_node_pointer;
        pl->to_next_node_pointer->to_last_node_pointer=pl;//重新构造插入处的链表结构
        p->to_last_node_pointer->index=p->index;//存入处的索引值
        p->to_last_node_pointer->data=data;//存入处的存入数据
        while(p->index!=-2){
            ++p->index;
            p=p->to_next_node_pointer;
        }//后续索引值依次加1
    }
    
    //依次打印各个节点的索引值，用于测试索引值标记是否正确，使用时可以忽视这一函数
    bool printIndex(){
        int k=0;
        MyVectorNode<T>* p=head->to_next_node_pointer;
        while(p->index!=-2){
            if (k!=p->index)
                return false;
            p=p->to_next_node_pointer;
            ++k;
        }
        return true;
    }
    
    //冒泡排序，参数默认为升序排列，若希望降序排列传入bool类型参数false
    void sort(bool is_increase=true){
        int length=size();
        if (!checkDataType())
            return;
        for (int i=length-1;i>=0;--i){
            bool flag=true;
            for (int j=0;j<i;++j){
                if(comparePattern(is_increase,search(j+1),search(j))){
                    swap(j,j+1);
                    flag=false;
                }
            }
            if (flag)
                return;
        }
    }
    
    //返回最大值，仅对int,float,long,double类型有效
    T max(){
        if(!checkDataType())
            return head->to_next_node_pointer->data;
        MyVectorNode<T>* p=head->to_next_node_pointer;
        T max_data=p->data;
        while(p->index!=-2){
            if (max_data<p->data)
                max_data=p->data;
            p=p->to_next_node_pointer;
        }
        return max_data;
    }
    
    //返回最小值，仅对int,float,long,double类型有效
    T min(){
        if(!checkDataType())
            return head->to_next_node_pointer->data;
        MyVectorNode<T>* p=head->to_next_node_pointer;
        T min_data=p->data;
        while(p->index!=-2){
            if (min_data>p->data)
                min_data=p->data;
            p=p->to_next_node_pointer;
        }
        return min_data;
    }
    
    //交换两个索引值对应的数据，传入两个int类型的参数，为希望交换值的索引值
    void swap(int i1,int i2){
        T tmp=search(i1);
        search(i1)=search(i2);
        search(i2)=tmp;
    }
};
