//final code 5DOF+gripper
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <math.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// ================= SERVO CONFIG =================
#define SERVOMIN   125
#define SERVOMAX   625
#define SERVO_FREQ 50

// ================= CHANNELS =================
#define CH_BASE  0
#define CH_SH    1
#define CH_EL    2
#define CH_WY    3   // dependent wrist yaw
#define CH_WR    4   // fixed wrist roll

// ================= HOME ANGLES =================
#define HOME_BASE 0
#define HOME_SH   40
#define HOME_EL   0
#define HOME_WY   0
#define HOME_WR   0

// ================= LINK LENGTHS (cm) =================
float L1 = 2.4;
float L2 = 10.5;
float L3 = 19.5;
float L4 = 9.0;
float L3e;

// ================= MOTION CONTROL =================
#define MOVE_STEPS     60
#define STEP_DELAY_MS  15
#define DEADBAND_DEG    2
#define COMMAND_DELAY 500

bool busy = false;
unsigned long lastCmd = 0;

// Current servo angles
int curBase = HOME_BASE;
int curSh   = HOME_SH;
int curEl   = HOME_EL;
int curWy   = HOME_WY;
int curWr   = HOME_WR;

// ================= SERVO HELPERS =================
int clampAngle(int a){ return constrain(a, 0, 180); }

void setServo(uint8_t ch, int angle){
  angle = clampAngle(angle);
  int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(ch, 0, pulse);
}

void setServoDeadband(uint8_t ch, int &cur, int target){
  target = clampAngle(target);
  if (abs(target - cur) >= DEADBAND_DEG){
    setServo(ch, target);
    cur = target;
  }
}

// ================= SMOOTH MOVE =================
void smoothMove(int tb, int ts, int te, int twy){
  int sb = curBase, ss = curSh, se = curEl, sy = curWy;

  for (int i = 1; i <= MOVE_STEPS; i++){
    float a = (float)i / MOVE_STEPS;

    setServoDeadband(CH_BASE, curBase, sb + (tb - sb) * a);
    setServoDeadband(CH_SH,   curSh,   ss + (ts - ss) * a);
    setServoDeadband(CH_EL,   curEl,   se + (te - se) * a);
    setServoDeadband(CH_WY,   curWy,   sy + (twy - sy) * a);

    delay(STEP_DELAY_MS);
  }
}

// ================= HOME =================
void goHome(){
  smoothMove(HOME_BASE, HOME_SH, HOME_EL, HOME_WY);
  setServo(CH_WR, HOME_WR);
}

// ================= INVERSE KINEMATICS =================
bool IK(float x, float y, float z,
        float &t1, float &t2, float &t3){

  float theta1 = atan2(y, x);

  float r  = sqrt(x*x + y*y);
  float z2 = z - L1;

  float d = sqrt(r*r + z2*z2);
  if (d < fabs(L3e - L2) || d > (L3e + L2)) return false;

  float D = (r*r + z2*z2 - L2*L2 - L3e*L3e) / (2*L2*L3e);
  if (D < -1 || D > 1) return false;

  float theta3 = atan2(sqrt(1 - D*D), D);
  float theta2 = atan2(z2, r)
               - atan2(L3e*sin(theta3), L2 + L3e*cos(theta3));

  t1 = degrees(theta1);
  t2 = degrees(theta2);
  t3 = degrees(theta3);

  return true;
}

// ================= SETUP =================
void setup(){
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);
  delay(500);

  L3e = L3 + L4;

  setServo(CH_BASE, HOME_BASE);
  setServo(CH_SH,   HOME_SH);
  setServo(CH_EL,   HOME_EL);
  setServo(CH_WY,   HOME_WY);
  setServo(CH_WR,   HOME_WR);

  Serial.println("INPUT FORMAT: x y z s");
  Serial.println("4-input constrained control");
}

// ================= LOOP =================
void loop(){
  if (!Serial.available()) return;
  if (busy) return;
  if (millis() - lastCmd < COMMAND_DELAY) return;

  busy = true;

  float x = Serial.parseFloat();
  float y = Serial.parseFloat();
  float z = Serial.parseFloat();
  float s = Serial.parseFloat();   // configuration parameter

  while (Serial.available()) Serial.read();

  float t1, t2, t3;
  if (IK(x, y, z, t1, t2, t3)){

    int tb  = HOME_BASE + round(t1);
    int ts  = HOME_SH   + round(t2);
    int te  = HOME_EL   + round(t3);
    int twy = HOME_WY   + round(s - t1);   // dependent motion

    smoothMove(tb, ts, te, twy);
    delay(500);
    goHome();

  } else {
    Serial.println("UNREACHABLE POSITION");
  }

  lastCmd = millis();
  busy = false;
}
