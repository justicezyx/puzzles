def merge_list(nums1, nums2):
    """
    :type nums1: List[int]
    :type m: int
    :type nums2: List[int]
    :type n: int
    :rtype: None Do not return anything, modify nums1 in-place instead.
    """
    if len(nums1) == 0:
        return nums2
    if len(nums2) == 0:
        return nums1

    m = len(nums1)
    n = len(nums2)

    res = [0] * (m+n)
    end_idx = m+n-1
    while n > 0 and m > 0 :
        if nums2[n-1] >= nums1[m-1]:
            res[end_idx] = nums2[n-1]
            n-=1
        else:
            res[end_idx] = nums1[m-1]
            m-=1
        end_idx-=1
    while n > 0:
        res[end_idx] = nums2[n-1]
        n-=1
        end_idx-=1
    while m > 0:
        res[end_idx] = nums1[m-1]
        m-=1
        end_idx-=1
    return res
