/*
 * jpg.h
 *
 *  Created on: 9 avr. 2015
 *      Author: jfellus
 */

#ifndef PG_JPG_H_
#define PG_JPG_H_

#include <jpeglib.h>
typedef unsigned int uint;
#define TRUE 1
#define FALSE 0

typedef struct jpegfile {
	FILE* file;
	struct jpeg_decompress_struct info;
	struct jpeg_error_mgr err;
	uint w,h;
} JPEGFILE;


void save_jpg(const float* data, size_t w, size_t h, const char* outfile) {
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	FILE* f = fopen(outfile, "w");
	if(!f) {fprintf(stderr, "Can't open jpg file\n"); exit(1); }

	jpeg_stdio_dest(&cinfo, f);

	cinfo.image_width = w; 	/* image width and height, in pixels */
	cinfo.image_height = h;
	cinfo.input_components = 3;		/* # of color components per pixel */
	cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, 80, TRUE /* limit to baseline-JPEG values */);

	jpeg_start_compress(&cinfo, TRUE);

	unsigned char* line = (unsigned char*) malloc(w*3);
	row_pointer[0] = line;
	while (cinfo.next_scanline < cinfo.image_height) {
		for(uint i=0; i<w; i++) line[i*3] = line[i*3+1] = line[i*3+2] = data[cinfo.next_scanline*w + i];
		(void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}
	free(line); line = 0;

	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
}



#endif /* PG_JPG_H_ */
