#pragma once
#ifndef NDEBUG
#define DbgOut(x) printf("%s:%d: x\n", __FILE__, __LINE__)
#define DbgWait(x)                                    \
    {                                                 \
        char c_X_j;                                   \
        printf("%s:%d: Weiter?", __FILE__, __LINE__); \
        scanf("%c", &c_X_j);                          \
    }
#define DbgsOut(x) printf("%s:%d: x >%s<\n", __FILE__, __LINE__, x)
#define DbgpOut(x) printf("%s:%d: x=%p\n", __FILE__, __LINE__, x)
#define DbgiOut(i) printf("%s:%d: i=%d\n", __FILE__, __LINE__, i)
#define DbglOut(i) printf("%s:%d: i=%ld\n", __FILE__, __LINE__, i)
#define DbgfOut(x) printf("%s:%d: x=%f\n", __FILE__, __LINE__, x)
#define DbgStart() printf("%s:%d: Anfang\n", __FILE__, __LINE__)
#define DbgStop() printf("%s:%d: Ende\n", __FILE__, __LINE__)
#define DbgRecOut(rec) printf("%s:%d: rec={{%d,%d}{%d,%d}}\n", __FILE__, __LINE__, rec.ll.x, rec.ll.y, rec.ur.x, rec.ur.y)
#endif