# MP4 to Ascii mov
#### Video Demo:  <URL HERE>
#### Description: Automatically convert an MP4 video file into a black and white ASCII string animation.

受到filter-more这一作业的启发，想到将mp4按照帧提取成bmp图片，然后将每一张图片都转换成对应的ascii字符串，连续输出的情况下相当于变成了ascii字符串的动画。

由于python对文件的调用，对字符串处理的方便性，所以用python代码作为主程序，用c来处理每张图片，因为c在处理二进制文件上的性能更高效。

这样综合起来既有了python的方便易操作，又有了c的高效性能，也更容易维护代码。

> 使用方法：需要将bmp2asc.exe和需要转换的convert.mp4放到ascii_mov.py同级目录下，并且需要安装ffmpeg.exe和ffplay.exe

#### 使用ffmpeg
原本想根据cs50学到的知识直接对图片进行处理，但是思考再三后还是选择了用ffmpeg来帮助程序实现特定功能，比如按帧提取bmp图片并进行翻转。

因为在c语言进行字符串转化的时候数组是按顺序执行的，有些图片就会翻转，而且本身就需要用ffmpeg来提取图片和音频文件，所以就直接使用了ffmpeg软件，而且ffmpeg更高效效果也更好。

在播放ascii动画时需要背景音乐，顺便就使用了ffplay。

#### ascii_mov.py
这是主程序入口，定义了路径以及用来调用各个函数用，代码不会太长，因为需要保证main函数的简洁性方便维护。

#### bin\bmp2asc.c
使用c语言实现对bmp图片的操作。

主要是根据filter作业当中的思路，对bmp图片平均他们的灰度值，然后按照灰度值使用对应的ascii字符填充，并且可以在命令行参数中自定义字符串输出后的宽度。

#### sources\ffmpeg.py
在这个文件中，主要是对bmp图像进行处理

* ensure_directory: 验证需要输出的文件夹是否存在，如果存在则清空
* convert_to_bmp: 将视频文件用ffmpeg转成bmp图片
* get_audio_code: 获取mp4视频文件中音乐的格式，比如aac还是wav
* extract_to_wav: 提取mp4视频文件中的音乐
* convert_to_asc: 将bmp转换成ascii
* convert_txt_path: 通过图片名构建对应的txt文件名
* get_bmp：获取提取后文件夹下所有的bmp图片相对路径

#### sources\play.py
在这个文件中，主要是播放相关函数

* move_cursor_to_top: 每次输出万一个字符串就将光标移动到顶部，原本是使用clear命令，但是这个命令会造成闪烁，于是使用移动光标位置来替代。
* play_ascii_art: 循环播放所有字符串
* play_audio: 使用子进程同步播放音乐
