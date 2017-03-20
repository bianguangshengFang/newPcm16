//
//  main.c
//  pcm16
//
//  Created by bianguangsheng on 2017/3/17.
//  Copyright © 2017年 soufunnet. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
int simplest_pcm16le_split(char *url);
int simplest_pcm16le_HalfVolumeLeft(char *url);
int simplest_pcm16le_doubleSpeed(char *url);
int simplest_pcm16le_to_pcm8(char *url);
//将从pcm16le 单声道音频采样数据中截取一部分数据
int simplest_pcm16le_cut_singlechannel(char *url,int startNum,int durNum);
//将pcm16le 双声道音频采样数据转换为WAVE 格式音频数据
int simplest_pcm16le_to_wave(const char *pcmPath,int channels,int sample_rate,const char *wavePath);
int main(int argc, const char * argv[]) {
    // insert code here...
//    本程序将pcm 音频采样数据，分割中左声道和右声道两份数据，并写入两个文件中。
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
    printf("Hello, World!\n");
    return 0;
}

/**
 将pcm文件 分割程两个文件

 @param url pcm文件本地路径
 @return 0
 */
int simplest_pcm16le_split(char *url){
    FILE *fp=fopen(url, "rb+");
    FILE *fp1=fopen("/Users/bianguangsheng/Desktop/ffmpegStudyProject/FFmpegPCM16/pcm16/pcm16/output_1.pcm", "wb+");
    FILE *fp2=fopen("/Users/bianguangsheng/Desktop/ffmpegStudyProject/FFmpegPCM16/pcm16/pcm16/output_2.pcm", "wb+");
    unsigned char *sample=(unsigned char *)malloc(4);
    //feof() 如果输入结束，则返回非零值
    while (!feof(fp)) {
        fread(sample, 1, 4, fp);
        //left
        fwrite(sample, 1, 2, fp1);
        //right
        fwrite(sample+2, 1, 2, fp2);
    }
  
    return 0;
}
//将左声道的音量降低一半

/**
 将左声道的音量降低为原来的一半

 @param url pcm文件在本地路径
 @return 0
 */
int simplest_pcm16le_HalfVolumeLeft(char *url){
    FILE *fp=fopen(url, "rb+");
    FILE *fp1=fopen("/Users/bianguangsheng/Desktop/ffmpegStudyProject/FFmpegPCM16/pcm16/pcm16/output-halfvolume.pcm", "wb+");
    int cnt=0;
    unsigned char *sample=(unsigned char *)malloc(4);
    while (!feof(fp)) {
        short *sampleNum=NULL;
        fread(sample, 1, 4, fp);
        sampleNum=(short *)sample;
        *sampleNum=*sampleNum/2;
        //left
        fwrite(sample, 1, 2, fp1);
        //right
        fwrite(sample+2, 1, 2, fp1);
        cnt++;
        
        
    }
    printf("sampel count:%d",cnt);
    free(sample);
    fclose(fp);
    fclose(fp1);
    
    return 0;
}
//将pcm16le双声道音频采样数据的声音速度提高一倍

/**
 将pcm16le双声道音频采样数据的声音速度提高一倍

 @param url 初始音频pcm文件存储路径
 @return 0
 */
int simplest_pcm16le_doubleSpeed(char *url){
    FILE *fp=fopen(url, "rb+");
    FILE *fp1=fopen("/Users/bianguangsheng/Desktop/ffmpegStudyProject/FFmpegPCM16/pcm16/pcm16/output-doubleVolume.pcm", "wb+");
    unsigned char *sample=(unsigned char *)malloc(4);
    int count=0;
    while (!feof(fp)) {
        fread(sample, 1, 4, fp);
        if (count%2!=0) {
            //将左声道的数据写入out文件
            fwrite(sample, 1, 2, fp1);
            //将右声道数据写入out文件
            fwrite(sample+2, 1, 2, fp1);
        }
        
        count++;
    }
    printf("count:%d",count);
    free(sample);
    fclose(fp);
    fclose(fp1);
    
    return 0;
}
//将pcm16le双声道音频采样数据转换为pcm8音频的采样数据

/**
 pcm16le双声道音频采样数据转换为pcm8音频的采样数据

 @param url pcm16le 路径
 @return 0
 */
int simplest_pcm16le_to_pcm8(char *url){
    FILE *fp=fopen(url, "rb+");
    FILE *fpw=fopen("/Users/bianguangsheng/Desktop/ffmpegStudyProject/FFmpegPCM16/pcm16/pcm16/output-pcm8.pcm", "wb+");
    unsigned char *sample=(unsigned char *)malloc(4);
    int cnt=0;
    while (!feof(fp)) {
        short *sample16Num=NULL;
        char sampleNume8=0;
        unsigned char sampleNum8_u=0;
        fread(sample, 1, 4, fp);
        //(-32768-32767)
        sample16Num=(short *)sample;
        //转为-128-127
        sampleNume8=(*sample16Num)>>8;//右移 sample6num 缩小为原来的256分之一，
        //转为0-255
        sampleNum8_u=sampleNume8+128;
        //left
        fwrite(&sampleNum8_u, 1, 1, fpw);
        sample16Num=(short *)(sample+2);
        sampleNume8=(*sample16Num)>>8;
        sampleNum8_u=sampleNume8+128;
        //r
        fwrite(&sampleNume8, 1, 1, fpw);
        
        cnt++;
    }
    free(sample);
    fclose(fp);
    fclose(fpw);
    return 0;
}

//将从pcm16le 单声道音频采样数据中截取一部分数据

/**
 将从pcm16le 单声道音频采样数据中截取一部分数据

 @param url pcm16le文件本地路径
 @param startNum 初始位置
 @param durNum 变化数目
 @return 0
 */
int simplest_pcm16le_cut_singlechannel(char *url,int startNum,int durNum){
    FILE *fp=fopen(url, "rb+");
    FILE *fpcut=fopen("/Users/bianguangsheng/Desktop/ffmpegStudyProject/FFmpegPCM16/pcm16/pcm16/outcut.pcm", "wb+");
    FILE *fptext=fopen("/Users/bianguangsheng/Desktop/ffmpegStudyProject/FFmpegPCM16/pcm16/pcm16/outcuttext.txt", "wb+");
    unsigned char *sample=(unsigned char *)malloc(2);
    int cnt=0;
    while (!feof(fp)) {
        fread(sample, 1, 2, fp);
        if (cnt>startNum&&cnt<=startNum+durNum) {
            fwrite(sample, 1, 2, fpcut);
            short sampleNum=sample[1];
            sampleNum=sampleNum*256;
            sampleNum=sampleNum+sample[1];
            //将新的数据写入 outcuttext.txt 文件txt
            fprintf(fptext, "%6d",sampleNum);
            if (cnt%10==0) {
                fprintf(fptext, "\n");
            }
        }
    }
    free(sample);
    fclose(fptext);
    fclose(fp);
    fclose(fpcut);
    
    return 0;
}
//将pcm16le 双声道音频采样数据转换为WAVE 格式音频数据

/**
 将pcm16le 双声道音频采样数据转换为WAVE 格式音频数据

 @param pcmPath PCM16LE 文件路径
 @param channels 频道数
 @param sample_rate 样本频率
 @param wavePath wave文件地址
 @return 0
 */
int simplest_pcm16le_to_wave(const char *pcmPath,int channels,int sample_rate,const char *wavePath){
    typedef struct WAVE_HEADER{
        char fccID[4];//
        unsigned long dwSize;
        char fccType[4];
        
        
        
    }WAVE_HEADER;
    typedef struct WAVE_FMT {
        char fccID[4];
        unsigned long dwSize;
        unsigned short wFormatTag;
        unsigned short wChannals;
        unsigned long dwSamplesPerSec;
        unsigned long dwAvgBytesPerSec;
        unsigned short wBlockAlign;
        unsigned short uiBitsPerSample;
    
        
    }WAVE_FMT;
    
    typedef struct WAVE_DATA {
        char fccID[4];
        unsigned long dwSize;
    }WAVE_DATA;
    if (channels==0||sample_rate==0) {
        channels=2;
        sample_rate=44100;
    }
    int bits=16;
    WAVE_HEADER pcmHeader;
    WAVE_FMT pcmFMT;
    WAVE_DATA pcmData;
    unsigned short m_pcmData;
    FILE *fp,*fout;
    fp=fopen(pcmPath, "rb+");
    fout=fopen(wavePath,"wb+");
    if (fp==NULL) {
        printf("open pcm file error\n");
        return -1;
        
    }
    if (fout==NULL) {
        printf("create wave file error\n");
        return -1;
    }
    //wave header
    memcpy(pcmHeader.fccID,"RIFF",strlen("RIFF"));
    memcpy(pcmHeader.fccType,"WAVE",strlen("WAVE"));
    fseek(fout, sizeof(pcmHeader), 1);
    //wave_fmt
    pcmFMT.dwSamplesPerSec=sample_rate;
    pcmFMT.dwAvgBytesPerSec=pcmFMT.dwSamplesPerSec * sizeof(m_pcmData);
    pcmFMT.uiBitsPerSample=bits;
    memcpy(pcmFMT.fccID, "fmt", sizeof("fmt"));
    pcmFMT.dwSize=16;
    pcmFMT.wBlockAlign=2;//每个采样点字节数
    pcmFMT.wChannals=channels;
    pcmFMT.wFormatTag=1;//设置波形声音的格式
    fwrite(&pcmFMT, sizeof(WAVE_FMT), 1, fout);
    //wave_data
    memcpy(pcmData.fccID, "data", strlen("data"));
    pcmData.dwSize=0;
    fseek(fout, sizeof(WAVE_DATA), SEEK_CUR);
    //将fp文件指针指向文件 按一次读取 sizeof(unsigned short) 读取到m_pcmData 缓存中
    fread(&m_pcmData, sizeof(unsigned short), 1, fp);
    while (!feof(fp)) {
        pcmData.dwSize+=2;
        fwrite(&m_pcmData, sizeof(unsigned short), 1, fout);
        fread(&m_pcmData, sizeof(unsigned short), 1, fp);
    }
    pcmHeader.dwSize=44+pcmData.dwSize;
    rewind(fout);
    //把pcmheader存储的内容 写入到文件
    fwrite(&pcmHeader, sizeof(WAVE_HEADER), 1, fout);
    //定位文件指针从文件当前位置偏离sizeof（wave——fmt）个位置
    fseek(fout, sizeof(WAVE_FMT), SEEK_CUR);
    //pcmdata 内容写入到fout 指定的文件中
    fwrite(&pcmData, sizeof(WAVE_FMT), 1, fout);
    
    fclose(fp);
    fclose(fout);
    
    
    
    
    
    
    return 0;
}

