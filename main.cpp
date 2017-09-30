// YUVimages.cpp

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
//////////////////////////////////////////////////////////////////////////////////////////////
// declare all your subroutines here
void background(unsigned char rcolor, unsigned char gcolor, unsigned char bcolor,int width, int height,
			unsigned char * r, unsigned char * g, unsigned char * b);
int rectangle(int lower_x, int lower_y, int r_width, int r_height, float angle_deg, unsigned char red,
            unsigned char green, unsigned char blue, unsigned char * r, unsigned char * g, unsigned char * b,
            int image_width, int image_height);
int ellipse(int lower_x, int lower_y, int r_width, int r_height, float angle_deg, unsigned char red,
	unsigned char green, unsigned char blue, unsigned char * r, unsigned char * g, unsigned char * b,
	int image_width, int image_height);
int arc(int ipix_wide,float arc_length_deg,int lower_x, int lower_y, int r_width, int r_height, float angle_deg, unsigned char red,
	unsigned char green, unsigned char blue, unsigned char * r, unsigned char * g, unsigned char * b,
	int image_width, int image_height);
int triangle(int lower_x, int lower_y, int r_width, int r_height, int peak_x, float angle_deg, unsigned char red,
	unsigned char green, unsigned char blue, unsigned char * r, unsigned char * g, unsigned char * b,
	int image_width, int image_height);
int girl_tinman(int upper_x, int upper_y, int r_height, float angle_deg,
		   unsigned char red, unsigned char green, unsigned char blue,
		   unsigned char * r, unsigned char * g, unsigned char * b,
		   int image_width, int image_height);
int guy_tinman(int upper_x, int upper_y, int r_height, float angle_deg,
		   unsigned char red, unsigned char green, unsigned char blue,
		   unsigned char * r, unsigned char * g, unsigned char * b,
		   int image_width, int image_height);
int soccerGround(int upper_x, int upper_y, int r_height, float angle_deg,
		   unsigned char red, unsigned char green, unsigned char blue,
		   unsigned char * r, unsigned char * g, unsigned char * b,
		   int image_width, int image_height);
int number1(int lower_x, int lower_y, float angle_deg,
		   unsigned char * r, unsigned char * g, unsigned char * b,
		   int image_width, int image_height);
int number2(int lower_x, int lower_y, float angle_deg,
		   unsigned char * r, unsigned char * g, unsigned char * b,
		   int image_width, int image_height);
int number3(int lower_x, int lower_y, float angle_deg,
		   unsigned char * r, unsigned char * g, unsigned char * b,
		   int image_width, int image_height);
int soccer(int upper_x, int upper_y, int r_height, float angle_deg,
		   unsigned char red, unsigned char green, unsigned char blue,
		   unsigned char * r, unsigned char * g, unsigned char * b,
		   int image_width, int image_height);
int celebration(int upper_x, int upper_y, int r_height, float angle_deg,
		   unsigned char red, unsigned char green, unsigned char blue,
		   unsigned char * r, unsigned char * g, unsigned char * b,
		   int image_width, int image_height);
//////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
   // create all your variables here
   int i,j,k,i1,j1,itmp,jtmp,ytmp,width,height,ireturn;
   int num_images;
   int ix,iy;
   float angle;
   int num_written,fd_out;
   unsigned char *r,*g,*b,*y,*u,*v;
   char directory[90];
   char basename[50],file_name_out[100];
   float usum,vsum,alpha;
   int cntr = 0;
   // _________________________________________________________________
   // get user input
   //printf("\t\tenter: the full name of an existing directory to place\n");
   //printf("\t\t     the YUV images (e.g.  C:\\example).\n");
   //scanf("%s",directory);
   //printf("\t\tenter: the number of YUV images to generate.\n");
   //scanf("%d",&num_images);
   //printf("\t\tenter: two even integers\n");
   //printf("\t\t  the horizontal and vertical size of images.\n");
   //scanf("%d %d",&width,&height);
   //printf("\t\tenter: a basename for the image files.\n");
   //printf("\t\t(e.g. enter glop and you get files named glop0.yuv, glop2.yuv, etc..\n");
   //scanf("%s",basename);

   //Bypass user input (for efficiency)
   sprintf(directory,"%s", "c:\\video");
   num_images = 1500;
   width = 960;
   height = 640;
   sprintf(basename,"%s", "test");
   // _________________________________________________________________
   // malloc space for row-ordered RGB images and row-ordered YUV images.
   // note: UV images will be sub-sampled (4:2:0)
   r =(unsigned char *)malloc(width*height*sizeof(unsigned char));
   g =(unsigned char *)malloc(width*height*sizeof(unsigned char));
   b =(unsigned char *)malloc(width*height*sizeof(unsigned char));
   //
   y =(unsigned char *)malloc(width*height*sizeof(unsigned char));
   u =(unsigned char *)malloc(width*height/4*sizeof(unsigned char));
   v =(unsigned char *)malloc(width*height/4*sizeof(unsigned char));
   for(i=0; i<width*height; i++){*(r+i) = (unsigned char)0;}
   for(i=0; i<width*height; i++){*(g+i) = (unsigned char)0;}
   for(i=0; i<width*height; i++){*(b+i) = (unsigned char)0;}
   for(i=0; i<width*height; i++){*(y+i) = (unsigned char)0;}
   for(i=0; i<width*height/4; i++){*(u+i) = (unsigned char)0;}
   for(i=0; i<width*height/4; i++){*(v+i) = (unsigned char)0;}
  //___________________________________________________________________________________________________________________

   for(k=0; k<num_images; k++){  // iterate through the #-frames = num_images

      background(24,145,19,width,height,r,g,b);
      ireturn=soccerGround(900,(height/2)+40,70, 60.0,(unsigned char)0,(unsigned char)0,(unsigned char)255,r,g,b,width,height);

     if (k < 30){ireturn=number1(280, 320, 0.0,r,g,b,width,height);}
     if (k>=30 && k < 60){ireturn=number2(420, 260, 0.0,r,g,b,width,height);}
     if (k>=60&& k < 90){number3(600, 330, 0.0,r,g,b,width, height);}
     if(k>=90 && k<100){

          ireturn=girl_tinman(430,height/2-70,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(330,height/2+80,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(330,height/2-140,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(100,height/2-50,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=guy_tinman(500,height/2-50,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=soccer(width/2,height/2,70, 60.0,(unsigned char)0,(unsigned char)0,(unsigned char)0,r,g,b,width,height);
          ireturn=guy_tinman(600,height/2+80,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=guy_tinman(600,height/2-140,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=guy_tinman(860,height/2-50,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          }
		  
          if(k>=100 && k<200){
          ireturn=girl_tinman(430,height/2-70,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(330,height/2+80,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(330,height/2-140,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(100,height/2-50,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=guy_tinman(500,height/2-50,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=guy_tinman(600,height/2+80,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=guy_tinman(600,height/2-140,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=guy_tinman(860,height/2-50,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=soccer(width/2+(k-100),height/2+(k-100),70, 60.0,(unsigned char)0,(unsigned char)0,(unsigned char)0,r,g,b,width,height);
          }
          if(k>=200 && k<400){
          if(k>300){
          ireturn=girl_tinman(430+(k-300),height/2-70,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          }
          if(k<=300){
          ireturn=girl_tinman(430,height/2-50,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          }
          ireturn=girl_tinman(330+(k-200),height/2+80,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(330,height/2-140,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(100,height/2-50,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          if(k<270){
          ireturn=guy_tinman(500,height/2-(50-200+k),70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          }else{
          ireturn=guy_tinman(500,height/2-120,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          }
          ireturn=guy_tinman(600-(k-200),height/2+90,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=guy_tinman(600,height/2-140,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=guy_tinman(860,height/2-50,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=soccer(width/2+100,height/2+(300-k),70, 60.0,(unsigned char)0,(unsigned char)0,(unsigned char)0,r,g,b,width,height);

          }
          if(k>=400 && k<450){
          ireturn=girl_tinman(530,height/2-70-(k-400),70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(530,height/2+80,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(330,height/2-140,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(100,height/2-50,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=guy_tinman(500,height/2-120,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=guy_tinman(400,height/2+90,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=guy_tinman(600,height/2-140,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=guy_tinman(860,height/2-50,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);

          ireturn=soccer(width/2+100-(k-400),height/2-100,70, 60.0,(unsigned char)0,(unsigned char)0,(unsigned char)0,r,g,b,width,height);

          }
          if(k>=450 && k<500){
          ireturn=girl_tinman(530,height/2-70-(k-400),70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(530,height/2+80,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(330,height/2-140,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(100,height/2-50,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=guy_tinman(500,height/2-120-(k-450),70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=guy_tinman(400,height/2+90,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=guy_tinman(600,height/2-140,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=guy_tinman(860,height/2-50,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=soccer(width/2+50,height/2-100-(k-500),70, 60.0,(unsigned char)0,(unsigned char)0,(unsigned char)0,r,g,b,width,height);

          }
          if(k>=500 && k<900){
          if(k<600){
          ireturn=girl_tinman(530+(k-500),height/2-170,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          }else if(k<700){
          ireturn=girl_tinman(630,height/2-170,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          }else if(k<800){
          ireturn=girl_tinman(630,height/2-170+(k-700),70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          }else{
          ireturn=girl_tinman(630,height/2-70,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          }
          ireturn=girl_tinman(530,height/2+80,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(330,height/2-140,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(100,height/2-50,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          if(k<600){
          ireturn=guy_tinman(500,height/2-170+(k-500),70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          }else{
          ireturn=guy_tinman(500,height/2-30,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          }
          ireturn=guy_tinman(400,height/2+90,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          if(k>700){
          ireturn=guy_tinman(600+(k-700),height/2-140,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          }else{
          ireturn=guy_tinman(600,height/2-120,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);

          }
		  
          if(k<700){
          ireturn=guy_tinman(860,height/2-50-(k-700),70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          }if(k>700 && k<= 800){
          ireturn=guy_tinman(860,height/2-100,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          }if(k>800 && k<= 900){
          ireturn=guy_tinman(860,height/2-100+(k-800),70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          }if(k>900){
          ireturn=guy_tinman(860,height/2-50,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          }
          if(k<600){
          ireturn=soccer(width/2+50,height/2-50+(k-500),70, 60.0,(unsigned char)0,(unsigned char)0,(unsigned char)0,r,g,b,width,height);
          }else if(k<700){
          ireturn=soccer(width/2+50+(k-600),height/2-50-(k-650),70, 60.0,(unsigned char)0,(unsigned char)0,(unsigned char)0,r,g,b,width,height);
          }else if(k<800){
          ireturn=soccer(width/2+150,height/2-100+(k-700),70, 60.0,(unsigned char)0,(unsigned char)0,(unsigned char)0,r,g,b,width,height);
          }else{
          ireturn=soccer(width/2+130+(7*(k-800)),height/2,70, 60.0,(unsigned char)0,(unsigned char)0,(unsigned char)0,r,g,b,width,height);
          }

          }
          if(k>=900 && k<1100){

          ireturn=guy_tinman(500,height/2-30,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=guy_tinman(400,height/2+90,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=guy_tinman(860,height/2-120,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=guy_tinman(860,height/2-50,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=girl_tinman(630-2*(k-900),height/2-70,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(530-2*(k-900),height/2+80,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(330-(k-900),height/2-140,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(100,height/2-50,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);

          }
		  
		  if(k>=1100 && k<1150){
          ireturn=guy_tinman(500,height/2-30,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=guy_tinman(400,height/2+90,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=guy_tinman(860,height/2-120,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=guy_tinman(860,height/2-50,70, 60.0,(unsigned char)172,(unsigned char)112,(unsigned char)61,r,g,b,width,height);
          ireturn=girl_tinman(230-(k-1100),height/2-70,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(130,height/2+80-(k-1100),70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(130,height/2-140,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          ireturn=girl_tinman(100,height/2-50,70, 60.0,(unsigned char)228,(unsigned char)153,(unsigned char)105,r,g,b,width,height);
          }
          }





     // don't close loop using 'k' over num_images, cause we have to write out the frame

/////////////////////////////////////////////////////////////////////
///////////////       End of movie frame      ////////////
/////////////////////////////////////////////////////////////////////

     // compute the Y-pixels from the RGB values
	 for(i=0; i<height; i++){
	   for(j=0; j<width; j++){
		 ytmp = (int)(   0.299*(float)(*(r+j+i*width))
			  +0.587*(float)(*(g+j+i*width))+0.114*(float)(*(b+j+i*width))  );
		 *(y+j+i*width) = (unsigned char)(ytmp);
	 } }
     // compute the sub-sampled (4:2:0) UV from RGB
	 for(i=0; i<height/2; i++){
	   for(j=0; j<width/2; j++){
		 usum = (float)0.0;
		 vsum = (float)0.0;
		 for(i1=0; i1<2; i1++){
		   itmp = (i1+i*2)*width;
		   for(j1=0; j1<2; j1++){
                                                 jtmp = j1+j*2+itmp;
			 usum +=  (float)(-0.169*(float)(*(r+jtmp))-0.331*(float)(*(g+jtmp))+0.500*(float)(*(b+jtmp)));
			 vsum += (float)(0.500*(float)(*(r+jtmp))-0.419*(float)(*(g+jtmp))-0.081*(float)(*(b+jtmp)));
		 } }
         		*(u+j+i*width/2) = (unsigned char)(usum/(4.0)+128.0);
		 *(v+j+i*width/2) = (unsigned char)(vsum/(4.0)+128.0);
	 } }
     /////////////////////////////////////////////////////////////////////
     // write out the kth frame of the video
	 // ::::::::::::::::::::::::::::::::::::::::::::::::::::
	 //  generate filename for the kth image.
	 sprintf(file_name_out,"%s\\%s%d.yuv",directory,basename,k);
                 printf("writing YUV image to %s\n",file_name_out);
	 // open a file for writing. If unable to open - then exit program.
	 fd_out = _open(file_name_out,O_WRONLY|_O_BINARY|_O_CREAT,_S_IWRITE);
                 if(fd_out == -1){printf(" unable to open %s for output. Exitting program.\n",file_name_out); exit(-1);}
     // write image to file
	 if( (num_written = write(fd_out,y,width*height)) != width*height){
		printf("wrote %d instead of %d bytes.\n",num_written,width*height);
	 }
	 if( (num_written = write(fd_out,u,width*height/4)) != width*height/4){
		printf("wrote %d instead of %d bytes.\n",num_written,width*height/4);
	 }
	 if( (num_written = write(fd_out,v,width*height/4)) != width*height/4){
		printf("wrote %d instead of %d bytes.\n",num_written,width*height/4);
	 }
	 close(fd_out);

               } // done with kth image

	return 0;
}
/////////////////////////////////////////////////////////////////////////////////
// set the background color
// r,g,b,width and height are global vaiables defined at the top of this program,
//  so this subroutine can use them
void background(unsigned char rcolor, unsigned char gcolor, unsigned char bcolor, int width, int height,
				unsigned char * r, unsigned char * g, unsigned char * b)
{
       int i,j;
	 for(i=0; i<height; i++){
	   for(j=0; j<width; j++){
		 *(r+j+i*width) = (unsigned char)rcolor;
         *(g+j+i*width) = (unsigned char)gcolor;
         *(b+j+i*width) = (unsigned char)bcolor;
	 } }
}

/////////////////////////////////////////////////////////////////////////////////
// Draw a rectangle of color (red,green,blue) in the image starting at lower-left-pixel (lower_x,lower_y)
//  and ending at upper-right-pixel (lower_x+r_width-1, lower_y-r_height+1)
// The rectangle can be tilted by choosing a non-zero tilt-angle angle_deg
int rectangle(int lower_x, int lower_y, int r_width, int r_height, float angle_deg, unsigned char red,
	unsigned char green, unsigned char blue, unsigned char * r, unsigned char * g, unsigned char * b,
	int image_width, int image_height)
{
  int i,j,i_rot,j_rot,i_sub,j_sub;
  float angle_rad,cosa,sina,x_rot,y_rot;
  //upper_x=lower_x; upper_y=lower_y-r_height+1;
  angle_rad= -(float)(3.14159265359*angle_deg/180.0);
  cosa=(float)cos(angle_rad);
  sina=(float)sin(angle_rad);
  for(i_rot=0; i_rot<r_height; i_rot++){  // iterate over the image rows that contain the rectangle
	for(j_rot=0; j_rot<r_width; j_rot++){ // iterate over the image columns that contain the rectangle
 	  for(i_sub=0; i_sub<2; i_sub++){ // iterate over 2 samples per pixel in the vert direction
		for(j_sub=0; j_sub<2; j_sub++){ // iterate over 2 samples per pixel in the horiz direction
                                  // form the x,y location of the sample  in object-oriented coordinates x_rot,y_rot
		   y_rot=(float)(-r_height+1+i_rot+0.25+0.5*i_sub);
		   x_rot=(float)(j_rot+0.25+0.5*j_sub);
		   // form the i,j pixel in the un-rotated coordinates
		   j= (int)(lower_x+x_rot*cosa-y_rot*sina);
		   i= (int)(lower_y+x_rot*sina+y_rot*cosa);
                                  if(i>=0 && i<image_height){ // check to be sure that i'th row is inside the image
		     if(j>=0 && j<image_width){ // check to be sure that the j'th col is inside the image
			   (*(r+j+i*image_width))=(unsigned char)red;
                                                   (*(g+j+i*image_width))=(unsigned char)green;
			   (*(b+j+i*image_width))=(unsigned char)blue;
  } } } } } }

  return 0;

}

/////////////////////////////////////////////////////////////////////////////////
// draw an ellipse of color (red,green,blue) in the image starting at lower-left-pixel (lower_x,lower_y)
//  and ending at upper-right-pixel (lower_x+r_width-1, lower_y-r_height+1)
// If the defined rectangle is a square, then the "ellipse" is a circle.
int ellipse(int lower_x, int lower_y, int r_width, int r_height, float angle_deg, unsigned char red,
	unsigned char green, unsigned char blue, unsigned char * r, unsigned char * g, unsigned char * b,
	int image_width, int image_height)
{
  int i,j,i_rot,j_rot,i_sub,j_sub;
  float angle_rad,cosa,sina,x_rot,y_rot,radius_x,radius_y,xtmp,ytmp;
  radius_x=0.5*r_width-0.999;
  radius_y=0.5*r_height-0.999;
  angle_rad= -(float)(3.14159265359*angle_deg/180.0);
  cosa=(float)cos(angle_rad); sina=(float)sin(angle_rad);
  for(i_rot=0; i_rot<r_height; i_rot++){  // iterate over the image rows that contain the rectangle
	for(j_rot=0; j_rot<r_width; j_rot++){ // iterate over the image columns that contain the rectangle
 	  for(i_sub=0; i_sub<2; i_sub++){ // iterate over 2 samples per pixel in the vert direction
		for(j_sub=0; j_sub<2; j_sub++){ // iterate over 2 samples per pixel in the horiz direction
                                   // form the x,y location of the sample  in object-oriented coordinates x_rot,y_rot
		   y_rot=(float)(-r_height+1+i_rot+0.25+0.5*i_sub);
		   x_rot=(float)(j_rot+0.25+0.5*j_sub);
		   xtmp=(x_rot-radius_x)/radius_x;
		   ytmp=(y_rot+radius_y)/radius_y;
		   if(xtmp*xtmp+ytmp*ytmp<1.0){
		     // assign the i,j pixel in the un-rotated coordinates to the indicated color
			 j= (int)(lower_x+x_rot*cosa-y_rot*sina);
		     i= (int)(lower_y+x_rot*sina+y_rot*cosa);
             //
             if(i>=0 && i<image_height){ // check to be sure that i'th row is inside the image
		       if(j>=0 && j<image_width){ // check to be sure that the j'th col is inside the image
			     (*(r+j+i*image_width))=(unsigned char)red;
                 (*(g+j+i*image_width))=(unsigned char)green;
			     (*(b+j+i*image_width))=(unsigned char)blue;
  } } } } } } }

  return 0;

}
/////////////////////////////////////////////////////////////////////////////////
// Draw a triangle of color (red,green,blue) in the image
//  with the triangle base starting at lower-left pixel (lower_x,lower_y)
//  and ending at lower-right pixel (lower_x+r_width-1, lower_y)
//  and the top peak at pixel (lower_x+peak_x,lower_y-r_height+1)
int triangle(int lower_x, int lower_y, int r_width, int r_height, int peak_x,
			 float angle_deg, unsigned char red, unsigned char green, unsigned char blue,
			 unsigned char * r, unsigned char * g, unsigned char * b, int image_width, int image_height)
{
  int i,j,i_rot,j_rot,i_sub,j_sub;
  float angle_rad,cosa,sina,x_rot,y_rot,x1,x2;
  angle_rad= -(float)(3.14159265359*angle_deg/180.0);
  cosa=(float)cos(angle_rad); sina=(float)sin(angle_rad);
  for(i_rot=0; i_rot<r_height; i_rot++){  // iterate over the image rows that contain the triangle
     for(j_rot=0; j_rot<r_width; j_rot++){ // iterate over the image columns that contain the triangle
        for(i_sub=0; i_sub<2; i_sub++){ // iterate over 2 samples per pixel in the vert direction
           for(j_sub=0; j_sub<2; j_sub++){ // iterate over 2 samples per pixel in the horiz direction
                                 // form the x,y location of the sample  in object-oriented coordinates x_rot,y_rot
		   y_rot=(float)(-r_height+1+i_rot+0.25+0.5*i_sub);
		   x_rot=(float)(j_rot+0.25+0.5*j_sub);
                                    x1=(float)( y_rot*peak_x/(-r_height+1.0));  // compute the left-most x-value of the triangle at y location y_rot
		    x2=(float)( peak_x*y_rot/(-r_height+1.0) +(r_width-1.0)*(1.0-y_rot/(-r_height+1.0)));  // compute the right-most x-value of the triangle at y location y_rot
		   if( x_rot>= x1  && x_rot<= +x2){ // then the sample is within the triangle
		     // assign the i,j pixel in the un-rotated coordinates to the indicated color
	                      j= (int)(lower_x+x_rot*cosa-y_rot*sina);
		     i= (int)(lower_y+x_rot*sina+y_rot*cosa);
                                     if(i>=0 && i<image_height){ // check to be sure that i'th row is inside the image
		       if(j>=0 && j<image_width){ // check to be sure that the j'th col is inside the image
			     (*(r+j+i*image_width))=(unsigned char)red;
                 (*(g+j+i*image_width))=(unsigned char)green;
			     (*(b+j+i*image_width))=(unsigned char)blue;
  } } } } } } }

  return 0;

}


/////////////////////////////////////////////////////////////////////////////////
//
// a simple subroutine to draw a 1-pixel wide line.
//  the angle of the line is determined by the two endpoints (pnt1_x, pnt1_y) and (pnt2_x,pnt2_y)

int line(int  pnt1_x, int pnt1_y, int pnt2_x, int pnt2_y, unsigned char red,
	unsigned char green, unsigned char blue, unsigned char * r, unsigned char * g, unsigned
             char * b,  int image_width, int image_height)
{
	int i,ix,iy,num_steps;
	float dist,del_x,del_y;

	// compute distance (in units of pixel-widths) between the two endpoints
    dist = sqrt((pnt2_x - pnt1_x)* (pnt2_x - pnt1_x)+(pnt2_y - pnt1_y)* (pnt2_y - pnt1_y));
	// use approximately 3 samples per pixel-width,
    num_steps = (int)(3*dist+0.5);
	// compute the stepsize
    del_x= (pnt2_x - pnt1_x)/(num_steps-1.0);
    del_y= (pnt2_y - pnt1_y)/(num_steps-1.0);
    for(i=0; i<num_steps; i++){
      ix=(int)(pnt1_x+0.5+i*del_x);
      iy=(int)(pnt1_y+0.5+i*del_y);
      if(ix>=0 && iy >= 0 && ix < image_width && iy < image_height){
         (*(r+ix+iy*image_width))=red;
         (*(g+ix+iy*image_width))=green;
         (*(b+ix+iy*image_width))=blue;
	} }
    return 0;
}

int soccer(int upper_x, int upper_y, int r_height, float angle_deg,
		   unsigned char red, unsigned char green, unsigned char blue,
		   unsigned char * r, unsigned char * g, unsigned char * b,
		   int image_width, int image_height)
{
  int ireturn;
     // face
	 ireturn=ellipse(upper_x-6,upper_y+31,16,20,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     //left eye
     ireturn=ellipse(upper_x-3,upper_y+20,5,5,0.0,(unsigned char)0,(unsigned char)0,(unsigned char)0,
	         r,g,b,image_width,image_height);
	 // right eye
	 ireturn=ellipse(upper_x+3,upper_y+20,5,5,0.0,(unsigned char)0,(unsigned char)0,(unsigned char)0,
	         r,g,b,image_width,image_height);
     ireturn=ellipse(upper_x,upper_y+23,5,5,0.0,(unsigned char)0,(unsigned char)0,(unsigned char)0,
	         r,g,b,image_width,image_height);

     ireturn=ellipse(upper_x-3,upper_y+26,5,5,0.0,(unsigned char)0,(unsigned char)0,(unsigned char)0,
	         r,g,b,image_width,image_height);
	 // right eye
	 ireturn=ellipse(upper_x+3,upper_y+26,5,5,0.0,(unsigned char)0,(unsigned char)0,(unsigned char)0,
	         r,g,b,image_width,image_height);
   return 0;

}


////////////////////////////////////////////
int girl_tinman(int upper_x, int upper_y, int r_height, float angle_deg,
		   unsigned char red, unsigned char green, unsigned char blue,
		   unsigned char * r, unsigned char * g, unsigned char * b,
		   int image_width, int image_height)
{
  int ireturn;

     // face
	 ireturn=ellipse(upper_x-6,upper_y+31,16,20,0.0,red,green,blue,
	         r,g,b,image_width,image_height);
	 // left eye
	 ireturn=ellipse(upper_x-3,upper_y+20,4,5,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
	 // right eye
	 ireturn=ellipse(upper_x+3,upper_y+20,4,5,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     // nose
	 ireturn=triangle(upper_x-2,upper_y+25,5,4,2,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     // hat
	 ireturn=triangle(upper_x-9,upper_y+15,21,11,11,0.0,(unsigned char)215,(unsigned char)226,(unsigned char)55,
	         r,g,b,image_width,image_height);
     // neck
     ireturn=rectangle(upper_x-2,upper_y+32,7,7,0.0,red,green,blue,
	         r,g,b,image_width,image_height);
     // body
     ireturn=rectangle(upper_x-10,upper_y+72,23,40,0.0,(unsigned char)215,(unsigned char)226,(unsigned char)55,
	         r,g,b,image_width,image_height);
	 // mouth
     ireturn=rectangle(upper_x-2,upper_y+26,5,1,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     //left leg
     ireturn=rectangle(upper_x-7,upper_y+90,5,18,0.0,(unsigned char)215,(unsigned char)226,(unsigned char)55,
	         r,g,b,image_width,image_height);
    //right leg
    ireturn=rectangle(upper_x+5,upper_y+90,5,18,0.0,(unsigned char)215,(unsigned char)226,(unsigned char)55,
	         r,g,b,image_width,image_height);
    ireturn=line(upper_x-10,upper_y+42,upper_x-17,upper_y+55,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
    ireturn=line(upper_x+13,upper_y+42,upper_x+20,upper_y+55,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
  return 0;

}
int guy_tinman(int upper_x, int upper_y, int r_height, float angle_deg,
		   unsigned char red, unsigned char green, unsigned char blue,
		   unsigned char * r, unsigned char * g, unsigned char * b,
		   int image_width, int image_height)
{
  int ireturn;

     // face
	 ireturn=ellipse(upper_x-6,upper_y+31,16,20,0.0,red,green,blue,
	         r,g,b,image_width,image_height);
	 // left eye
	 ireturn=ellipse(upper_x-3,upper_y+20,4,5,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
	 // right eye
	 ireturn=ellipse(upper_x+3,upper_y+20,4,5,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     // nose
	 ireturn=triangle(upper_x-2,upper_y+25,5,4,2,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     // hat
	 ireturn=triangle(upper_x-9,upper_y+15,21,11,11,0.0,(unsigned char)243,(unsigned char)150,(unsigned char)237,
	         r,g,b,image_width,image_height);
     // neck
     ireturn=rectangle(upper_x-2,upper_y+32,7,7,0.0,red,green,blue,
	         r,g,b,image_width,image_height);
     // body
     ireturn=rectangle(upper_x-10,upper_y+72,23,40,0.0,(unsigned char)243,(unsigned char)150,(unsigned char)237,
	         r,g,b,image_width,image_height);
	 // mouth
     ireturn=rectangle(upper_x-2,upper_y+26,5,1,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     //left leg
     ireturn=rectangle(upper_x-7,upper_y+87,5,18,0.0,(unsigned char)243,(unsigned char)150,(unsigned char)237,
	         r,g,b,image_width,image_height);
     //right leg
     ireturn=rectangle(upper_x+5,upper_y+87,5,18,0.0,(unsigned char)243,(unsigned char)150,(unsigned char)237,
	         r,g,b,image_width,image_height);
     ireturn=line(upper_x-10,upper_y+42,upper_x-17,upper_y+55,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     ireturn=line(upper_x+13,upper_y+42,upper_x+20,upper_y+55,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     //skirt
     ireturn=triangle(upper_x-16,upper_y+75,40,18,18,0.0,(unsigned char)255,(unsigned char)0,(unsigned char)0,
	         r,g,b,image_width,image_height);


  return 0;

}

int soccerGround(int upper_x, int upper_y, int r_height, float angle_deg,
		   unsigned char red, unsigned char green, unsigned char blue,
		   unsigned char * r, unsigned char * g, unsigned char * b,
		   int image_width, int image_height)
{
  int ireturn;
     // Left Goal post
     ireturn=rectangle(upper_x,upper_y,15,120,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     ireturn=rectangle(upper_x,upper_y,45,15,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     ireturn=rectangle(upper_x,upper_y-120,45,15,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);

     //Right goal post
     ireturn=rectangle(upper_x-855,upper_y,15,120,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     ireturn=rectangle(upper_x-885,upper_y,45,15,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     ireturn=rectangle(upper_x-885,upper_y-120,45,15,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
    //left off side ox
     ireturn=rectangle(upper_x-80,upper_y+128,3,370,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     ireturn=rectangle(upper_x-80,upper_y+128,125,3,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     ireturn=rectangle(upper_x-80,upper_y-240,125,3,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     //right off side box
     ireturn=rectangle(upper_x-760,upper_y+128,3,370,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     ireturn=rectangle(upper_x-885,upper_y+128,125,3,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     ireturn=rectangle(upper_x-885,upper_y-240,125,3,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     //Ground border
     ireturn=rectangle(upper_x-888,upper_y+260,3,610,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     ireturn=rectangle(upper_x-888,upper_y+260,935,3,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     ireturn=rectangle(upper_x+45,upper_y+260,3,610,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     ireturn=rectangle(upper_x-888,upper_y-350,935,3,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     //Mid line
     ireturn=rectangle(upper_x-435,upper_y+260,3,610,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
	         r,g,b,image_width,image_height);
     //Center circle
     ireturn=arc(3,360.0,upper_x-515,upper_y+15,170,170,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
             r,g,b,image_width,image_height);
     //Corner arcs right-top
     ireturn=arc(3,90.0,upper_x-916,upper_y-320,60,60,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
             r,g,b,image_width,image_height);
    //Corner arcs right-down
     ireturn=arc(3,90.0,upper_x-858,upper_y+288,60,60,90.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
             r,g,b,image_width,image_height);
    //Corner arcs left-down
     ireturn=arc(3,90.0,upper_x+75,upper_y+230,60,60,180.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
             r,g,b,image_width,image_height);
    //Corner arcs left-top
     ireturn=arc(3,90.0,upper_x+18,upper_y-380,60,60,270.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,
             r,g,b,image_width,image_height);
/*
     ireturn=arc(3,45.0,upper_x/2-128,upper_y/2+160,160,160,0.0,(unsigned char)0,(unsigned char)255,(unsigned char)0,
             r,g,b,image_width,image_height);
     ireturn=arc(3,45.0,upper_x/2+184,upper_y/2,160,160,180.0,(unsigned char)0,(unsigned char)0,(unsigned char)0,
             r,g,b,image_width,image_height);*/


  return 0;

}

/////////////////////////////////////////////////////////////////////////////////
// draw an arc of an ellipse of thickness ipix_wide and color (red,green,blue) that fits in the rectangle with lower-left-pixel (lower_x,lower_y)
//  and ending at upper-right-pixel (lower_x+r_width-1, lower_y-r_height+1)
// If the defined rectangle is a square, then the "ellipse" is a circle.
int arc(int ipix_wide,float arc_length_deg,int lower_x, int lower_y, int r_width, int r_height, float angle_deg, unsigned char red,
	unsigned char green, unsigned char blue, unsigned char * r, unsigned char * g, unsigned char * b,
	int image_width, int image_height)
{
  int i,j,i_rot,j_rot,i_sub,j_sub;
  float arc_angle_rad,angle_rad,cosa,sina,x_rot,y_rot,radius_x1,radius_y1,radius_x2,radius_y2,xtmp1,ytmp1,xtmp2,ytmp2,arc_length_rad;
  radius_x1=0.5*r_width-0.999;
  radius_y1=0.5*r_height-0.999;
  radius_x2=0.5*(r_width-2.0*ipix_wide)-0.999;
  radius_y2=0.5*(r_height-2.0*ipix_wide)-0.999;
  angle_rad= -(float)(3.14159265359*angle_deg/180.0);
  arc_length_rad = (float)(3.14159265359*arc_length_deg/180.0);
  cosa=(float)cos(angle_rad);   sina=(float)sin(angle_rad);
  for(i_rot=0; i_rot<r_height; i_rot++){  // iterate over the image rows that contain the rectangle
     for(j_rot=0; j_rot<r_width; j_rot++){ // iterate over the image columns that contain the rectangle
        for(i_sub=0; i_sub<2; i_sub++){ // iterate over 2 samples per pixel in the vert direction
           for(j_sub=0; j_sub<2; j_sub++){ // iterate over 2 samples per pixel in the horiz direction
               // form the x,y location of the sample  in object-oriented coordinates x_rot,y_rot
	            y_rot=(float)(-r_height+1+i_rot+0.25+0.5*i_sub);
	            x_rot=(float)(j_rot+0.25+0.5*j_sub);
				arc_angle_rad=atan2(y_rot+0.5*r_height,x_rot-0.5*r_width);
				if(arc_angle_rad<0.0)arc_angle_rad += 2.0*3.14159265359;
				if(arc_angle_rad >= 0.0 && arc_angle_rad <= arc_length_rad){  // arc_length_rad
                  xtmp1=(x_rot-radius_x1)/radius_x1;
	              ytmp1=(y_rot+radius_y1)/radius_y1;
				  xtmp2=(x_rot-ipix_wide-radius_x2)/radius_x2;
	              ytmp2=(y_rot+ipix_wide+radius_y2)/radius_y2;
                  if(xtmp1*xtmp1+ytmp1*ytmp1<=1.0 && xtmp2*xtmp2+ytmp2*ytmp2>=1.0){
	              // assign the i,j pixel in the un-rotated coordinates to the indicated color
	               j= (int)(lower_x+x_rot*cosa-y_rot*sina);
	               i= (int)(lower_y+x_rot*sina+y_rot*cosa);
                    //
                    if(i>=0 && i<image_height){ // check to be sure that i'th row is inside the image
                       if(j>=0 && j<image_width){ // check to be sure that the j'th col is inside the image
	                         (*(r+j+i*image_width))=(unsigned char)red;
                            (*(g+j+i*image_width))=(unsigned char)green;
	                        (*(b+j+i*image_width))=(unsigned char)blue;
					} }
				} }
	 } } } }

  return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// ******* Subroutine for #1,#2,#3*********
//
// USES these other subroutines:
//
//int rectangle(int lower_x, int lower_y, int r_width, int r_height, float angle_deg, unsigned char red,
//	unsigned char green, unsigned char blue, unsigned char * r, unsigned char * g, unsigned char * b,
//	int image_width, int image_height)
/////////////////////////////////////////////////////////////////////////////////////////////////

int number1(int lower_x, int lower_y, float angle_deg,
		   unsigned char * r, unsigned char * g, unsigned char * b,
		   int image_width, int image_height)
{
          int ireturn;

          //number1
          ireturn=rectangle(lower_x,lower_y,150,35,90.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,r,g,b,960,640);

          return 0;
}

int number2(int lower_x, int lower_y, float angle_deg,
		   unsigned char * r, unsigned char * g, unsigned char * b,
		   int image_width, int image_height)
{
          int ireturn;

          ireturn=rectangle(lower_x,lower_y-70,75,35,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,r,g,b,960,640);
          ireturn=rectangle(lower_x,lower_y,75,35,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,r,g,b,960,640);
          ireturn=rectangle(lower_x + 75,lower_y,75,35,90.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,r,g,b,960,640);
          ireturn=rectangle(lower_x+35,lower_y+42,75,35,90.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,r,g,b,960,640);
          ireturn=rectangle(lower_x,lower_y+70,75,35,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,r,g,b,960,640);

          return 0;
}

int number3(int lower_x, int lower_y, float angle_deg,
		   unsigned char * r, unsigned char * g, unsigned char * b,
		   int image_width, int image_height)
{
          int ireturn;

          ireturn=rectangle(lower_x,lower_y,75,35,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,r,g,b,960,640);
          ireturn=rectangle(lower_x + 75,lower_y,150,35,90.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,r,g,b,960,640);
          ireturn=rectangle(lower_x,lower_y - 150,75,35,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,r,g,b,960,640);
          ireturn=rectangle(lower_x,lower_y-75,75,35,0.0,(unsigned char)255,(unsigned char)255,(unsigned char)255,r,g,b,960,640);

          return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


