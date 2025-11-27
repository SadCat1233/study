def bytes_to_uint(bts, endianness="Little"):
    val = 0
    if endianness == "Little":
        for i, byte in enumerate(bts):
            val |= (byte & 0xFF) << (8 * i)
    else:
        for byte in bts:
            val = (val << 8) | (byte & 0xFF)
    return val

def bytes_to_signed(bts, endianness="Little", bits=None):
    if bits is None:
        bits = 8 * len(bts)
    u = bytes_to_uint(bts, endianness)
    sign_bit = 1 << (bits - 1)
    return u - (1 << bits) if (u & sign_bit) else u

def bytes_to_float32(bts, endianness="Little"):
    u = bytes_to_uint(bts, endianness)
    sign = (u >> 31) & 1
    exp = (u >> 23) & 0xFF
    mant = u & 0x7FFFFF
    if exp == 255:
        if mant == 0:
            return float("inf") if sign==0 else float("-inf")
        else:
            return float("nan")
    elif exp == 0:
        val = (mant) / (2 ** 23) * (2 ** (1-127))
    else:
        val = (1 + mant / (2 ** 23)) * (2 ** (exp - 127))
    return -val if sign else val


def errors_parse(error, packet_id):
    print(f"Packet {packet_id}: {error}")
    return 0

filename = input()
path = f"/Users/a1/Downloads/Тесты для 2 задачи/{filename}"
if path[-3:] == "bin":
    file = open(path, "rb")
    data = bytearray(file.read())
else:
    file = open(path, "r", encoding='utf-8')
    data = bytes.fromhex(file.read())
byte_list = []
for i, byte in enumerate(data):
    byte_list.append(hex(byte)[2:].zfill(2))
packet_count = 0
sensor_types_list = ["", "uint16", "int16", "uint32", "int32", "float32"]
byte_list = list(filter(None, "".join(byte_list).split("aa")))

for packet in byte_list:
    packet_count += 1
    if packet[:2] != packet[-2:]:
        errors_parse("truncated_packet", packet_count)
        continue

    byte_packet_list = [packet[byte:byte+2] for byte in range(2, len(packet) - 2, 2)]
    flag = True if byte_packet_list[0] == "01" else False
    sensor_count = byte_packet_list[1]
    checksum = bytes.fromhex("".join(byte_packet_list)[-2:])

    byte_body = b""
    for i in range(0, len("".join(byte_packet_list)) - 3, 2):
        byte_body += bytes.fromhex("".join(byte_packet_list)[i:i+2])
    byte_packet_list = byte_packet_list[2:]

    if len(byte_packet_list) < 7:
        errors_parse("truncated_packet", packet_count)
        continue

    temp = 0
    sensors_info = []
    while temp < (len(byte_packet_list) - 1):
        sensor_id = byte_packet_list[temp]
        sensor_type_byte = temp + 1
        value = ""
        if byte_packet_list[temp + 1] in ["01", "02"]:
            try:
                value = byte_packet_list[temp + 2:temp + 4]
                temp += 4
            except IndexError:
                errors_parse("truncated_packet", packet_count)
                break
        elif byte_packet_list[temp + 1] in ["03", "04", "05"]:
            try:
                value = byte_packet_list[temp + 2:temp + 6]
                temp += 6
            except IndexError:
                errors_parse("truncated_packet", packet_count)
                break
        else:
            errors_parse("unknown_sensor_type", packet_count)
            break
        value = "".join(value)
        sensor_type = sensor_types_list[int(byte_packet_list[sensor_type_byte], 16)]
        sensors_info.append([sensor_id, sensor_type, value])

    calc_checksum = bytes.fromhex(hex(sum(byte_body) & 0xFF)[2:])
    if calc_checksum != checksum:
        print(f"Packet {packet_count}: checksum error")
        break

    print(f"Packet {packet_count}: Endianness={'Big' if flag else 'Little'}")
    for sensor in sensors_info:
        byte_value = b""
        for i in range(0, len(sensor[2]) - 1, 2):
            byte_value += bytes.fromhex(sensor[2][i:i+2])
        if "uint" in sensor[1]:
            sensor[2] = bytes_to_uint(byte_value, "Big" if flag else "Little")
        elif "int" in sensor[1]:
            sensor[2] = bytes_to_signed(byte_value, "Big" if flag else "Little")
        else:
            sensor[2] = bytes_to_float32(byte_value, "Big" if flag else "Little")
        print(f"Sensor ID={int(sensor[0], 16)} Type={sensor[1]} Value={sensor[2]}")