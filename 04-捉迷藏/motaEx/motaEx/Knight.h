#pragma once

class Knight {
	public:
		CStatic *m_cs_knight;
		HBITMAP hbk[16];
		HANDLE hthreadk[4];
		bool runningk[4];
		int directionk;

		Knight();
		void SetCStatic(CStatic *m_knight);
		void PlayKnightDirection(int direction);	
};