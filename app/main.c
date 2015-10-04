/******************** (C) COPYRIGHT 2011 清帑窮徨垢恬片 ********************
* 猟周兆       ��main.c
* 宙峰         �差こ鳴０翳却�
*
* 糞刮峠岬     ��landzo窮徨蝕窟井
* 垂井云       ��
* 廼秘狼由     ��
*
* 恬宀         ��landzo 清窮徨
* 猛右糾       ��http://landzo.taobao.com/

**********************************************************************************/

#include "include.h"
#include "calculation.h"

/*************************
譜崔狼由議嶄僅痕方延楚
*************************/
extern  uint8  LPT_INT_count;                    //LPT 琢喝柴方匂

extern uint8 TIME0flag_5ms;                    //PTI0 5ms炎崗了
extern uint8 TIME0flag_10ms;                    //PTI0 10ms炎崗了
extern uint8 TIME0flag_20ms;                    //PTI0 20ms炎崗了 
extern uint8 TIME0flag_80ms;                     //PTI0 80ms炎崗了   
extern uint8 TIME0flag_100ms;                     //PTI0 100ms炎崗了 
extern uint8 TIME0flag_200ms;                     //PTI0 100ms炎崗了 

extern uint16 Sample_Line_Count;                //DMA寡鹿議佩方
extern uint8  DMA_Over_Flag;                      //DMA寡鹿頼撹炎崗了

/********
畠蕉
********/                
/*********
堀業延楚
*********/
uint16 Set_Speed=0 ;                                  //朕炎堀業
uint16 Speed_Count =0 ;                          //琢喝柴方匂
int SpeedPWM_Value_left=0 ;                          //PID柴麻議PWM 
int SpeedPWM_Value_right=0 ;                          //PID柴麻議PWM 
int SpeedPWM_Value_left_jiansu=0 ;                          //PID柴麻議PWM 
int SpeedPWM_Value_right_jiansu=0 ;                          //PID柴麻議PWM 
int test;
int num=0;
uint8 Speed_P;
uint8 Speed_I;
uint8 Speed_D;

/*********
廬�魃篩�
*********/
uint8  Turn_P=0;
uint8  Turn_D=0;
uint8  Turn_i=0;
uint16 TurnPWM_Value=4800 ;                        //廬�魑�PWM峙 
int16  Sum_Station=0;
char  Station=71 ;                         //CCD議菜�瀘志�
uint8  MIDSTATION = 71 ;                 //CCD勧湖匂燕幣議菜�澣綴仄篶志�

/********
父�駘群票�延楚
********/
uint8  BUFF[500] ;
uint8  checkflag = 0 ;  
uint8  Sample_Over=0;
uint8  g_PointCount=DATACOUNT;
uint16  g_temp0=0; 
uint8  ADdata[DATAROW][DATACOUNT]={0};
uint8  *finger, *finger1; 
uint8  g_LineCalculation=0;
//uint8  Rightblackedge[DATAROW]={0};
//uint8  Leftblackedge[DATAROW]={0};
//uint8  CameraStation[DATAROW]={0};
uint8  Rightblackedge[5]={0};
uint8  Leftblackedge[5]={0};
uint8  CameraStation[5]={0};

uint8  single[2];
uint8  single_left;
uint8  singleflag=1;
uint8  lastleftedge;
uint8  lastrightedge;
uint8  lastsingleedge[3];
int shizi_flag=0;
int shizibiandan_flag=0;
int k1,k2;

int zhijiaoyanshi;
uint8 guaiwanyanshi;
int zhijiaoheixian;
uint8 zhijiaoflag;
int zhijiaozuoguai;
int zhijiaoyouguai;
uint8 left_num[5];
uint8 right_num[5];
uint8 diuxianflag;
uint8 diuxianyanshi;
int zuozhangaiflag;
int zhijiaoheixianhouyanshi;
int youzhangaiflag;

int danxianshu;
int danxianshuzuo;
int danxianshuyou;
int danxianshuzuo1;
int danxianshuyou1;
int danxianshuzuo2;
int danxianshuyou2;
int danxianstation;
int danxianshuzuo3;
int danxianshuyou3;


uint8 shizizhijiaoflag=0;

uint8 zhangaiyanshi;

uint8 zhijiaojiansu;

uint8 zhijiaoyouguaiyanshi;

int dengta=0;



void main()
{
  DisableInterrupts;                             //鋤峭悳嶄僅 
  /*********************************************************
  兜兵晒畠蕉延楚
  *********************************************************/
  
  Set_Speed = 10 ;  //64
  
  Speed_I=0;
  Speed_D=10;
  
  

  
  /*********************************************************
  兜兵晒殻會
  *********************************************************/
  
  uart_init (UART0 , 9600);                      //兜兵晒UART0��補竃重PTA15��補秘重PTA14��堪笥撞楕 115200
  gpio_init (PORTB , 17, GPO,HIGH);                //LED描妨  
  gpio_init (PORTB, 3, GPI,HIGH);  
  
  
  gpio_init (PORTB , 11, GPO,LOW);                //狼由医霞編LED兜兵晒
  gpio_init (PORTB , 13, GPO,HIGH);                //LED描妨  
  gpio_init (PORTB, 7, GPI,HIGH);  
  gpio_init (PORTB, 9, GPI,HIGH);  
   OLED_Init();                                     //兜兵晒OLED勧湖匂 
  pit_init_ms(PIT0, 1);                            //兜兵晒PIT0��協扮扮寂葎�� 1ms
  Camera_init();                                    //兜兵晒父�駘郡�湖匂    
  MOTORPWM_init();                                 //窮字兜兵晒
  TURNPWM_init() ;                                 //廬�魍�兵晒  
    OLED_Print(5,0,"fuck");  //査忖忖憲堪�塋�
   while(checkflag != 1 )  
  {
    checkflag = LandzoIICEEROM_INIT() ; //宥狛塘崔聞父�駘景箜�方忖佚催
    BFdelay_1us(100);                   // 决扮100us 
  }
  
  EnableInterrupts;			            //蝕悳嶄僅  
  
  /******************************************
  峇佩殻會
  ******************************************/
  while(1)
  {
    
    
    if(gpio_get(PORTB, 7)==0)
    {
    /*********************
    5ms殻會峇佩旗鷹粁
    *********************/
    if(TIME0flag_5ms == 1)
    { 
      TIME0flag_5ms = 0 ;
      
    }
    
    /*********************
    10ms殻會峇佩旗鷹粁
    *********************/
    if(TIME0flag_10ms == 1)
    {
      TIME0flag_10ms = 0 ;
      //LPTMR0_CNR=1; 
/*      Speed_Count = LPTMR0_CNR;                                                     //隠贋琢喝柴方匂柴麻峙
      lptmr_counter_clean();                                                  //賠腎琢喝柴方匂柴麻峙��瀧貧賠腎��宸劔嘉嬬隠屬柴方峙彈鳩��
      Speed_Count = LPT_INT_count * LIN_COUT +  Speed_Count;                              //寂侯10ms議琢喝肝方
      LPT_INT_count = 0;     */        
      //賠腎LPT嶄僅肝方   
    }
    
    /*********************
    20ms殻會峇佩旗鷹粁
    *********************/
    if(TIME0flag_20ms == 1)
    {
      uart_putchar(UART0,CameraStation[1]);
      TIME0flag_20ms = 0 ;
      //賠茅扮寂炎崗了   
      k2=gpio_get(PORTB, 3);
      if(gpio_get(PORTB, 9)==1)
      {
      if(dengta==0)
      {
         if( gpio_get(PORTB, 3)==1)
        {
           for(k1=0;k1<12;k1++)
           {
             BFdelay_1us(300);
             if(gpio_get(PORTB, 3)==0)
               break;
              if(k1%3==0)
                BFDly_ms(1);
               
          }
          if(k1==12)
          {
           
            dengta=1;
          }
        else
          dengta=0; 
        }
       }
      if(dengta==1)
      {
          if(gpio_get(PORTB, 3)==0)
          {
            dengta=0;
          }   
       }
    }
    else
    {
      if(dengta==0 )
      {
        k1++;
        if(k1>250)
          dengta=1;
      }
    }
      if(zhijiaoflag>0)
         gpio_init (PORTA , 17, GPO,LOW);
      else
         gpio_init (PORTA , 17, GPO,HIGH);   
      /******************汽褒登僅殻會**********************/
        singleflag=0;
    
        danxianshuzuo=0;
        
        for(int i=Leftblackedge[1]-5;i>Leftblackedge[1]-20;i--)
        {
          if(i<10)
            break;
          if(ADdata[15][i]>100)
            danxianshuzuo++;
        }
        danxianshuyou=0;
        for(int i=Rightblackedge[1]+5;i<Rightblackedge[1]+20;i++)
        {
          if(i>130)
            break;
          if(ADdata[15][i]>100)
            danxianshuyou++;
        }
        
         danxianshuzuo1=0;
        
        for(int i=Leftblackedge[1]-10;i>Leftblackedge[1]-40;i--)
        {
          if(i<20)
            break;
          if(ADdata[12][i]>100)
            danxianshuzuo1++;
        }
        danxianshuyou1=0;
        for(int i=Rightblackedge[1]+10;i<Rightblackedge[1]+40;i++)
        {
          if(i>120)
            break;
          if(ADdata[12][i]>100)
            danxianshuyou1++;
        }
        
            danxianshuzuo2=0;
        
        for(int i=Leftblackedge[3]-5;i>Leftblackedge[3]-20;i--)
        {
          if(i<10)
            break;
          if(ADdata[10][i]>100)
            danxianshuzuo2++;
        }
        danxianshuyou2=0;
        for(int i=Rightblackedge[3]+5;i<Rightblackedge[3]+20;i++)
        {
          if(i>130)
            break;
          if(ADdata[10][i]>100)
            danxianshuyou2++;
        }
         danxianshuzuo3=0;
        
        for(int i=Leftblackedge[3]-10;i>Leftblackedge[3]-40;i--)
        {
          if(i<20)
            break;
          if(ADdata[10][i]>100)
            danxianshuzuo3++;
        }
        danxianshuyou3=0;
        for(int i=Rightblackedge[3]+10;i<Rightblackedge[3]+40;i++)
        {
          if(i>120)
            break;
          if(ADdata[10][i]>100)
            danxianshuyou3++;
        }
        
        if(diuxianflag==0)
        {
        if((danxianshuzuo>10||danxianshuyou>10 || danxianshuzuo2>10||danxianshuyou2>10))
        {        
                  /*if(danxianshuzuo>10&&danxianshuyou<10 && Leftblackedge[1]>10 && Rightblackedge[1]<130)
                  {
                 //   Station=(Rightblackedge[1]+5)/2;
                    Station=Leftblackedge[1];
                    danxianstation=Station;
                    singleflag=2;
                  }
                  else if(danxianshuzuo<10&&danxianshuyou>10 && Leftblackedge[1]>10 && Rightblackedge[1]<130)
                  {
                //    Station=(Leftblackedge[1]+135)/2;
                     Station=Rightblackedge[1];
                    danxianstation=Station;
                    singleflag=2;
                  }*/
                  if(danxianshuzuo>10 && Leftblackedge[1]>10)
                  {
                    Station=Leftblackedge[1];
                    danxianstation=Station;
                    singleflag=1;
                  }
                  else if(danxianshuyou>10  && Rightblackedge[1]<130)
                  {
                    Station=Rightblackedge[1];
                    danxianstation=Station;
                    singleflag=1;
                  }
                 /* else if(danxianshuzuo2>10&&danxianshuyou2<10 && Leftblackedge[3]>10 && Rightblackedge[3]<130)
                  {
                 //   Station=(Rightblackedge[1]+5)/2;
                    Station=Leftblackedge[3];
                    danxianstation=Station;
                    singleflag=2;
                  }
                  else if(danxianshuzuo2<10&&danxianshuyou2>10 && Leftblackedge[3]>10 && Rightblackedge[3]<130)
                  {
                //    Station=(Leftblackedge[1]+135)/2;
                     Station=Rightblackedge[3];
                    danxianstation=Station;
                    singleflag=2;
                  }*/
                  else if(danxianshuzuo2>10 && Leftblackedge[3]>10)
                  {
                    Station=Leftblackedge[3];
                    danxianstation=Station;
                    singleflag=1;
                  }
                  else if(danxianshuyou2>10  && Rightblackedge[3]<130)
                  {
                    Station=Rightblackedge[3];
                    danxianstation=Station;
                    singleflag=1;
                  }
        }
        /***********屎械函峠譲***********/
        else
        {
              Station=CameraStation[1];  
              singleflag=0;
         }
         if((Leftblackedge[1]<10 && Rightblackedge[1]>130))
        {
   
            Station=danxianstation;
            diuxianflag=1;
        }    

     
         /***********岷叔**********/

         if((zhangaiyanshi==0)&&(((left_num[0]>20)&&(right_num[0]>20))||((left_num[1]>20)&&(right_num[1]>20))||((left_num[2]>20)&&(right_num[2]>20))) &&(zhijiaoheixian==0)&&((Rightblackedge[4]<135 &&Leftblackedge[4]>5)|| (Rightblackedge[3]<135 &&Leftblackedge[3]>5) ) &&(( left_num[4]<20&& right_num[4]<20)||( left_num[3]<20&& right_num[3]<20)))    
     //   if((((left_num[0]>20)&&(right_num[0]>20))||((left_num[1]>20)&&(right_num[1]>20))||((left_num[2]>20)&&(right_num[2]>20))) &&(zhijiaoheixian==0)&&(zhangaiyanshi==0))
        {
            guaiwanyanshi=0;
            if(zhijiaoflag==0)
              zhijiaoflag=1;
            else
              zhijiaoflag=0;
            zhijiaoheixian=100;
            shizibiandan_flag=100;
            shizizhijiaoflag=10;
            zhijiaoyouguai=0;
            zhijiaozuoguai=0;
            zhijiaoheixianhouyanshi=40;
            zhijiaoyanshi=130;  
        }
        // if((zhijiaoflag==1)&&(zhijiaozuoguai==0)&&(zhijiaoyouguai==0)&&(((Leftblackedge[0]>5)&&(Rightblackedge[0]>100))||((Leftblackedge[1]>5)&&(Rightblackedge[1]>100))||((Leftblackedge[2]>5)&&(Rightblackedge[2]>100)))&&(zhijiaoheixianhouyanshi==0))
        if((zhijiaoflag==1)&&(zhijiaozuoguai==0)&&(zhijiaoyouguai==0)&&(CameraStation[0]>70 ||CameraStation[1]>70 ||CameraStation[2]>70||Rightblackedge[0]==135||Rightblackedge[1]==135||Rightblackedge[2]==135)&&(zhijiaoheixianhouyanshi==0))
            {
                 zhijiaoyouguai=25;
            }  
        // if((zhijiaoflag==1)&&(zhijiaozuoguai==0)&&(zhijiaoyouguai==0)&&(((Leftblackedge[0]<20)&&(Rightblackedge[0]<135))||((Leftblackedge[1]<20)&&(Rightblackedge[1]<135))||((Leftblackedge[2]<20)&&(Rightblackedge[2]<135)))&&(zhijiaoheixianhouyanshi==0))
        if((zhijiaoflag==1)&&(zhijiaoyouguai==0)&&(zhijiaozuoguai==0)&&(CameraStation[0]<55 || CameraStation[1]<55 ||CameraStation[2]<55||Leftblackedge[0]==5||Leftblackedge[1]==5||Leftblackedge[2]==5)&&(zhijiaoheixianhouyanshi==0))
            {            
                 zhijiaozuoguai=25;           
             }
            

        }else   //diuxianflag==1
        {               
          if( Leftblackedge[1]>20 &&Leftblackedge[1]<120)
          {
            diuxianflag=0;
            if(danxianshuzuo>10)
              Station=(Leftblackedge[1]+135)/2;
            else
              Station=Leftblackedge[1];     
          }
          if( Rightblackedge[1]>20 &&Rightblackedge[1]<120)
          {
            diuxianflag=0;
            if(danxianshuyou>10)
              Station=(Rightblackedge[1]+5)/2;
            else
              Station=Rightblackedge[1];    
          }
          if( CameraStation[1]>50 &&CameraStation[1]<90&&(Leftblackedge[1]>20 && Rightblackedge[1]<100))
          {
            diuxianflag=0;
            Station=CameraStation[1];    
          }
        }
           /***********嬾悪***********/

        if((shizi_flag==0)&&(singleflag<2)&&(diuxianflag==0)&&((Leftblackedge[4]>10)&&(Rightblackedge[4]<130)||(Leftblackedge[3]>10)&&(Rightblackedge[3]<130))&&(((danxianshuzuo1>4)&&(danxianshuzuo1<10))||((danxianshuzuo3>4)&&(danxianshuzuo3<10)))&&(lastsingleedge[0]>50 && lastsingleedge[0]<70))
        {
            zuozhangaiflag=20;
         //   zhangaiyanshi=10;
        }
        if((shizi_flag==0)&&(singleflag<2)&&(diuxianflag==0)&&((Leftblackedge[4]>10)&&(Rightblackedge[4]<100)||(Leftblackedge[3]>10)&&(Rightblackedge[3]<100))&&(((danxianshuyou1>4)&&(danxianshuyou1<10))||((danxianshuyou3>4)&&(danxianshuyou3<10)))&&(lastsingleedge[0]>50 && lastsingleedge[0]<70))
        {
            youzhangaiflag=30;
         //   zhangaiyanshi=10;
        }
        /***********嬾悪**********/
/*         if(zhijiaoflag==1 && ( zuozhangaiflag>0 ||  youzhangaiflag>0))
        {
          zuozhangaiflag=0;
          youzhangaiflag=0;
          zhangaiyanshi=0;
        }*/
        if(zhijiaoflag==1 && singleflag==1)
        {
          singleflag=0;
        }
        if(zuozhangaiflag>0)
        {
          zuozhangaiflag--;
          if(zuozhangaiflag==1)
            shizibiandan_flag=20;
          Station=Rightblackedge[1];
        }
        if(zhangaiyanshi>0)
        {
          zhangaiyanshi--;
        }
        if(youzhangaiflag>0)
        {
          youzhangaiflag--;
          if(youzhangaiflag==1)
            shizibiandan_flag=20;
          Station=Leftblackedge[1];
        }
                /***********噴忖***********/
        if((singleflag==0) &&((Rightblackedge[3]>110)&&(Leftblackedge[3]<20)) && ((Rightblackedge[4]<130)&&(Leftblackedge[4]>10)) && (( CameraStation[4]>30)&&( CameraStation[4]<100)) )
        {
           shizi_flag=8; 
           diuxianflag=0;
        }
                 /***********噴忖决扮**********/
        if(shizi_flag>0)
        {
          shizi_flag--;
          shizibiandan_flag=50;
          Station=CameraStation[4];
          diuxianflag=0;
        }
        if( shizibiandan_flag>0)
        {
          shizibiandan_flag--;
        }
        /*****************岷叔列登************/
        /*if(Station<60||Station>80)
        {
          zhijiaoyanshi=10;
        }
        if(zhijiaoyanshi>0)
        {
          zhijiaoyanshi--;
          zhijiaoflag=0;
        }*/
         /***********岷叔决扮**********/
      if(zhijiaoheixian>0)
        {
         
          zhijiaoheixian--;
        }
        if(guaiwanyanshi>1)
        {
          Station=65;
          guaiwanyanshi--;
        }
        if((zhijiaozuoguai>1))
        {
          
          
          zhijiaozuoguai--;
          Station=5;
          
        }
        if((zhijiaoyouguai>1))
        {
          
          zhijiaoyouguai--;
          Station=135;
          
        }
        if(zhijiaoheixianhouyanshi>0)
        {
          zhijiaoheixianhouyanshi--;
        }
        if(zhijiaoyanshi>0)
        {
          if(zhijiaoyanshi==1)
          {
            zhijiaoflag=0;
            zhijiaoyouguai=0;
            zhijiaozuoguai=0;
          }
          zhijiaoyanshi--;
        }
        if(shizizhijiaoflag>0)
        {
          shizizhijiaoflag--;
          Station=65;
        }
        
        /*******卿�瀾喨�********/
         lastsingleedge[2]=lastsingleedge[1];
         lastsingleedge[1]=lastsingleedge[0];
         lastsingleedge[0]=Station; 
         
         lastleftedge=Leftblackedge[1];
         lastrightedge=Rightblackedge[1];
        /******************汽褒登僅殻會潤崩**********************/
         
//       k1=TurnPWM(50, MIDSTATION,50,0,0);
         if(zuozhangaiflag>0)
         {
            TurnPWM_Value=3120+TurnPWM(Rightblackedge[1],90,20,0,30);
         }
         else if(youzhangaiflag>0)
         {
            TurnPWM_Value=3120+TurnPWM(Leftblackedge[1],40,20,0,30);
         }
         else if(singleflag>0)
         {
            TurnPWM_Value=3120+TurnPWM(Station,70,20,0,35);
         }
         else if(shizi_flag>0)
         {
            TurnPWM_Value=3120+TurnPWM(Station,70,20,0,35);
         }
         
         /*else if(Leftblackedge[1]==5 && Rightblackedge[1]!=135)
         {
           TurnPWM_Value=3120+TurnPWM(Rightblackedge[1],120,20,0,35);     //功象CCD了崔峙柴麻廬��PWM峙痕方
         }
         else if(Leftblackedge[1]!=5 && Rightblackedge[1]==135)
         {
           TurnPWM_Value=3120+TurnPWM(Leftblackedge[1],20,20,0,35);     //功象CCD了崔峙柴麻廬��PWM峙痕方
         }*/
         /*else if(Station>67 && Station<73 )
         {
           TurnPWM_Value=3120+TurnPWM(Station,70,5,0,0);  
         }*/
        /* else if(Station<66 ||  Station>84 )
         {
           TurnPWM_Value=3120+TurnPWM(Station,70,23,0,35);  
         }*/
         //  TurnPWM_Value=3120+TurnPWM(Station,70,20,0,35);     //功象CCD了崔峙柴麻廬��PWM峙痕方
         else
         TurnPWM_Value=3120+TurnPWM(Station,70,23,0,35);     //功象CCD了崔峙柴麻廬��PWM峙痕方
       

            
       
      if(TurnPWM_Value>3750)
         TurnPWM_Value=3750;
      if(TurnPWM_Value<2750)
        TurnPWM_Value=2750;
      FTM_CnV_REG(FTMx[FTM1], CH1) = TurnPWM_Value ;                            //廬�鮓隔�   倶字2   
    //  FTM_CnV_REG(FTMx[FTM1], CH1) = 2750;  
       if(dengta==0)
       {
         SpeedPWM_Value_left=0;
         SpeedPWM_Value_right=0;
         SpeedPWM_Value_left_jiansu=0;
         SpeedPWM_Value_right_jiansu=0;
            
       }
       else if(zhijiaoyouguai>0 && zhijiaozuoguai!=1 && zhijiaoyouguai!=1)
       {
         SpeedPWM_Value_left=400;
        SpeedPWM_Value_right=0;
         SpeedPWM_Value_left_jiansu=0 ;                          //PID柴麻議PWM 
        SpeedPWM_Value_right_jiansu=0 ;                          //PID柴麻議PWM 
       }
       else if(zhijiaozuoguai>0 &&zhijiaozuoguai!=1 && zhijiaoyouguai!=1)
       {
         SpeedPWM_Value_left=0;
        SpeedPWM_Value_right=500;
         SpeedPWM_Value_left_jiansu=0 ;                          //PID柴麻議PWM 
        SpeedPWM_Value_right_jiansu=0 ;                          //PID柴麻議PWM 
       }
        else if(zuozhangaiflag>0||youzhangaiflag>0)
        {
               SpeedPWM_Value_left=350;
               SpeedPWM_Value_right=350;
               SpeedPWM_Value_left_jiansu=0;                          //PID柴麻議PWM 
               SpeedPWM_Value_right_jiansu=0;                          //PID柴麻議PWM 
        }
        else if(zhijiaoflag==1&&zhijiaozuoguai!=1 && zhijiaoyouguai!=1)
       {
        if( SpeedPWM_Value_left>390 ||  SpeedPWM_Value_right>390)
        {
            zhijiaojiansu=10;
        }
        if(zhijiaojiansu>0)
        {
            SpeedPWM_Value_left=0;
            SpeedPWM_Value_right=0;
            SpeedPWM_Value_left_jiansu=0 ;                          //PID柴麻議PWM 
            SpeedPWM_Value_right_jiansu=0 ;                          //PID柴麻議PWM */
            zhijiaojiansu--;
        }
        else
        {
               SpeedPWM_Value_left=350;
               SpeedPWM_Value_right=350;
               SpeedPWM_Value_left_jiansu=0;                          //PID柴麻議PWM 
               SpeedPWM_Value_right_jiansu=0;                          //PID柴麻議PWM 
        }
       }
       else if(shizi_flag>0)
       {
           SpeedPWM_Value_left=500;
           SpeedPWM_Value_right=500;
           SpeedPWM_Value_left_jiansu=0 ;                          //PID柴麻議PWM 
           SpeedPWM_Value_right_jiansu=0 ;                          //PID柴麻議PWM 
       }
        else if(diuxianflag==1)
       {
    
        
               SpeedPWM_Value_left=350+(Station-70)*10;
               SpeedPWM_Value_right=350-(Station-70)*10;
               SpeedPWM_Value_left_jiansu=0;                          //PID柴麻議PWM 
              SpeedPWM_Value_right_jiansu=0;                          //PID柴麻議PWM 
       }
       else if(singleflag>0)
       {
              //SpeedPWM_Value_left=350+(Station-70)*10;
              //SpeedPWM_Value_right=350-(Station-70)*10;
              SpeedPWM_Value_left=600;
              SpeedPWM_Value_right=600;
              SpeedPWM_Value_left_jiansu=0;                          //PID柴麻議PWM 
              SpeedPWM_Value_right_jiansu=0;                          //PID柴麻議PWM 
       }
         
       /*else if((Station<60)||(Station>80)&& singleflag==1)
       {
           /* if( SpeedPWM_Value_left>390 ||  SpeedPWM_Value_right>390)
            {
              diuxianflag=5;
            }*/
    /*        if(diuxianflag>0)
            {
                  SpeedPWM_Value_left=100;
                  SpeedPWM_Value_right=100;
                  SpeedPWM_Value_left_jiansu=100 ;                          //PID柴麻議PWM 
                  SpeedPWM_Value_right_jiansu=100 ;                          //PID柴麻議PWM 
            }
            else
            {
              SpeedPWM_Value_left=350+(Station-70)*10;
             SpeedPWM_Value_right=350-(Station-70)*10;
             SpeedPWM_Value_left_jiansu=0 ;                          //PID柴麻議PWM 
             SpeedPWM_Value_right_jiansu=0 ;  
            }
       }*/
       else if((Station<80)&&(Station>60)&&(CameraStation[4]>60 && CameraStation[4]<80)&&(singleflag==0))
      {
     //   SpeedPWM_Value_left =600+(Station-70)*6;
     //   SpeedPWM_Value_right=600-(Station-70)*6;
        SpeedPWM_Value_left =600;
        SpeedPWM_Value_right=600;
         SpeedPWM_Value_left_jiansu=0 ;                          //PID柴麻議PWM 
        SpeedPWM_Value_right_jiansu=0 ;                          //PID柴麻議PWM 
      }
      else
      {

        {
        SpeedPWM_Value_left=500+(Station-70)*5;
        SpeedPWM_Value_right=500-(Station-70)*5;
        SpeedPWM_Value_left_jiansu=0 ;                          //PID柴麻議PWM 
        SpeedPWM_Value_right_jiansu=0 ;                          //PID柴麻議PWM 
        }
      }
     
      /*if(diuxianflag>0||diuxianyanshi>0)
      {
        SpeedPWM_Value_left=300;
        SpeedPWM_Value_right=300;
      }*/
       if(SpeedPWM_Value_left<0)
         SpeedPWM_Value_left=0;
       if(SpeedPWM_Value_right<0)
         SpeedPWM_Value_right=0;
        FTM_PWM_Duty(FTM0 , CH0,SpeedPWM_Value_left_jiansu);                                           //FTM0 CH0 PWM補竃 �撒膸�陣崙
        FTM_PWM_Duty(FTM0 , CH1,SpeedPWM_Value_left);                              //FTM0 CH1 PWM補竃 �撒膸�陣崙  
        FTM_PWM_Duty(FTM0 , CH2,SpeedPWM_Value_right_jiansu);                                           //FTM0 CH0 PWM補竃 �撒膸�陣崙
        FTM_PWM_Duty(FTM0 , CH3,SpeedPWM_Value_right);                             //FTM0 CH1 PWM補竃 �撒膸�陣崙  
     /*   FTM_PWM_Duty(FTM0 , CH0,0);                                           //FTM0 CH0 PWM補竃 �撒膸�陣崙
        FTM_PWM_Duty(FTM0 , CH1,0);                              //FTM0 CH1 PWM補竃 �撒膸�陣崙  
        FTM_PWM_Duty(FTM0 , CH2,0);                                           //FTM0 CH0 PWM補竃 �撒膸�陣崙
        FTM_PWM_Duty(FTM0 , CH3,0);*/
        
    }
    
    /*********************
    80ms殻會峇佩旗鷹粁
    *********************/    
    if(TIME0flag_80ms == 1)
    {        
      TIME0flag_80ms = 0 ;                                                    //賠茅扮寂炎崗了
      PTA16_OUT = ~PTA16_OUT ;                                                //霞編LED描妨      

      
       // SpeedPWM_Value+=SpeedControl(Speed_Count,Set_Speed,Speed_P,Speed_I,Speed_D) ;    //PID痕方柴麻PWM峙    
      
    }
    
    /*********************
    100ms殻會峇佩旗鷹粁
    *********************/
    if(TIME0flag_100ms == 1)
    { 
      TIME0flag_100ms = 0 ;
      
    }
    
    if(DMA_Over_Flag==1)
    {
      DMA_Over_Flag=0;      

 //     Camera_Black_single(&ADdata[21][0],&single[1],&single_left);
 //     Camera_Black_single(&ADdata[22][0],&single[2]);  
      /*  uart_putchar (UART0 , 0);  
        uart_putchar (UART0 , 255);
        uart_putchar (UART0 , 1); 
        uart_putchar (UART0 , 0); 
        for(int i=0;i<30;i++)
          for(int j=0;j<140;j++)
        {
             uart_putchar (UART0 ,ADdata[i][j] );  
        }
        */
        Camera_Black1(&ADdata[12][0],&Rightblackedge[0],&Leftblackedge[0],&CameraStation[0]);
         left_num[0]=0;right_num[0]=0;
        for(int i=70;i>40;i--)
        {
          if(i<5)
            break;
          if(ADdata[12][i]<100)
            left_num[0]++;
        }
        for(int i=70;i<100;i++)
        {
          if(i>135)
            break;
          if(ADdata[12][i]<100)
            right_num[0]++;
        }
        Camera_Black2(&ADdata[14][0],&Rightblackedge[1],&Leftblackedge[1],&CameraStation[1]);
        left_num[1]=0;right_num[1]=0;
        for(int i=70;i>40;i--)
        {
          if(i<5)
            break;
          if(ADdata[14][i]<100)
            left_num[1]++;
        }
        for(int i=70;i<100;i++)
        {
          if(i>135)
            break;
          if(ADdata[14][i]<100)
            right_num[1]++;
        }
        Camera_Black3(&ADdata[16][0],&Rightblackedge[2],&Leftblackedge[2],&CameraStation[2]);
           left_num[2]=0;right_num[2]=0;
         for(int i=70;i>40;i--)
        {
          if(i<5)
            break;
          if(ADdata[16][i]<100)
            left_num[2]++;
        }
        for(int i=70;i<100;i++)
        {
          if(i>135)
            break;
          if(ADdata[16][i]<100)
            right_num[2]++;
        }
        Camera_Black4(&ADdata[10][0],&Rightblackedge[3],&Leftblackedge[3],&CameraStation[3]);
        left_num[3]=0;right_num[3]=0;
        for(int i=70;i>40;i--)
        {
          if(i<5)
            break;
          if(ADdata[10][i]<100)
            left_num[3]++;
        }
        for(int i=70;i<100;i++)
        {
          if(i>135)
            break;
          if(ADdata[10][i]<100)
            right_num[3]++;
        }
        Camera_Black5(&ADdata[3][0],&Rightblackedge[4],&Leftblackedge[4],&CameraStation[4]);
        left_num[4]=0;right_num[4]=0;
        for(int i=70;i>40;i--)
        {
          if(i<5)
            break;
          if(ADdata[3][i]<100)
            left_num[4]++;
        }
        for(int i=70;i<100;i++)
        {
          if(i>135)
            break;
          if(ADdata[3][i]<100)
            right_num[4]++;
        }
    }  
     
    
    
  }
  /***************************************************************************************************************/
  /***************************************************************************************************************/
  /***************************************************************************************************************/
  /***************************************************************************************************************/
  /***************************************************************************************************************/
  /***************************************************************************************************************/
  //蛸堀殻會  
  /***************************************************************************************************************/
  /***************************************************************************************************************/
  /***************************************************************************************************************/
  /***************************************************************************************************************/
  /***************************************************************************************************************/
  /***************************************************************************************************************/
  else
  {
       /*********************
    5ms殻會峇佩旗鷹粁
    *********************/
    if(TIME0flag_5ms == 1)
    { 
      TIME0flag_5ms = 0 ;
      
    }
    
    /*********************
    10ms殻會峇佩旗鷹粁
    *********************/
    if(TIME0flag_10ms == 1)
    {
      TIME0flag_10ms = 0 ;
      //LPTMR0_CNR=1; 
/*      Speed_Count = LPTMR0_CNR;                                                     //隠贋琢喝柴方匂柴麻峙
      lptmr_counter_clean();                                                  //賠腎琢喝柴方匂柴麻峙��瀧貧賠腎��宸劔嘉嬬隠屬柴方峙彈鳩��
      Speed_Count = LPT_INT_count * LIN_COUT +  Speed_Count;                              //寂侯10ms議琢喝肝方
      LPT_INT_count = 0;     */        
      //賠腎LPT嶄僅肝方   
    }
    
    /*********************
    20ms殻會峇佩旗鷹粁
    *********************/
    if(TIME0flag_20ms == 1)
    {

      TIME0flag_20ms = 0 ;
      //賠茅扮寂炎崗了   
           k2=gpio_get(PORTB, 3);
       k2=gpio_get(PORTB, 3);
      if(gpio_get(PORTB, 9)==1)
      {
      if(dengta==0)
      {
         if( gpio_get(PORTB, 3)==1)
        {
           for(k1=0;k1<12;k1++)
           {
             BFdelay_1us(300);
             if(gpio_get(PORTB, 3)==0)
               break;
              if(k1%3==0)
                BFDly_ms(1);
               
          }
          if(k1==12)
          {
           
            dengta=1;
          }
        else
          dengta=0; 
        }
       }
      if(dengta==1)
      {
          if(gpio_get(PORTB, 3)==0)
          {
            dengta=0;
          }   
       }
    }
    else
    {
      if(dengta==0 )
      {
        k1++;
        if(k1>250)
          dengta=1;
      }
    }
      if(zhijiaoflag>0)
         gpio_init (PORTA , 17, GPO,LOW);
      else
         gpio_init (PORTA , 17, GPO,HIGH);   
      /******************汽褒登僅殻會**********************/
        singleflag=0;
   
        danxianshuzuo=0;
        
        for(int i=Leftblackedge[1]-5;i>Leftblackedge[1]-20;i--)
        {
          if(i<10)
            break;
          if(ADdata[15][i]>100)
            danxianshuzuo++;
        }
        danxianshuyou=0;
        for(int i=Rightblackedge[1]+5;i<Rightblackedge[1]+20;i++)
        {
          if(i>120)
            break;
          if(ADdata[15][i]>100)
            danxianshuyou++;
        }
        
         danxianshuzuo1=0;
        
        for(int i=Leftblackedge[1]-10;i>Leftblackedge[1]-40;i--)
        {
          if(i<10)
            break;
          if(ADdata[13][i]>100)
            danxianshuzuo1++;
        }
        danxianshuyou1=0;
        for(int i=Rightblackedge[1]+10;i<Rightblackedge[1]+40;i++)
        {
          if(i>130)
            break;
          if(ADdata[13][i]>100)
            danxianshuyou1++;
        }
        
            danxianshuzuo2=0;
        
        for(int i=Leftblackedge[3]-5;i>Leftblackedge[3]-20;i--)
        {
          if(i<10)
            break;
          if(ADdata[10][i]>100)
            danxianshuzuo2++;
        }
        danxianshuyou2=0;
        for(int i=Rightblackedge[3]+5;i<Rightblackedge[3]+20;i++)
        {
          if(i>130)
            break;
          if(ADdata[10][i]>100)
            danxianshuyou2++;
        }
         danxianshuzuo3=0;
        
        for(int i=Leftblackedge[3]-10;i>Leftblackedge[3]-40;i--)
        {
          if(i<10)
            break;
          if(ADdata[10][i]>100)
            danxianshuzuo3++;
        }
        danxianshuyou3=0;
        for(int i=Rightblackedge[3]+10;i<Rightblackedge[3]+40;i++)
        {
          if(i>130)
            break;
          if(ADdata[10][i]>100)
            danxianshuyou3++;
        }
        
        if(diuxianflag==0)
        {
        if(danxianshuzuo>10||danxianshuyou>10 || danxianshuzuo2>10||danxianshuyou2>10)
        {        
                  if(danxianshuzuo>10&&danxianshuyou<10 && Leftblackedge[1]>20 && Rightblackedge[1]<130)
                  {
                 //   Station=(Rightblackedge[1]+5)/2;
                    Station=Leftblackedge[1];
                    danxianstation=Station;
                    singleflag=2;
                  }
                  else if(danxianshuzuo<10&&danxianshuyou>10 && Leftblackedge[1]>20 && Rightblackedge[1]<130)
                  {
                //    Station=(Leftblackedge[1]+135)/2;
                     Station=Rightblackedge[1];
                    danxianstation=Station;
                    singleflag=2;
                  }
                  else if(danxianshuzuo>10 && Leftblackedge[1]>20)
                  {
                    Station=Leftblackedge[1];
                    danxianstation=Station;
                    singleflag=1;
                  }
                  else if(danxianshuyou>10  && Rightblackedge[1]<130)
                  {
                    Station=Rightblackedge[1];
                    danxianstation=Station;
                    singleflag=1;
                  }
                  else if(danxianshuzuo2>10&&danxianshuyou2<10 && Leftblackedge[3]>20 && Rightblackedge[3]<130)
                  {
                 //   Station=(Rightblackedge[1]+5)/2;
                    Station=Leftblackedge[3];
                    danxianstation=Station;
                    singleflag=2;
                  }
                  else if(danxianshuzuo2<10&&danxianshuyou2>10 && Leftblackedge[3]>20 && Rightblackedge[3]<130)
                  {
                //    Station=(Leftblackedge[1]+135)/2;
                     Station=Rightblackedge[3];
                    danxianstation=Station;
                    singleflag=2;
                  }
                  else if(danxianshuzuo2>10 && Leftblackedge[3]>20)
                  {
                    Station=Leftblackedge[3];
                    danxianstation=Station;
                    singleflag=1;
                  }
                  else if(danxianshuyou2>10  && Rightblackedge[3]<130)
                  {
                    Station=Rightblackedge[3];
                    danxianstation=Station;
                    singleflag=1;
                  }
        }
        /***********屎械函峠譲***********/
        else
        {
              Station=CameraStation[1];  
              singleflag=0;
         }
         if((Leftblackedge[1]<10 && Rightblackedge[1]>130))
        {
   
            Station=danxianstation;
            diuxianflag=1;
        }    

     
         /***********岷叔**********/

         if((zhangaiyanshi==0)&&(((left_num[0]>20)&&(right_num[0]>20))||((left_num[1]>20)&&(right_num[1]>20))||((left_num[2]>20)&&(right_num[2]>20))) &&(zhijiaoheixian==0)&&((Rightblackedge[4]<135 &&Leftblackedge[4]>5)|| (Rightblackedge[3]<135 &&Leftblackedge[3]>5) ) &&(( left_num[4]<20&& right_num[4]<20)||( left_num[3]<20&& right_num[3]<20)))    
     //   if((((left_num[0]>20)&&(right_num[0]>20))||((left_num[1]>20)&&(right_num[1]>20))||((left_num[2]>20)&&(right_num[2]>20))) &&(zhijiaoheixian==0)&&(zhangaiyanshi==0))
        {
            guaiwanyanshi=0;
            if(zhijiaoflag==0)
              zhijiaoflag=1;
            else
              zhijiaoflag=0;
            zhijiaoheixian=100;
            shizibiandan_flag=100;
            shizizhijiaoflag=20;
            zhijiaoyouguai=0;
            zhijiaozuoguai=0;
            zhijiaoheixianhouyanshi=40;
            zhijiaoyanshi=150;  
        }
         //if((zhijiaoflag==1)&&(((Leftblackedge[0]>5)&&(Rightblackedge[0]>100))||((Leftblackedge[1]>5)&&(Rightblackedge[1]>100))||((Leftblackedge[2]>5)&&(Rightblackedge[2]>100)))&&(zhijiaoheixianhouyanshi==0))
     //   if((zhijiaoflag==1)&&(zhijiaozuoguai==0)&&(zhijiaoyouguai==0)&&(CameraStation[0]>75 ||CameraStation[1]>75||CameraStation[3]>75||CameraStation[4]>75 ||CameraStation[2]>75)&&(zhijiaoheixianhouyanshi==0))
          if((zhijiaoflag==1)&&(zhijiaozuoguai==0)&&(zhijiaoyouguai==0)&&(CameraStation[1]>70 ||CameraStation[2]>70  || Rightblackedge[1]>130 || Rightblackedge[2]>130)&&(zhijiaoheixianhouyanshi==0))
            {
                 zhijiaoyouguai=30;
            }  
       //  else if((zhijiaoflag==1)&&(((Leftblackedge[0]<20)&&(Rightblackedge[0]<135))||((Leftblackedge[1]<20)&&(Rightblackedge[1]<135))||((Leftblackedge[2]<20)&&(Rightblackedge[2]<135)))&&(zhijiaoheixianhouyanshi==0))
        //if((zhijiaoflag==1)&&(zhijiaoyouguai==0)&&(zhijiaozuoguai==0)&&(CameraStation[0]<65 || CameraStation[1]<65 ||CameraStation[2]<65||CameraStation[3]<65||CameraStation[4]<65 )&&(zhijiaoheixianhouyanshi==0))
          if((zhijiaoflag==1)&&(zhijiaoyouguai==0)&&(zhijiaozuoguai==0)&&( CameraStation[1]<55 ||CameraStation[2]<55  ||Leftblackedge[1]<10 ||Leftblackedge[2]<10)&&(zhijiaoheixianhouyanshi==0))
            {            
                 zhijiaozuoguai=30;           
             }
            

        }else   //diuxianflag==1
        {               
          if( Leftblackedge[1]>20 &&Leftblackedge[1]<120)
          {
            diuxianflag=0;
            if(danxianshuzuo>10)
              Station=(Leftblackedge[1]+135)/2;
            else
              Station=Leftblackedge[1];     
          }
          if( Rightblackedge[1]>20 &&Rightblackedge[1]<120)
          {
            diuxianflag=0;
            if(danxianshuyou>10)
              Station=(Rightblackedge[1]+5)/2;
            else
              Station=Rightblackedge[1];    
          }
          if( CameraStation[1]>50 &&CameraStation[1]<90&&(Leftblackedge[1]>20 && Rightblackedge[1]<100))
          {
            diuxianflag=0;
            Station=CameraStation[1];    
          }
        }
           /***********嬾悪***********/

         if((shizi_flag==0)&&(singleflag<2)&&(diuxianflag==0)&&((Leftblackedge[4]>20)&&(Rightblackedge[4]<130)||(Leftblackedge[3]>20)&&(Rightblackedge[3]<130))&&(((danxianshuzuo1>4)&&(danxianshuzuo1<10))||((danxianshuzuo3>4)&&(danxianshuzuo3<10)))&&(lastsingleedge[0]>60 && lastsingleedge[0]<80))
        {
            zuozhangaiflag=20;
         //   zhangaiyanshi=10;
        }
        if((shizi_flag==0)&&(singleflag<2)&&(diuxianflag==0)&&((Leftblackedge[4]>10)&&(Rightblackedge[4]<100)||(Leftblackedge[3]>10)&&(Rightblackedge[3]<100))&&(((danxianshuyou1>4)&&(danxianshuyou1<10))||((danxianshuyou3>4)&&(danxianshuyou3<10)))&&(lastsingleedge[0]>60 && lastsingleedge[0]<80))
        {
            youzhangaiflag=30;
         //   zhangaiyanshi=10;
        }
        /***********嬾悪**********/
         if(zhijiaoflag==1 && ( zuozhangaiflag>0 ||  youzhangaiflag>0))
        {
          zuozhangaiflag=0;
          youzhangaiflag=0;
          zhangaiyanshi=0;
        }
        if(zhijiaoflag==1 && singleflag==1)
        {
          singleflag=0;
        }
        if(zuozhangaiflag>0)
        {
          zuozhangaiflag--;
          if(zuozhangaiflag==1)
            shizibiandan_flag=20;
          Station=Rightblackedge[1];
        }
        if(zhangaiyanshi>0)
        {
          zhangaiyanshi--;
        }
        if(youzhangaiflag>0)
        {
          youzhangaiflag--;
          if(youzhangaiflag==1)
            shizibiandan_flag=20;
          Station=Leftblackedge[1];
        }
                /***********噴忖***********/
        if((singleflag==0) &&((Rightblackedge[3]>110)&&(Leftblackedge[3]<20)) && ((Rightblackedge[4]<130)&&(Leftblackedge[4]>10)) && (( CameraStation[4]>30)&&( CameraStation[4]<100)) )
        {
           shizi_flag=10; 
           diuxianflag=0;
        }
                 /***********噴忖决扮**********/
        if(shizi_flag>0)
        {
          shizi_flag--;
          shizibiandan_flag=50;
          Station=CameraStation[4];
          diuxianflag=0;
        }
        if( shizibiandan_flag>0)
        {
          shizibiandan_flag--;
        }
        /*****************岷叔列登************/
        /*if(Station<60||Station>80)
        {
          zhijiaoyanshi=10;
        }
        if(zhijiaoyanshi>0)
        {
          zhijiaoyanshi--;
          zhijiaoflag=0;
        }*/
         /***********岷叔决扮**********/
      if(zhijiaoheixian>0)
        {
         
          zhijiaoheixian--;
        }
        if(guaiwanyanshi>1)
        {
          Station=70;
          Station=CameraStation[3];
          guaiwanyanshi--;
        }
        if((zhijiaozuoguai>1))
        {
          
          
          zhijiaozuoguai--;
          Station=5;
          
        }
        if((zhijiaoyouguai>1))
        {
          
          zhijiaoyouguai--;
          Station=135;
          
        }
        if(zhijiaoheixianhouyanshi>0)
        {
          zhijiaoheixianhouyanshi--;
        }
        if(zhijiaoyanshi>0)
        {
          if(zhijiaoyanshi==1)
          {
            zhijiaoflag=0;
            zhijiaoyouguai=0;
            zhijiaozuoguai=0;
          }
          zhijiaoyanshi--;
        }
        if(shizizhijiaoflag>0)
        {
          shizizhijiaoflag--;
          Station=65;
        }
        
        /*******卿�瀾喨�********/
         lastsingleedge[2]=lastsingleedge[1];
         lastsingleedge[1]=lastsingleedge[0];
         lastsingleedge[0]=Station; 
         
         lastleftedge=Leftblackedge[1];
         lastrightedge=Rightblackedge[1];
        /******************汽褒登僅殻會潤崩**********************/
         
//       k1=TurnPWM(50, MIDSTATION,50,0,0);
         if(zuozhangaiflag>0)
         {
            TurnPWM_Value=3120+TurnPWM(Rightblackedge[1],90,20,0,20);
         }
         else if(youzhangaiflag>0)
         {
            TurnPWM_Value=3120+TurnPWM(Leftblackedge[1],40,20,0,20);
         }
         else if(singleflag>0)
         {
            if(Station<66)
            {
              TurnPWM_Value=3120+TurnPWM(Station,70,30,0,35);
            }
            TurnPWM_Value=3120+TurnPWM(Station,70,30,0,35);
         }
         
         /*else if(Leftblackedge[1]==5 && Rightblackedge[1]!=135)
         {
           TurnPWM_Value=3120+TurnPWM(Rightblackedge[1],120,20,0,35);     //功象CCD了崔峙柴麻廬��PWM峙痕方
         }
         else if(Leftblackedge[1]!=5 && Rightblackedge[1]==135)
         {
           TurnPWM_Value=3120+TurnPWM(Leftblackedge[1],20,20,0,35);     //功象CCD了崔峙柴麻廬��PWM峙痕方
         }*/
         else 
           TurnPWM_Value=3120+TurnPWM(Station,70,20,0,35);     //功象CCD了崔峙柴麻廬��PWM峙痕方
       

            
       
      if(TurnPWM_Value>3750)
         TurnPWM_Value=3750;
      if(TurnPWM_Value<2750)
        TurnPWM_Value=2750;
      FTM_CnV_REG(FTMx[FTM1], CH1) = TurnPWM_Value ;                            //廬�鮓隔�   倶字2   
    //   FTM_CnV_REG(FTMx[FTM1], CH1) = 3150;  
       if(dengta==0)
       {
           SpeedPWM_Value_left=0;
           SpeedPWM_Value_right=0;
           SpeedPWM_Value_left_jiansu=0 ;                          //PID柴麻議PWM 
           SpeedPWM_Value_right_jiansu=0 ;                          //PID柴麻議PWM 
       }
       else if(zhijiaoyouguai>0 && zhijiaozuoguai!=1 && zhijiaoyouguai!=1)
       {
         SpeedPWM_Value_left=400;
        SpeedPWM_Value_right=0;
         SpeedPWM_Value_left_jiansu=0 ;                          //PID柴麻議PWM 
        SpeedPWM_Value_right_jiansu=0 ;                          //PID柴麻議PWM 
       }
       else if(zhijiaozuoguai>0 &&zhijiaozuoguai!=1 && zhijiaoyouguai!=1)
       {
         SpeedPWM_Value_left=0;
        SpeedPWM_Value_right=500;
         SpeedPWM_Value_left_jiansu=0 ;                          //PID柴麻議PWM 
        SpeedPWM_Value_right_jiansu=0 ;                          //PID柴麻議PWM 
       }
        else if(zhijiaoflag==1&&zhijiaozuoguai!=1 && zhijiaoyouguai!=1)
       {
        if( SpeedPWM_Value_left>390 ||  SpeedPWM_Value_right>390)
        {
            zhijiaojiansu=10;
        }
        if(zhijiaojiansu>0)
        {
            SpeedPWM_Value_left=0;
            SpeedPWM_Value_right=0;
            SpeedPWM_Value_left_jiansu=0 ;                          //PID柴麻議PWM 
            SpeedPWM_Value_right_jiansu=0 ;                          //PID柴麻議PWM */
            zhijiaojiansu--;
        }
        else
        {
               SpeedPWM_Value_left=350;
               SpeedPWM_Value_right=350;
               SpeedPWM_Value_left_jiansu=0;                          //PID柴麻議PWM 
               SpeedPWM_Value_right_jiansu=0;                          //PID柴麻議PWM 
        }
       }
        else if(diuxianflag==1)
       {
    
        
               SpeedPWM_Value_left=350+(Station-70)*10;
               SpeedPWM_Value_right=350-(Station-70)*10;
               SpeedPWM_Value_left_jiansu=0;                          //PID柴麻議PWM 
              SpeedPWM_Value_right_jiansu=0;                          //PID柴麻議PWM 
       }
       else if(singleflag>0)
       {
              SpeedPWM_Value_left =500;
              SpeedPWM_Value_right=500;
              SpeedPWM_Value_left_jiansu=0 ;                          //PID柴麻議PWM 
              SpeedPWM_Value_right_jiansu=0 ;                          //PID柴麻議PWM                  
       }
       /*else if((Station<60)||(Station>80)&& singleflag==1)
       {
           /* if( SpeedPWM_Value_left>390 ||  SpeedPWM_Value_right>390)
            {
              diuxianflag=5;
            }*/
    /*        if(diuxianflag>0)
            {
                  SpeedPWM_Value_left=100;
                  SpeedPWM_Value_right=100;
                  SpeedPWM_Value_left_jiansu=100 ;                          //PID柴麻議PWM 
                  SpeedPWM_Value_right_jiansu=100 ;                          //PID柴麻議PWM 
            }
            else
            {
              SpeedPWM_Value_left=350+(Station-70)*10;
             SpeedPWM_Value_right=350-(Station-70)*10;
             SpeedPWM_Value_left_jiansu=0 ;                          //PID柴麻議PWM 
             SpeedPWM_Value_right_jiansu=0 ;  
            }
       }*/
       else if((Station<80)&&(Station>60)&&(CameraStation[3]>60 && CameraStation[3]<80)&&(singleflag==0))
      {
        SpeedPWM_Value_left =500;
        SpeedPWM_Value_right=500;
         SpeedPWM_Value_left_jiansu=0 ;                          //PID柴麻議PWM 
        SpeedPWM_Value_right_jiansu=0 ;                          //PID柴麻議PWM 
      }
      else
      {
        /*if(diuxianflag>0)
            {
                  SpeedPWM_Value_left=100;
                  SpeedPWM_Value_right=100;
                  SpeedPWM_Value_left_jiansu=100 ;                          //PID柴麻議PWM 
                  SpeedPWM_Value_right_jiansu=100 ;                          //PID柴麻議PWM 
            }*/
      //  else
        {
        SpeedPWM_Value_left=400+(Station-70)*10;
        SpeedPWM_Value_right=400-(Station-70)*10;
        SpeedPWM_Value_left_jiansu=0 ;                          //PID柴麻議PWM 
        SpeedPWM_Value_right_jiansu=0 ;                          //PID柴麻議PWM 
        }
      }
     
      /*if(diuxianflag>0||diuxianyanshi>0)
      {
        SpeedPWM_Value_left=300;
        SpeedPWM_Value_right=300;
      }*/
       if(SpeedPWM_Value_left<0)
         SpeedPWM_Value_left=0;
       if(SpeedPWM_Value_right<0)
         SpeedPWM_Value_right=0;
        FTM_PWM_Duty(FTM0 , CH0,SpeedPWM_Value_left_jiansu);                                           //FTM0 CH0 PWM補竃 �撒膸�陣崙
        FTM_PWM_Duty(FTM0 , CH1,SpeedPWM_Value_left);                              //FTM0 CH1 PWM補竃 �撒膸�陣崙  
        FTM_PWM_Duty(FTM0 , CH2,SpeedPWM_Value_right_jiansu);                                           //FTM0 CH0 PWM補竃 �撒膸�陣崙
        FTM_PWM_Duty(FTM0 , CH3,SpeedPWM_Value_right);                             //FTM0 CH1 PWM補竃 �撒膸�陣崙  
       /* FTM_PWM_Duty(FTM0 , CH0,0);                                           //FTM0 CH0 PWM補竃 �撒膸�陣崙
        FTM_PWM_Duty(FTM0 , CH1,300);                              //FTM0 CH1 PWM補竃 �撒膸�陣崙  
        FTM_PWM_Duty(FTM0 , CH2,0);                                           //FTM0 CH0 PWM補竃 �撒膸�陣崙
        FTM_PWM_Duty(FTM0 , CH3,300);*/
        
    }
    
    /*********************
    80ms殻會峇佩旗鷹粁
    *********************/    
    if(TIME0flag_80ms == 1)
    {        
      TIME0flag_80ms = 0 ;                                                    //賠茅扮寂炎崗了
      PTA16_OUT = ~PTA16_OUT ;                                                //霞編LED描妨      

      
       // SpeedPWM_Value+=SpeedControl(Speed_Count,Set_Speed,Speed_P,Speed_I,Speed_D) ;    //PID痕方柴麻PWM峙    
      
    }
    
    /*********************
    100ms殻會峇佩旗鷹粁
    *********************/
    if(TIME0flag_100ms == 1)
    { 
      TIME0flag_100ms = 0 ;
      
    }
    
    if(DMA_Over_Flag==1)
    {
      DMA_Over_Flag=0;      

 //     Camera_Black_single(&ADdata[21][0],&single[1],&single_left);
 //     Camera_Black_single(&ADdata[22][0],&single[2]);  
        
        
        Camera_Black1(&ADdata[12][0],&Rightblackedge[0],&Leftblackedge[0],&CameraStation[0]);
         left_num[0]=0;right_num[0]=0;
        for(int i=70;i>40;i--)
        {
          if(i<5)
            break;
          if(ADdata[12][i]<100)
            left_num[0]++;
        }
        for(int i=70;i<100;i++)
        {
          if(i>135)
            break;
          if(ADdata[12][i]<100)
            right_num[0]++;
        }
        Camera_Black2(&ADdata[14][0],&Rightblackedge[1],&Leftblackedge[1],&CameraStation[1]);
        left_num[1]=0;right_num[1]=0;
        for(int i=70;i>40;i--)
        {
          if(i<5)
            break;
          if(ADdata[14][i]<100)
            left_num[1]++;
        }
        for(int i=70;i<100;i++)
        {
          if(i>135)
            break;
          if(ADdata[14][i]<100)
            right_num[1]++;
        }
        Camera_Black3(&ADdata[16][0],&Rightblackedge[2],&Leftblackedge[2],&CameraStation[2]);
           left_num[2]=0;right_num[2]=0;
         for(int i=70;i>40;i--)
        {
          if(i<5)
            break;
          if(ADdata[16][i]<100)
            left_num[2]++;
        }
        for(int i=70;i<100;i++)
        {
          if(i>135)
            break;
          if(ADdata[16][i]<100)
            right_num[2]++;
        }
        Camera_Black4(&ADdata[10][0],&Rightblackedge[3],&Leftblackedge[3],&CameraStation[3]);
        left_num[3]=0;right_num[3]=0;
        for(int i=70;i>40;i--)
        {
          if(i<5)
            break;
          if(ADdata[10][i]<100)
            left_num[3]++;
        }
        for(int i=70;i<100;i++)
        {
          if(i>135)
            break;
          if(ADdata[10][i]<100)
            right_num[3]++;
        }
        Camera_Black5(&ADdata[3][0],&Rightblackedge[4],&Leftblackedge[4],&CameraStation[4]);
        left_num[4]=0;right_num[4]=0;
        for(int i=70;i>40;i--)
        {
          if(i<5)
            break;
          if(ADdata[3][i]<100)
            left_num[4]++;
        }
        for(int i=70;i<100;i++)
        {
          if(i>135)
            break;
          if(ADdata[3][i]<100)
            right_num[4]++;
        }
    }  
     
     
  }
  
  
  
  }
}


/*
    欠(かぜ)　仟(あたら)しく　駄(みどり)を�l(か)ける
　　どこまでも垓(とお)く　確(す)み局(わた)るよ
　　書(いま)　�X(かろ)やかに　高(ひかり)は指(まわ)る
　　畠(すべ)てをやわらかく孚(て)らすだろう
　　佛(ほし)さえ需(み)えない
　　嚏(あめ)の扮(とき)でも
　　埴(きみ)が知(ゆめ)需(み)てる隆栖(みらい)は
　　迦(そば)にあるよ
　　いつの晩(ひ)も梧(うた)おう
　　この伉(こころ)のまま
　　��(ひび)くよ　腎(そら)の��(む)こう
　　泳圭(かなた)まで
　　そしてまたどこかで
　　埴(きみ)に曙(とど)いたら
　　房(おも)い竃(だ)してほしい
　　勦(かがや)く丶冲(えがお)で狛(す)ごした晩？(ひび)を
　　欠(かぜ)　邑(す)き宥(とお)り　寄仇(だいち)にそよぐ
　　單(やさ)しく扮寂(じかん)を淫(つつ)んでるよ
　　書(いま)　�g(おだ)やかに　高(ひかり)は廣(そそ)ぐ
　　畠(すべ)てを��(なつ)かしく孚(て)らすだろう
　　祇(みち)さえ需(み)えない
　　��(やみ)の扮(とき)でも
　　埴(きみ)が佚(しん)じてる隆栖(みらい)は
　　迦(そば)にあるよ
　　いつの晩(ひ)も梧(うた)おう
　　この伉(こころ)のまま
　　丑(かな)しみも階(こ)えて佩(い)く
　　膿(つよ)い蕗(こえ)
　　埴(きみ)がその啾��(ゆうき)で
　　匯�i(いっぽ)序(すす)む扮(とき)
　　房(おも)い竃(だ)してほしい
　　四(きらめ)く憂(ひとみ)で狛(す)ごした晩？(ひび)を
　　いつの晩(ひ)も梧(うた)おう
　　この伉(こころ)のまま
　　��(ひび)くよ　腎(そら)の��(む)こう
　　泳圭(かなた)まで
　　そしてまたどこかで
　　埴(きみ)に曙(とど)いたら
　　房(おも)い竃(だ)してほしい
　　四(きらめ)く憂(ひとみ)で狛(す)ごした晩？(ひび)を
　　勦(かがや)く丶冲(えがお)で狛(す)ごした晩？(ひび)を
*/
