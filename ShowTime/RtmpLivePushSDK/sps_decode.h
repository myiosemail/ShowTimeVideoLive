/**
 * Simplest Librtmp Send 264
 *
 * 雷霄骅，张晖
 * leixiaohua1020@126.com
 * zhanghuicuc@gmail.com
 * 中国传媒大学/数字电视技术
 * Communication University of China / Digital TV Technology
 * http://blog.csdn.net/leixiaohua1020
 *
 * 本程序用于将内存中的H.264数据推送至RTMP流媒体服务器。
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

typedef  unsigned int UINT;
typedef  unsigned char BYTE;
typedef  unsigned long DWORD;

#define false 0
#define true 1

UINT Ue(BYTE *pBuff, UINT nLen, UINT** nStartBit)
{
	//计算0bit的个数
	UINT nZeroNum = 0;
	UINT* tmp = *nStartBit;
	while ((*tmp) < nLen * 8)
	{
		if (pBuff[(*tmp) / 8] & (0x80 >> ((*tmp) % 8))) //&:按位与，%取余
		{
			break;
		}
		nZeroNum++;
		(*tmp)++;
	}
	(*tmp) ++;


	//计算结果
	DWORD dwRet = 0;
	UINT i=0;
	for (i=0; i<nZeroNum; i++)
	{
		dwRet <<= 1;
		if (pBuff[(*tmp) / 8] & (0x80 >> ((*tmp) % 8)))
		{
			dwRet += 1;
		}
		(*tmp)++;
	}
	return (1 << nZeroNum) - 1 + dwRet;
}


int Se(BYTE *pBuff, UINT nLen, UINT** nStartBit)
{
	int UeVal=Ue(pBuff,nLen,nStartBit);
	double k=UeVal;
	int nValue=ceil(k/2);//ceil函数：ceil函数的作用是求不小于给定实数的最小整数。ceil(2)=ceil(1.2)=cei(1.5)=2.00
	if (UeVal % 2==0)
		nValue=-nValue;
	return nValue;
}


DWORD u(UINT BitCount,BYTE * buf,UINT** nStartBit)
{
	DWORD dwRet = 0;
	UINT* tmp = *nStartBit;
	UINT i=0;
	for (i=0; i<BitCount; i++)
	{
		dwRet <<= 1;
		if (buf[(*tmp) / 8] & (0x80 >> ((*tmp) % 8)))
		{
			dwRet += 1;
		}
		(*tmp)++;
	}
	return dwRet;
}

/**
 * H264的NAL起始码防竞争机制 
 *
 * @param buf SPS数据内容
 *
 * @无返回值
 */ 
void de_emulation_prevention(BYTE* buf,unsigned int* buf_size)
{
	int i=0,j=0;
	BYTE* tmp_ptr=NULL;
	unsigned int tmp_buf_size=0;
	int val=0;

	tmp_ptr=buf;
	tmp_buf_size=*buf_size;
	for(i=0;i<(tmp_buf_size-2);i++)
	{
		//check for 0x000003
		val=(tmp_ptr[i]^0x00) +(tmp_ptr[i+1]^0x00)+(tmp_ptr[i+2]^0x03);
		if(val==0)
		{
			//kick out 0x03
			for(j=i+2;j<tmp_buf_size-1;j++)
				tmp_ptr[j]=tmp_ptr[j+1];

			//and so we should devrease bufsize
			(*buf_size)--;
		}
	}

	return;
}

/**
 * 解码SPS,获取视频图像宽、高信息 
 *
 * @param buf SPS数据内容
 * @param nLen SPS数据的长度
 * @param width 图像宽度
 * @param height 图像高度

 * @成功则返回1 , 失败则返回0
 */ 
int h264_decode_sps(BYTE * buf,unsigned int nLen,int** width,int** height,int** fps)
{
	int* Width = *width;
	int* Height = *height;
	int* Fps = *fps;
	
	UINT StartBit=0; 
	UINT* pStartBit = &StartBit;
	(*Fps)=0;
	de_emulation_prevention(buf,&nLen);

	int forbidden_zero_bit=u(1,buf,&pStartBit);
	int nal_ref_idc=u(2,buf,&pStartBit);
	int nal_unit_type=u(5,buf,&pStartBit);
	if(nal_unit_type==7)
	{
		int profile_idc=u(8,buf,&pStartBit);
		int constraint_set0_flag=u(1,buf,&pStartBit);	//(buf[1] & 0x80)>>7;
		int constraint_set1_flag=u(1,buf,&pStartBit);	//(buf[1] & 0x40)>>6;
		int constraint_set2_flag=u(1,buf,&pStartBit);	//(buf[1] & 0x20)>>5;
		int constraint_set3_flag=u(1,buf,&pStartBit);	//(buf[1] & 0x10)>>4;
		int reserved_zero_4bits=u(4,buf,&pStartBit);
		int level_idc=u(8,buf,&pStartBit);

		int seq_parameter_set_id=Ue(buf,nLen,&pStartBit);

		if( profile_idc == 100 || profile_idc == 110 ||
			profile_idc == 122 || profile_idc == 144 )
		{
			int chroma_format_idc=Ue(buf,nLen,&pStartBit);
			if( chroma_format_idc == 3 )
			{	
				int residual_colour_transform_flag=u(1,buf,&pStartBit);
			}
			int bit_depth_luma_minus8=Ue(buf,nLen,&pStartBit);
			int bit_depth_chroma_minus8=Ue(buf,nLen,&pStartBit);
			int qpprime_y_zero_transform_bypass_flag=u(1,buf,&pStartBit);
			int seq_scaling_matrix_present_flag=u(1,buf,&pStartBit);

			int seq_scaling_list_present_flag[8];
			if( seq_scaling_matrix_present_flag )
			{
				int i=0;
				for(i = 0; i < 8; i++ ) {
					seq_scaling_list_present_flag[i]=u(1,buf,&pStartBit);
				}
			}
		}
		int log2_max_frame_num_minus4=Ue(buf,nLen,&pStartBit);
		int pic_order_cnt_type=Ue(buf,nLen,&pStartBit);
		if( pic_order_cnt_type == 0 )
			Ue(buf,nLen,&pStartBit);
		else if( pic_order_cnt_type == 1 )
		{
			int delta_pic_order_always_zero_flag=u(1,buf,&pStartBit);
			int offset_for_non_ref_pic=Se(buf,nLen,&pStartBit);
			int offset_for_top_to_bottom_field=Se(buf,nLen,&pStartBit);
			int num_ref_frames_in_pic_order_cnt_cycle=Ue(buf,nLen,&pStartBit);

			//int *offset_for_ref_frame=new int[num_ref_frames_in_pic_order_cnt_cycle];
			int i = 0;
			int tmp;
			for( i = 0; i < num_ref_frames_in_pic_order_cnt_cycle; i++ )
				/*offset_for_ref_frame[i]*/ tmp = Se(buf,nLen,&pStartBit);
			//delete [] offset_for_ref_frame;
		}
		int num_ref_frames=Ue(buf,nLen,&pStartBit);
		int gaps_in_frame_num_value_allowed_flag=u(1,buf,&pStartBit);
		int pic_width_in_mbs_minus1=Ue(buf,nLen,&pStartBit);
		int pic_height_in_map_units_minus1=Ue(buf,nLen,&pStartBit);
		
		(*Width)=(pic_width_in_mbs_minus1+1)*16;
		(*Height)=(pic_height_in_map_units_minus1+1)*16;

		int frame_mbs_only_flag=u(1,buf,&pStartBit);
		if(!frame_mbs_only_flag)
			u(1,buf,&pStartBit);

		int direct_8x8_inference_flag=u(1,buf,&pStartBit);
		int frame_cropping_flag=u(1,buf,&pStartBit);
		if(frame_cropping_flag)
		{
			int frame_crop_left_offset=Ue(buf,nLen,&pStartBit);
			int frame_crop_right_offset=Ue(buf,nLen,&pStartBit);
			int frame_crop_top_offset=Ue(buf,nLen,&pStartBit);
			int frame_crop_bottom_offset=Ue(buf,nLen,&pStartBit);
		}
		int vui_parameter_present_flag=u(1,buf,&pStartBit);
		if(vui_parameter_present_flag)
		{
			int aspect_ratio_info_present_flag=u(1,buf,&pStartBit);              
			if(aspect_ratio_info_present_flag)
			{
				int aspect_ratio_idc=u(8,buf,&pStartBit);   
				if(aspect_ratio_idc==255)
				{
					int sar_width=u(16,buf,&pStartBit);                                  
					int sar_height=u(16,buf,&pStartBit);                                      
				}
			}
			int overscan_info_present_flag=u(1,buf,&pStartBit); 
			if(overscan_info_present_flag)
				u(1,buf,&pStartBit);                   
			int video_signal_type_present_flag=u(1,buf,&pStartBit); 
			if(video_signal_type_present_flag)
			{
				int video_format=u(3,buf,&pStartBit);                         
				int video_full_range_flag=u(1,buf,&pStartBit);                       
				int colour_description_present_flag=u(1,buf,&pStartBit);
				if(colour_description_present_flag)
				{
					int colour_primaries=u(8,buf,&pStartBit);              
					int transfer_characteristics=u(8,buf,&pStartBit);                     
					int matrix_coefficients=u(8,buf,&pStartBit);                  		
				}
			}
			int chroma_loc_info_present_flag=u(1,buf,&pStartBit);  
			if(chroma_loc_info_present_flag)
			{
				int chroma_sample_loc_type_top_field=Ue(buf,nLen,&pStartBit);             
				int chroma_sample_loc_type_bottom_field=Ue(buf,nLen,&pStartBit);       
			}
			int timing_info_present_flag=u(1,buf,&pStartBit);        
			if(timing_info_present_flag)
			{
				int num_units_in_tick=u(32,buf,&pStartBit);                              
				int time_scale=u(32,buf,&pStartBit);    
				(*Fps)=time_scale/(2*num_units_in_tick);
			}
		}
		return true;
	}
	else
		return false;
}
