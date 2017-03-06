
class CpuzzleDlg;

class MyPuzzle {
	public:
		int puzzles[4][4];		//虚拟迷宫矩阵
		int bx, by;					//空白坐标
		int dx, dy;					//已绘图坐标
		bool israndom;		//随机移动判断
		CStatic *pics[16];		//控件指针
		CpuzzleDlg *dlg;		//对话框指针

		MyPuzzle();
		void SetDlg(CpuzzleDlg *wnddlg);
		void RandomMove();
		int GetBlankDirection(int x, int y);
		void MovePic(int x, int y);
		bool IsSamePoint(int x, int y);
		bool IsWin();
		void DrawFrame(int x, int y);
		void EraseFrame();
		void EraseBlank();
};


