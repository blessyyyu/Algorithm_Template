package SortAlgorithm;

/**
 * @author Yu Shaoqing
 * @date 2021/6/1/22:04
 */
public class MergeSORT {
    public void DivedeInterval(int[] nums,int left,int right){
//        每次2等分，划分区间
        if(left < right){
            int mid = (left + right) / 2;
            DivedeInterval(nums,left,mid);
            DivedeInterval(nums,mid+1,right);
            Merge(nums,left,mid,mid+1,right);
        }
    }
    public void Merge(int[] nums, int l1, int r1, int l2, int r2){
        int i = l1, j = l2;
        System.out.println(nums.length);
        int[] temp = new int[r2 - l1 +1];
        int index = 0;
//        双指针法合并有序数组
        while(i <= r1 && j <= r2){
            if(nums[i] <= nums[j]){
                temp[index++] = nums[i++];
            }else{
                temp[index++] = nums[j++];
            }
        }
        while(i <= r1)  temp[index++] = nums[i++];
        while(j <= r2)  temp[index++] = nums[j++];
        for(int k = 0; k< index; k++)
            nums[l1 + k] = temp[k];
    }
}
