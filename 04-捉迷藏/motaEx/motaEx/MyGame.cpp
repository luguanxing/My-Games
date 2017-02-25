#include "stdafx.h"
#include "motaEx.h"
#include "MyGame.h"
#include "motaExDlg.h"

/////////////////////////////初始化/////////////////////////////////////
MyGame *pmygame;

MyGame::MyGame() {	
	caughtnum = 0;
	dlgwidth = 0;
	dlgheight = 0;
	dlg = NULL;
}

void MyGame::SetDlg(CmotaExDlg *dlg) {
	//设置窗口和控件指针
	this->dlg = dlg;
	GetWindowRect(dlg->m_hWnd, &dlg->mygame.rectdlg);
	dlgwidth = dlg->mygame.rectdlg.right-dlg->mygame.rectdlg.left;
	dlgheight = dlg->mygame.rectdlg.bottom-dlg->mygame.rectdlg.top;
}

/////////////////////////完整动作接口，包括移动图片和改变播放线程//////////////////////////////
void MyGame::SoliderUp() {	
	solider.PlaySoliderDirection(0);
	GetSoliderPos();
	if (rects.top >= 3) {
		rects.top -= 3;
		rects.bottom -= 3;
	}
	dlg->m_solider.MoveWindow(rects);
}
void MyGame::SoliderDown() {
	solider.PlaySoliderDirection(1);
	GetSoliderPos();
	if (rects.bottom <= dlgheight-30) {
		rects.top += 3;
		rects.bottom += 3;
	}
	dlg->m_solider.MoveWindow(rects);
}
void MyGame::SoliderLeft() {
	solider.PlaySoliderDirection(2);
	GetSoliderPos();
	if (rects.left >= 3) {
		rects.left -= 3;
		rects.right -= 3;
	}
	dlg->m_solider.MoveWindow(rects);
}
void MyGame::SoliderRight() {
	solider.PlaySoliderDirection(3);
	GetSoliderPos();
	if (rects.right <= dlgwidth - 11) {
		rects.right += 3;
		rects.left += 3;
	}
	dlg->m_solider.MoveWindow(rects);
}
void MyGame::SoliderStop() {
	solider.SetSoliderDirection(solider.directions);
}



void MyGame::KnightUp() {
	knight.PlayKnightDirection(0);
	GetKnightPos();
	if (rectk.top >= 3) {
		rectk.top -= 1;
		rectk.bottom -= 1;
	}
	dlg->m_knight.MoveWindow(rectk);
}
void MyGame::KnightDown() {
	knight.PlayKnightDirection(1);
	GetKnightPos();
	if (rectk.bottom <= dlgheight-30) {
		rectk.top += 1;
		rectk.bottom += 1;
	}
	dlg->m_knight.MoveWindow(rectk);
}
void MyGame::KnightLeft() {
	knight.PlayKnightDirection(2);
	GetKnightPos();
	if (rectk.left >= 3) {
		rectk.left -= 1;
		rectk.right -= 1;
	}
	dlg->m_knight.MoveWindow(rectk);
}
void MyGame::KnightRight() {
	knight.PlayKnightDirection(3);
	GetKnightPos();
	if (rectk.right <= dlgwidth - 8) {
		rectk.right += 1;
		rectk.left += 1;
	}
	dlg->m_knight.MoveWindow(rectk);
}

////////////////////////////游戏基本函数//////////////////////////////////////

bool MyGame::IsCollision() {
	RECT rect, rect1, rect2;
	dlg->m_solider.GetWindowRect(&rect1);
	dlg->m_knight.GetWindowRect(&rect2);
	return IntersectRect(&rect, &rect1, &rect2);
}

int random(int max) {
	CTime t = CTime::GetCurrentTime();
	int n = t.GetMinute() * 60 + t.GetSecond();
	while(n-- > 0)
		rand();
	return rand()%max;
}
void MyGame::CheckCollision() {
	while (IsCollision()){
		TRACE("抓到了\n");
		SoliderIsCaught();
		int x = random(this->dlgwidth-30);
		int y = random(this->dlgheight-70);
		solider.SetSoliderDirection(solider.directions);
		SetSoliderPos(x,y);
	}
}
void MyGame::SetSoliderPos(int x, int y) {
	dlg->m_solider.MoveWindow(x, y, 32, 32);
}
void MyGame::GetSoliderPos() {
	dlg->m_solider.GetWindowRect(&rects);	//获取控件的屏幕坐标
	dlg->ScreenToClient(&rects);	//转换为对话框上的客户坐标
}
void MyGame::GetKnightPos() {
	dlg->m_knight.GetWindowRect(&rectk);	//获取控件的屏幕坐标
	dlg->ScreenToClient(&rectk);	//转换为对话框上的客户坐标
}

///////////////////////////AI追玩家////////////////////////////////////
DWORD WINAPI ChaseSolider(LPVOID lpParam) {
	while (true) {
		RECT rects, rectk;
		pmygame->solider.m_cs_solider->GetWindowRect(&rects);
		pmygame->knight.m_cs_knight->GetWindowRect(&rectk);

		int soliderx, solidery;
		soliderx = rects.left;
		solidery = rects.top;

		int knightx, knighty;
		knightx = rectk.left;
		knighty = rectk.top;

		if (soliderx < knightx) {				//目标在左边
			pmygame->KnightLeft();
		} else if (soliderx > knightx) {		//目标在右边
			pmygame->KnightRight();
		} else {											//目标在同列
			if (solidery > knighty) {								//目标在下面
				pmygame->KnightDown();
			} else if (solidery < knighty) {						//目标在上面
				pmygame->KnightUp();
			} else {															//抓到了

			}
		}
		::Sleep(20);
	}
}
void MyGame::MoveKnight() {
	pmygame = this;
	::CreateThread(NULL, 0, ChaseSolider, NULL,  NULL,  NULL);
}

void MyGame::SoliderIsCaught() {
	WCHAR wbuff[255];
	wsprintf(wbuff, L"捉迷藏 （被抓：%d次）", ++caughtnum);
	pmygame->dlg->SetWindowText(wbuff);
}