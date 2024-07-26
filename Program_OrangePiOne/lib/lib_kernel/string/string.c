//
// Created by huangcheng on 2024/5/28.
//

#include "string.h"

/* 将dst_起始的size个字节置为value */
void memset(void* dst_, uint8_t value, uint32_t size) {
    uint8_t* dst = (uint8_t*)dst_;
    while (size-- > 0)
        *dst++ = value;
}

/* 将src_起始的size个字节复制到dst_ */
void memcpy(void* dst_, const void* src_, uint32_t size) {
    uint8_t* dst = dst_;
    const uint8_t* src = src_;
    while (size-- > 0)
        *dst++ = *src++;
}

/* 连续比较以地址a_和地址b_开头的size个字节,若相等则返回0,若a_大于b_返回+1,否则返回-1 */
int memcmp(const void* a_, const void* b_, uint32_t size) {
    const char* a = a_;
    const char* b = b_;
    while (size-- > 0) {
        if(*a != *b) {
            return *a > *b ? 1 : -1;
        }
        a++;
        b++;
    }
    return 0;
}

/* 将字符串从src_复制到dst_ */
char* strcpy(char* dst_, const char* src_) {
    char* r = dst_;		       // 用来返回目的字符串起始地址
    while((*dst_++ = *src_++));
    return r;
}

/* 返回字符串长度 */
uint32_t strlen(const char* str) {
    const char* p = str;
    while(*p++);
    return (p - str - 1);
}

/* 比较两个字符串,若a_中的字符大于b_中的字符返回1,相等时返回0,否则返回-1. */
int8_t strcmp (const char* a, const char* b) {
    while (*a != 0 && *a == *b) {
        a++;
        b++;
    }
/* 如果*a小于*b就返回-1,否则就属于*a大于等于*b的情况。在后面的布尔表达式"*a > *b"中,
 * 若*a大于*b,表达式就等于1,否则就表达式不成立,也就是布尔值为0,恰恰表示*a等于*b */
    return *a < *b ? -1 : *a > *b;
}

/* 从左到右查找字符串str中首次出现字符ch的地址(不是下标,是地址) */
char* strchr(const char* str, const uint8_t ch) {
    while (*str != 0) {
        if (*str == ch) {
            return (char*)str;	    // 需要强制转化成和返回值类型一样,否则编译器会报const属性丢失,下同.
        }
        str++;
    }
    return NULL;
}

/* 从后往前查找字符串str中首次出现字符ch的地址(不是下标,是地址) */
char* strrchr(const char* str, const uint8_t ch) {
    const char* last_char = NULL;
    /* 从头到尾遍历一次,若存在ch字符,last_char总是该字符最后一次出现在串中的地址(不是下标,是地址)*/
    while (*str != 0) {
        if (*str == ch) {
            last_char = str;
        }
        str++;
    }
    return (char*)last_char;
}

/* 将字符串src_拼接到dst_后,将回拼接的串地址 */
char* strcat(char* dst_, const char* src_) {
    char* str = dst_;
    while (*str++);
    --str;      // 别看错了，--str是独立的一句，并不是while的循环体
    while((*str++ = *src_++));	 // 当*str被赋值为0时,此时表达式不成立,正好添加了字符串结尾的0.
    return dst_;
}

/* 在字符串str中查找指定字符ch出现的次数 */
uint32_t strchrs(const char* str, uint8_t ch) {
    uint32_t ch_cnt = 0;
    const char* p = str;
    while(*p != 0) {
        if (*p == ch) {
            ch_cnt++;
        }
        p++;
    }
    return ch_cnt;
}

void int_to_str(int num, char *buffer) {
    int i = 0;
    int is_negative = 0;

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    do {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    } while (num > 0);

    if (is_negative) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0';

    for (int j = 0; j < i / 2; ++j) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
}

void uint_to_str(unsigned int num, char *buffer) {
    int i = 0;

    do {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    } while (num > 0);

    buffer[i] = '\0';

    for (int j = 0; j < i / 2; ++j) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
}

void hex_to_str(unsigned int num, char *buffer) {
    const char *digits = "0123456789abcdef";
    int i = 0;

    do {
        buffer[i++] = digits[num % 16];
        num /= 16;
    } while (num > 0);

    buffer[i] = '\0';

    for (int j = 0; j < i / 2; ++j) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
}

void ptr_to_str(void* ptr, char* buffer) {
    unsigned long addr = (unsigned long)ptr;
    hex_to_str(addr, buffer);
}

/*

// 因为arm的gcc又发疯了，非要用库函数操作double类型数据
// 没办法只能用定点数代替浮点数，它爱发疯就发疯吧，不奉陪
// 这个版本是GPT 4o写的替代版
void double_to_str_int(int int_part, int frac_part, char* buffer, int precision) {
    if (precision < 0) {
        precision = 6;
    }

    // 把整数部分转换为字符串
    int_to_str(int_part, buffer);
    while (*buffer) buffer++;

    *buffer++ = '.';

    // 将小数部分按精度进行处理
    for (int i = 0; i < precision; ++i) {
        frac_part *= 10;
    }

    // 把小数部分转换为字符串
    char frac_buffer[20];
    int_to_str(frac_part, frac_buffer);

    // 补齐前导零
    int frac_length = strlen(frac_buffer);
    for (int i = 0; i < precision - frac_length; ++i) {
        *buffer++ = '0';
    }

    // 将小数部分拷贝到 buffer
    strcpy(buffer, frac_buffer);
}

// 包装函数
// 经过测试，只要是double一律调库，double任何运算全部调库，受不了了，弃用
void double_to_str(double num, char* buffer, int precision) {
    // 处理负数
    if (num < 0) {
        *buffer++ = '-';
        num = -num;
    }

    // 提取整数部分和小数部分
    int int_part = (int)num;
    int frac_part = (int)((num - int_part) * 1000000); // 使用 10^6 来保留小数部分

    // 调用整数处理的函数
    double_to_str_int(int_part, frac_part, buffer, precision);
}

*/

int sprintf(char* buffer, const char* format, ...) {
    const char* p = format;
    int* arg = (int*)(void*)(&format + 1);
    char* buf_ptr = buffer;
    char temp_buffer[32];

    while (*p) {
        if (*p == '%' && *(p + 1) != '\0') {
            p++;
            int width = 0;
            int precision = -1;

            while (*p >= '0' && *p <= '9') {
                width = width * 10 + (*p - '0');
                p++;
            }

            if (*p == '.') {
                p++;
                precision = 0;
                while (*p >= '0' && *p <= '9') {
                    precision = precision * 10 + (*p - '0');
                    p++;
                }
            }

            switch (*p) {
                case 'd':
                    int_to_str(*arg++, temp_buffer);
                    break;
                case 'u':
                    uint_to_str(*arg++, temp_buffer);
                    break;
                case 'x':
                    hex_to_str(*arg++, temp_buffer);
                    break;
                case 'c':
                    *temp_buffer = (char)*arg++;
                    temp_buffer[1] = '\0';
                    break;
                case 's': {
                    char* str = (char*)*arg++;
                    while (*str) {
                        *buf_ptr++ = *str++;
                    }
                    continue;
                }
                case 'p':
                    ptr_to_str((void*)*arg++, temp_buffer);
                    break;
//                case 'f':         // 原因我也在上面说了，实在不行
//                    double_to_str(*(double*)arg++, temp_buffer, precision);
//                    break;
                default:
                    *buf_ptr++ = '%';
                    *buf_ptr++ = *p;
                    continue;
            }

            char* temp_ptr = temp_buffer;
            while (*temp_ptr) {
                *buf_ptr++ = *temp_ptr++;
            }
        } else {
            *buf_ptr++ = *p;
        }
        p++;
    }
    *buf_ptr = '\0';
    return buf_ptr - buffer;
}
