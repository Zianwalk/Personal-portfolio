class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int sum ;
        vector<int> ans ;

        
        for ( int i = 1 ; i < nums.size() ; i++ ) {
            sum = nums[0] + nums[i] ;
            if ( sum == target ) {
                ans.push_back( 0 ) ;
                ans.push_back( i ) ;
                break ;
            }
            
            else {
                
                for ( int j = 1 ; j <= i ; j++ ) {
                    sum = nums[i] + nums[i-j] ;
                    if ( sum == target ) {
                        ans.push_back( i - j ) ;
                        ans.push_back( i ) ;
                        return ans ;
                    }
                }
            }
            
        }
        

        return ans;
    }
};
