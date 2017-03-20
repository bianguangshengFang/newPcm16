# newPcm16
# newPcm16
/    本程序将pcm 音频采样数据，分割中左声道和右声道两份数据，并写入两个文件中。
    simplest_pcm16le_split("/Users/bianguangsheng/Desktop/ffmpegStudyProject/FFmpegPCM16/pcm16/pcm16/NocturneNo2inEflat_44.1k_s16le.pcm");
//    本程序将pcm采样音频数据，左声道的音量调为一般
    simplest_pcm16le_HalfVolumeLeft("/Users/bianguangsheng/Desktop/ffmpegStudyProject/FFmpegPCM16/pcm16/pcm16/NocturneNo2inEflat_44.1k_s16le.pcm");
//     本程序将pcm采样音频数据的声音速度提高一倍
    simplest_pcm16le_doubleSpeed("/Users/bianguangsheng/Desktop/ffmpegStudyProject/FFmpegPCM16/pcm16/pcm16/NocturneNo2inEflat_44.1k_s16le.pcm");
//    将ple16 音频数据转为pcm8 音频数据
    simplest_pcm16le_to_pcm8("/Users/bianguangsheng/Desktop/ffmpegStudyProject/FFmpegPCM16/pcm16/pcm16/NocturneNo2inEflat_44.1k_s16le.pcm");
//     将从pcm16le 单声道音频采样数据中截取一部分数据
    
    simplest_pcm16le_cut_singlechannel("/Users/bianguangsheng/Desktop/ffmpegStudyProject/FFmpegPCM16/pcm16/pcm16/NocturneNo2inEflat_44.1k_s16le.pcm", 0, 120);
    //将pcm16le 双声道音频采样数据转换为WAVE 格式音频数据
    simplest_pcm16le_to_wave("/Users/bianguangsheng/Desktop/ffmpegStudyProject/FFmpegPCM16/pcm16/pcm16/NocturneNo2inEflat_44.1k_s16le.pcm", 2, 44100, "/Users/bianguangsheng/Desktop/ffmpegStudyProject/FFmpegPCM16/pcm16/pcm16/output_nocturne.wav");
