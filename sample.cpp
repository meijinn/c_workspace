/********************************************************************
*                                                                   *
* HSMAC�@�ɂ��L���r�e�B�[�����R�Η��̃T���v���v���O����           *
*                                                                   *
********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define NX 20 /* NX:x�����i�q�� */
#define NY 20 /* NY:y�����i�q�� */
#define NX1 21 /* NX1=NX+1 */
#define NX2 22 /* NX2=NX+2 */
#define NY1 21 /* NY1=NY+1 */
#define NY2 22 /* NY2=NY+2 */
void cinit();
void adv();
void calvel();
void press();
void caltem();
void velbnd();
void tbnd();
void prout();
void output( char *fname_out);
double DX, DY, DT;
double VIS, ALP, BUO;
double RE, PR, GR, TIME, OMG, EPSP;
int  ICYCLE, ITR, IFLG, IRELP;
double DMAX;
int ITYPE;
char fname[10][80];
char *fname10;
FILE *in_10, *out_11, *out_12, *out_13, *out_14, *out_21;
FILE *in_15, *in_16, *in_17, *in_18;
double UO[NX1][NY2], UN[NX1][NY2], VO[NX2][NY1], VN[NX2][NY1];
double PO[NX2][NY2], TO[NX2][NY2], TN[NX2][NY2];
void main()
{
     int i,j,NITR,NCYCLE;
     double DLX,DLY;
     char buff[80];
     fname10="parameter.inc";
     strncpy(fname[0],fname10,13);
     in_10=fopen(fname[0],"r"); /*�p�����[�^�t�@�C���̃I�[�v��*/
     for (i=1;i<=9;i++){/*�o�̓t�@�C�����̓ǂݍ���*/
       fgets(buff, sizeof buff,in_10);
       for (j=0;buff[j]!=0;j++);
       strncpy(fname[i], buff, j-1);
     }
     out_11=fopen(fname[1],"wb");/*U�̌v�Z���ʏo�͗p�t�@�C���I�[�v��*/
     out_12=fopen(fname[2],"wb");/*V�̌v�Z���ʏo�͗p�t�@�C���I�[�v��*/
     out_13=fopen(fname[3],"wb");/*P�̌v�Z���ʏo�͗p�t�@�C���I�[�v��*/
     out_14=fopen(fname[4],"wb");/*T�̌v�Z���ʏo�͗p�t�@�C���I�[�v��*/
     fgets(buff, sizeof buff,in_10);/*parameter.inc���̃R�����g�s(10�s��)�̃X�L�b�v*/
     fgets(buff, sizeof buff,in_10);/*                   ��(11�s��)*/
     fgets(buff, sizeof buff,in_10);/*                   ��(12�s��)*/
     fgets(buff, sizeof buff,in_10);/*                   ��(13�s��)*/
     fgets(buff, sizeof buff,in_10);/*                   ��(14�s��)*/
     fgets(buff, sizeof buff,in_10);/*                   ��(15�s��)*/
     fscanf(in_10," %d %d %d %d ",&ITYPE,&ICYCLE,&NITR,&NCYCLE);
     fgets(buff, sizeof buff,in_10);/*parameter.inc���̃R�����g�s(17�s��)�̃X�L�b�v*/
     fgets(buff, sizeof buff,in_10);/*parameter.inc���̃R�����g�s(18�s��)�̃X�L�b�v*/
     fscanf(in_10," %lg %lg ",&EPSP,&OMG);
     fgets(buff, sizeof buff,in_10);/*parameter.inc���̃R�����g�s(20�s��)�̃X�L�b�v*/
     fgets(buff, sizeof buff,in_10);/*parameter.inc���̃R�����g�s(21�s��)�̃X�L�b�v*/
     fscanf(in_10," %lg %lg %lg %lg ",&DT,&RE,&PR,&GR);
     fgets(buff, sizeof buff,in_10);/*parameter.inc���̃R�����g�s(23�s��)�̃X�L�b�v*/
     fgets(buff, sizeof buff,in_10);/*parameter.inc���̃R�����g�s(24�s��)�̃X�L�b�v*/
     fscanf(in_10," %lg %lg %d",&DLX,&DLY,&IRELP);
     printf (" ITYPE = %d ICYCLE= %d NITR= %d NCYCLE= %d \n",
             ITYPE,ICYCLE,NITR,NCYCLE);
     printf(" EPSP= %12.3lE  OMG = %12.3lE \n",EPSP,OMG);
     printf(" DT = %12.3lE  RE = %12.3lE  PR = %12.3lE  GR = %12.3lE \n",DT,RE,PR,GR);
     printf(" DLX = %12.3lE  DLY = %12.3lE  IRELP = %d  \n",DLX,DLY,IRELP);
     if ( ICYCLE != 0 ){/*�p���̌v�Z�̏ꍇ*/
       in_15=fopen(fname[5],"rb");/*U�f�[�^�t�@�C���̃I�[�v��*/
       in_16=fopen(fname[6],"rb");/*V�f�[�^�t�@�C���̃I�[�v��*/
       in_17=fopen(fname[7],"rb");/*P�f�[�^�t�@�C���̃I�[�v��*/
       in_18=fopen(fname[8],"rb");/*T�f�[�^�t�@�C���̃I�[�v��*/
     }
     DX=DLX/(double)NX; DY=DLY/(double)NY;/*x,y�����̊i�q��DX,DY*/
     VIS=PR; ALP=1.0; BUO=( GR * ( PR*PR ) );
      /*VIS:�^�����������̊g�U���̌W��(�����ł�Pr)*/
      /*ALP:�G�l���M�[���������̊g�U���̌W��(�����ł�1)*/
      /*BUO:���͍��̌W��(�����ł� Gr * Pr**2)*/
     if ( ITYPE==1 ){/* ������Ȃ畂�͍��̌W�����[���ɐݒ� */
       BUO = 0.0;
     }
     cinit();/*�����l�̐ݒ�*/
     label_700:{};/*���Ԑi�s�̂��߂̖߂�_*/
     adv();/*���Ԑi�s*/
     calvel();/*���x��̌v�Z*/
     ITR=1;
     label_710:{};/*���͔����̂��߂̖߂�_*/
     IFLG=0;
     press();/*���̈��͏�̌v�Z*/
     if ( IFLG==0 ){/*Newton-Raphson�@�ɂ�鈳�͏�̌v�Z�����������Ƃ�*/
       if ( ITYPE==2 ){/*�񓙉���v�Z�̏ꍇ*/
         caltem();/*���x����v�Z*/
       }
     }
     if ( IFLG==1 ){/*���͏�̌v�Z���������Ă��Ȃ��Ƃ�*/
       if ( ITR<NITR ){/*���͌v�Z�̔����񐔂����炩���ߐݒ肳�ꂽ�ő�lNITR��菬�����Ƃ�*/
         ITR = ITR + 1;/*����ɔ������J��Ԃ�*/
         goto label_710;
       }
       else{/*���͌v�Z�̔����񐔂�NITR�ȏ�̂Ƃ����U�Ƃ݂Ȃ��Čv�Z�I��*/
         printf(" calculation has diverged \n");
         prout();
         goto label_900;
       }
     }
     if ( ICYCLE < NCYCLE ){/*���Ԑi�s�T�C�N��(ICYCLE)��NCYCLE��菬������*/
       goto label_700;
     }
     else{/*���Ԑi�s�T�C�N����NCYCLE�ɂȂ�����->�v�Z�I��*/
       prout();
     }
     label_900:{};
     output(fname[9]);/*�v�Z���ʂ̏o��*/
     fclose (in_10); fclose (out_11); fclose (out_12);
     fclose (out_13); fclose (out_14);
}
/*�����ݒ�*/
void cinit()
{
     int ix,iy;
     if ( ICYCLE == 0 ){/*�V�K�v�Z�̏ꍇ*/
       for (ix=0;ix<=NX;ix++){/*U�̏����l�ݒ�*/
         for (iy=0;iy<=NY+1;iy++){
           UN[ix][iy] = 0.0;
         }
       }
       for (ix=0;ix<=NX+1;ix++){/*V�̏����l�ݒ�*/
         for (iy=0;iy<=NY;iy++){
           VN[ix][iy] = 0.0;
         }
       }
       for (ix=0;ix<=NX+1;ix++){/*P�̏����l�ݒ�*/
         for (iy=0;iy<=NY+1;iy++){
           PO[ix][iy] = 0.0;
         }
       }
       for (ix=0;ix<=NX+1;ix++){/*T�̏����l�ݒ�(�̈���͍���(+0.5)�ƒቷ(-0.5)�̒��ԉ��x)*/
         for (iy=0;iy<=NY+1;iy++){/*�i���Ӂj���͍��̌v�Z�ŉ��x�̔z����g�p����*/
           TN[ix][iy] = 0.0;/*����̂œ�����ł�T=0�Ƃ��ď������������͐ݒ肷��*/
         }/*�K�v������D�[���ȊO�̒l������ƕ��͍����v�Z�����\��������̂Œ��ӁD*/
       }
       for (iy=0;iy<=NY+1;iy++){/*T�̋��E�F�E���ǁi��p�jT=-0.5*/
         TN[NX+1][iy] = 2.0 * ( -0.5 ) - TN[NX][iy];
       }
       for (iy=0;iy<=NY+1;iy++){/*T�̋��E�F�����ǁi���M�jT=+0.5*/
         TN[0][iy] = 2.0 * ( +0.5 ) - TN[1][iy];
       }
       for (ix=1;ix<=NX;ix++){/*T�̋��E�F��ʁi�f�M�j*/
         TN[ix][NY+1] = TN[ix][NY];
       }
       for (ix=1;ix<=NX;ix++){/*T�̋��E�F���ʁi�f�M�j*/
         TN[ix][0] = TN[ix][1];
       }
     }
     else{/*�p���v�Z�i���łɂ���v�Z���ʂ���X�^�[�g�j�̏ꍇ*/
       /*U�f�[�^�t�@�C������̓ǂݍ���[Unit No.=15]*/
       fread(UN, sizeof(double), NX1*NY2, in_15);
       /*V�f�[�^�t�@�C������̓ǂݍ���[Unit No.=16]*/
       fread(VN, sizeof(double), NX2*NY1, in_16);
       /*P�f�[�^�t�@�C������̓ǂݍ���[Unit No.=17]*/
       fread(PO, sizeof(double), NX2*NY2, in_17);
       /*T�f�[�^�t�@�C������̓ǂݍ���[Unit No.=18]*/
       fread(TN, sizeof(double), NX2*NY2, in_18);
       fclose (in_15); fclose (in_16); fclose (in_17); fclose (in_18);
     }
}
/*���Ԑi�s*/
void adv()
{
     int ix,iy;
     TIME = DT*(double)ICYCLE; ICYCLE = ICYCLE + 1;
     if ( (ICYCLE%100) ==0 ){/*ICYCLE��100�񖈂ɕ\��*/
       printf ("  CYC = %8d \n",ICYCLE);
     }
     for (ix=0;ix<=NX;ix++){/* UN -> UO : �K�v�Ȃ����ւ���O��UN��UO����ϓ��ʂ����߂�*/
       for (iy=0;iy<=NY+1;iy++){/*UN:�O�̎��ԃX�e�b�v�ɂ����čŏI�I�ɓ���ꂽ�l�C���͕␳�̓x�ɍX�V�����*/
         UO[ix][iy] = UN[ix][iy];/*UO:�V�������ԃX�e�b�v�ł̏����l�DUN��ۑ��D*/
       }
     }
     for (ix=0;ix<=NX+1;ix++){/* VN -> VO : �K�v�Ȃ����ւ���O��VN��VO����ϓ��ʂ����߂�*/
       for (iy=0;iy<=NY;iy++){/*VN:�O�̎��ԃX�e�b�v�ɂ����čŏI�I�ɓ���ꂽ�l�C���͕␳�̓x�ɍX�V�����*/
         VO[ix][iy] = VN[ix][iy];/*VO:�V�������ԃX�e�b�v�ł̏����l�DVN��ۑ��D*/
       }
     }
     for (ix=0;ix<=NX+1;ix++){/* TN -> TO : �K�v�Ȃ����ւ���O��TN��TO����ϓ��ʂ����߂�*/
       for (iy=0;iy<=NY+1;iy++){/*TN:�O�̎��ԃX�e�b�v�ł̌v�Z�l*/
         TO[ix][iy] = TN[ix][iy];/*TO:�V�������ԃX�e�b�v�ł̏����l�DTN��ۑ��D*/
       }
     }
}
/*���x��̌v�Z*/
void calvel()
{
     int ix,iy;
     double vv,cnvux,cnvuy,buou,difu;
     double uu,cnvvx,cnvvy,tv,buov,difv;
     /*U(ix,iy)�̌v�Z*/
     for (ix=1;ix<=NX-1;ix++){
       for (iy=1;iy<=NY;iy++){
         /* vv��U(ix,iy)�ɂ�����V�̕�Ԓl */
         vv=(VO[ix][iy]+VO[ix+1][iy]+VO[ix][iy-1]+VO[ix+1][iy-1])/4.0;
         /* �Η���(cnvux,cnvuy)���P�����x���㍷���ɂČv�Z */
         if ( UO[ix][iy] >= 0.0 ){
           cnvux = UO[ix][iy]*( UO[ix][iy]-UO[ix-1][iy] ) / DX;
         }
         else if ( UO[ix][iy] < 0.0 ){
           cnvux = UO[ix][iy]*( UO[ix+1][iy] - UO[ix][iy] ) / DX;
         }
         if ( vv >= 0.0 ){
           cnvuy = vv*( UO[ix][iy] - UO[ix][iy-1] ) / DY;
         }
         else if ( vv < 0.0 ){
           cnvuy = vv*( UO[ix][iy+1] - UO[ix][iy] ) / DY;
         }
         /* x�����̕��͍�(buou)�̓[�� */
         buou = 0.0;
         /* �g�U��(difu)�̌v�Z */
         difu = VIS*( (UO[ix-1][iy]-2.0*UO[ix][iy]+UO[ix+1][iy])/(DX*DX)
                     +(UO[ix][iy-1]-2.0*UO[ix][iy]+UO[ix][iy+1])/(DY*DY) );
         /*���̑��x(U)�̌v�Z*/
         UN[ix][iy] = UO[ix][iy]
              + DT*( -cnvux-cnvuy+difu+buou+( PO[ix][iy]-PO[ix+1][iy] )/DX );
       }
     }
     /*V(ix,iy)�̌v�Z*/
     for (ix=1;ix<=NX;ix++){
       for (iy=1;iy<=NY-1;iy++){
         /* uu��V(ix,iy)�ɂ�����U�̕�Ԓl */
         uu=(UO[ix-1][iy]+UO[ix][iy]+UO[ix-1][iy+1]+UO[ix][iy+1])/4.0;
         /* �Η���(cnvvx,cnvvy)���P�����x���㍷���ɂČv�Z */
         if ( uu >= 0.0 ){
           cnvvx = uu*( VO[ix][iy] - VO[ix-1][iy] ) / DX;
         }
         else if ( uu < 0.0 ){
           cnvvx = uu*( VO[ix+1][iy] - VO[ix][iy] ) / DX;
         }
         if ( VO[ix][iy] >= 0.0 ){
           cnvvy = VO[ix][iy]*( VO[ix][iy]-VO[ix][iy-1] ) / DY;
         }
         else if ( VO[ix][iy] < 0.0 ){
           cnvvy = VO[ix][iy]*( VO[ix][iy+1]-VO[ix][iy] ) / DY;
         }
         /*���͍�(buov)�̌v�Z*/
         tv = ( TO[ix][iy] + TO[ix][iy+1] )/2.0;
         buov = BUO*tv;
         /*�g�U��(difv)�̌v�Z*/
         difv = VIS*( (VO[ix-1][iy]-2.0*VO[ix][iy]+VO[ix+1][iy])/(DX*DX)
                     +(VO[ix][iy-1]-2.0*VO[ix][iy]+VO[ix][iy+1])/(DY*DY) );
         /*���̑��x(V)�̌v�Z*/
         VN[ix][iy] = VO[ix][iy]
              + DT*( -cnvvx-cnvvy+difv+buov+(PO[ix][iy]-PO[ix][iy+1])/DY );
       }
     }
     velbnd();
}
/*���͏�̌v�Z*/
void press()
{
     int ixmax,iymax,ix,iy;
     double del,div,delp,postn;
     ixmax = 0; iymax = 0; DMAX = 0.0e0;
     /*P(ix,iy)�̌v�Z*/
     for (ix=1;ix<=NX;ix++){
       for (iy=1;iy<=NY;iy++){
         del = DT*( 2.0/(DX*DX) + 2.0/(DY*DY) );
         div = ( UN[ix][iy] - UN[ix-1][iy  ] )/DX
             + ( VN[ix][iy] - VN[ix  ][iy-1] )/DY;
         if ( fabs(div) >= fabs(DMAX) ){
           ixmax = ix; iymax = iy; DMAX = div;
         }
         delp = - OMG * div / del;
         PO[ix][iy] = PO[ix][iy] + delp;
         UN[ix  ][iy  ]=UN[ix  ][iy  ]+DT/DX*delp;
         UN[ix-1][iy  ]=UN[ix-1][iy  ]-DT/DX*delp;
         VN[ix  ][iy  ]=VN[ix  ][iy  ]+DT/DY*delp;
         VN[ix  ][iy-1]=VN[ix  ][iy-1]-DT/DY*delp;
       }
     }
     /* ���͂̑��ΐ��Ɋւ��鏈��(IRELP=1�Ȃ�ȉ��̏������s��) */
     if (IRELP==1){
       postn = PO[1][1];
       for (ix=1;ix<=NX;ix++){
         for (iy=1;iy<=NY;iy++){
           PO[ix][iy] = PO[ix][iy]-postn;
         }
       }
     }
     /* IFLG=1�Ȃ�C�A���̎��𖞂����Ă��Ȃ��Ɣ��肵�Ăш��͌v�Z���s�� */
     if ( fabs(DMAX) >= EPSP ){
       IFLG = 1;
     }
     /* ���͌v�Z�̉񐔂�100�񂲂Ƃɕ\�� */
     if ( (ITR%100) == 0){
       printf (" Iteration= %8d, Div(max)( %6d, %6d ) = %15.6lE\n",ITR,ixmax,iymax,DMAX);
     }
     /*�V���ɓ���ꂽ���x��p���ċ��E��������������*/
     velbnd();
}
/*���x��̌v�Z*/
void caltem()
{
     int ix,iy;
     double uut,vvt,cnvtx,cnvty,dift;
     /*T(ix,iy)�̌v�Z*/
     for (ix=1;ix<=NX;ix++){
       for (iy=1;iy<=NY;iy++){
         /* uut,vvt�͂��ꂼT(IX,IY)�ɂ�����U,V�̕�Ԓl */
         uut = ( UO[ix][iy] + UO[ix-1][iy  ] ) / 2.0;
         vvt = ( VO[ix][iy] + VO[ix  ][iy-1] ) / 2.0;
         /*�Η���(cnvtx,cnvty)���P�����x���㍷���ɂČv�Z*/
         if ( uut >= 0.0 ){
           cnvtx = uut*( TO[ix][iy] - TO[ix-1][iy] ) / DX;
         }
         else if ( uut < 0.0 ){
           cnvtx = uut*( TO[ix+1][iy] - TO[ix][iy] ) / DX;
         }
         if ( vvt >= 0.0 ){
           cnvty = vvt*( TO[ix][iy] - TO[ix][iy-1] ) / DY;
         }
         else if ( vvt < 0.0 ){
           cnvty = vvt*( TO[ix][iy+1] - TO[ix][iy] ) / DY;
         }
         /* �g�U��(dift)�̌v�Z */
         dift = ALP*( (TO[ix-1][iy]-2.0*TO[ix][iy]+TO[ix+1][iy])/(DX*DX)
                     +(TO[ix][iy-1]-2.0*TO[ix][iy]+TO[ix][iy+1])/(DY*DY) );
         /* ���̎��Ԃ�T�̌v�Z */
         TN[ix][iy] = TO[ix][iy] + DT*( -cnvtx-cnvty+dift );
       }
     }
     /* ���E�����̏��� */
     tbnd();
}
/* ���x�̋��E�����̏��� */
void velbnd()
{
     int ix,iy;
     for (iy=1;iy<=NY;iy++){/*U�i�E���ʁj*/
       UN[NX][iy] = 0.0;
     }
     for (iy=1;iy<=NY;iy++){/*U�i�����ʁj*/
       UN[0][iy] = 0.0;
     }
     for (ix=0;ix<=NX;ix++){/*U�i��ʁj*/
       UN[ix][NY+1] = -UN[ix][NY];
     }
     for (ix=0;ix<=NX;ix++){/*U�i���ʁj*/
       UN[ix][0] = -UN[ix][1];
     }
     for (iy=1;iy<=NY-1;iy++){/*V�i�E���ʁj*/
       VN[NX+1][iy] = -VN[NX][iy];
     }
     for (iy=1;iy<=NY-1;iy++){/*V�i�����ʁj*/
       VN[0][iy] = -VN[1][iy];
     }
     for (ix=0;ix<=NX+1;ix++){/*V�i��ʁj*/
       VN[ix][NY] = 0.0;
     }
     for (ix=0;ix<=NX+1;ix++){/*V�i���ʁj*/
       VN[ix][0] = 0.0;
     }
}
/*���x�̋��E�����̏���*/
void tbnd()
{
     int ix,iy;
      for (iy=0;iy<=NY+1;iy++){/*�E����*/
        TN[NX+1][iy] = 2.0 * ( -0.5 ) - TN[NX][iy];
      }
      for (iy=0;iy<=NY+1;iy++){/*������*/
        TN[0][iy] = 2.0 * ( +0.5 ) - TN[1][iy];
      }
      for (ix=1;ix<=NX;ix++){/*���*/
        TN[ix][NY+1] = TN[ix][NY];
      }
      for (ix=1;ix<=NX;ix++){/*����*/
        TN[ix][0] = TN[ix][1];
      }
}
void prout()/*�f�[�^�o�͗p*/
{
    fwrite(UN, sizeof(double), NX1*NY2, out_11);
    fwrite(VN, sizeof(double), NX2*NY1, out_12);
    fwrite(PO, sizeof(double), NX2*NY2, out_13);
    fwrite(TN, sizeof(double), NX2*NY2, out_14);
}
/* �v�Z���ʂ̏o�� */
void output ( char *fname_out )
{

     int ix,iy;
     double x,y,u,v,t;

     out_21=fopen(fname_out,"w");
     fprintf (out_21," VARIABLES = \"X\", \"Y\", \"U\", \"V\", \"T\"\n");
     fprintf (out_21," ZONE I=%3d, J=%3d, F=POINT \n",NX1,NY1);

     for (iy=0;iy<=NY;iy++){
       for (ix=0;ix<=NX;ix++){
         x = DX * (double)ix;
         y = DY * (double)iy;
         u = ( UN[ix][iy]+UN[ix][iy+1])/2.0;
         v = ( VN[ix][iy]+VN[ix+1][iy])/2.0;
         t = ( TN[ix][iy]+TN[ix+1][iy]
              +TN[ix][iy+1]+TN[ix+1][iy+1] )/4.0;
         fprintf(out_21,"%12.3lE %12.3lE %12.3lE %12.3lE %12.3lE\n",x,y,u,v,t);
       }
     }
     fclose (out_21);
}
