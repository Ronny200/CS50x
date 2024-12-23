import os
import shutil
from subprocess import run, CalledProcessError, check_output
from pathlib import Path


# 验证文件夹是否存在并清空目录
def ensure_directory(folder):
    if not isinstance(folder, Path):
        folder = Path(folder)

    if folder.exists() and folder.is_dir():
        shutil.rmtree(folder)

    folder.mkdir(parents=True, exist_ok=True)


# 提取mp4的音频属性
def get_audio_code(mp4_path):
    try:
        result = check_output(
            [
                "ffmpeg",
                "i",
                mp4_path,
            ],
            text=True,
        )

        for line in result.splitlines():
            if "Audio:" in line:
                codec_info = line.split("Audio:")[1].strip().split()[0]
            return codec_info

        return None
    except CalledProcessError as e:
        print(f"无法获取音频格式：{e}")
        return None


# 转换MP4为BMP文件
def convert_to_bmp(mp4_path, out_path):
    try:
        # 验证文件路径是否存在，不存在则创建
        ensure_directory(out_path)

        # 输出文件名格式，默认0001.bmp
        output_pattern = os.path.join(out_path, "output_%04d.bmp")

        # 使用ffmpeg提取视频为bmp
        convert = run(
            [
                "ffmpeg",
                "-i",
                mp4_path,
                "-vf",
                "scale=640:480",
                output_pattern,
            ],
            check=True,
        )

        print("sucesfull")
    except CalledProcessError as e:
        print(f"转换错误: {e}")

    except Exception as e:
        print("发生意外错误：{e}")


# 提取mp4的wav文件
def extract_to_wav(mp4_path, out_path):
    try:
        # 验证文件路径是否存在，不存在则创建
        ensure_directory(out_path)

        base_name = Path(mp4_path).stem

        output_wav_path = os.path.join(out_path, f"{base_name}.aac")

        # 使用ffmpeg提取视频为bmp
        convert = run(
            [
                "ffmpeg",
                "-i",
                mp4_path,
                "-vn",
                "-acodec",
                "copy",
                output_wav_path,
            ],
            check=True,
        )

        print("sucesfull")
    except CalledProcessError as e:
        print(f"转换错误: {e}")

    except Exception as e:
        print("发生意外错误：{e}")
