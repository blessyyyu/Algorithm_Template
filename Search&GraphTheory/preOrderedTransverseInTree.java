package Tree;

import java.util.Deque;
import java.util.LinkedList;

/**
 * @author Yu Shaoqing
 * @date 2021/4/29/14:32
 */
public class DFS {
    public void Dfs_recur(TreeNode root)
    {
        if(root!=null)
        {
            //访问root结点;
            visit(root);
            Dfs_recur(root.left);
            Dfs_recur(root.right);
        }
    }

    public void Dfs_stack(TreeNode root)
    {
//        创建一个栈便于之后回退访问
        Deque<TreeNode> stack = new LinkedList<TreeNode>();
//        创建一个遍历结点
        TreeNode curNode = root;
        while( curNode != null || !stack.isEmpty() )
        {
            while(curNode!=null)
            {
                visit(curNode);
                stack.push(curNode);
                curNode = curNode.left;
            }
            curNode = stack.pop();
            curNode = curNode.right;
        }
    }
    public void visit(TreeNode n)
    {
        System.out.println("visit node " + n.val);
    }


}
