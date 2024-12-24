import os
import shutil
from subprocess import run, CalledProcessError, check_output
from pathlib import Path


def get_bmp(directory):
    try:
        # 获取目录下所有的文件和子目录
        with os.scandir(directory) as entries:
            # 构建完整路径并过滤出只包含.bmp文件的列表
            bmp_files = [
                os.path.join(directory, entry.name)
                for entry in entries
                if entry.is_file() and entry.name.lower().endswith(".bmp")
            ]
        return bmp_files
    except FileNotFoundError:
        print(f"The directory {directory} does not exist.")
        return []


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
                "vflip, scale=640:480",
                "-c:v",
                "bmp",
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


def convert_txt_path(bmp_path, asc_dir):
    """
    参数:
    bmp_path (str): 输入的 .bmp 文件路径。
    asc_dir (str): 输出的 .txt 文件所在的目录路径。
    """
    # 获取文件名（不带路径）
    file_name = os.path.basename(bmp_path)

    # 检查文件扩展名是否为.bmp
    if not file_name.lower().endswith(".bmp"):
        raise ValueError("Input path does not point to a .bmp file.")

    # 构建新的文件名（将.bmp替换为.txt）
    base_name, _ = os.path.splitext(file_name)
    new_file_name = f"{base_name}.txt"

    # 确保新目录存在，如果不存在则创建它
    os.makedirs(asc_dir, exist_ok=True)

    # 构建完整的新文件路径
    new_file_path = os.path.join(asc_dir, new_file_name)

    return new_file_path


# 转换bmp为ascii
def convert_to_asc(bmp_path, txt_path):
    try:
        # 使用bmp2asc将bmp转成ascii字符图
        convert = run(
            [
                "bmp2asc.exe",
                "-i",
                bmp_path,
                "-o",
                txt_path,
            ],
            check=True,
        )

        print("sucesfull")
    except CalledProcessError as e:
        print(f"转换错误: {e}")

    except Exception as e:
        print("发生意外错误：{e}")
