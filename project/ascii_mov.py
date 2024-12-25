import sources.play as p
import sources.ffmpeg as f
import argparse
import sys


def main():
    # 添加命令行参数
    parser = argparse.ArgumentParser(
        description="Convert the mp4 file to ascii mov.",
    )
    parser.add_argument(
        "-c",
        "--convert",
        type=str,
        metavar="mp4_file",
        help="auto convert and play ascii mov.",
    )
    parser.add_argument(
        "-p",
        "--play",
        type=str,
        metavar="mp4_file",
        help="play ascii mov.",
    )

    # 判断命令行参数
    args = parser.parse_args()
    info = {}

    if args.convert:
        info = f.parse_filename(args.convert)
        f.ensure_directory(info["temp_folder"])

        print("start convert mp4 to bmp...")
        f.convert_to_bmp(info["file_name"], info["temp_folder"])

        print("start extract music...")
        f.extract_to_wav(info["file_name"], info["folder_path"])

        print("start convert all bmp to ascii...")
        f.convert_bmp_asc(info["temp_folder"], info["folder_path"])

        f.ensure_directory(info["temp_folder"])

        try:
            f.clear_console_subprocess()
            p.move_cursor_to_top()
            p.play_audio(info["audio_file"])
            p.play_ascii_art(info["folder_path"], info["fps"])

        except KeyboardInterrupt:
            print("\nProgram interrupted by user.")
            sys.exit(1)

    elif args.play:
        # 直接播放ascii动画
        info = f.parse_filename(args.play)

        if f.ensure_art_directory(info["folder_path"]):
            f.clear_console_subprocess()
            p.move_cursor_to_top()
            p.play_audio(info["audio_file"])
            p.play_ascii_art(info["folder_path"], info["fps"])

    else:
        parser.print_help()
        sys.exit(1)


if __name__ == "__main__":
    main()
