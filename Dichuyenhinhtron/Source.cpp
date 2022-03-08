#include <afxwin.h>
#include <iostream>
#include <string>

using namespace std;

class DrawAndMove : public CFrameWnd {
public:
	DrawAndMove() {
		Create(NULL, _T("Main - Draw and move"));
		m_Width = 0;
		m_Height = 0;
	}

protected:
	int m_Width, m_Height;
	//Khai báo bán kính
	int radius = 50;
	//Khai báo biến xác định click được hay không
	bool clickAble = true;
	//Khai báo biến xác định xem click vào hình tròn nào
	int chooseCricle = true;
	// Khai báo bốn tâm hình tròn + bốn tâm lưu vị trí cũ(dùng để lưu lại nếu muốn reset)
	POINT c1, c2, c3, c4;
	POINT lc1, lc2, lc3, lc4;
	
	afx_msg int OnCreate(LPCREATESTRUCT lpStruct) {
		//Định nghĩa vị trí của các tâm hình tròn
		CRect mRect;
		GetClientRect(&mRect);
		m_Width = mRect.Width();
		m_Height = mRect.Height();
		
		lc1 = c1 = { 50,50 };
		lc2 = c2 = { m_Width - 50,50 };
		lc3 =  c3 = { 50 ,m_Height - 50 };
		lc4 = c4 = { m_Width - 50 ,m_Height - 50 };
		
		return 0;
	}
	// Hàm kiểm tra có thuộc hình tròn hay không
	bool CheckIbCircle(POINT center, CPoint point, int radius) {
		float kc;
		kc = sqrt((point.x - center.x) * (point.x - center.x) + (point.y - center.y) * (point.y - center.y));
		if (kc <= radius) {
			return true;
			
		}
		else {
			return false;
		}
	}

	afx_msg void OnPaint() {
		CPaintDC dc(this);
				
		//Draw
		int padding = 100;
		
		float perX, perY;
		int m_Top, m_Left, m_Right, m_Bottom;
		// vẽ hình tròn theo các tâm
		// top = tâm.x - bán kính
		// left = tâm.y - bán kính
		// right = tâm.x + bán kính
		// bottm = tâm.y + bán kính
		dc.Ellipse(c1.x - radius, c1.y - radius, c1.x + radius, c1.y + radius);
		dc.Ellipse(c2.x - radius, c2.y - radius, c2.x + radius, c2.y + radius);
		dc.Ellipse(c3.x - radius, c3.y - radius, c3.x + radius, c3.y + radius);
		dc.Ellipse(c4.x - radius, c4.y - radius, c4.x + radius, c4.y + radius);
		// Vẽ lưới		
		dc.MoveTo(0, padding);
		dc.LineTo(m_Width, padding);

		dc.MoveTo(0, m_Height - padding);
		dc.LineTo(m_Width, m_Height - padding);

		dc.MoveTo(padding, 0);
		dc.LineTo(padding, m_Height);

		dc.MoveTo(m_Width - padding, 0);
		dc.LineTo(m_Width - padding, m_Height);

		dc.MoveTo(m_Width / 2, 0);
		dc.LineTo(m_Width / 2, m_Height);
		//				
	}
	// Hàm di chuyển
	//Hàm này sẽ tác động trực tiếp lên biến tâm
	void Move(POINT& point, int step) {
		//tâm + bước nhảy
		point.x = point.x + step;
		//check xem liệu đã đến đích chưa 
		//(point.x < radius) là đến góc trái màn hình
		//(point.x > m_Width - radius)) là đến góc phải màn hình
		if (point.x < radius || point.x > m_Width - radius) {
			MessageBox(L"Đã chạy hết");
			// Khi đến đích gọi lại Hàm Reset để trả lại giá trị ban đầu của các tâm
			Reset();
		}
		//Hàm gọi vẽ lại màn hình
		Invalidate();
		
	}
	void Reset() {
		// xét có thể click được
		clickAble = true;
		//trả tâm về giá trị bán đầu
		c1 = lc1;
		c2 = lc2;
		c3 = lc3;
		c4 = lc4;
	}
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point) {
		//Kiểm tả xem có click được không
		if (!clickAble) {
			//Nếu ko đc thông báo là ko đc click
			MessageBox(L"Đang chọn đường tròn không thể click");
		}
		else {
			//Nếu click đc kiểm tra xem có thuộc đường tròn không
			//Nếu đã ckick chúng đường chọn để biến cọn đường tròn chạy thoe các số 1-4 tương ứng với 4 loại đường tròn
			//Và set không click được
			if (CheckIbCircle(c1, point, radius)) {
				MessageBox(L"Đang chọn đường tròn 1");
				chooseCricle = 1;
				clickAble = false;
			}
			else if (CheckIbCircle(c2, point, radius)) {
				MessageBox(L"Đang chọn đường tròn 2");
				chooseCricle = 2;
				clickAble = false;
			}
			else if (CheckIbCircle(c3, point, radius)) {
				MessageBox(L"Đang chọn đường tròn 3");
				chooseCricle = 3;
				clickAble = false;
			}
			else if (CheckIbCircle(c4, point, radius)) {
				MessageBox(L"Đang chọn đường tròn 4");
				chooseCricle = 4;
				clickAble = false;
			}
			
		}
	}
	
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
		// Kiểm tra xem liệu đã không còn click hay chưa?

		if (!clickAble ) {
			// Kiểm tả nếu nút mũi tên phải được nhấn
			//Tra GG bảng mã ASCII để biết thêm chi tiết
			if (nChar == 39) {
				// Nếu đúng kiểm tra hình tròn nào đang được nhấn
				if (chooseCricle == 1) {
					// chạy Hình tròn
					Move(c1, 20);
				}
				else if (chooseCricle == 3) {
					Move(c3, 20);
				}
				else {
					MessageBox(L"ko đi đc hướng này");
				}
			}
			// Kiểm tả nếu nút mũi tên trái được nhấn
			else if (nChar == 37) {
				if (chooseCricle == 2) {
					//Tương tự
					Move(c2, -20);
				}
				else if (chooseCricle == 4) {
					Move(c4, -20);
				}
				else {
					MessageBox(L"ko đi đc hướng này");
				}
			}
		}		
	}
	afx_msg void OnSize(UINT someParam, int width, int height) {
		m_Width = width;
		m_Height = height;	
	}

private:
	DECLARE_MESSAGE_MAP()
};

//Link method
BEGIN_MESSAGE_MAP(DrawAndMove, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

class MyApp : public CWinApp {
	//Báº¯t buá»™c
	BOOL InitInstance() {
		DrawAndMove* frame = new DrawAndMove();
		m_pMainWnd = frame;
		frame->ShowWindow(SW_NORMAL);
		frame->UpdateWindow();

		return TRUE;
	}
};

MyApp theAPP;