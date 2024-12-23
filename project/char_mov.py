from sources.ffmpeg import convert_to_bmp, extract_to_wav


def main():
    # 定义默认路径
    mp4 = "convert.mp4"
    bmp_path = r"convert\bmp"
    asc_path = r"convert\asc"
    wav_path = r"convert\wav"

    convert_to_bmp(mp4, bmp_path)
    extract_to_wav(mp4, wav_path)


if __name__ == "__main__":
    main()
