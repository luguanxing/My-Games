
class Solider {
	CStatic *pic;
	HBITMAP *hbs;
	public:
		Solider();
		void Set(CStatic *dlgpic, HBITMAP *dlghbs);
		void SetPic(int num);
		void Stand();
		void Up();
		void Down();
		void Left();
		void Right();
};

class Knight {
	CStatic *pic;
	HBITMAP *hbs;
	public:
		Knight();
		void Set(CStatic *dlgpic, HBITMAP *dlghbs);
		void SetPic(int num);
		void Stand();
};