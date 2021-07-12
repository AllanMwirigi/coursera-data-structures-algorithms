import sys

# incomplete - soln can contain multiple instances of the same digit
def solution(line):
    numDict = {
        'zero': '0', 
        'one': '1', 
        'two': '2',
        'three': '3',
        'four': '4',
        'five': '5',
        'six': '6',
        'seven': '7',
        'eight': '8',
        'nine': '9'
    }
    numList = [
        'zero', 
        'one', 
        'two',
        'three',
        'four',
        'five',
        'six',
        'seven',
        'eight',
        'nine'
    ]
    val = ''
    for i, num in enumerate(numList):
        hasCh = True
        for ch in num:
            if ch not in line:
                hasCh = False
                break
        if hasCh:
            val += numDict[num]

    return val

for line in sys.stdin:
  print(solution(line))
        




