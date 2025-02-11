/****************************************Copyright (c)************************************************
** File Name:			    ft_main.c
** Descriptions:			Factory test main interface source file
** Created By:				xie biao
** Created Date:			2023-02-17
** Modified Date:      		2023-02-17 
** Version:			    	V1.0
******************************************************************************************************/
#include <zephyr.h>
#include <drivers/gpio.h>
#include <drivers/flash.h>

#ifdef CONFIG_PPG_SUPPORT
#include "max32674.h"
#endif
#ifdef CONFIG_TOUCH_SUPPORT
#include "CST816.h"
#endif
#include "nb.h"
#include "external_flash.h"
#include "fota_mqtt.h"
#include "screen.h"
#include "settings.h"
#include "logger.h"
#include "ft_main.h"
#include "ft_gpio.h"

#define FT_MAIN_MENU_MAX_PER_PG	4
#define FT_SUB_MENU_MAX_PER_PG	3

#define FT_MENU_BG_W			169
#define FT_MENU_BG_H			38
#define FT_MENU_BG_X			((LCD_WIDTH-FT_MENU_BG_W)/2)
#define FT_MENU_BG_Y			38
#define FT_MENU_BG_OFFSET_Y		4
#define SETTINGS_MENU_STR_OFFSET_X	5			
#define SETTINGS_MENU_STR_OFFSET_Y	8

#define FT_MENU_STR_W			150
#define FT_MENU_STR_H			30
#define FT_MENU_STR_X			(FT_MENU_BG_X+5)
#define FT_MENU_STR_H			30
#define FT_MENU_STR_OFFSET_Y	8

static bool ft_running_flag = false;
static bool ft_main_redaw_flag = false;

uint8_t ft_main_menu_index = 0;

ft_menu_t ft_menu = {0};

static void FTMainDumpProc(void)
{
}

static void FTMainMenu1Proc()
{
	ft_main_menu_index = ft_menu.index;
}

static void FTMainMenu2Proc(void)
{
	ft_main_menu_index = ft_menu.index;
	EnterFTMenuKey();
}

static void FTMainMenu3Proc(void)
{
	ft_main_menu_index = ft_menu.index;
}

static void FTMainMenu4Proc(void)
{
	ft_main_menu_index = ft_menu.index;
}

static void FTMainMenu5Proc(void)
{
	ft_main_menu_index = ft_menu.index;
}

static void FTMainMenu6Proc(void)
{
	ft_main_menu_index = ft_menu.index;
}

static void FTMainMenu7Proc(void)
{
	ft_main_menu_index = ft_menu.index;
}

static void FTMainMenu8Proc(void)
{
	ft_main_menu_index = ft_menu.index;
}

static void	FTMainMenu9Proc(void)
{
	ft_main_menu_index = ft_menu.index;
}

static void	FTMainMenu10Proc(void)
{
	ft_main_menu_index = ft_menu.index;
}

static void	FTMainMenu11Proc(void)
{
	ft_main_menu_index = ft_menu.index;
}

static void	FTMainMenu12Proc(void)
{
	ft_main_menu_index = ft_menu.index;
}

static void	FTMainMenu13Proc(void)
{
	ft_main_menu_index = ft_menu.index;
}

static void	FTMainMenu14Proc(void)
{
	ft_main_menu_index = ft_menu.index;
}

static void	FTMainMenu15Proc(void)
{
	ft_main_menu_index = ft_menu.index;
}

static void	FTMainMenu16Proc(void)
{
	ft_main_menu_index = ft_menu.index;
}

static void FTMainMenuProcess(void)
{
	switch(ft_menu.index)
	{
	case 0:
		FTMainMenu1Proc();
		break;
	case 1:
		FTMainMenu2Proc();
		break;
	case 2:
		FTMainMenu3Proc();
		break;
	case 3:
		FTMainMenu4Proc();
		break;
	case 4:
		FTMainMenu5Proc();
		break;
	case 5:
		FTMainMenu6Proc();
		break;
	case 6:
		FTMainMenu7Proc();
		break;
	case 7:
		FTMainMenu8Proc();
		break;
	case 8:
		FTMainMenu9Proc();
		break;
	case 9:
		FTMainMenu10Proc();
		break;
	case 10:
		FTMainMenu11Proc();
		break;
	case 11:
		FTMainMenu12Proc();
		break;
	case 12:
		FTMainMenu13Proc();
		break;
	case 13:
		FTMainMenu14Proc();
		break;
	case 14:
		FTMainMenu15Proc();
		break;
	case 15:
		FTMainMenu16Proc();
		break;
	}
}

void FTMainMenuPgUpProc(void)
{
	uint8_t count = FT_MAIN_MENU_MAX_PER_PG;
	
	if(ft_menu.index < (ft_menu.count - count))
	{
		ft_menu.index += count;
		if(screen_id == SCREEN_ID_FACTORY_TEST)
			scr_msg[screen_id].act = SCREEN_ACTION_UPDATE;
	}
}

void FTMainMenuPgDownProc(void)
{
	uint8_t count = FT_MAIN_MENU_MAX_PER_PG;

	if(ft_menu.index >= count)
	{
		ft_menu.index -= count;
		if(screen_id == SCREEN_ID_FACTORY_TEST)
			scr_msg[screen_id].act = SCREEN_ACTION_UPDATE;
	}
}

const ft_menu_t FT_MENU_MAIN = 
{
	FT_MAIN,
	0,
	16,
	{
		{
			{0x0043,0x0075,0x0072,0x0072,0x0065,0x006E,0x0074,0x0020,0x0074,0x0065,0x0073,0x0074,0x0000},//Current test
			{0x004B,0x0065,0x0079,0x0020,0x0074,0x0065,0x0073,0x0074,0x0000},//Key test
			{0x0053,0x0063,0x0072,0x0065,0x0065,0x006E,0x0020,0x0074,0x0065,0x0073,0x0074,0x0000},//Screen test
			{0x0054,0x006F,0x0075,0x0063,0x0068,0x0020,0x0074,0x0065,0x0073,0x0074,0x0000},//Touch test
			{0x0054,0x0065,0x006D,0x0070,0x0065,0x0072,0x0061,0x0074,0x0075,0x0072,0x0065,0x0020,0x0074,0x0065,0x0073,0x0074,0x0000},//Temperature test
			{0x0057,0x0072,0x0069,0x0073,0x0074,0x0020,0x006F,0x0066,0x0066,0x0020,0x0074,0x0065,0x0073,0x0074,0x0000},//Wrist off test
			{0x0053,0x0074,0x0065,0x0070,0x0020,0x0074,0x0065,0x0073,0x0074,0x0000},//Step test
			{0x0046,0x004C,0x0041,0x0053,0x0048,0x0020,0x0074,0x0065,0x0073,0x0074,0x0000},//FLASH test
			{0x0053,0x0049,0x004D,0x0020,0x0063,0x0061,0x0072,0x0064,0x0020,0x0074,0x0065,0x0073,0x0074,0x0000},//SIM card test
			{0x0042,0x004C,0x0045,0x0020,0x0074,0x0065,0x0073,0x0074,0x0000},//BLE test
			{0x0057,0x0069,0x0046,0x0069,0x0020,0x0074,0x0065,0x0073,0x0074,0x0000},//WiFi test
			{0x0047,0x0050,0x0053,0x0020,0x0074,0x0065,0x0073,0x0074,0x0000},//GPS test
			{0x004E,0x0065,0x0074,0x0077,0x006F,0x0072,0x006B,0x0020,0x0074,0x0065,0x0073,0x0074,0x0000},//Network test
			{0x0050,0x0050,0x0047,0x0020,0x0074,0x0065,0x0073,0x0074,0x0000},//PPG test
			{0x0043,0x0068,0x0061,0x0072,0x0067,0x0069,0x006E,0x0067,0x0020,0x0074,0x0065,0x0073,0x0074,0x0000},//Charging test
			{0x0056,0x0069,0x0062,0x0072,0x0061,0x0074,0x0069,0x006F,0x006E,0x0020,0x0074,0x0065,0x0073,0x0074,0x0000},//Vibration test
		},
		{
			{0x7535,0x6D41,0x6D4B,0x8BD5,0x0000},//��������
			{0x6309,0x952E,0x6D4B,0x8BD5,0x0000},//��������
			{0x5C4F,0x5E55,0x6D4B,0x8BD5,0x0000},//��Ļ����
			{0x89E6,0x6478,0x6D4B,0x8BD5,0x0000},//��������
			{0x6E29,0x5EA6,0x6D4B,0x8BD5,0x0000},//�¶Ȳ���
			{0x8131,0x8155,0x6D4B,0x8BD5,0x0000},//�������
			{0x8BA1,0x6B65,0x6D4B,0x8BD5,0x0000},//�Ʋ�����
			{0x0046,0x004C,0x0041,0x0053,0x0048,0x6D4B,0x8BD5,0x0000},//flash����
			{0x0053,0x0049,0x004D,0x5361,0x6D4B,0x8BD5,0x0000},//SIM������
			{0x0042,0x004C,0x0045,0x6D4B,0x8BD5,0x0000},//BLE����
			{0x0057,0x0069,0x0046,0x0069,0x6D4B,0x8BD5,0x0000},//WiFi����
			{0x0047,0x0050,0x0053,0x6D4B,0x8BD5,0x0000},//GPS����
			{0x7F51,0x7EDC,0x6D4B,0x8BD5,0x0000},//�������
			{0x0050,0x0050,0x0047,0x6D4B,0x8BD5,0x0000},//PPG����
			{0x5145,0x7535,0x6D4B,0x8BD5,0x0000},//������
			{0x9707,0x52A8,0x6D4B,0x8BD5,0x0000},//�𶯲���
		},
	},	
	{
		FTMainMenu1Proc,
		FTMainMenu2Proc,
		FTMainMenu3Proc,
		FTMainMenu4Proc,
		FTMainMenu5Proc,
		FTMainMenu6Proc,
		FTMainMenu7Proc,
		FTMainMenu8Proc,
		FTMainMenu9Proc,
		FTMainMenu10Proc,
		FTMainMenu11Proc,
		FTMainMenu12Proc,
		FTMainMenu13Proc,
		FTMainMenu14Proc,
		FTMainMenu15Proc,
		FTMainMenu16Proc,
	},
	{	
		//page proc func
		FTMainMenuPgUpProc,
		FTMainMenuPgDownProc,
		FTMainDumpProc,
		FTMainDumpProc,
	},
};

static void FactoryTestMainUpdate(void)
{
	uint8_t i,count,language;
	uint16_t x,y,w,h;
	uint16_t bg_clor = 0x2124;
	uint16_t green_clor = 0x07e0;

	LCD_Clear(BLACK);
	LCD_SetFontSize(FONT_SIZE_20);
	LCD_SetFontBgColor(bg_clor);

#ifdef CONFIG_TOUCH_SUPPORT
	clear_all_touch_event_handle();
#endif

	if(global_settings.language == LANGUAGE_CHN)
		language = 1;
	else
		language = 0;
	
	for(i=0;i<4;i++)
	{
		LCD_ShowImg_From_Flash(FT_MENU_BG_X, FT_MENU_BG_Y+i*(FT_MENU_BG_H+FT_MENU_BG_OFFSET_Y), IMG_SET_BG_ADDR);
		LCD_SetFontColor(WHITE);
	
		LCD_MeasureUniString(ft_menu.name[language][i+4*(ft_menu.index/4)], &w, &h);
		LCD_ShowUniString(FT_MENU_STR_X+(FT_MENU_STR_W-w)/2, FT_MENU_BG_Y+i*(FT_MENU_BG_H+FT_MENU_BG_OFFSET_Y)+FT_MENU_STR_OFFSET_Y, ft_menu.name[language][i+4*(ft_menu.index/4)]);
	
	#ifdef CONFIG_TOUCH_SUPPORT
		register_touch_event_handle(TP_EVENT_SINGLE_CLICK, 
									FT_MENU_BG_X, 
									FT_MENU_BG_X+FT_MENU_BG_W, 
									FT_MENU_BG_Y+i*(FT_MENU_BG_H+FT_MENU_BG_OFFSET_Y), 
									FT_MENU_BG_Y+i*(FT_MENU_BG_H+FT_MENU_BG_OFFSET_Y)+FT_MENU_BG_H, 
									ft_menu.sel_handler[i+4*(ft_menu.index/4)]);
	#endif
	}	

#ifdef CONFIG_TOUCH_SUPPORT
	register_touch_event_handle(TP_EVENT_MOVING_UP, 0, LCD_WIDTH, 0, LCD_HEIGHT, ft_menu.pg_handler[0]);
	register_touch_event_handle(TP_EVENT_MOVING_DOWN, 0, LCD_WIDTH, 0, LCD_HEIGHT, ft_menu.pg_handler[1]);
	register_touch_event_handle(TP_EVENT_MOVING_LEFT, 0, LCD_WIDTH, 0, LCD_HEIGHT, FactoryTestExit);
	register_touch_event_handle(TP_EVENT_MOVING_RIGHT, 0, LCD_WIDTH, 0, LCD_HEIGHT, FactoryTestExit);	
#endif		

	LCD_ReSetFontBgColor();
	LCD_ReSetFontColor();
}


static void FactoryTestMainShow(void)
{
	uint8_t language;
	uint16_t i,x,y,w,h;
	uint16_t bg_clor = 0x2124;
	uint16_t green_clor = 0x07e0;
	
	LCD_Clear(BLACK);
	LCD_SetFontSize(FONT_SIZE_20);
	LCD_SetFontBgColor(bg_clor);

#ifdef CONFIG_TOUCH_SUPPORT
	clear_all_touch_event_handle();
#endif

	if(global_settings.language == LANGUAGE_CHN)
		language = 1;
	else
		language = 0;
	
	for(i=0;i<4;i++)
	{
		LCD_ShowImg_From_Flash(FT_MENU_BG_X, FT_MENU_BG_Y+i*(FT_MENU_BG_H+FT_MENU_BG_OFFSET_Y), IMG_SET_BG_ADDR);
		LCD_SetFontColor(WHITE);
	
		LCD_MeasureUniString(ft_menu.name[language][i+4*(ft_menu.index/4)], &w, &h);
		LCD_ShowUniString(FT_MENU_STR_X+(FT_MENU_STR_W-w)/2, FT_MENU_BG_Y+i*(FT_MENU_BG_H+FT_MENU_BG_OFFSET_Y)+FT_MENU_STR_OFFSET_Y, ft_menu.name[language][i+4*(ft_menu.index/4)]);
	
	#ifdef CONFIG_TOUCH_SUPPORT
		register_touch_event_handle(TP_EVENT_SINGLE_CLICK, 
									FT_MENU_BG_X, 
									FT_MENU_BG_X+FT_MENU_BG_W, 
									FT_MENU_BG_Y+i*(FT_MENU_BG_H+FT_MENU_BG_OFFSET_Y), 
									FT_MENU_BG_Y+i*(FT_MENU_BG_H+FT_MENU_BG_OFFSET_Y)+FT_MENU_BG_H, 
									ft_menu.sel_handler[i+4*(ft_menu.index/4)]);
	#endif
	}

#ifdef CONFIG_TOUCH_SUPPORT
	register_touch_event_handle(TP_EVENT_MOVING_UP, 0, LCD_WIDTH, 0, LCD_HEIGHT, ft_menu.pg_handler[0]);
	register_touch_event_handle(TP_EVENT_MOVING_DOWN, 0, LCD_WIDTH, 0, LCD_HEIGHT, ft_menu.pg_handler[1]);
	register_touch_event_handle(TP_EVENT_MOVING_LEFT, 0, LCD_WIDTH, 0, LCD_HEIGHT, FactoryTestExit);
	register_touch_event_handle(TP_EVENT_MOVING_RIGHT, 0, LCD_WIDTH, 0, LCD_HEIGHT, FactoryTestExit);	
#endif		

	LCD_ReSetFontBgColor();
	LCD_ReSetFontColor();		
}

static void FactoryTestMainProcess(void)
{
	if(scr_msg[SCREEN_ID_FACTORY_TEST].act != SCREEN_ACTION_NO)
	{
		if(scr_msg[SCREEN_ID_FACTORY_TEST].status != SCREEN_STATUS_CREATED)
			scr_msg[SCREEN_ID_FACTORY_TEST].act = SCREEN_ACTION_ENTER;

		switch(scr_msg[SCREEN_ID_FACTORY_TEST].act)
		{
		case SCREEN_ACTION_ENTER:
			scr_msg[SCREEN_ID_FACTORY_TEST].status = SCREEN_STATUS_CREATED;
			FactoryTestMainShow();
			break;
			
		case SCREEN_ACTION_UPDATE:
			FactoryTestMainUpdate();
			break;
		}
	
		scr_msg[SCREEN_ID_FACTORY_TEST].act = SCREEN_ACTION_NO;
	}
}

void FactoryTestExit(void)
{
	ft_running_flag = false;
	
	SetModemTurnOn();
	EntryIdleScr();
}

void EnterFactoryTestScreen(void)
{
	AppSetModemOff();
	
#ifdef CONFIG_ANIMATION_SUPPORT	
	AnimaStopShow();
#endif
#ifdef CONFIG_TEMP_SUPPORT
	if(TempIsWorking()&&!TempIsWorkingTiming())
		MenuStopTemp();
#endif
#ifdef CONFIG_PPG_SUPPORT
	if(IsInPPGScreen()&&!PPGIsWorkingTiming())
		MenuStopPPG();
#endif
#ifdef CONFIG_WIFI_SUPPORT
	if(IsInWifiScreen()&&wifi_is_working())
		MenuStopWifi();
#endif

	LCD_Set_BL_Mode(LCD_BL_AUTO);
	
	history_screen_id = screen_id;
	scr_msg[history_screen_id].act = SCREEN_ACTION_NO;
	scr_msg[history_screen_id].status = SCREEN_STATUS_NO;

	screen_id = SCREEN_ID_FACTORY_TEST;	
	scr_msg[SCREEN_ID_FACTORY_TEST].act = SCREEN_ACTION_ENTER;
	scr_msg[SCREEN_ID_FACTORY_TEST].status = SCREEN_STATUS_CREATING;

	SetLeftKeyUpHandler(FTMainMenuProcess);
	SetRightKeyUpHandler(FactoryTestExit);
}

void ReturnFTMainMenu(void)
{
	memcpy(&ft_menu, &FT_MENU_MAIN, sizeof(ft_menu_t));
	FactoryTestMainShow();
}

void EnterFactoryTest(void)
{
	ft_running_flag = true;
	memcpy(&ft_menu, &FT_MENU_MAIN, sizeof(ft_menu_t));

	EnterFactoryTestScreen();
}

bool FactryTestActived(void)
{
	return ft_running_flag;
}

void FactoryTestProccess(void)
{
	if(!ft_running_flag)
		return;

	switch(ft_menu.id)
	{
	case FT_MAIN:
		FactoryTestMainProcess();
		break;
	case FT_FLASH:
		break;
	case FT_LCD:
		break;
	case FT_KEY:
		FTMenuKeyProcess();
		break;
	case FT_WRIST:
		break;
	case FT_VIABRATE:
		break;
	case FT_NET:
		break;
	case FT_AUDIO:
		break;
	case FT_BLE:
		break;
	case FT_GPS:
		break;
	case FT_IMU:
		break;
	case FT_PPG:
		break;
	case FT_TEMP:
		break;
	case FT_TOUCH:
		break;
	case FT_WIFI:
		break;
	}
}
