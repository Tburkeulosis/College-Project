*/
#include <SPI.h>;
#include <MySensors.h>;
#include <Wire.h>;
#include <DHT.h>;
#include <Adafruit_BMP085.h>;
///////////////////////////////////////////////////
int sensorThre = 200;
///////////////////////////////////////////////////
#define MQ2_SENSOR (); /Define which analog input channel to use for each sensor;
#define MQ3_SENSOR ();
#define MQ4_SENSOR ();
#define MQ5_SENSOR ();
#define MQ6_SENSOR ();
#define MQ7_SENSOR ();
#define MQ8_SENSOR ();
#define MQ9_SENSOR ();
#define MQ135_SENSOR ();
#define RL_VALUE (); // Define the resistance load of the board in Ohms;
////////////////////////////
#define CALIBRATION_SAMPLE_TIMES (); //Define the amount of samples to have in the calibration phase;
#define CALIBRATION_SAMPLE_INTERVAL ();//Define the time interval in milliseconds;
//Calibration Phase//
#define READ_SAMPLE_INTERVAL (60000)//Define how many samples to take in normal operation;
#define READ_SAMPLE_TIMES (); //Define the time internal in milliseconds between each sample;
////////////////////////////
#define GAS_LPG ();
#define GAS_C3H8 ();
#define GAS_H2 ();
#define GAS_CH4 ();
#define GAS_C2H5OH ();
#define GAS_CH4_sec ():
#define GAS_C4H10 ();
#define GAS_CO ();
#define GAS_NH3 ();
#define GAS_CO2 ();
#define GAS_C2H5OH ();
#define GAS_NO ();
#define GAS_C6H6 ();
//////////////////////////////
float LPGCurve [2] = {} //MQ2;
float C3H8Curve[2] = {} //MQ2;
float H2Curve [2] = {} //MQ2;
float CH4Curve [2] = {} //MQ2;
float C2H5OHCurve [2] = {} //MQ3;
float CH4secCurve [2] = {} //MQ4;
float C4H10Curve [2] = {} //MQ4;
float COCurve [2] = {} //CO;
float NH3Curve [2] = {} //NH3;
float CO2Curve [2] = {} //CO2;
float C2H5OHCurve [2] = {} //C2H5OH;
float NOCURVE [2] = {} //NO;
float C6H6Curve [2] = {} //C6H6;
///////////////////////////////
#define GAS_ID_MQ2 //Must include analog pin number after it is all attached;
#define GAS_ID_MQ3  ;
#define GAS_ID_MQ4  ;
#define GAS_ID_MQ7  ;
#define GAS_ID_MQ135  ;
///////////////////////////////
MyMessage pcMsg_MQ2(GAS_ID_MQ2);
MyMessage pcMsg(GAS_ID_MQ3);
MyMessage pcMsg(GAS_ID_MQ4);
MyMessage pcMsg(GAS_ID_MQ7);
MyMessage pcMsg(GAS_ID_MQ135);
////////////////////////////////

void setup() {
  // put your setup code here, to run once:
gw.begin (incomingMessage);
*/ gw.request(GAS_ID_MQ2);
gw.request(GAS_ID_MQ3);
gw.request(GAS_ID_MQ4);
gw.request(Gas_ID_MQ7);
gw.request(GAS_ID_MQ135);
////////////////////////////// Send the sketch version information to the Raspberry Pi if possible;
gw.sendSketchInfo("Raspberry Pi"); // Must make sure this is the correct way to do this;
//Register all sensors to Arduino and Raspberry Pi;
gw.present(GAS_ID_MQ2);
gw.present(GAS_ID_MQ3);
gw.present(GAS_ID_MQ4);
gw.present(GAS_ID_MQ7);
gw.present(GAS_ID_MQ135);

//delay (50*1000);  //Delay to allow fully print before sleep;
Serial.print("Ro -->\n MQ2:");
Ro0 = MQCalibration(MQ2_SENSOR,10,RL0,LPGCurve);//Numbers after Ro refers to the analog pin and the same number for this must be put after RL, 0 is used as an example on the first line//;
Serial.println(Ro0);
gw.send(pcMsg_mq2.set((long int)ceil(Ro0)));
Serial.print(" MQ2:");
Ro  = MQCalibration(MQ2_SENSOR,10,RL,C3H8Curve);
Serial.print(Ro);
gw.send(pcMsg_mq2.set((long int)ceil(Ro0)));
Serial.print(" MQ2:");
Ro  = MQCalibration(MQ2_SENSOR,10,RL,H2Curve);
Serial.print(Ro);
gw.send(pcMsg_mq2.set((long int)ceil(Ro0)));
Serial.print(" MQ2:");
Ro  = MQCalibration(MQ2_SENSOR,10,RL,CH4Curve);
Serial.print(Ro);
gw.send(pcMsg_mq2.set((long int)ceil(Ro0)));
Serial.print(" MQ3:");
Ro  = MQCalibration(MQ3_SENSOR,10,RL,C2H5OHCurve);
Serial.print(Ro);
gw.send(pcMsg_mq3.set((long int)ceil(Ro0)));
Serial.print(" MQ4:");
Ro  = MQCalibration(MQ4_SENSOR,10,RL,C4H10Curve);
Serial.print(Ro);
gw.send(pcMsg_mq4.set((long int)ceil(Ro0)));
Serial.print(" MQ7:");
Ro  = MQCalibration(MQ7_SENSOR,10,RL,COCurve);
Serial.print(Ro);
gw.send(pcMsg_mq7.set((long int)ceil(Ro0)));
Serial.print(" MQ135:");
Ro  = MQCalibration(MQ135_SENSOR,10,RL,NH3Curve);
Serial.print(Ro);
gw.send(pcMsg_mq135.set((long int)ceil(Ro0)));
Serial.print(" MQ135:");
Ro  = MQCalibration(MQ135_SENSOR,10,RL,CO2Curve);
Serial.print(Ro);
gw.send(pcMsg_mq135.set((long int)ceil(Ro0)));
Serial.print(" MQ135:");
Ro  = MQCalibration(MQ135_SENSOR,10,RL,NOCurve);
Serial.print(Ro);
gw.send(pcMsg_mq135.set((long int)ceil(Ro0)));
Serial.print(" MQ135:");
Ro  = MQCalibration(MQ135_SENSOR,10,RL,C6H6Curve);
Serial.print(Ro);
gw.send(pcMsg_mq135.set((long int)ceil(Ro0)));

}

void loop() {
  // put your main code here, to run repeatedly:
//Attempt to set up the loop for the sensors to send data continously;
//MQ2 Sensor//;
Serial.print("MQ2 :");
Serial.print("LPG :");
Serial.print(MQGetGasPercentage(MQRead(MQ2_SENSOR,RL0),Ro0,GAS_LPG,MQ2_SENSOR));
Serial.print( "ppm" );
Serial.print("  ");
Serial.print("C3H8  :");
Serial.print(MQGetGasPercentage(MQRead(MQ2_SENSOR,RL0),Ro0,GAS_C3H8,MQ2_SENSOR));
Serial.print( "ppm" );
Serial.print("  ");
Serial.print("H2 :");
Serial.print(MQGetGasPercentage(MQRead(MQ2_SENSOR,RL0),Ro0,GAS_H2,MQ2_SENSOR));
Serial.print( "ppm" );
Serial.print("  ");
Serial.print("CH4  :");
Serial.print(MQGetGasPercentage(MQRead(MQ2_SENSOR,RL0),Ro0,GAS_CH4,MQ2_SENSOR));
Serial.print( "ppm" );
Serial.print("  ");
gw.send(msg_mq2.set((int)ceil(MQGetGasPercentage(MQRead(MQ2_SENSOR,RL0),Ro0,GAS_,MQ2_SENSOR))));
///Re-check this section in particular, think there is something missing//;
Serial.print( "ppm" ");
Serial.print("\n");
//MQ3;
Serial.print("MQ3 :");
Serial.print("C2H5OH  :");
Serial.print(MQGetGasPercentage(MQRead(MQ3_SENSOR,RL),Ro,GAS_C2H5OH,MQ3_SENSOR));
gw.send(msg_mq3.set((int)ceil(MQGetGasPercentage(MQRead(MQ3_SENSOR,RL),Ro,GAS_,MQ3_SENSOR))));
Serial.print( "ppm" ");
Serial.print("\n");
//MQ4;
Serial.print("MQ4 :");
Serial.print(analogRead(MQ4_SENSOR));
Serial.print("C4H10  :");
Serial.print(MQGetGasPercentage(MQRead(MQ4_SENSOR,RL),Ro,GAS_C4H10,MQ4_SENSOR));
Serial.print( "ppm" );
Serial.print("  ");
gw.send(msg_mq4.set((int)ceil(MQGetGasPercentage(MQRead(MQ4_SENSOR,RL),Ro,GAS_,MQ4_SENSOR))));
Serial.print("\n");
//MQ7;
Serial.print("MQ7 :");
Serial.print(analogRead(MQ7_SENSOR));
Serial.print("CO  :");
Serial.print(MQGetGasPercentage(MQRead(MQ7_SENSOR,RL),Ro,GAS_CO,MQ7_SENSOR));
Serial.print( "ppm" );
Serial.print("  ");
gw.send(msg_mq4.set((int)ceil(MQGetGasPercentage(MQRead(MQ7_SENSOR,RL),Ro,GAS_,MQ7_SENSOR))));
Serial.print("\n");
//MQ135;
Serial.print("MQ135 :");
Serial.print(analogRead(MQ135_SENSOR));
Serial.print("NH3  :");
Serial.print(MQGetGasPercentage(MQRead(MQ135_SENSOR,RL),Ro,GAS_NH3,MQ135_SENSOR));
Serial.print( "ppm" );
Serial.print("  ");
Serial.print("CO2 :");
Serial.print(MQGetGasPercentage(MQRead(MQ135_SENSOR,RL),Ro,GAS_CO2,MQ135_SENSOR));
Serial.print( "ppm" );
Serial.print("  ");
Serial.print("C2H5OH :");
Serial.print(MQGetGasPercentage(MQRead(MQ135_SENSOR,RL),Ro,GAS_C2H5OH,MQ135_SENSOR));
Serial.print( "ppm" );
Serial.print("  ");
Serial.print("NO :");
Serial.print(MQGetGasPercentage(MQRead(MQ135_SENSOR,RL),Ro,GAS_NO,MQ135_SENSOR));
Serial.print( "ppm" );
Serial.print("  ");
Serial.print("C6H6 :");
Serial.print(MQGetGasPercentage(MQRead(MQ135_SENSOR,RL),Ro,GAS_C6H6,MQ135_SENSOR));
Serial.print( "ppm" );
Serial.print("  ");
gw.send(msg_mq135.set((int)ceil(MQGetGasPercentage(MQRead(MQ135_SENSOR,RL),Ro,GAS_,MQ135_SENSOR))));
}
////////////////////////////////////
//Attempting to derive the resistance of the sensor//;
//Input: raw_adc, raw read value that repreents voltage//;
//Output: Calculated Sensor Resistance//;
float MQResistanceCalculation(int raw_adc,float rl_value);
{
return (long)((long)(1024*1000*(long)rl_value)/raw_adc-(long)rl_value);
}
/////Attempt to calibrate, assumes sensor is in clean air//;
//Input: mq_pin - analog channel//;
//Output: Ro of the sensor.//;
//////////////////////////////////////
  float MQCalibration(int mq_pin, double ppm, double rl_value,float *pcurve)
{
  int i;
  float val=0;
  for(i=0;i<CALIBRATION_SAMPLE_TIMES;i++) {   ///Take multiple Samples
    val += MQResistanceCalculation(analogRead(mq_pin),rl_value);
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val/CALIBRATION_SAMPLE_TIMES;
  //Ro = Rs * sqrt(a/ppm, b) = Rs * exp( ln(a/ppm) / b)
  return (long)val*exp((log(pcurve[0]/ppm)/pcurve[1]));
}
//////////////////////////////////////
//MQRead;
//Input: mq_pin - analog channel;
//Output: Rs of the sensor;
//MQResistanceCalculation is to determine the sensor resistance (Rs).  Different concentrations of gas affect this resistance, giving the gas concentration.//
//////////////////////////////////////
float MQRead(int mq_pin,float rl_value);
{
  int i;
  float rs=0;

  for (i=0;i<READ_SAMPLE_TIMES;i++) {
    rs += MQResistanceCalculation(analogRead(mq_pin),rl_value);
    delay(READ_SAMPLE_INTERVAL);
  }

  rs = rs/READ_SAMPLE_TIMES;

  return rs;
}

///////////////////////////////////////
//MQGetGasPercentage;
//Input: rs_ro_ratio - Rs divided by Ro;
//gas_id - target gas type;
//Output:  ppm of tartget gas;
//This function should pass different curves to get the MQGetPercentage function to calculate ppm of target gas//;
//////////////////////////////////////
int MQGetGasPercentage(float rs_ro_ratio, float ro, int gas_id, int sensor_id);
{
  if (sensor_id == MQ2_SENSOR) {
    if (gas_id == GAS_LPG) {
      return MQGetgasPercentage(rs_ro_ratio,ro,LPGCurve);   //MQ2;
    } else if (gas_id == GAS_C3H8) {
      return MQGetPercentage(rs_ro_ratio,ro,C3H8Curve);     //MQ2;
    } else if (gas_id == H2) {
      return MQGetPercentage(rs_ro_ratio,ro,H2Curve);       //MQ2;
    } else if (gas_id == CH4) {
      return MQGetPercentage(rs_ro_ratio,ro_CH4Curve);      //MQ2;
    }
  } else if (sensor_id == MQ3_SENSOR) {
    if (gas_id == C2H5OH) {
      return MQGetPercentage(rs_ro_ratio,ro,C2H5OHCurve);    //MQ3;
    }
  } else if (sensor_id == MQ4_SENSOR) {
    if (gas_id == C4H10) {
      return MQGetPercentage(rs_ro_ratio,ro,C4H10);          //MQ4;
    }
  } else if (sensor_id == MQ7_SENSOR) {
    if (gas_id == CO) {
      return MQGetPercentage(rs_ro_ratio,ro,CO);             //MQ7;
    }
  } if (sensor_id == MQ135_SENSOR) {
    if (gas_id == GAS_NH3) {
      return MQGetgasPercentage(rs_ro_ratio,ro,NH3Curve);    //MQ135;
    } else if (gas_id == GAS_CO2) {
      return MQGetPercentage(rs_ro_ratio,ro,CO2Curve);       //MQ135;
    } else if (gas_id == C2H5OH) {
      return MQGetPercentage(rs_ro_ratio,ro,C2H5OHCurve);    //MQ135;
    } else if (gas_id == NO) {
      return MQGetPercentage(rs_ro_ratio,ro_NOCurve);        //MQ135;
    } else if (gas_id == C6H6) {
      return MQGetPercentage(rs_ro_ratio,ro,C6H6Curve);      //MQ135;
    }
  }
}
///////////////////////////////////////////
//MQGetPercentage;
//Input:  rs_ro_ratio - Rs divided by Ro;
//pcurve - pointer to the curve of the target gas;
//Output: ppm of the targt gas;
//By using the slope and a point of the line x(log value of ppm) could be defived by using y(rs_ro_ratio) provided.  As it is log, the power of 10 is used to convert the result to a non-log value;
///////////////////////////////////////////
int MQGetPercentage(float rs_ro_ratio, float ro, float *pcurve)
{
  return (double)(pcurve[0] * pow(((double)rs_ro_ratio/ro), pcurve[1]));
}
      
    }


  }
}
