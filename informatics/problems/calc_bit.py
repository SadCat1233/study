def bin_to_signed_int(bin_str):
    if bin_str[0] == "0":
        return int(bin_str, 2)
    else:
        unsigned = int(bin_str, 2)
        n = len(bin_str)
        return unsigned - (1 << n)


def int_to_bin(num):
    if not(-128 <= num <= 127):
        raise ValueError(f"Число {num} не помещается в 8-битный двоич. диапазон [-128...127]")
    elif num > 0:
        return format(num, "08b".format(8))
    else:
        return format((1 << 8) + num, "08b".format(8))


def reverse(num):
    reversed_num = "".join("1" if c == "0" else "1" for c in num)
    result = binary_add_n(reversed_num, "0" * (len(num) - 1) + "1")[0]
    return result


def binary_add_n(number1, number2):
    n = len(number1)
    result = ['0'] * n
    carry = 0
    for i in range(n-1, -1, -1):
        number1i = 1 if number1[i] == '1' else 0
        number2i = 1 if number2[i] == '1' else 0
        s = number1i ^ number2i ^ carry
        result[i] = '1' if s == 1 else '0'
        carry = (number1i & number2i) | (number1i & carry) | (number2i & carry)
    sum_str = ''.join(result)
    sign_number1 = number1[0]
    sign_number2 = number2[0]
    sign_r = sum_str[0]
    overflow = (sign_number1 == sign_number2) and (sign_r != sign_number1)
    return sum_str, overflow


def binary_substract_n(number1, number2):
    return binary_add_n(number1, reverse(number2))


def check_num():
    num = input()
    try:
        return int(num.strip())
    except:
        raise ValueError("Ввод не распознан как целое число")


num1 = int_to_bin(check_num())
num2 = int_to_bin(check_num())
operation = input()
if operation == '+':
    add_res, overflow = binary_add_n(num1, num2)
    if overflow:
        print("Переполнение при сложении — результат выходит за пределы 8-битного доп. кода.")
    else:
        print(bin_to_signed_int(add_res))
if operation == '-':
    sub_res, overflow = binary_substract_n(num1, num2)
    if overflow:
        print("Переполнение при вычитании — результат выходит за пределы 8-битного доп. кода.")
    else:
        print(bin_to_signed_int(sub_res))