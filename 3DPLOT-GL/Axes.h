#pragma once
class Axes
{
public:
	Axes();
	~Axes();
	/*
	* � ������ ������ ������������ ��������� ���� ����������� ������� Axes
	*/
	void paintAxes();			
	
	void showXAxisGrid();
	void showYAxisGrid();
	void showZAxisGrid();

	void showXAxis();
	void showYAxis();
	void showZAxis();
	
	void showXAxisText();
	void showYAxisText();
	void showZAxisText();

	void showXYZPlate();

	void setShowXAxis(bool show);								// ����������� �� ��� X
	void setShowYAxis(bool show);								// ����������� �� ��� Y
	void setShowZAxis(bool show);								// ����������� �� ��� Z

	void setShowXAxisGrid(bool show);							// ����������� �� ����� X
	void setShowYAxisGrid(bool show);							// ����������� �� ����� Y
	void setShowZAxisGrid(bool show);							// ����������� �� ����� Z

	void setShowXYZAxisPlate(bool show);						// ����������� ��������� XYZ

	void setShowXAxisText(bool show);
	void setShowYAxisText(bool show);
	void setShowZAxisText(bool show);

	bool isXAxis();												// ������������ �� ��� X
	bool isYAxis();												// ������������ �� ��� Y
	bool isZAxis();												// ������������ �� ��� Z
															
	bool isXAxisGrid();											// ������������ �� ��������� X
	bool isYAxisGrid();											// ������������ �� ��������� Y
	bool isZAxisGrid();											// ������������ �� ��������� Z
		
	bool isshowXYZPlate();										// ������������ �� ��������� XYZ
	
	bool isXAxisText();											// ������������ �� ������� ������� ��� X
	bool isYAxisText();											// ������������ �� ������� ������� ��� Y
	bool isZAxisText();											// ������������ �� ������� ������� ��� Z

private:
	bool XAxisGrid = true; 
	bool YAxisGrid = true;
	bool ZAxisGrid = true;

	bool XYZPlate = true;

	bool XAxis = true;
	bool YAxis = true;
	bool ZAxis = true;

	bool XAxisText = true;
	bool YAxisText = true;
	bool ZAxisText = true;
};

