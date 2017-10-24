/** 
 * Codigo para Arduino de la consola del llamado de enfermeras
 * Obtiene pulsos para hacer llamado al panel led he imprimir ubicacion
 * Genera tiempo que duro el pulso y envia este mediante serial a la raspberry pi
 * Escribe mediante protocolo en el serial para envio de datos a pantalla led con codigos
 * m mensajes
 * h hora
 * a codigo azul
 * v codigo verde
 * lee hora desde RTC
 * 
 * 
 * Version:             2.9
 * Fecha:               24/10/2017
 * Creado por:          Fabian Garzon reado para la clinica itagui para 14 puntos independientes 
 * Editado ultima vez:  Boris Urrea
 * Correo:              borisan999@gmail.com
**/
#include "RTClib.h"
#include <Wire.h>
  bool DEBUG=true;
  bool alerta = false;
  unsigned long time2=0; 
  unsigned long time3=0; 
  unsigned long time4=0; 
  unsigned long time_led=0; 
  int TIEMPO_MENSAJE=4;//se multiplica por 10.5 segundos
  int TIEMPO_HORA=2;//se multiplica por 10.5 segundos
  int conta_serial=0;
  int T=3; 
  int E=10000;  
  unsigned long idtiempo[64];
  int idpin[64]={4,23,39,2,63,50,41,34,25,56,48,64,43,32,27,57,65,46,45,29,30,58,66,44,28,31,47,59,67,42,49,33,26,60,68,40,35,51,24,61,38,69,37,53,22,52,62,36,11,12,7,6,9,10,8,13,55,3,5,54};
  String llamadopin[64]={" COD. AZUL 200 "," COD. AZUL 201 "," COD. AZUL 202 "," COD. AZUL 203 "," COD. AZUL 204 "," COD. AZUL 205 "," COD. AZUL 206 "," COD. AZUL 207 "," COD. AZUL 208 "," COD. AZUL 209 "," COD. AZUL 210 "," COD. AZUL 211 "," COD. AZUL 212 "," COD. AZUL 213 "," COD. AZUL 214 "," COD. AZUL 215 "," COD. AZUL 216 "," COD. AZUL 217 "," COD. AZUL 218 "," COD. AZUL 219 "," COD. AZUL 220 "," COD. AZUL 221 "," COD. AZUL 222 "," COD. AZUL 223 "," COD. AZUL 224 "," COD. AZUL 225 "," COD. AZUL 226 "," COD. AZUL 227 "," COD. AZUL 228 "," COD. AZUL 229 "," COD. AZUL 230 "," COD. AZUL 231 "," COD. AZUL 232 "," COD. AZUL 233 "," COD. AZUL 234 "," COD. AZUL 235 "," COD. AZUL 236 "," COD. AZUL 237 "," COD. AZUL 238 "," COD. AZUL 239 "," COD. AZUL 240 "," COD. AZUL 241 "," COD. AZUL 242 "," COD. AZUL 243 "," COD. AZUL 244 "," COD. AZUL 245 "," COD. AZUL 246 "," COD. AZUL 247 "," COD. AZUL 248 "," COD. AZUL 249 "," COD. AZUL 250 "," COD. AZUL 251 "," COD. AZUL 252 "," COD. AZUL 253 "," COD. AZUL 254 "," COD. AZUL 255 "," COD. AZUL 256 "," COD. AZUL 257 "," COD. AZUL 258 "," COD. AZUL 259 "};
  int alertapin[64]={1,1,1,2,3,1,1,1,2,3,1,1,1,2,3,1,1,1,2,3,1,1,1,2,3,1,1,1,2,3,1,1,1,2,3,1,1,1,2,3,1,1,1,2,3,1,1,1,2,3,1,1,1,2,3,1,1,1,2,3};
  int pa=0;
  RTC_DS1307 RTC;
  void setup()
  { 
  for (int i = 0; i < 59; i = i + 1) {
  pinMode(idpin[i],INPUT);
      
    }
  Serial1.begin(9600);
  Serial.begin(9600);
  RTC.begin();  
  }
 
  
  void loop()
 {
  //Serial.println("inicio loop");
  delay (50);
  // jack 1.2 PREPARACION CAMA 1 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
   for (int i = 0; i < 59; i = i + 1) {
     pa =  digitalRead(idpin[i]); //ping 
     if(pa == HIGH ) {
     if(idtiempo[i]==0){
       idtiempo[i]=millis();
       llama_led_v(llamadopin[i]);
      } 
      time2 = millis();
      time3 = time2-time_led;  
      if( time3 > E ){// imprime en pantalla cada 10000
          time3=0; 
          llama_led_v(llamadopin[i]);
      }
    }
    if(pa == LOW && idtiempo[i]>0){// cuando detecta pulso abajo calcula tiempo y envia a raspberry
       time2 = millis();
       time3 = (time2-idtiempo[i])/1000;  
       idtiempo[i]=0;
       String cadena1="i";
       String cadena2= String(i);
       String cadena3=",";
       
       String cadena4="f"; 
       if (time3 > T) {                            //si el tiempo de pulsado el pulsador es mayor a 5 segundos imprime el tiempo en el reporte 
       Serial.println( cadena1+cadena2+cadena3+time3+cadena3+alertapin[i]+cadena4 );
       }
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
    char TimeNow[20] = "      11:33     "  ;
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
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   void writeString(String stringData) {// Escribe datos por serial
      for (int i = 0; i < stringData.length(); i++)
      {
        Serial1.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
      }
      Serial1.write('\n');
    }// end writeString

