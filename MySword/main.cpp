/*
 * Created by G.Q on 2019/3/27.
 * 剑指offer题
 */
#include <iostream>
#include <cstring>
#include <stack>

template<class T>
inline void logOut(T &element) {
    std::cout << "[Logging]: " << element << std::endl;
}

void arrOutput(int *nums, int numsSize) {
    for (int i = 0; i != numsSize; ++i)
        std::cout << nums[i] << " ";
    std::cout << std::endl;
}

namespace Q0 {
    // 经典排序算法
    void BubbleSort(int *nums, int numsSize) {
        // 冒泡排序: 相邻的两个元素作比较
        for (int i = 0; i != numsSize - 1; ++i) {
            for (int j = 0; j != numsSize - i - 1; ++j) {
                // 第一次遍历会把最大的一个换到数组尾部
                if (nums[j] > nums[j + 1]) {
                    int tmp = nums[j];
                    nums[j] = nums[j + 1];
                    nums[j + 1] = tmp;
                }
            }
        }

        // 输出数组
        arrOutput(nums, numsSize);
    }

    void InsertSort(int *nums, int numsSize) {
        // 插入排序: 将数组分为有序数组(第一个元素)和无序数组(其他元素)
        int tmp, j;
        for (int i = 1; i != numsSize; ++i) {
            // 保存无序数组第一个
            tmp = nums[i];
            j = i - 1;
            while (tmp < nums[j] && j >= 0) {
                nums[j + 1] = nums[j];
                --j;
            }
            nums[j + 1] = tmp;
        }
        arrOutput(nums, numsSize);
    }

    void SelectSort(int *nums, int numsSize) {
        // 选择排序: 依次选取第i个元素和所有剩余元素作比较
        for (int i = 0; i != numsSize; ++i) {
            for (int j = i + 1; j != numsSize; ++j) {
                if (nums[i] > nums[j]) {
                    int tmp = nums[j];
                    nums[j] = nums[i];
                    nums[i] = tmp;
                }
            }
        }
        arrOutput(nums, numsSize);
    }

    void QuickSort(int *nums, int left, int right) {
        // 快速排序: 选出基准值k，小于k的放到左边，大于k的放到右边
        int begin = left;
        int end = right;
        int base = nums[begin];

        while (begin < end) {
            // 找到左边第一个比基准值小的
            while (nums[begin] < base) ++begin;
            while (nums[end] > base) --end;
            if (begin < end) {
                int temp = nums[begin];
                nums[begin] = nums[end];
                nums[end] = temp;
                --end;
                ++begin;
            }
        }
        if (begin == end)
            ++begin;
        if (left < end)
            QuickSort(nums, left, begin - 1);
        if (begin < right)
            QuickSort(nums, end + 1, right);
    }

    void ShellSort(int *nums, int numsSize) {
        // 带步长的插入排序
        for (int step = numsSize / 2; step >= 1; step /= 2) {
            for (int i = step; i < numsSize; ++i) {
                int temp = nums[i];
                int j = i - step;
                while (j >= 0 && nums[j] > temp) {
                    nums[j + step] = nums[j];
                    j -= step;
                }
                nums[j + step] = temp;
            }
        }
    }

    int test() {
        int nums[] = {3, 9, 0, 6, 7, 4, 3, 9, 0, 2};
        int numsSize = 10;

        // 冒泡排序
        // BubbleSort(nums, numsSize);

        // 选择排序
        // SelectSort(nums, numsSize);

        // 插入排序
        // InsertSort(nums, numsSize);

        // 快速排序
        QuickSort(nums, 0, 9);

        // 希尔排序
        // ShellSort(nums, numsSize);
        arrOutput(nums, 10);
        return 0;
    }
}

namespace Q1 {
    // 为类型CMyString添加赋值运算符
    class CMyString {
    public:
        CMyString(char *pData = nullptr);

        CMyString(const CMyString &str);

        ~CMyString() { delete[] this->m_pData; }

        // my code
        CMyString &operator=(const CMyString &str);

    private:
        char *m_pData;
    };

    CMyString::CMyString(const Q1::CMyString &str) {
        if (this->m_pData != nullptr) delete[] this->m_pData;

        this->m_pData = (char *) malloc(strlen(str.m_pData) + 1);
        strcmp(this->m_pData, str.m_pData);
    }

    CMyString &CMyString::operator=(const Q1::CMyString &str) {
        // 先判断不能自己对自己赋值
        if (this != &str) {
            // 拷贝构造一个临时的对象，用来做中间值，即使构造过程中出现错误，也不改变当前实例的内容
            // 离开if作用域后会自动调用析构函数析构临时对象
            CMyString strTemp(str);
            char *pTemp = strTemp.m_pData;
            strTemp.m_pData = str.m_pData;
            this->m_pData = pTemp;
        }
        return *this;
    }
}

namespace Q2 {
    // 单例模式C++
    class Singleton {
    public:
        static Singleton *getInstance() {
            return instance;
        }

    private:
        // 将构造函数放入私有区不允许外界调用
        Singleton() {}

        Singleton(const Singleton &) {}

        Singleton &operator=(const Singleton &);

        static Singleton *instance;
    };

    Singleton *Singleton::instance = new Singleton;
}

namespace Q3 {
    // 找出数组中重复的数字，数组长度为n，数字在n~1内
    int *dup(int *arr, int arrSize) {
        if (arr == nullptr || arrSize == 0)
            return nullptr;

        if (arrSize == 1) return arr;

        int index = 0;
        int *newArr = new int[arrSize];
        for (int i = 0; i != arrSize; ++i)
            newArr[i] = -1;
        for (int i = 0; i != arrSize; ++i) {
            while (arr[i] != i) {
                if (arr[i] == arr[arr[i]]) {
                    newArr[index++] = arr[i];
                    break;
                }
                int tmp = arr[i];
                arr[i] = arr[tmp];
                arr[tmp] = tmp;
            }
        }
        return newArr;
    }

    void test() {
        int arr[7] = {2, 3, 1, 0, 2, 5, 3};
        int *newArr = dup(arr, 7);
        for (int i = 0; i != 7; ++i) {
            if (newArr[i] != -1)
                std::cout << newArr[i] << " ";
        }
        delete[] newArr;
    }
}

namespace Q5 {
    // 找出二维数组中是否有指定整数
    bool findInt(int **&matrix, int rows, int columns, int number) {
        bool flag = false;

        if (matrix != nullptr && rows > 0 && columns > 0) {
            int maxRow = 0;
            int maxCol = columns - 1;
            while (maxRow < rows && maxCol < columns) {
                if (matrix[maxRow][maxCol] == number) {
                    flag = true;
                    break;
                } else if (matrix[maxRow][maxCol] > number)
                    --maxCol;
                else
                    ++maxRow;
            }
        }
        return flag;
    }

    void test() {
        int **matrix = new int *[4];
        for (int i = 0; i != 4; ++i)
            matrix[i] = new int[4];
        matrix[0][0] = 1;
        matrix[0][1] = 2;
        matrix[0][2] = 8;
        matrix[0][3] = 9;
        matrix[1][0] = 2;
        matrix[1][1] = 4;
        matrix[1][2] = 9;
        matrix[1][3] = 12;
        matrix[2][0] = 5;
        matrix[2][1] = 7;
        matrix[2][2] = 10;
        matrix[2][3] = 13;
        matrix[3][0] = 6;
        matrix[3][1] = 8;
        matrix[3][2] = 11;
        matrix[3][3] = 15;
        if (findInt(matrix, 4, 4, 5))
            std::cout << "find successfully" << std::endl;
        else
            std::cout << "None" << std::endl;
    }
}

namespace Q6 {
    // 替换字符串中的空格
    void replaceBlank(char *str, int capacity) {
        if (str == nullptr || capacity <= 0)
            return;

        int originalLength = static_cast<int>(strlen(str)) + 1;
        int numberOfBlank = 0;
        for (int i = 0; i != originalLength; ++i)
            if (str[i] == ' ')
                ++numberOfBlank;
        logOut(numberOfBlank);

        int newLength = originalLength + numberOfBlank * 2;
        logOut(newLength);
        if (newLength > capacity)
            return;

        // 设置两个指针
        int pStart = originalLength;
        int pEnd = newLength;
        while (pStart != pEnd) {
            if (str[pStart] == ' ') {
                str[--pEnd] = '0';
                str[--pEnd] = '2';
                str[--pEnd] = '%';
                --pStart;
            } else {
                str[--pEnd] = str[--pStart];
            }
        }
        for (int i = 0; i != newLength; ++i)
            std::cout << str[i];

    }

    void test() {
        char str[] = "I am softEnginee!";
        replaceBlank(str, 50);
    }
}

namespace Q7 {
    struct ListNode {
        int element;
        ListNode *next;

        ListNode(int theElement) : element(theElement), next(nullptr) {}
    };

    // 从尾到头打印链表
    void printReverse(ListNode *pHead) {
        // 方法一：把链表每个元素压入栈（较简单，不再演示）
        // 方法二：递归
        if (pHead != nullptr) {
            if (pHead->next != nullptr)
                printReverse(pHead->next);
            std::cout << pHead->element << std::endl;
        }
    }

    void test() {
        Q7::ListNode *pHead = new Q7::ListNode(1);
        Q7::ListNode *p2 = new Q7::ListNode(2);
        Q7::ListNode *p3 = new Q7::ListNode(3);
        Q7::ListNode *p4 = new Q7::ListNode(4);
        Q7::ListNode *p5 = new Q7::ListNode(5);
        Q7::ListNode *p6 = new Q7::ListNode(6);
        pHead->next = p2;
        p2->next = p3;
        p3->next = p4;
        p4->next = p5;
        p5->next = p6;
        printReverse(pHead);
        while (pHead != nullptr) {
            Q7::ListNode *tmp = pHead->next;
            delete pHead;
            pHead = tmp;
        }

    }
}

namespace Q9 {
    // 用两个栈组成一个队列
    template<class T>
    class CQueue {
    public:
        CQueue() {}

        ~CQueue() {}

        void appendTail(const T &theElement);

        T deleteHead();

    private:
        std::stack<T> stack1;
        std::stack<T> stack2;
    };

    template<class T>
    void CQueue<T>::appendTail(const T &theElement) {
        stack1.push(theElement);
    }

    template<class T>
    T CQueue<T>::deleteHead() {
        if (stack2.size() <= 0) {
            while (stack1.size() > 0) {
                T &data = stack1.top();
                stack1.pop();
                stack2.push(data);
            }
        }
        if (stack2.size() == 0)
            std::cout << "queue is empty" << std::endl;

        T head = stack2.top();
        stack2.pop();

        return head;
    }

    void test() {
        CQueue<int> q;
        q.appendTail(1);
        q.appendTail(2);
        std::cout << q.deleteHead() << std::endl;
    }
}

namespace Q10 {
    // 斐波那契数列
    long long Fibonacci(unsigned n) {
        int result[2] = {0, 1};
        if (n < 2)
            return result[n];

        long long fibNMinusOne = 1;
        long long fibNMinusTwo = 0;
        long long fibN = 0;
        for (unsigned int i = 2; i <= n; ++i) {
            fibN = fibNMinusOne + fibNMinusTwo;
            fibNMinusTwo = fibNMinusOne;
            fibNMinusOne = fibN;
        }
        return fibN;
    }
}

namespace Q11 {
    // 旋转数组的最小数字
    int MinInOrder(int *nums, int index1, int index2) {
        int result = nums[index1];
        for (int i = index1 + 1; i <= index2; ++i) {
            if (result > nums[i])
                result = nums[i];
        }
        return result;
    }

    int Min(int *nums, int numsSize) {
        if (nums == nullptr || numsSize <= 0) {
            std::cout << "Invalid parameters" << std::endl;
            return -1;
        }
        int index1 = 0;
        int index2 = numsSize - 1;
        int indexMid = index1;
        while (nums[index1] >= nums[index2]) {
            if (index2 - index1 == 1) {
                indexMid = index2;
                break;
            }
            indexMid = (index1 + index2) / 2;

            if (nums[indexMid] == nums[index2] && nums[indexMid] == nums[index1])
                return MinInOrder(nums, index1, index2);

            if (nums[indexMid] >= nums[index1])
                index1 = indexMid;
            else if (nums[indexMid] <= nums[index2])
                index2 = indexMid;
        }
        return nums[indexMid];
    }
}

int main() {
    Q0::test();
    // Q3::test();
    // Q5::test();
    // Q6::test();
    // Q7::test();
    // Q9::test();
}
