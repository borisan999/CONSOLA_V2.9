/** 
 * Codigo para Arduino de la consola del llamado de enfermeras ATENTO
 * Obtiene pulsos para hacer llamado al panel led he imprimir ubicacion
 * Genera tiempo que duro el pulso y envia este mediante serial a la raspberry pi
 * Escribe mediante protocolo en el serial para envio de datos a pantalla led
 * escribe letra v para alertas verdes
 * Escribe letra a para alertas azules
 * Escribe letra h para enviar hora leida en el RTC
 * Escribe letra m para indicar a la pantalla que puede imprimir mensajes pregrabados
 * 
 * Version:             2.9
 * Fecha:               20/10/2017
 * Creado por:          Fabian Garzon
 * Editado ultima vez:  Boris Urrea
 * Correo:              borisan999@gmail.com
**/

#include "RTClib.h"
#include <Wire.h>
  bool DEBUG=false;
  bool alerta = false;
  unsigned long time2=0; 
  unsigned long time3=0; 
  unsigned long time4=0; 
  unsigned long time_led=0; 
  int TIEMPO_MENSAJE=4;//se multiplica por 10.5 segundos
  int TIEMPO_HORA=2;//se multiplica por 10.5 segundos
  int conta_serial=0;
  unsigned long T=3; 
  unsigned long E=10000;  
  const int p1   =4;    
  const int p2   =23;  //no funciona  
  const int p3   =39;  
  const int p4   =2;
  const int p5   =63; //punto con falla revienta 219    
  const int p6   =50; //
  const int p7   =41;     
  const int p8   =34; //funciona perfecto 
  const int p9   =25;   
  const int p10  =56;    
  const int p11  =48;    
  const int p12  =64;  
  const int p13  =43;    
  const int p14  =32;  
  const int p15  =27;       
  const int p16  =57; 
  const int p17  =65; 
  const int p18  =46;
  const int p19  =45;  
  const int p20  =29;        
  const int p21  =30; 
  const int p22  =58; 
  const int p23  =66; 
  const int p24  =44; 
  const int p25  =28;         
  const int p26  =31;    
  const int p27  =47;  
  const int p28  =59;
  const int p29  =67; 
  const int p30  =42; 
  const int p31  =49; 
  const int p32  =33; 
  const int p33  =26; 
  const int p34  =60;  
  const int p35  =68;     
  const int p36  =40; 
  const int p37  =35; 
  const int p38  =51; 
  const int p39  =24; 
  const int p40  =61;  
  const int p41  =38;
  const int p42  =69;
  const int p43  =37;
  const int p44  =53;
  const int p45  =22; 
  const int p46  =52;
  const int p47  =62;
  const int p48  =36;
  const int p49  =11; //jack.1.1 ok 
  const int p50  =12; //jack1.2 ok 
  const int p51  =7 ;  //jack 13.1 ok
  const int p52  =6 ;  //jack 13.2 ok
  const int p53  =9 ;  //jack 2.1
  const int p54  =10;  //jack 2.2
  const int p58  =8 ;//jack 3.2  
  const int p60  =13; //jack 15.2
  const int p61  =55;  //a1 jack 4.1ok 
  const int p62  =3 ;  //jack 4.2
  const int p63  =5 ; //jack 16.1 ok 
  const int p64  =54;  //ao jack 16.2
 
 
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////       
  
  int pa1 =0;    int pa2 =0;    int pa3 =0;     int pa4 =0;    int pa5 =0;    int pa6 =0;   int pa7 =0;    int pa8 =0;    int pa9 =0;     int pa10 =0;   int pa11 =0;   int pa12 =0;   
  int pa13 =0;   int pa14 =0;   int pa15 =0;    int pa16 =0;   int pa17 =0;   int pa18 =0;  int pa19 =0;   int pa20 =0;   int pa21 =0;    int pa22 =0;   int pa23 =0;   int pa24 =0; 
  int pa25 =0;   int pa26 =0;   int pa27 =0;    int pa28 =0;   int pa29 =0;   int pa30 =0;  int pa31 =0;   int pa32 =0;   int pa33 =0;    int pa34 =0;   int pa35 =0;   int pa36 =0;  
  int pa37 =0;   int pa38 =0;   int pa39 =0;    int pa40 =0;   int pa41 =0;   int pa42 =0;  int pa43 =0;   int pa44 =0;   int pa45 =0;    int pa46 =0;   int pa47 =0;   int pa48 =0;
  int pa49 =0;   int pa50 =0;   int pa51 =0;    int pa52 =0;   int pa53 =0;   int pa54 =0;   
  int pa60 =0; int pa58 =0;
  int pa61 =0;   int pa62 =0;   int pa63 =0;    int pa64 =0;  
 
 //////////////////////////////////////////////////////////////////////////MATRIX PARA 1000 PUNTOS DE LLAMADO ENFERMERAS  //////////////////////////////////////////////////////////////////
 unsigned long idtiempo[1000];
  RTC_DS1307 RTC;
  void setup()
  { 
  pinMode(p1,INPUT);    pinMode(p2,INPUT);  pinMode(p3,INPUT);  pinMode(p4,INPUT);  pinMode(p5,INPUT);   pinMode(p6,INPUT);  pinMode(p7,INPUT); pinMode(p8,INPUT);  
  pinMode(p9,INPUT);    pinMode(p10,INPUT); pinMode(p11,INPUT); pinMode(p12,INPUT); pinMode(p13,INPUT);  pinMode(p14,INPUT); pinMode(p15,INPUT);pinMode(p16,INPUT);
  pinMode(p17,INPUT);   pinMode(p18,INPUT); pinMode(p19,INPUT); pinMode(p20,INPUT); pinMode(p21,INPUT);  pinMode(p22,INPUT); pinMode(p23,INPUT);pinMode(p24,INPUT); 
  pinMode(p25,INPUT);   pinMode(p26,INPUT); pinMode(p27,INPUT); pinMode(p28,INPUT); pinMode(p29,INPUT);  pinMode(p30,INPUT); pinMode(p31,INPUT);pinMode(p32,INPUT); 
  pinMode(p33,INPUT);   pinMode(p34,INPUT); pinMode(p35,INPUT); pinMode(p36,INPUT); pinMode(p37,INPUT);  pinMode(p38,INPUT); pinMode(p39,INPUT);pinMode(p40,INPUT); 
  pinMode(p41,INPUT);   pinMode(p42,INPUT); pinMode(p43,INPUT); pinMode(p44,INPUT); pinMode(p45,INPUT);  pinMode(p46,INPUT); pinMode(p47,INPUT);pinMode(p48,INPUT);
  pinMode(p49,INPUT);   pinMode(p50,INPUT); pinMode(p51,INPUT); pinMode(p52,INPUT); pinMode(p53,INPUT);  pinMode(p54,INPUT);
  pinMode(p58,INPUT);  pinMode(p60,INPUT); pinMode(p61,INPUT);  pinMode(p62,INPUT); pinMode(p63,INPUT);pinMode(p64,INPUT);
 // pinMode(20,OUTPUT); 
  Serial1.begin(9600);
  Serial.begin(9600);
  RTC.begin();  
  }
 
  
  void loop()
 {
  // jack 1.2 PREPARACION CAMA 1 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
   
     pa50 =  digitalRead(p50); //ping 
     if(pa50 == HIGH ) {
     if(idtiempo[1]==0){
       idtiempo[1]=millis();
       llama_led_v(" COD. AZUL 203 ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
          time3=0; 
          llama_led_v(" COD. AZUL 203 ");
      }
    }
    if(pa50 == LOW && idtiempo[1]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[1])/1000;  
       idtiempo[1]=0;
       String cadena1="i1,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
       Serial.println( cadena1+time3+cadena2 );
       }
    }
//jack 2.2   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   pa54 =  digitalRead(p54); //ping 
   if(pa54 == HIGH ) {
    if(idtiempo[2]==0){
      idtiempo[2]=millis();
      llama_led_v("COD. AZUL 205 ");
    } 
    time2 = millis();
    time3 = (time2-time_led);  
    if( time3 > E ){
        time3=0;
      llama_led_v(" COD. AZUL 205 ");
  
    }
  }
  if(pa54 == LOW && idtiempo[2]>0){
    time2 = millis();
    time3 = (time2-idtiempo[2])/1000; 
    idtiempo[2]=0;
    String cadena1="i2,";String cadena2=",2f"; 
    if (time3 > T) 
    {
      Serial.println( cadena1+time3+cadena2 );
    }
  }

///11  /*jack 3.2 *////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
 
    pa58 =  digitalRead(p58); //ping 39
    if(pa58 == HIGH ) {
     if(idtiempo[3]==0){
       idtiempo[3]=millis();
       llama_led_v(" COD. AZUL 215 ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
        llama_led_v(" COD. AZUL 215 ");
      }
    }
    if(pa58 == LOW && idtiempo[3]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[3])/1000;  
       idtiempo[3]=0;
       String cadena1="i3,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    }      
                   
//jack 4.2  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    pa62 =  digitalRead(p62); //ping 
    if(pa62 == HIGH ) {
     if(idtiempo[4]==0){
       idtiempo[4]=millis();
       llama_led_v(" COD. AZUL 206 ");
         // Serial.println( "llega a llamado 1" );
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
        llama_led_v(" COD. AZUL 206 ");
       //  Serial.println( "llega a llamado 2" );
      }
    }
    if(pa62 == LOW && idtiempo[4]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[4])/1000;  
       idtiempo[4]=0;
       String cadena1="i4,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    }           

//jack 5.2 10   /*jack 5.3 */  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   pa2 =  digitalRead(p2); //ping 23
   if(pa2 == HIGH ) {
    if(idtiempo[5]==0){
      idtiempo[5]=millis();
      llama_led_v("COD. AZUL 207");
    } 
    time2 = millis();
    time3 = (time2-time_led);  
    if( time3 > E ){
        time3=0;
      llama_led_v("COD. AZUL 207");
  
    }
  }
  if(pa2 == LOW && idtiempo[5]>0){
    time2 = millis();
    time3 = (time2-idtiempo[5])/1000; 
    idtiempo[5]=0;
    String cadena1="i5,";String cadena2=",2f"; 
    if (time3 > T) 
    {
      Serial.println( cadena1+time3+cadena2 );
    }
  }

//15  /*jack 6.2*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
 pa8 =  digitalRead(p8); //ping 43
    if(pa8 == HIGH ) {
     if(idtiempo[6]==0){
       idtiempo[6]=millis();
       llama_led_v(" COD. AZUL 208 ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
        llama_led_v(" COD. AZUL 208 ");
      }
    }
    if(pa8 == LOW && idtiempo[6]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[6])/1000;  
       idtiempo[6]=0;
       String cadena1="i6,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    }  


//18  /*jack 7.2 */ ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 pa14 =  digitalRead(p14); //ping 
    if(pa14 == HIGH ) {
     if(idtiempo[7]==0){
       idtiempo[7]=millis();
       llama_led_v(" COD. AZUL 209 ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
        llama_led_v(" COD. AZUL 209 ");
      }
    }
    if(pa14 == LOW && idtiempo[7]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[7])/1000;  
       idtiempo[7]=0;
       String cadena1="i7,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    }  



 //21  /*jack 8.2 */ ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 pa20 =  digitalRead(p20); //ping 
    if(pa20 == HIGH ) {
     if(idtiempo[8]==0){
       idtiempo[8]=millis();
       llama_led_v(" COD. AZUL 210 ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
        llama_led_v(" COD. AZUL 210 ");
      }
    }
    if(pa20 == LOW && idtiempo[8]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[8])/1000;  
       idtiempo[8]=0;
       String cadena1="i8,";String cadena2=",1f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    }



// jack 9.2////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 pa26 =  digitalRead(p26); //ping 
    if(pa26 == HIGH ) {
     if(idtiempo[9]==0){
       idtiempo[9]=millis();
           llama_led_v(" COD. AZUL 211 ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
            llama_led_v(" COD. AZUL 211 ");
      }
    }
    if(pa26 == LOW && idtiempo[9]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[9])/1000;  
       idtiempo[9]=0;
       String cadena1="i9,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    }

 //23  /*jack 10.2 */ ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 pa32 =  digitalRead(p32); //ping 
    if(pa32 == HIGH ) {
     if(idtiempo[10]==0){
       idtiempo[10]=millis();
          llama_led_v("  COD. AZUL 212  ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
          llama_led_v(" COD. AZUL 212  ");
      }
    }
    if(pa32 == LOW && idtiempo[10]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[10])/1000;  
       idtiempo[10]=0;
       String cadena1="i10,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    }

 //24   /*jack 11.1 */ ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 pa37 =  digitalRead(p37); //ping 49
    if(pa37 == HIGH ) {
     if(idtiempo[11]==0){
       idtiempo[11]=millis();
       llama_led_v(" COD. AZUL 213 ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
        llama_led_v(" COD. AZUL 213 ");
      }
    }
    if(pa37 == LOW && idtiempo[11]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[11])/1000;  
       idtiempo[11]=0;
       String cadena1="i11,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
  }    

 //27   /*jack 12.2 */////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
      pa44 =  digitalRead(p44); //ping 
    if(pa44 == HIGH ) {
     if(idtiempo[12]==0){
       idtiempo[12]=millis();
       llama_led_v(" COD. AZUL 214 ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
        llama_led_v(" COD. AZUL 214 ");
      }
    }
    if(pa44 == LOW && idtiempo[12]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[12])/1000;  
       idtiempo[12]=0;
       String cadena1="i12,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    }      


//30 /*jack 13.2 */ ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
       pa52 =  digitalRead(p52); //ping 
    if(pa52 == HIGH ) {
     if(idtiempo[13]==0){
       idtiempo[13]=millis();
       llama_led_v(" COD. AZUL 204 ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
        llama_led_v(" COD. AZUL 204 ");
      }
    }
    if(pa52 == LOW && idtiempo[13]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[13])/1000;  
       idtiempo[13]=0;
       String cadena1="i13,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    } 

//41  /*jack 14.2  */    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
   pa9 =  digitalRead(p9); //ping 
    if(pa9 == HIGH ) {
     if(idtiempo[14]==0){
       idtiempo[14]=millis();
       llama_led_v(" COD. AZUL 216 ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
        llama_led_v(" COD. AZUL 216 ");
      }
    }
    if(pa9 == LOW && idtiempo[14]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[14])/1000;  
       idtiempo[14]=0;
       String cadena1="i14,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    }                   
                 
//44  /*jack 15.2 */ ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
    pa60 =  digitalRead(p60); //ping 
    if(pa60 == HIGH ) {
     if(idtiempo[15]==0){
       idtiempo[15]=millis();
       llama_led_v(" COD. AZUL 217 ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
        llama_led_v(" COD. AZUL 217 ");
      }
    }
    if(pa60 == LOW && idtiempo[15]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[15])/1000;  
       idtiempo[15]=0;
       String cadena1="i15,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    }  

//47 /*jack 16 */ ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
    pa64 =  digitalRead(p64); //ping 
    if(pa64 == HIGH ) {
     if(idtiempo[16]==0){
       idtiempo[16]=millis();
       llama_led_v(" COD. AZUL 218 ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
        llama_led_v(" COD. AZUL 218 ");
      }
    }
    if(pa64 == LOW && idtiempo[16]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[16])/1000;  
       idtiempo[16]=0;
       String cadena1="i16,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    }  



 //50  /*jack 17.2 */ PING 58 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 pa5 =  digitalRead(p5); //ping 
    if(pa5 == HIGH ) {
     if(idtiempo[17]==0){
       idtiempo[17]=millis();
       llama_led_v(" COD. AZUL 219 ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
        llama_led_v(" COD. AZUL 219 ");
      }
    }
    if(pa5 == LOW && idtiempo[17]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[17])/1000;  
       idtiempo[17]=0;
       String cadena1="i17,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    }  
//53 /*jack 18.2 */////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      pa11 =  digitalRead(p11); //ping 
      if(pa11 == HIGH ) {
      if(idtiempo[18]==0){
       idtiempo[18]=millis();
       llama_led_v("  COD. AZUL 220  ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
        llama_led_v("  COD. AZUL 220 ");
      }
    }
    if(pa11 == LOW && idtiempo[18]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[18])/1000;  
       idtiempo[18]=0;
       String cadena1="i18,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    }  

// /*jack 19.2 */ ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  
       pa17 =  digitalRead(p17); //ping 60
      if(pa17 == HIGH ) {
      if(idtiempo[19]==0){
       idtiempo[19]=millis();
       llama_led_v(" COD. AZUL 221 ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
        llama_led_v(" COD. AZUL 221 ");
      }
    }
    if(pa17 == LOW && idtiempo[19]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[19])/1000;  
       idtiempo[19]=0;
       String cadena1="i19,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    }  

//59 /*jack 20.2 */  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
    pa23 =  digitalRead(p23); //ping 
      if(pa23 == HIGH ) {
      if(idtiempo[20]==0){
       idtiempo[20]=millis();
       llama_led_v(" COD. AZUL 222 ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
        llama_led_v(" COD. AZUL 222 ");
      }
    }
    if(pa23 == LOW && idtiempo[20]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[20])/1000;  
       idtiempo[20]=0;
       String cadena1="i20,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    }                  


//59 /*jack 21.2 */  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
    pa29 =  digitalRead(p29); //ping 
      if(pa29 == HIGH ) {
      if(idtiempo[21]==0){
       idtiempo[21]=millis();
       llama_led_v(" COD. AZUL 223 ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
        llama_led_v(" COD. AZUL 223 ");
      }
    }
    if(pa29 == LOW && idtiempo[21]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[21])/1000;  
       idtiempo[21]=0;
       String cadena1="i21,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    }                  

//59 /*jack 22.2 */  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
    pa35 =  digitalRead(p35); //ping 
      if(pa35 == HIGH ) {
      if(idtiempo[22]==0){
       idtiempo[22]=millis();
       llama_led_v(" COD. AZUL 224 ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
        llama_led_v(" COD. AZUL 224 ");
      }
    }
    if(pa35 == LOW && idtiempo[22]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[22])/1000;  
       idtiempo[22]=0;
       String cadena1="i22,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    }                  

//59 /*jack 23.2 */  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
    pa41 =  digitalRead(p41); //ping 
      if(pa41 == HIGH ) {
      if(idtiempo[23]==0){
       idtiempo[23]=millis();
       llama_led_v(" COD. AZUL 225 ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
        llama_led_v(" COD. AZUL 225 ");
      }
    }
    if(pa41 == LOW && idtiempo[23]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[23])/1000;  
       idtiempo[23]=0;
       String cadena1="i23,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    }                  


//59 /*jack 24.2 */  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
    pa47 =  digitalRead(p47); //ping 
      if(pa47 == HIGH ) {
      if(idtiempo[24]==0){
       idtiempo[24]=millis();
       llama_led_v(" COD. AZUL 226 ");
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
        time3=0; 
        llama_led_v(" COD. AZUL 226 ");
      }
    }
    if(pa47 == LOW && idtiempo[24]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[24])/1000;  
       idtiempo[24]=0;
       String cadena1="i24,";String cadena2=",2f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
         Serial.println( cadena1+time3+cadena2 );
       }
    }

  /////////////////////////////////////////////////////////////////////////restablecimiento de tiempos a cero DENTRO DE INICIO
   time2 = millis();//Maneja el tiempo para que se imrpima en led
   time3 = time2-time_led;  
   if( time3 > 10500 ){
    if(alerta==false)
    {
      if(conta_serial>=TIEMPO_HORA)
      {
        hora();
      }
      conta_serial++;
      if(conta_serial>=TIEMPO_MENSAJE)
      {
        llama_led_m();
        conta_serial=0;
      }   
    }
    alerta=false;
     time_led= millis();
     time2 = 0;
     time3 = 0;
  }

 }//end inicio
 
String inData2; 
const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data
boolean newData = false;

String Codigo_H="h";
  void hora() // Imprime hora en pantalla
  { 
    if(DEBUG == true)
      {
        delay(50);
        Serial.print("LLEGA A HORA");
      }
    //DateTime now = RTC.now();
    char TimeNow[20] = "      04:22";
    //sprintf(TimeNow,"      %.2d:%.2d",now.hour(),now.minute());
    writeString("123");
    delay(50);
    int cont=0;
      while(true) 
      {
       cont++;
       recvWithEndMarker();
       delay(20);
       if( ( receivedChars[0] == '4' ) && ( receivedChars[1] == '5' ) && ( receivedChars[2] == '6' ) ){
         memset(receivedChars, 0, sizeof(receivedChars));
         newData = false;
         Codigo_H.concat(TimeNow);
          if(DEBUG == true)
          {
            delay(50);
            Serial.print(Codigo_H);
          }
         writeString(Codigo_H);
         delay(1000);
         Codigo_H="h";
         break;
       }else{
        if(cont>5)
        {
            writeString("123");
            delay(50);
        }
        if(cont>10)
        {
          memset(receivedChars, 0, sizeof(receivedChars));
          newData = false;
          break;   
        }
       }   
    } 
  }

////////////////////////////////////////////////////////////////////////////////////////////CODIGO AZUL 
String Codigo_A="a";
  void llama_led_a(String msn)//Protocolo para enviar por serial con codigo a, que deja estaticas las letras y genera sonido
  {
     if(DEBUG == true)
      {
        delay(50);
        Serial.print("codigo a");
        Serial.print(msn);
      }
    alerta =true;
    writeString("123");
    delay(50);
    int cont=0;
      while(true) 
      {
       cont++;
       recvWithEndMarker();
       delay(100);
       if( ( receivedChars[0] == '4' ) && ( receivedChars[1] == '5' ) && ( receivedChars[2] == '6' ) ){
         memset(receivedChars, 0, sizeof(receivedChars));
         newData = false;
         Codigo_A.concat(msn);
         writeString(Codigo_A);
          delay(3100);
         Codigo_A="a";
         break;
       }else{
        if(cont>5)
        {
            writeString("123");
            delay(50);
        }
        if(cont>10)
        {
          newData = false;
          break;   
        }
       }   
    } 
  }
 //////////////////////////////////////////////////////////////////CODIGO NORMAL SONIDO 1  
String Codigo_V="v";
  void llama_led_v(String msn)//Protocolo para enviar por serial con codigo v, quemueve los caracteres de arriba a abajo con sonido 
  {
         if(DEBUG == true)
      {
        delay(50);
        Serial.print("codigo v");
        Serial.print(msn);
      }
    alerta =true;
    writeString("123");
    delay(50);
    int cont=0;
      while(true) 
      {
       cont++;
       recvWithEndMarker();
       delay(100);
       if( ( receivedChars[0] == '4' ) && ( receivedChars[1] == '5' ) && ( receivedChars[2] == '6' ) ){
         memset(receivedChars, 0, sizeof(receivedChars));
         newData = false;
         Codigo_V.concat(msn);
         writeString(Codigo_V);
         delay(6000);
         Codigo_V="v";
         break;
       }else{
        if(cont>5)
        {
            writeString("123");
            delay(50);
        }

       if(cont>10)
        {
          newData = false;
          break;   
        }
       }   
    } 
  }
   //////////////////////////////////////////////////////////////////CODIGO PARA MENSAJES  
String Codigo_M="m";
  void llama_led_m()//Protocolo para enviar por serial con codigo v, quemueve los caracteres de arriba a abajo con sonido 
  {
         if(DEBUG == true)
      {
        delay(50);
        Serial.print("codigo m");
      }
    alerta =true;
    writeString("123");
    delay(50);
    int cont=0;
      while(true) 
      {
       cont++;
       recvWithEndMarker();
       delay(100);
       if( ( receivedChars[0] == '4' ) && ( receivedChars[1] == '5' ) && ( receivedChars[2] == '6' ) ){
        memset(receivedChars, 0, sizeof(receivedChars));
         newData = false;
         writeString(Codigo_M);
         delay(100);
         Codigo_M="m";
         break;
       }else{
        if(cont>5)
        {
            writeString("123");
            delay(50);
        }

       if(cont>10)
        {
          newData = false;
          break;   
        }
       }   
    } 
  }
  String Codigo_x="x";
  void llama_led_x()//Protocolo para enviar por serial con codigo v, quemueve los caracteres de arriba a abajo con sonido 
  {
         if(DEBUG == true)
      {
        delay(50);
        Serial.print("codigo x");
      }
    alerta =true;
    writeString("123");
    delay(50);
    int cont=0;
      while(true) 
      {
       cont++;
       recvWithEndMarker();
       delay(20);
       if( ( receivedChars[0] == '4' ) && ( receivedChars[1] == '5' ) && ( receivedChars[2] == '6' ) ){
        memset(receivedChars, 0, sizeof(receivedChars));
         newData = false;
         Codigo_x.concat(".");
         writeString(Codigo_x);
         delay(2000);
         Codigo_x="x";
         break;
       }else{
        if(cont>5)
        {
            writeString("123");
            delay(50);
        }

       if(cont>10)
        {
          newData = false;
          break;   
        }
       }   
    } 
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void recvWithEndMarker() {//recibe datos por serial
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    while (Serial1.available() > 0 && newData == false) {
      rc = Serial1.read();
      
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        ndx = 0;
        newData = true;
      }
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   void writeString(String stringData) {// Escribe datos por serial
      for (int i = 0; i < stringData.length(); i++)
      {
        Serial1.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
      }
      Serial1.write('\n');
    }// end writeString

