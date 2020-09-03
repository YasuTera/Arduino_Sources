/**
 * Arduino UnoでのKXSC7-2050加速度センサーのスケッチ
 */
const int X_PIN = A3;
const int Y_PIN = A4;
const int Z_PIN = A5;

/* 加速度センサの値の構造体 */
struct Coordinate {
  long cx;
  long cy;
  long cz;
};

/* 角度の構造体 */
struct Angle {
  int ax;
  int ay;
  int az;
};

void setup() {
  Serial.begin(115200) ;
}

void loop() {
  Coordinate c = getCoordinate();
  // showCoordinate(c); // ここのコメントアウトを外して最大値・最小値を記録してください
  Angle a = angleCalculation(c);
  showAngle(a);

  delay(50) ;
}

/**
 * 加速度センサーの値を取得する関数
 */
Coordinate getCoordinate() {
  Coordinate c;
  long x = 0, y = 0, z = 0;

  // 各データを100回読込んで平均化する
  for (int i = 0; i < 100; i++) {
    x = x + analogRead(X_PIN);  // Ｘ軸を読込む
    y = y + analogRead(Y_PIN);  // Ｙ軸を読込む
    z = z + analogRead(Z_PIN);  // Ｚ軸を読込む
  }

  c.cx = x / 100;
  c.cy = y / 100;
  c.cz = z / 100;
  return c;
}

/**
 * センサの値から各座標の角度を計算する関数
 */
Angle angleCalculation(Coordinate c){
  // 以下のx,y,zの最大値最小値は各自で測定してください
  int MAX_X = 524, MAX_Y = 514, MAX_Z = 526;
  int MIN_X = 222, MIN_Y = 214, MIN_Z = 227;

  // 各座標の1度あたりの角度を計算
  float oneAngleX = (MAX_X - MIN_X) / 180.000;
  float oneAngleY = (MAX_Y - MIN_Y) / 180.000;
  float oneAngleZ = (MAX_Z - MIN_Z) / 180.000;

  // 各座標の角度を計算
  Angle a;
  a.ax = (c.cx - MIN_X) / oneAngleX - 90;
  a.ay = (c.cy - MIN_Y) / oneAngleY - 90;
  a.az = (c.cz - MIN_Z) / oneAngleZ - 90;
  return a;
}

/**
 * 角度を表示する関数
 */
void showAngle(Angle a) {
  Serial.print(a.ax);
  Serial.print(",");
  Serial.print(a.ay);
  Serial.print(",");
  Serial.println(a.az);
}

/**
 * 加速度センサーの値を表示する関数
 */
void showCoordinate(Coordinate c) {
  Serial.print("x:");
  Serial.print(c.cx);
  Serial.print(" y:");
  Serial.print(c.cy);
  Serial.print(" z:");
  Serial.println(c.cz);
}
