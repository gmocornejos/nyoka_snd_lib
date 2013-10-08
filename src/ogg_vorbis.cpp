 #include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>

#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>

#define READ 1000000

/************** DECODER FUNCTIONS *****************************/

//returns the total number of samples in file
//if file is not in the same directory of executable then fname
// should include PATH



/*! \fn samples_number(const char *fname)
 * \brief The function  receives a pointer towards to the name of the archive thar has to be .ogg and return the number of tatal samples 
 * \param :*fname is  a pointer towards the name and direction of the song.
 * \return The number of samples in total song.
*/
int samples_number(const char *fname){
	//initialize vorbis environment
	OggVorbis_File vf;
	FILE* file = fopen(fname, "r");
	ov_open(file, &vf, NULL, 0);

	int smpls_num = (int)ov_pcm_total(&vf, -1);
	ov_clear(&vf);
	return smpls_num;
}
/*! \fn total_time(const char *fname)
 * \brief The function  receives a pointer towards to the name of the archive thar has to be .ogg and return the time of the song in seconds 
 * \param *fname is  a pointer towards the name and direction of the song.
 * \return The total time in seconds song.
*/
double total_time(const char *fname){
	//initialize vorbis environment
        OggVorbis_File vf;
        FILE* file = fopen(fname, "r");
        ov_open(file, &vf, NULL, 0);

	double total_tm = ov_time_total(&vf, -1);
	ov_clear(&vf);
	return total_tm;
}
/*! \fn samples_rate(const char *fname)
 * \brief The function  receives a pointer towards to the name of the archive thar has to be .ogg and return the samples for second
 * \param *fname is  a pointer towards the name and direction of the song.
 * \return The samples for second of the song.
*/
double samples_rate(const char *fname){
	//initialize vorbis environment
        OggVorbis_File vf;
        FILE* file = fopen(fname, "r");
        ov_open(file, &vf, NULL, 0);
	
	double smpls_rate = (double)ov_pcm_total(&vf, -1)/ov_time_total(&vf, -1);
	ov_clear(&vf);
	return smpls_rate;
}
/*! \fn decode(const char *fname, double *buffer, int smpls_num)
 * \brief The functiondecodes the song in a real array and send it to buffer this need the file are monochannel sound and be a .ogg.
 * \param  *buffer is a pointer towards array where de decoder song are sent.
 * \param  *fname is  a pointer towards the name and direction of the song.
 * \param  smpls_num is the number of total samples and is equal to size of buffer.
 * \return the number of samples read 
 */
// de datos a archivo  
long decode(const char *fname, double *buffer, int smpls_num){
	//initialize vorbis environment
	OggVorbis_File vf;
        FILE* file = fopen(fname, "r");
        ov_open(file, &vf, NULL, 0);
	
	int current_section;
	float **tempbuff;
	long read = 0; long ret = 1;
	while(ret != 0){
		ret = ov_read_float(&vf, &tempbuff, smpls_num, &current_section);
		float *temp =  tempbuff[0];  //monochannel sound
		int i;
 		for(i = 0; i < ret; i++){
			buffer[read+i] = (double) temp[i];
		}
		read = read + ret;
	}
	return read;
}



/******************* ENCODER FUNCTIONS *************************/

/** \fn encoder(const char *outfilename, double *inbuffer, int smpls_num, double smpls_rate).
 * \brief The function  is the inverce to decoder this convert a array in a file .ogg using pointers
 * \param  *outfilename is pointer toward the first letter to file where send the array once encoder
 * \param  *inbuffer is a pointer to the array whit the song decoder or the file you want to convert.
 * \param  *fname is  a pointer towards the fist letter to the archive song.
 * \param  smpls_num is the number of total samples and is equal to size of buffer.
 * \param  smpls_rate is the number of samples per second.
 */
//codificarlo comprime el acrchivo y empaquetarlo 
void encoder(const char *outfilename, double *inbuffer, int smpls_num, double smpls_rate){
	//Creates a file to work with
	FILE* file = fopen(outfilename, "w");

	//Initialize  ogg-vorbis data structure pointers
	ogg_stream_state os;
	ogg_page         og;
	ogg_packet       op;
	vorbis_info      vi;
	vorbis_comment   vc;
	vorbis_dsp_state vd;
	vorbis_block     vb;

	int eos = 0, ret;

	/*** Encode setup ***/

	vorbis_info_init(&vi);
	// Encoding using VBR. parameters: vobis info*, num of channels
	// sampling rate, quality.
	ret = vorbis_encode_init_vbr(&vi, 1, smpls_rate, 1);
	// do no continue if setup failed.
	if(ret) exit(1);

	// Add a commet
	vorbis_comment_init(&vc);
	vorbis_comment_add_tag(&vc, "ENCODER", "encoder example");

	// Analysis state setup
	vorbis_analysis_init(&vd, &vi);
	vorbis_block_init(&vd, &vb);

	// Setup stream encoder
	srand(time(NULL));
	ogg_stream_init(&os, rand());

	/**** Vorbis stream headers ****/
	{
		ogg_packet header;
		ogg_packet header_comm;
		ogg_packet header_code;

		vorbis_analysis_headerout(&vd, &vc, &header, &header_comm, &header_code);
		ogg_stream_packetin(&os, &header);
		ogg_stream_packetin(&os, &header_comm);
		ogg_stream_packetin(&os, &header_code);

		// Ensures the actual audio data will start on a new page
		while(!eos){
			int result=ogg_stream_flush(&os,&og);
			if(result==0) break;
			fwrite(og.header, 1, og.header_len, file);
			fwrite(og.body, 1, og.body_len, file);
		}
	}

	/*** Begin encoding ***/
	int buffpos = 0;
	while(!eos){
		int i;

		if(buffpos == smpls_num){
			vorbis_analysis_wrote(&vd, 0);
		}else{
			float **buffer = vorbis_analysis_buffer(&vd, READ);
			for(i = 0; i < READ; i++){
				buffer[0][i] = (float) inbuffer[i+buffpos];
				if((buffpos+i) == smpls_num) break;
			}
			buffpos = buffpos + i;
			vorbis_analysis_wrote(&vd, i);
		}

		while(vorbis_analysis_blockout(&vd, &vb) == 1){
			vorbis_analysis(&vb, NULL);
			vorbis_bitrate_addblock(&vb);

			while(vorbis_bitrate_flushpacket(&vd, &op)){
				ogg_stream_packetin(&os, &op);
				while(!eos){
					int result = ogg_stream_pageout(&os, &og);
					if(result == 0) break;
					fwrite(og.header, 1, og.header_len, file);
					fwrite(og.body, 1, og.body_len, file);

					if(ogg_page_eos(&og)) eos = 1;
				}
			}
		}
	}

	// Clean up and exit.
	ogg_stream_clear(&os);
	vorbis_block_clear(&vb);
	vorbis_dsp_clear(&vd);
	vorbis_comment_clear(&vc);
	vorbis_info_clear(&vi);

	fclose(file);
}
