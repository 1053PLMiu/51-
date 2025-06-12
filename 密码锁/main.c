#include <REGX52.H>
#include "Delay.H"
#include "LCD1602.H"
#include "MatrixKey.H"

//定义区域
unsigned char password[6] = {1,2,3,4,5,6};  // 解锁密码

unsigned char inputPassword[6];    // 存储用户输入的密码
 
unsigned char index = 0;       // 输入密码的索引            

unsigned char KeyNum;         //接收键码

bit isCorrect=1;

//函数声明区域
void ClearInputPassword(void);

void CheckPassword(void);

void ClearTheScreen(void);


void main(){
	LCD_Init();
	LCD_ShowString(1,1,"Password:");
	while(1){
		
		KeyNum=MatrixKey();
		
		if(KeyNum<10 && KeyNum!=0 &&index<6){		  
			inputPassword[index] = KeyNum;	// 获取按键值并存储在inputPassword			
			LCD_ShowNum(2,index+1,inputPassword[index],1);
			index++;
			LCD_ShowString(2,10,"Count:");
			LCD_ShowNum(2,16,index,1);
		}
		
		if(KeyNum == 11){
			if(index == 6){ // 必须输入满6位才能验证
				CheckPassword();   //验证
				if(isCorrect){
					ClearTheScreen();
					LCD_ShowString(1,14,"YES");
						
				}else{
					ClearTheScreen();
					LCD_ShowString(1,14," NO");
				}
				ClearInputPassword(); // 清除输入
			}else{
				LCD_ShowString(1, 14, "few"); // 提示输入数据太少
				isCorrect = 0;

			}
		}	
		//   清零
			 if(KeyNum == 10){
				
				LCD_ShowString(1, 14, "Clr"); // 显示清零提示
				Delay(500);
				ClearInputPassword();
				ClearTheScreen();
				
			}

			// 处理退出系统按键
			if(KeyNum == 12){				
				LCD_Init();
				LCD_ShowString(1, 1, "System Exit");
				while (1); // 无限循环，停止程序
			}
		}
	
	}
	


/**
  * @brief    用来清除用户输入的数组密码和键码和输入的索引限制
  * @param    无
  * @retval   无
  */
void ClearInputPassword(void){
    unsigned char i;
    for(i=0;i<6;i++){ // 遍历整个密码数组，确保全部清除
        inputPassword[i] = 0;
    }
    KeyNum = 0;
    index = 0;
//    LCD_Init(); // 清屏
//    LCD_ShowString(1, 1, "Password:");
//   LCD_ShowString(1, 14, "     "); // 清除状态提示区域
}

/**
  * @brief    检验密码是否正确，赋值给isCorrect确定
  * @param    无
  * @retval   无
  */
void CheckPassword(void){
    unsigned char i;
    isCorrect=1;
    for(i=0;i<6;i++){
        if (inputPassword[i] != password[i]) {
            isCorrect = 0; // 如果有任意一个字符不匹配，则密码错误
            break;
        }
    }
}

/**
  * @brief    清屏恢复初始
  * @param    无
  * @retval   无
  */
void ClearTheScreen(void){
	LCD_Init();
	LCD_ShowString(1, 1, "Password:");
	
}

