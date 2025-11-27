def convert(lst):
    result = b""
    for byte in lst:
        result += byte
    return result


for number in range(1, 11):
    print("------------------------------------------------")
    filename = f"/Users/a1/Downloads/Тесты для 3 задачи/{number}.bin"
    file = open(filename, "rb")
    data = file.read()
    byte_list = []
    for byte in data:
        byte_list.append(bytes.fromhex(hex(byte)[2:].zfill(2)))

    title = byte_list[:8]
    byte_list = byte_list[8:]
    signature = title[:4]
    length = convert(title[4:])
    length = int.from_bytes(length, byteorder='little', signed=False)
    if length != len(byte_list[:-4]):
        print("Неверная длина полезной нагрузки")
        continue
    print("Number", number)
    ind = 0
    records_count = 0
    while ind < len(byte_list) - 5:
        records_count += 1
        flag = byte_list[0]
        flag = ''.join(f"{byte:08b}" for byte in flag)
        endianess = "big" if flag[0] == '0' else "little"
        uint32_type = True if flag[1] == '1' else False
        is_valid = True if flag[-1] == '0' else False
        print(flag)
        if not is_valid:
            print(f"Запись {records_count} ошибочна")
            ind += 5
            continue

        num = convert(byte_list[ind + 1:ind + 5])
        num = int.from_bytes(num, byteorder=endianess, signed=uint32_type)
        print(num)
        ind += 5
    calc_checksum = convert(byte_list[:-4])
    calc_checksum = sum(calc_checksum)
    checksum = convert(byte_list[-4:])
    print(calc_checksum, "checksum", sum(checksum))

