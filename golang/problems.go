package main


func isValid(s string) bool {
	n := len(s)
	stack := make([]string, 0, n)
	mapping := map[string]string{
		")": "(",
		"]": "[",
		"}": "{",
	}
	for i := 0; i < n; i++ {
		if _, exist := mapping[string(s[i])]; exist {
			if len(stack) != 0 {
				if stack[len(stack)-1] == mapping[string(s[i])] {
					stack = stack[:len(stack)-1]
				} else {
					return false
				}
			} else {
				return false
			}
		} else {
			stack = append(stack, string(s[i]))
		}
	}
	if len(stack) != 0 {
		return false
	}
	return true
}

func removeDuplicates(nums []int) int {
	i := 1
	for j := 1; j < len(nums); j++ {
		if nums[j] != nums[i - 1] {
            nums[i] = nums[j]
            i++
        }
	}
	return i
}

func removeElement(nums []int, val int) int {
	i := 0
	for j := 0; j < len(nums); j++ {
		if nums[j] != val {
            nums[i] = nums[j]
            i++
        }
	}
	return i
	//[0,1,2,2,3,0,4,2]
}

