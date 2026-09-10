class Solution {
public:
    using u64=unsigned long long;
    int  count=0;
    u64 postOrder(TreeNode* node){
        if (node==NULL) return 0;
        u64 sum_n_L=postOrder(node->left);
        u64 sum_n_R=postOrder(node->right);
        u64 sum_n=node->val+(1LL<<32);
        sum_n+=sum_n_L+sum_n_R;
        count+=((sum_n&0xffffffff)/(sum_n>>32 )==node->val);
   
        return sum_n;
    }

    int averageOfSubtree(TreeNode* root) {
        postOrder(root);
        return count;
    }
};
auto init = []()
{ 
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 'c';
}();