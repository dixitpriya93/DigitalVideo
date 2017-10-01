//  To compile and run:
//
//  Using Visual C++
//  0) Place this file (greyscaleimage.c) in a separate Folder.
//  1) Launch your Visual C++ application.
//  2) Pull-down under "File" in the upper left corner of Visual C++
//          to select "Open". A browser will pop-up. Find this file (greyscaleimage.c)
//          in the browser and open this file.
//  3) Pull-down under "Build" at the top  of Visual C++ to select "Compile"
//     A window will pop-up and ask if you want to create a "default project workspace".
//      Select "Yes". The workspace will be created and greyscaleimage.c will be compiled.
//  4) Pull-down under "Build" again and select "Build gryscaleimage.exe".
//  5) Pull-down under "Build" again and select "Execute gryscaleimage.exe"
//        and the program will run.
//
//
//  If you are using, e.g., Dev-C++
//  simply put the file in a folder, compile and run
//
//
//
//  When you have run this program, double-click on it and your default BMP display application
//   will open the file and display it on your screen.
//
//
//  Now copy this program to another file, and modify the program.
//  Change the program lines so that it outputs the exact same image as a BMP with Bitcount = 24,
//  i.e. a 24-bit BMP image file.
//  E-mail your modified program and a 100x100 pel 24-bit BMP file to me by 9/27/2012.
//
//

# include <stdio.h>
# include <io.h>
# include <stddef.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <limits.h>
// declare your subroutines
int fill4bits(unsigned char * header, int number);
//
int main(int argc, char* argv[])
{
   int i,j,rowsize,filesize,offset;
   int width, height,num_written,ireturn;
   int fd_out,k;
   unsigned char *imagedata,bitmapfileheader[14],bitmapinfoheader[40],colortable[4*256];
   unsigned char zerovec[4];
   char directory[90],basename[50],file_name_out[100];
   double PI;
   //
   PI=3.14159265359;
   // _________________________________________________________________ 
   printf("\t\tenter: an existing directory to write image to \n");
   printf("\t\t\t(use double backslashes as in c:\\\\directory1 )\n");
   scanf("%s",directory);
   printf("\t\tenter: the output filename for the grey-scale BMP image.\n");
   printf("\t\t\t(without the .bmp extension)\n");
   scanf("%s",basename);
   // form the filename for the output BMP image
   sprintf(file_name_out,"%s\\%s.bmp",directory,basename);
   printf("\t\tenter: the horizontal and vertical size of the image\n");
   scanf("%d %d",&width,&height);
   // _________________________________________________________________
   // zero-out the 14-byte bitmapfileheader
   for(i=0; i<14; i++){(*(bitmapfileheader+i))=(unsigned char)0;}
   // assign the value 66 and 77 to the 1st two bytes to identify the file as a BMP file
   (*(bitmapfileheader+0))= (unsigned char)66;
   (*(bitmapfileheader+1))= (unsigned char)77;
   // compute the filesize for the 256-level greyscale image
   // To do this we need the rowsize for the image-data where 0-padding
   // to a 4-byte boundary has been applied where needed.
   //  #-of-bytes-per-row is 0-padded to be a multiple of 4)
   rowsize = 4*int((width+3)/4);
   filesize=14+40+256*4+rowsize*height;
   //fill in the 4-byte filesize
   ireturn = fill4bits(bitmapfileheader+2,filesize);
   // Set the reserve bytes in the bitmapfileheader to 0
   ireturn = fill4bits(bitmapfileheader+6,0);
   // compute the offset to the image-data and fill-in those bytes
   offset=14+40+256*4;
   ireturn = fill4bits(bitmapfileheader+10,offset);
   // The bitmapfileheader is complete
   ////////////////////////////////////////////////////////
   // assign the bytes for the size of the bitmapinfoheader (40)
   ireturn = fill4bits(bitmapinfoheader,40);
   // assign the width and height in the bitmapinfoheader
   ireturn = fill4bits(bitmapinfoheader+4,width);
   ireturn = fill4bits(bitmapinfoheader+8,height);
   // assign the # of planes to byte # 12 and 13 of bitmapinfoheader
   (*(bitmapinfoheader+12)) = (unsigned char)1;
   (*(bitmapinfoheader+13)) = (unsigned char)0;
   // assign the bytes 14-15 for the number of bits per pixel
   (*(bitmapinfoheader+14)) = (unsigned char)8;
   (*(bitmapinfoheader+15)) = (unsigned char)0;
   // fill-in the Compression=0 (no compression)
   ireturn = fill4bits(bitmapinfoheader+16,0);
   //  Now fill-in the size of the size of the image-data = rowsize*height.
   ireturn = fill4bits(bitmapinfoheader+20,rowsize*height);
   // fill-in # horiz-vert pixels per meter (just use 0)
   ireturn = fill4bits(bitmapinfoheader+24,0);
   ireturn = fill4bits(bitmapinfoheader+28,0);
   // fill-in the number-of-colors = 256 in the image
   ireturn = fill4bits(bitmapinfoheader+32,256);
   // fill-in the number-of-important-colors = 256
   ireturn = fill4bits(bitmapinfoheader+36,256);
   // The bitmapinfoheader is complete
   /////////////////////////////////////////////////////////////////
   // Now assign the RGBQUADS in the color-table
   for(i=0; i<256; i++){
	 colortable[4*i]=i;
	 colortable[1+4*i]=i;
	 colortable[2+4*i]=i;
	 colortable[3+4*i]=0;
   }
   // The RGBQUAD colortable is complete
   /////////////////////////////////////////////////////////////////
   // finally, fill-in the image-data (greyscale)
   // 1st malloc space for the row-ordered greyscale image
   imagedata =(unsigned char *)malloc(width*height*sizeof(unsigned char));
   // zero it out
   for(i=0; i<width*height; i++){*(imagedata+i) = (unsigned char)0;}
   // assign a grey-scale image as being 1 cycle of a cosine in the x-direction
   for(i=0; i<height; i++){
	 for(j=0; j<width; j++){
		k=(int)( 0.5*255.99*(1.0+cos(2.0*PI*j/width)) );
       (*(imagedata+j+i*width))=(unsigned char)k;
   } }
   //  The image-data is complete

   // ________________________________________________________________ //
   // In  writing out the image, we can use a vector of zeros 
   //    called zerovec[]
   //    to zero-pad the image-data rows to a multiple of 4 (if needed)
   for(i=0; i<3; i++){zerovec[i]=(unsigned char)0;}
   ////////////////////////////////
   // write out the BMP file
   fd_out = _open(file_name_out,O_WRONLY|_O_BINARY|_O_CREAT,_S_IWRITE);
   if(fd_out == -1){printf(" unable to open %s for output. Exitting program.\n",file_name_out); exit(-1);}
   // write the bitmapfileheader
   num_written = write(fd_out,bitmapfileheader,14);
   // write out the bitmapinfoheader
   num_written = write(fd_out,bitmapinfoheader,40);
   // write out the RGBQUAD colortable
   num_written = write(fd_out,colortable,4*256);
   // write out the image-data one row at a time (cause we might need to 0-pad)
   // Note: The BMP format writes out the image-data stating at the
   //   bottom row of the image
   for(i=height-1; i>=0; i--){
     num_written = write(fd_out,imagedata+i*width,width);
	 // 0-pad to a 4-byte boundary if necessary
	 if(rowsize>width){
		 num_written = write(fd_out,zerovec,rowsize-width);
	 }
   }
   //close image file
   close(fd_out);
   //
   return 0;
}

//////////////////////////////////////////////////////////////////////////////
int fill4bits(unsigned char * header, int number)
{
   (*(header+3)) = (unsigned char)(number/(256*256*256));
   (*(header+2)) = (unsigned char)((number-(*(header+3))*(256*256*256))/(256*256));
   (*(header+1)) = (unsigned char)((number-(*(header+3))*(256*256*256)-(*(header+2))*(256*256))/(256));
   (*(header+0)) = (unsigned char)(number%256);

 return 0;
}
//////////////////////////////////////////////////////////