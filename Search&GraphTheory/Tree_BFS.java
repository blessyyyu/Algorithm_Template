package Tree;

import java.util.LinkedList;
import java.util.Queue;

/**
 * @author Yu Shaoqing
 * @date 2021/4/28/22:54
 */
public class BFS {
    Queue<TreeNode> que = new LinkedList<TreeNode>();

    public void Bfs(TreeNode root)
    {
        if(root == null)    return;
        que.offer(root);
        while( !que.isEmpty() )
        {
            TreeNode curNode = que.poll();
//            访问curNode
            if(curNode.left!= null)
                que.offer(curNode.left);
            if(curNode.right!= null)
                que.offer(curNode.right);
        }
        return;
    }
}
