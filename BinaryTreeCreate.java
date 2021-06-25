import java.util.*;
public class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode(int x) { val = x; }
}
//      从数组中构建一个二叉树
class BinaryTreeCreate{
    /**
     *
     * @param list  数组
     * @param index  需要访问的当前结点
     * @return 返回根节点
     */
    public TreeNode CreateBinaryTree(List<Integer>list, int index)
    {
        TreeNode curNode = null;
        if(index < list.size())
        {
            int value = list.get(index);
            curNode = new TreeNode(value);
            curNode.left = CreateBinaryTree(list,2*index+1);
            curNode.right = CreateBinaryTree(list,2*index+2);
            return curNode;
        }
        return curNode;
    }
}