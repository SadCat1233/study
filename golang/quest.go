package main

import (
	"strings"
	"strconv"
)

func getConcatenation(nums []int) []int {
	nums = append(nums, nums...)
	return nums
}

func shuffle(nums []int, n int) []int {
	result := make([]int, 0, n*2)
	for i := 0; i < n; i++ {
		result = append(result, nums[i], nums[i+n])
	}
	return result
}

func findMaxConsecutiveOnes(nums []int) int {
	counter := 0
	ans := 0
	for i := 0; i < len(nums); i++ {
		if nums[i] == 1 {
			counter += 1
			ans = max(ans, counter)
		} else {
			counter = 0
		}
	}
	return ans
}

func findErrorNums(nums []int) []int {
	n := len(nums)
	dublicate := 0
	missing := 0
	temp := make([]int, n+1)
	for i := 0; i < n; i++ {
		temp[nums[i]]++
	}
	for i := 1; i < n+1; i++ {
		if temp[i] == 2 {
			dublicate = i
		}
		if temp[i] == 0 {
			missing = i
		}
	}
	return []int{dublicate, missing}
}

func smallerNumbersThanCurrent(nums []int) []int {
	n := len(nums)
	tempArray := make([]int, 101)
	result := make([]int, n)
	for i := 0; i < n; i++ {
		tempArray[nums[i]]++
	}
	for i := 1; i < 101; i++ {
		tempArray[i] += tempArray[i-1]
	}
	for i := 0; i < n; i++ {
		if nums[i] == 0 {
			result[i] = 0
		} else {
			result[i] = tempArray[nums[i]-1]
		}
	}
	return result
}

func findDisappearedNumbers(nums []int) []int {
	n := len(nums)
	tempArray := make([]int, n+1)
	result := make([]int, 0)
	for i := 0; i < n; i++ {
		tempArray[nums[i]]++
	}
	for i := 1; i < n+1; i++ {
		if tempArray[i] == 0 {
			result = append(result, i)
		}
	}
	return result
}

func evalRPN(tokens []string) int {
	n := len(tokens)
	tempArray := make([]string, 0, n)
	for i := 0; i < n; i++ {
		switch tokens[i] {
		case "+":
			second, _ := strconv.Atoi(tempArray[len(tempArray) - 1])
			first, _ := strconv.Atoi(tempArray[len(tempArray) - 2])
			tempArray[len(tempArray) - 2] = strconv.Itoa(first + second)
			tempArray = tempArray[:len(tempArray) - 1]
		case "-":
			second, _ := strconv.Atoi(tempArray[len(tempArray) - 1])
			first, _ := strconv.Atoi(tempArray[len(tempArray) - 2])
			tempArray[len(tempArray) - 2] = strconv.Itoa(first - second)	
			tempArray = tempArray[:len(tempArray) - 1]		
		case "*":
			second, _ := strconv.Atoi(tempArray[len(tempArray) - 1])
			first, _ := strconv.Atoi(tempArray[len(tempArray) - 2])
			tempArray[len(tempArray) - 2] = strconv.Itoa(first * second)
			tempArray = tempArray[:len(tempArray) - 1]		
		case "/":
			second, _ := strconv.Atoi(tempArray[len(tempArray) - 1])
			first, _ := strconv.Atoi(tempArray[len(tempArray) - 2])
			tempArray[len(tempArray) - 2] = strconv.Itoa(first / second)
			tempArray = tempArray[:len(tempArray) - 1]
		default:
			tempArray = append(tempArray, tokens[i])
		}
	}
	answer, _ := strconv.Atoi(tempArray[0])
	return answer
}

func exclusiveTime(n int, logs []string) []int {
	stack := make([]int, 0, n)
    currProcess := strings.Split(logs[0], ":")
	id, _ := strconv.Atoi(currProcess[0])
	stack = append(stack, id)
	result := make([]int, n)
	previousTime, _ := strconv.Atoi(currProcess[2])
	for i := 1; i < len(logs); i++ {
		currProcess = strings.Split(logs[i], ":")
		currTime, _ := strconv.Atoi(currProcess[2])
		id, _ = strconv.Atoi(currProcess[0])
		if currProcess[1] == "start" {
			if len(stack) != 0 {
				result[stack[len(stack) - 1]] += currTime - previousTime
			}
			stack = append(stack, id)
			previousTime = currTime
		} else {
			result[stack[len(stack) - 1]] +=  currTime - previousTime + 1
			stack = stack[:len(stack) - 1]
			previousTime = currTime + 1
		}
	}
	return result
}

func finalPrices(prices []int) []int {
	n := len(prices)
	stack := make([]int, 0, n)
	for i := 0; i < n; i++ {
		for (len(stack) != 0 && (prices[stack[(len(stack) - 1)]] >= prices[i])) {
			prices[stack[len(stack) - 1]] -= prices[i]
			stack = stack[:len(stack) - 1]
		}
		stack = append(stack, i)
	}
	return prices
}

func dailyTemperatures(temperatures []int) []int {
	n := len(temperatures)
    stack := make([]int, 0, n)
	answer := make([]int, n)
    for i := 0; i < n; i++ {
		for (len(stack) != 0 && (temperatures[stack[len(stack) - 1]] < temperatures[i])) {
			answer[stack[len(stack) - 1]] = i - stack[len(stack) - 1]
			stack = stack[:len(stack) - 1]
		}
        stack = append(stack, i)
    }
	return answer
}

func largestRectangleArea(heights []int) []int {
	n := len(heights)
    stack := make([]int, 0, n)
	answer := make([]int, n)
    for i := 0; i < n; i++ {
		for (len(stack) != 0 && (heights[stack[len(stack) - 1]] < heights[i])) {
			answer[stack[len(stack) - 1]] = i - stack[len(stack) - 1]
			stack = stack[:len(stack) - 1]
		}
        stack = append(stack, i)
    }
	return answer
}