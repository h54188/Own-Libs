#ifndef sorts1
#define sorts1
#include <iostream>
using std::swap;

namespace sorts {
	//Ĭ�ϱȽϺ���
	template<typename ElemType>

	inline bool cmpTwoElem(const ElemType a, const ElemType b) {
		return a < b;
	}
	//����ȡ���㷨
	template<typename ElemType>

	ElemType MidOfThree(ElemType *first, ElemType *last, bool (*CompareElem)(const ElemType first_,
	                    const ElemType second_) = cmpTwoElem) {
		ElemType *mid = first + (last - first) / 2;
		if (CompareElem(*(last - 1), *first)) //���һ�����һ��������ͽ���
			swap(*first, *(last - 1));
		if (CompareElem(*(last - 1), *mid)) //���һ�����м�������ͽ���
			swap(*mid, *(last - 1));
		if (CompareElem(*mid, *first)) //�м���ǰ��������ͽ���
			swap(*first, *mid);
		return *mid;
	}
	//ð������
	template<typename ElemType>
	void BubSort(ElemType *SortStart, ElemType *SortEnd,

	             bool (*CompareElem)(const ElemType first_, const ElemType second_) = cmpTwoElem) {
		if (SortStart >= SortEnd)
			return;
		bool breakSort;
		ElemType *StartPoint = SortStart, *EndPoint = SortEnd + 1;
		do {
			breakSort = true;
			StartPoint = SortStart;
			--EndPoint;
			do {
				if (CompareElem(*(StartPoint + 1), *StartPoint)) {
					swap(*(StartPoint + 1), *StartPoint);
					breakSort = false;
				}
				++StartPoint;
			} while (StartPoint < EndPoint - 1);
			if (breakSort)
				return;
		} while (SortStart < EndPoint);
	}
	//��������
	template<typename ElemType>
	void InsSort(ElemType *SortStart, ElemType *SortEnd,

	             bool (*CompareElem)(const ElemType first_, const ElemType second_) = cmpTwoElem) {
		if (SortStart >= SortEnd)
			return;
		ElemType *lPoint, *rPoint;
		ElemType *outIter = SortStart, *inIter, *movIter; //���ָ��,�ڲ�ָ��,�ƶ�ָ��
		ElemType pTemp;
		do {
			lPoint = SortStart - 1, rPoint = outIter - 1, inIter = outIter - 1; //��ʼ�����ҵ��ڲ�ָ��
			pTemp = *outIter; //�洢Ҫ�����Ԫ��
			do {
				inIter = lPoint + (rPoint - lPoint + 1) / 2; //ȡ�м�ָ��
				if (lPoint >= rPoint) //�����ָ�������ָ��ֹͣ
					break;
				if (!CompareElem(pTemp, *inIter)) //����м�ָ���ֵ�����ѯ��ֵ������п����Ǵ�
					lPoint = inIter;
				else
					rPoint = inIter - 1; //��֮���Ǵ�
			} while (lPoint <= rPoint);
			if (inIter != outIter - 1) {
				movIter = outIter - 1; //��ʼ����ֵָ��
				while (movIter > inIter) { //ѭ����������ƶ�һλ
					*(movIter + 1) = *movIter; //��λ��ֵ�ɵ�λ
					--movIter; //���λ�ݼ�
				}
				*(movIter + 1) = pTemp; //���λ��ֵ��pTemp
			}
			++outIter;
		} while (outIter < SortEnd);
	}

	//��������
	template<typename ElemType>
	void QuickSort(ElemType *SortStart, ElemType *SortEnd, bool (*CompareElem)(const ElemType first_,
	               const ElemType second_) = cmpTwoElem) {
		if (SortEnd - SortStart <= 10) { //����Ԫ������<=10�Ͳ�������
			InsSort(SortStart, SortEnd, CompareElem);
			return;
		}
		ElemType *topLeft = SortStart - 1, *topRight = SortEnd; //��¼��mid��ͬ�����Ҵ���ջ��

		ElemType *lPoint = SortStart, *rPoint = SortEnd - 1, mid; //������ָ��,������ָ��,��ֵ
		mid = MidOfThree(SortStart, SortEnd, CompareElem); //����ȡ��

		do {
			while (lPoint < rPoint && !CompareElem(mid, *lPoint )) { //��ָ��С�ڵ���mid�ͼ�����
				if (!CompareElem(*lPoint, mid))
					swap(*lPoint, *(++topLeft));
				++lPoint;
			}
			while (lPoint < rPoint && !CompareElem(*rPoint, mid )) { //��ָ����ڵ���mid�ͼ�����
				if (!CompareElem(mid, *rPoint))
					swap(*rPoint, *(--topRight));
				--rPoint;
			}
			if (lPoint < rPoint) { //��������ָ��
				swap(*lPoint, *rPoint);
				++lPoint, --rPoint;
			}
		} while (lPoint < rPoint);

		while (SortStart - 1 < topLeft) { //�ۼ���Ԫ��
			swap(*topLeft, *(--lPoint));
			--topLeft;
		}
		while (topRight < SortEnd) { //�ۼ���Ԫ��
			swap(*topRight, *(++rPoint));
			++topRight;
		}
		if (SortStart < lPoint)
			QuickSort(SortStart, lPoint, CompareElem); //Ѱ��������
		if (rPoint < SortEnd - 1)
			QuickSort(rPoint, SortEnd, CompareElem); //Ѱ��������
	}

	//�鲢����ݹ麯��
	template <typename TypeElem>
	void __MergeSort(TypeElem *SortStart, TypeElem *SortEnd, TypeElem *TempStart, TypeElem *TempEnd,
	                 bool CompareElem(const TypeElem first_, const TypeElem second_) = cmpTwoElem) {
		TypeElem *midPoint = SortStart + (SortEnd - SortStart) / 2; //���������������ָ��
		TypeElem *midTemp = TempStart + (TempEnd - TempStart) / 2; //����洢�������ָ��
		if (SortEnd - SortStart <= 6) { //�������Ԫ������<=6���Ͳ�������
			InsSort(SortStart, SortEnd, CompareElem);
			return;
		}
		TypeElem *lPoint = SortStart, *rPoint = midPoint, *kIter = TempStart; //����������ָ��,��ָ��,�洢��ָ��
		__MergeSort(SortStart, midPoint, TempStart, midTemp, CompareElem); //����������
		__MergeSort(midPoint, SortEnd, midTemp, TempEnd, CompareElem); //����������
		if (CompareElem(*(midPoint - 1), *midPoint)) //����������м�ָ�����ǰһ��ָ��ͷ���
			return;
		while (lPoint < midPoint && rPoint < SortEnd) { //�Ƚϲ��洢Ԫ��
			if (CompareElem(*lPoint, *rPoint)) {
				*kIter = *lPoint;
				++lPoint;
			} else {
				*kIter = *rPoint;
				++rPoint;
			}
			++kIter;
		}
		while (lPoint < midPoint) { //�������Ԫ��û�洢��ͼ����洢
			*kIter = *lPoint;
			++lPoint;
			++kIter;
		}
		while (rPoint < SortEnd) { //����Ұ��Ԫ��û�洢��ͼ����洢
			*kIter = *rPoint;
			++rPoint;
			++kIter;
		}
		while (TempStart < TempEnd) { //���洢�������ֵ����ԭ����
			*SortStart = *TempStart;
			++SortStart, ++TempStart;
		}
		return;
	}
	//�鲢����������
	template<typename TypeElem>

	void MergeSort(TypeElem *SortStart, TypeElem *SortEnd, bool CompareElem(const TypeElem first_,
	               const TypeElem second_) = cmpTwoElem) {
		TypeElem *pTemp = new TypeElem[SortEnd - SortStart]; //���ٴ洢�ռ�
		__MergeSort(SortStart, SortEnd, pTemp, pTemp + (SortEnd - SortStart), CompareElem);
		delete[] pTemp; //���ٶ��ڴ�
	}

	//������
	//heapify(���������(�����֮Ϊ����)),�ݹ���ʽ
#define __treeLeftChild(x,y) ((x) + ((x) - (y)) + 1)  //�������
#define __treeRightChild(x,y) ((x) + ((x) - (y)) + 2) //����Һ���
	template<typename TypeElem>

	void __heapifyRecursion(TypeElem *HeapStart, TypeElem *HeapEnd, TypeElem *nowAddr,
	                        bool CompareElem(const TypeElem first_, const TypeElem second_) = cmpTwoElem) {
		TypeElem *leftChild = __treeLeftChild(nowAddr, HeapStart), //�ҵ�����
		          *rightChild = __treeRightChild(nowAddr, HeapStart), //�ҵ��Һ���
		           *largestAddr = nowAddr; //����ָ��洢���ֵ��ַ
		if (leftChild < HeapEnd && CompareElem(*largestAddr, *leftChild)) //������ڵ������ӽڵ�������ͽ���
			largestAddr = leftChild;
		if (rightChild < HeapEnd && CompareElem(*largestAddr, *rightChild)) //������ڵ������ӽڵ�������ͽ���
			largestAddr = rightChild;
		if (largestAddr != nowAddr) { //������ڵ㲻�ǳ�ʼ�ڵ�
			swap(*largestAddr, *nowAddr); //����˳��
			__heapifyRecursion(HeapStart, HeapEnd, largestAddr, CompareElem); //�������µ����ڵ�˳��֤��Ϊ�����
		}
		return;
	}
	//heapify���������,�ǵݹ���ʽ
	template<typename TypeElem>
	void __heapify(TypeElem *HeapStart, TypeElem *HeapEnd, TypeElem *nowAddr,

	               bool CompareElem(const TypeElem first_, const TypeElem second_) = cmpTwoElem) {
		TypeElem *rightChild,
		         *largestAddr = __treeLeftChild(nowAddr, HeapStart); //�����Һ���ָ��,����ָ��洢���ֵ��ַ,����ָ��
		TypeElem shiftDownData = *nowAddr; //�³�������
		while (largestAddr < HeapEnd) { //����ǰ�ڵ�������ʱ
			rightChild = __treeRightChild(nowAddr, HeapStart); //�ҳ��ҽڵ�
			if (rightChild < HeapEnd && CompareElem(*largestAddr, *rightChild)) //������ڵ������ӽڵ�������ͽ���
				largestAddr = rightChild;
			if (CompareElem(shiftDownData, *largestAddr)) { //������ڵ㲻�ǳ�ʼ�ڵ�
				*nowAddr = *largestAddr; //����˳��
				nowAddr = largestAddr;
			} else
				break;
			largestAddr = __treeLeftChild(nowAddr, HeapStart); //�������ֵ�����
		}
		*nowAddr = shiftDownData;
		return;
	}

	//������������
	template<typename TypeElem>
#define __firstNotLeafNode(x,y) ((y) + (((x) - (y))/2 - 1))
	void HeapSort(TypeElem *SortStart, TypeElem *SortEnd,
	              bool CompareElem(const TypeElem first_, const TypeElem second_) = cmpTwoElem) {
		if (SortStart == NULL || SortStart >= SortEnd) //�������û��Ԫ�ػ���Ϊ�վͷ���
			return;
		TypeElem *BuildHeapIter = __firstNotLeafNode(SortEnd, SortStart); //�ҵ���һ����Ҷ�ӽڵ�
		while (BuildHeapIter >= SortStart) { //�������ָ��û���ҵ����ڵ�ͼ������������
			__heapify(SortStart, SortEnd, BuildHeapIter, CompareElem);
			--BuildHeapIter;
		}
		BuildHeapIter = SortEnd - 1; //�Ӻ���ǰ�������ֵ����
		while (BuildHeapIter > SortStart) {
			swap(*SortStart, *BuildHeapIter); //�������ֵ���һ��ֵ
			__heapify(SortStart, BuildHeapIter, SortStart, CompareElem); //����˳��
			--BuildHeapIter;
		}
		return ;
	}
}


#endif //!sorts1