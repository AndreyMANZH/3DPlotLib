#pragma once
class Axes
{
public:
	Axes();
	~Axes();
	/*
	* В данном методе производится отрисовка всех компонентов объекта Axes
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

	void setShowXAxis(bool show);								// Отображаеть ли ось X
	void setShowYAxis(bool show);								// Отображаеть ли ось Y
	void setShowZAxis(bool show);								// Отображаеть ли ось Z

	void setShowXAxisGrid(bool show);							// Отображаеть ли сетку X
	void setShowYAxisGrid(bool show);							// Отображаеть ли сетку Y
	void setShowZAxisGrid(bool show);							// Отображаеть ли сетку Z

	void setShowXYZAxisPlate(bool show);						// Отображаеть плоскости XYZ

	void setShowXAxisText(bool show);
	void setShowYAxisText(bool show);
	void setShowZAxisText(bool show);

	bool isXAxis();												// Отображается ли ось X
	bool isYAxis();												// Отображается ли ось Y
	bool isZAxis();												// Отображается ли ось Z
															
	bool isXAxisGrid();											// Отображается ли плоскость X
	bool isYAxisGrid();											// Отображается ли плоскость Y
	bool isZAxisGrid();											// Отображается ли плоскость Z
		
	bool isshowXYZPlate();										// Отображается ли плоскость XYZ
	
	bool isXAxisText();											// Отображается ли подпись делений оси X
	bool isYAxisText();											// Отображается ли подпись делений оси Y
	bool isZAxisText();											// Отображается ли подпись делений оси Z

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

