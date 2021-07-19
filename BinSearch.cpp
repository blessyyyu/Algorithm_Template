//  整数二分
//  两个模板，注意计算mid时是否+1
int bsearch_1(int l, int r)
{
    while (l < r)
    {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    return l;
}

int bsearch_2(int l, int r)
{
    while (l < r)
    {
        int mid = l + r + 1 >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}

// 浮点数二分，注意右边界的值，如果题目是二分取平方根，0.01的平方根是0.1，反而比原来的值要大
// 所以应该右边界取为max(1,x),至于输出的内容，如果要求保留小数点后的位数，若保留6位小数，一般r - l > 1e-8;多2是比较保险的做法
double bsearch_3(double l, double r){
    while( r - l > 1e-8){
        double mid = (r + l) / 2;
        if(check(mid))  r = mid;
        else    l = mid;
    }
    return l;
}