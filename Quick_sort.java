import java.util.*;
import java.io.*;
public class Main{
    public static  void quick_sort(int[] arr, int l, int r){
        if(l >= r)  return;
        // 快速排序非常重要的一步就是选取标杆值
        // 这里不能写成 int x = l + r >> 1;
        // 因为代码中，这个x所在的下标可能正好和别人交换了
        // 所以保留的应该是标杆的值，而不是标杆的下标
        int x = arr[ (l + r) / 2];
        int i = l - 1;
        int j = r + 1;
        while(i < j){
            do i++; while(arr[i] < x);
            do j--; while(arr[j] > x);
            if( i < j){
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }
        quick_sort(arr, l , j);
        quick_sort(arr, j+1 , r);
    }
    public static void main(String[] args) throws IOException{
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        String[] arrstr = in.readLine().split(" ");
        int[] arr = new int[n];
        for(int i =0; i< n; i++){
            arr[i] = Integer.parseInt(arrstr[i]);
        }
        quick_sort(arr,0,n-1);
        for(int i=0;i<n;i++)    System.out.print(arr[i] + " ");
        in.close();
    }
}