// Rotating and scaled plane waves, ripples and spheres.
// Tidy up: removed some factory data, beautified, removed white lines

#include <REG52.H>
#include <intrins.h>
// #include <math.h>
//#include <stdlib.h>
#define uchar unsigned char
#define uint unsigned int
uchar display[8][8];

/* sine lookup table */
uchar code sinTab[256]={128,131,134,137,140,143,146,149,152,155,158,162,165,167,170,173,176,179,182,185,188,190,193,196,198,201,203,206,208,211,213,215,218,220,222,224,226,228,230,232,234,235,237,238,240,241,243,244,245,246,248,249,250,250,251,252,253,253,254,254,254,255,255,255,255,255,255,255,254,254,254,253,253,252,251,250,250,249,248,246,245,244,243,241,240,238,237,235,234,232,230,228,226,224,222,220,218,215,213,211,208,206,203,201,198,196,193,190,188,185,182,179,176,173,170,167,165,162,158,155,152,149,146,143,140,137,134,131,128,124,121,118,115,112,109,106,103,100,97,93,90,88,85,82,79,76,73,70,67,65,62,59,57,54,52,49,47,44,42,40,37,35,33,31,29,27,25,23,21,20,18,17,15,14,12,11,10,9,7,6,5,5,4,3,2,2,1,1,1,0,0,0,0,0,0,0,1,1,1,2,2,3,4,5,5,6,7,9,10,11,12,14,15,17,18,20,21,23,25,27,29,31,33,35,37,40,42,44,47,49,52,54,57,59,62,65,67,70,73,76,79,82,85,88,90,93,97,100,103,106,109,112,115,118,121,124};

/*initializtion
   That is to initialize the program .
   It is write to set the timer in c52 mcu.
   So the program can renovate the led_3d_cube in fixed time use the interrupt function.*/
void sinter()
{
	IE=0x82;
	TCON=0x01;
	TH0=0xc0;
	TL0=0;
	TR0=1;
}
void delay5us(void)   //���� -0.026765046296us STC 1T 22.1184Mhz
{
	unsigned char a,b;
	for(b=3; b>0; b--)
		for(a=2; a>0; a--);
}
void delay(uint i)
{
	while (i--) {
		delay5us();
	}            //12t��mcu ע��������ʱ����
}
/*To judge the num bit*/
uchar judgebit(uchar num,uchar b)
{
	char n;
	num=num&(1<<b);
	if (num)
		n=1;
	else
		n=0;
	return n;
}

/*To figure out the absolute value*/
uchar abss(char a)
{
	if (a<0)
		a=-a;
	return a;
}

void clear(char le)
{
	uchar i,j;
	for (j=0; j<8; j++)
	{
		for (i=0; i<8; i++)
			display[j][i]=le;
	}
}
void point(uchar x,uchar y,uchar z,uchar le)
{
	uchar ch1,ch0;
	ch1=1<<x;
	ch0=~ch1;
	if (le)
		display[z][y]=display[z][y]|ch1;
	else
		display[z][y]=display[z][y]&ch0;
}
uchar sinT(uchar x){
	return sinTab[x];
}
uchar cosT(uchar x){
	x=x-64;
	return sinTab[x];
}
/*
   rotate display around  axis (ax)
   d is number of rots. -ve for anti clockwise
   di is pseudo-degree interval (256 degs per rot.)
   t is delay between rots.
   ax is axis 0=z,1=x,2=y
 */
void rotateDisplay(char d,uchar di, uchar dt,uchar ax)
{
	uchar n;
	uchar data d0[8][8];
	char xr,yr,zr,x,y,z,si,ci,xt,yt,zt;
	int i;
	uchar code x0=7;     //2 times x centre of rot (3.5 for cube centre)
	uchar code y0=7;
	uchar code z0=7;
	for(y=0; y<8; y++) {
		for(z=0; z<8; z++) {
			d0[z][y]=display[z][y];
		}
	}
	for (n=0; n<abss(d); n++) {
		for (i=0; i<255; i+=di) {
			if(d<0) {
				si=(sinT(i)-128);
				ci=(cosT(i)-128);
			}
			else{
				si=(sinT(-i)-128);
				ci=(cosT(-i)-128);
			}
			clear(0);
			switch(ax) {
			case (0):
				for(x=0; x<8; x++) {
					for(y=0; y<8; y++) {
						xt=2*x-x0;
						yt=2*y-y0;
						xr=((-(xt*ci)+(yt*si))/128+x0)/2;
						yr=((-(xt*si)-(yt*ci))/128+y0)/2;
						for(z=0; z<8; z++) {
							if(judgebit(d0[z][y],x)) {
								if(xr>=0&&yr>=0) {
									point(xr,yr,z,1);
								}
							}
						}
					}
				}
				delay(dt*100);
				break;
			case (1):
				for(x=0; x<8; x++) {
					for(z=0; z<8; z++) {
						xt=2*x-x0;
						zt=2*z-z0;
						xr=((-(xt*ci)+(zt*si))/128+x0)/2;
						zr=((-(xt*si)-(zt*ci))/128+z0)/2;
						for(y=0; y<8; y++) {
							if(judgebit(d0[z][y],x)) {
								if(xr>=0&&zr>=0) {
									point(xr,y,zr,1);
								}
							}
						}
					}
				}
				delay(dt*100);
				break;
			case (2):
				for(y=0; y<8; y++) {
					for(z=0; z<8; z++) {
						yt=2*y-y0;
						zt=2*z-z0;
						yr=((-(yt*ci)+(zt*si))/128+y0)/2;
						zr=((-(yt*si)-(zt*ci))/128+z0)/2;
						for(x=0; x<8; x++) {
							if(judgebit(d0[z][y],x)) {
								if(yr>=0&&zr>=0) {
									point(x,yr,zr,1);
								}
							}
						}
					}
				}
				delay(dt*100);
				break;
			}
		}
		for(y=0; y<8; y++) {
			for(z=0; z<8; z++) {
				display[z][y]=d0[z][y];
			}
		}
	}
}

void flash_wave(uchar tt,uchar km,uchar lm,uchar tm,uchar dim) {
	uchar x,y;
	unsigned short int t;
	int k,l;
	//short int rt=(3*rand()%tt)/2;
	for (t=0; t<tt; t++) {
		delay(5000);
		k=(sinT(t*2)-128)/km;
		l=(sinT(t*2 -64)-128)/lm;
		clear(0);
		for(x=0; x<8; x++) {
			for(y=0; y<8; y++) {
				switch(dim) {
				case (0):
					point(x,y,sinT(k*x+l*y-tm*t)/32,1);
					break;
				case (1):
					point(x,sinT(k*x+l*y-tm*t)/32,y,1);
					break;
				case (2):
					point(sinT(k*x+l*y-tm*t)/32,x,y,1);
					break;
				}
			}
		}
		if(t==128) {
			delay(60000);
			rotateDisplay(3,10,50,rand()%3);
			delay(60000);
		}
	}
}
void flash_spheres(uchar nsp) {
	uchar x0,y0,z0,x1,y1,z1,x2,y2,z2,d,dd,x,y,z,n,this,last,mr;
	for(n=0; n<nsp; n++) {
		mr=rand()%6+4;         //max radius
		//final centre point
		x2=rand();
		x2=x2%8;
		y2=rand();
		y2=y2%8;
		z2=rand();
		z2=z2%8;
		//start centre point
		x1=rand();
		x1=x1%8;
		y1=rand();
		y1=y1%8;
		z1=rand();
		z1=z1%8;
		for(dd=0; dd<16; dd++) {
			//centre point
			x0=x1+((x2-x1)*dd)/16;
			y0=y1+((y2-y1)*dd)/16;
			z0=z1+((z2-z1)*dd)/16;
			//set radius d
			if(dd>8) {
				d=(16-dd)*mr/8;
			}
			else {
				d=dd*mr/8;
			}
			//display spherical shell
			for(x=0; x<8; x++) {
				for(y=0; y<8; y++) {
					for(z=0; z<8; z++) {
						this=(x-x0)*(x-x0)+(y-y0)*(y-y0)+(z-z0)*(z-z0)<d*d;
						last=(x-x0)*(x-x0)+(y-y0)*(y-y0)+(z-z0)*(z-z0)<(d-1)*(d-1);
						point(x,y,z,this);
						if(last) {
							point(x,y,z,0);
						}
					}
				}
			}
			delay(2000);
			/* if(dd==8){
			   rotateDisplay(1,10,50,rand()%3);
			   } */
		}
	}
}
void flash_ripple(uchar tt,uchar tm,uchar dim) {
	uchar x,y,k,r;
	unsigned short int t;
	short int rt=(3*rand()%tt)/2;
	uchar x0;
	uchar y0;
	x0=rand()%14;
	y0=rand()%14;
	k=5+rand()%8;
	for (t=0; t<tt; t++) {
		delay(5000);
		clear(0);
		for(x=0; x<8; x++) {
			for(y=0; y<8; y++) {
				r= ((2*x-x0)*(2*x-x0)+(2*y-y0)*(2*y-y0))/8;
				switch(dim) {
				case (0):
					point(x,y,(((40-r)*(sinT(k*r-tm*t)-(int)127)/16)/40+7)/2,1);
					break;
				case (1):
					point(x,(((40-r)*(sinT(k*r-tm*t)-(int)127)/16)/40+7)/2,y,1);
					break;
				case (2):
					point((((40-r)*(sinT(k*r-tm*t)-(int)127)/16)/40+7)/2,x,y,1);
					break;
				}
			}
		}
		if(t==128) {
			delay(60000);
			rotateDisplay(3,10,50,rand()%3);
			delay(60000);
		}
	}
}
void main()
{
	sinter();
	while(1) {
		/*play list*/
		switch(rand()%3) {
		case (0):
			flash_ripple(255,10+rand()%10,rand()%3);
			break;
		case (1):
			flash_wave(255,rand()%6+2,rand()%6+2,5+rand()%10,rand()&3);
			//flash_wave(255,7,7,14,0);
			break;
		case (2):
			flash_spheres(rand()%9+5);
			break;
		}
	}
}

void print() interrupt 1
{
	uchar i;
	static uchar layer=0;
	P1=0;
	for (i=0; i<8; i++)
	{
		P2=1<<i;
		delay(3);
		P0=display[layer][i];
		delay(3);
	}
	P1=1<<layer;
	if (layer<7)
		layer++;
	else
		layer=0;
	TH0=0xc0;
	TL0=0;
}
