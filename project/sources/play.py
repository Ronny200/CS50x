import os
import time
import subprocess


from pathlib import Path
from subprocess import run, CalledProcessError, check_output


def play_ascii_art(asc_dir, fps=25):
    """
    按顺序播放给定目录下的所有 .txt ASCII 艺术图画，并按照指定的帧率播放。

    参数:
    asc_dir (str): 包含 .txt ASCII 艺术图画的目录路径。
    fps (int): 播放帧率，默认为 25 帧/秒。
    """
    # 获取并排序所有的 .txt 文件
    txt_files = sorted(
        Path(asc_dir).glob("*.txt"),
        key=lambda p: (
            int(p.stem.split("_")[-1])
            if "_" in p.stem and p.stem.split("_")[-1].isdigit()
            else float("inf")
        ),
    )

    # 计算每帧之间的延迟时间
    delay = 1 / fps

    try:
        for txt_file in txt_files:
            with open(txt_file, "r", encoding="utf-8") as file:
                content = file.read()

            # 清屏并打印当前帧的内容
            clear_screen()
            print(content)

            # 等待一段时间以保持指定的帧率
            time.sleep(delay)
    except KeyboardInterrupt:
        print("\nPlayback interrupted by user.")


def clear_screen():
    """根据操作系统清空控制台屏幕"""
    import platform

    if platform.system() == "Windows":
        os.system("cls")
    else:
        os.system("clear")


def play_audio(path):
    play = ["ffplay.exe", "-nodisp", "-autoexit", "-loglevel", "quiet", path]
    process = subprocess.Popen(play)
    return process


if __name__ == "__main__":
    asc_path = r"convert\asc"
    play_ascii_art(asc_path, fps=25)
