package Tree;

import java.util.Deque;
import java.util.LinkedList;

/**
 * @author Yu Shaoqing
 * @date 2021/5/10/10:54
 */
public class LevelOfTree {
    public int levelofTree(TreeNode root,int key)
    {
        Deque<TreeNode> stack1 = new LinkedList<>();
        Deque<Integer> stack2 = new LinkedList<>();
        TreeNode p =root;
        int curlevel = 1;
        while(!stack1.isEmpty() || p!=null)
        {
            while(p!=null)
            {
                if(p.val == key)
                    return curlevel;
                stack1.push(p);
                stack2.push(curlevel);
                p = p.left;
                curlevel++;
            }
            p = stack1.pop();
            curlevel = stack2.pop();
            p = p.right;
            curlevel++;
        }
        return curlevel;
    }

}
