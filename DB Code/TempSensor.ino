double Vo;
double R2, T, R1 = 10000;


double redUpper = 1e200;
double redLower = 57;

double greenUpper = 57;
double greenLower = 31;

double blueUpper = 31;
double blueLower = -1e200;



double A, B, C;

void setup() {
Serial.begin(9600); 
pinMode(7, OUTPUT);
pinMode(13, OUTPUT);
pinMode(2, OUTPUT);
getConst(26148.41, 4.0, 5934.58, 37.0 , 1468.61, 74.1);
Serial.println(A*1e3,12);
Serial.println(B*1e4,12);
Serial.println(C*1e7,12);
}

void loop() {
  T=0;
  Vo = 1023./analogRead(0);
  R2 = R1 * (Vo - 1.0);
  Serial.print(Vo); Serial.print(" Volts\n");
  T = A + B*(log(R2)) + C*(log(R2)*log(R2)*log(R2));
  T = 1./T;
  T -= 273.15;
  Serial.print(T);   Serial.print(" C\t");
  Serial.print(R2);     Serial.println(" Ohms");
  
  if(T >= greenLower  &&  T <= greenUpper){
    digitalWrite(13, LOW);
    digitalWrite(2, LOW);            
    digitalWrite(7, HIGH);
  }
  else if(T > redLower  &&  T < redUpper){
    digitalWrite(2, LOW);
    digitalWrite(7, LOW);
    digitalWrite(13, HIGH);
  }
  else if (T > blueLower  &&  T < blueUpper){
    digitalWrite(7, LOW);
    digitalWrite(2, HIGH);
    digitalWrite(13, LOW);
  }
  delay(500);
}

void getConst(float R1, float T1, float R2, float T2, float R3, float T3){
  double L1, L2, L3, Y1, Y2, Y3, G2, G3;
  T1+=273.15;
  T2+=273.15;
  T3+=273.15;
  L1=log(R1); L2=log(R2); L3=log(R3);
  Y1=1./T1; Y2=1./T2; Y3=1./T3;
  G2=((Y2-Y1)/(L2-L1));
  G3=((Y3-Y1)/(L3-L1));
  C=((G3-G2)/(L3-L2))*pow((L1+L2+L3),-1);
  B=G2-C*(pow(L1,2)+L1*L2+pow(L2,2));
  A=Y1-(B+pow(L1,2)*C)*L1;
}
