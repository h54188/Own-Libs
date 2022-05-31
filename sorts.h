#ifndef sorts1
#define sorts1
#include <iostream>
using std::swap;

namespace sorts {
	//默认比较函数
	template<typename ElemType>

	inline bool cmpTwoElem(const ElemType a, const ElemType b) {
		return a < b;
	}
	//三数取中算法
	template<typename ElemType>

	ElemType MidOfThree(ElemType *first, ElemType *last, bool (*CompareElem)(const ElemType first_,
	                    const ElemType second_) = cmpTwoElem) {
		ElemType *mid = first + (last - first) / 2;
		if (CompareElem(*(last - 1), *first)) //最后一个与第一个是乱序就交换
			swap(*first, *(last - 1));
		if (CompareElem(*(last - 1), *mid)) //最后一个与中间是乱序就交换
			swap(*mid, *(last - 1));
		if (CompareElem(*mid, *first)) //中间与前面是乱序就交换
			swap(*first, *mid);
		return *mid;
	}
	//冒泡排序
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
	//插入排序
	template<typename ElemType>
	void InsSort(ElemType *SortStart, ElemType *SortEnd,

	             bool (*CompareElem)(const ElemType first_, const ElemType second_) = cmpTwoElem) {
		if (SortStart >= SortEnd)
			return;
		ElemType *lPoint, *rPoint;
		ElemType *outIter = SortStart, *inIter, *movIter; //外层指针,内层指针,移动指针
		ElemType pTemp;
		do {
			lPoint = SortStart - 1, rPoint = outIter - 1, inIter = outIter - 1; //初始化查找的内层指针
			pTemp = *outIter; //存储要插入的元素
			do {
				inIter = lPoint + (rPoint - lPoint + 1) / 2; //取中间指针
				if (lPoint >= rPoint) //如果左指针大于右指针停止
					break;
				if (!CompareElem(pTemp, *inIter)) //如果中间指针的值与待查询的值有序就有可能是答案
					lPoint = inIter;
				else
					rPoint = inIter - 1; //反之不是答案
			} while (lPoint <= rPoint);
			if (inIter != outIter - 1) {
				movIter = outIter - 1; //初始化赋值指针
				while (movIter > inIter) { //循环遍历向后移动一位
					*(movIter + 1) = *movIter; //高位赋值成低位
					--movIter; //向低位递减
				}
				*(movIter + 1) = pTemp; //最低位赋值成pTemp
			}
			++outIter;
		} while (outIter < SortEnd);
	}

	//快速排序
	template<typename ElemType>
	void QuickSort(ElemType *SortStart, ElemType *SortEnd, bool (*CompareElem)(const ElemType first_,
	               const ElemType second_) = cmpTwoElem) {
		if (SortEnd - SortStart <= 10) { //区间元素数量<=10就插入排序
			InsSort(SortStart, SortEnd, CompareElem);
			return;
		}
		ElemType *topLeft = SortStart - 1, *topRight = SortEnd; //记录与mid相同的左右储存栈顶

		ElemType *lPoint = SortStart, *rPoint = SortEnd - 1, mid; //左搜索指针,右搜索指针,中值
		mid = MidOfThree(SortStart, SortEnd, CompareElem); //三数取中

		do {
			while (lPoint < rPoint && !CompareElem(mid, *lPoint )) { //左指针小于等于mid就继续找
				if (!CompareElem(*lPoint, mid))
					swap(*lPoint, *(++topLeft));
				++lPoint;
			}
			while (lPoint < rPoint && !CompareElem(*rPoint, mid )) { //右指针大于等于mid就继续找
				if (!CompareElem(mid, *rPoint))
					swap(*rPoint, *(--topRight));
				--rPoint;
			}
			if (lPoint < rPoint) { //交换左右指针
				swap(*lPoint, *rPoint);
				++lPoint, --rPoint;
			}
		} while (lPoint < rPoint);

		while (SortStart - 1 < topLeft) { //聚集左元素
			swap(*topLeft, *(--lPoint));
			--topLeft;
		}
		while (topRight < SortEnd) { //聚集右元素
			swap(*topRight, *(++rPoint));
			++topRight;
		}
		if (SortStart < lPoint)
			QuickSort(SortStart, lPoint, CompareElem); //寻找左区间
		if (rPoint < SortEnd - 1)
			QuickSort(rPoint, SortEnd, CompareElem); //寻找右区间
	}

	//归并排序递归函数
	template <typename TypeElem>
	void __MergeSort(TypeElem *SortStart, TypeElem *SortEnd, TypeElem *TempStart, TypeElem *TempEnd,
	                 bool CompareElem(const TypeElem first_, const TypeElem second_) = cmpTwoElem) {
		TypeElem *midPoint = SortStart + (SortEnd - SortStart) / 2; //定义排序数组的中指针
		TypeElem *midTemp = TempStart + (TempEnd - TempStart) / 2; //定义存储数组的中指针
		if (SortEnd - SortStart <= 6) { //如果区间元素数量<=6个就插入排序
			InsSort(SortStart, SortEnd, CompareElem);
			return;
		}
		TypeElem *lPoint = SortStart, *rPoint = midPoint, *kIter = TempStart; //定义排序左指针,右指针,存储左指针
		__MergeSort(SortStart, midPoint, TempStart, midTemp, CompareElem); //搜索左区间
		__MergeSort(midPoint, SortEnd, midTemp, TempEnd, CompareElem); //搜索右区间
		if (CompareElem(*(midPoint - 1), *midPoint)) //如果有序且中间指针大于前一个指针就返回
			return;
		while (lPoint < midPoint && rPoint < SortEnd) { //比较并存储元素
			if (CompareElem(*lPoint, *rPoint)) {
				*kIter = *lPoint;
				++lPoint;
			} else {
				*kIter = *rPoint;
				++rPoint;
			}
			++kIter;
		}
		while (lPoint < midPoint) { //如果左半边元素没存储完就继续存储
			*kIter = *lPoint;
			++lPoint;
			++kIter;
		}
		while (rPoint < SortEnd) { //如果右半边元素没存储完就继续存储
			*kIter = *rPoint;
			++rPoint;
			++kIter;
		}
		while (TempStart < TempEnd) { //将存储数组里的值赋给原数组
			*SortStart = *TempStart;
			++SortStart, ++TempStart;
		}
		return;
	}
	//归并排序主函数
	template<typename TypeElem>

	void MergeSort(TypeElem *SortStart, TypeElem *SortEnd, bool CompareElem(const TypeElem first_,
	               const TypeElem second_) = cmpTwoElem) {
		TypeElem *pTemp = new TypeElem[SortEnd - SortStart]; //开辟存储空间
		__MergeSort(SortStart, SortEnd, pTemp, pTemp + (SortEnd - SortStart), CompareElem);
		delete[] pTemp; //销毁堆内存
	}

	//堆排序
	//heapify(构建逆序堆(有序称之为正序)),递归形式
#define __treeLeftChild(x,y) ((x) + ((x) - (y)) + 1)  //求解左孩子
#define __treeRightChild(x,y) ((x) + ((x) - (y)) + 2) //求解右孩子
	template<typename TypeElem>

	void __heapifyRecursion(TypeElem *HeapStart, TypeElem *HeapEnd, TypeElem *nowAddr,
	                        bool CompareElem(const TypeElem first_, const TypeElem second_) = cmpTwoElem) {
		TypeElem *leftChild = __treeLeftChild(nowAddr, HeapStart), //找到左孩子
		          *rightChild = __treeRightChild(nowAddr, HeapStart), //找到右孩子
		           *largestAddr = nowAddr; //定义指针存储最大值地址
		if (leftChild < HeapEnd && CompareElem(*largestAddr, *leftChild)) //如果最大节点与左子节点是正序就交换
			largestAddr = leftChild;
		if (rightChild < HeapEnd && CompareElem(*largestAddr, *rightChild)) //如果最大节点与右子节点是正序就交换
			largestAddr = rightChild;
		if (largestAddr != nowAddr) { //如果最大节点不是初始节点
			swap(*largestAddr, *nowAddr); //调整顺序
			__heapifyRecursion(HeapStart, HeapEnd, largestAddr, CompareElem); //继续向下调整节点顺序保证其为逆序堆
		}
		return;
	}
	//heapify构建逆序堆,非递归形式
	template<typename TypeElem>
	void __heapify(TypeElem *HeapStart, TypeElem *HeapEnd, TypeElem *nowAddr,

	               bool CompareElem(const TypeElem first_, const TypeElem second_) = cmpTwoElem) {
		TypeElem *rightChild,
		         *largestAddr = __treeLeftChild(nowAddr, HeapStart); //定义右孩子指针,定义指针存储最大值地址,左孩子指针
		TypeElem shiftDownData = *nowAddr; //下沉的数据
		while (largestAddr < HeapEnd) { //当当前节点有左孩子时
			rightChild = __treeRightChild(nowAddr, HeapStart); //找出右节点
			if (rightChild < HeapEnd && CompareElem(*largestAddr, *rightChild)) //如果最大节点与右子节点是正序就交换
				largestAddr = rightChild;
			if (CompareElem(shiftDownData, *largestAddr)) { //如果最大节点不是初始节点
				*nowAddr = *largestAddr; //调整顺序
				nowAddr = largestAddr;
			} else
				break;
			largestAddr = __treeLeftChild(nowAddr, HeapStart); //假设最大值在左边
		}
		*nowAddr = shiftDownData;
		return;
	}

	//堆排序主函数
	template<typename TypeElem>
#define __firstNotLeafNode(x,y) ((y) + (((x) - (y))/2 - 1))
	void HeapSort(TypeElem *SortStart, TypeElem *SortEnd,
	              bool CompareElem(const TypeElem first_, const TypeElem second_) = cmpTwoElem) {
		if (SortStart == NULL || SortStart >= SortEnd) //如果数组没有元素或者为空就返回
			return;
		TypeElem *BuildHeapIter = __firstNotLeafNode(SortEnd, SortStart); //找到第一个非叶子节点
		while (BuildHeapIter >= SortStart) { //如果迭代指针没有找到根节点就继续构建逆序堆
			__heapify(SortStart, SortEnd, BuildHeapIter, CompareElem);
			--BuildHeapIter;
		}
		BuildHeapIter = SortEnd - 1; //从后往前进行最大值交换
		while (BuildHeapIter > SortStart) {
			swap(*SortStart, *BuildHeapIter); //交换最后值与第一个值
			__heapify(SortStart, BuildHeapIter, SortStart, CompareElem); //调整顺序
			--BuildHeapIter;
		}
		return ;
	}
}


#endif //!sorts1