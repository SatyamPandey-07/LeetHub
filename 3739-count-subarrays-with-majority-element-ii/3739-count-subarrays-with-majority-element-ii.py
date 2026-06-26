class Solution:
    def countMajoritySubarrays(self, nums: List[int], target: int) -> int:
        prf,cnt = [*accumulate([(num==target)*2 -1 for num in nums], initial=0)], SortedList()
        return  sum(cnt.add(p) or cnt.bisect_left(p) for p in prf)
        