from string import ascii_uppercase


def comparison(number1, number2):
    number1, number2 = non_zeros(number1), non_zeros(number2)
    if len(number1) != len(number2):
        return len(number1) - len(number2)
    for x, y in zip(number1, number2):
        if x != y:
            return x - y
    return 0

def multiply_table(base):
    table = [[0] * base for _ in range(base)]
    for i in range(base):
        for j in range(base):
            table[i][j] = i * j
    return table


def non_zeros(num_with_zeros):
    num_no_zeros = []
    found_non_zero = False
    for elem in num_with_zeros:
        if elem != 0:
            found_non_zero = True
        if found_non_zero:
            num_no_zeros.append(elem)
    return num_no_zeros


def zeros(number1, number2):
    if len(number1) < len(number2):
        number1 = [0] * (len(number2) - len(number1)) + number1
    else:
        number2 = [0] * (len(number1) - len(number2)) + number2
    return [number1, number2]


def plus(number1, number2, res):
    number1, number2 = zeros(number1, number2)
    for i in range(1, len(number1) + 1):
        res[-i] += (number1[-i] + number2[-i]) % system
        if number1[-i] + number2[-i] >= system:
            res[-i - 1] = res[-i - 1] + 1
    return non_zeros(res)


def minus(number1, number2, res):
    number1, number2 = zeros(number1, number2)
    for i in range(1, len(number1) + 1):
        res[-i] = number1[-i] - number2[-i]
        if number1[-i] - number2[-i] < 0:
            if i != len(number1):
                res[-i] = int(system + number1[-i] - number2[-i])
                number1[-i - 1] = number1[-i - 1] - 1
            else:
                res[-i] = abs(number1[-i] - number2[-i])
                res[-i - 1] = 36
    return non_zeros(res) if comparison(number1, number2) > 0 else [36] + non_zeros(res)

    
def multiply(number1, number2, res):
    number1 = number1[::-1]
    number2 = number2[::-1]
    table = multiply_table(system)
    res = [0] * (len(number1) + len(number2))
    for i in range(len(number1)):
        for j in range(len(number2)):
            p = table[int(number1[i])][int(number2[j])]
            res[i + j] += p
            res[i + j + 1] += res[i + j] // system
            res[i + j] %= system
    
    while len(res) > 1 and res[-1] == 0:
        res.pop()

    return non_zeros(res[::-1])


def division(number1, number2):
    if number2 == [0]:
        raise ZeroDivisionError
    number1, number2 = non_zeros(number1), non_zeros(number2)
    if comparison(number1, number2) < 0:
        return [0], number1
    r = []
    undivided = []
    for i in number1:
        r.append(i)
        r = non_zeros(r)
        t = 0
        for j in range(system):
            temp = multiply(number2, [j], [0])
            if comparison(temp, r) <= 0:
                t = j
            else:
                break
        undivided.append(t)
        if t != 0:
            r = minus(r, multiply(number2, [t], [0]), [0] * max(len(r), len(number2)))
    return undivided, r[1:]


system = int(input('Enter system '))
nums = '0123456789' + ascii_uppercase + '-'

try:
    num1 = [nums.index(i) for i in input('num1 ')]
    int("".join([str(i) for i in num1]), system)
except ValueError:
    print("Ошибка, введите число повторно")
    num1 = [nums.index(i) for i in input('num1 ')]

try:
    num2 = [nums.index(i) for i in input('num2 ')]
    int("".join([str(i) for i in num2]), system)
except TypeError:
    print("Ошибка, введите число повторно")
    num2 = [nums.index(i) for i in input('num2 ')]

operation = input('Введите знак операции ')
result = [0] * (max(len(num1), len(num2)) + 2)

if operation == '-':
    if num1[0] == num2[0] == 36:
        result = minus(num2[1:], num1[1:], result)
    if num1[0] == 36 and num2[0] != 36:
        result = [36] + plus(num1[1:], num2, result)
    if num1[0] != 36 and num2[0] != 36:
        result = minus(num1, num2, result)
    if num1[0] != 36 and num2[0] == 36:
        result = plus(num1, num2[1:], result)
    if result.count(36) > 1:
        result = list(dict.fromkeys(result))

elif operation == '+':
    if num1[0] == num2[0] == 36:
        result = [36] + plus(num1[1:], num2[1:], result)
    if num1[0] == 36 and num2[0] != 36:
        result = minus(num2, num1[1:], result)
    if num1[0] != 36 and num2[0] != 36:
        result = plus(num1, num2, result)
    if num1[0] != 36 and num2[0] == 36:
        result = minus(num1, num2[1:], result)

elif operation == '*':
    if num1[0] != 0 and num2[0] != 0:
        if num1[0] == num2[0] == 36:
            result = multiply(num1[1:], num2[1:], result)
        if num1[0] == 36 and num2[0] != 36:
            result = [36] + multiply(num1[1:], num2, result)
        if num1[0] != 36 and num2[0] != 36:
            result = multiply(num1, num2, result)
        if num1[0] != 36 and num2[0] == 36:
            result = [36] + multiply(num1[1:], num2, result)
    else:
        result = [0]

elif operation == "/":
    if num1[0] == num2[0] == 36:
        result = division(num1, num2)
    if num1[0] == 36 and num2[0] != 36:
        result = [36] + division(num1[1:], num2)
    if num1[0] != 36 and num2[0] != 36:
        result = division(num1, num2)
    if num1[0] != 36 and num2[0] == 36:
        result = [36] + division(num1, num2)

print(result)