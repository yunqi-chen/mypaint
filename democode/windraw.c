#include "windraw.h"
#include "draw.h"
#include "operation.h"
#include "file.h"
#include "math.h"
char* bColors[] =
{
	"Black",
	"Dark Gray",
	"Light Gray",
	"White",
	"Brown",
	"Red",
	"Orange",
	"Yellow",
	"Green",
	"Blue",
	"Violet",
	"Magenta",
	"Cyan"
};
void Initwin()
{
	static char* menuListFile[] = { "File",
		"New  | Ctrl-N", // 快捷键必须采用[Ctrl-X]格式，放在字符串的结尾
		"Open | Ctrl-O",
		"Save | Ctrl-S",
		"Rename",
		"Close",
		"Exit" };
	static char* menuListEdit[] = { "Edit",
		"Undo   | Ctrl-Z",
		"Redo   | Ctrl-Y",
		"Cut    | Ctrl-X",
		"Copy   | Ctrl-C",
		"Paste  | Ctrl-V",
		"Delete | Delete" };
	static char* menuListDraw[] = { "Draw",
		"Rectangle",
		"Roundrec",
		"Diamond",
		"Line",
		"Arrow" };
	static char* menuListHelp[] = { "Help",
		"About us",
		"Short cuts list",
		"Guard"
	};
	static char* menuListColors1[] =
	{
		"Fill Colors",
		"Black(default)",
		"Dark Gray",
		"Light Gray",
		"White",
		"Brown",
		"Red",
		"Orange",
		"Yellow",
		"Green",
		"Blue",
		"Violet",
		"Magenta",
		"Cyan"
	};
	static char* menuListColors2[] =
	{
		"Front Colors",
		"Black(default)",
		"Dark Gray",
		"Light Gray",
		"White",
		"Brown",
		"Red",
		"Orange",
		"Yellow",
		"Green",
		"Blue",
		"Violet",
		"Magenta",
		"Cyan"
	};
	static char* menuListAli[] =
	{
		"Alignment",
		"L(default)",
		"R"
	}; 
	static char* menuListPenSize[] =
	{
		"PenSize",
		"1",
		"2",
		"3",
		"4",
		"5"
	};
	static char* menuListArrowstyle[] =
	{
		"Arrowstyle",
		"1",
		"2",
	};
	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = winheight;
	double w = TextStringWidth(menuListFile[0]) * 4; // 主菜单宽度
	double wlist = TextStringWidth(menuListFile[1]) * 1.2;
	double xindent = winheight / 20; // 缩进
	int    selection;
	int enable_move_disc = 1;
	// menu bar
	h = fH * 1.5; // 控件高度
	DefineColor("Black", 0, 0, 0);
	SetPenColor("Black");
	drawRectangle(x, y - 2 * h, winwidth, h, 0);
	drawRectangle(x, 0, 10 * h, winheight - 2 * h, 0);
	drawRectangle(10 * h, 0, winwidth - 8 * h, h, 0);
	SetPenColor("Light Gray");
	drawRectangle(10 * h, h, 8 * h, winheight - 3 * h, 1);
	drawRectangle(winwidth - 8 * h, h, 8 * h, winheight - 3 * h, 1);
	setMenuColors("Dark Gray", "White", "Black", "Yellow", 1);
	drawMenuBar(0, y - h, winwidth, h);
	selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (selection == 2)
	{
		char szFile[MAX_PATH] = { 0 };
		FileOpenDialog(szFile);//szFile中返回了再文件选择窗口选择得文件得路径
	}
	else if (selection == 3)
	{
		char szFile[MAX_PATH] = { 0 };
		FileSaveDialog(szFile);//szFile中返回了再文件选择窗口选择得文件得路径
	}
	// Edit 菜单
	selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListEdit, sizeof(menuListEdit) / sizeof(menuListEdit[0]));
	//Draw 菜单
	selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListDraw, sizeof(menuListDraw) / sizeof(menuListEdit[0]));
	// Help 菜单
	selection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
	drawMenuBar(44 * h, y - 2 * h, 10 * h, h);
	selection = menuList(GenUIID(0), 44 * h, y - 2 * h, w, wlist, h, menuListColors1, sizeof(menuListColors1) / sizeof(menuListColors1[0]));
	if (selection)
	{
		filled_color = selection-1;
		if (operate_flag == 2)
		{
			strcpy(selected_rect->fill_color, bColors[filled_color]);
			
			
		}
	}
	selection = menuList(GenUIID(0), 44 * h+w, y -2*  h, w, wlist, h, menuListColors2, sizeof(menuListColors2) / sizeof(menuListColors2[0]));
	if (selection)
	{
		front_color = selection - 1;
		if (operate_flag == 2)
		{
			strcpy(selected_rect->front_color, bColors[front_color]);
			
			
		}
	}
	selection = menuList(GenUIID(0), 44 * h+2*w, y - 2 * h, w, wlist, h, menuListAli, sizeof(menuListAli) / sizeof(menuListAli[0]));
	if (selection)
	{
		alignment_flag = selection - 1;
		if (operate_flag == 2)
		{
			selected_rect->alignment = alignment_flag == 0 ? 'L' : 'R';
		}
	}
	selection = menuList(GenUIID(0), 44 * h + 3 * w, y - 2 * h, w, wlist, h, menuListPenSize, sizeof(menuListPenSize) / sizeof(menuListAli[0]));
	if (selection)
	{
		PenSize = selection;
		if (operate_flag == 2)
		{
			
		}
	}
	selection = menuList(GenUIID(0), 44 * h -w, y - 2 * h, w, wlist, h, menuListArrowstyle, sizeof(menuListArrowstyle) / sizeof(menuListArrowstyle[0]));
	if (selection)
	{
		arrow_style = selection - 1;
	}
}
void InitButton()
{
	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = winheight;
	double xindent = winheight / 20; // 缩进
	int    selection;
	int enable_move_disc = 1;
	setButtonColors("Light Gray", "Black", "Dark Gray", "Yellow", 1);
	if (button(GenUIID(0), 0 * h, y - 2 * h, h, h, "←"))
	{
		// undo button
	}

	if (button(GenUIID(0), 1 * h, y - 2 * h, h, h, "→"))
	{
		//redo button
	}
	if (button(GenUIID(0), 3 * h, y - 2 * h, 4 * h, h, "Save"))
	{
		//Save button
	}
	if (button(GenUIID(0), 7 * h, y - 2 * h, 4 * h, h, "Open"))
	{
		//Open button
	}
	if (button(GenUIID(0), 11 * h, y - 2 * h, 4 * h, h, "Delete"))
	{
		if (operate_flag == 2)
		{
			pop();
			operate_flag = 0;
		}
	}
	if (button(GenUIID(0), 15 * h, y - 2 * h, 4 * h, h, "Grid"))
	{
		//whether use grid lines
	}
	if (button(GenUIID(0), 19 * h, y - 2 * h, 4 * h, h, "Copy"))
	{
		//
	}
	if (button(GenUIID(0), 23 * h, y - 2 * h, 4 * h, h, "Paste"))
	{
		//whether use grid lines
	}
	setButtonColors("Light Gray", "Black", "Dark Gray", "Black", 0);
	if (button(GenUIID(0), 0, y - 4 * h, 10 * h, 2 * h, "Rectangle"))
	{

		//draw Rectangle
		operate_flag = 1;
		click_count = 0;
		draw_what = 1;
	}
	if (button(GenUIID(0), 0, y - 6 * h, 10 * h, 2 * h, "Roundrec"))
	{
		//draw roundrec
		operate_flag = 1;
		click_count = 0;
		draw_what = 2;
	}
	if (button(GenUIID(0), 0, y - 8 * h, 10 * h, 2 * h, "Diamond"))
	{
		//draw diamond
		operate_flag = 1;
		click_count = 0;
		draw_what = 3;
	}
	if (button(GenUIID(0), 0, y - 10 * h, 10 * h, 2 * h, "Line"))
	{
		//draw line
		operate_flag = 1;
		click_count = 0;
		draw_what = 4;
	}
	if (button(GenUIID(0), 0, y - 12 * h, 10 * h, 2 * h, "Directional connection"))
	{
		//draw directional connection 单向箭头
		operate_flag = 1;
		click_count = 0;
		draw_what = 5;
	}
	if (button(GenUIID(0), 0, y - 14 * h, 10 * h, 2 * h, "Bidirectional connection"))
	{
		//draw 双向箭头
		operate_flag = 1;
		click_count = 0;
		draw_what = 6;
	}
	if (button(GenUIID(0), 0, y - 16 * h, 10 * h, 2 * h, "Dashed line"))
	{
		//draw dashed line 虚线
		operate_flag = 1;
		click_count = 0;
		draw_what = 7;
	}
	if (button(GenUIID(0), 0, y - 18 * h, 10 * h, 2 * h, "Parallelogram"))
	{
         //draw process
		operate_flag = 1;
		click_count = 0;
		draw_what = 8 ;
	}
	if (button(GenUIID(0), 0, y - 20 * h, 10 * h, 2 * h, "Circle"))
	{
        //draw circle  圆
		operate_flag = 1;
		click_count = 0;
		draw_what = 9;
	}
	if (button(GenUIID(0), 0, y - 22 * h, 10 * h, 2 * h, "Oval"))
	{
        //draw oval  椭圆 
		operate_flag = 1;
		click_count = 0;
		draw_what = 10;
	}
	setButtonColors("Light Gray", "Black", "Dark Gray", "Black", 0);
	if (filled_flag==1)
	{
		if (button(GenUIID(0), 10 * h, 0, 4 * h, h, "filled"))
		{
			filled_flag *= -1;
		}
	}
	else
	{
		if (button(GenUIID(0), 10 * h, 0, 4 * h, h, "unfilled"))
		{
			filled_flag *= -1;
		}
	}
	if (operate_flag == 0)
		drawLabel(winwidth - 6 * h, 0.25 * h, "No operation");
	else if (operate_flag == 1)
		drawLabel(winwidth - 6 * h, 0.25 * h, "Drawing");
	else if (operate_flag == 2)
		drawLabel(winwidth - 6 * h, 0.25 * h, "Selecting");
	else if (operate_flag == 3)
		drawLabel(winwidth - 6 * h, 0.25 * h, "Moving");
	drawLabel(winwidth - 13 * h, 0.25 * h, "Front Color:");
	drawLabel(winwidth - 9.5 * h, 0.25 * h, bColors[front_color]);
	drawLabel(winwidth - 19 * h, 0.25 * h, "Fill Color:");
	drawLabel(winwidth - 16 * h, 0.25 * h, bColors[filled_color]);
	if (textbox(GenUIID(0), 18 * h, 0, 10 * h, h, mytext, 100))
	{
		if (operate_flag == 2)
		{
			switch (select_what)
			{
			case 1:
			{
				strcpy(selected_rect->text, mytext);
				break;
			}
			case 2:
			{
				strcpy(selected_roundrect->text, mytext);
				break;
			}
			case 3:
			{
				strcpy(selected_diamond->text, mytext);
				break;
			}
			}
		}
	}

}



/* 画一个圆角矩形 */
void drawRoundrec(double x, double y, double w, double h, int fillflag)
{
	MovePen(x, y);
	if( fillflag ) StartFilledRegion(1); 
	{
		DrawLine(w, 0);
		DrawEllipticalArc(w/6,h/6, 270, 90);
		DrawLine(0, h);
		DrawEllipticalArc(w/6,h/6, 0, 90);
		DrawLine(-w, 0);
		DrawEllipticalArc(w/6,h/6, 90, 90);
		DrawLine(0, -h);
		DrawEllipticalArc(w/6,h/6, 180, 90);
	}
	if( fillflag ) EndFilledRegion();
}

/* 画一个菱形 */
void drawDiamond(double x, double y, double w, double h, int fillflag)
{
	MovePen(x, y+h/2);
	if( fillflag ) StartFilledRegion(1); 
	{
		DrawLine(w/2, h/2);
		DrawLine(w/2, -h/2);
		DrawLine(-w/2, -h/2);
		DrawLine(-w/2, h/2);
	}
	if( fillflag ) EndFilledRegion();
}

/*画一个圆 */
void drawCircle(double x, double y, double r,int fillflag)
{
	
    MovePen(x + r, y);
	if( fillflag ) StartFilledRegion(1); 
	{
		DrawArc(r, 0, 360);
	}
	if( fillflag ) EndFilledRegion();
	
 } 


/* 画一条直线 */
void drawLine(double x1,double y1,double dx,double dy)
{ 
	MovePen(x1, y1);
	DrawLine(dx, dy);
}

/*画一条虚线 */ 
void drawDashline(double x1,double y1,double dx, double dy)
{
	int i;
	double ddx=dx/10;   
	double ddy=dy/10;
	for(i=0;i<10;i+=2)
	{
		MovePen(x1+i*ddx,y1+i*ddy);
		DrawLine(dx/10,dy/10);
	}
	 
}
/*画一个单向箭头*/ 
void drawDirectionalconnection(double x, double y, double dx, double dy, int fillflag, int arrow_style)
{
	
	MovePen( x,  y);
	double sin =  dy / (sqrt( dy *  dy +  dx *  dx));
	double cos =  dx / (sqrt( dy *  dy +  dx *  dx));
	double length =  sqrt(dy * dy + dx * dx);
	if ( arrow_style == 1)
	{
		if ( fillflag) StartFilledRegion(1);
		
			DrawLine(length * 0.05*sin, -cos * length * 0.05);
			DrawLine(0.9 * length * cos, 0.9 * length * sin);
			DrawLine(length * 0.05*sin, -cos * length * 0.05);
			DrawLine(dx - 0.9 * length * cos - length * 0.1*sin, dy - 0.9 * length * sin + cos* length * 0.1);
			DrawLine(-dx +0.9 * length * cos - length * 0.1 * sin, -dy + 0.9 * length * sin + cos * length * 0.1);
			DrawLine(length * 0.05 * sin, -cos * length * 0.05);
			DrawLine(-0.9 * length * cos, -0.9 * length * sin);
			DrawLine(length * 0.05 * sin, -cos * length * 0.05);
			
		if ( 	fillflag) EndFilledRegion();
	}
	else
	{
		DrawLine( dx,  dy);
		DrawLine(0.1*length* (-0.65 * cos - 0.5 * sin), 0.1 * length*( -0.65 * sin + 0.5 * cos));
		MovePen(x + dx, y + dy);
		DrawLine(0.1 * length * (-0.65 * cos + sin * 0.5), 0.1 * length * (-sin * 0.65 - cos * 0.5));
	}
}

/*画一个双向箭头*/ 
void drawBidirectionalconnection(double x, double y, double dx, double dy, int fillflag, int arrow_style)
{
	double sin = dy / (sqrt(dy * dy + dx * dx));
	double cos = dx / (sqrt(dy * dy + dx * dx));
	double length = sqrt(dy * dy + dx * dx);
	drawDirectionalconnection(x+0.5*dx, y+0.5*dy, 0.5*dx, 0.5*dy, fillflag, arrow_style);
	drawDirectionalconnection(x+0.5*dx, y+0.5*dy, -0.5*dx, -0.5*dy, fillflag, arrow_style);
}

/*画一个椭圆*/ 
void drawOval(double x, double y, double rx,double ry,int fillflag)
{
	
    MovePen(x + 2*rx, y+ry);
	if( fillflag ) StartFilledRegion(1); 
	{
		DrawEllipticalArc(rx, ry, 0, 360);
	}
	if( fillflag ) EndFilledRegion();
	
 } 
/* 画一个process */
void drawProcess(double x, double y, double w, double h, int fillflag)
{
	MovePen(x, y);
	if( fillflag ) StartFilledRegion(1); 
	{
		DrawLine(w*0.75, 0);
		DrawLine(w*0.25, h);
		DrawLine(-w*0.75, 0);
		DrawLine(-w*0.25, -h);
	}
	if( fillflag ) EndFilledRegion();
	    

	
}


/* 画一个圆角矩形，并在其内部居中显示一个字符串标签label */
void drawRoundrecBox(double x, double y, double w, double h, int fillflag, char *label, char labelAlignment, char *labelColor)
{
	double fa = GetFontAscent();   //这个我不知道干嘛的 
	//roundrec 
	drawRoundrec(x,y,w,h,fillflag);
	// text
	if( label && strlen(label)>0 ) {
		mySetPenColor(labelColor);
		if( labelAlignment=='L' )
			MovePen(x+fa/2, y+h/2-fa/2);
		else if( labelAlignment=='R' )
			MovePen(x+w-fa/2-TextStringWidth(label), y+h/2-fa/2);
		else // if( labelAlignment=='C'
			MovePen(x+(w-TextStringWidth(label))/2, y+h/2-fa/2);
		DrawTextString(label);
	}
}

/* 画一个菱形，并在其内部居中显示一个字符串标签label */
void drawDiamondBox(double x, double y, double w, double h, int fillflag, char *label, char labelAlignment, char *labelColor)
{
	double fa = GetFontAscent();
	// diamond 
	drawDiamond(x,y,w,h,fillflag);
	// text
	if( label && strlen(label)>0 ) {
		mySetPenColor(labelColor);
		if( labelAlignment=='L' )
			MovePen(x+fa/2, y+h/2-fa/2);
		else if( labelAlignment=='R' )
			MovePen(x+w-fa/2-TextStringWidth(label), y+h/2-fa/2);
		else // if( labelAlignment=='C'
			MovePen(x+(w-TextStringWidth(label))/2, y+h/2-fa/2);
		DrawTextString(label);
	}
}

/* 画一个圆形，并在其内部居中显示一个字符串标签label */
void drawCircleBox(double x, double y, double r, int fillflag, char *label, char labelAlignment, char *labelColor)
{
	double fa = GetFontAscent();
	// circle 
	drawCircle(x,y,r,fillflag);
	// text
	if( label && strlen(label)>0 )
	 {
		mySetPenColor(labelColor);
		if( labelAlignment=='L' )
			MovePen(x+fa/2, y+r/2-fa/2);
		else if( labelAlignment=='R' )
			MovePen(x+r-fa/2-TextStringWidth(label), y+r/2-fa/2);
		else // if( labelAlignment=='C'
			MovePen(x+(r-TextStringWidth(label))/2, y+r/2-fa/2);
		DrawTextString(label);
	}   
}

/* 画一个oval，并在其内部居中显示一个字符串标签label */
void drawOvalBox(double x, double y, double rx, double ry, int fillflag, char *label, char labelAlignment, char *labelColor)
{
	double fa = GetFontAscent();
	// oval 
	drawOval(x,y,rx,ry,fillflag);
	// text
	if( label && strlen(label)>0 ) {
		mySetPenColor(labelColor);
		if( labelAlignment=='L' )
			MovePen(x+fa/2, y+ry-fa/2);
		else if( labelAlignment=='R' )
			MovePen(x+2*rx-fa/2-TextStringWidth(label), y+ry-fa/2);
		else // if( labelAlignment=='C'
			MovePen(x+(2*rx-TextStringWidth(label))/2, y+ry-fa/2);
		DrawTextString(label);
	}
}
/* 画一个process，并在其内部居中显示一个字符串标签label */
void drawProcessBox(double x, double y, double w, double h, int fillflag, char *label, char labelAlignment, char *labelColor)
{
	double fa = GetFontAscent();
	// process
	drawProcess(x,y,w,h,fillflag);
	// text
	if( label && strlen(label)>0 ) {
		mySetPenColor(labelColor);
		if( labelAlignment=='L' )
			MovePen(x+fa/2, y+h/2-fa/2);
		else if( labelAlignment=='R' )
			MovePen(x+w-fa/2-TextStringWidth(label), y+h/2-fa/2);
		else // if( labelAlignment=='C'
			MovePen(x+(w-TextStringWidth(label))/2, y+h/2-fa/2);
		DrawTextString(label);
	}
}
void display()
{
	//clear
	DisplayClear();
	InitButton();
	drawlinklist1();
	drawlinklist2();
	drawlinklist3();
	drawlinklist4();
	drawlinklist5();
	drawlinklist6();
	drawlinklist7();
	drawlinklist8();
	drawlinklist9();
	drawlinklist10();
	Initwin();
}
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI字符输入
	display(); //刷新显示
}

// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event); // GUI获取键盘


}

// 用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event)
{
	double mx, my;
	uiGetMouse(x, y, button, event); //GUI获取鼠标
	mx = ScaleXInches(x);/*pixels --> inches*/
	my = ScaleYInches(y);/*pixels --> inches*/
	display();
	switch(event)
	{
		case BUTTON_DOWN:
		{
			if (button == RIGHT_BUTTON)
			{										
				if(operate_flag!=0)
					operate_flag = 0;
			}
			else if (button == LEFT_BUTTON)
			{
				if (operate_flag == 1)
				{
					if (mx > 18 * h && mx < winwidth - 8 * h && my<winheight - 3 * h && my>h)//当鼠标在画布区域左击
					{
						if (click_count == 0)				//当此时是取第一个点时，mx,my为左上点
						{
							click_count = 1;
							x_1 = mx;
							y_1 = my;
						}
						else
						{
							click_count = 2;
							x_2 = mx;
							y_2 = my;
							draw();
							display();
							click_count = 0;
							operate_flag = 0;
						}
					}
				}								
				else if (operate_flag == 0)
				{
					if (mx > 18 * h && mx < winwidth - 8 * h && my<winheight - 3 * h && my>h)//当鼠标在画布区域左击
					{
						if (click_count == 0)								//遍历所有得rect结构体确定选中得rect
						{
							select_graphic(mx,my);
							break;
						}
					}
				}
				else if (operate_flag == 2)
				{
					if (select_graphic(mx,my))
					{
						operate_flag = 3;
						x_1 = mx;
						y_1 = my;
						break;
					}
					else if(mx > 18 * h && mx < winwidth - 8 * h && my<winheight - 3 * h && my>h)
					{
						operate_flag = 0;
						break;
					}
				}
			}
			break;
		}
		case BUTTON_UP:
		{
			if (button == LEFT_BUTTON)
			{
				if (operate_flag == 3)
				{
					operate_flag = 2;
				}
			}
			break;
		}
		case MOUSEMOVE:
		{
			if (operate_flag == 3)
			{
				move( mx - x_1, my - y_1);
				y_1 = my;
				x_1 = mx;
			}
			break;
		}
		case ROLL_UP:
		{
			if (operate_flag == 2)
			{
				upper();						
				break;
			}
			break;
		}
		case ROLL_DOWN:
		{
			if (operate_flag == 2)
			{
				downer();
				break;
			}
			break;
		}
	}
}

// 用户的计时器时间响应函数
void TimerEventProcess(int timerID)
{
	if (2019 == timerID)
	{
		display();
	}
}
void drawlinklist1()//n 张linklist中储存着各个图元、每次display都会将所有链表中的图元输出
{
	myrect* p = rect_head->next;
	while (p != NULL)
	{
		SetPenColor(p->fill_color);
		drawBox(p->x, p->y, p->width, p->height, p->fillflag, p->text, p->alignment, p->front_color);
		//drawRectangle(p->x, p->y, p->width, p->height, p->fillflag);
		p = p->next;

	}
	return;
}
void drawlinklist2()
{
	myroundrect* p = roundrect_head->next;
	while (p != NULL)
	{
		
		SetPenColor(p->fill_color);
		drawRoundrecBox(p->x, p->y, p->width, p->height, p->fillflag, p->text, p->alignment, p->front_color);
		//drawRoundrec(p->x, p->y, p->width, p->height, p->fillflag);
		p = p->next;
	}
	return;
}
void drawlinklist3()
{
	mydiamond* p = diamond_head->next;
	while (p != NULL)
	{
		
		SetPenColor(p->fill_color);
		drawDiamondBox(p->x, p->y, p->width, p->height, p->fillflag, p->text, p->alignment, p->front_color);
		//drawDiamond(p->x, p->y, p->width, p->height, p->fillflag);
		p = p->next;
	}
	return;
}
void drawlinklist4()
{
	myline* p = line_head->next;
	while (p != NULL)
	{
		
		SetPenColor(p->pencolor);
		SetPenSize(p->pensize);
		drawLine(p->x1, p->y1, p->dx,p->dy);
		SetPenSize(1);
		p = p->next;
	}
	return;
}
void drawlinklist7()
{
	mydashline* p = dashline_head->next;
	while (p != NULL)
	{
		
		SetPenColor(p->pencolor);
		SetPenSize(p->pensize);
		drawDashline(p->x1, p->y1, p->dx, p->dy);
		SetPenSize(1);
		p = p->next;
	}
	return;
}
void drawlinklist5()
{
	mydirectionalconnection* p = directionalconnection_head->next;
	while (p != NULL)
	{
		SetPenColor(p->fill_color);
		SetPenSize(p->pensize);
		drawDirectionalconnection(p->x,p->y,p->dx,p->dy,p->fillflag,p->arrow_style);
		p = p->next;
		SetPenSize(1);

	}
	return;
}
void drawlinklist6()
{
	mybidirectionalconnection* p = bidirectionalconnection_head->next;
	while (p != NULL)
	{
		SetPenColor(p->fill_color);
		drawBidirectionalconnection(p->x, p->y, p->dx, p->dy, p->fillflag,p->arrow_style);
		p = p->next;

	}
	return;
}
void drawlinklist8()
{
	myprocess* p = process_head->next;
	while (p != NULL)
	{
		SetPenColor(p->fill_color);
		drawProcessBox(p->x, p->y, p->width, p->height, p->fillflag, p->text, p->alignment, p->front_color);
		//drawProcess//
		p = p->next;

	}
	return;
}
void drawlinklist9()
{
	mycircle* p = circle_head->next;
	while (p != NULL)
	{
		SetPenColor(p->fill_color);
		drawCircleBox(p->x, p->y, p->r, p->fillflag, p->text, p->alignment, p->front_color);
		//drawCircle//
		p = p->next;

	}
	return;
}

void drawlinklist10()
{
	myoval* p = oval_head->next;
	while (p != NULL)
	{
		SetPenColor(p->fill_color);
		drawOvalBox(p->x, p->y, p->rx, p->ry, p->fillflag, p->text, p->alignment, p->front_color);
		//drawOval
		p = p->next;

	}
	return;
}
int  select_graphic(double mx,double my)
{
	myrect* p = rect_head->next;
	while (p != NULL)
	{
		if (mx >= p->x && mx <= (p->x + p->width) && my >= p->y && my <= (p->y + p->height))
		{
			operate_flag = 2;
			selected_rect = p;
			select_what = 1;
			return 1;
		}
		p = p->next;
	}
	myroundrect* q = roundrect_head->next;
	while (q != NULL)
	{
		if (mx >= q->x && mx <= (q->x + q->width) && my >= q->y && my <= (q->y + q->height))
		{
			operate_flag = 2;
			selected_roundrect = q;
			select_what = 2;
			return 1;
		}
		q = q->next;
	}
	myline* o = line_head->next;
	while (o != NULL)
	{
		if ((my>=(o->dy*(mx-o->x1)/o->dx+o->y1-0.1))&& (my <= (o->dy * (mx - o->x1) / o->dx + o->y1 + 0.1)))
		{
			operate_flag = 2;
			selected_line= o;
			select_what = 4;
			return 1;
		}
		o = o->next;
	}
	mydiamond* s = diamond_head->next;
	while (s != NULL)
	{
		if (mx >= s->x && mx <= (s->x + s->width) && my >= s->y && my <= (s->y + s->height))
		{
			operate_flag = 2;
			selected_diamond = s;
			select_what = 3;
			return 1;
		}
		s = s->next;
	}
	
	mydirectionalconnection* t = directionalconnection_head->next;
	while (t != NULL)
	{
		if ((my >= (t->dy * (mx - t->x) / t->dx + t->y - 0.1)) && (my <= (t->dy * (mx - t->x) / t->dx + t->y + 0.1)))
		{
			operate_flag = 2;
			selected_directionalconnection = t;
			select_what = 5;
			return 1;
		}
		t = t->next;
	}

	mybidirectionalconnection* u = bidirectionalconnection_head->next;
	while (u != NULL)
	{
		if ((my >= (u->dy * (mx - u->x) / u->dx + u->y - 0.1)) && (my <= (u->dy * (mx - u->x) / u->dx + u->y + 0.1)))
		{
			operate_flag = 2;
			selected_bidirectionalconnection = u;
			select_what = 6;
			return 1;
		}
		u = u->next;
	}

	myprocess* v = process_head->next;
	while (v != NULL)
	{
		if (mx >= v->x && mx <= (v->x + v->width) && my >= v->y && my <= (v->y + v->height))
		{
			operate_flag = 2;
			selected_process = v;
			select_what = 8;
			return 1;
		}
		v = v->next;
	}
	mydashline* w = dashline_head->next;
	while (w != NULL)
	{
		if ((my >= (w->dy * (mx - w->x1) / w->dx + w->y1 - 0.1)) && (my <= (w->dy * (mx - w->x1) / w->dx + w->y1 + 0.1)))
		{
			operate_flag = 2;
			selected_dashline = w;
			select_what = 7;
			return 1;
		}
		w = w->next;
	}
	mycircle* x = circle_head->next;
	while (x != NULL)
	{
		double distance = sqrt((mx - x->x) * (mx - x->x) + (my - x->y) * (my - x->y));
		if (distance <= x->r)
		{
			operate_flag = 2;
			selected_circle = x;
			select_what = 9;
			return 1;
		}
		x = x->next;
	}
	myoval* y = oval_head->next;
	while (y != NULL)
	{
		if ((pow(mx-y->x-y->rx,2)/pow(y->rx,2) + pow(my-y->y-y->ry,2)/pow(y->ry,2))<= 1)
		{
			operate_flag = 2;
			selected_oval = y;
			select_what = 10;
			return 1;
		}
		y = y->next;
	}
	
	return 0;
}
