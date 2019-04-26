/*
 * 型别萃取器设计
 * 服务于算法, 针对容器提取其iterator相应型别
 *            但对原生指针则不行, 原生指针没有标准型别
 *            使用偏特化方法, 如 <class T> => T value_type
 *                             <class T*> => T value_type  指针
 *                             <class const T*> => T value_type
 */

#ifndef MYSTL_TYPE_TRAITS_H
#define MYSTL_TYPE_TRAITS_H

#include <type_traits>

namespace MySTL {
    template<class T, T v>
    struct m_integral_constant {
        // 常量表达式, 编译过程中就能得到结果
        static constexpr T value = v;
    };

    template<bool b>
    using m_bool_constant = m_integral_constant<bool, b>;

    typedef m_bool_constant<true> m_true_type;
    typedef m_bool_constant<false> m_false_type;

    template<class T1, class T2>
    struct pair;

    template<class T>
    struct is_pair : MySTL::m_false_type {
    };

    template<class T1, class T2>
    struct is_pair<MySTL::pair<T1, T2>> : MySTL::m_true_type {
    };
}

#endif //MYSTL_TYPE_TRAITS_H
