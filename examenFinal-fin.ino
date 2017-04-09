#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

int duracion=250; //Duración del sonido
int fMin=50; //Frecuencia más baja que queremos emitir
int fMax=100; //Frecuencia más alta que queremos emitir
int jj=0;
int blinky=30,pinky=31,inkey=32,clyde=33,aux2=0;
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int i ,j,asustar,contadorAsustar ;
int life=3;
int nextLeft,nextRight,nextUp,nextDown,contNext=0;
int yObjetivo,xObjetivo;
int muere30,muere31,muere32,muere33;
int carmov1,carmov2,carmov3;
int antghost;

#define  c3    7634
#define  d3    6803
#define  e3    6061
#define  f3    5714
#define  g3    5102
#define  a3    4545
#define  b3    4049

#define  c4    3816    // 261 Hz
#define  d4    3401    // 294 Hz
#define  e4    3030    // 329 Hz
#define  f4    2865    // 349 Hz
#define  fs4   2718       //369
#define  g4    2551    // 392 Hz
#define  gs4   2420    
#define  a4    2272    // 440 Hz
#define  a4s   2146
#define  b4    2028    // 493 Hz

#define  c5    1912    // 523 Hz
#define  d5    1706
#define  d5s   1608
#define  e5    1517    // 659 Hz
#define  f5    1433    // 698 Hz
#define  g5    1276
#define  a5    1136
#define  a5s   1073
#define  b5    1012
#define  c6    955

#define  R     0   
int melody1[] = {  d4,R,b4,R,fs4,R,d4,R,b4,R,fs4,R,e4,R,c4,R,g4,R,e4,R,g4,R,d4,R,b4,R,fs4,R,d4,R,b4,R,fs4,R,e4,R,f4,R,g4,R,g4,R,gs4,R,a4,R,a4,R,b4,R,b4,R,c4,R};
int beats1[]  = {  20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,20, 20, 20, 20, 20, 20, 20, 20, 20, 20,20, 20, 20, 20, 20, 20, 20, 20, 20, 20}; 
int MAX_COUNT = sizeof(melody1) / 2;
long tempo = 10000;
int pause = 1000;
int rest_count = 50;
int toneM = 0;
int beat = 0;
long duration  = 0;
int potVal = 0;
int speakerOut = 47;
int led = 6;
int auxAsustarB=0,auxAsustarP=0,auxAsustarI=0,auxAsustarC=0;
int antyghost ,antxghost ,xghost =9,yghost =8;    //red
int antyghostP,antxghostP,xghostP=9,yghostP=8;
int antyghostC,antxghostC,xghostC=9,yghostC=8;
int antyghostO,antxghostO,xghostO=9,yghostO=8;

int x,y,xx=0,xxx,yy=0,yyy,xo,yo,fallaX=0,direccionMov,auxiliarDireccionMov;
int xxxant,yyyant,chooseWay;
char mat[22][19];
unsigned long despliegue();
unsigned long cargadoniv();
char dato;
int aux;
int pasos=0,score=0,antpasos=0,antscore=0,datox,xant,yant,datoy,contadorNivel;
const int analogInPin = A8;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to
char niv1[22][19]= { {10,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1},
                     {1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1},
                     {1 ,0 ,1 ,1 ,0 ,1 ,1 ,1 ,0 ,1 ,0 ,1 ,1 ,1 ,0 ,1 ,1 ,0 ,1},
                     {1 ,34,1 ,1 ,0 ,1 ,1 ,1 ,0 ,1 ,0 ,1 ,1 ,1 ,0 ,1 ,1 ,34,1},
                     {1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1},
                     {1 ,0 ,1 ,1 ,0 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,0 ,1 ,0 ,1 ,1 ,0 ,1},
                     {1 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,1},
                     {1 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,7 ,1 ,7 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,1},
                     {7 ,7 ,7 ,1 ,0 ,1 ,7 ,7 ,7 ,7, 7 ,7 ,7 ,1 ,0 ,1 ,7 ,7 ,7},
                     {7 ,7 ,7 ,1 ,0 ,1 ,7 ,1 ,1 ,1 ,1 ,1 ,7 ,1 ,0 ,1 ,1 ,1 ,1},
                     {1 ,1 ,1 ,1 ,0 ,7 ,7 ,1 ,31 ,32 ,33 ,1 ,7 ,7 ,0 ,7 ,7 ,7 ,7},
                     {7 ,7 ,7 ,7 ,0 ,1 ,7 ,1 ,1 ,1 ,1 ,1 ,7 ,1 ,0 ,1 ,1 ,1 ,1},
                     {1 ,1 ,1 ,1 ,0 ,1 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,1 ,0 ,1 ,7 ,7 ,7},
                     {1 ,1 ,1 ,1 ,0 ,1 ,7 ,1 ,1 ,1 ,1 ,1 ,7 ,1 ,0 ,1 ,1 ,1 ,1},
                     {1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1},
                     {1 ,0 ,1 ,1 ,0 ,1 ,1 ,1 ,0 ,1 ,0 ,1 ,1 ,1 ,0 ,1 ,1 ,34,1},
                     {1 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,1},
                     {1 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,1},
                     {1 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,1},
                     {1 ,34,1 ,1 ,1 ,1 ,1 ,1 ,0 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,1},
                     {1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1},
                     {1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1}}; 
void setup() {  
  Serial.begin(9600);
  pinMode (47, OUTPUT); //pin configurado como salida
  Serial.println("ILI9341 Test!"); 
  tft.begin();
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX);  
  Serial.println(F("Done!"));
  
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  
  
  
  caratula(); delay(1000);
  tft.setRotation(0);
  tft.fillScreen(ILI9341_BLACK);
  
  cargadoniv(); 
  Serial.println(despliegue(0,0,22,19));
  xx=16;  //inicio pacman 
  yy=9;
  asustar=51;
  Serial.begin(9600);
}
void loop(void) 
{

  

  
  if(life!=0){
  tft.fillRect(109,114,10,5,ILI9341_WHITE);}
  Serial.println(despliegue(0,0,22,19));
  tft.setTextSize(1.5);
  tft.setCursor(20,280);  tft.setTextColor(ILI9341_WHITE);  tft.println("SCORE");
  tft.setCursor(120,280); tft.setTextColor(ILI9341_WHITE);  tft.println("LIVES");
 if(antscore==score){
 tft.setCursor(80,280);  tft.setTextColor(ILI9341_YELLOW); tft.println(score);
  antscore=score;
  }
  else{
  tft.setTextColor(ILI9341_BLACK);
  tft.setCursor(80,280);  tft.println(antscore);
  tft.setTextColor(ILI9341_YELLOW); 
  tft.setCursor(80,280); tft.println(score);
  antscore=score;
  }
switch(life){
  case 3: {
           pacmanOpen(165, 277,0,3,1,9);
           pacmanOpen(180, 277,0,3,1,9);
           break;}
  case 2: {tft.fillCircle(186,283,7,ILI9341_BLACK);   break;}
  case 1: {tft.fillCircle(171,283,7,ILI9341_BLACK);   break;}
  case 0: {tft.fillRoundRect(90,192,50,12,3,ILI9341_BLACK);
          tft.setCursor(89,195); tft.setTextColor(ILI9341_RED); tft.setTextSize(1.8); tft.println("GAME OVER!");
          estadoInicial();delay(400);
          //AQUI AUN PONERLE LAS POSICIONES DE DONDE SE ENCUENTRAN LAS COSAS PARA QUITARLE EL MANEJO DEL PACMAN AL JUGADOR ...LO MISMO CON LOS FANTASMAS
          break; delay (10);
          }
          }
  playing();
  } 
 unsigned long playing()
    {
  datox = analogRead (A8);
  xxx = map(datox, 0, 1023, 0, 25);
  datoy = analogRead (A9); 
  yyy = map(datoy, 0, 1023,0,25); 
   if(xxx>12 ) 
  {  dato=mat[xx+1][yy];
    if(dato!=1) {xx++; direccionMov=26; }
  }
  if(xxx<8)
  { dato=mat[xx-1][yy];
    if(dato!=1)  {xx--; direccionMov=27;}
  }
  if(yyy<8)
    {dato=mat[xx][yy+1]; 
     if(dato!=1) {yy++; direccionMov=25;}
    }
  if(yyy>12) 
    {dato=mat[xx][yy-1];
    if(dato!=1)  {yy--; direccionMov=24;}
    } 
     aux=mat[xx][yy];
  if(fallaX==0){
     mat[xx][yy]=22;
     fallaX=1;
     pasos++;
     }else{
     mat[xx][yy]=direccionMov;
     fallaX=0;
     pasos++;
          }
    if(xx!=xant || yy!=yant){mat[xant][yant]=7; }
    xant=xx;  yant=yy;

    if(aux==0){score+=10;tone(47, e4, duracion);
}else{tone(47,c4, duracion);
    if(aux==34){asustar=1;
               }
    if(asustar<20){ 
      if(auxAsustarB==0)blinky=35; 
      if(auxAsustarC==0)clyde=35;
      if(auxAsustarP==0)pinky=35;
      if(auxAsustarI==0)inkey=35; 
      asustar++;
                }
      else{
        blinky=30;
        pinky=31;
        inkey=32;
        clyde=33;
          }
 if(aux==33){  life-=1; xx=16; yy=9; estadoInicial();muere33=1;mat[antyghost][antxghost]=7;  pasos=35;loose();}
 if(aux==32){  life-=1; xx=16; yy=9; estadoInicial();muere32=1;mat[antyghostP][antxghostP]=7;pasos=35;loose();}         
 if(aux==31){  life-=1; xx=16; yy=9; estadoInicial();muere31=1;mat[antyghostC][antxghostC]=7;pasos=35;loose();}
 if(aux==30){  life-=1; xx=16; yy=9; estadoInicial();muere30=1;mat[antyghostO][antxghostO]=7;pasos=35;loose();}    
 if(aux==blinky && blinky==35){ estadoInicial(); mat[yghost][xghost]=7;  printScore(yghost,xghost,200);  xghost=9;  yghost=8;  blinky=30;  auxAsustarB=1;score+=200;pasos=35;}
 if(aux==pinky  && pinky==35) { estadoInicial(); mat[yghostP][xghostP]=7;printScore(yghostP,xghostP,200);xghostP=9; yghostP=8; blinky=31;  auxAsustarP=1;score+=200;pasos=35;}
 if(aux==inkey  && inkey==35) { estadoInicial(); mat[yghostC][xghostC]=7;printScore(yghostC,xghostC,200);xghostC=9; yghostC=8; blinky=32;  auxAsustarI=1;score+=200;pasos=35;}
 if(aux==clyde  && clyde==35) { estadoInicial(); mat[yghostO][xghostO]=7;printScore(yghostO,xghostO,200);xghostO=9; yghostO=8; blinky=30;  auxAsustarC=1;score+=200;pasos=35;}}
if(pasos>1){  
  if(asustar>20){  
  ghostBlinky(xx,yy);}
      else{ghostBlinky(2,2);}
 }
 if(pasos>10){
  if(asustar>20){ghostPinky(xx+2,yy+1);}
  else{ghostPinky(16,4);}
 }
 if(pasos>20){
  if(asustar>20){ghostInkey(xx-2,yy+2);}
  else{ghostInkey(15,20);}
 }
 if(pasos>35){
  if(asustar<20){ghostClyde(8,8);}
  else{
  ghostClyde(xx-1,yy-1);}
  }

  if(life==0&&aux2==0){ mat[0][0]=11; aux2=1;}else {mat[0][0]=10;  aux2=0;}
}

unsigned long despliegue(int imin,int jmin,int imax,int jmax) 
{
  y=jmin*12;
  for(i=imin;i<imax;i++)
  { x=imin*12; 
    for(j=jmin;j<jmax;j++)
    {   dato=mat[i][j];
        switch(dato)
        {
          case 0: { tft.fillRect(x,y,12,12,ILI9341_BLACK); caminoLibre(x,y,2);     break;}
          case 7: { tft.fillRect(x,y,12,12,ILI9341_BLACK);                         break;}
          case 1: {                                 break;}
          case 10:{ muros(x,y,ILI9341_BLUE);        break;}
          case 11:{ muros(x,y,ILI9341_WHITE);       break;}        
          case 22:{ pacmanClose(x,y);               break;}
          case 24:{ pacmanOpen(x,y,0,3,1,9);        break;}//IZQUIERDA
          case 25:{ pacmanOpen(x,y,12,3,11,9);      break;}//DERECHA
          case 26:{ pacmanOpen(x,y,3,12,9,12);      break;}//ABAJO
          case 27:{ pacmanOpen(x,y,3,0,9,0);        break;}//ARRIBA
          case 30:{ ghost(x,y,ILI9341_RED);         break;}
          case 31:{ ghost(x,y,ILI9341_PINK);        break;}
          case 32:{ ghost(x,y,ILI9341_CYAN);        break;}
          case 33:{ ghost(x,y,ILI9341_ORANGE);      break;}
          case 34:{ tft.fillCircle(x+6,y+6,4,ILI9341_WHITE); break;}
          case 35:{ scaredGhost(x,y,ILI9341_BLUE); break;}
          case 36:{ ghost(x,y,ILI9341_BLACK);      break;}
          }  
   x=x+12;
  }y=y+12;
  }
}

unsigned long cargadoniv() 
{
  for(i=0;i<22;i++)
  {for(j=0;j<19;j++)
    {mat[i][j]=niv1[i][j];}
  }

  contadorNivel=1;
}
unsigned long pacmanClose(int x, int y )
{
  tft.fillRoundRect(x+1,y+1,10,10,4,ILI9341_YELLOW);
}
unsigned long pacmanOpen(int x, int y,int a,int b,int c,int d)
{
 tft.fillRoundRect(x+1,y+1,10,10,4,ILI9341_YELLOW);
 tft.fillTriangle(x+6,y+6  ,x+a   ,y+b   ,x+c,y+d    ,ILI9341_BLACK); 
} 
unsigned long caminoLibre(int x, int y ,int a)
{
  tft.fillRect(x+1,y+1,10,10,ILI9341_BLACK);
  tft.fillRect(x+5,y+5,a,a,ILI9341_WHITE);
}
unsigned long muros(int x, int y, uint16_t color)
{
  int a=12;
  mid(x,y,x,y,19,1,color);
  mid(x,y,x,y,1,8,color);
  mid(x,y,x,7,4,1,color);
  mid(x,y,3,7,1,4,color);
  mid(x,y,x,10,4,1,color);
  mid(x,y,3,12,1,2,color);
  mid(x,y,x,12,4,1,color);
  mid(x,y,x,13,4,1,color);
  mid(x,y,x,13,1,9,color);
  mid(x,y,x,21,19,1,color);
  mid(x,y,9,y,1,4,color);
  mid(x,y,18,y,1,8,color);
  mid(x,y,15,7,4,1,color);
  mid(x,y,15,7,1,3,color);
  mid(x,y,15,9,4,1,color);
  mid(x,y,15,11,4,1,color);
  mid(x,y,15,11,1,3,color);
  mid(x,y,15,13,4,1,color);
  mid(x,y,18,13,1,9,color);
  mid(x,y,2,2,2,2,color);
  mid(x,y,5,2,3,2,color);
  mid(x,y,11,2,3,2,color);
  mid(x,y,15,2,2,2,color);
  mid(x,y,2,5,2,1,color);
  mid(x,y,15,5,2,1,color);
  mid(x,y,5,5,1,5,color);
  mid(x,y,5,7,3,1,color); 
  mid(x,y,5,11,1,3,color);
  mid(x,y,2,2,2,2,color);
  mid(x,y,7,5,5,1,color);
  mid(x,y,9,5,1,3,color);
  mid(x,y,13,5,1,5,color);
  mid(x,y,11,7,3,1,color);
  mid(x,y,7,13,5,1,color);
  mid(x,y,9,13,1,3,color);
  mid(x,y,5,15,3,1,color);
  mid(x,y,11,15,3,1,color);
  mid(x,y,13,11,1,3,color);
  mid(x,y,2,15,2,1,color);
  mid(x,y,3,15,1,3,color);
  mid(x,y,x,17,2,1,color);
  mid(x,y,2,19,6,1,color);
  mid(x,y,7,17,5,1,color);
  mid(x,y,9,17,1,3,color);
  mid(x,y,11,19,6,1,color);
  mid(x,y,13,17,1,3,color);
  mid(x,y,17,17,2,1,color);
  mid(x,y,15,15,2,1,color);
  mid(x,y,15,15,1,3,color);
  mid(x,y,5,17,1,3,color);
  mid(x,y,7,9,2,1,color);
  mid(x,y,7,9,1,3,color);
  mid(x,y,10,9,2,1,color);
  mid(x,y,7,11,5,1,color);
  mid(x,y,11,9,1,3,color);
}
  unsigned long mid(int x,int y,int timesx,int timesy,int ancho,int alto,uint16_t color)
  {
    int a=12;
    tft.fillRoundRect(x+(timesx*a)+3,y+(timesy*a)+3,ancho*a -6,a*alto -6,4,color);
  } 
unsigned long ghost(int x,int y,uint16_t color)
{
  tft.fillRect(x,y+6,1,6,color);
  tft.fillRect(x+1,y+3,1,8,color);
  tft.fillRect(x+2,y+1,1,9,color);
  tft.fillRect(x+3,y+1,1,10,color);
  tft.fillRect(x+4,y,1,12,color);
  tft.fillRect(x+5,y,2,10,color);
  tft.fillRect(x+7,y,1,12,color);
  tft.fillRect(x+8,y+1,1,10,color);
  tft.fillRect(x+9,y+2,1,8,color);
  tft.fillRect(x+10,y+3,1,8,color);
  tft.fillRect(x+11,y+6,1,6,color);
  tft.fillRect(x+2,y+4,1,3,ILI9341_WHITE);
  tft.fillRect(x+3,y+3,2,5,ILI9341_WHITE);
  tft.fillRect(x+5,y+4,1,3,ILI9341_WHITE);
  tft.fillRect(x+4,y+5,2,2,ILI9341_BLUE);
  tft.fillRect(x+7,y+4,1,3,ILI9341_WHITE);
  tft.fillRect(x+8,y+3,2,5,ILI9341_WHITE);
  tft.fillRect(x+10,y+4,1,3,ILI9341_WHITE);
  tft.fillRect(x+9,y+5,2,2,ILI9341_BLUE);
}
unsigned long scaredGhost(int x,int y,uint16_t color)
{
  tft.fillRect(x,y+6,1,6,color);
  tft.fillRect(x+1,y+3,1,8,color);
  tft.fillRect(x+2,y+1,1,9,color);
  tft.fillRect(x+3,y+1,1,10,color);
  tft.fillRect(x+4,y,1,12,color);
  tft.fillRect(x+5,y,2,10,color);
  tft.fillRect(x+7,y,1,12,color);
  tft.fillRect(x+8,y+1,1,10,color);
  tft.fillRect(x+9,y+2,1,8,color);
  tft.fillRect(x+10,y+3,1,8,color);
  tft.fillRect(x+11,y+6,1,6,color);
  tft.fillRect(x+2,y+4,1,3,ILI9341_WHITE);
  tft.fillRect(x+3,y+3,2,5,ILI9341_WHITE);
  tft.fillRect(x+5,y+4,1,3,ILI9341_WHITE);
  tft.fillRect(x+4,y+5,2,2,ILI9341_BLACK);
  tft.fillRect(x+7,y+4,1,3,ILI9341_WHITE);
  tft.fillRect(x+8,y+3,2,5,ILI9341_WHITE);
  tft.fillRect(x+10,y+4,1,3,ILI9341_WHITE);
  tft.fillRect(x+9,y+5,2,2,ILI9341_BLACK);
  tft.drawLine(x+3,y+10,x+8,y+10,ILI9341_WHITE);
    }
    unsigned long estadoInicial()
    {
    if(asustar==1){
    mat[yghost][xghost]=7;
    mat[yghostC][xghostC]=7;
    mat[yghostP][xghostP]=7;
    mat[yghostO][xghostO]=7;
    }
    yghost=8; xghost=9;
    yghostC=8; xghostC=9;
    yghostP=8; xghostP=9;
    yghostO=8; xghostO=9;
    mat[10][8]=31;  
    mat[10][9]=32;
    mat[10][10]=33;
    pasos=0;
    }

void Tone()
{
  for (int i=0; i<MAX_COUNT; i++) {
toneM = melody1[i];
beat = beats1[i];
duration = beat * tempo;
playTone();
delayMicroseconds(pause);
}
  }
void playTone() {
long elapsed_time = 0;
if (toneM > 0) {
digitalWrite(led,HIGH);
while (elapsed_time < duration) {
digitalWrite(speakerOut,HIGH);
delayMicroseconds(toneM / 2);
digitalWrite(speakerOut, LOW);
delayMicroseconds(toneM / 2);
elapsed_time += (toneM);
       }
digitalWrite(led,LOW);
}
else {
for (int j = 0; j < rest_count; j++) {
delayMicroseconds(duration);
}
}
}
  unsigned long ghostBlinky (int xObjetivo,int yObjetivo){
  if(muere30==1){mat[yghost][xghost]=0; yghost=8 ; xghost=9;muere30=0;}
  nextLeft=mat[yghost][xghost-1];
  nextRight=mat[yghost][xghost+1];
  nextUp=mat[yghost-1][xghost];
  nextDown=mat[yghost+1][xghost];
if(yghost<xObjetivo){chooseWay=2; if (nextDown==1){if(xghost<yy){chooseWay=4;}else{chooseWay=3;}}}
if(yghost>xObjetivo){chooseWay=1;if(nextUp==1){if(xghost<yy){chooseWay=4;}else{chooseWay=3;}}}
if(xghost<yObjetivo){chooseWay=4;if(nextRight==1){if(yghost<xx){chooseWay=2;}else{chooseWay=1;}}}
if(xghost>yObjetivo){chooseWay=3;if(nextLeft==1){if(yghost<xx){chooseWay=2;}else{chooseWay=1;}}}
switch (chooseWay){    case 1:{ if(nextUp!=1)   {yghost--;}  break;  }
                       case 2:{ if(nextDown!=1) {yghost++;}  break;  }
                       case 3:{ if(nextLeft!=1) {xghost--;}  break;  }
                       case 4:{ if(nextRight!=1){xghost++;}  break;  } }
   aux=mat[yghost][xghost]; 
   if(aux==0||aux==7||aux==22||aux==24||aux==25||aux==26||aux==27){
   if(aux==22||aux==24||aux==25||aux==26||aux==27){aux=7;}
   mat[yghost][xghost]=blinky;
   mat[antyghost][antxghost]=aux;
   antxghost=xghost;
   antyghost=yghost;}}

unsigned long ghostPinky(int xObjetivo,int yObjetivo)
  {
     if(muere31==1){mat[yghostP][xghostP]=0;yghostP=8 ; xghostP=9;muere31=0;}
  mat[10][8]=7;
  nextLeft=mat[yghostP][xghostP-1];
  nextRight=mat[yghostP][xghostP+1];
  nextUp=mat[yghostP-1][xghostP];
  nextDown=mat[yghostP+1][xghostP];
  
if(yghostP<xObjetivo){chooseWay=2;if(nextDown==1){if(xghostP<yy){chooseWay=4;}else{chooseWay=3;}}}
if(yghostP>xObjetivo){chooseWay=1;if(nextUp==1){if(xghostP<yy){chooseWay=4;}else{chooseWay=3;}}}
if(xghostP<yObjetivo){chooseWay=4;if(nextRight==1){if(yghostP<xx){chooseWay=2;}else{chooseWay=1;}}}
if(xghostP>yObjetivo){chooseWay=3;if(nextLeft==1){if(yghostP<xx){chooseWay=2;}else{chooseWay=1;}}}
switch (chooseWay){    case 1:{ if(nextUp!=1)   {yghostP--;}  break;  }
                       case 2:{ if(nextDown!=1) {yghostP++;}  break;  }
                       case 3:{ if(nextLeft!=1) {xghostP--;}  break;  }
                       case 4:{ if(nextRight!=1){xghostP++;}  break;  } }
   aux=mat[yghostP][xghostP];
   if(aux==0||aux==7||aux==22||aux==24||aux==25||aux==26||aux==27){
    if(aux==22||aux==24||aux==25||aux==26||aux==27){aux=7;}
   mat[yghostP][xghostP]=pinky;
   mat[antyghostP][antxghostP]=aux;
   antyghostP=yghostP;
   antxghostP=xghostP;} 
  }

unsigned long ghostInkey(int xObjetivo, int yObjetivo)
{
if(muere32==1){ mat[yghostC][xghostC]=0; yghostC=8 ; xghostC=9; muere32=0;}
  mat[10][9]=7;
  nextLeft=mat[yghostC][xghostC-1];
  nextRight=mat[yghostC][xghostC+1];
  nextUp=mat[yghostC-1][xghostC];
  nextDown=mat[yghostC+1][xghostC];
if(yghostC<xObjetivo){chooseWay=2; if (nextDown==1){if(xghostC<yy){chooseWay=4;}else{chooseWay=3;}}}
if(yghostC>xObjetivo){chooseWay=1;if(nextUp==1){if(xghostC<yy){chooseWay=4;}else{chooseWay=3;}}}
if(xghostC<yObjetivo){chooseWay=4;if(nextRight==1){if(yghostC<xx){chooseWay=2;}else{chooseWay=1;}}}
if(xghostC>yObjetivo){chooseWay=3;if(nextLeft==1){if(yghostC<xx){chooseWay=2;}else{chooseWay=1;}}}
switch (chooseWay){    case 1:{ if(nextUp!=1)   {yghostC--;}  break;  }
                       case 2:{ if(nextDown!=1) {yghostC++;}  break;  }
                       case 3:{ if(nextLeft!=1) {xghostC--;}  break;  }
                       case 4:{ if(nextRight!=1){xghostC++;}  break;  } }
  aux=mat[yghostC][xghostC];
  if(aux==0||aux==7||aux==22||aux==24||aux==25||aux==26||aux==27){
    if(aux==22||aux==24||aux==25||aux==26||aux==27){aux=7;}
   mat[yghostC][xghostC]=inkey;
   mat[antyghostC][antxghostC]=aux;
   antyghostC=yghostC;
   antxghostC=xghostC;
                    }
}
unsigned long ghostClyde(int xObjetivo, int yObjetivo)
{
  if(muere33==1){mat[yghostO][xghostO]=0;yghostO=8 ; xghostO=9; muere33=0;}
  mat[10][10]=7;
  nextLeft=mat[yghostO][xghostO-1];
  nextRight=mat[yghostO][xghostO+1];
  nextUp=mat[yghostO-1][xghostO];
  nextDown=mat[yghostO+1][xghostO];  
//if(yghostO<xObjetivo){chooseWay=2; if (nextDown==1){if(xghostO<yy){chooseWay=4;}else{chooseWay=3;}}}
//if(yghostO>xObjetivo){chooseWay=1;if(nextUp==1){if(xghostO<yy){chooseWay=4;}else{chooseWay=3;}}}
//if(xghostO<yObjetivo){chooseWay=4;if(nextRight==1){if(yghostO<xx){chooseWay=2;}else{chooseWay=1;}}}
//if(xghostO>yObjetivo){chooseWay=3;if(nextLeft==1){if(yghostO<xx){chooseWay=2;}else{chooseWay=1;}}}
chooseWay=random(1,4);
switch (chooseWay){    case 1:{ if(nextUp!=1)   {yghostO--;}  break;  }
                       case 2:{ if(nextDown!=1) {yghostO++;}  break;  }
                       case 3:{ if(nextLeft!=1) {xghostO--;}  break;  }
                       case 4:{ if(nextRight!=1){xghostO++;}  break;  } }
   aux=mat[yghostO][xghostO];
   if(aux==0||aux==7||aux==22||aux==24||aux==25||aux==26||aux==27){
    if(aux==22||aux==24||aux==25||aux==26||aux==27){aux=7;}
   mat[yghostO][xghostO]=clyde;
   mat[antyghostO][antxghostO]=aux;
   antyghostO=yghostO;
   antxghostO=xghostO;}
} 

unsigned long printScore(int x,int y, int score)
 {
  tft.setCursor(y*12,x*12);
  tft.setTextColor(ILI9341_GREEN);
  tft.println(score);delay(100);
  tft.setTextColor(ILI9341_BLACK);
  tft.println(score);delay(100);
 }
 unsigned long caratula()
{
 
  tft.fillRect(10,20,300,90,ILI9341_MAROON);
  tft.fillRect(15,25,290,80,ILI9341_ORANGE);
  tft.drawCircle(45,58,21,ILI9341_BLACK);
  tft.fillRect(23,38,19,55,ILI9341_WHITE);
  tft.drawRect(22,37,20,56,ILI9341_BLACK);
  tft.fillRect(25,40,20,55,ILI9341_YELLOW);
  tft.drawRect(24,39,21,56,ILI9341_BLACK);
  tft.fillCircle(45,58,20,ILI9341_YELLOW);
  tft.fillTriangle(68,96,85,41,101,96, ILI9341_WHITE);
  tft.drawTriangle(67,97,86,40,102,97, ILI9341_BLACK);
  tft.fillTriangle(63,93,84,40,98,93, ILI9341_YELLOW);
  tft.drawTriangle(62,94,83,39,99,94, ILI9341_BLACK);
  tft.fillCircle(84,70,3, ILI9341_BLACK);
  tft.fillCircle(127,65,28,ILI9341_WHITE);
  tft.drawCircle(127,65,28,ILI9341_BLACK);
  tft.fillCircle(130,67,28,ILI9341_YELLOW);
  tft.drawCircle(130,67,29,ILI9341_BLACK);
 tft.fillTriangle(133,67,158,50,158,90, ILI9341_ORANGE);
 tft.fillRect(155,65,20,10,ILI9341_YELLOW);
 tft.drawRect(154,64,21,11,ILI9341_BLACK);
tft.drawTriangle(184,96,184,38,201,96,ILI9341_BLACK);
tft.drawTriangle(201,96,216,38,216,96,ILI9341_BLACK);
tft.drawTriangle(181,93,181,35,208,91,ILI9341_BLACK);
tft.drawTriangle(208,91,213,35,213,91,ILI9341_BLACK);
tft.fillTriangle(185,95,185,39,200,95, ILI9341_WHITE);
tft.fillTriangle(200,95,215,39,215,95, ILI9341_WHITE);
tft.fillTriangle(182,92,182,36,207,92, ILI9341_YELLOW);
tft.fillTriangle(187,92,212,36,212,92, ILI9341_YELLOW);
tft.fillTriangle(220,95,239,42,256,95, ILI9341_WHITE);
tft.drawTriangle(219,96,239,41,257,96, ILI9341_BLACK);
tft.fillTriangle(218,93,236,40,253,93, ILI9341_YELLOW);
tft.drawTriangle(219,94,236,39,254,94, ILI9341_BLACK);
tft.fillCircle(236,70,3, ILI9341_BLACK);
tft.fillTriangle(260,95,260,40,290,95,ILI9341_WHITE);
tft.drawTriangle(259,96,259,39,291,96,ILI9341_BLACK);
tft.drawTriangle(256,93,256,39,288,93,ILI9341_BLACK);
tft.drawRect(271,36,15,54,ILI9341_BLACK);
tft.drawRect(274,39,18,57,ILI9341_BLACK);
tft.fillRect(275,40,17,56,ILI9341_WHITE);
tft.fillTriangle(257,92,257,40,287,92,ILI9341_YELLOW);
tft.fillRect(272,37,14,53,ILI9341_YELLOW);
tft.setCursor(100, 170);
pacmanOpen(145,135,12,3,11,9);
ghost(100,135,ILI9341_RED);
ghost(115,135,ILI9341_PINK);
ghost(130,135,ILI9341_CYAN);
tft.setTextColor(ILI9341_RED);tft.setTextSize(2.5);
 tft.setCursor(100, 155); tft.print(" PLAY GAME ");
 tft.fillScreen(ILI9341_BLACK);
ghost(80,45,ILI9341_RED);
tft.setTextColor(ILI9341_RED);tft.setTextSize(2.5);
 tft.setCursor(100, 45); tft.print("....  B L I N K Y ");
ghost(80,75,ILI9341_PINK);
tft.setTextColor(ILI9341_PINK );tft.setTextSize(2.5);
 tft.setCursor(100, 75); tft.print("....  P I N K Y ");
ghost(80,105,ILI9341_CYAN);
tft.setTextColor(ILI9341_CYAN );tft.setTextSize(2.5);
 tft.setCursor(100, 105); tft.print("....  I N K Y ");
}

unsigned long loose()
{
  tone(47,a4, 200);
  tone(47,0, 200); 
  tone(47,g4, 200);
  tone(47,0, 200);
  tone(47,f4, 200);
  tone(47,0, 200);
}
