/*
 * 迭代器设计
 */

#ifndef MYSTL_ITERATOR_H
#define MYSTL_ITERATOR_H

#include <cstddef>
#include <type_traits>
/* c标准库的头文件，定义了各种变量类型和宏
 * ptrdiff_t : 有符号整型, 两个指针相减的结果
 * size_t : 无符号整型, sizeof的结果
 * wchar_t : 宽字符大小的整型
 * NULL : 空指针常量
 */

namespace MySTL {
    /* 五种迭代器类型 */
    struct input_iterator_tag {
    };      // 只读迭代器
    struct output_iterator_tag {
    };      // 可写迭代器
    struct forward_iterator_tag : public input_iterator_tag {
    };      // 读写型迭代器
    struct bidirectional_iterator_tag : public forward_iterator_tag {
    };      // 双向迭代器
    struct random_access_iterator_tag : public bidirectional_iterator_tag {
    };      // 随机访问迭代器

    // iterator模板
    template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference=T &>
    struct iterator {
        // STL 标准型别
        typedef Category iterator_category;     // 迭代器类型
        typedef T value_type;                   // 所指对象类型
        typedef Pointer pointer;                // 对象指针
        typedef Reference reference;            // 对象引用
        typedef Distance difference_type;       // 两个迭代器之间的距离
    };

    // 判断迭代器是否有类型
    template<class T>
    struct has_iterator_cate {
    private:
        struct two {
            char a;
            char b;
        };

        // test仅做返回值类型校验, 无需方法体
        // 变长参数增强健壮性
        template<class U>
        static two test(...);

        template<class U>
        static char test(typename U::iterator_category * = 0);

    public:
        /* 若T有iterator_category则返回一个char
         * 否则为two => 设定为两个char的结构体
         */
        static const bool value = sizeof(test<T>(0)) == sizeof(char);
    };

    // 迭代器萃取基本萃取实现 空实现
    template<class Iterator, bool>
    struct iterator_traits_impl {
    };

    // 迭代器萃取, TRUE偏特化实现
    template<class Iterator>
    struct iterator_traits_impl<Iterator, true> {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::difference_type difference_type;
    };

    // 迭代器萃取辅助 空实现
    template<class Iterator, bool>
    struct iterator_traits_helper {
    };

    // 迭代器萃取辅助 TRUE偏特化实现
    // 使用标准库方法is_convertible, 当且仅当 arg1 => arg2 成立时为true
    //     arg1 => arg2 : 迭代器必须为 可读/可写迭代器的派生类
    template<class Iterator>
    struct iterator_traits_helper<Iterator, true> : public iterator_traits_impl<Iterator,
            std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
            std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value> {
    };

    /* 萃取器
     * 实现逻辑: iterator_traits 为 iterator_traits_helper的派生, 迭代器有iterator_category属性时偏特化实现, 否则为空实现
     *          iterator_traits_helper 为 iterator_traits_helper 的派生, 迭代器为 读/写 迭代器的派生时偏特化实现, 否则为空实现
     *          iterator_traits_impl 为 萃取基本功能实现
     */
    template<class Iterator>
    struct iterator_traits : public iterator_traits_helper<Iterator, has_iterator_cate<Iterator>::value> {
    };

    // 萃取器针对原生指针的偏特化实现
    template<class T>
    struct iterator_traits<T *> {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef ptrdiff_t difference_type;
    };

    // 萃取器针对常量指针的偏特化实现
    template<class T>
    struct iterator_traits<const T *> {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef const T *pointer;
        typedef const T &reference;
        typedef ptrdiff_t difference_type;
    };

}
#endif //MYSTL_ITERATOR_H
