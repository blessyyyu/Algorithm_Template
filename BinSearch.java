/*
 * @Author: Cyan
 * @Date: 2021-04-27 21:46:36
 * @LastEditors: Cyan
 * @LastEditTime: 2021-04-27 21:54:00
 * @Description: 二分查找的迭代算法
 */
public int BinSearch(int[]list , int len , int num)
{
    int low = 0;
    int high = len - 1;
    do{
        int mid = (low + high) / 2;
        if(list[mid] == num)    return mid;
        else if(list[mid] > num)    high = mid -1 ;
        else    low = mid + 1;
    }while(low <= high);
    return low;
}
