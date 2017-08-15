/*
 * dynimic data of fixed size element
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
const int nSuccess = 0;
const int nFailure = -1;

typedef struct {
    char *data;
    size_t used;
    size_t capacity;
    size_t elem_size;
} DynamicArray;

int  initDynamicArray(DynamicArray *a, size_t initialSize,int elem_size) {
    int nRet = nFailure;
    do
    {
        if (NULL == a)
        {
            break;
        }
        a->elem_size = elem_size;
        a->data = (char *)malloc(initialSize * a->elem_size);
        if(NULL == a->data)
        {
            break;
        }
        a->used = 0;
        a->capacity = initialSize;
        nRet = nSuccess;
    } while(0);
    return nRet;
}

int insertDynamicArray(DynamicArray *a, void* element) {
    int nRet = nFailure;
    do
    {
        if (NULL == a)
        {
            break;
        }
        if (a->used == a->capacity)
        {
            a->capacity*= 2;
            a->data = (char *)realloc(a->data, a->capacity * a->elem_size);
            if (a->data == NULL )
            {
                printf("realloc failed\n");
                break;
            }
        }
        memcpy( a->data + a->used*a->elem_size, element,a->elem_size);
        a->used =a->used+1;
        nRet = nSuccess;
    } while(0);
    return nRet;
}

int  getDynamicArray(DynamicArray *a,void *elem, int index) {
    int nRet = nFailure;
    do
    {
        if ( index >= a->used )
        {
            break;
        }
        memcpy( elem, a->data + (index * a->elem_size), a->elem_size);
        nRet = nSuccess;
    } while(0);
    return nRet;
}
void freeDynamicArray(DynamicArray *a) {
    if (a->data)
    {
        free(a->data);
    }
    a->data = NULL;
    a->used = a->capacity= 0;
}
int main(char* argv, int argc)
{
    DynamicArray a;
    int i;

    initDynamicArray(&a, 1,sizeof(int));

    int nMax = 15;
    for (i = 0; i < nMax; i++)
    {
        int *el = &i;
        insertDynamicArray(&a, el);
    }
    for (i = nMax; i>=0; --i)
    {
        int el =0;
        if (nSuccess == getDynamicArray(&a, &el,i))
        {
            printf("%d\n", el);
        }
    }
    freeDynamicArray(&a);
    return 0;
}
