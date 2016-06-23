//
//  LibRtmpSession.hpp
//  AudioEditX
//
//  Created by Alex.Shi on 16/3/8.
//  Copyright © 2016年 com.Alex. All rights reserved.
//

#ifndef RtmpSession_hpp
#define RtmpSession_hpp

#include <stdio.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif
    
typedef struct RTMP RTMP;
typedef struct RTMPPacket RTMPPacket;
typedef struct _RTMPMetadata RTMPMetadata;
typedef struct _DataItem DataItem;
    
class LibRtmpSession{
public:
    LibRtmpSession(char* szRtmpUrl);
    ~LibRtmpSession();
    
    int Connect();
    void DisConnect();
    int IsConnected();
    
    int SendAudioRawData(unsigned char* pBuff, int len, unsigned int ts);
    
    int SendVideoRawData(unsigned char* buf, int videodatalen, unsigned int ts);
    int GetConnectedFlag(){return  _iConnectFlag;};
    void SetConnectedFlag(int iConnectFlag){_iConnectFlag=iConnectFlag;};
private:
    LibRtmpSession();
    void MakeAudioSpecificConfig(char* pData, int aactype, int sampleRate, int channels);
    int SendAudioSpecificConfig(int aactype, int sampleRate, int channels);
    int SendAudioData(unsigned char* buf, int size);
    int SendVideoData(unsigned char* buf, int size);
    
    int RtmpPacketSend(RTMPPacket* packet);
    int SendPacket(unsigned int nPacketType,unsigned char *data,unsigned int size,unsigned int nTimestamp);
    int SendH264Packet(unsigned char *data,unsigned int size,int bIsKeyFrame,unsigned int nTimeStamp);
    int SendAACData(unsigned char* buf, int size, unsigned int timeStamp);
    int SendVideoSpsPps(unsigned char *pps,int pps_len,unsigned char * sps,int sps_len);
    int getSampleRateType(int iSampleRate);
    
    int SeparateNalus(unsigned char* pBuff, int len);
private:
    char _szRtmpUrl[256];
    RTMP* _pRtmp;
    DataItem* _pAdtsItems;
    DataItem* _pNaluItems;
    int _iConnectFlag;
    int _iMetaDataFlag;
    unsigned int _uiStartTimestamp;
    unsigned int _uiAudioDTS;
    unsigned int _uiVideoLastAudioDTS;
    unsigned int _uiAudioDTSNoChangeCnt;
    
    RTMPMetadata* _pMetaData;
    //pthread_mutex_t _mConnstatMutex;
};
#ifdef __cplusplus
}
#endif
#endif /* RtmpSession_hpp */
