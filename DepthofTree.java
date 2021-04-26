/**
 * @author Yu Shaoqing
 * @date 2021/4/26/21:15
 */
public class DepthofTree {
    public int Depth(TreeNode root)
    {
        if(root != null)
        {
            int leftdepth,rightdepth;
            leftdepth = Depth(root.left);
            rightdepth = Depth(root.right);
            return Math.max(leftdepth,rightdepth) + 1;
        }
        else
        {
            return 0;
        }
    }

}
