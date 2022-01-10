#define MAX_ELEMENTS 100
typedef int ElementType;
typedef struct
{
    ElementType data[MAX_ELEMENTS];
    int size;
} List;

/* Tạo danh sach rỗng */
void make_null(List *L)
{
    L->size = 0;
}

/* Thêm một phần tử vào cuối danh sách */
void push_back(List *L, ElementType x)
{
    L->data[L->size] = x;
    L->size++;
}

/* Lấy phần tử tại vị trí i, vị trí tính từ 1 */
ElementType element_at(List *L, int i)
{
    return L->data[i - 1];
}

/* Trả về số phần tử của danh sách */
int count_list(List *L)
{
    return L->size;
}