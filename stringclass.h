#pragma once
#ifndef STRINGCLASS_H				//条件编译开始
#define STRINGCLASS_H
#include<iostream>
#include<stdlib.h>
#include<cstring>
using namespace std;
class String
{
private:
	char * str;
	int size;
	
public:
	void Error(const char* cs)const { cout << cs<<endl; }//后置const常成员函数
	String(const char * c = " ");				//转换构造函数和默认构造函数一起用
	String(const String &s);
	~String();
	//访问方法
	String& operator = (const char * c);//转换赋值：类串=C串
	String& operator =(const String & s);//COPY赋值：类串 = 类串
	String& Insert(int id, const String & s);//子串插入
	String& Erase(int id, int num);//删除的位置  和  删除的个数
	String SubStr(const int& id, const int & num)const//返回子串
	String operator + (const String & s)const;//串的连接：类串 = 类串+类串//这里不返回引用
	String operator + (const char * c)const;//串的连接:类串 = 类串 + C串
	//下面这个要好好理解一下
	friend String operator+(const char * c, const String & s);//设置为友元函数  其实是一个普通函数
	bool operator == (const String & s)const;//串的比较：类串===类串
	bool operator == (const char * c)const;//串的比较：类串 == C串
	friend bool operator == (const String & s, const char * c);// 串的比较：C串 == 类串
	operator char*()const;//成员转换
	char& operator[](int id);//下标运算符
	const char & operator[](int id) const;//常量型下标运算符
	int Size(void)const { return size; }
	int Find_First_Of(char ch, int id)const;
	int Find_First_Of(const String& s, int id)const;
	//输入输出
	friend istream& operator <<(istream &input, String &s);//<<运算符重载
	friend ostream& operator >>(ostream &output, String &s);//>>运算符重载
	int ReadString(istream& input, char delimiter);

	
};
#endif 
