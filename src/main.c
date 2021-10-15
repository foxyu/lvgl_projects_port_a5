#include "lvgl.h"
#include <stdio.h>
#include "lv_demo_widgets.h"
#include "lv_demo_benchmark.h"
#include "wayland/wayland.h"

void lv_porting_disp_indev(void)
{
	wayland_init();
	////port display...
	/* Example for 1) */
		//static lv_disp_draw_buf_t draw_buf_dsc_1;
		//static lv_color_t buf_1[MY_DISP_HOR_RES * 10];							/*A buffer for 10 rows*/
		//lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL, MY_DISP_HOR_RES * 10);	 /*Initialize the display buffer*/
	
		/* Example for 2) */
		static lv_disp_draw_buf_t draw_buf_dsc_2;
		static lv_color_t buf_2_1[WAYLAND_HOR_RES * 10];						/*A buffer for 10 rows*/
		static lv_color_t buf_2_2[WAYLAND_HOR_RES * 10];						/*An other buffer for 10 rows*/
		lv_disp_draw_buf_init(&draw_buf_dsc_2, buf_2_1, buf_2_2, WAYLAND_HOR_RES * 10);   /*Initialize the display buffer*/
	
		/* Example for 3) also set disp_drv.full_refresh = 1 below*/
		//static lv_disp_draw_buf_t draw_buf_dsc_3;
		//static lv_color_t buf_3_1[MY_DISP_HOR_RES * MY_DISP_VER_RES];			 /*A screen sized buffer*/
		//static lv_color_t buf_3_2[MY_DISP_HOR_RES * MY_DISP_VER_RES];			 /*An other screen sized buffer*/
		//lv_disp_draw_buf_init(&draw_buf_dsc_3, buf_3_1, buf_3_2, MY_DISP_VER_RES * LV_VER_RES_MAX);   /*Initialize the display buffer*/


	
	//static lv_disp_draw_buf_t draw_buf_dsc_3;
	//static lv_color_t buf_3_1[WAYLAND_HOR_RES * WAYLAND_VER_RES];			 /*A screen sized buffer*/
	//static lv_color_t buf_3_2[WAYLAND_HOR_RES * WAYLAND_VER_RES];			 /*An other screen sized buffer*/
	//lv_disp_draw_buf_init(&draw_buf_dsc_3, buf_3_1, buf_3_2, WAYLAND_HOR_RES * WAYLAND_VER_RES);   /*Initialize the display buffer*/

	/*-----------------------------------
	 * Register the display in LVGL
	 *----------------------------------*/

	static lv_disp_drv_t disp_drv;						   /*Descriptor of a display driver*/
	lv_disp_drv_init(&disp_drv);					/*Basic initialization*/

	/*Set up the functions to access to your display*/

	/*Set the resolution of the display*/
	disp_drv.hor_res = WAYLAND_HOR_RES;
	disp_drv.ver_res = WAYLAND_VER_RES;

	/*Used to copy the buffer's content to the display*/
	disp_drv.flush_cb = wayland_flush;

	/*Set a display buffer*/
	disp_drv.draw_buf = &draw_buf_dsc_2;

	/*Required for Example 3)*/
	//disp_drv.full_refresh = 1;

	/* Fill a memory array with a color if you have GPU.
	 * Note that, in lv_conf.h you can enable GPUs that has built-in support in LVGL.
	 * But if you have a different GPU you can use with this callback.*/
	//disp_drv.gpu_fill_cb = gpu_fill;

	/*Finally register the driver*/
	lv_disp_drv_register(&disp_drv);

	///port indev
	static lv_indev_drv_t indev_drv_touch;
	lv_indev_drv_init(&indev_drv_touch);
	indev_drv_touch.type = LV_INDEV_TYPE_POINTER;
	indev_drv_touch.read_cb = wayland_touch_read;

	lv_indev_drv_register(&indev_drv_touch);

}

void print_help(void)
{
	printf("lvgl_prj cmd\r\n");
	printf("cmd:\r\n");
	printf("   benchmark: run benchmark demo\r\n");
	printf("   music: run music widget\r\n");
	printf("   cluster: run cluster demo \r\n");
	printf("   demowidgets: run demowidget \r\n");
}

static void test(void)
{
	
}

int main(int argc, char** argv)
{			
	lv_init(); 

	lv_porting_disp_indev();

	if(argc < 2){
		print_help();
		return -1;
	}

	if(!strcmp(argv[1],"benchmark"))
	{
		lv_demo_benchmark();
	}
	else if(!strcmp(argv[1], "demowidgets"))
	{
		lv_demo_widgets();
	}
	else if(!strcmp(argv[1], "music"))
	{
		lv_demo_music();
	}
	else{
		print_help();
		return -1;
	}
	while(1)
	{
		lv_task_handler();
	}
}

void tim_lv_tick()
{
	lv_tick_inc(1);
}

