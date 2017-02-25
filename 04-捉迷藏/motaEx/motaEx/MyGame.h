#pragma once

#include "Solider.h"
#include "Knight.h"

class CmotaExDlg;

class MyGame {
	private:
		int caughtnum;
		int dlgwidth;  	//窗口大小
		int dlgheight;
		CRect rects; 	//控件位置
		CRect rectk; 
		CRect rectdlg; 
		CmotaExDlg *dlg;	//窗口指针

	public:
		Solider solider;
		Knight knight;
		MyGame();
		void SetDlg(CmotaExDlg *dlg);
		void SoliderUp();		//播放动画
		void SoliderDown();
		void SoliderLeft();
		void SoliderRight();
		void SoliderStop();	//停止播放动画

		void KnightUp();
		void KnightDown();
		void KnightLeft();
		void KnightRight();

		bool IsCollision();
		void CheckCollision();
		void SoliderIsCaught();
		void MoveKnight();
		void SetSoliderPos(int x, int y);
		void GetSoliderPos();
		void GetKnightPos();
};