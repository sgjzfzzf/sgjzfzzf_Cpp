//作者：刘津榤
//时间：2021/3/22
//文件内容：RSA密码系统的简单实现
#include <iostream>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;

//随机数生成器
class RandomNumberProducer
{
public:
    RandomNumberProducer();
    bool isPrime(long long int);
    bool areComprime(long long int, long long int);
    int produceRandomNumber(long long int, long long int, bool);
    int produceRandomBits(long long int, bool);
};


//RSA加密解密模型
class RSAModel
{
private:
    long long int p;
    long long int q;
    long long int n;
    long long int eulerN;
    long long int d;
    long long int e;
    RandomNumberProducer producer;
    long long int pow_mod(long long int, long long int, long long int);

public:
    RSAModel();
    long long int privateKey();
    long long int publishedKey();
    long long int encode(long long int, long long int);
    vector<long long int> encode(string, long long int);
    long long int decode(long long int, long long int);
    string decode(vector<long long int>, long long int);
};

//交换函数
void swap(long long int &x, long long int &y)
{
    long long int tmp = x;
    x = y;
    y = tmp;
}

//初始化随机数列表
RandomNumberProducer::RandomNumberProducer()
{
    srand(time(NULL));
}

//用厄氏筛法判断是否是质数
bool RandomNumberProducer::isPrime(long long int x)
{
    if (x <= 1)
    {
        cerr << "ERROR!Please check you input." << endl;
        return false;
    }
    else if (x == 2)
    {
        return true;
    }
    else
    {
        for (int i = 2; i <= sqrt(x); ++i)
        {
            if (x % i == 0)
            {
                return false;
            }
        }
        return true;
    }
}

//用辗转相除法判断两数是否互质
bool RandomNumberProducer::areComprime(long long int x, long long int y)
{
    if (x < y)
    {
        swap(x, y);
    }
    int tmp = x % y;
    while (tmp != 0)
    {
        x = y;
        y = tmp;
        tmp = x % y;
    }
    return y == 1;
}

//返回一个[min,max)区间的随机数，producePrimeNumber决定是否返回数必须为质数
int RandomNumberProducer::produceRandomNumber(long long int min, long long int max, bool producePrimeNumber = false)
{
    long long int randomNumber;
    do
    {
        randomNumber = min + rand() % (max - min);
    } while (!isPrime(randomNumber) && producePrimeNumber);
    return randomNumber;
}

//产生定长的比特串
int RandomNumberProducer::produceRandomBits(long long int k, bool producePrimeNumber = false)
{
    return produceRandomNumber(1 << k - 1, 1 << k, producePrimeNumber);
}

//带有模运算的乘方的实现，x为底数，i为指数，m为模
long long int RSAModel::pow_mod(long long int x, long long int i, long long int m)
{
    long long int ans = 1, b = x;
    for (; i != 0; i /= 2)
    {
        if (i % 2 == 1)
        {
            ans = ans * b % m;
        }
        b = b * b % m;
    }
    return ans;
}

//定义RSA模型中的各种参数
RSAModel::RSAModel()
{
    p = producer.produceRandomBits(14, true);
    q = producer.produceRandomBits(14, true);
    n = p * q;
    eulerN = (p - 1) * (q - 1);
    do
    {
        d = producer.produceRandomNumber(1, eulerN);
    } while (!producer.areComprime(d, eulerN));//生成的d必须在1与eulerN之间且两者互质
    for (e = 1; (d * e - 1) % eulerN != 0; ++e)
        ;//遍历生辰合适的e
}

//返回私钥
long long int RSAModel::privateKey()
{
    return d;
}

//返回公钥
long long int RSAModel::publishedKey()
{
    return e;
}

//对单个数字的加密函数，生成的密文也为一个数字，第一个参数doc为明文，第二个参数pubKey为公钥
long long int RSAModel::encode(long long int doc, long long int pubKey)
{
    return pow_mod(doc, pubKey, n);
}

//对整个字符串的加密函数，生成的密文为一个字符数组，第一个参数doc为明文，第二个参数pubKey为公钥
vector<long long int> RSAModel::encode(string doc, long long int pubKey)
{
    vector<long long int> sec;
    for (char ch : doc)
    {
        sec.push_back(encode(static_cast<int>(ch), pubKey));
    }
    return sec;
}

//对单个数字密文的解密函数，第一个参数sec为密文，第二个参数priKey为私钥
long long int RSAModel::decode(long long int sec, long long int priKey)
{
    return pow_mod(sec, priKey, n);
}

//对数字数组密文的解密函数，第一个参数sec为密文，第二个参数priKey为私钥
string RSAModel::decode(vector<long long int> sec, long long int priKey)
{
    string doc;
    for (int n : sec)
    {
        doc += static_cast<char>(decode(n, priKey));
    }
    return doc;
}

int main()
{
    RSAModel model;//RSA模型定义
    vector<long long int> sec;
    string doc = "\"Mathematical Fundation of Information Security + 201202001 + 学号\"", sec_d;//欲加密的字符串
    sec = model.encode(doc, model.publishedKey());//加密后的数字数组
    sec_d = model.decode(sec, model.privateKey());//解密后的字符串
    cout << "original information is " << doc << endl;
    cout << "encoded information is ";
    for (int n : sec)
    {
        cout << n << ',';
    }
    cout << endl;
    cout << "decoded information is " << sec_d << endl;
    return 0;
}
