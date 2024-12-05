import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print(f"usage: {sys.argv[0]} csv txt.")
        sys.exit()

    # TODO: Read database file into a variable
    # 读取所有csv字段到rows数组，每一行为数组中的一个字典
    rows = []
    with open(sys.argv[1]) as f:
        reader = csv.DictReader(f)
        for row in reader:
            rows.append(row)

    # TODO: Read DNA sequence file into a variable
    # 读取所有dna长字符信息
    with open(sys.argv[2]) as f:
        dna_seq = f.read()

    # TODO: Find longest match of each STR in DNA sequence
    # 用循环读取csv所有字段，因为不确定到底有几个特征，名字设置临时变量
    strs = {}
    for key in rows[0].keys():
        if key == "name":
            strs[key] = "tmp"
        strs[key] = str(longest_match(dna_seq, key))

    # TODO: Check database for matching profiles
    # 循环数组内所有人员字典，将strs中的name字段设置为当前一样的名字，方便对比两个字典
    for row in rows:
        strs["name"] = row["name"]
        if strs == row:
            print(strs["name"])
            return
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables  初始化变量
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence 检查序列中的特征哪个连续的最多
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            # 设置开始位置和结束位置，间隔指定的子特征长度
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            # 如果符合子特征，则计数+1 ，继续下一次循环
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        # 每次for循环结束一轮就对比当前count和前几轮哪次次数最多
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
