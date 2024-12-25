import sys

from sources.play import play_ascii_art, play_audio, move_cursor_to_top
from sources.ffmpeg import (
    convert_to_bmp,
    extract_to_wav,
    get_bmp,
    convert_to_asc,
    convert_txt_path,
    clear_console_subprocess,
)


def main():
    # 定义默认路径
    music_name = r"convert\wav\convert.aac"
    bmp_path = r"convert\bmp"
    asc_path = r"convert\asc"
    wav_path = r"convert\wav"
    mp4 = r"convert.mp4"
    fps = 25

    convert_to_bmp(mp4, bmp_path)
    extract_to_wav(mp4, wav_path)
    all_bmps = get_bmp(bmp_path)

    print("convert bmp to ascii...")
    for bmp in all_bmps:
        convert_to_asc(bmp, convert_txt_path(bmp, asc_path))

    try:
        clear_console_subprocess()
        move_cursor_to_top()
        play_audio(music_name)
        play_ascii_art(asc_path, fps)
    except KeyboardInterrupt:
        print("\nProgram interrupted by user.")
        sys.exit(1)


if __name__ == "__main__":
    main()
