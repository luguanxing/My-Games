#pragma once

class Solider {
	public:
		CStatic *m_cs_solider;	//图片控件指针
		HBITMAP hbs[16];	//动画图片
		HANDLE hthreads[4];	//播放动画线程
		bool runnings[4];		//播放动画线程记录标志
		int directions;	//相应keyup消息并设置方向图片和暂停播放动画线程

		Solider();
		void SetCStatic(CStatic *m_solider);
		void SetSoliderDirection(int direction);		//固定播放方向动画
		void PlaySoliderDirection(int direction);	//设置播放方向动画
};