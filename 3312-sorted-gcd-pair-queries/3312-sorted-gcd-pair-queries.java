class Solution {
    public int[] gcdValues(int[] nums, long[] queries) {
        int mx = Arrays.stream(nums).max().getAsInt();
        int[] freq = new int[mx + 1];
        for (int v : nums)
            ++freq[v];

        long[] g = new long[mx + 1];
        for (int d = mx; d > 0; --d) {
            long m = 0;
            for (int k = d; k <= mx; k += d) {
                m += freq[k];
                g[d] -= g[k];          
            }
            g[d] += m * (m - 1) / 2;    
        }

        long[] s = g.clone();         
        Arrays.parallelPrefix(s, Long::sum);

        return Arrays.stream(queries).mapToInt(q -> upperBound(s, q)).toArray();
    }

    private int upperBound(long[] s, long q) {
        int lo = 0, hi = s.length;
        while (lo < hi) {
            int mid = (lo + hi) >>> 1;
            if (s[mid] > q) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
}