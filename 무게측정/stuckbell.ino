#include <HX711.h> // Github Bogde files!
#include <DHT11.h>    //라이브러리 불러옴

int firePin = 8;  // 디지털 12번핀을 불꽃감지센서로 지정합니다.

int dhtPin = 9;            //Signal 이 연결된 아두이노의 핀번호
DHT11 dht11(dhtPin);

HX711 scale(A4, A5); // 24 bit load cell amplifier

void setup()
{
  Serial.begin(9600);
  scale.set_scale(3280.f); //// this value is obtained by calibrating the scale with known weights
  scale.tare();
}
void loop()
{




  int weight = - ((scale.get_units() / 0.1189 ) +1.0) ;
  
  Serial.print("현재재고 무게:");
  Serial.print(weight, 1);
  Serial.println("g");
  scale.power_down(); // put the ADC in sleep mode
  delay(1000);
  scale.power_up();

  int err;
  float temp, humi;
  if((err=dht11.read(humi, temp))==0) //온도, 습도 읽어와서 표시
  {
    Serial.print("기온:");
    Serial.print(temp);
    Serial.println("C");
    Serial.print("습도:");
    Serial.print(humi);
    Serial.print("%");
    Serial.println();
  }

  
  int val = digitalRead(firePin);
  if (val == LOW) {
    Serial.println("화재위험 감지!!");
  }else{
    Serial.println("화재위험 없음..");
  }

  

  

  


    

 
  
  
}
