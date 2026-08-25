#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

static char buf[1024];

void putch(char ch);

int printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    
    int val = vsnprintf(buf, 1024, fmt, ap);
    char *tmp = buf;
    while (*tmp != 0) {
        putch(*tmp);
        tmp++;
    }
    va_end(ap);
    
    return val;
}


int vsprintf(char *out, const char *fmt, va_list ap) {
      panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  
  int val = vsnprintf(out, 1024, fmt, ap);
  va_end(ap);

  return val;
}

//out   是指向数组的指针
//n     写入字符串的最大数量
//fmt   格式字符串，%s %d啥的
//ap    包含了要格式化的可变数量的参数。这个列表是通过 va_start 宏初始化的，可以通过 va_arg 宏来访问其中的参数。
int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
    char *start = out;
    while (n-- && *fmt != '\0') {
        if (*fmt == '%') {
            fmt++;
            if (*fmt == 's') {
                char *tmp_s = va_arg(ap, char*);
                while (*tmp_s != '\0') {
                    *out++ = *tmp_s++;
                }
            }
            else if (*fmt == 'd') {
                int tmp_int = va_arg(ap, int);//从可变参量列表ap中获取int类型的参数
                if (tmp_int < 0) {
                    *out++ = '-';
                    tmp_int = -1 * tmp_int;
                }
                int number = tmp_int;
                int len  = 0;
                do {
                    number /= 10; //看这个%d一共有几位
                    len++;
                } while (number);
                out = out + len - 1;//定位输出位置
                int tmp_len = len;  //逐位写入数字字符
                while (tmp_len--) {
                    int tmp = tmp_int % 10;
                    *out-- = tmp + 48; //将数字转换为对应的ASCII字符
                    tmp_int /= 10;  //准备处理下一个字符
                }
                out += (len+1);
            }
            else if (*fmt == '%') {
                *out++ = '%';
            }
            else if (*fmt == 'c') {
                char tmp_char = va_arg(ap, int);
                *out++ = tmp_char;
            }
            else {
                return -1;
            }
        }
        else {
            *out++ = *fmt;
        }
        fmt++;
    }
    *out = '\0';
    return out - start;
}

#endif