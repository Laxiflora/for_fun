


def valid(inp, len):
    for i in range(len-1):
        inp = inp//10000
    return inp<10000

def changeCapital(a = 0):
    unit = ['', '萬', '億', '兆']
    numbers = []
    chinese_map = ['零', '壹', '貳', '參', '肆', '伍', '陸', '柒', '捌', '玖']
    units_in_unit = ['', '拾', '佰', '仟']
    try:
        t = int(a)
        if(not valid(t, len(unit))):
            raise
    except:
        print("格式錯誤或輸入數值過大")
        exit(0)
    if t<0:
        print("格式錯誤")
        exit(0)
    while len(a)>4:
        numbers.append(a[-4:])
        a = a[:-4]
    numbers.append(a)
    numbers.reverse()
    data = []
    for unit_index, i in enumerate(numbers, 0):
        i = [x for x in i]
        final_unit = []
        zero = False
        i.reverse()
        for index, j in enumerate(i, 0):
            string = ""
            j = int(j)
            if(j == 0):
                zero = True
                continue
            if zero and len(final_unit)>0:
                final_unit[-1] = "零"+final_unit[-1]
            zero = False
            string = string + chinese_map[j] + units_in_unit[index]
            final_unit.append(string)
        final_unit.reverse()
        final_unit = ''.join(final_unit)
        data.append(final_unit)
    data.reverse()
    final_data = []
    for index, i in enumerate(data, 0):
        final_data.append(i+unit[index])

    final_data.reverse()

    return "".join(final_data)+"元整"


if __name__ == "__main__":
    print("輸入要轉換成中文表示的金額:")
    _in = input()
    print(changeCapital(_in))