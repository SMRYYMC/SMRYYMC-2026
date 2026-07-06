#include "asr.h"
extern "C"{ void * __dso_handle = 0 ;}
#include "setup.h"
#include "myLib/asr_servo.h"
#include "myLib/asr_event.h"

uint32_t snid;
uint8_t L = 0;
uint8_t R = 0;
uint8_t F = 0;
uint8_t B = 0;
uint8_t G = 0;
Servo servo_4;
Servo servo_0;
Servo servo_6;
Servo servo_3;
Servo servo_5;
void ASR_CODE();

//{speak:娇娇-邻家女声,vol:10,speed:10,platform:haohaodada}
//{playid:10001,voice:欢迎使用智能机械臂，用小谢唤醒我。}
//{playid:10002,voice:我退下了，用小谢唤醒我}

/*描述该功能...
*/
void ASR_CODE(){
  //本函数是语音识别成功钩子程序
  //运行时间越短越好，复杂控制启动新线程运行
  //唤醒时间设置必须在ASR_CODE中才有效
  set_state_enter_wakeup(60000);
  //用switch分支选择，根据不同的识别成功的ID执行相应动作，点击switch左上齿轮
  //可以增加分支项
  switch (snid) {
   case 1:
    //左转时，先检测Y是否为0
    //若Y=0、Z=0，那么进行左转45度，并且将Z置1
    //若Y=0、Z=1，那么再进行左转45度，并且将Z置2
    //若Y=1，意味着目前在右侧状态1，那么需要往回正
    //若Y=2，意味着目前在右侧状态2，那么需要右侧状态1
    if((R == 0) && (L == 0)){
      servo_4.write(135);
      L = 1;
      R = 0;
      //{playid:10500,voice:好的，执行左转}
      play_audio(10500);
      //此时状态为左1状态
    }
    else if((R == 0) && (L == 1)){
      servo_4.write(175);
      L = 2;
      R = 0;
      //{playid:10501,voice:好的，执行左转}
      play_audio(10501);
      //此时状态为左2状态
    }
    else if((R == 1) && (L == 0)){
      servo_4.write(90);
      L = 0;
      R = 0;
      //{playid:10502,voice:好的，执行左转}
      play_audio(10502);
      //此时状态为回正状态
    }
    else if((R == 2) && (L == 0)){
      servo_4.write(45);
      L = 0;
      R = 1;
      //{playid:10503,voice:好的，执行左转}
      play_audio(10503);
      //此时状态为右1状态
    }
    else if((R == 0) && (L == 2)){
      //{playid:10504,voice:已经达到最左侧了，不能再转了}
      play_audio(10504);
    }
    break;
   case 2:
    //右转时，先检测Z是否为0
    //若Z=0、Y=0，那么进行右转45度，并且将Y置1
    //若Z=0、Y=1，那么再进行右转45度，并且将Y置2
    //若Z=1，意味着目前在左侧状态1，那么需要往回正
    //若Z=2，意味着目前在左侧状态2，那么需要左侧状态1
    if((R == 0) && (L == 0)){
      servo_4.write(45);
      L = 0;
      R = 1;
      //{playid:10505,voice:好的，执行右转}
      play_audio(10505);
      //此时状态为右1状态
    }
    else if((R == 1) && (L == 0)){
      servo_4.write(10);
      L = 0;
      R = 2;
      //{playid:10506,voice:好的，执行右转}
      play_audio(10506);
      //此时状态为右2状态
    }
    else if((R == 0) && (L == 1)){
      servo_4.write(90);
      L = 0;
      R = 0;
      //{playid:10507,voice:好的，执行右转}
      play_audio(10507);
      //此时状态为回正状态
    }
    else if((R == 0) && (L == 2)){
      servo_4.write(135);
      L = 1;
      R = 0;
      //{playid:10508,voice:好的，执行右转}
      play_audio(10508);
      //此时状态为左1状态
    }
    else if((R == 2) && (L == 0)){
      //{playid:10509,voice:已经达到最右侧了，不能再转了}
      play_audio(10509);
    }
    break;
   case 3:
    //前伸时，先检测B是否为0
    //若B=0、F=0，那么进行前伸45度，并且将F置1
    //若B=0、F=1，那么再进行前伸45度，并且将F置2
    //若B=1，意味着目前在后仰状态1，那么需要往回正
    //若B=2，意味着目前在后仰状态2，那么需要后仰状态1
    if((F == 0) && (B == 0)){
      servo_0.write(135);
      B = 0;
      F = 1;
      //{playid:10510,voice:好的，执行前伸}
      play_audio(10510);
      //此时状态为右1状态
    }
    else if((B == 0) && (F == 1)){
      servo_0.write(170);
      B = 0;
      F = 2;
      //{playid:10511,voice:好的，执行前伸}
      play_audio(10511);
      //此时状态为回正状态
    }
    else if((F == 0) && (B == 1)){
      servo_0.write(90);
      B = 0;
      F = 0;
      //{playid:10512,voice:好的，执行前伸}
      play_audio(10512);
      //此时状态为左1状态
    }
    else if((F == 0) && (B == 2)){
      servo_0.write(45);
      B = 1;
      F = 0;
      //{playid:10513,voice:好的，执行前伸}
      play_audio(10513);
    }
    else if((F == 2) && (B == 0)){
      //{playid:10514,voice:已经达到最前侧了，不能再前伸了}
      play_audio(10514);
    }
    break;
   case 4:
    //后仰时，先检测F是否为0
    //若F=0、B=0，那么进行后仰45度，并且将B置1
    //若F=0、B=1，那么再进行后仰45度，并且将B置2
    //若F=1，意味着目前在前伸状态1，那么需要往回正
    //若F=2，意味着目前在前伸状态2，那么需要前伸状态1
    if((F == 0) && (B == 0)){
      servo_0.write(45);
      F = 0;
      B = 1;
      //{playid:10515,voice:好的，执行后仰}
      play_audio(10515);
    }
    else if((B == 1) && (F == 0)){
      servo_0.write(10);
      B = 2;
      F = 0;
      //{playid:10516,voice:好的，执行后仰}
      play_audio(10516);
      //此时状态为回正状态
    }
    else if((F == 1) && (B == 0)){
      servo_0.write(90);
      B = 0;
      F = 0;
      //{playid:10517,voice:好的，执行后仰}
      play_audio(10517);
      //此时状态为左1状态
    }
    else if((F == 2) && (B == 0)){
      servo_0.write(135);
      B = 0;
      F = 1;
      //{playid:10518,voice:好的，执行后仰}
      play_audio(10518);
    }
    else if((F == 0) && (B == 2)){
      //{playid:10519,voice:已经达到最后侧了，不能再后仰了}
      play_audio(10519);
    }
    break;
   case 5:
    //先判断G状态，抓
    //G=0，合爪状态
    //G=1，开爪状态
    //若G=0，则执行“无法抓取”
    //若G=1，则执行“抓取”
    if(G == 1){
      servo_6.write(100);
      G = 0;
      //{playid:10520,voice:好的，执行抓取}
      play_audio(10520);
    }
    else{
      G = 0;
      //{playid:10521,voice:已经处于抓取状态了，无法抓取}
      play_audio(10521);
    }
    break;
   case 6:
    //先判断G状态，放
    //G=0，合爪状态
    //G=1，开爪状态
    //若G=1，则执行“无法放开”
    //若G=0，则执行“放开”
    if(G == 0){
      servo_6.write(40);
      G = 1;
      //{playid:10522,voice:好的，执行放开}
      play_audio(10522);
    }
    else{
      G = 1;
      //{playid:10523,voice:已经处于放开状态了，无法放开}
      play_audio(10523);
    }
    break;
   case 7:
    servo_4.write(90);
    servo_0.write(90);
    servo_3.write(90);
    servo_5.write(90);
    servo_6.write(100);
    break;
   case 8:
    //立正模式，，仅仅需要控制4号舵机
    servo_4.write(90);
    servo_0.write(90);
    servo_3.write(90);
    servo_5.write(175);
    servo_6.write(100);
    break;
   case 9:
    //握手模式，需要控制4号舵机，以及前伸模式，然后让5号舵机多次开合
    servo_0.write(135);
    servo_3.write(135);
    servo_5.write(135);
    servo_6.write(100);
    delay(1000);
    //达到上述状态后进行5号舵机开合状态
    servo_6.write(40);
    delay(1000);
    servo_6.write(100);
    delay(1000);
    servo_6.write(40);
    delay(1000);
    servo_6.write(100);
    break;
   case 10:
    //鞠躬模式，
    servo_4.write(90);
    servo_0.write(90);
    servo_3.write(90);
    servo_5.write(175);
    servo_6.write(100);
    delay(500);
    servo_3.write(75);
    delay(500);
    servo_3.write(60);
    delay(500);
    servo_3.write(45);
    delay(500);
    servo_3.write(30);
    break;
   case 11:
    //点头模式，
    servo_4.write(90);
    servo_0.write(90);
    servo_3.write(90);
    servo_5.write(175);
    servo_6.write(100);
    delay(1000);
    servo_5.write(90);
    delay(1000);
    servo_5.write(175);
    delay(1000);
    servo_5.write(90);
    delay(1000);
    servo_5.write(175);
    break;
  }

}

void hardware_init(){
  //需要操作系统启动后初始化的内容
  //音量范围1-7
  vol_set(4);
  servo_4.write(90);
  servo_0.write(90);
  servo_3.write(90);
  servo_5.write(90);
  servo_6.write(100);
  vTaskDelete(NULL);
}

void setup()
{
  //需要操作系统启动前初始化的内容
  //播报音下拉菜单可以选择，合成音量是指TTS生成文件的音量
  //欢迎词指开机提示音，可以为空
  //退出语音是指休眠时提示音，可以为空
  //休眠后用唤醒词唤醒后才能执行命令，唤醒词最多5个。回复语可以空。ID范围为0-9999
  //{ID:0,keyword:"唤醒词",ASR:"小谢",ASRTO:"我在"}
  //{ID:1,keyword:"命令词",ASR:"左转",ASRTO:""}
  //{ID:2,keyword:"命令词",ASR:"右转",ASRTO:""}
  //{ID:3,keyword:"命令词",ASR:"前伸",ASRTO:""}
  //{ID:4,keyword:"命令词",ASR:"后仰",ASRTO:""}
  //{ID:5,keyword:"命令词",ASR:"抓取",ASRTO:""}
  //{ID:6,keyword:"命令词",ASR:"放开",ASRTO:""}
  //{ID:7,keyword:"命令词",ASR:"全部回正",ASRTO:"好的，全部回正"}
  //{ID:8,keyword:"命令词",ASR:"立正",ASRTO:"好的，立正"}
  //{ID:9,keyword:"命令词",ASR:"握手",ASRTO:"好的，握手，你好啊你好啊"}
  //{ID:10,keyword:"命令词",ASR:"鞠躬",ASRTO:"好的，鞠躬"}
  //{ID:11,keyword:"命令词",ASR:"点头",ASRTO:"好的，点头"}
  setPinFun(4,FIFTH_FUNCTION);
  setPinFun(0,SECOND_FUNCTION);
  dpmu_set_adio_reuse(PA0,DIGITAL_MODE);
  setPinFun(3,FIFTH_FUNCTION);
  setPinFun(5,FIFTH_FUNCTION);
  setPinFun(6,FIFTH_FUNCTION);
  //左转变量
  //右转变量
  //前伸变量
  //后仰变量
  //抓取/放下变量,0为闭爪状态，1为开爪状态
  //舵机编号，从下到上分别为1、2、3、4、5号舵机
  //1号舵机控制左右转换
  //2号舵机控制前伸、后仰
  //3号舵机控制
  //4号舵机控制
  //5号舵机控制抓取
  servo_4.attach(4);
  servo_0.attach(0);
  servo_6.attach(6);
  servo_3.attach(3);
  servo_5.attach(5);
}

