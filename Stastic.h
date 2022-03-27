#ifndef Stastic1
#define Stastic1
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
template<class Type>

Type const &Max(Type const &x, Type const &y) {
	return x > y ? x : y;
}
template<class Type>

Type const &Min(Type const &x, Type const &y) {
	return x < y ? x : y;
}
using namespace std;

class Satistics {
	private:
		bool UP_Calculated;
	public:
		double aver_x, aver_y;
		double a_UP, b_UP, r_UP, parameter1, parameter2, parameter3, parameter4; //未知数a,b,p1,p2,p3,p4,以及刻画相关指数r
		double R_sqr; //刻画线性回归方程拟合效果
		double *x_axis, *y_axis; //x坐标数组,y坐标数组
		int *sections; //整形指针
		int Asect;//分段函数段数
		Satistics();
		//坐标数组初始化定义
		template<class Type>
		void AxisCreat(Type Num);
		//平均数函数定义
		template<class Type>
		double Average(Type *Start, Type *End);
		//方差函数定义
		template<class Type>
		double Variance(Type *Start, Type *End);
		template<class Type>
		double StandardDeviation(Type *Start, Type *End);
		//取中位数函数定义
		template<class Type>
		double Median(Type *Start, Type *End);
		//取极差函数定义
		template<class Type>
		Type Range(Type *Start, Type *End);
		//分段计数函数定义
		template<class Type, class Num>
		int *Section(Type *Start, Type *End, Num Interval);
		//样本相关系数定义
		template<class Type>
		double Sample_Correlation_Coefficient(Type Start, Type End);
		//线性经验回归方程定义
		template<class Type>
		void Linear_Empirical_Regression_Equation(Type Start, Type End);
};

Satistics::Satistics() {
	//进行初始化加载
	Asect = 0;
	parameter1 = parameter2 = parameter3 = parameter4 = 0 ;
	a_UP = b_UP = r_UP = 0;
	sections = NULL;
	x_axis = y_axis = NULL;
	UP_Calculated = false;
	aver_x = aver_y = 0;
}
Satistics Sati;
//坐标初始化
template<class Type>

void Satistics::AxisCreat(Type Num) {  //用来预处理坐标数组,长度为Num+1
	x_axis = new double[int(Num + 1)], y_axis = new double[int(Num + 1)];
	int i = 0;
	while (i <= Num)         //为数组附初始值零
		x_axis[i] = 0, y_axis[i] = 0, i++;
	UP_Calculated = false;   //若果重新加载就不再使用原来计算的线性回归方程和相关期望指数
	return ;
}
//计算平均数
template<class Type>

double Satistics::Average(Type *Start, Type *End) {
	double Result = 0; //结果
	int Count = 0;     //计数器
	while (Start + Count < End) {    //循环计算总和
		Result = Result + Start[Count];
		Count += 1;
	}
	return Result / Count;    //计算并返回平均数
}

//计算方差
template<class Type>
double Satistics::Variance(Type *Start, Type *End) {
	double average = Average(Start, End);   //计算平均数
	double Result = 0;
	int Count = 0;                      //计数器
	while (Start + Count < End) {               //循环计算总和 (a_i-平均数)^2
		Result += (average - Start[Count]) * (average - Start[Count]);
		Count += 1;
	}
	return Result / Count;     //计算并返回方差
}
template<class Type>

inline double Satistics::StandardDeviation(Type *Start, Type *End) {
	return sqrt(Variance(Start, End)); //调用方差函数并且开平方
}

//取中位数
template<class Type>
double Satistics::Median(Type *Start, Type *End) {
	std::sort(Start, End); //排序
	int amount = (End - Start + 1);
	if (amount % 2 == 1)
		return 1.0 * Start[(amount - 1) / 2];  //如果amount为奇数 那么最中间一个数为(amount-1)/2
	else
		return (Start[(amount) / 2] + Start[(amount) / 2 - 1]) / 2.0; //如果amount为偶数 就取中间两个数的平均值
}

//求极差
template<class Type>
Type Satistics::Range(Type *Start, Type *End) {
	Type Max_ = -pow(2, sizeof(Type) * 8 - 1) + 1, Min_ = pow(2, sizeof(Type) * 8 - 1) - 1; //极大值和极小值
	int Count = 0;
	while (Start + Count < End) {
		Max_ = Max(Start[Count], Max_ ) ; //选出最大者
		Min_ = Min(Start[Count], Min_);  //选出最小者
		Count++;
	}
	return Max_ - Min_;     //最大值-最小值
}

//求分段中每段的数据数量
template<class Type, class Num>
int *Satistics::Section(Type *Start, Type *End, Num Interval) {
	delete []sections;  //删除上一次的值
	std::sort(Start, End); //从低到高排序
	sections = new int[End - Start + 1]; //用来计算每一段数量的数组
	Type Start_Num = *Start;            //开始值
	int *init = sections;
	while (init <= sections + int(End - Start) + 1) //初始化数组
		*(init++) = 0;
	int idx = 0, Count = 0;
	while (Start + Count < End) {
		while (Start_Num + (idx + 1)*Interval <= Start[Count]) //超过范围刷新上下界
			idx++;
		if (Start_Num + idx * Interval <= Start[Count] && Start_Num + (idx + 1)*Interval > Start[Count]) //如果在范围内就累加
			sections[idx]++;
		Count++;
	}
	Asect = idx;
	return sections;
}
//样本相关系数实现
template<class Type>

double Satistics::Sample_Correlation_Coefficient(Type Start, Type End) {
	if (!UP_Calculated) { //如果没有计算过
		aver_x = Average(x_axis + Start, x_axis + End);  //计算x和y数组的平均值
		aver_y = Average(y_axis + Start, y_axis + End);
		int idx = 0;
		while (Start + idx < End) { //计算p1,p2,p3
			parameter1 += ((x_axis[Start + idx] - aver_x) * (y_axis[Start + idx] - aver_y));
			parameter2 += ((x_axis[Start + idx] - aver_x) * (x_axis[Start + idx] - aver_x));
			parameter3 += ((y_axis[Start + idx] - aver_y) * (y_axis[Start + idx] - aver_y));
			idx++;
		}
		UP_Calculated = true; //计算过了
	}
	return r_UP = parameter1 / (sqrt(parameter2) * sqrt(parameter3)); //计算相关刻画指数
}
//线性经验回归方程实现
template<class Type>

void Satistics::Linear_Empirical_Regression_Equation(Type Start, Type End) {
	if (!UP_Calculated) { //如果没有计算过
		aver_x = Average(x_axis + Start, x_axis + End);  //计算x和y数组的平均值
		aver_y = Average(y_axis + Start, y_axis + End);
		int idx = 0;
		while (Start + idx < End) { //计算p1,p2,p3
			parameter1 += ((x_axis[Start + idx] - aver_x) * (y_axis[Start + idx] - aver_y));
			parameter2 += ((x_axis[Start + idx] - aver_x) * (x_axis[Start + idx] - aver_x));
			parameter3 += ((y_axis[Start + idx] - aver_y) * (y_axis[Start + idx] - aver_y));
			idx++;
		}
		idx = 0;
		b_UP = parameter1 / parameter2;  //计算方程b的值
		a_UP = aver_y - b_UP * aver_x;   //计算方程a的值
		while (Start + idx < End) {
			parameter4 += ((y_axis[Start + idx] - (x_axis[Start + idx] * b_UP + a_UP)) * (y_axis[Start + idx] -
			               (x_axis[Start + idx] * b_UP + a_UP)));
			idx++;
		}
		R_sqr = 1 - (parameter4 / parameter3);
		UP_Calculated = true;            //计算过了
	}
	return ;
}
#endif // !Stastic1