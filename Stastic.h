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
		double a_UP, b_UP, r_UP, parameter1, parameter2, parameter3, parameter4; //δ֪��a,b,p1,p2,p3,p4,�Լ��̻����ָ��r
		double R_sqr; //�̻����Իع鷽�����Ч��
		double *x_axis, *y_axis; //x��������,y��������
		int *sections; //����ָ��
		int Asect;//�ֶκ�������
		Satistics();
		//���������ʼ������
		template<class Type>
		void AxisCreat(Type Num);
		//ƽ������������
		template<class Type>
		double Average(Type *Start, Type *End);
		//���������
		template<class Type>
		double Variance(Type *Start, Type *End);
		template<class Type>
		double StandardDeviation(Type *Start, Type *End);
		//ȡ��λ����������
		template<class Type>
		double Median(Type *Start, Type *End);
		//ȡ���������
		template<class Type>
		Type Range(Type *Start, Type *End);
		//�ֶμ�����������
		template<class Type, class Num>
		int *Section(Type *Start, Type *End, Num Interval);
		//�������ϵ������
		template<class Type>
		double Sample_Correlation_Coefficient(Type Start, Type End);
		//���Ծ���ع鷽�̶���
		template<class Type>
		void Linear_Empirical_Regression_Equation(Type Start, Type End);
};

Satistics::Satistics() {
	//���г�ʼ������
	Asect = 0;
	parameter1 = parameter2 = parameter3 = parameter4 = 0 ;
	a_UP = b_UP = r_UP = 0;
	sections = NULL;
	x_axis = y_axis = NULL;
	UP_Calculated = false;
	aver_x = aver_y = 0;
}
Satistics Sati;
//�����ʼ��
template<class Type>

void Satistics::AxisCreat(Type Num) {  //����Ԥ������������,����ΪNum+1
	x_axis = new double[int(Num + 1)], y_axis = new double[int(Num + 1)];
	int i = 0;
	while (i <= Num)         //Ϊ���鸽��ʼֵ��
		x_axis[i] = 0, y_axis[i] = 0, i++;
	UP_Calculated = false;   //�������¼��ؾͲ���ʹ��ԭ����������Իع鷽�̺��������ָ��
	return ;
}
//����ƽ����
template<class Type>

double Satistics::Average(Type *Start, Type *End) {
	double Result = 0; //���
	int Count = 0;     //������
	while (Start + Count < End) {    //ѭ�������ܺ�
		Result = Result + Start[Count];
		Count += 1;
	}
	return Result / Count;    //���㲢����ƽ����
}

//���㷽��
template<class Type>
double Satistics::Variance(Type *Start, Type *End) {
	double average = Average(Start, End);   //����ƽ����
	double Result = 0;
	int Count = 0;                      //������
	while (Start + Count < End) {               //ѭ�������ܺ� (a_i-ƽ����)^2
		Result += (average - Start[Count]) * (average - Start[Count]);
		Count += 1;
	}
	return Result / Count;     //���㲢���ط���
}
template<class Type>

inline double Satistics::StandardDeviation(Type *Start, Type *End) {
	return sqrt(Variance(Start, End)); //���÷�������ҿ�ƽ��
}

//ȡ��λ��
template<class Type>
double Satistics::Median(Type *Start, Type *End) {
	std::sort(Start, End); //����
	int amount = (End - Start + 1);
	if (amount % 2 == 1)
		return 1.0 * Start[(amount - 1) / 2];  //���amountΪ���� ��ô���м�һ����Ϊ(amount-1)/2
	else
		return (Start[(amount) / 2] + Start[(amount) / 2 - 1]) / 2.0; //���amountΪż�� ��ȡ�м���������ƽ��ֵ
}

//�󼫲�
template<class Type>
Type Satistics::Range(Type *Start, Type *End) {
	Type Max_ = -pow(2, sizeof(Type) * 8 - 1) + 1, Min_ = pow(2, sizeof(Type) * 8 - 1) - 1; //����ֵ�ͼ�Сֵ
	int Count = 0;
	while (Start + Count < End) {
		Max_ = Max(Start[Count], Max_ ) ; //ѡ�������
		Min_ = Min(Start[Count], Min_);  //ѡ����С��
		Count++;
	}
	return Max_ - Min_;     //���ֵ-��Сֵ
}

//��ֶ���ÿ�ε���������
template<class Type, class Num>
int *Satistics::Section(Type *Start, Type *End, Num Interval) {
	delete []sections;  //ɾ����һ�ε�ֵ
	std::sort(Start, End); //�ӵ͵�������
	sections = new int[End - Start + 1]; //��������ÿһ������������
	Type Start_Num = *Start;            //��ʼֵ
	int *init = sections;
	while (init <= sections + int(End - Start) + 1) //��ʼ������
		*(init++) = 0;
	int idx = 0, Count = 0;
	while (Start + Count < End) {
		while (Start_Num + (idx + 1)*Interval <= Start[Count]) //������Χˢ�����½�
			idx++;
		if (Start_Num + idx * Interval <= Start[Count] && Start_Num + (idx + 1)*Interval > Start[Count]) //����ڷ�Χ�ھ��ۼ�
			sections[idx]++;
		Count++;
	}
	Asect = idx;
	return sections;
}
//�������ϵ��ʵ��
template<class Type>

double Satistics::Sample_Correlation_Coefficient(Type Start, Type End) {
	if (!UP_Calculated) { //���û�м����
		aver_x = Average(x_axis + Start, x_axis + End);  //����x��y�����ƽ��ֵ
		aver_y = Average(y_axis + Start, y_axis + End);
		int idx = 0;
		while (Start + idx < End) { //����p1,p2,p3
			parameter1 += ((x_axis[Start + idx] - aver_x) * (y_axis[Start + idx] - aver_y));
			parameter2 += ((x_axis[Start + idx] - aver_x) * (x_axis[Start + idx] - aver_x));
			parameter3 += ((y_axis[Start + idx] - aver_y) * (y_axis[Start + idx] - aver_y));
			idx++;
		}
		UP_Calculated = true; //�������
	}
	return r_UP = parameter1 / (sqrt(parameter2) * sqrt(parameter3)); //������ؿ̻�ָ��
}
//���Ծ���ع鷽��ʵ��
template<class Type>

void Satistics::Linear_Empirical_Regression_Equation(Type Start, Type End) {
	if (!UP_Calculated) { //���û�м����
		aver_x = Average(x_axis + Start, x_axis + End);  //����x��y�����ƽ��ֵ
		aver_y = Average(y_axis + Start, y_axis + End);
		int idx = 0;
		while (Start + idx < End) { //����p1,p2,p3
			parameter1 += ((x_axis[Start + idx] - aver_x) * (y_axis[Start + idx] - aver_y));
			parameter2 += ((x_axis[Start + idx] - aver_x) * (x_axis[Start + idx] - aver_x));
			parameter3 += ((y_axis[Start + idx] - aver_y) * (y_axis[Start + idx] - aver_y));
			idx++;
		}
		idx = 0;
		b_UP = parameter1 / parameter2;  //���㷽��b��ֵ
		a_UP = aver_y - b_UP * aver_x;   //���㷽��a��ֵ
		while (Start + idx < End) {
			parameter4 += ((y_axis[Start + idx] - (x_axis[Start + idx] * b_UP + a_UP)) * (y_axis[Start + idx] -
			               (x_axis[Start + idx] * b_UP + a_UP)));
			idx++;
		}
		R_sqr = 1 - (parameter4 / parameter3);
		UP_Calculated = true;            //�������
	}
	return ;
}
#endif // !Stastic1