def isPalindrome(s: str) -> bool:
	return s == s[::-1]

def validPalindrome_2(s: str) -> bool:
	l = len(s)
	if l < 2:
		return True
	low, high = 0, l-1
	while low < high:
		if s[low] == s[high]:
			low += 1
			high -= 1
		else:
			# mismatch detected

			# delete low and check
			if isPalindrome(s[low+1:high+1]):
				return True
			elif isPalindrome(s[low:high]):
				return True
			else:
				return False
	return True
